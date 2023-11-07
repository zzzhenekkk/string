#include "string.h"

int main () {
  static char buf1 [500] = {0};
  static char buf2 [500] = {0};
  sprintf(buf1, "Hello %d \n", 123);
  s21_sprintf (buf2, "Hello2 %d\n", 456);

  
  printf ("%s", buf1);
  printf ("%s", buf2);
}
