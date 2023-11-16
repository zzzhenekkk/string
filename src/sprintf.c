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
  return (str - str_begin);
}

// str куда записываем
// format форматная строка со спецификаторами
// перебираем все после процента
void parsing(const char **format, options_sprintf *opt, char **str, va_list *vl,
            char *str_begin) {
  // получаем всю информацию из под %
  get_opt(format, opt, vl);
  push_opt(opt, str, vl, str_begin);
  // не забудем вернуть формат увелеченный на количество
}

void get_opt(const char **format, options_sprintf *opt, va_list *vl) {
  get_flags(format, opt);
  get_width(format, opt, vl);
  get_precision(format, opt, vl);
  get_length(format, opt);
  get_specifiers(format, opt);
  check_conflict_flags(opt);
}

void push_opt(options_sprintf *opt, char **str, va_list *vl,
             char *str_begin) {
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

void work_g(options_sprintf *opt, char **str, va_list *vl,
            char *buf) {
  long double var_double = 0;
  if (opt->length == 'L') {
    var_double = (long double)va_arg(*vl, long double);
  } else {
    var_double = (double)va_arg(*vl, double);
  }

  if (!isnan(var_double) && !isinf(var_double)) {
    //////////////////////////////////////////////////
    // отрицательное ли число
    opt->negative = var_double < 0 ? 1 : 0;
    var_double = var_double < 0 ? -var_double : var_double;

    long double var_double_2 = var_double;
    // приводит число с плавающей точкой к виду 1 <= f < 10 и записывает степень
    // в opt->exponent
    normilize(&var_double_2, opt);
    /////////////////////////////////////////////////
    // char buf2[5000] = {0};
    // opt->exponent = 0;
    // options_sprintf opt2 = *opt;
    // itoa_and_precision_for_e(buf, &opt2, var_double);
    // itoa_and_precision_for_f(buf2, opt, var_double);

    // reset_opt(opt);

    // if (s21_strlen(buf) > s21_strlen(buf2)) flag = 2;

    if (opt->exponent < -4 || opt->exponent > 5) {
      opt->exponent = 0;
      itoa_and_precision_for_e(buf, opt, var_double);
    } else {
      opt->exponent = 0;
      itoa_and_precision_for_f(buf, opt, var_double);
    }
    add_width(buf, opt);
    save_buf_in_str(str, buf);

    // проверка на inf - превышает максимально допустимое значение
    // и non - недопустимое число
  } else if (isnan(var_double)) {
    s21_strcat(buf, opt->specifiers == 'G' ? "NAN" : "nan");
    save_buf_in_str(str, buf);
  } else if (isinf(var_double)) {
    s21_strcat(buf, opt->specifiers == 'G' ? "FNI" : "fni");
    s21_strcat(buf, var_double > 0 ? "+" : "-");
    save_buf_in_str(str, buf);
  }
  // add_width(flag == 2 ? buf2 : buf, flag == 2 ? &opt2 : opt);
  // save_buf_in_str(str, flag == 2 ? buf2 : buf, opt);
}
// void reset_opt(options_sprintf *opt) {
//   opt->negative = 0;  // отрицительное ли число
//   opt->exponent = 0;  // показатель степени
//                       // при спецификаторе e после E +1.23E+03
// }

void work_e(options_sprintf *opt, char **str, va_list *vl,
            char *buf) {
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

void work_double(options_sprintf *opt, char **str,
                 va_list *vl, char *buf) {
  long double var_double = 0;
  if (opt->length == 'L') {
    var_double = (long double)va_arg(*vl, long double);
  } else {
    var_double = (double)va_arg(*vl, double);
  }

  if (!isnan(var_double) && !isinf(var_double)) {
    itoa_and_precision_for_f(buf, opt, var_double);
    add_width(buf, opt);
    save_buf_in_str(str, buf);

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
  // отрицательное ли число
  opt->negative = var_double < 0 ? 1 : 0;
  var_double = var_double < 0 ? -var_double : var_double;

  //////////////////////////////////////////////////
  // приводит число с плавающей точкой к виду 1 <= f < 10 и записывает степень
  // в opt->exponent
  normilize(&var_double, opt);
  /////////////////////////////////////////////////

  // для точности -1
  if (opt->precision == -1) var_double = roundl(var_double);
  // если не введена точность, то по умолчанию 6
  if (!opt->is_precision) opt->precision = 6;
  if (opt->specifiers == 'g' || opt->specifiers == 'G') {
    opt->precision--;
  }
  // разделяем число на целую и дробную часть, left - целая, right - дробная
  long double left = 0;
  long double right = modfl(var_double, &left);

  long long lleft = left;
  char left_str[50] = {'\0'};
  char right_str[50] = {'\0'};

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
  ////////////////////////////////////////////////////
  // переводим opt->exponent в буфер
  s21_itoa(buf, opt, opt->exponent);
  // дописываем ноль, если e от 0 до 9
  if (s21_strlen(buf) == 1) {
    buf[1] = '0';
  }
  s21_strcat(buf, opt->exponent >= 0 ? "+" : "-");
  s21_strcat(buf, opt->uppercase ? "E" : "e");
  ////////////////////////////////////////////////////

  // переводим все в буфер, склеиваем строку
  if (s21_strlen(right_str)) {
    s21_strcat(buf, right_str);
    s21_strcat(buf, ".");
  }
  s21_strcat(buf, left_str);
}

void itoa_and_precision_for_f(char *buf, options_sprintf *opt,
                              long double var_double) {
  // для точности -1
  if (opt->precision == -1) var_double = roundl(var_double);
  // если не введена точность, то по умолчанию 6
  if (!opt->is_precision) opt->precision = 6;

  // отрицательное ли число
  if (!s21_strchr("gG", opt->specifiers))
    opt->negative = var_double < 0 ? 1 : 0;
  var_double = var_double < 0 ? -var_double : var_double;

  // разделяем число на целую и дробную часть, left - целая, right - дробная
  long double left = 0;
  long double right = modfl(var_double, &left);

  long long lleft = left;
  char left_str[500] = {'\0'};
  char right_str[500] = {'\0'};
  long double rrright = right;
  long double lllleft;

  if (s21_strchr("gG", opt->specifiers)) {
    int count = 0;
    while (modfl(rrright, &lllleft) >= 1e-6) {
      rrright *= 10;
      count++;
    }
    // if (count > 5) count = 5;
    if (opt->precision > count) opt->precision = count;
    // точность 5
  }

  // для установления точности числа, вначале переводим его в целую часть, до
  // указанной точности
  for (int i = 0; i < opt->precision; i++) {
    right *= 10;
    // для спецификаторов gG нужно выводить кратчайшую запись без точности
    // if (s21_strchr("gG", opt->specifiers))
    //   if ((right - roundl(right)) < 0.000001) break;
  }

  long long rright =
      roundl(right);  // roundl - округление до ближайшего целого, чтобы
  if (rright) {
    // записывает в буфер правую часть
    s21_itoa(right_str, opt, rright);
  }

  // дописываем нули при точности большей чем длина после точки, не подходит для
  // gG спецификаторов
  // if (!s21_strchr("gG", opt->specifiers))
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
  // устанавливаем ширину
  add_width(buf, opt);

  save_buf_in_str(str, buf);
}

void work_str(options_sprintf *opt, char **str,
              va_list *vl) {
  char *str_arg = (char *)va_arg(*vl, char *);
  if (str_arg) {
    long long unsigned int len = s21_strlen(str_arg);
    long long unsigned int len_d = len;
    if ((long long unsigned int)opt->width > len) len_d = opt->width;
    if ((long long unsigned int)opt->precision > len) len_d = opt->precision;
    // если мы указываем точность меньше чем длина строки, то строка
    // уменьшается
    if (opt->is_precision && (long long unsigned int)opt->precision < len) len = opt->precision;
    char *str_buf = calloc(sizeof(char), len_d + 30);
    if (str_buf) {
      // Заполянем буфер
      long long unsigned int i = 0;
      while (len > 0) {
        len--;
        str_buf[i] = str_arg[len];
        i++;
      }
      add_precision(str_buf, opt);
      // устанавливаем ширину
      add_width(str_buf, opt);

      save_buf_in_str(str, str_buf);

      free(str_buf);
    }

  } else {
    **str = 0;
  }
  // printf("!!!%s!!!", str_arg);
}

void work_symbol(options_sprintf *opt, char **str,
                 va_list *vl, char *buf) {
  int symbol = (int)va_arg(*vl, int);
  *buf = symbol;
  add_precision(buf, opt);
  // устанавливаем ширину
  add_width(buf, opt);

  save_buf_in_str(str, buf);
}

void work_unsigned(options_sprintf *opt, char **str,
                  va_list *vl, char *buf) {
  unsigned long int var_decimal;
  if (opt->length == 'h') {
    var_decimal = (unsigned int)va_arg(*vl, unsigned int);
  } else if (opt->length == 'l') {  // "%ld"
    var_decimal = (unsigned long int)va_arg(*vl, unsigned long int);
  } else {
    var_decimal = (unsigned int)va_arg(*vl, unsigned int);
  }
  // обнуляются

  // преобразует число в строку и записывает наоборот
  s21_itoa(buf, opt, var_decimal);

  // дополняет нулями, если есть точность больше чем число
  add_precision(buf, opt);

  // устанавливаем ширину
  add_width(buf, opt);

  save_buf_in_str(str, buf);
}

// работаем с d или i
void work_decimal(options_sprintf *opt, char **str,
                 va_list *vl, char *buf) {
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
  // впечатываем в буфер
  save_buf_in_str(str, buf);
  // strcat(*str, buf);
  // *str += strlen(buf);
}

void save_buf_in_str(char **str, char *buf) {
  // *str += s21_strlen(*str);
  long long unsigned int len = s21_strlen(buf);
  while (len-- > 0) {
    *((*str)++) = buf[len];
  }
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
  // флаг костыль нужен для печатания знака в ширину если есть negative space
  // or show_sign
  int flag_zero_znak = 0;

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
  if (!flag_zero_znak) {
    if (opt->negative) {
      buf[len] = '-';
    } else if (opt->show_sign) {
      buf[len] = opt->negative ? '-' : '+';
    } else if (opt->leave_space) {
      buf[len] = ' ';
    }
  }

  // вставляем 0x
  len = s21_strlen(buf);
  if (opt->insert_ox_dot && opt->base == 16) {
    s21_strcat(buf, opt->specifiers == 'x' ? "x0" : "X0");
  }

  len = s21_strlen(buf);

  // вставляем пробелы если отсуствует в конце buf    '-' - left_alignment
  if (!opt->left_alignment) {
    long int deff = opt->width - len;
    while (deff-- > 0) {
      buf[len++] = ' ';
    }
  }

  len = s21_strlen(buf);
  // вставляем пробелы и сдвигаем текст при выравнивании слева left_alignment
  if (opt->left_alignment && opt->width > len) {
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
  // '+' ' ' => '+'
  if (opt->show_sign && opt->leave_space) opt->leave_space = 0;
  // '-' '0' => '-'
  if (opt->left_alignment && opt->insert_zero) opt->insert_zero = 0;

  // для вот этих специкаторов oxXu не нужны флаги +' '
  if (s21_strchr("oxXu", opt->specifiers)) {
    opt->show_sign = 0;
    opt->leave_space = 0;
  }
  // для заглавных букв
  if (s21_strchr("XEFG", opt->specifiers)) {
    opt->uppercase = 1;
  }

  if (opt->specifiers == 'd' || opt->specifiers == 'i' ||
      opt->specifiers == 'e' || opt->specifiers == 'E' ||
      opt->specifiers == 'f' || opt->specifiers == 'F' ||
      opt->specifiers == 'g' || opt->specifiers == 'G')
    opt->base = 10;
  if (opt->specifiers == 'x' || opt->specifiers == 'X') opt->base = 16;
  if (opt->specifiers == 'p') opt->base = 16;
  if (opt->specifiers == 'o') opt->base = 8;

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
  // printf("!!!%s %llu!!!\n", *format, s21_strspn(*format, "-+ #0"));
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
      default:
        printf("Какая-то ошибка )))");
        break;
    }
    (*format)++;
  }
}

// считываем значение ширины
void get_width(const char **format, options_sprintf *opt, va_list *vl) {
  if (**format >= '0' && **format <= '9') {
    int long_width = s21_strspn(*format, "1234567890");
    // printf("long width %d\n", long_width);
    opt->width = string_to_number(*format, long_width);
    *format += long_width;
    // нужно написать преоброзование строки в число
  } else if (**format == '*') {
    // нужно дописать получение int из аргв
    opt->width = va_arg(*vl, int);
    (*format)++;
  }
  // printf("!!!!!    opt->width %llu   !!! \n", opt->width);
}

// считываем значение длины
void get_length(const char **format, options_sprintf *opt) {
  if (s21_strchr("hlL", **format)) {
    opt->length = **format;
    (*format)++;
  } else {
    // здесь, мы пишем, не подходящий, или еще какая-то ошибка
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

    // printf("long precision %d\n", long_precision);
    // записываем точность
    opt->precision = string_to_number(*format, long_precision);
    // костыль для отрицательной точности
    if (opt->negative_presicion) opt->precision = -opt->precision;
    *format += long_precision;

    // костыль для точности в спецификаторе s
    opt->is_precision = 1;

    // нужно написать преоброзование строки в число
  } else if (**format == '.' && *(*format + 1) == '*') {
    // нужно дописать получение int из аргв
    opt->precision = va_arg(*vl, int);
    (*format) += 2;
    opt->is_precision = 1;
  }
  // printf("!!!!!    opt->precision %llu   !!! \n", opt->precision);
}

// считываем спецификатор
void get_specifiers(const char **format, options_sprintf *opt) {
  if (s21_strchr("cdieEfFgGosuxXpn%", **format)) {
    opt->specifiers = **format;
    (*format)++;
  } else {
    // здесь, мы пишем, если спецификатор не подходящий, или еще какая-то
    // ошибка
  }
}

// преобразует строку в число, на заданное количество символов
s21_size_t string_to_number(const char *start, int number_of_symbols) {
  s21_size_t res = 0;
  start += number_of_symbols - 1;
  int i = 0;
  while (number_of_symbols-- > 0) {
    res += (s21_size_t)pow(10, i) * (int)(*start - 48);
    i++;
    start--;
  }
  // printf("res %lu\n", res);
  return res;
}
