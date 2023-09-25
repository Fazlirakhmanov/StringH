#include "s21_string.h"
// Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
// байтах строки, на которую указывает аргумент str.
void *s21_memchr(const void *str, int c, size_t n) {
  int flag = 0;
  void *exit;
  const unsigned char *copy = str;
  for (size_t i = 0; i < n; i++) {
    if (*copy == c && flag == 0) {
      exit = (void *)copy;
      flag = 1;
    }
    copy++;
  }
  if (flag == 0) exit = NULL;
  return (void *)exit;
}

// Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.
char *s21_strchr(const char *str, int c) {
  while (*str != '\0') {
    if (*str == c) return (char *)str;
    str++;
  }
  if (c == '\0')
    return (char *)str;
  else
    return NULL;
}

// Находит первый символ в строке str1, который соответствует любому символу,
// указанному в str2.
char *s21_strpbrk(const char *str1, const char *str2) {
  s21_size_t len = 0;
  for (; str2[len]; len++)
    ;
  while (*str1 != '\0') {
    for (s21_size_t i = 0; i < len; i++) {
      if (*str1 == str2[i]) return (char *)str1;
    }
    str1++;
  }
  return NULL;
}

// Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.
char *s21_strrchr(const char *str, int c) {
  s21_size_t len = 0;
  for (; str[len]; len++)
    ;
  for (int i = len; i >= 0; i--) {
    if (str[i] == c) return (char *)str + i;
  }
  return NULL;
}

// Находит первое вхождение всей строки needle (не включая завершающий нулевой
// символ), которая появляется в строке haystack.

const char *s21_strstr(const char *haystack, const char *needle) {
  if (needle[0] == '\0') {
    return haystack;  // Если искомая подстрока пуста, возвращаем начало строки
  }

  while (*haystack != '\0') {
    if (*haystack == *needle && compare_str(haystack, needle)) {
      return haystack;  // Если символы совпали и подстроки совпали, возвращаем
                        // текущее местоположение
    }
    haystack++;
  }
  return NULL;  // Подстрока не найдена
}

int compare_str(const char *haystack, const char *needle) {
  while (*haystack && *needle) {
    if (*haystack != *needle) {
      return 0;
    }
    haystack++;
    needle++;
  }
  return (*needle == '\0');
}