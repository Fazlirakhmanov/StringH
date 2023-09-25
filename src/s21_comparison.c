#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, size_t n) {
  int char_compare_status = 0;
  if (str1 && str2) {
    const unsigned char *arr_1 = (unsigned char *)str1;
    const unsigned char *arr_2 = (unsigned char *)str2;
    s21_size_t flag = 1;
    if (arr_1 == arr_2) {
      flag = 0;
    }
    while (n > 0 && flag) {
      if (*arr_1 != *arr_2) {
        char_compare_status = *arr_1 - *arr_2;
        flag = 0;
      }
      n--;
      arr_1++;
      arr_2++;
    }
  }
  return char_compare_status;
}

int s21_strncmp(const char *str1, const char *str2, size_t n) {
  s21_size_t len = 0;
  while (str1[len] && (str1[len] == str2[len]) && len < n) len++;
  int result;
  if (len == n)
    result = (int)(str1[len - 1] - str2[len - 1]);
  else
    result = (int)(str1[len] - str2[len]);
  return result;
}
