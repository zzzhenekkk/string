#include "string.h"

int main() {
  static char buf1[500] = {0};
  static char buf12[500] = {0};
  static char buf13[500] = {0};
  static char buf14[500] = {0};
  static char buf15[500] = {0};
  static char buf16[500] = {0};
  static char buf17[500] = {0};
  static char buf18[500] = {0};

  static char buff1[500] = {0};
  static char buff12[500] = {0};
  static char buff13[500] = {0};
  static char buff14[500] = {0};
  static char buff15[500] = {0};
  static char buff16[500] = {0};
  static char buff17[500] = {0};
  static char buff18[500] = {0};

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

  static char buff3[500] = {0};
  static char buff32[500] = {0};
  static char buff33[500] = {0};
  static char buff34[500] = {0};
  static char buff35[500] = {0};
  static char buff36[500] = {0};
  static char buff37[500] = {0};
  static char buff38[500] = {0};

  static char buf4[500] = {0};
  static char buf42[500] = {0};
  static char buf43[500] = {0};
  static char buf44[500] = {0};
  static char buf45[500] = {0};
  static char buf46[500] = {0};
  static char buf47[500] = {0};
  static char buf48[500] = {0};

  static char buff4[500] = {0};
  static char buff42[500] = {0};
  static char buff43[500] = {0};
  static char buff44[500] = {0};
  static char buff45[500] = {0};
  static char buff46[500] = {0};
  static char buff47[500] = {0};
  static char buff48[500] = {0};

  sprintf(buf1,
          "%d  1d '%1d'  .1d '%.1d'  4d '%4d'  .4d '%.4d'  4.6d '%4.6d'  6.4d "
          "'%6.4d'",
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  s21_sprintf(
      buff1,
      "%d  1d '%1d'  .1d '%.1d'  4d '%4d'  .4d '%.4d'  4.6d '%4.6d'  6.4d "
      "'%6.4d'\n",
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  sprintf(buf12,
          "%d -1d '%-1d' -.1d '%-.1d' -4d '%-4d' -.4d '%-.4d' -4.6d '%-4.6d' "
          "-6.4d '%-6.4d'",
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  s21_sprintf(
      buff12,
      "%d -1d '%-1d' -.1d '%-.1d' -4d '%-4d' -.4d '%-.4d' -4.6d '%-4.6d' "
      "-6.4d '%-6.4d'\n",
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  sprintf(buf13,
          "%d +1d '%+1d' +.1d '%+.1d' +4d '%+4d' +.4d '%+.4d' +4.6d '%+4.6d' "
          "+6.4d '%+6.4d'",
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  s21_sprintf(
      buff13,
      "%d +1d '%+1d' +.1d '%+.1d' +4d '%+4d' +.4d '%+.4d' +4.6d '%+4.6d' "
      "+6.4d '%+6.4d'\n",
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  sprintf(buf14,
          "%d  1d '% 1d'  .1d '% .1d'  4d '% 4d'  .4d '% .4d'  4.6d '% 4.6d' "
          " 6.4d '% 6.4d'",
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  s21_sprintf(
      buff14,
      "%d  1d '% 1d'  .1d '% .1d'  4d '% 4d'  .4d '% .4d'  4.6d '% 4.6d' "
      " 6.4d '% 6.4d'\n",
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  sprintf(buf15,
          "%d #1d '%#1d' #.1d '%#.1d' #4d '%#4d' #.4d '%#.4d' #4.6d '%#4.6d' "
          "#6.4d '%#6.4d'",
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  s21_sprintf(
      buff15,
      "%d #1d '%#1d' #.1d '%#.1d' #4d '%#4d' #.4d '%#.4d' #4.6d '%#4.6d' "
      "#6.4d '%#6.4d'\n",
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  sprintf(buf16,
          "%d 01d '%01d' 0.1d '%0.1d' 04d '%04d' 0.4d '%0.4d' 04.6d '%04.6d' "
          "06.4d '%06.4d'",
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  s21_sprintf(
      buff16,
      "%d 01d '%01d' 0.1d '%0.1d' 04d '%04d' 0.4d '%0.4d' 04.6d '%04.6d' "
      "06.4d '%06.4d'\n",
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  sprintf(buf17,
          "%d -+1d '%-+1d' -+.1d '%-+.1d' -+4d '%-+4d' -+.4d '%-+.4d' -+4.6d "
          "'%-+4.6d' "
          "-+6.4d '%-+6.4d'\n",
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  s21_sprintf(
      buff17,
      "%d -+1d '%-+1d' -+.1d '%-+.1d' -+4d '%-+4d' -+.4d '%-+.4d' -+4.6d "
      "'%-+4.6d' "
      "-+6.4d '%-+6.4d'\n",
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  sprintf(buf18,
          "%d -+ 01d '%-+ 01d' -+ 0.1d '%-+ 0.1d' -+ 04d '%-+ 04d' -+ 0.4d "
          "'%-+ 0.4d' -+ 04.6d '%-+ 04.6d' "
          "-+ 06.4d '%-+ 06.4d'",
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  s21_sprintf(buff18,
              "%d -+ 01d '%-+ 01d' -+ 0.1d '%-+ 0.1d' -+ 04d '%-+ 04d' -+ 0.4d "
              "'%-+ 0.4d' -+ 04.6d '%-+ 04.6d' "
              "-+ 06.4d '%-+ 06.4d'\n",
              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  sprintf(
      buf2,
      "!!!%d  1d '%1d'  .1d '%.1d'  4d '%4d'  .4d '%.4d'  4.6d '%4.6d'  6.4d "
      "'%6.4d'",
      12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);

  s21_sprintf(
      buff2,
      "!!!%d  1d '%1d'  .1d '%.1d'  4d '%4d'  .4d '%.4d'  4.6d '%4.6d'  6.4d "
      "'%6.4d'\n",
      12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);

  sprintf(
      buf22,
      "$$$%d -1d '%-1d' -.1d '%-.1d' -4d '%-4d' -.4d '%-.4d' -4.6d '%-4.6d' "
      "-6.4d '%-6.4d'",
      12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);
  s21_sprintf(
      buff22,
      "$$$%d -1d '%-1d' -.1d '%-.1d' -4d '%-4d' -.4d '%-.4d' -4.6d '%-4.6d' "
      "-6.4d '%-6.4d'\n",
      12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);

  sprintf(
      buf23,
      "???%d +1d '%+1d' +.1d '%+.1d' +04d '%+04d' +.4d '%+.4d' +4.6d '%+4.6d' "
      "+6.4d '%+6.4d'",
      12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);
  s21_sprintf(
      buff23,
      "??!%d +1d '%+1d' +.1d '%+.1d' +04d '%+04d' +.4d '%+.4d' +4.6d '%+4.6d' "
      "+6.4d '%+6.4d'\n",
      12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);

  sprintf(buf24,
          "%d  1d '% 1d'  .1d '% .1d' 04d '% 04d'  .4d '% .4d'  4.6d '% 4.6d' "
          " 6.4d '% 6.4d'",
          12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);
  s21_sprintf(
      buff24,
      "%d  1d '% 1d'  .1d '% .1d' 04d '% 04d'  .4d '% .4d'  4.6d '% 4.6d' "
      " 6.4d '% 6.4d'\n",
      12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);

  sprintf(buf25,
          "%d #1d '%#1d' #.1d '%#.1d' #4d '%#4d' #.4d '%#.4d' #4.6d '%#4.6d' "
          "#6.4d '%#6.4d'",
          12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);
  s21_sprintf(
      buff25,
      "%d #1d '%#1d' #.1d '%#.1d' #4d '%#4d' #.4d '%#.4d' #4.6d '%#4.6d' "
      "#6.4d '%#6.4d'\n",
      12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);

  sprintf(buf26,
          "%d 01d '%01d' 0.1d '%0.1d' 04d '%04d' 0.4d '%0.4d' 04.6d '%04.6d' "
          "06.4d '%06.4d'",
          12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);
  s21_sprintf(
      buff26,
      "%d 01d '%01d' 0.1d '%0.1d' 04d '%04d' 0.4d '%0.4d' 04.6d '%04.6d' "
      "06.4d '%06.4d'\n",
      12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);

  sprintf(buf27,
          "%d -+1d '%-+1d' -+.1d '%-+.1d' -+4d '%-+4d' -+.4d '%-+.4d' -+4.6d "
          "'%-+4.6d' "
          "-+6.4d '%-+6.4d'",
          12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);
  s21_sprintf(
      buff27,
      "%d -+1d '%-+1d' -+.1d '%-+.1d' -+4d '%-+4d' -+.4d '%-+.4d' -+4.6d "
      "'%-+4.6d' "
      "-+6.4d '%-+6.4d'\n",
      12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);

  sprintf(buf28,
          "%d -+ 01d '%-+ 01d' -+ 0.1d '%-+ 0.1d' -+ 04d '%-+ 04d' -+ 0.4d "
          "'%-+ 0.4d' -+ 04.6d '%-+ 04.6d' "
          "-+ 06.4d '%-+ 06.4d'",
          12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);
  s21_sprintf(buff28,
              "%d -+ 01d '%-+ 01d' -+ 0.1d '%-+ 0.1d' -+ 04d '%-+ 04d' -+ 0.4d "
              "'%-+ 0.4d' -+ 04.6d '%-+ 04.6d' "
              "-+ 06.4d '%-+ 06.4d'\n",
              12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12);

  sprintf(buf3,
          "%d  1d '%1d'  .1d '%.1d'  4d '%4d'  .4d '%.4d'  4.6d '%4.6d'  6.4d "
          "'%6.4d'",
          -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);
  s21_sprintf(
      buff3,
      "%d  1d '%1d'  .1d '%.1d'  4d '%4d'  .4d '%.4d'  4.6d '%4.6d'  6.4d "
      "'%6.4d'\n",
      -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);

  sprintf(buf32,
          "%d -1d '%-1d' -.1d '%-.1d' -4d '%-4d' -.4d '%-.4d' -4.6d '%-4.6d' "
          "-6.4d '%-6.4d'",
          -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);
  s21_sprintf(
      buff32,
      "%d -1d '%-1d' -.1d '%-.1d' -4d '%-4d' -.4d '%-.4d' -4.6d '%-4.6d' "
      "-6.4d '%-6.4d'\n",
      -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);

  sprintf(buf33,
          "%d +1d '%+1d' +.1d '%+.1d' +4d '%+4d' +.4d '%+.4d' +4.6d '%+4.6d' "
          "+6.4d '%+6.4d'",
          -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);
  s21_sprintf(
      buff33,
      "%d +1d '%+1d' +.1d '%+.1d' +4d '%+4d' +.4d '%+.4d' +4.6d '%+4.6d' "
      "+6.4d '%+6.4d'\n",
      -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);

  sprintf(buf34,
          "%d  1d '% 1d'  .1d '% .1d'  4d '% 4d'  .4d '% .4d'  4.6d '% 4.6d' "
          " 6.4d '% 6.4d'",
          -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);
  s21_sprintf(
      buff34,
      "%d  1d '% 1d'  .1d '% .1d'  4d '% 4d'  .4d '% .4d'  4.6d '% 4.6d' "
      " 6.4d '% 6.4d'\n",
      -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);

  sprintf(buf35,
          "%d #1d '%#1d' #.1d '%#.1d' #4d '%#4d' #.4d '%#.4d' #4.6d '%#4.6d' "
          "#6.4d '%#6.4d'",
          -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);
  s21_sprintf(
      buff35,
      "%d #1d '%#1d' #.1d '%#.1d' #4d '%#4d' #.4d '%#.4d' #4.6d '%#4.6d' "
      "#6.4d '%#6.4d'\n",
      -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);

  sprintf(buf36,
          "%d 01d '%01d' 0.1d '%0.1d' 04d '%04d' 0.4d '%0.4d' 04.6d '%04.6d' "
          "06.4d '%06.4d'",
          -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);
  s21_sprintf(
      buff36,
      "%d 01d '%01d' 0.1d '%0.1d' 04d '%04d' 0.4d '%0.4d' 04.6d '%04.6d' "
      "06.4d '%06.4d'\n",
      -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);

  sprintf(buf37,
          "%d -+1d '%-+1d' -+.1d '%-+.1d' -+4d '%-+4d' -+.4d '%-+.4d' -+4.6d "
          "'%-+4.6d' "
          "-+6.4d '%-+6.4d'",
          -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);
  s21_sprintf(
      buff37,
      "%d -+1d '%-+1d' -+.1d '%-+.1d' -+4d '%-+4d' -+.4d '%-+.4d' -+4.6d "
      "'%-+4.6d' "
      "-+6.4d '%-+6.4d'\n",
      -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);

  sprintf(buf38,
          "*****%d -01d '%-01d' -0.1d '%-0.1d' -04d '%-04d' -0.4d "
          "'%-0.4d' -04.6d '%-04.6d' "
          "-06.4d '%-06.4d'",
          -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);
  s21_sprintf(buff38,
              "*****%d -01d '%-01d' -0.1d '%-0.1d' -04d '%-04d' -0.4d "
              "'%-0.4d' -04.6d '%-04.6d' "
              "-06.4d '%-06.4d'\n",
              -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);

  printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
         buf1, buff1, buf12, buff12, buf13, buff13, buf14, buff14, buf15,
         buff15, buf16, buff16, buf17, buff17, buf18, buff18);

  printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
         buf2, buff2, buf22, buff22, buf23, buff23, buf24, buff24, buf25,
         buff25, buf26, buff26, buf27, buff27, buf28, buff28);

  printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
         buf3, buff3, buf32, buff32, buf33, buff33, buf34, buff34, buf35,
         buff35, buf36, buff36, buf37, buff37, buf38, buff38);

  sprintf(buf4, "%+d 04d '%+04d' ' 04d''% 04d' +04.1d '%+04.1d'", 12, 12, 12,
          12, 12);

  s21_sprintf(buff4, "%+d 04d '%+04d' ' 04d''% 04d' +04.1d '%+04.1d'", 12, 12,
              12, 12, 12);

  printf("%s\n%s\n", buf4, buff4);

  static char test[500] = {0};
  sprintf(test, "Hello '%#-12x'", 015);
  printf("%s\n", test);

  static char test2[500] = {0};
  s21_sprintf(test2, "Hello '%#-12x'", 015);
  printf("%s\n", test2);

  static char test3[500] = {0};
  sprintf(test3, "Hello '%-010c'", 'e');
  printf("%s\n", test3);

  static char testt3[500] = {0};
  s21_sprintf(testt3, "Hello '%-010c'", 'e');
  printf("%s\n", testt3);

  static char test4[500] = {0};
  sprintf(test3, "11Hello '%010.1s'", "Sok");
  printf("%s\n", test3);

  static char testt4[500] = {0};
  s21_sprintf(testt4, "11Hello '%010.1s'", "Sok");
  printf("%s\n", testt4);
  // обгуляются флаги для +' '

  return 0;
}
