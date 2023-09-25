#include "s21_string.h"

// Вычисляет длину начального сегмента str1, который полностью состоит из
// символов, не входящих в str2.

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t length = 0;
  int isCharFound = 0;
  for (int i = 0; i < (int)s21_strlen(str1) && !isCharFound; i++) {
    for (int j = 0; j < (int)s21_strlen(str2) && !isCharFound; j++) {
      if (str1[i] == str2[j]) {
        isCharFound = 1;
      }
    }
    if (!isCharFound) length++;
  }
  return length;
}
