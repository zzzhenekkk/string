#include "string.h"

int s21_sprintf(char *str, const char *format, ...) {
  char * str_begin = str; // понадобится для вычисления длины на return
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
      parsing(&format, &opt, &str);
    }
  }
  va_end(vl);
  return (str-str_begin);
}

// str куда записываем
// format форматная строка со спецификаторами
// перебираем все после процента
int parsing(const char **format, options_sprintf * opt, char ** str) {
  get_flags(format, opt);
  (void)opt;
  (void)str;
  

  // не забудем вернуть формат увелеченный на количество 
  return 0;
}

//считываем флаги "-+ #0"
int get_flags(const char **format, options_sprintf * opt) {

  int long_flags = s21_strspn( *format, "-+ #0");
  while(long_flags--) {
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
