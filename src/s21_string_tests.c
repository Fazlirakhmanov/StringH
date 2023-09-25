#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(strtok_1) {
  char str[] = {"UwU"};
  char *res_my = s21_strtok(str, "UwU");
  char *res = strtok(str, "UwU");
  ck_assert_ptr_null(res);
  ck_assert_ptr_null(res_my);
}
END_TEST

START_TEST(strtok_2) {
  char str[] = {"Сегодня - последний день лета"};
  char *res_my = s21_strtok(str, "-");
  char *res = strtok(str, "-");
  ck_assert_str_eq(res_my, res);
}
END_TEST

START_TEST(strtok_3) {
  char str[] = {"Pneumonoultramicroscopicsilicovolcanokoniosis"};
  char *res_my = s21_strtok(str, "s");
  char *res = strtok(str, "s");
  ck_assert_str_eq(res_my, res);
}
END_TEST

START_TEST(strtok_4) {
  char str[] = "1";
  char *res_my = s21_strtok(str, "\0");
  char *res = strtok(str, "\0");
  ck_assert_str_eq(res_my, res);
}
END_TEST

START_TEST(strtok_5) {
  char str[] = {"something with\0 error"};
  char *res_my = s21_strtok(str, "error");
  char *res = strtok(str, "error");
  ck_assert_str_eq(res_my, res);
}
END_TEST

START_TEST(strtok_6) {
  char str[] = "";
  char *res_my = s21_strtok(str, "");
  char *res = strtok(str, "");
  ck_assert_ptr_null(res);
  ck_assert_ptr_null(res_my);
}
END_TEST

START_TEST(strtok_7) {
  char *res_my = s21_strtok(NULL, "");
  char *res = strtok(NULL, "");
  ck_assert_ptr_null(res);
  ck_assert_ptr_null(res_my);
}
END_TEST

START_TEST(strncat_1) {
  char str_1[100] = "Mai-ia-hii";
  char str_2[100] = "Mai-ia-huu";
  ck_assert_str_eq(s21_strncat(str_1, str_2, 6), strncat(str_1, str_2, 6));
}
END_TEST

START_TEST(strncat_2) {
  char str_1[100] = "1234";
  char str_2[100] = "Mai-ia-huu";
  ck_assert_str_eq(s21_strncat(str_1, str_2, 6), strncat(str_1, str_2, 6));
}
END_TEST

START_TEST(strncat_3) {
  char str_1[100] = "Can’t touch this (oh-oh oh oh oh-oh-oh)";
  char str_2[100] = "My-my-my-my music";
  ck_assert_str_eq(s21_strncat(str_1, str_2, 60), strncat(str_1, str_2, 60));
}
END_TEST

START_TEST(strerror_1) {
  for (int i = 0; i < 150; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

START_TEST(test_s21_memcpy) {
  int i = 10;
  char str1[100] = "Hello, World";
  char str2[100] = " ,!";
  char str3[100] = "abrakadabra";
  char str4[100];
  ck_assert_str_eq(s21_memcpy(str4, str1, i), memcpy(str4, str1, i));
  ck_assert_str_eq(s21_memcpy(str4, str2, i), memcpy(str4, str2, i));
  ck_assert_str_eq(s21_memcpy(str4, str3, i), memcpy(str4, str3, i));
}
END_TEST

START_TEST(test_s21_memset) {
  int i = 10;
  char str4[100];
  ck_assert_str_eq(s21_memset(str4, 'a', i), memset(str4, 'a', i));
  ck_assert_str_eq(s21_memset(str4, '3', i), memset(str4, '3', i));
}
END_TEST

START_TEST(test_s21_strncpy) {
  int i = 10;
  char str1[100] = "Hello, World";
  char str2[100] = " ,!";
  char str3[100] = "abrakadabra";
  char str4[100];
  ck_assert_str_eq(s21_strncpy(str4, str1, i), strncpy(str4, str1, i));
  ck_assert_str_eq(s21_strncpy(str4, str2, i), strncpy(str4, str2, i));
  ck_assert_str_eq(s21_strncpy(str4, str3, i), strncpy(str4, str3, i));
}
END_TEST

START_TEST(test_s21_strlen) {
  char *str_strlen = "How are you today, buddy?";
  size_t res1 = s21_strlen(str_strlen);
  size_t res2 = strlen(str_strlen);
  ck_assert_int_eq(res1, res2);

  str_strlen = "abrakadabra";
  res1 = s21_strlen(str_strlen);
  res2 = strlen(str_strlen);
  ck_assert_int_eq(res1, res2);

  str_strlen = "987 sadfdasf 097879 as8";
  res1 = s21_strlen(str_strlen);
  res2 = strlen(str_strlen);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_strcspn) {
  char str_strcspn[4096] = "Hello, World!";
  size_t res1 = s21_strcspn(str_strcspn, "aeiou");
  size_t res2 = strcspn(str_strcspn, "aeiou");
  ck_assert_int_eq(res1, res2);

  res1 = s21_strcspn(str_strcspn, "abc123xyz");
  res2 = strcspn(str_strcspn, "0123456789");
  ck_assert_int_eq(res1, res2);

  res1 = s21_strcspn(str_strcspn, "12345");
  res2 = strcspn(str_strcspn, "12345");
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_c_1) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  s21_sprintf(str, "test %c", 'V');
  sprintf(str_res, "test %c", 'V');
  ck_assert_str_eq(str, str_res);
}
END_TEST

START_TEST(sprintf_c_2) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  s21_sprintf(str, "test %c%c", 'V', 'N');
  sprintf(str_res, "test %c%c", 'V', 'N');
  ck_assert_str_eq(str, str_res);
}
END_TEST

START_TEST(sprintf_c_3) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  s21_sprintf(str, "test %c%ctest", 'V', 'N');
  sprintf(str_res, "test %c%ctest", 'V', 'N');
  ck_assert_str_eq(str, str_res);
}
END_TEST

START_TEST(sprintf_c_4) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  s21_sprintf(str, "test %c%-ctest", 'V', 'N');
  sprintf(str_res, "test %c%-ctest", 'V', 'N');
  ck_assert_str_eq(str, str_res);
}
END_TEST

START_TEST(sprintf_s_1) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  s21_sprintf(str, "test %s", "Veronica");
  sprintf(str_res, "test %s", "Veronica");
  ck_assert_str_eq(str, str_res);
}
END_TEST

START_TEST(sprintf_s_2) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  s21_sprintf(str, "test %s %s", "maked by", "Veronica");
  sprintf(str_res, "test %s %s", "maked by", "Veronica");
  ck_assert_str_eq(str, str_res);
}
END_TEST

START_TEST(sprintf_s_3) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  s21_sprintf(str, "test %s %s student", "school", "Veronica");
  sprintf(str_res, "test %s %s student", "school", "Veronica");
  ck_assert_str_eq(str, str_res);
}
END_TEST

START_TEST(sprintf_f_1) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  s21_sprintf(str, "test %f", 12.6);
  sprintf(str_res, "test %f", 12.6);
  ck_assert_str_eq(str, str_res);
}
END_TEST

START_TEST(sprintf_f_2) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  s21_sprintf(str, "test %f,%f", 12.6, 100.001);
  sprintf(str_res, "test %f,%f", 12.6, 100.001);
  ck_assert_str_eq(str, str_res);
}
END_TEST

START_TEST(sprintf_f_3) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  s21_sprintf(str, "test % f,%+f", 12.6, 100.001);
  sprintf(str_res, "test % f,%+f", 12.6, 100.001);
  ck_assert_str_eq(str, str_res);
}
END_TEST

START_TEST(sprintf_f_4) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  int a = s21_sprintf(str, "test % 014f,%-+12f", 12.6, 100.001);
  int b = sprintf(str_res, "test % 014f,%-+12f", 12.6, 100.001);
  ck_assert_str_eq(str, str_res);
  ck_assert_uint_eq(a, b);
}
END_TEST

START_TEST(sprintf_f_5) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  int a = s21_sprintf(str, "test % 014.3f,%-+12.3f", 12.6, 100.001);
  int b = sprintf(str_res, "test % 014.3f,%-+12.3f", 12.6, 100.001);
  ck_assert_str_eq(str, str_res);
  ck_assert_uint_eq(a, b);
}
END_TEST

START_TEST(sprintf_f_6) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  int a = s21_sprintf(str, "test %.0f,%#.0f, %f", 12., 100., 69.);
  int b = sprintf(str_res, "test %.0f,%#.0f, %f", 12., 100., 69.);
  ck_assert_str_eq(str, str_res);
  ck_assert_uint_eq(a, b);
}
END_TEST

START_TEST(sprintf_n_1) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  int a = 0, b = 0, c = 0, d = 0;
  s21_sprintf(str, "test %n here is not the end %n", &a, &b);
  sprintf(str_res, "test %n here is not the end %n", &c, &d);
  ck_assert_uint_eq(a, c);
  ck_assert_uint_eq(b, d);
}
END_TEST

START_TEST(sprintf_o_1) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  int a = s21_sprintf(str, "test %014o,%-12o", 12, 100001);
  int b = sprintf(str_res, "test %014o,%-12o", 12, 100001);

  ck_assert_str_eq(str, str_res);
  ck_assert_uint_eq(a, b);
}
END_TEST

