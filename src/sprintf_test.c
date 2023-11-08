#include "string.h"

int main() {
  static char buf1[500] = {0};
  static char buf3[500] = {0};
  static char buf4[500] = {0};
  static char buf2[500] = {0};


  
  sprintf(buf3, "%d 7d '%7d' .7d '%.7d' 3.7d '%3.7d' 10.7d '%10.7d'\n", 123, 123, 123, 123, 123, 123, 123, 123, 123);
  
  sprintf(buf1, "%d 6d '%6d' 6.10d '%6.10d' -.10d '%-.10d' +.10d '%+.10d'\n", 123, 123, 123, 123, 123);
  
  s21_sprintf(buf2, "Hello2 %+- #0*.*ld\n", 555, 667);

printf("%s", buf4);
  printf("%s", buf3);
  printf("%s", buf1);
  printf("%s", buf2);
}
