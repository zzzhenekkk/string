#include "string.h"

int s21_sprintf(char *str, const char *format, ...) {
  char *str_begin = str;  // понадобится для вычисления длины на return
  va_list vl;
  va_start(vl, format);

  // обрабатываем каждый элемент формата, если не встретили %, записываем в str,
  // иначе парсим спецификатор с флагами
  while (*format) {
    if (*format != '%') {
      *str = *format;
      str++;
      format++;

    } else {
      format++;
      // сюда записываем все флаги и значения для спецификатора
      options_sprintf opt = {0};
      parsing(&format, &opt, &str, &vl, str_begin);
    }
  }
  va_end(vl);
  return ((int)(str - str_begin));
}

// str куда записываем
// format форматная строка со спецификаторами откуда считываем

void parsing(const char **format, options_sprintf *opt, char **str, va_list *vl,
             char *str_begin) {
  // считываем данные из format
  get_opt(format, opt, vl);
  // обрабатываем и записываем в str
  push_opt(opt, str, vl, str_begin);
}

void get_opt(const char **format, options_sprintf *opt, va_list *vl) {
  // считываем все по порядку, пример форматной строки "%+-010.-1hd"
  get_flags(format, opt);      // считываем флаги +- #0
  get_width(format, opt, vl);  // считываем ширину
  get_precision(format, opt, vl);  // считываем точность, это та которая идет
                                   // после точки, в том числе отрицательную
  get_length(format,
             opt);  // считываем длину спецификатора hlL - short,long,double
  get_specifiers(format, opt);  // считываем спецификатор cdieEfFgGosuxXpn%
  check_conflict_flags(opt);  // для настройки флагов, установки с-мы счисления
}

void push_opt(options_sprintf *opt, char **str, va_list *vl, char *str_begin) {
  // буфер , перед тем как все сохранять в str, записываме туда
  char buf[8100] = {0};

  if (opt->specifiers == 'd' || opt->specifiers == 'i') {
    work_decimal(opt, str, vl, buf);
  } else if (opt->specifiers == 'u' || opt->specifiers == 'o' ||
             opt->specifiers == 'x' || opt->specifiers == 'X') {
    work_unsigned(opt, str, vl, buf);
  } else if (opt->specifiers == 'c') {
    work_symbol(opt, str, vl, buf);
  } else if (opt->specifiers == 's') {
    work_str(opt, str, vl);
  } else if (opt->specifiers == 'p') {
    work_unsigned(opt, str, vl, buf);
  } else if (opt->specifiers == 'n') {
    long long int *n = (long long int *)va_arg(*vl, long long int *);
    *n = (long long int)(*str - str_begin);
  } else if (opt->specifiers == '%') {
    work_percent(opt, str, buf);
  } else if (opt->specifiers == 'f' || opt->specifiers == 'F') {
    work_double(opt, str, vl, buf);
  } else if (opt->specifiers == 'e' || opt->specifiers == 'E') {
    work_e(opt, str, vl, buf);
  } else if (opt->specifiers == 'g' || opt->specifiers == 'G') {
    work_g(opt, str, vl, buf);
  }
}

