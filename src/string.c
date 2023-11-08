#include "string.h"
/**
 * @brief  Ищет вхождение в массив символа, код которого задан аргументом c,
сравнивая каждый байт массива.
 *
 * @param arr Указатель на массив, в котором будет осуществляться поиск.
 * @param c Код искомого символа.
 * @param n Размер сравниваемой части массива в байтах.
 * @return Указатель на найденный символ, если, на указанном участке массива,
найден требуемый символ. NULL – если требуемый символ не найден.
 */
void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *s1 = (char *)str;
  char *buf = s21_NULL;
  for (s21_size_t i = 0; i < n; i++) {
    if (s1[i] == c) {
      buf = s1 + i;
      break;
    }
  }
  return buf;
}

/**
 * @brief Побайтно сравнивает два массива, на которые указывают аргументы arr1 и
 * arr2.
 *
 * @param arr1 Указатель на сравниваемый массив.
 * @param arr2 Указатель на сравниваемый массив.
 * @param n Размер сравниваемой части массива в байтах.
 * @return Результат сравнивания.
 */
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *s1;
  const unsigned char *s2;
  s1 = str1;
  s2 = str2;
  char count = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (s1[i] != s2[i]) {
      count = s1[i] - s2[i];
      break;
    }
  }
  return count;
}

/**
 * @brief Копирует n байт в массив.
 *
 * @param destination Указатель на массив в которой будут скопированы данные.
 * @param source Указатель на массив источник копируемых данных.
 * @param n Количество байт для копирования.
 * @return Возвращает указатель на массив, в который скопированы данные.
 */
void *s21_memcpy(void *destination, const void *source, s21_size_t n) {
  char *dst = destination;
  const char *src = source;
  while (n--) *dst++ = *src++;
  return destination;
}

/**
 * @brief Копирует n байт из массива в массив.
 *
 * @param dest Указатель на массив в который будут скопированы данные.
 * @param src Указатель на массив источник копируемых данных.
 * @param n Количество байт для копирования.
 * @return Функция возвращает указатель на массив, в который скопированы данные.
 */
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *dst = dest;
  const char *o_src = src;
  if (dst > o_src && dst < o_src + n) {
    o_src += n;
    dst += n;
    while (n--) *--dst = *--o_src;
  } else {
    while (n--) *dst++ = *o_src++;
  }
  return dest;
}

/**
 * @brief Заполняет первые n байт в области памяти.
 *
 * @param str Указатель на заполняемый массив.
 * @param c Код символа для заполнения.
 * @param n Размер заполняемой части массива в байтах.
 * @return Функция возвращает указатель на заполняемый массив.
 */
void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *a = str;
  while (n--) *a++ = c;
  return str;
}

/**
 * @brief Объединение строк
 *
 * @param dest Указатель на строку назначения, к которой добавятся символы
 * строки source
 * @param src Си-строка, которая добавляется в конец строки destination.
 * @return char* Возвращает указатель на массив, в который добавлена строка .
 */
char *s21_strcat(char *dest, const char *src) {
  char *a = dest;
  while (*a) a++;
  while ((*a++ = *src++)) continue;
  return dest;
}

/**
 * @brief Функция добавляет в строку, на которую указывает аргумент dest,
 * строку, на которую указывает аргумент append, пока не встретится символ конца
 * строки или пока не будет добавлено n символов.
 *
 * @param dest Указатель на массив в который будет добавлена строка.
 * @param src Указатель на массив из которого будет скопирована строка.
 * @param n Максимальная длина добавляемой строки.
 * @return char* Возвращает указатель на массив, в который добавлена строка
 */
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *a = dest + s21_strlen(dest);

  while (*src && n--) *a++ = *src++;
  *a = '\0';
  return dest;
}

