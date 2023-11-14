#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

// #define s21_size_t unsigned long long
#define s21_NULL ((void *)0)
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <wctype.h>
// временно
#include <stdio.h>
#include <string.h>

typedef long long unsigned s21_size_t;

#if defined(__APPLE__) && defined(__MACH__)
#define UERROR "Unknown error: "
#define N 106
#define error                                                                  \
  {                                                                            \
    "Undefined error: 0", "Operation not permitted",                           \
        "No such file or directory", "No such process",                        \
        "Interrupted system call", "Input/output error",                       \
        "Device not configured", "Argument list too long",                     \
        "Exec format error", "Bad file descriptor", "No child processes",      \
        "Resource deadlock avoided", "Cannot allocate memory",                 \
        "Permission denied", "Bad address", "Block device required",           \
        "Resource busy", "File exists", "Cross-device link",                   \
        "Operation not supported by device", "Not a directory",                \
        "Is a directory", "Invalid argument", "Too many open files in system", \
        "Too many open files", "Inappropriate ioctl for device",               \
        "Text file busy", "File too large", "No space left on device",         \
        "Illegal seek", "Read-only file system", "Too many links",             \
        "Broken pipe", "Numerical argument out of domain", "Result too large", \
        "Resource temporarily unavailable", "Operation now in progress",       \
        "Operation already in progress", "Socket operation on non-socket",     \
        "Destination address required", "Message too long",                    \
        "Protocol wrong type for socket", "Protocol not available",            \
        "Protocol not supported", "Socket type not supported",                 \
        "Operation not supported", "Protocol family not supported",            \
        "Address family not supported by protocol family",                     \
        "Address already in use", "Can't assign requested address",            \
        "Network is down", "Network is unreachable",                           \
        "Network dropped connection on reset",                                 \
        "Software caused connection abort", "Connection reset by peer",        \
        "No buffer space available", "Socket is already connected",            \
        "Socket is not connected", "Can't send after socket shutdown",         \
        "Too many references: can't splice", "Operation timed out",            \
        "Connection refused", "Too many levels of symbolic links",             \
        "File name too long", "Host is down", "No route to host",              \
        "Directory not empty", "Too many processes", "Too many users",         \
        "Disc quota exceeded", "Stale NFS file handle",                        \
        "Too many levels of remote in path", "RPC struct is bad",              \
        "RPC version wrong", "RPC prog. not avail", "Program version wrong",   \
        "Bad procedure for program", "No locks available",                     \
        "Function not implemented", "Inappropriate file type or format",       \
        "Authentication error", "Need authenticator", "Device power is off",   \
        "Device error", "Value too large to be stored in data type",           \
        "Bad executable (or shared library)", "Bad CPU type in executable",    \
        "Shared library version mismatch", "Malformed Mach-o file",            \
        "Operation canceled", "Identifier removed",                            \
        "No message of desired type", "Illegal byte sequence",                 \
        "Attribute not found", "Bad message", "EMULTIHOP (Reserved)",          \
        "No message available on STREAM", "ENOLINK (Reserved)",                \
        "No STREAM resources", "Not a STREAM", "Protocol error",               \
        "STREAM ioctl timeout", "Operation not supported on socket",           \
        "Policy not found", "State not recoverable", "Previous owner died",    \
        "Interface output queue is full"                                       \
  }