void work_g(options_sprintf *opt, char **str, va_list *vl, char *buf) {
  long double var_double = 0;
  if (opt->length == 'L') {
    var_double = (long double)va_arg(*vl, long double);
  } else {
    var_double = (double)va_arg(*vl, double);
  }
  // проверка на недопустимое значение NAN INFINITY
  if (!isnan(var_double) && !isinf(var_double)) {
    // проверяет отрицательное ли число, и переводит в положительное
    opt->negative = var_double < 0 ? 1 : 0;
    var_double = var_double < 0 ? -var_double : var_double;

    // приводит число с плав. точкой к виду 1<=f<10 и записывает степень в
    // opt->exponent
    long double var_double_2 = var_double;
    normilize(&var_double_2, opt);

    // в зависимости от степени, определяем в каком виде обрабатывать e или f
    // где e - научная нотация (степень < -4 или >5), f - число с плавающей
    // точкой (-4<=f<=5)
    if (opt->exponent < -4 || opt->exponent > 5) {
      opt->exponent = 0;
      itoa_and_precision_for_e(buf, opt, var_double);
    } else {
      opt->exponent = 0;
      itoa_and_precision_for_f(buf, opt, var_double);
    }
    add_width(buf, opt);        // устанавливаем ширину
    save_buf_in_str(str, buf);  // сохраняем буфер в строку

    // если считываемое число не определено или
  } else if (isnan(var_double)) {
    s21_strcat(buf, opt->specifiers == 'G' ? "NAN" : "nan");
    save_buf_in_str(str, buf);
  } else if (isinf(var_double)) {
    s21_strcat(buf, opt->specifiers == 'G' ? "FNI" : "fni");
    s21_strcat(buf, var_double > 0 ? "+" : "-");
    save_buf_in_str(str, buf);
  }
}

void work_e(options_sprintf *opt, char **str, va_list *vl, char *buf) {
  long double var_double = 0;
  if (opt->length == 'L') {
    var_double = (long double)va_arg(*vl, long double);
  } else {
    var_double = (double)va_arg(*vl, double);
  }

  if (!isnan(var_double) && !isinf(var_double)) {
    itoa_and_precision_for_e(buf, opt, var_double);
    add_width(buf, opt);
    save_buf_in_str(str, buf);

  } else if (isnan(var_double)) {
    s21_strcat(buf, opt->specifiers == 'E' ? "NAN" : "nan");
    save_buf_in_str(str, buf);
  } else if (isinf(var_double)) {
    s21_strcat(buf, opt->specifiers == 'E' ? "FNI" : "fni");
    s21_strcat(buf, var_double > 0 ? "+" : "-");
    save_buf_in_str(str, buf);
  }
}

void work_double(options_sprintf *opt, char **str, va_list *vl, char *buf) {
  long double var_double = 0;
  if (opt->length == 'L') {
    var_double = (long double)va_arg(*vl, long double);
  } else {
    var_double = (double)va_arg(*vl, double);
  }

  // проверка на NAN - недопустимое значение,
  // INFINITY - число выходит за пределы диапазона
  if (!isnan(var_double) && !isinf(var_double)) {
    itoa_and_precision_for_f(buf, opt, var_double);  //
    add_width(buf, opt);        // устаналвиаем ширину
    save_buf_in_str(str, buf);  // сохраняем буфер в строку

    // если nan или infinity, то выводим следующую шляпу
  } else if (isnan(var_double)) {
    s21_strcat(buf, opt->specifiers == 'F' ? "NAN" : "nan");
    save_buf_in_str(str, buf);
  } else if (isinf(var_double)) {
    s21_strcat(buf, opt->specifiers == 'F' ? "FNI" : "fni");
    s21_strcat(buf, var_double > 0 ? "+" : "-");
    save_buf_in_str(str, buf);
  }
}

void normilize(long double *var_double, options_sprintf *opt) {
  if (*var_double >= 10.0) {
    while (*var_double > 10.0) {
      *var_double /= 10.0;
      opt->exponent++;
    }
  } else if (*var_double < 1.0 && *var_double) {
    while (*var_double < 1.0) {
      *var_double *= 10.0;
      opt->exponent--;
    }
  }
}