/**
 * @brief Функция strchr ищет последнее вхождения символа, код которого указан в
 * аргументе ch, в строке, на которую указывает аргумент str.
 *
 * @param str Указатель на строку, в которой будет осуществляться поиск.
 * @param c Код искомого символа.
 * @return char* Указатель на искомый символ, если он найден в строке str, иначе
 * NULL.
 */
char *s21_strchr(const char *str, int c) {
  while (*str != c && *str) str++;
  return *str == c ? (char *)str : s21_NULL;
}

/**
 * @brief Функция побайтно сравнивает коды символов двух строк, на которые
 * указывают аргументы функции.
 *
 * @param str1  Указатель на сравниваемую строку.
 * @param str2  Указатель на сравниваемую строку.
 * @return int 0 – если сравниваемее строки идентичны;
 * Положительное число – если строки отличаются;Отрицательное число – если
 * строки отличаются
 */
int s21_strcmp(const char *str1, const char *str2) {
  while (*str1 && (*str1 == *str2)) {
    str1++;
    str2++;
  }
  return *str1 - *str2;
}

/**
 * @brief Функция побайтно сравнивает коды символов двух строк, на которые
 * указывают аргументы функции.
 *
 * @param str1 Указатель на сравниваемую строку.
 * @param str2 Указатель на сравниваемую строку.
 * @param n Количество символов для сравнения.
 * @return int 0 – если сравниваемее строки идентичны;
 * Положительное число – если строки отличаются;Отрицательное число – если
 * строки отличаются
 */
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  s21_size_t i = 0;
  while (*str1 && (*str1 == *str2) && i < n - 1) {
    str1++;
    str2++;
    i++;
  }
  return *str1 - *str2;
}

/**
 * @brief Копирует данные из строки, на которую указывает аргумент src, в dest
 *
 * @param dest Указатель на строку, в которую будут скопированы данные.
 * @param src Указатель на строку источник копируемых данных.
 * @return char* Возвращает указатель на строку, в которую скопированы данные.
 */
char *s21_strcpy(char *dest, const char *src) {
  char *res = &dest[0];
  for (int i = 0; (dest[i] = src[i]); i++) {
  }
  return res;
}

/**
 * @brief Копирует  данные из строки, на которую указывает аргумент src, в dest
 *
 * @param dest Указатель на строку в которую будут скопированы данные.
 * @param src Указатель на строку источник копируемых данных.
 * @param n Ограничение длинны копирования
 * @return char* Возвращает указатель на строку, в которую скопированы данные.
 */
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  while (i < n && src[i]) {
    dest[i] = src[i];
    i++;
  }
  if (i > s21_strlen(src)) {
    dest[i++] = 0;
  }
  return dest;
}

/**
 * @brief Вычисляет длину начального сегмента str1, который полностью состоит из
 * символов, не входящих в str2.
 *
 * @param str1 Указатель на строку, в которой ведется поиск.
 * @param str2 Указатель на строку с набором символов, которые должны входить в
 * участок строки str1.
 * @return Функция возвращает длину начального участка строки, не содержащая
 * символов указанных в аргументе str2.
 */
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t len = 0;
  while (*str1) {
    if (s21_strchr(str2, *str1)) {
      break;
    } else {
      str1++, len++;
    }
  }
  return len;
}

/**
 * @brief Вычисляет количество символов в строке.
 *
 * @param str Указатель на строку.
 * @return Функция возвращает количество символов в строке до первого вхождения
 * символа конца строки.
 */
s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  while (str[len]) len++;
  return len;
}

/**
 * @brief Ищет первое вхождение в строку, одного из символов, входящих в строку
 * 2
 *
 * @param str1 Указатель на строку, в которой ведется поиск.
 * @param str2 Указатель на строку с набором искомых символов.
 * @return char* Указатель на первый найденный в строке str1 символ из множества
 * символов строки str2.
 */
