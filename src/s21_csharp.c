#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *result = malloc(sizeof(char) * s21_strlen(str) + 1);
  if (result == s21_NULL) return s21_NULL;
  s21_size_t i = 0;
  for (; i < s21_strlen(str); i++) {
    if (str[i] >= 65 && str[i] <= 90)
      result[i] = str[i] + 32;
    else
      result[i] = str[i];
  }
  result[i] = '\0';
  return (void *)result;
}

void *s21_to_upper(const char *str) {
  char *result = malloc(sizeof(char) * s21_strlen(str) + 1);
  if (result == s21_NULL) return s21_NULL;
  s21_size_t i = 0;
  for (; i < s21_strlen(str); i++) {
    if (str[i] >= 97 && str[i] <= 122)
      result[i] = str[i] - 32;
    else
      result[i] = str[i];
  }
  result[i] = '\0';
  return (void *)result;
}

void *s21_insert(const char *src, const char *str, size_t start_index) {
  s21_size_t src_len = 0;
  s21_size_t str_len = 0;
  char *result = s21_NULL;
  if (src != s21_NULL) {
    src_len = s21_strlen(src);
  }
  if (str != s21_NULL) {
    str_len = s21_strlen(str);
  }
  if (start_index <= src_len) {
    result = (char *)calloc(src_len + str_len + 1, sizeof(char));
    for (s21_size_t i = 0; i < start_index; i++) {
      result[i] = src[i];
    }
    for (s21_size_t i = start_index; i < start_index + str_len; i++) {
      result[i] = str[i - start_index];
    }
    for (s21_size_t i = start_index + str_len; i < src_len + str_len; i++) {
      result[i] = src[i - str_len];
    }
  }
  return (void *)result;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == NULL) {
    return NULL;
  }

  size_t src_len = s21_strlen(src);

  // Ищем количество символов, которые нужно удалить в начале строки
  size_t start_trim = 0;
  while (start_trim < src_len &&
         s21_strchr(trim_chars, src[start_trim]) != NULL) {
    start_trim++;
  }

  // Ищем количество символов, которые нужно удалить в конце строки
  size_t end_trim = 0;
  while (start_trim + end_trim < src_len &&
         s21_strchr(trim_chars, src[src_len - end_trim - 1]) != NULL) {
    end_trim++;
  }

  size_t new_str_len = src_len - start_trim - end_trim;

  char *result = (char *)malloc((new_str_len + 1) * sizeof(char));
  if (result == NULL) {
    return NULL;
  }

  // Копирование подстроки после удаления начальных и конечных символов
  for (size_t i = 0; i < new_str_len; i++) {
    result[i] = src[start_trim + i];
  }
  result[new_str_len] = '\0';

  return result;
}