void itoa_and_precision_for_e(char *buf, options_sprintf *opt,
                              long double var_double) {
  // обрабтываем отрицательное число
  opt->negative = var_double < 0 ? 1 : 0;
  var_double = var_double < 0 ? -var_double : var_double;

  // приводит числ с плав. точкой к виду 1<=f<10, записывает степень
  // в opt->exponent
  normilize(&var_double, opt);

  // для точности -1, остается только целая часть
  if (opt->precision == -1) var_double = roundl(var_double);

  // если не введена точность, то по умолчанию 6
  if (!opt->is_precision) opt->precision = 6;
  // для специфиатора gG точность на один меньше
  if (opt->specifiers == 'g' || opt->specifiers == 'G') {
    opt->precision--;
  }
  // разделяем число на целую и дробную часть, left - целая, right - дробная
  long double left = 0;
  long double right = modfl(var_double, &left);

  long long lleft = left;
  char left_str[500] = {'\0'};
  char right_str[500] = {'\0'};

  // для установления точности числа, вначале переводим его в целую часть, до
  // указанной точности
  for (int i = 0; i < opt->precision; i++) {
    right *= 10;
  }

  long long rright =
      roundl(right);  // roundl - округление до ближайшего целого, чтобы
  if (rright) {
    // записывает правую часть в строку
    s21_itoa(right_str, opt, rright);
  }

  // дописываем нули при точности большей чем длина после точки
  while (opt->precision != -1 && (int)s21_strlen(right_str) < opt->precision) {
    right_str[s21_strlen(right_str)] = '0';
  }

  // переводим левую часть в строку
  s21_itoa(left_str, opt, lleft);

  // переводим opt->exponent в буфер
  s21_itoa(buf, opt, opt->exponent);
  // дописываем ноль, если e от 0 до 9, потому что вид 1e+03 c двумя нулями
  if (s21_strlen(buf) == 1) {
    buf[1] = '0';
  }
  // дописываем знак +- и Е
  s21_strcat(buf, opt->exponent >= 0 ? "+" : "-");
  s21_strcat(buf, opt->uppercase ? "E" : "e");

  // переводим все в буфер, склеиваем строку
  if (s21_strlen(right_str)) {
    s21_strcat(buf, right_str);
    s21_strcat(buf, ".");
  }
  s21_strcat(buf, left_str);
}

void itoa_and_precision_for_f(char *buf, options_sprintf *opt,
                              long double var_double) {
  // отрицательное ли число, для спецификаторов gG у нас проверяется отдельно
  if (!s21_strchr("gG", opt->specifiers))
    opt->negative = var_double < 0 ? 1 : 0;
  var_double = var_double < 0 ? -var_double : var_double;

  // для точности -1, округляем все число до целой части
  if (opt->precision == -1) var_double = roundl(var_double);

  // если не введена точность, то по умолчанию 6
  if (!opt->is_precision) opt->precision = 6;

  // разделяем число на целую и дробную часть, left - целая, right - дробная
  long double left = 0;
  long double right = modfl(var_double, &left);

  long long lleft = left;
  char left_str[1000] = {'\0'};
  char right_str[1000] = {'\0'};
  long double rrright = right;
  long double lllleft;

  // для спецификатора gG убираем лишние нули после запятой, то есть выводим
  // кратчайшую запись
  if (s21_strchr("gG", opt->specifiers)) {
    int count = 0;
    // для этого раздеяем на дробную и целую часть и смотрим не равна ли у нас
    // дробная часть 0, 1e-6 - используется потому что машинный ноль
    // воспринимается не точно, а с границами относительной погрешности
    while (modfl(rrright, &lllleft) >= 1e-6) {
      rrright *= 10;
      count++;
    }

    if (opt->precision > count) opt->precision = count;
  }

  // для установления точности числа, вначале переводим его в целую часть, до
  // указанной точности
  for (int i = 0; i < opt->precision; i++) {
    right *= 10;
  }

  // округляем правую часть под указанную точность
  long long rright =
      roundl(right);  // roundl - округление до ближайшего целого, чтобы
  if (rright) {
    // записывает в буфер правую часть
    s21_itoa(right_str, opt, rright);
  }

  // дописываем нули при точности большей чем длина после точки
  while (opt->precision != -1 && (int)s21_strlen(right_str) < opt->precision) {
    right_str[s21_strlen(right_str)] = '0';
  }

  // переводим левую часть в строку
  s21_itoa(left_str, opt, lleft);

  // переводим все в буфер, склеиваем строку
  if (s21_strlen(right_str)) {
    s21_strcat(buf, right_str);
    s21_strcat(buf, ".");
  }
  s21_strcat(buf, left_str);
}

