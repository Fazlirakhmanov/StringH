#include <string.h>

#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  char *res = s21_NULL;
  if (!str || !delim) {
    str = s21_NULL;
  } else {
    res = str;
    while (*res && strchr(delim, *res)) {
      *res = '\0';
      res++;
    }
    //   если после первого шага строка рес не пуста и не 0
    if (strlen(res) > 0) {
      str = res;
      while (*res && !strchr(delim, *res)) {
        res++;
      }
      while (*res && strchr(delim, *res)) {
        *res = '\0';
        res++;
      }
    } else {
      str = s21_NULL;
    }
  }
  return str;
}