#elif defined(__linux__)
#define UERROR "Unknown error "
#define N 133
#define error                                                                  \
  {                                                                            \
    "Success", "Operation not permitted", "No such file or directory",         \
        "No such process", "Interrupted system call", "Input/output error",    \
        "No such device or address", "Argument list too long",                 \
        "Exec format error", "Bad file descriptor", "No child processes",      \
        "Resource temporarily unavailable", "Cannot allocate memory",          \
        "Permission denied", "Bad address", "Block device required",           \
        "Device or resource busy", "File exists", "Invalid cross-device link", \
        "No such device", "Not a directory", "Is a directory",                 \
        "Invalid argument", "Too many open files in system",                   \
        "Too many open files", "Inappropriate ioctl for device",               \
        "Text file busy", "File too large", "No space left on device",         \
        "Illegal seek", "Read-only file system", "Too many links",             \
        "Broken pipe", "Numerical argument out of domain",                     \
        "Numerical result out of range", "Resource deadlock avoided",          \
        "File name too long", "No locks available",                            \
        "Function not implemented", "Directory not empty",                     \
        "Too many levels of symbolic links", "Unknown error 41",               \
        "No message of desired type", "Identifier removed",                    \
        "Channel number out of range", "Level 2 not synchronized",             \
        "Level 3 halted", "Level 3 reset", "Link number out of range",         \
        "Protocol driver not attached", "No CSI structure available",          \
        "Level 2 halted", "Invalid exchange", "Invalid request descriptor",    \
        "Exchange full", "No anode", "Invalid request code", "Invalid slot",   \
        "Unknown error 58", "Bad font file format", "Device not a stream",     \
        "No data available", "Timer expired", "Out of streams resources",      \
        "Machine is not on the network", "Package not installed",              \
        "Object is remote", "Link has been severed", "Advertise error",        \
        "Srmount error", "Communication error on send", "Protocol error",      \
        "Multihop attempted", "RFS specific error", "Bad message",             \
        "Value too large for defined data type", "Name not unique on network", \
        "File descriptor in bad state", "Remote address changed",              \
        "Can not access a needed shared library",                              \
        "Accessing a corrupted shared library",                                \
        ".lib section in a.out corrupted",                                     \
        "Attempting to link in too many shared libraries",                     \
        "Cannot exec a shared library directly",                               \
        "Invalid or incomplete multibyte or wide character",                   \
        "Interrupted system call should be restarted", "Streams pipe error",   \
        "Too many users", "Socket operation on non-socket",                    \
        "Destination address required", "Message too long",                    \
        "Protocol wrong type for socket", "Protocol not available",            \
        "Protocol not supported", "Socket type not supported",                 \
        "Operation not supported", "Protocol family not supported",            \
        "Address family not supported by protocol", "Address already in use",  \
        "Cannot assign requested address", "Network is down",                  \
        "Network is unreachable", "Network dropped connection on reset",       \
        "Software caused connection abort", "Connection reset by peer",        \
        "No buffer space available",                                           \
        "Transport endpoint is already connected",                             \
        "Transport endpoint is not connected",                                 \
        "Cannot send after transport endpoint shutdown",                       \
        "Too many references: cannot splice", "Connection timed out",          \
        "Connection refused", "Host is down", "No route to host",              \
        "Operation already in progress", "Operation now in progress",          \
        "Stale file handle", "Structure needs cleaning",                       \
        "Not a XENIX named type file", "No XENIX semaphores available",        \
        "Is a named type file", "Remote I/O error", "Disk quota exceeded",     \
        "No medium found", "Wrong medium type", "Operation canceled",          \
        "Required key not available", "Key has expired",                       \
        "Key has been revoked", "Key was rejected by service", "Owner died",   \
        "State not recoverable", "Operation not possible due to RF-kill",      \
        "Memory page has hardware error"                                       \
  }
#endif

// s21_string.c

// 01 Поиск первого вхождения символа в массиве, возвращает указатель
void *s21_memchr(const void *str, int c, s21_size_t n);

// 02 Сравнение массивов, возвращает число
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);

// 03 Копирует n байт массива в другой массив, возвращает указатель
void *s21_memcpy(void *dest, const void *src, s21_size_t n);

// 04 Копирует n байт массива в другой массив, возвращает указатель
void *s21_memmove(void *dest, const void *src, s21_size_t n);

// 05 Заполняет n байт символом, возвращает указатель
void *s21_memset(void *str, int c, s21_size_t n);

// 06 Добавляет строку в строку, возвращает указатель
char *s21_strcat(char *dest, const char *src);

// 07 Добавляет n символов строки в строку, возвращает указатель
char *s21_strncat(char *dest, const char *src, s21_size_t n);

// 08 Ищет первое вхождения символа в строке, возвращает указатель
char *s21_strchr(const char *str, int c);

// 09 Сравнивает строки, возвращает число
int s21_strcmp(const char *str1, const char *str2);

// 10 Сравнивает n символов строк, возвращает число
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);

// 11 Копирует строку в строку, возвращает указатель
char *s21_strcpy(char *dest, const char *src);

// 12 Копирует n символов строки в строку, возвращает указатель
char *s21_strncpy(char *dest, const char *src, s21_size_t n);

// 13 Определяет длину участка строки без искомых символов, возвращает длину
s21_size_t s21_strcspn(const char *str1, const char *str2);

// 14 Транслирует код ошибки
char *s21_strerror(int errnum);

// 15 Вычисляет количество символов в строке, возвращает количество
s21_size_t s21_strlen(const char *str);

// 16 Ищет в строке вхождение одного из символов, возвращает указатель или 0
char *s21_strpbrk(const char *str1, const char *str2);

// 17 Ищет последнее вхождение символа в строке, возвращает указатель или 0
char *s21_strrchr(const char *str, int c);

// 18 Определяет наибольшую длину строки с искомыми символами, возвращает длину
s21_size_t s21_strspn(const char *str1, const char *str2);

// 19 Ищет первое вхождение строки в строку, возвращает указатель или 0
char *s21_strstr(const char *haystack, const char *needle);

// 20 Выделяет часть строки, возвращает указатель или 0
char *s21_strtok(char *str, const char *delim);

// s21_sprintf.c