START_TEST(sprintf_o_2) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  int a = s21_sprintf(str, "test %14.4o,%-12.4o", 12, 100001);
  int b = sprintf(str_res, "test %14.4o,%-12.4o", 12, 100001);
  ck_assert_str_eq(str, str_res);
  ck_assert_uint_eq(a, b);
}
END_TEST

START_TEST(sprintf_o_3) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  int a = s21_sprintf(str, "test %#14.4o,%#-12.4o", 12, 100001);
  int b = sprintf(str_res, "test %#14.4o,%#-12.4o", 12, 100001);
  ck_assert_str_eq(str, str_res);
  ck_assert_uint_eq(a, b);
}
END_TEST

START_TEST(sprintf_x_1) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  int a = s21_sprintf(str, "test %014x,%-12x", 12, 100001);
  int b = sprintf(str_res, "test %014x,%-12x", 12, 100001);
  ck_assert_str_eq(str, str_res);
  ck_assert_uint_eq(a, b);
}
END_TEST

START_TEST(sprintf_x_2) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  int a = s21_sprintf(str, "test %14.4x,%-12.4x", 12, 100001);
  int b = sprintf(str_res, "test %14.4x,%-12.4x", 12, 100001);
  ck_assert_str_eq(str, str_res);
  ck_assert_uint_eq(a, b);
}
END_TEST

START_TEST(sprintf_x_3) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  int a = s21_sprintf(str, "test %#14.4x,%#-12.4x", 12, 100001);
  int b = sprintf(str_res, "test %#14.4x,%#-12.4x", 12, 100001);
  ck_assert_str_eq(str, str_res);
  ck_assert_uint_eq(a, b);
}
END_TEST

START_TEST(sprintf_X_1) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  int a = s21_sprintf(str, "test %014X,%-12X", 12, 100001);
  int b = sprintf(str_res, "test %014X,%-12X", 12, 100001);
  ck_assert_str_eq(str, str_res);
  ck_assert_uint_eq(a, b);
}
END_TEST

START_TEST(sprintf_X_2) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  int a = s21_sprintf(str, "test %14.4X,%-12.4X", 12, 100001);
  int b = sprintf(str_res, "test %14.4X,%-12.4X", 12, 100001);
  ck_assert_str_eq(str, str_res);
  ck_assert_uint_eq(a, b);
}
END_TEST

START_TEST(sprintf_X_3) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  int a = s21_sprintf(str, "test %#14.4X,%#-12.4X", 12, 100001);
  int b = sprintf(str_res, "test %#14.4X,%#-12.4X", 12, 100001);
  ck_assert_str_eq(str, str_res);
  ck_assert_uint_eq(a, b);
}
END_TEST

START_TEST(sprintf_g_1) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  int a = sprintf(str, "test %06.9g", 92008.00);
  int b = s21_sprintf(str_res, "test %06.9g", 92008.00);
  ck_assert_str_eq(str, str_res);
  ck_assert_uint_eq(a, b);
}
END_TEST

START_TEST(sprintf_g_2) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  int a = sprintf(str, "test %12g", 0.9200800);
  int b = s21_sprintf(str_res, "test %12g", 0.9200800);
  ck_assert_str_eq(str, str_res);
  ck_assert_uint_eq(a, b);
}
END_TEST

START_TEST(sprintf_p_1) {
  static char str[BUFSIZ];
  static char str_res[BUFSIZ];
  int count = 500;
  int count2 = 500;
  int a = s21_sprintf(str, "test %14p,%-12p", &count, &count2);
  int b = sprintf(str_res, "test %14p,%-12p", &count, &count2);
  ck_assert_str_eq(str, str_res);
  ck_assert_uint_eq(a, b);
}
END_TEST

/* SEARCH (memchr, strchr, strpbrk, strrchr, strstr) */