void work_percent(options_sprintf *opt, char **str, char *buf) {
  *buf = '%';
  add_precision(buf, opt);
  add_width(buf, opt);
  save_buf_in_str(str, buf);
}

void work_str(options_sprintf *opt, char **str, va_list *vl) {
  char *str_arg = (char *)va_arg(*vl, char *);
  if (str_arg) {
    long long unsigned int len = s21_strlen(str_arg);
    long long unsigned int len_d = len;
    // если ширина или точность больше len, то записываем ее в len_d, чтобы
    // выделить память!
    if ((long long unsigned int)opt->width > len) len_d = opt->width;
    if ((long long unsigned int)opt->precision > len) len_d = opt->precision;

    // если мы указываем точность меньше чем длина строки, то строка уменьшается
    if (opt->is_precision && (long long unsigned int)opt->precision < len)
      len = opt->precision;
    char *str_buf = calloc(sizeof(char), len_d + 100);
    if (str_buf) {
      // Заполянем буфер
      long long unsigned int i = 0;
      while (len > 0) {
        len--;
        str_buf[i] = str_arg[len];
        i++;
      }
      add_precision(str_buf, opt);
      add_width(str_buf, opt);
      save_buf_in_str(str, str_buf);
      free(str_buf);
    }

  } else {
    **str = 0;
  }
}

void work_symbol(options_sprintf *opt, char **str, va_list *vl, char *buf) {
  int symbol = (int)va_arg(*vl, int);
  *buf = symbol;
  add_precision(buf, opt);
  add_width(buf, opt);
  save_buf_in_str(str, buf);
}

void work_unsigned(options_sprintf *opt, char **str, va_list *vl, char *buf) {
  unsigned long int var_decimal;
  if (opt->length == 'h') {
    var_decimal = (unsigned int)va_arg(*vl, unsigned int);
  } else if (opt->length == 'l') {  // "%ld"
    var_decimal = (unsigned long int)va_arg(*vl, unsigned long int);
  } else {
    var_decimal = (unsigned int)va_arg(*vl, unsigned int);
  }

  // преобразует число в строку и записывает наоборот
  s21_itoa(buf, opt, var_decimal);

  // дополняет нулями, если есть точность больше чем число
  add_precision(buf, opt);

  // устанавливаем ширину
  add_width(buf, opt);

  // сохраняем буфер в строку
  save_buf_in_str(str, buf);
}

// работаем с d или i
void work_decimal(options_sprintf *opt, char **str, va_list *vl, char *buf) {
  long int var_decimal;
  if (opt->length == 'h') {
    var_decimal = (int)va_arg(*vl, int);
  } else if (opt->length == 'l') {  // "%ld"
    var_decimal = (long int)va_arg(*vl, long int);
  } else {
    var_decimal = (int)va_arg(*vl, int);
  }
  // преобразует число в строку и записывает наоборот, со знаком!
  s21_itoa(buf, opt, var_decimal);
  // дополняет нулями, если есть точность больше чем число
  add_precision(buf, opt);
  // устанавливаем ширину
  add_width(buf, opt);
  // сохраняем буфер в строку
  save_buf_in_str(str, buf);
}

void save_buf_in_str(char **str, char *buf) {
  long long int len = s21_strlen(buf);
  char *str_begin = *str;
  // переворачиваем buf и записываем в str
  while (len-- > 0) {
    *((*str)++) = buf[len];
  }
  // дописываем конец строки в str
  **str = 0;
}