char *s21_strpbrk(const char *str1, const char *str2) {
  char *string1 = (char *)str1;
  char *string2 = (char *)str2;
  int flag = 1;
  char *res = s21_NULL;
  for (int i = 0; string1[i] != '\0' && flag == 1; i++) {
    char symbol = string1[i];
    if (s21_strchr(string2, symbol) != s21_NULL) {
      res = &string1[i];
      flag = 0;
    }
  }
  return res;
}

/**
 * @brief Ищет последнее вхождения символа, код которого указан в аргументе c, в
 * строке, на которую указывает аргумент str.
 *
 * @param str Указатель на строку, в которой будет осуществляться поиск.
 * @param c Код искомого символа.
 * @return char* Указатель на искомый символ, если он найден в строке str, иначе
 * NULL.
 */
char *s21_strrchr(const char *str, int c) {
  char *result = s21_NULL;
  do {
    if (*str == c) result = (char *)str;
  } while (*str++);

  return result;
}

/**
 * @brief Определяет наибольшую длину начального участка строки содержащего
 * только символы строки, на которую указывает аргумент
 *
 * @param str1 Указатель на строку, в которой ведется поиск.
 * @param str2 Указатель на строку с набором символов, которые должны входить в
 * участок строки str1.
 * @return s21_size_t Длина начального участка строки, содержащая только
 * символы, указанные в аргументе str2.
 */
s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t len = 0;
  while (*str1 && s21_strchr(str2, *str1++)) {
    len++;
  }
  return len;
}

/**
 * @brief Ищет первое вхождение строки 1 в строку 2. Если строка 2 имеет нулевую
 * длину, то функция вернет указатель на начало строки 2.
 *
 * @param haystack Указатель на строку, в которой ведется поиск.
 * @param needle Указатель на искомую строку.
 * @return char* NULL – если строка heystack не входит в строку needle.
 * Указатель на первое вхождение строки heystack в строку needle.
 */
char *s21_strstr(const char *haystack, const char *needle) {
  int len_needle = s21_strlen(needle) - 1;
  char *str = s21_NULL;
  char *ptr = (char *)haystack;
  if ((len_needle + 1) != 0)
    for (int i = 0; ptr[i] != '\0' && str == s21_NULL; i++) {
      int count = 0, flag = 1;
      while ((count <= len_needle) && flag) {
        flag = ptr[i + count] == needle[count];
        count++;
      }
      if (flag && (count > len_needle)) {
        str = &(ptr[i]);
      }
    }
  return str;
}

/**
 * @brief Разбивает строку str на ряд токенов, разделенных delim.
 *
 * @param str Указатель на разбиваемую строку.
 * @param delim Указатель на строку, содержащую набор символов разделителей.
 * @return char* NULL – если строку str невозможно разделить на части. Указатель
 * на первый символ выделенной части строки.
 */
char *s21_strtok(char *str, const char *delim) {
  static char *p = s21_NULL;
  // первый вход, мы передаем строку
  if (str) p = str;

  if (p != 0) {
    str = p + s21_strspn(p, delim);
    p = str + s21_strcspn(str, delim);

    if (p == str) {
      str = 0;
    }

    if (*p != 0) {
      *p = 0;
      p = p + 1;
    } else {
      p = 0;
    }
  } else {
    str = 0;
  }
  return str;
}

/**
 * @brief Выполняет поиск во внутреннем массиве номера ошибки errnum и
 * возвращает указатель на строку с сообщением об ошибке. Нужно объявить
 * макросы, содержащие массивы сообщений об ошибке для операционных систем mac и
 * linux. Описания ошибок есть в оригинальной библиотеке. Проверка текущей ОС
 * осуществляется с помощью директив.
 *
 * @param int Номер ошибки.
 * @return char* – Трансляция ошибки строкой.
 */
char *s21_strerror(int errnum) {
  static char *array[] = error;
  if (errnum >= 0 && errnum <= N) {
    return array[errnum];
  } else {
    static char str_code[256] = "";
    s21_sprintf(str_code, "%s%d", UERROR, errnum);
    return str_code;
  }
}
