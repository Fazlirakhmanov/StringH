#include "s21_string.h"
void *s21_memcpy(void *dest, const void *src, size_t n);

void *s21_memcpy(void *dest, const void *src, size_t n) {
  // из войда в char
  char *cdest = (char *)dest;
  char *csrc = (char *)src;
  if (dest != NULL && src != NULL) {
    for (size_t i = 0; i < n; i++) {
      cdest[i] = csrc[i];
    }
  }
  return dest;
}

void *s21_memset(void *str, int c, size_t n) {
  unsigned char *cstr = (unsigned char *)str;
  if (str != NULL) {
    for (size_t i = 0; i < n; i++) {
      cstr[i] = c;
    }
  }
  return cstr;
}

char *s21_strncpy(char *dest, const char *src, size_t n) {
  if (dest != NULL && src != NULL) {
    for (size_t i = 0; i < n; i++) {
      dest[i] = src[i];
    }
  }
  return dest;
}
