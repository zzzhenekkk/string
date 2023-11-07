#include "s21_string.h"

/**
 * @brief Записывает данные в массив.
 *
 * @param str Указатель на изначальный массив.
 * @param format Формат для обработки.
 * @return Функция возвращает количество успешно записанных символов.
 */
int s21_sprintf(char *str, const char *format, ...) {
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
      struct format_sprintf _format_sprintf;
      init_flags(&_format_sprintf);

      if (parsing(&format, &_format_sprintf) == 1) {
        record_arg(&format, &str, &_format_sprintf, vl);
      }
    }
  }
  va_end(vl);
  return s21_strlen(str);
}

/**
 * @brief Парсит данные и записывает в поля структуры.
 *
 * @param format Исходная строка.
 * @param _format_sprintff Указатель на структуру.
 * @param flag_pars Указатель на возвращаемое значение.
 * @returns Возвращает значение.
 */
int parsing(const char **format, struct format_sprintf *_format_sprintff) {
  int flag_pars = 0;
  while (**format) {
    if (**format == '-' || **format == '+' ||
        **format == ' ') {  // Ckeck for flags
      if (**format == '-') {
        _format_sprintff->flag_minus = 1;
      } else if (**format == '+') {
        _format_sprintff->flag_plus = 1;
      } else if (**format == ' ') {
        _format_sprintff->flag_space = 1;
      }
      (*format)++;

    } else if (is_digit(**format) == ON) {  // Check for Width
      while (is_digit(**format)) {
        _format_sprintff->width = **format - '0' + _format_sprintff->width * 10;
        (*format)++;
      }

    } else if (**format == '.') {  // Check for precision
      _format_sprintff->is_pricision = 1;
      (*format)++;
      while (is_digit(**format)) {
        _format_sprintff->precision =
            **format - '0' + _format_sprintff->precision * 10;
        (*format)++;
      }

    } else if (**format == 'h' || **format == 'l') {  // Check for length
      if (**format == 'h') {
        _format_sprintff->length_h = 1;
      } else if (**format == 'l') {
        _format_sprintff->length_l = 1;
      }
      (*format)++;

    } else if (is_specifier(**format) == ON) {  // Check for specifier
      flag_pars = 1;
      break;

    } else {  // Returns error
      flag_pars = 0;
      break;
    }
  }
  return flag_pars;
}

/**
 * @brief Обнуляет поля структуры.
 *
 * @param formatS Указатель на структуру.
 */
void init_flags(struct format_sprintf *formatS) {
  formatS->flag_minus = 0;
  formatS->flag_plus = 0;
  formatS->flag_space = 0;
  formatS->length_h = 0;
  formatS->length_l = 0;
  formatS->precision = 0;
  formatS->width = 0;
  formatS->is_pricision = 0;
}