// устанавливаем точность
void add_precision(char *buf, options_sprintf *opt) {
  long int len = s21_strlen(buf);
  long int def = opt->precision - len;
  if (opt->specifiers != 's')
    while (def-- > 0) {
      buf[len++] = '0';
    }
  // для спецификатора o чтобы дописать 0 если есть флаг #
  if (opt->specifiers == 'o') {
    len = s21_strlen(buf);
    if (buf[len - 1] != '0') {
      buf[len] = '0';
      buf[len + 1] = 0;
    }
  }
}

// устанавливаем ширину
void add_width(char *buf, options_sprintf *opt) {
  long int len = s21_strlen(buf);
  // если у нас стоит флаг '0' - insert_zero, то мы дополняем ширину 0
  if ((opt->insert_zero && !opt->precision) ||
      (opt->insert_zero && s21_strchr("sfFgGeE", opt->specifiers))) {
    long int def = opt->width - len;
    while (def-- > 0) {
      if ((def == 0 && ((opt->show_sign || opt->negative || opt->leave_space) ||
                        (opt->insert_ox_dot && opt->base == 16))) ||
          (def == 1 && (opt->insert_ox_dot && opt->base == 16)))
        continue;
      buf[len] = '0';
      len++;
    }
  }

  len = s21_strlen(buf);

  // вставляем знак
  if (opt->negative) {
    buf[len] = '-';
  } else if (opt->show_sign) {
    buf[len] = opt->negative ? '-' : '+';
  } else if (opt->leave_space) {
    buf[len] = ' ';
  }

  // вставляем 0x для спецификаторов xX

  if (opt->insert_ox_dot && opt->base == 16) {
    len = s21_strlen(buf);
    s21_strcat(buf, opt->specifiers == 'x' ? "x0" : "X0");
  }

  // вставляем пробелы если отсуствует в конце buf    '-' - left_alignment
  if (!opt->left_alignment) {
    len = s21_strlen(buf);
    long int deff = opt->width - len;
    while (deff-- > 0) {
      buf[len++] = ' ';
    }
  }

  // вставляем пробелы и сдвигаем текст при выравнивании слева left_alignment
  if (opt->left_alignment && opt->width > len) {
    len = s21_strlen(buf);
    long int deff_la = opt->width - len;
    while ((len--) + deff_la > 0) {
      buf[len + deff_la] = buf[len];
    }
    len = 0;
    while (len < deff_la) {
      buf[len] = ' ';
      len++;
    }
  }
}

// преобразует число в строку и записывает наоборот, без знака!
void s21_itoa(char *buf, options_sprintf *opt, long int var) {
  // определяем отрицательное число, не нужно для флагов с плавающей точкой,
  // там по другому!
  if (!s21_strchr("fFgGeE", opt->specifiers)) opt->negative = var < 0 ? 1 : 0;
  // это нужно для unsigned
  if (s21_strchr("oxXu", opt->specifiers)) {
    opt->negative = 0;
  }

  int i = 0;
  var = var < 0 ? -var : var;
  if (var == 0) {
    buf[i++] = '0';
  } else {
    while (var > 0) {
      buf[i] = "0123456789abcdef"[var % opt->base];
      // если X большое, то и буквы в 16ти ричной системе большие
      if (opt->specifiers == 'X' && ((var % opt->base) >= 10) &&
          ((var % opt->base) <= 15)) {
        buf[i] -= 32;
      }
      var /= opt->base;
      i++;
    }
  }
  buf[i] = 0;
}