START_TEST(memchr_1) {
  char str[] = "Hello, world!";
  int ch = ' ';
  s21_size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), s21_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_2) {
  char str[] = "Hello, world!";
  int ch = 101;
  s21_size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), s21_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_3) {
  char str[] = "Hello, world!";
  int ch = '1';
  s21_size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), s21_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_4) {
  char str[] = "Hello, world!";
  int ch = 65;
  s21_size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), s21_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_5) {
  char str[] = "Hello, world!";
  int ch = 'l';
  s21_size_t len = 10;
  ck_assert_ptr_eq(memchr(str, ch, len), s21_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_6) {
  char str[] = "Hello, world!";
  int ch = 'w';
  s21_size_t len = 5;
  ck_assert_ptr_eq(memchr(str, ch, len), s21_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_7) {
  char str[] = "69917020";
  int ch = '3';
  s21_size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), s21_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_8) {
  char str[] = "69917020";
  int ch = '6';
  s21_size_t len = 0;
  ck_assert_ptr_eq(memchr(str, ch, len), s21_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_9) {
  char str[] = "69917020";
  int ch = 'g';
  s21_size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), s21_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_10) {
  char str[] = "69917020";
  int ch = '\0';
  s21_size_t len = 9;
  ck_assert_ptr_eq(memchr(str, ch, len), s21_memchr(str, ch, len));
}
END_TEST

START_TEST(strchr_1) {
  char s[] = "Hello, world!";
  int ch = 'h';
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST

START_TEST(strchr_2) {
  char s[] = "Hello, world!";
  int ch = '\0';
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST

START_TEST(strchr_3) {
  char s[] = "Hello, world!";
  int ch = ',';
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST

START_TEST(strchr_4) {
  char s[] = "Hello, world!";
  int ch = 33;
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST

START_TEST(strchr_5) {
  char s[] = "Hello, Polina!";
  int ch = 'P';
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST

START_TEST(strchr_6) {
  char s[] = "Hello, world!";
  int ch = 'w';
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST

START_TEST(strchr_7) {
  char s[] = "Hello, world!";
  int ch = '0';
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST

START_TEST(strchr_8) {
  char s[] = "Hello, world!";
  int ch = 'm';
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST

START_TEST(strpbrk_1) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, world!";
  ck_assert_pstr_eq(strpbrk(s1, s2), s21_strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_2) {
  char s1[] = "Hello, world!";
  char s2[] = "!";
  ck_assert_pstr_eq(strpbrk(s1, s2), s21_strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_3) {
  char s1[] = "";
  char s2[] = "He";
  ck_assert_pstr_eq(strpbrk(s1, s2), s21_strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_4) {
  char s1[] = "\0";
  char s2[] = "";
  ck_assert_pstr_eq(strpbrk(s1, s2), s21_strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_5) {
  char s1[] = "";
  char s2[] = "";
  ck_assert_pstr_eq(strpbrk(s1, s2), s21_strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_6) {
  char s1[] = "1242434246364377659";
  char s2[] = "364377659";
  ck_assert_pstr_eq(strpbrk(s1, s2), s21_strpbrk(s1, s2));
}
END_TEST

START_TEST(strrchr_1) {
  char s[] = "Hello, world!";
  int ch = 'h';
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST

START_TEST(strrchr_2) {
  char s[] = "Hello, world!";
  int ch = '\0';
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST

START_TEST(strrchr_3) {
  char s[] = "Hello, world!";
  int ch = ',';
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST

START_TEST(strrchr_4) {
  char s[] = "Hello, world!";
  int ch = 33;
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST

START_TEST(strrchr_5) {
  char s[] = "Hello, Polina!";
  int ch = 'P';
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST

START_TEST(strrchr_6) {
  char s[] = "Hello, world!";
  int ch = 'w';
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST

START_TEST(strrchr_7) {
  char s[] = "Hello, world!";
  int ch = '0';
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST

START_TEST(strrchr_8) {
  char s[] = "Hello, world!";
  int ch = 'm';
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST

START_TEST(strstr_1) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, world!";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_2) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, P!";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_3) {
  char s1[] = "Hello, world!";
  char s2[] = "!";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_4) {
  char s1[] =
      "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!";
  char s2[] = "world";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_5) {
  char s1[] = "";
  char s2[] = "";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_6) {
  char s1[] = "Hello, world!";
  char s2[] = "";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_7) {
  char s1[] = "";
  char s2[] = "Hello, P!";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_8) {
  char s1[] = "69917020";
  char s2[] = "0";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_9) {
  char s1[] = "69917020";
  char s2[] = "\0";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_10) {
  char s1[] = "69917020";
  char s2[] = "32859160 8v3489-74 tvc4y8719c n4[nqymu uv 4vm9cw";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_11) {
  char s1[] = "1   345 345 345 345 345";
  char s2[] = "345";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_12) {
  char s1[] = "sususususpicioussusususpicious";
  char s2[] = "susp";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_13) {
  char s1[] = "sus";
  char s2[] = "suspi";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(memcmp_1) {
  char *test1 = "Hello World Cat Dog";
  char *test2 = "Hello World Alla Walla";
  ck_assert_uint_eq(s21_memcmp(test1, test2, 11) > 0,
                    memcmp(test1, test2, 11) > 0);
}
END_TEST

START_TEST(memcmp_2) {
  char *test1 = "Hello World Cat Dog";
  char *test2 = "Hello World Alla Walla";
  ck_assert_uint_eq(s21_memcmp(test1, test2, 11) > 0,
                    memcmp(test1, test2, 11) > 0);
}
END_TEST

START_TEST(memcmp_3) {
  char *test1 = "Hello World Cat Dog";
  char *test2 = "Hello World Alla Walla";
  ck_assert_uint_eq(s21_memcmp(test1, test2, 5) == 0,
                    memcmp(test1, test2, 5) == 0);
}
END_TEST

START_TEST(memcmp_4) {
  char *test2 = "Hello World Alla Walla";
  char *test3 = "123455";
  ck_assert_uint_eq(s21_memcmp(test3, test2, 2) < 0,
                    memcmp(test3, test2, 2) < 0);
}
END_TEST

START_TEST(memcmp_5) {
  int test4[] = {1, 2, 3, 4, 5};
  int test5[] = {1, 2, 3, 4, 6};
  ck_assert_uint_eq(s21_memcmp(test4, test5, 4) == 0,
                    memcmp(test4, test5, 4) == 0);
}
END_TEST

START_TEST(memcmp_6) {
  int test4[] = {1, 2, 3, 4, 5};
  int test5[] = {1, 2, 3, 4, 6};
  ck_assert_uint_eq(s21_memcmp(test4, test5, 3) < 0,
                    memcmp(test4, test5, 3) < 0);
}
END_TEST

START_TEST(memcmp_7) {
  char test7[] = "goga\0 job";
  char test8[] = "goga\0 job";
  ck_assert_uint_eq(s21_memcmp(test7, test8, 2) == 0,
                    memcmp(test7, test8, 2) == 0);
}
END_TEST

START_TEST(memcmp_9) {
  char *test1 = "Hello World Cat Dog";
  char test8[] = "goga\0 job";
  ck_assert_uint_eq(s21_memcmp(test1, test8, 3) < 0,
                    memcmp(test1, test8, 3) < 0);
}
END_TEST

START_TEST(memcmp_10) {
  char *test1 = "Hello World Cat Dog";
  char *test2 = "Hello World";
  ck_assert_uint_eq(s21_memcmp(test1, test2, 5) < 0,
                    memcmp(test1, test2, 5) < 0);
}
END_TEST

START_TEST(strncmp_1) {
  char *test1 = "Hello World Cat Dog";
  char *test2 = "Hello World Alla Walla";
  ck_assert_uint_eq(s21_strncmp(test1, test2, 2), strncmp(test1, test2, 2));
}
END_TEST

START_TEST(strncmp_2) {
  char *test1 = "Hello World Cat Dog";
  char *test2 = "Hello World Alla Walla";
  ck_assert_uint_eq(s21_strncmp(test1, test2, 11), strncmp(test1, test2, 11));
}
END_TEST

START_TEST(strncmp_3) {
  char *test1 = "Hello World Cat Dog";
  char *test2 = "Hello World Alla Walla";
  ck_assert_uint_eq(s21_strncmp(test1, test2, 14), strncmp(test1, test2, 14));
}
END_TEST

START_TEST(strncmp_4) {
  char *test1 = "Hello World Cat Dog";
  char *test2 = "Hello World Alla Walla";
  ck_assert_uint_eq(s21_strncmp(test1, test2, 18), strncmp(test1, test2, 18));
}
END_TEST

START_TEST(strncmp_5) {
  char test7[] = "goga\0 job";
  char test8[] = "goga\0 job";
  ck_assert_uint_eq(s21_strncmp(test7, test8, 9), strncmp(test7, test8, 9));
}
END_TEST

START_TEST(strncmp_6) {
  char test6[] = "\0";
  char test7[] = "goga\0 job";
  ck_assert_uint_eq(s21_strncmp(test6, test7, 1), strncmp(test6, test7, 1));
}
END_TEST

START_TEST(strncmp_7) {
  char *test1 = "Hello World Cat Dog";
  char test8[] = "goga\0 job";
  ck_assert_uint_eq(s21_strncmp(test1, test8, 5), strncmp(test1, test8, 5));
}
END_TEST

START_TEST(s21_trim_test_1) {
  const char test_str_1[50] = "hello world";
  const char test_trim_set_1[50] = "dh";
  char *trim_result_1 = (char *)(s21_trim(test_str_1, test_trim_set_1));
  ck_assert_str_eq("ello worl", trim_result_1);
  if (trim_result_1) free(trim_result_1);
}
END_TEST

START_TEST(s21_trim_test_2) {
  const char test_str_2[50] = "123abc456xyz789";
  const char test_trim_set_2[50] = "123456789";
  char *trim_result_2 = (char *)(s21_trim(test_str_2, test_trim_set_2));
  ck_assert_str_eq("abc456xyz", trim_result_2);
  if (trim_result_2) free(trim_result_2);
}
END_TEST

START_TEST(s21_trim_test_3) {
  const char test_str_3[50] = "---abc---xyz----";
  const char test_trim_set_3[50] = "-";
  char *trim_result_3 = (char *)(s21_trim(test_str_3, test_trim_set_3));
  ck_assert_str_eq("abc---xyz", trim_result_3);
  if (trim_result_3) free(trim_result_3);
}
END_TEST

START_TEST(s21_trim_test_4) {
  const char test_str_4[50] = "*** Much Ado About Nothing ***";
  const char test_trim_set_4[50] = "*?/ ";
  char *trim_result_4 = (char *)(s21_trim(test_str_4, test_trim_set_4));
  ck_assert_str_eq("Much Ado About Nothing", trim_result_4);
  if (trim_result_4) free(trim_result_4);
}
END_TEST

START_TEST(s21_trim_test_5) {
  const char test_str_5[50] = "hello world";
  const char test_trim_set_5[50] = "dh--";
  char *trim_result_5 = (char *)(s21_trim(test_str_5, test_trim_set_5));
  ck_assert_str_eq("ello worl", trim_result_5);
  if (trim_result_5) free(trim_result_5);
}
END_TEST

START_TEST(s21_trim_test_6) {
  const char test_str_6[50] = "123abc456xyz789";
  const char test_trim_set_6[50] = "12345678900000";
  char *trim_result_6 = (char *)(s21_trim(test_str_6, test_trim_set_6));
  ck_assert_str_eq("abc456xyz", trim_result_6);
  if (trim_result_6) free(trim_result_6);
}
END_TEST

START_TEST(s21_trim_test_7) {
  const char test_str_7[50] = "---abc---xyz----";
  const char test_trim_set_7[50] = "-?";
  char *trim_result_7 = (char *)(s21_trim(test_str_7, test_trim_set_7));
  ck_assert_str_eq("abc---xyz", trim_result_7);
  if (trim_result_7) free(trim_result_7);
}
END_TEST

START_TEST(s21_trim_test_8) {
  const char test_str_8[50] = "*** Much Ado About Nothing ***";
  const char test_trim_set_8[50] = "*_?/ ";
  char *trim_result_8 = (char *)(s21_trim(test_str_8, test_trim_set_8));
  ck_assert_str_eq("Much Ado About Nothing", trim_result_8);
  if (trim_result_8) free(trim_result_8);
}
END_TEST

START_TEST(s21_trim_test_9) {
  const char test_str_9[50] = "hello world";
  const char test_trim_set_9[50] = "--";
  char *trim_result_9 = (char *)(s21_trim(test_str_9, test_trim_set_9));
  ck_assert_str_eq("hello world", trim_result_9);
  if (trim_result_9) free(trim_result_9);
}
END_TEST

START_TEST(s21_trim_test_10) {
  const char test_str_10[50] = "123abc456xyz789";
  const char test_trim_set_10[50] = "0";
  char *trim_result_10 = (char *)(s21_trim(test_str_10, test_trim_set_10));
  ck_assert_str_eq("123abc456xyz789", trim_result_10);
  if (trim_result_10) free(trim_result_10);
}
END_TEST

START_TEST(s21_trim_test_11) {
  const char test_str_11[50] = "";
  const char test_trim_set_11[50] = "abc";
  char *trim_result_11 = (char *)(s21_trim(test_str_11, test_trim_set_11));
  ck_assert_str_eq("", trim_result_11);
  if (trim_result_11) free(trim_result_11);
}
END_TEST

START_TEST(s21_trim_test_12) {
  const char test_str_12[50] = "";
  const char test_trim_set_12[50] = "";
  char *trim_result_12 = (char *)(s21_trim(test_str_12, test_trim_set_12));
  ck_assert_str_eq("", trim_result_12);
  if (trim_result_12) free(trim_result_12);
}
END_TEST

START_TEST(s21_to_lower_test_1) {
  const char test_str_1[64] = "123abc456xyz789";
  char *lower_result_1 = (char *)(s21_to_lower(test_str_1));
  ck_assert_str_eq("123abc456xyz789", lower_result_1);
  if (lower_result_1) free(lower_result_1);
}
END_TEST

START_TEST(s21_to_upper_test_1) {
  const char test_str_1[64] = "123abc456xyz789";
  char *upper_result_1 = (char *)(s21_to_upper(test_str_1));
  ck_assert_str_eq("123ABC456XYZ789", upper_result_1);
  if (upper_result_1) free(upper_result_1);
}
END_TEST

START_TEST(s21_to_lower_test_2) {
  const char test_str_2[64] = "*** Much Ado About Nothing ***";
  char *lower_result_2 = (char *)(s21_to_lower(test_str_2));
  ck_assert_str_eq("*** much ado about nothing ***", lower_result_2);
  if (lower_result_2) free(lower_result_2);
}
END_TEST

START_TEST(s21_to_upper_test_2) {
  const char test_str_2[64] = "*** Much Ado About Nothing ***";
  char *upper_result_2 = (char *)(s21_to_upper(test_str_2));
  ck_assert_str_eq("*** MUCH ADO ABOUT NOTHING ***", upper_result_2);
  if (upper_result_2) free(upper_result_2);
}
END_TEST

START_TEST(s21_to_lower_test_3) {
  const char test_str_3[64] = "--";
  char *lower_result_3 = (char *)(s21_to_lower(test_str_3));
  ck_assert_str_eq("--", lower_result_3);
  if (lower_result_3) free(lower_result_3);
}
END_TEST

START_TEST(s21_to_upper_test_3) {
  const char test_str_3[64] = "--";
  char *upper_result_3 = (char *)(s21_to_upper(test_str_3));
  ck_assert_str_eq("--", upper_result_3);
  if (upper_result_3) free(upper_result_3);
}
END_TEST

START_TEST(s21_to_lower_test_4) {
  const char test_str_4[64] = "";
  char *lowt_4 = (char *)(s21_to_lower(test_str_4));
  ck_assert_str_eq("", lowt_4);
  if (lowt_4) free(lowt_4);
}
END_TEST

START_TEST(s21_to_upper_test_4) {
  const char test_str_4[64] = "";
  char *upper_result_4 = (char *)(s21_to_upper(test_str_4));
  ck_assert_str_eq("", upper_result_4);
  if (upper_result_4) free(upper_result_4);
}
END_TEST

START_TEST(s21_to_lower_test_5) {
  const char test_str_5[64] = "hello world";
  char *lower_result_5 = (char *)(s21_to_lower(test_str_5));
  ck_assert_str_eq("hello world", lower_result_5);
  if (lower_result_5) free(lower_result_5);
}
END_TEST

START_TEST(s21_to_upper_test_5) {
  const char test_str_5[64] = "hello world";
  char *upper_result_5 = (char *)(s21_to_upper(test_str_5));
  ck_assert_str_eq("HELLO WORLD", upper_result_5);
  if (upper_result_5) free(upper_result_5);
}
END_TEST

START_TEST(s21_to_lower_test_6) {
  const char test_str_6[64] = "HELLO, 21SCHOOL";
  char *lower_result_6 = (char *)(s21_to_lower(test_str_6));
  ck_assert_str_eq("hello, 21school", lower_result_6);
  if (lower_result_6) free(lower_result_6);
}
END_TEST

START_TEST(s21_to_upper_test_6) {
  const char test_str_6[64] = "HELLO, 21SCHOOL";
  char *upper_result_6 = (char *)(s21_to_upper(test_str_6));
  ck_assert_str_eq("HELLO, 21SCHOOL", upper_result_6);
  if (upper_result_6) free(upper_result_6);
}
END_TEST

START_TEST(s21_to_lower_test_7) {
  const char test_str_7[64] =
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit";
  char *lower_result_7 = (char *)(s21_to_lower(test_str_7));
  ck_assert_str_eq("lorem ipsum dolor sit amet, consectetur adipiscing elit",
                   lower_result_7);
  if (lower_result_7) free(lower_result_7);
}
END_TEST

START_TEST(s21_to_upper_test_7) {
  const char test_str_7[64] =
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit";
  char *upper_result_7 = (char *)(s21_to_upper(test_str_7));
  ck_assert_str_eq("LOREM IPSUM DOLOR SIT AMET, CONSECTETUR ADIPISCING ELIT",
                   upper_result_7);
  if (upper_result_7) free(upper_result_7);
}
END_TEST

START_TEST(s21_to_lower_test_8) {
  const char test_str_8[64] = "---abc---xyz----";
  char *lower_result_8 = (char *)(s21_to_lower(test_str_8));
  ck_assert_str_eq("---abc---xyz----", lower_result_8);
  if (lower_result_8) free(lower_result_8);
}
END_TEST

START_TEST(s21_to_upper_test_8) {
  const char test_str_8[64] = "---abc---xyz----";
  char *upper_result_8 = (char *)(s21_to_upper(test_str_8));
  ck_assert_str_eq("---ABC---XYZ----", upper_result_8);
  if (upper_result_8) free(upper_result_8);
}
END_TEST

START_TEST(s21_to_lower_test_9) {
  const char test_str_9[64] = "&&&&&&&";
  char *lower_result_9 = (char *)(s21_to_lower(test_str_9));
  ck_assert_str_eq("&&&&&&&", lower_result_9);
  if (lower_result_9) free(lower_result_9);
}
END_TEST

START_TEST(s21_to_upper_test_9) {
  const char test_str_9[64] = "&&&&&&&";
  char *upper_result_9 = (char *)(s21_to_upper(test_str_9));
  ck_assert_str_eq("&&&&&&&", upper_result_9);
  if (upper_result_9) free(upper_result_9);
}
END_TEST

START_TEST(s21_insert_test_1) {
  const char test_str_1[50] = "123abc456xyz789";
  const char test_insertion_1[50] = "0";
  char *insert_result_1 = (char *)(s21_insert(test_str_1, test_insertion_1, 0));
  ck_assert_str_eq("0123abc456xyz789", insert_result_1);
  if (insert_result_1) free(insert_result_1);
}
END_TEST

START_TEST(s21_insert_test_2) {
  const char test_str_2[50] = "I Groot";
  const char test_insertion_2[50] = "am ";
  char *insert_result_2 = (char *)(s21_insert(test_str_2, test_insertion_2, 2));
  ck_assert_str_eq("I am Groot", insert_result_2);
  if (insert_result_2) free(insert_result_2);
}
END_TEST

START_TEST(s21_insert_test_3) {
  const char test_str_3[50] = "--";
  const char test_insertion_3[50] = "";
  char *insert_result_3 = (char *)(s21_insert(test_str_3, test_insertion_3, 1));
  ck_assert_str_eq("--", insert_result_3);
  if (insert_result_3) free(insert_result_3);
}
END_TEST

START_TEST(s21_insert_test_4) {
  const char test_str_4[50] = "";
  const char test_insertion_4[50] = "aboba";
  char *insert_result_4 = (char *)(s21_insert(test_str_4, test_insertion_4, 0));
  ck_assert_str_eq("aboba", insert_result_4);
  if (insert_result_4) free(insert_result_4);
}
END_TEST

START_TEST(s21_insert_test_5) {
  const char test_str_5[50] = "hello, !!!";
  const char test_insertion_5[50] = "world";
  char *insert_result_5 = (char *)(s21_insert(test_str_5, test_insertion_5, 7));
  ck_assert_str_eq("hello, world!!!", insert_result_5);
  if (insert_result_5) free(insert_result_5);
}
END_TEST

START_TEST(s21_insert_test_6) {
  const char test_str_6[50] = "HELLO, 21SCHOOL";
  const char test_insertion_6[50] = "!!!";
  char *insert_result_6 =
      (char *)(s21_insert(test_str_6, test_insertion_6, 15));
  ck_assert_str_eq("HELLO, 21SCHOOL!!!", insert_result_6);
  if (insert_result_6) free(insert_result_6);
}
END_TEST

START_TEST(s21_insert_test_7) {
  const char test_str_7[50] = "I Groot";
  const char test_insertion_7[50] = "am ";
  char *insert_result_7 =
      (char *)(s21_insert(test_str_7, test_insertion_7, 20));
  ck_assert_ptr_null(insert_result_7);
  if (insert_result_7) free(insert_result_7);
}
END_TEST

// sprintf i

START_TEST(sprintf_spec_i_1) {
  char str[50], s21_str[50];
  char *format = "|%i|";
  int num = 0b1001;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_2) {
  char str[50], s21_str[50];
  char *format = "|%-i|";
  int num = 0xFFF;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_3) {
  char str[50], s21_str[50];
  char *format = "|%10.8i|";
  int num = 013;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_4) {
  char str[50], s21_str[50];
  char *format = "|%9.4i|";
  int num = -0b1111;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_5) {
  char str[50], s21_str[50];
  char *format = "|%010i|";
  int num = 010;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_6) {
  char str[50], s21_str[50];
  char *format = "|%8i|";
  int num = -45;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_7) {
  char str[50], s21_str[50];
  char *format = "|%-6i|";
  int num = 0b1011101;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_8) {
  char str[50], s21_str[50];
  char *format = "|%1.1i|";
  int num = -0365;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_9) {
  char str[50], s21_str[50];
  char *format = "|%.3i|";
  int num = 0xAA128;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_10) {
  char str[50], s21_str[50];
  char *format = "|%-.4i|";
  int num = -45;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_11) {
  char str[50], s21_str[50];
  char *format = "|%08i|";
  int num = 0b001111;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_12) {
  char str[50], s21_str[50];
  char *format = "|%5.10i|";
  int num = 0xCABF;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_13) {
  char str[50], s21_str[50];
  char *format = "|%-7.13i|";
  int num = -586;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_14) {
  char str[50], s21_str[50];
  char *format = "|%i|";
  int num = -0b111001101;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_15) {
  char str[50], s21_str[50];
  char *format = "|%5.i|";
  int num = 78;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_16) {
  char str[50], s21_str[50];
  char *format = "|%-7.i|";
  int num = -164;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_17) {
  char str[50], s21_str[50];
  char *format = "|%.0i|";
  int num = -61;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_18) {
  char str[50], s21_str[50];
  char *format = "|%8.0i|";
  int num = 999;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_19) {
  char str[50], s21_str[50];
  char *format = "|%-7.0i|";
  int num = 546;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_20) {
  char str[50], s21_str[50];
  char *format = "|%+i|";
  int num = -1675;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_21) {
  char str[50], s21_str[50];
  char *format = "|%li|";
  long num = -156;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_22) {
  char str[50], s21_str[50];
  char *format = "|%+0li|";
  long num = -645;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_23) {
  char str[50], s21_str[50];
  char *format = "|%+3.1li|";
  long num = -17;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_24) {
  char str[50], s21_str[50];
  char *format = "|%hi|";
  short num = 678;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_25) {
  char str[50], s21_str[50];
  char *format = "|%0hi|";
  short num = -4566;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_26) {
  char str[50], s21_str[50];
  char *format = "|%-hi|";
  short num = -78;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_27) {
  char str[50], s21_str[50];
  char *format = "|%-5.1hi|";
  short num = 166;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_28) {
  char str[50], s21_str[50];
  char *format = "|%-.8hi|";
  short num = 6615;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_29) {
  char str[50], s21_str[50];
  char *format = "|%0.8hi|";
  short num = -6;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_30) {
  char str[50], s21_str[50];
  char *format = "|% i|";
  int num = -64;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_31) {
  char str[50], s21_str[50];
  char *format = "|%*i|";
  int num = 54;
  int star = 10;
  ck_assert_int_eq(sprintf(str, format, star, num),
                   s21_sprintf(s21_str, format, star, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_32) {
  char str[50], s21_str[50];
  char *format = "|%-*i|";
  int num = -465;
  int star = 7;
  ck_assert_int_eq(sprintf(str, format, star, num),
                   s21_sprintf(s21_str, format, star, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_33) {
  char str[50], s21_str[50];
  char *format = "|%0*i|";
  int num = 565;
  int star = 5;
  ck_assert_int_eq(sprintf(str, format, star, num),
                   s21_sprintf(s21_str, format, star, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_34) {
  char str[50], s21_str[50];
  char *format = "|%.*i|";
  int num = 9634;
  int star = 8;
  ck_assert_int_eq(sprintf(str, format, star, num),
                   s21_sprintf(s21_str, format, star, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_35) {
  char str[50], s21_str[50];
  char *format = "|%.*i|";
  int num = -96;
  int star = -3;
  ck_assert_int_eq(sprintf(str, format, star, num),
                   s21_sprintf(s21_str, format, star, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_36) {
  char str[50], s21_str[50];
  char *format = "|%0.*i|";
  int num = 81;
  int star = 6;
  ck_assert_int_eq(sprintf(str, format, star, num),
                   s21_sprintf(s21_str, format, star, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_37) {
  char str[50], s21_str[50];
  char *format = "|%+5.*i|";
  int num = -16;
  int star = 4;
  ck_assert_int_eq(sprintf(str, format, star, num),
                   s21_sprintf(s21_str, format, star, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_i_38) {
  char str[50], s21_str[50];
  char *format = "|%i| |%-i| |%+i| |%0i| |%5.3i| |%-3.3i|";
  int x1 = -16, x2 = 14, x3 = -10, x4 = 0, x5 = 1908, x6 = -1412;
  ck_assert_int_eq(sprintf(str, format, x1, x2, x3, x4, x5, x6),
                   s21_sprintf(s21_str, format, x1, x2, x3, x4, x5, x6));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

// sprintf u
START_TEST(sprintf_spec_u_1) {
  char str[50], s21_str[50];
  char *format = "|%u|";
  unsigned x = 100;
  ck_assert_int_eq(sprintf(str, format, x), s21_sprintf(s21_str, format, x));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_u_2) {
  char str[50], s21_str[50];
  char *format = "|%10u|";
  unsigned x = -65;
  ck_assert_int_eq(sprintf(str, format, x), s21_sprintf(s21_str, format, x));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_u_3) {
  char str[50], s21_str[50];
  char *format = "|%-8u|";
  unsigned x = 130;
  ck_assert_int_eq(sprintf(str, format, x), s21_sprintf(s21_str, format, x));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_u_4) {
  char str[50], s21_str[50];
  char *format = "|%+u|";
  unsigned x = 121;
  ck_assert_int_eq(sprintf(str, format, x), s21_sprintf(s21_str, format, x));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_u_5) {
  char str[50], s21_str[50];
  char *format = "|% u|";
  unsigned x = 77;
  ck_assert_int_eq(sprintf(str, format, x), s21_sprintf(s21_str, format, x));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_u_6) {
  char str[50], s21_str[50];
  char *format = "|%05u|";
  unsigned x = -25;
  ck_assert_int_eq(sprintf(str, format, x), s21_sprintf(s21_str, format, x));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_u_7) {
  char str[50], s21_str[50];
  char *format = "|%.5u|";
  unsigned x = 69;
  ck_assert_int_eq(sprintf(str, format, x), s21_sprintf(s21_str, format, x));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_u_8) {
  char str[50], s21_str[50];
  char *format = "|%.3u|";
  unsigned x = -1459;
  ck_assert_int_eq(sprintf(str, format, x), s21_sprintf(s21_str, format, x));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_u_9) {
  char str[50], s21_str[50];
  char *format = "|%hu|";
  unsigned short x = 55;
  ck_assert_int_eq(sprintf(str, format, x), s21_sprintf(s21_str, format, x));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_u_10) {
  char str[50], s21_str[50];
  char *format = "|%lu|";
  unsigned long x = 55;
  ck_assert_int_eq(sprintf(str, format, x), s21_sprintf(s21_str, format, x));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_u_11) {
  char str[50], s21_str[50];
  char *format = "|%5.3u|";
  unsigned x = 2165;
  ck_assert_int_eq(sprintf(str, format, x), s21_sprintf(s21_str, format, x));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_u_12) {
  char str[50], s21_str[50];
  char *format = "|%3.7u|";
  unsigned x = 17899;
  ck_assert_int_eq(sprintf(str, format, x), s21_sprintf(s21_str, format, x));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_u_13) {
  char str[50], s21_str[50];
  char *format = "|%-10.2u|";
  unsigned x = 45987;
  ck_assert_int_eq(sprintf(str, format, x), s21_sprintf(s21_str, format, x));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_u_14) {
  char str[50], s21_str[50];
  char *format = "|%*.3u|";
  unsigned x = -17;
  int star = 8;
  ck_assert_int_eq(sprintf(str, format, star, x),
                   s21_sprintf(s21_str, format, star, x));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_u_15) {
  char str[50], s21_str[50];
  char *format = "|%3.*u|";
  unsigned x = 56879;
  int star = 2;
  ck_assert_int_eq(sprintf(str, format, star, x),
                   s21_sprintf(s21_str, format, star, x));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_u_16) {
  char str[50], s21_str[50];
  char *format = "|%lu|";
  unsigned long x = -879;
  ck_assert_int_eq(sprintf(str, format, x), s21_sprintf(s21_str, format, x));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

// sprintf e

START_TEST(sprintf_spec_e_1) {
  char str[50], s21_str[50];
  char *format = "|%e|";
  float num = 10.76;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_2) {
  char str[50], s21_str[50];
  char *format = "|%7e|";
  float num = 54.898;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_3) {
  char str[50], s21_str[50];
  char *format = "|%6.3e|";
  float num = -45.648;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_4) {
  char str[50], s21_str[50];
  char *format = "|%1.7e|";
  float num = 98.534;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_5) {
  char str[50], s21_str[50];
  char *format = "|%-2.10e|";
  float num = 7.16;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_6) {
  char str[50], s21_str[50];
  char *format = "|%.10e|";
  float num = 7.62;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_7) {
  char str[50], s21_str[50];
  char *format = "|%.5e|";
  float num = -122.9;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_8) {
  char str[50], s21_str[50];
  char *format = "|% 7e|";
  float num = 256.01;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_9) {
  char str[50], s21_str[50];
  char *format = "|%+4e|";
  float num = 1.12;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_10) {
  char str[50], s21_str[50];
  char *format = "|%3e|";
  float num = 1245.001;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_11) {
  char str[50], s21_str[50];
  char *format = "|%11.11e|";
  float num = -1245.045645601;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_12) {
  char str[50], s21_str[50];
  char *format = "|%11.0e|";
  float num = 21.11;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_13) {
  char str[50], s21_str[50];
  char *format = "|%9.9e|";
  float num = 888.22;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_14) {
  char str[50], s21_str[50];
  char *format = "|%-8.8e|";
  float num = 4617.235;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_15) {
  char str[50], s21_str[50];
  char *format = "|%.0e|";
  float num = 77.99;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_16) {
  char str[50], s21_str[50];
  char *format = "|%-5.1e|";
  float num = 116.43;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_17) {
  char str[50], s21_str[50];
  char *format = "|%010e|";
  float num = -75.36;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_18) {
  char str[50], s21_str[50];
  char *format = "|%#e|";
  float num = 116.0;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_19) {
  char str[50], s21_str[50];
  char *format = "|%*e|";
  float x = 82.175;
  int star = 10;
  ck_assert_int_eq(sprintf(str, format, star, x),
                   s21_sprintf(s21_str, format, star, x));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_20) {
  char str[50], s21_str[50];
  char *format = "|%5.*e|";
  float x = -981.956;
  int star = 3;
  ck_assert_int_eq(sprintf(str, format, star, x),
                   s21_sprintf(s21_str, format, star, x));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_21) {
  char str[100], s21_str[100];
  char *format = "|%5.1e| |%3.8e| |%4e| |%-5e| |%08e| |% e|";
  float x1 = -981.05, x2 = 67.65, x3 = -56.3, x4 = 3.13, x5 = -167.01,
        x6 = 0.0001;
  ck_assert_int_eq(sprintf(str, format, x1, x2, x3, x4, x5, x6),
                   s21_sprintf(s21_str, format, x1, x2, x3, x4, x5, x6));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_22) {
  char str[50], s21_str[50];
  char *format = "|%0e|";
  float num = 0.0;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_23) {
  char str[50], s21_str[50];
  char *format = "|%-0e|";
  float num = 0.0;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_24) {
  char str[50], s21_str[50];
  char *format = "|%-0.0e|";
  float num = 0.0;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_spec_e_25) {
  char str[50], s21_str[50];
  char *format = "|%0.0e|";
  float num = 7127.9943;
  ck_assert_int_eq(sprintf(str, format, num),
                   s21_sprintf(s21_str, format, num));
  ck_assert_pstr_eq(str, s21_str);
}
END_TEST

START_TEST(ssanf_integer_format_d_1) {
  char fstr[] = "%d";
  int value1 = 0, value2 = 0;

  int res1 = s21_sscanf("12345", fstr, &value1);
  int res2 = sscanf("12345", fstr, &value2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(value1, value2);
}
END_TEST

START_TEST(ssanf_unsigned_format_u_1) {
  char fstr[] = "%u %lu %llu %hu";
  unsigned int value1_1 = 0, value1_2 = 0;
  unsigned long int value2_1 = 0, value2_2 = 0;
  unsigned long long int value3_1 = 0, value3_2 = 0;
  unsigned short int value4_1 = 0, value4_2 = 0;

  int res1 = s21_sscanf("98765 1234567890 18446744073709551615 12345", fstr,
                        &value1_1, &value2_1, &value3_1, &value4_1);
  int res2 = sscanf("98765 1234567890 18446744073709551615 12345", fstr,
                    &value1_2, &value2_2, &value3_2, &value4_2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(value1_1, value1_2);
  ck_assert_int_eq(value2_1, value2_2);
  ck_assert_int_eq(value3_1, value3_2);
  ck_assert_int_eq(value4_1, value4_2);
}
END_TEST

START_TEST(ssanf_process_long_int) {
  char fstr[] = "%ld";
  long long int value1 = 0, value2 = 0;

  int res1 = s21_sscanf("987654321", fstr, &value1);
  int res2 = sscanf("987654321", fstr, &value2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(value1, value2);
}
END_TEST

START_TEST(ssanf_process_long_long_int) {
  char fstr[] = "%lld";
  long long int value1 = 0, value2 = 0;

  int res1 = s21_sscanf("1234567890123456789", fstr, &value1);
  int res2 = sscanf("1234567890123456789", fstr, &value2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(value1, value2);
}
END_TEST

START_TEST(ssanf_floating_point_format_f_1) {
  char fstr[] = "%f %lf";
  float value1_1 = 0.0, value1_2 = 0.0;
  double value2_1 = 0.0, value2_2 = 0.0;

  int res1 =
      s21_sscanf("3.14159 12345.67890123456789", fstr, &value1_1, &value2_1);
  int res2 = sscanf("3.14159 12345.67890123456789", fstr, &value1_2, &value2_2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(value1_1, value1_2);
  ck_assert_double_eq(value2_1, value2_2);
}
END_TEST

START_TEST(ssanf_string_format_s_1) {
  char fstr[] = "%s";
  char str1[100], str2[100];

  int res1 = s21_sscanf("Hello, World!", fstr, str1);
  int res2 = sscanf("Hello, World!", fstr, str2);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ssanf_character_format_c_1) {
  char fstr[] = "%c";
  char value1 = '\0', value2 = '\0';

  int res1 = s21_sscanf("X", fstr, &value1);
  int res2 = sscanf("X", fstr, &value2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(value1, value2);
}
END_TEST

START_TEST(ssanf_skip_whitespace_1) {
  char fstr[] = "%d%d";
  int value1_1 = 0, value2_1 = 0, value1_2 = 0, value2_2 = 0;

  int res1 = s21_sscanf("   42  99", fstr, &value1_1, &value2_1);
  int res2 = sscanf("   42  99", fstr, &value1_2, &value2_2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(value1_1, value1_2);
  ck_assert_int_eq(value2_1, value2_2);
}
END_TEST

START_TEST(ssanf_set_width_1) {
  char fstr[] = "%4d";
  int value1 = 0, value2 = 0;

  int res1 = s21_sscanf("1234567", fstr, &value1);
  int res2 = sscanf("1234567", fstr, &value2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(value1, value1);
}
END_TEST

START_TEST(ssanf_assignment_suppression_1) {
  char fstr[] = "%*d%d";
  int value1_1 = 0, value2_1 = 0, value1_2 = 0, value2_2 = 0;

  int res1 = s21_sscanf("42 99", fstr, &value1_1, &value2_1);
  int res2 = sscanf("42 99", fstr, &value1_2, &value2_2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(value1_1, value1_2);
  ck_assert_int_eq(value2_1, value2_2);
}
END_TEST

START_TEST(ssanf_n1_option) {
  const char *input = "Hello, World!";
  int chars_read1 = 0, chars_read2 = 0;
  int res1 = s21_sscanf(input, "%n", &chars_read1);
  int res2 = sscanf(input, "%n", &chars_read2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(chars_read1, chars_read2);
}
END_TEST

START_TEST(ssanf_n2_option) {
  const char *input = "10 33 44 55";

  long long value1_1 = 0, value1_2 = 0, value1_3 = 0, value1_4 = 0;
  long long value2_1 = 0, value2_2 = 0, value2_3 = 0, value2_4 = 0;
  int32_t n1 = 5, n2 = 5;

  char fstr[] = "%lli %lli %n %lli %lli";

  int res1 =
      s21_sscanf(input, fstr, &value1_1, &value1_2, &n1, &value1_3, &value1_4);
  int res2 =
      sscanf(input, fstr, &value2_1, &value2_2, &n2, &value2_3, &value2_4);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(value1_1, value2_1);
  ck_assert_int_eq(value1_2, value2_2);
  ck_assert_int_eq(value1_3, value2_3);
  ck_assert_int_eq(value1_4, value2_4);
}
END_TEST

START_TEST(ssanf_invalid_input_1) {
  char fstr[] = "%d";
  int value1 = 0, value2 = 0;

  int res1 = s21_sscanf("999999999999999999", fstr, &value1);
  int res2 = sscanf("999999999999999999", fstr, &value2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(value1,
                   value2);  // value should remain unchanged due to overflow
}
END_TEST

START_TEST(ssanf_hexadecimal_input_1) {
  char fstr1[] = "%x", fstr2[] = "%x";
  unsigned int value1 = 0, value2 = 0;

  int res1 = s21_sscanf("1A", fstr1, &value1);
  int res2 = sscanf("1A", fstr1, &value2);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(fstr1, fstr2);
  ck_assert_int_eq(value1, value2);
}
END_TEST

START_TEST(ssanf_suppress_flag_1) {
  char fstr1[] = "%*d %f", fstr2[] = "%*d %f";
  float floatValue1 = 0.0, floatValue2 = 0.0;

  int res1 = s21_sscanf("42 3.14", fstr1, &floatValue1);
  int res2 = sscanf("42 3.14", fstr2, &floatValue2);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(fstr1, fstr2);
  ck_assert_float_eq(floatValue1, floatValue2);
}
END_TEST

START_TEST(ssanf_pointer_format_1) {
  char fstr1[] = "%p", fstr2[] = "%p";
  void *ptrValue1 = NULL, *ptrValue2 = NULL;

  int res1 = s21_sscanf("0x7fff5a42f9a0", fstr1, &ptrValue1);
  int res2 = sscanf("0x7fff5a42f9a0", fstr1, &ptrValue2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(ptrValue1, ptrValue2);
  ck_assert_str_eq(fstr1, fstr2);
}
END_TEST

START_TEST(ssanf_percent_literal_1) {
  char fstr1[] = "%% %d", fstr2[] = "%% %d";
  int intValue1 = 0, intValue2 = 0;

  int res1 = s21_sscanf("%% 42", fstr1, &intValue1);
  int res2 = sscanf("%% 42", fstr1, &intValue1);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(intValue1, intValue2);
  ck_assert_str_eq(fstr1, fstr2);
}
END_TEST

START_TEST(ssanf_unsigned_integer_format_1) {
  const char fstr1[] = "%u %o %x", fstr2[] = "%u %o %x";
  unsigned int uValue1 = 0, uValue2 = 0;
  unsigned int oValue1 = 0, oValue2 = 0;
  unsigned int xValue1 = 0, xValue2 = 0;

  int res1 = s21_sscanf("123 077 0x1A", fstr1, &uValue1, &oValue1, &xValue1);
  int res2 = sscanf("123 077 0x1A", fstr2, &uValue2, &oValue2, &xValue2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(uValue1, uValue2);
  ck_assert_uint_eq(oValue1, oValue2);
  ck_assert_uint_eq(xValue1, xValue2);
}
END_TEST

START_TEST(ssanf_sscanf_float_formats_1) {
  char fstr1[] = "%f %lf %Lf", fstr2[] = "%f %lf %Lf";
  float floatValue1 = 0.0f, floatValue2 = 0.0f;
  double doubleValue1 = 0.0, doubleValue2 = 0.0;
  long double longDoubleValue1 = 0.0, longDoubleValue2 = 0.0;

  int res1 = s21_sscanf("3.14 -2.71828 1.4142135623730950488", fstr1,
                        &floatValue1, &doubleValue1, &longDoubleValue1);
  int res2 = sscanf("3.14 -2.71828 1.4142135623730950488", fstr2, &floatValue2,
                    &doubleValue2, &longDoubleValue2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(floatValue1, floatValue2);
  ck_assert_double_eq(doubleValue1, doubleValue2);
  ck_assert_ldouble_eq(longDoubleValue1, longDoubleValue2);
  ck_assert_str_eq(fstr1, fstr2);
}
END_TEST

START_TEST(ssanf_non_format_1) {
  const char *input = "Hello, World! How are you?";
  char fstr[] = "Hello, %s! How are you?";
  char str1[20], str2[20];

  int res1 = s21_sscanf(input, fstr, &str1);
  int res2 = sscanf(input, fstr, &str2);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite *string_suite_create(void) {
  Suite *suite = suite_create("s21_string");
  TCase *tcase_core = tcase_create("Core");

  tcase_add_test(tcase_core, strtok_1);
  tcase_add_test(tcase_core, strtok_2);
  tcase_add_test(tcase_core, strtok_3);
  tcase_add_test(tcase_core, strtok_4);
  tcase_add_test(tcase_core, strtok_5);
  tcase_add_test(tcase_core, strtok_6);
  tcase_add_test(tcase_core, strtok_7);
  tcase_add_test(tcase_core, strncat_1);
  tcase_add_test(tcase_core, strncat_2);
  tcase_add_test(tcase_core, strncat_3);
  tcase_add_test(tcase_core, strerror_1);
  tcase_add_test(tcase_core, test_s21_memcpy);
  tcase_add_test(tcase_core, test_s21_memset);
  tcase_add_test(tcase_core, test_s21_strncpy);
  tcase_add_test(tcase_core, test_s21_strlen);
  tcase_add_test(tcase_core, test_s21_strcspn);

  // sprintf (c,s,f,o,p,n,x,X)
  tcase_add_test(tcase_core, sprintf_c_1);
  tcase_add_test(tcase_core, sprintf_c_2);
  tcase_add_test(tcase_core, sprintf_c_3);
  tcase_add_test(tcase_core, sprintf_c_4);
  tcase_add_test(tcase_core, sprintf_s_1);
  tcase_add_test(tcase_core, sprintf_s_2);
  tcase_add_test(tcase_core, sprintf_s_3);
  tcase_add_test(tcase_core, sprintf_f_1);
  tcase_add_test(tcase_core, sprintf_f_2);
  tcase_add_test(tcase_core, sprintf_f_3);
  tcase_add_test(tcase_core, sprintf_f_4);
  tcase_add_test(tcase_core, sprintf_f_5);
  tcase_add_test(tcase_core, sprintf_f_6);
  tcase_add_test(tcase_core, sprintf_n_1);
  tcase_add_test(tcase_core, sprintf_o_1);
  tcase_add_test(tcase_core, sprintf_o_2);
  tcase_add_test(tcase_core, sprintf_o_3);
  tcase_add_test(tcase_core, sprintf_x_1);
  tcase_add_test(tcase_core, sprintf_x_2);
  tcase_add_test(tcase_core, sprintf_x_3);
  tcase_add_test(tcase_core, sprintf_X_1);
  tcase_add_test(tcase_core, sprintf_X_2);
  tcase_add_test(tcase_core, sprintf_X_3);
  tcase_add_test(tcase_core, sprintf_g_1);
  tcase_add_test(tcase_core, sprintf_g_2);
  tcase_add_test(tcase_core, sprintf_p_1);
  /* SEARCH (memchr, strchr, strpbrk, strrchr, strstr) */
  tcase_add_test(tcase_core, memchr_1);
  tcase_add_test(tcase_core, memchr_2);
  tcase_add_test(tcase_core, memchr_3);
  tcase_add_test(tcase_core, memchr_4);
  tcase_add_test(tcase_core, memchr_5);
  tcase_add_test(tcase_core, memchr_6);
  tcase_add_test(tcase_core, memchr_7);
  tcase_add_test(tcase_core, memchr_8);
  tcase_add_test(tcase_core, memchr_9);
  tcase_add_test(tcase_core, memchr_10);
  tcase_add_test(tcase_core, strchr_1);
  tcase_add_test(tcase_core, strchr_2);
  tcase_add_test(tcase_core, strchr_3);
  tcase_add_test(tcase_core, strchr_4);
  tcase_add_test(tcase_core, strchr_5);
  tcase_add_test(tcase_core, strchr_6);
  tcase_add_test(tcase_core, strchr_7);
  tcase_add_test(tcase_core, strchr_8);
  tcase_add_test(tcase_core, strpbrk_1);
  tcase_add_test(tcase_core, strpbrk_2);
  tcase_add_test(tcase_core, strpbrk_3);
  tcase_add_test(tcase_core, strpbrk_4);
  tcase_add_test(tcase_core, strpbrk_5);
  tcase_add_test(tcase_core, strpbrk_6);
  tcase_add_test(tcase_core, strrchr_1);
  tcase_add_test(tcase_core, strrchr_2);
  tcase_add_test(tcase_core, strrchr_3);
  tcase_add_test(tcase_core, strrchr_4);
  tcase_add_test(tcase_core, strrchr_5);
  tcase_add_test(tcase_core, strrchr_6);
  tcase_add_test(tcase_core, strrchr_7);
  tcase_add_test(tcase_core, strrchr_8);
  tcase_add_test(tcase_core, strstr_1);
  tcase_add_test(tcase_core, strstr_2);
  tcase_add_test(tcase_core, strstr_3);
  tcase_add_test(tcase_core, strstr_4);
  tcase_add_test(tcase_core, strstr_5);
  tcase_add_test(tcase_core, strstr_6);
  tcase_add_test(tcase_core, strstr_7);
  tcase_add_test(tcase_core, strstr_8);
  tcase_add_test(tcase_core, strstr_9);
  tcase_add_test(tcase_core, strstr_10);
  tcase_add_test(tcase_core, strstr_11);
  tcase_add_test(tcase_core, strstr_12);
  tcase_add_test(tcase_core, strstr_13);

  // comparation and c sharp funtions
  tcase_add_test(tcase_core, memcmp_1);
  tcase_add_test(tcase_core, memcmp_2);
  tcase_add_test(tcase_core, memcmp_3);
  tcase_add_test(tcase_core, memcmp_4);
  tcase_add_test(tcase_core, memcmp_5);
  tcase_add_test(tcase_core, memcmp_6);
  tcase_add_test(tcase_core, memcmp_7);
  tcase_add_test(tcase_core, memcmp_9);
  tcase_add_test(tcase_core, memcmp_10);
  tcase_add_test(tcase_core, strncmp_1);
  tcase_add_test(tcase_core, strncmp_2);
  tcase_add_test(tcase_core, strncmp_3);
  tcase_add_test(tcase_core, strncmp_4);
  tcase_add_test(tcase_core, strncmp_5);
  tcase_add_test(tcase_core, strncmp_6);
  tcase_add_test(tcase_core, strncmp_7);
  tcase_add_test(tcase_core, s21_trim_test_1);
  tcase_add_test(tcase_core, s21_trim_test_2);
  tcase_add_test(tcase_core, s21_trim_test_3);
  tcase_add_test(tcase_core, s21_trim_test_4);
  tcase_add_test(tcase_core, s21_trim_test_5);
  tcase_add_test(tcase_core, s21_trim_test_6);
  tcase_add_test(tcase_core, s21_trim_test_7);
  tcase_add_test(tcase_core, s21_trim_test_8);
  tcase_add_test(tcase_core, s21_trim_test_9);
  tcase_add_test(tcase_core, s21_trim_test_10);
  tcase_add_test(tcase_core, s21_trim_test_11);
  tcase_add_test(tcase_core, s21_trim_test_12);
  tcase_add_test(tcase_core, s21_to_lower_test_1);
  tcase_add_test(tcase_core, s21_to_upper_test_1);
  tcase_add_test(tcase_core, s21_to_lower_test_2);
  tcase_add_test(tcase_core, s21_to_upper_test_2);
  tcase_add_test(tcase_core, s21_to_lower_test_3);
  tcase_add_test(tcase_core, s21_to_upper_test_3);
  tcase_add_test(tcase_core, s21_to_lower_test_4);
  tcase_add_test(tcase_core, s21_to_upper_test_4);
  tcase_add_test(tcase_core, s21_to_lower_test_5);
  tcase_add_test(tcase_core, s21_to_upper_test_5);
  tcase_add_test(tcase_core, s21_to_lower_test_6);
  tcase_add_test(tcase_core, s21_to_upper_test_6);
  tcase_add_test(tcase_core, s21_to_lower_test_7);
  tcase_add_test(tcase_core, s21_to_upper_test_7);
  tcase_add_test(tcase_core, s21_to_lower_test_8);
  tcase_add_test(tcase_core, s21_to_upper_test_8);
  tcase_add_test(tcase_core, s21_to_lower_test_9);
  tcase_add_test(tcase_core, s21_to_upper_test_9);
  tcase_add_test(tcase_core, s21_insert_test_1);
  tcase_add_test(tcase_core, s21_insert_test_2);
  tcase_add_test(tcase_core, s21_insert_test_3);
  tcase_add_test(tcase_core, s21_insert_test_4);
  tcase_add_test(tcase_core, s21_insert_test_5);
  tcase_add_test(tcase_core, s21_insert_test_6);
  tcase_add_test(tcase_core, s21_insert_test_7);

  // sprintf i
  tcase_add_test(tcase_core, sprintf_spec_i_1);
  tcase_add_test(tcase_core, sprintf_spec_i_2);
  tcase_add_test(tcase_core, sprintf_spec_i_3);
  tcase_add_test(tcase_core, sprintf_spec_i_4);
  tcase_add_test(tcase_core, sprintf_spec_i_5);
  tcase_add_test(tcase_core, sprintf_spec_i_6);
  tcase_add_test(tcase_core, sprintf_spec_i_7);
  tcase_add_test(tcase_core, sprintf_spec_i_8);
  tcase_add_test(tcase_core, sprintf_spec_i_9);
  tcase_add_test(tcase_core, sprintf_spec_i_10);
  tcase_add_test(tcase_core, sprintf_spec_i_11);
  tcase_add_test(tcase_core, sprintf_spec_i_12);
  tcase_add_test(tcase_core, sprintf_spec_i_13);
  tcase_add_test(tcase_core, sprintf_spec_i_14);
  tcase_add_test(tcase_core, sprintf_spec_i_15);
  tcase_add_test(tcase_core, sprintf_spec_i_16);
  tcase_add_test(tcase_core, sprintf_spec_i_17);
  tcase_add_test(tcase_core, sprintf_spec_i_18);
  tcase_add_test(tcase_core, sprintf_spec_i_19);
  tcase_add_test(tcase_core, sprintf_spec_i_20);
  tcase_add_test(tcase_core, sprintf_spec_i_21);
  tcase_add_test(tcase_core, sprintf_spec_i_22);
  tcase_add_test(tcase_core, sprintf_spec_i_23);
  tcase_add_test(tcase_core, sprintf_spec_i_24);
  tcase_add_test(tcase_core, sprintf_spec_i_25);
  tcase_add_test(tcase_core, sprintf_spec_i_26);
  tcase_add_test(tcase_core, sprintf_spec_i_27);
  tcase_add_test(tcase_core, sprintf_spec_i_28);
  tcase_add_test(tcase_core, sprintf_spec_i_29);
  tcase_add_test(tcase_core, sprintf_spec_i_30);
  tcase_add_test(tcase_core, sprintf_spec_i_31);
  tcase_add_test(tcase_core, sprintf_spec_i_32);
  tcase_add_test(tcase_core, sprintf_spec_i_33);
  tcase_add_test(tcase_core, sprintf_spec_i_34);
  tcase_add_test(tcase_core, sprintf_spec_i_35);
  tcase_add_test(tcase_core, sprintf_spec_i_36);
  tcase_add_test(tcase_core, sprintf_spec_i_37);
  tcase_add_test(tcase_core, sprintf_spec_i_38);

  // sprintf u

  tcase_add_test(tcase_core, sprintf_spec_u_1);
  tcase_add_test(tcase_core, sprintf_spec_u_2);
  tcase_add_test(tcase_core, sprintf_spec_u_3);
  tcase_add_test(tcase_core, sprintf_spec_u_4);
  tcase_add_test(tcase_core, sprintf_spec_u_5);
  tcase_add_test(tcase_core, sprintf_spec_u_6);
  tcase_add_test(tcase_core, sprintf_spec_u_7);
  tcase_add_test(tcase_core, sprintf_spec_u_8);
  tcase_add_test(tcase_core, sprintf_spec_u_9);
  tcase_add_test(tcase_core, sprintf_spec_u_10);
  tcase_add_test(tcase_core, sprintf_spec_u_11);
  tcase_add_test(tcase_core, sprintf_spec_u_12);
  tcase_add_test(tcase_core, sprintf_spec_u_13);
  tcase_add_test(tcase_core, sprintf_spec_u_14);
  tcase_add_test(tcase_core, sprintf_spec_u_15);
  tcase_add_test(tcase_core, sprintf_spec_u_16);

  // sprintf e
  tcase_add_test(tcase_core, sprintf_spec_e_1);
  tcase_add_test(tcase_core, sprintf_spec_e_2);
  tcase_add_test(tcase_core, sprintf_spec_e_3);
  tcase_add_test(tcase_core, sprintf_spec_e_4);
  tcase_add_test(tcase_core, sprintf_spec_e_5);
  tcase_add_test(tcase_core, sprintf_spec_e_6);
  tcase_add_test(tcase_core, sprintf_spec_e_7);
  tcase_add_test(tcase_core, sprintf_spec_e_8);
  tcase_add_test(tcase_core, sprintf_spec_e_9);
  tcase_add_test(tcase_core, sprintf_spec_e_10);
  tcase_add_test(tcase_core, sprintf_spec_e_11);
  tcase_add_test(tcase_core, sprintf_spec_e_12);
  tcase_add_test(tcase_core, sprintf_spec_e_13);
  tcase_add_test(tcase_core, sprintf_spec_e_14);
  tcase_add_test(tcase_core, sprintf_spec_e_15);
  tcase_add_test(tcase_core, sprintf_spec_e_16);
  tcase_add_test(tcase_core, sprintf_spec_e_17);
  tcase_add_test(tcase_core, sprintf_spec_e_18);
  tcase_add_test(tcase_core, sprintf_spec_e_19);
  tcase_add_test(tcase_core, sprintf_spec_e_20);
  tcase_add_test(tcase_core, sprintf_spec_e_21);
  tcase_add_test(tcase_core, sprintf_spec_e_22);
  tcase_add_test(tcase_core, sprintf_spec_e_23);
  tcase_add_test(tcase_core, sprintf_spec_e_24);
  tcase_add_test(tcase_core, sprintf_spec_e_25);

  tcase_add_test(tcase_core, ssanf_integer_format_d_1);
  tcase_add_test(tcase_core, ssanf_unsigned_format_u_1);
  tcase_add_test(tcase_core, ssanf_process_long_int);
  tcase_add_test(tcase_core, ssanf_process_long_int);
  tcase_add_test(tcase_core, ssanf_process_long_long_int);
  tcase_add_test(tcase_core, ssanf_floating_point_format_f_1);
  tcase_add_test(tcase_core, ssanf_string_format_s_1);
  tcase_add_test(tcase_core, ssanf_character_format_c_1);
  tcase_add_test(tcase_core, ssanf_skip_whitespace_1);
  tcase_add_test(tcase_core, ssanf_set_width_1);
  tcase_add_test(tcase_core, ssanf_assignment_suppression_1);
  tcase_add_test(tcase_core, ssanf_n1_option);
  tcase_add_test(tcase_core, ssanf_n2_option);
  tcase_add_test(tcase_core, ssanf_invalid_input_1);
  tcase_add_test(tcase_core, ssanf_hexadecimal_input_1);
  tcase_add_test(tcase_core, ssanf_suppress_flag_1);
  tcase_add_test(tcase_core, ssanf_pointer_format_1);
  tcase_add_test(tcase_core, ssanf_percent_literal_1);
  tcase_add_test(tcase_core, ssanf_unsigned_integer_format_1);
  tcase_add_test(tcase_core, ssanf_sscanf_float_formats_1);
  tcase_add_test(tcase_core, ssanf_non_format_1);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

int main(void) {
  int number_failed;
  Suite *suite = string_suite_create();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  // получаем количество проваленных тестов
  number_failed = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return (number_failed == 0) ? 0 : 1;
}