typedef struct options_sprintf {
  // flags
  int left_alignment;  //  '-' выравнивание по левому краю
  int show_sign;       //  '+' показывать знак числа
  int leave_space;  //     ' ' если нет знака оставлять пробел
  int insert_zero;    //     '0' заполянет число нулями
  int insert_ox_dot;  //   '#' При использовании со спецификаторами o, x или X
                      //  перед числом вставляется 0, 0x или 0X соответственно
  // При использовании с e, E и f "заставляет" записанный вывод содержать
  // десятичную точку, даже если за ней не последует никаких цифр При
  // использовании с g или G результат такой же, как и с e или E, но конечные
  // нули не удаляются

  // widtd, len
  int width;  // ширина - минимальное количество печатаемых символов,
              // если число меньше, то дополняется пробелами
  int precision;  // точность - минимальное количество записываемых цифр, если
                  // значение короче, то записывается нулями
  char length;  // h - short idouxX, l - long idouxX, L - double eEfgG

  // specifiers спецификатор
  char specifiers;

  // additionally, для удобства кодинга
  int negative;  // отрицительное ли число
  int base;      // система счисления
  int flag_for_s_precision;

} options_sprintf;

// Парсит данные и записывает в поля структуры.
int parsing(const char **format, options_sprintf *opt, char **str, va_list *vl, char *str_begin);
int get_opt(const char **format, options_sprintf *opt, char **str, va_list *vl);
int get_flags(const char **format, options_sprintf *opt);
int get_width(const char **format, options_sprintf *opt, va_list *vl);
int get_precision(const char **format, options_sprintf *opt, va_list *vl);
int get_length(const char **format, options_sprintf *opt);
int get_specifiers(const char **format, options_sprintf *opt, va_list *vl);

int push_opt(const char **format, options_sprintf *opt, char **str,
             va_list *vl, char *str_begin);

int check_conflict_flags(options_sprintf *opt);



void work_double(const char **format, options_sprintf *opt, char **str,
              va_list *vl, char *buf);
void work_str(const char **format, options_sprintf *opt, char **str,
              va_list *vl, char *buf);
int work_decimal(const char **format, options_sprintf *opt, char **str,
                 va_list *vl, char *buf);
int work_unsigned(const char **format, options_sprintf *opt, char **str,
                  va_list *vl, char *buf);

void work_symbol(const char **format, options_sprintf *opt, char **str,
                 va_list *vl, char *buf);

void s21_itoa(char *buf, options_sprintf *opt, long int var);
void add_precision(char *buf, options_sprintf *opt);
void add_width(char *buf, options_sprintf *opt);
void save_buf_in_str(char **str, char *buf, options_sprintf *opt);

// преобразуем строку в число
s21_size_t string_to_number(const char *start, int number_of_symbols);
// // Переводит символ в число
// int s21_virtual_num(int num, char ch_num);

// // Ищет флаги, длину, ширину, точность
// int s21_post_parse(char spec, char *parse_buff, char *identify_buff, char
// *buffer, va_list arg);

// Записывает строку в буфер
int s21_sprintf(char *str, const char *format, ...);

// // Ищет спецификаторы
// void s21_parse(char *buffer, const char *str, va_list arg);

// // Записывает символ в буфер
// void s21_char(char *buff, int c, options *OP);

// // Идентифицирует флаг
// void s21_identify(char *buff, options *OP, va_list arg);

// // Обрабатывает точку
// int s21_dot(char *parse_buff, char *numbers, options *OP);

// // Записывает строку в буфер
// void s21_putstr(char *buffer, char *str, options *OP);

// // Записывает число в буфер
// void s21_putnbr(char *buffer, long long int n, options *OP);

// // Разбивает число на символы
// char *s21_itoa(int num, char *buffer, int base, options *OP);

// // Разбивает длинное число на символы
// char *s21_long_itoa(long long int num, char *buffer, int base, options *OP);

// // Разбивает короткое число на символы
// char *s21_short_itoa(short int num, char *buffer, int base, options *OP);

// // Записывает беззнаковое число в буфер
// void s21_put_unsigned_nbr(char *buffer, unsigned long long int n, options
// *OP);

// // Разбивает беззнаковое число на символы
// char *s21_utoa(unsigned int n, options *OP);

// // Разбивает длинное беззнаковое число на символы
// char *s21_long_utoa(unsigned long long int n, options *OP);

// // Разбивает короткое беззнаковое число на символы
// char *s21_short_utoa(unsigned short int n, options *OP);

// // Записывает вещественное число в буфер
// void s21_putdbl(char *res, double n, options *OP);

// // Преобразует число с плавающей точкой в строку
// char *s21_gcvt(double f, s21_size_t ndigit, char *buf, options *OP);

// // Меняет последовательность в обратную сторону
// void s21_reverse(char *buffer, int len);

#endif  // SRC_S21_STRING_H_
