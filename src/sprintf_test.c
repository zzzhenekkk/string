#include "string.h"

int main() {
  static char buff1[500] = {0};
  static char buf1[500] = {0};
  static char buf12[500] = {0};
  static char buf13[500] = {0};
  static char buf14[500] = {0};
  static char buf15[500] = {0};
  static char buf16[500] = {0};
  static char buf17[500] = {0};
  static char buf18[500] = {0};

  static char buf2[500] = {0};
  static char buf22[500] = {0};
  static char buf23[500] = {0};
  static char buf24[500] = {0};
  static char buf25[500] = {0};
  static char buf26[500] = {0};
  static char buf27[500] = {0};
  static char buf28[500] = {0};

  static char buff2[500] = {0};
  static char buff22[500] = {0};
  static char buff23[500] = {0};
  static char buff24[500] = {0};
  static char buff25[500] = {0};
  static char buff26[500] = {0};
  static char buff27[500] = {0};
  static char buff28[500] = {0};

  static char buf3[500] = {0};
  static char buf32[500] = {0};
  static char buf33[500] = {0};
  static char buf34[500] = {0};
  static char buf35[500] = {0};
  static char buf36[500] = {0};
  static char buf37[500] = {0};
  static char buf38[500] = {0};

  static char buf4[500] = {0};

  sprintf(buf1,
          "%d  1d '%1d'  .1d '%.1d'  4d '%4d'  .4d '%.4d'  4.6d '%4.6d'  6.4d "
          "'%6.4d'\n",
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  sprintf(buf12,
          "%d -1d '%-1d' -.1d '%-.1d' -4d '%-4d' -.4d '%-.4d' -4.6d '%-4.6d' "
          "-6.4d '%-6.4d'\n",
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  sprintf(buf13,
          "%d +1d '%+1d' +.1d '%+.1d' +4d '%+4d' +.4d '%+.4d' +4.6d '%+4.6d' "
          "+6.4d '%+6.4d'\n",
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  sprintf(buf14,
          "%d  1d '% 1d'  .1d '% .1d'  4d '% 4d'  .4d '% .4d'  4.6d '% 4.6d' "
          " 6.4d '% 6.4d'\n",
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  sprintf(buf15,
          "%d #1d '%#1d' #.1d '%#.1d' #4d '%#4d' #.4d '%#.4d' #4.6d '%#4.6d' "
          "#6.4d '%#6.4d'\n",
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  sprintf(buf16,
          "%d 01d '%01d' 0.1d '%0.1d' 04d '%04d' 0.4d '%0.4d' 04.6d '%04.6d' "
          "06.4d '%06.4d'\n",
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  sprintf(buf17,
          "%d -+1d '%-+1d' -+.1d '%-+.1d' -+4d '%-+4d' -+.4d '%-+.4d' -+4.6d "
          "'%-+4.6d' "
          "-+6.4d '%-+6.4d'\n",
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  sprintf(buf18,
          "%d -+ 01d '%-+ 01d' -+ 0.1d '%-+ 0.1d' -+ 04d '%-+ 04d' -+ 0.4d "
          "'%-+ 0.4d' -+ 04.6d '%-+ 04.6d' "
          "-+ 06.4d '%-+ 06.4d'\n",
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  sprintf(buf2,
          "!!!%d  1d '%1d'  .1d '%.1d'  4d '%4d'  .4d '%.4d'  4.6d '%4.6d'  6.4d "
          "'%6.4d'\n",
          12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);

s21_sprintf(buff2,
          "!!!%d  1d '%1d'  .1d '%.1d'  4d '%4d'  .4d '%.4d'  4.6d '%4.6d'  6.4d "
          "'%6.4d'\n",
          12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);


  sprintf(buf22,
          "%d -1d '%-1d' -.1d '%-.1d' -4d '%-4d' -.4d '%-.4d' -4.6d '%-4.6d' "
          "-6.4d '%-6.4d'\n",
          12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);

  sprintf(buf23,
          "%d +1d '%+1d' +.1d '%+.1d' +04d '%+04d' +.4d '%+.4d' +4.6d '%+4.6d' "
          "+6.4d '%+6.4d'\n",
          12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);

  sprintf(buf24,
          "%d  1d '% 1d'  .1d '% .1d' 04d '% 04d'  .4d '% .4d'  4.6d '% 4.6d' "
          " 6.4d '% 6.4d'\n",
          12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);

  sprintf(buf25,
          "%d #1d '%#1d' #.1d '%#.1d' #4d '%#4d' #.4d '%#.4d' #4.6d '%#4.6d' "
          "#6.4d '%#6.4d'\n",
          12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);

  sprintf(buf26,
          "%d 01d '%01d' 0.1d '%0.1d' 04d '%04d' 0.4d '%0.4d' 04.6d '%04.6d' "
          "06.4d '%06.4d'\n",
          12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);

  sprintf(buf27,
          "%d -+1d '%-+1d' -+.1d '%-+.1d' -+4d '%-+4d' -+.4d '%-+.4d' -+4.6d "
          "'%-+4.6d' "
          "-+6.4d '%-+6.4d'\n",
          12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);

  sprintf(buf28,
          "%d -+ 01d '%-+ 01d' -+ 0.1d '%-+ 0.1d' -+ 04d '%-+ 04d' -+ 0.4d "
          "'%-+ 0.4d' -+ 04.6d '%-+ 04.6d' "
          "-+ 06.4d '%-+ 06.4d'\n",
          12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);

  sprintf(buf3,
          "%d  1d '%1d'  .1d '%.1d'  4d '%4d'  .4d '%.4d'  4.6d '%4.6d'  6.4d "
          "'%6.4d'\n",
          -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);

  sprintf(buf32,
          "%d -1d '%-1d' -.1d '%-.1d' -4d '%-4d' -.4d '%-.4d' -4.6d '%-4.6d' "
          "-6.4d '%-6.4d'\n",
          -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);

  sprintf(buf33,
          "%d +1d '%+1d' +.1d '%+.1d' +4d '%+4d' +.4d '%+.4d' +4.6d '%+4.6d' "
          "+6.4d '%+6.4d'\n",
          -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);

  sprintf(buf34,
          "%d  1d '% 1d'  .1d '% .1d'  4d '% 4d'  .4d '% .4d'  4.6d '% 4.6d' "
          " 6.4d '% 6.4d'\n",
          -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);

  sprintf(buf35,
          "%d #1d '%#1d' #.1d '%#.1d' #4d '%#4d' #.4d '%#.4d' #4.6d '%#4.6d' "
          "#6.4d '%#6.4d'\n",
          -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);

  sprintf(buf36,
          "%d 01d '%01d' 0.1d '%0.1d' 04d '%04d' 0.4d '%0.4d' 04.6d '%04.6d' "
          "06.4d '%06.4d'\n",
          -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);

  sprintf(buf37,
          "%d -+1d '%-+1d' -+.1d '%-+.1d' -+4d '%-+4d' -+.4d '%-+.4d' -+4.6d "
          "'%-+4.6d' "
          "-+6.4d '%-+6.4d'\n",
          -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);

  sprintf(buf38,
          "%d -+ 01d '%-+ 01d' -+ 0.1d '%-+ 0.1d' -+ 04d '%-+ 04d' -+ 0.4d "
          "'%-+ 0.4d' -+ 04.6d '%-+ 04.6d' "
          "-+ 06.4d '%-+ 06.4d'\n",
          -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);

  s21_sprintf(buff1, ".4 '%.4d' 67 '%d' -67 '%d' 0 '%d' -0 '%d'\n", 67, 67, -67, 0,
              -0);

  printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", buf1, buf12, buf13, buf14, buf15,
         buf16, buf17, buf18);
  printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", buf2, buff2, buf22, buf23, buf24, buf25,
         buf26, buf27, buf28);

  printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", buf3, buf32, buf33, buf34, buf35,
         buf36, buf37, buf38);
  printf("%s\n\n", buf2);
  printf("%s", buff1);
}
