#include <string.h>

#include "s21_string.h"
/*destination – указатель на массив в который будет добавлена строка.
src – указатель на массив из которого будет скопирована строка.
n – максимальная длина добавляемой строки*/
char *s21_strncat(char *dest, const char *src, size_t n) {
  size_t j = 0;
  int i = strlen(dest);
  for (; j < n && j < strlen(src); i++, j++) {
    dest[i] = src[j];
  }
  dest[i] = '\0';
  return dest;
}