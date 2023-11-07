#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *p = (unsigned char *)str;
  int flag = 1;
  while (n--) {
    if (*p != (unsigned char)c) {
      p++;
    } else {
      flag = 0;
      break;
    }
  }
  if (flag) {
    p = 0;
  }
  return p;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *p1 = str1, *p2 = str2;
  int res, flag = 1;
  while (n--) {
    if (*p1 != *p2) {
      flag = 0;
      res = *p1 - *p2;
      break;
    } else {
      p1++, p2++;
    }
  }
  if (flag) {
    res = 0;
  }
  return res;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *dp = dest;
  const char *sp = src;
  while (n--) {
    *dp++ = *sp++;
  }
  return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *d_ptr, *s_ptr;
  s21_size_t i;
  int delta;
  if (dest < src) {
    d_ptr = (char *)dest;
    s_ptr = (char *)src;
    delta = 1;
  } else if (dest > src) {
    d_ptr = (char *)dest + n - 1;
    s_ptr = (char *)src + n - 1;
    delta = -1;
  } else {
    return dest;
  }
  for (i = 0; i < n; ++i) {
    *d_ptr = *s_ptr;
    d_ptr += delta;
    s_ptr += delta;
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *p = (unsigned char *)str;
  for (s21_size_t i = 0; i != n; i++) {
    p[i] = c;
  }
  return str;
}

char *s21_strcat(char *dest, const char *src) {
  char *begin = dest;
  while (*dest) {
    dest++;
  }
  while (*src) {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
  return begin;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *begin = dest;
  while (*dest) {
    dest++;
  }
  while (*src && (n != 0)) {
    *dest = *src;
    dest++;
    src++;
    n--;
  }
  *dest = '\0';
  return begin;
}

char *s21_strchr(const char *str, int c) {
  while (*str != (char)c) {
    if (!*str++) {
      return s21_NULL;
    }
  }
  return (char *)str;
}

int s21_strcmp(const char *str1, const char *str2) {
  while (*str1 && *str1 == *str2) {
    ++str1;
    ++str2;
  }
  return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res, flag = 1;
  while (n--) {
    if (*str1++ != *str2++) {
      flag = 0;
      res = *(unsigned char *)(str1 - 1) - *(unsigned char *)(str2 - 1);
      break;
    }
  }
  if (flag) {
    res = 0;
  }
  return res;
}

char *s21_strcpy(char *dest, const char *src) {
  char *addres = dest;
  while (*src != '\0') {
    *dest++ = *src++;
  }
  *dest = *src;
  return addres;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *address = dest;
  while (*src != '\0' && (n != 0)) {
    *dest++ = *src++;
    n--;
  }
  dest[s21_strlen(dest)] = '\0';
  return address;
}

// char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
//   s21_size_t stringlen = s21_strnlen(src, n);
//   if (stringlen != n) {
//     s21_memset(dest + stringlen, '\0', n - stringlen);
//   }
//   return s21_memcpy(dest, src, stringlen);
// }

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

int s21_strlen(const char *str) {
  int counter = 0;
  while (str[counter] != '\0') {
    counter++;
  }
  return counter;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  while (*str1) {
    if (s21_strchr(str2, *str1++)) {
      return (char *)--str1;
    }
  }
  return 0;
}

char *s21_strrchr(const char *str, int c) {
  const char *ptr = s21_NULL;
  while (*str != '\0') {
    if (*str == c) {
      ptr = str;
    }
    str++;
  }
  if (*str == c) {
    ptr = str;
  }
  if (ptr != 0) {
    return (char *)ptr;
  }
  return 0;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t len = 0;
  while (*str1 && s21_strchr(str2, *str1++)) {
    len++;
  }
  return len;
}

char *s21_strstr(const char *haystack, const char *needle) {
  const char *s1 = haystack;
  const char *s2 = needle;
  s21_size_t n = s21_strlen(s2);
  if (n == 0) {
    return (char *)s1;
  }
  while (*s1) {
    if (!s21_memcmp(s1++, s2, n)) {
      s1--;
      return (char *)s1;
    }
  }
  return s21_NULL;
}

char *s21_strtok(char *str, const char *delim) {
  static char *p = 0;
  if (str) {
    p = str;
  } else if (p == 0) {
    return 0;
  }
  str = p + s21_strspn(p, delim);
  p = str + s21_strcspn(str, delim);
  if (p == str) {
    return p = 0;
  }
  p = *p ? *p = 0, p + 1 : 0;
  return str;
}
