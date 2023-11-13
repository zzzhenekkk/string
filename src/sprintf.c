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
      parsing(&format, &opt, &str, &vl);
    }
  }
  va_end(vl);
  return (str - str_begin);
}

// str куда записываем
// format форматная строка со спецификаторами
// перебираем все после процента
int parsing(const char **format, options_sprintf *opt, char **str,
            va_list *vl) {
  // получаем всю информацию из под %
  get_opt(format, opt, str, vl);
  push_opt(format, opt, str, vl);
  // не забудем вернуть формат увелеченный на количество
  return 0;
}

int get_opt(const char **format, options_sprintf *opt, char **str,
            va_list *vl) {
  get_flags(format, opt);
  get_width(format, opt, vl);
  get_precision(format, opt, vl);
  get_length(format, opt);
  get_specifiers(format, opt, vl);
  check_conflict_flags(opt);
}

int push_opt(const char **format, options_sprintf *opt, char **str,
             va_list *vl) {
  get_specifiers_from_valist(format, opt, str, vl);

  return 0;
}

int get_specifiers_from_valist(const char **format, options_sprintf *opt,
                               char **str, va_list *vl) {
  char buf[8100] = {0};

  if (opt->specifiers == 'd' || opt->specifiers == 'i') {
    work_decimal(format, opt, str, vl, buf);
  } else if (opt->specifiers == 'u' || opt->specifiers == 'o' ||
             opt->specifiers == 'x' || opt->specifiers == 'X') {
    work_unsigned(format, opt, str, vl, buf);
  }

  return 0;
}

int work_unsigned(const char **format, options_sprintf *opt, char **str,
                  va_list *vl, char *buf) {
  unsigned long int var_decimal;
  if (opt->length == 'h') {
    var_decimal = (unsigned short)va_arg(*vl, unsigned short);
  } else if (opt->length == 'l') {  // "%ld"
    var_decimal = (unsigned long int)va_arg(*vl, unsigned long int);
  } else {
    var_decimal = (unsigned int)va_arg(*vl, unsigned int);
  }
  // обнуляются

  // преобразует число в строку и записывает наоборот
  s21_itoa(buf, opt, var_decimal);

  // дополняет нулями, если есть точность больше чем число
  add_precision(buf, opt, var_decimal, 10);

  // устанавливаем ширину
  add_width(buf, opt, var_decimal, 10);

  save_buf_in_str(str, buf, opt, var_decimal, 10);
}

// работаем с d или i
int work_decimal(const char **format, options_sprintf *opt, char **str,
                 va_list *vl, char *buf) {
  long int var_decimal;
  if (opt->length == 'h') {
    var_decimal = (short)va_arg(*vl, short);
  } else if (opt->length == 'l') {  // "%ld"
    var_decimal = (long int)va_arg(*vl, long int);
  } else {
    var_decimal = (int)va_arg(*vl, int);
  }
  // преобразует число в строку и записывает наоборот, со знаком!
  s21_itoa(buf, opt, var_decimal);
  // дополняет нулями, если есть точность больше чем число
  add_precision(buf, opt, var_decimal, 10);
  // устанавливаем ширину
  add_width(buf, opt, var_decimal, 10);
  // впечатываем в буфер
  save_buf_in_str(str, buf, opt, var_decimal, 10);
  // strcat(*str, buf);
  // *str += strlen(buf);
  return 0;
}

void save_buf_in_str(char **str, char *buf, options_sprintf *opt, long int var,
                     int base) {
  // *str += s21_strlen(*str);
  long long int len = s21_strlen(buf);
  while (len-- > 0) {
    *((*str)++) = buf[len];
  }
}

// устанавливаем точность
void add_precision(char *buf, options_sprintf *opt, long int var, int base) {
  long int len = s21_strlen(buf);
  long int def = opt->precision - len;

  while (def-- > 0) {
    buf[len++] = '0';
  }
}