void check_conflict_flags(options_sprintf *opt) {
  // Отрезаем конфлкитующие флаги
  // '+' и ' ' => '+'
  if (opt->show_sign && opt->leave_space) opt->leave_space = 0;
  // '-' и '0' => '-'
  if (opt->left_alignment && opt->insert_zero) opt->insert_zero = 0;

  // костыль для заглавных букв
  if (s21_strchr("XEFG", opt->specifiers)) {
    opt->uppercase = 1;
  }

  // устанавливаем систему счисления
  if (s21_strchr("dieEfFgG", opt->specifiers)) opt->base = 10;
  if (s21_strchr("xXp", opt->specifiers)) opt->base = 16;
  if (opt->specifiers == 'o') opt->base = 8;

  // настройка под разные спецификаторы, убираем флаги которые не используются
  if (s21_strchr("oxXu", opt->specifiers)) {
    opt->show_sign = 0;
    opt->leave_space = 0;
  }
  if (opt->specifiers == 'c') {
    opt->show_sign = 0;
    opt->leave_space = 0;
    opt->insert_ox_dot = 0;
    opt->precision = 0;
  }
  if (opt->specifiers == 's') {
    opt->show_sign = 0;
    opt->leave_space = 0;
    opt->insert_ox_dot = 0;
  }
  if (opt->specifiers == 'p') {
    opt->insert_ox_dot = 1;
    opt->show_sign = 0;
    opt->leave_space = 0;
    opt->length = 'l';
    opt->specifiers = 'x';
  }
  if (opt->specifiers == '%') {
    opt->show_sign = 0;
    opt->leave_space = 0;
    opt->insert_ox_dot = 0;
    opt->precision = 0;
  }
}

// считываем флаги "-+ #0"
void get_flags(const char **format, options_sprintf *opt) {
  int long_flags = s21_strspn(*format, "-+ #0");
  while (long_flags--) {
    switch (**format) {
      case '-':
        opt->left_alignment = 1;
        break;
      case '+':
        opt->show_sign = 1;
        break;
      case ' ':
        opt->leave_space = 1;
        break;
      case '#':
        opt->insert_ox_dot = 1;
        break;
      case '0':
        opt->insert_zero = 1;
        break;
    }
    (*format)++;
  }
}

// считываем значение ширины
void get_width(const char **format, options_sprintf *opt, va_list *vl) {
  if (**format >= '0' && **format <= '9') {
    int long_width = s21_strspn(*format, "1234567890");
    opt->width = string_to_number(*format, long_width);
    *format += long_width;
    // нужно написать преоброзование строки в число
  } else if (**format == '*') {
    // нужно дописать получение int из аргв
    opt->width = va_arg(*vl, int);
    (*format)++;
  }
}

// считываем значение длины
void get_length(const char **format, options_sprintf *opt) {
  if (s21_strchr("hlL", **format)) {
    opt->length = **format;
    (*format)++;
  }
}

// считываем точность
void get_precision(const char **format, options_sprintf *opt, va_list *vl) {
  if (**format == '.' && *(*format + 1) != '*') {
    (*format)++;
    int long_precision = s21_strspn(*format, "1234567890-");
    // для отрицательной точности
    if (**format == '-') {
      (*format)++;
      long_precision--;
      opt->negative_presicion = 1;
    }

    // записываем точность
    opt->precision = string_to_number(*format, long_precision);
    // костыль для отрицательной точности
    if (opt->negative_presicion) opt->precision = -opt->precision;
    // передвигаем указатель формата после считывания
    *format += long_precision;

    // костыль для точности в спецификаторе s, указывает что точность была
    // введена, в случае если кто-то поставит точность 0
    opt->is_precision = 1;

  } else if (**format == '.' && *(*format + 1) == '*') {
    // если указана .* то считываем точность с помощью va_arg
    opt->precision = va_arg(*vl, int);
    (*format) += 2;
    opt->is_precision = 1;
  }
}

// считываем спецификатор
void get_specifiers(const char **format, options_sprintf *opt) {
  if (s21_strchr("cdieEfFgGosuxXpn%", **format)) {
    opt->specifiers = **format;
    (*format)++;
  }
}

// преобразует строку в число из заданного количество символов
s21_size_t string_to_number(const char *start, int number_of_symbols) {
  s21_size_t res = 0;
  start += number_of_symbols - 1;
  int i = 0;
  while (number_of_symbols-- > 0) {
    res += (s21_size_t)pow(10, i) * (int)(*start - 48);
    i++;
    start--;
  }
  return res;
}