// устанавливаем ширину
void add_width(char *buf, options_sprintf *opt, long int var, int base) {
  // флаг костыль нужен для печатания знака в ширину если есть negative space or
  // show_sign
  int flag_zero_znak = 0;

  long int len = s21_strlen(buf);
  // если у нас стоит флаг '0' - insert_zero, то мы дополняем ширину 0
  if (opt->insert_zero && !opt->precision) {
    long int def = opt->width - len;
    while (def-- > 0) {
      if (def == 0 && (opt->show_sign || opt->negative || opt->leave_space))
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

  len = s21_strlen(buf);

  // вставляем пробелы если отсуствует в конце buf    '-' - left_alignment
  if (!opt->left_alignment) {
    long int deff = opt->width - len;
    while (deff-- > 0) {
      buf[len++] = ' ';
    }
  }

  len = s21_strlen(buf);
  // вставляем пробелы
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
  int i = 0;
  opt->negative = var < 0 ? 1 : 0;
  // это нужно для unsigned
  if (s21_strchr("oxXu", opt->specifiers)) {
    opt->negative = 0;
  }

  var = var < 0 ? -var : var;
  if (var == 0) {
    buf[i++] = '0';
  } else {
    while (var > 0) {
      buf[i] = "0123456789abcdef"[var % opt->base];
      // если X большое, то и буквы в 16ти ричной системе большие
      if (opt->specifiers == 'X' && buf[i] >= 10 && buf[i] <= 15) {
        buf[i] -= 32;
      }
      var /= opt->base;
      i++;
    }
  }
  buf[i] = 0;
}

int check_conflict_flags(options_sprintf *opt) {
  // '+' ' ' => '+'
  if (opt->show_sign && opt->leave_space) opt->leave_space = 0;
  // '-' '0' => '-'
  if (opt->left_alignment && opt->insert_zero) opt->insert_zero = 0;

  // для вот этих специкаторов oxXu не нужны флаги +' '
  if (s21_strchr("oxXu", opt->specifiers)) {
    opt->show_sign = 0;
    opt->leave_space = 0;
  }
  if (opt->specifiers == 'd' || opt->specifiers == 'i') opt->base = 10;
  if (opt->specifiers == 'x' || opt->specifiers == 'X') opt->base = 16;
  if (opt->specifiers == 'o') opt->base = 8;
}

// считываем флаги "-+ #0"
int get_flags(const char **format, options_sprintf *opt) {
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
  return 0;
}

// считываем значение ширины
int get_width(const char **format, options_sprintf *opt, va_list *vl) {
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
  return 0;
}

// считываем значение длины
int get_length(const char **format, options_sprintf *opt) {
  if (s21_strchr("hlL", **format)) {
    opt->length = **format;
    (*format)++;
  } else {
    // здесь, мы пишем, не подходящий, или еще какая-то ошибка
  }
  return 0;
}

// считываем точность
int get_precision(const char **format, options_sprintf *opt, va_list *vl) {
  if (**format == '.' && *(*format + 1) != '*') {
    (*format)++;
    int long_precision = s21_strspn(*format, "1234567890");
    // printf("long precision %d\n", long_precision);
    opt->precision = string_to_number(*format, long_precision);
    *format += long_precision;
    // нужно написать преоброзование строки в число
  } else if (**format == '.' && *(*format + 1) == '*') {
    // нужно дописать получение int из аргв
    opt->precision = va_arg(*vl, int);
    (*format) += 2;
  }
  // printf("!!!!!    opt->precision %llu   !!! \n", opt->precision);
  return 0;
}

// считываем спецификатор
int get_specifiers(const char **format, options_sprintf *opt, va_list *vl) {
  if (s21_strchr("cdieEfgGosuxXpn%", **format)) {
    opt->specifiers = **format;
    (*format)++;
  } else {
    // здесь, мы пишем, если спецификатор не подходящий, или еще какая-то ошибка
  }
  return 0;
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
