#ifndef S21_STRING_H
#define S21_STRING_H

typedef struct flags {
  int minus;
  int plus;
  int space;
  int sharp;
  int zero;
  unsigned int width;
  int precision;
  int is_precision;
  int length;
  int specifiers;
} flag;

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define s21_size_t unsigned long long
#define s21_NULL (void *)0

//-----------------------поиск / Асель---------------------------//

// Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
// байтах строки, на которую указывает аргумент str.
void *s21_memchr(const void *str, int c, size_t n);

// Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.
char *s21_strchr(const char *str, int c);

// Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.
char *s21_strrchr(const char *str, int c);

// Находит первое вхождение всей строки needle (не включая завершающий нулевой
// символ), которая появляется в строке haystack.
const char *s21_strstr(const char *haystack, const char *needle);

int compare_str(const char *haystack, const char *needle);

// Находит первый символ в строке str1, который соответствует любому символу,
// указанному в str2.
char *s21_strpbrk(const char *str1, const char *str2);

//-----------------------Сравнение / Маша---------------------------//

// Сравнивает первые n байтов str1 и str2.
int s21_memcmp(const void *str1, const void *str2, size_t n);

// Сравнивает не более первых n байтов str1 и str2.
int s21_strncmp(const char *str1, const char *str2, size_t n);
// верхний регистр
void *s21_to_upper(const char *str);
// нижний регистр
void *s21_to_lower(const char *str);
// Возвращает новую строку, в которой указанная строка вставлена в указанную
// позицию
void *s21_insert(const char *src, const char *str, size_t start_index);
// Возвращает новую строку, в которой удаляются все начальные и конечные
// вхождения
void *s21_trim(const char *src, const char *trim_chars);

//-----------------------Копирование / Олег---------------------------//

// Копирует n символов из src в dest.
void *s21_memcpy(void *dest, const void *src, size_t n);

// Копирует символ c (беззнаковый тип) в первые n символов строки, на которую
// указывает аргумент str.
void *s21_memset(void *str, int c, size_t n);

// Копирует до n символов из строки, на которую указывает src, в dest.
char *s21_strncpy(char *dest, const char *src, size_t n);

//-----------------------Вспомогательные / Вероника---------------------------//

// Разбивает строку str на ряд токенов, разделенных delim.
char *s21_strtok(char *str, const char *delim);

// Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest, длиной до n символов.
char *s21_strncat(char *dest, const char *src, size_t n);

// Выполняет поиск во внутреннем массиве номера ошибки errnum и возвращает
// указатель на строку с сообщением об ошибке. Нужно объявить макросы,
// содержащие массивы сообщений об ошибке для операционных систем mac и linux.
// Описания ошибок есть в оригинальной библиотеке. Проверка текущей ОС
// осуществляется с помощью директив.
char *s21_strerror(int errnum);

//-----------------------Вычисление / Марат---------------------------//

// Вычисляет длину строки str, не включая завершающий нулевой символ.
s21_size_t s21_strlen(const char *str);

// Вычисляет длину начального сегмента str1, который полностью состоит из
// символов, не входящих в str2.
s21_size_t s21_strcspn(const char *str1, const char *str2);

//-----------------------СПРИНТФ---------------------------//

// отправляет форматированный вывод в строку, на которую указывает str.
int s21_sprintf(char *str, const char *format, ...);

const char *flags_parser(const char *format_str, flag *flags, va_list *ptr);
const char *specifiers_parser(const char *format_str, flag *flags);
void flags_clean(flag *flags);
char *run_specifiers(char **str, flag flags, va_list *ptr, unsigned int *count);

// Oleg
void reverse(char *s);
void from_int_to_str(long int integer, char *buffer, unsigned int *count,
                     flag flags, int numlength);
const char *is_precision(const char *format_str, flag *flags, va_list *ptr);
char *int_specifier(char **str, flag flags, va_list *ptr, unsigned int *count);
char *uint_specifier(char **str, flag flags, va_list *ptr, unsigned int *count);
void precision_for_int(char *buffer, unsigned int *count, flag flags,
                       int numlength, int *i);
char *e_specifier(char **str, flag flags, unsigned int *count,
                  long double e_arg);
void minus_and_cnt_for_spec_e(int *cnt, long double *e_arg, int *znak);

// Veronika
char *char_specifier(char **str, flag flags, va_list *ptr, unsigned int *count);
char *string_specifier(char **str, flag flags, va_list *ptr,
                       unsigned int *count);
char *float_specifier(char **str, flag flags, unsigned int *count,
                      long double fl_arg);
void convertint_double_into_string(double value, char *arr, int precision,
                                   flag flags);
void flag_space_or_plus(flag flags, char **str, int true_for_space,
                        const unsigned int *str_len, unsigned int *count);
void flag_zero_width_sharp(flag flags, char **str, unsigned int str_len,
                           unsigned int *count);
const char *is_width(const char *format_str, flag *flags, va_list *ptr);
void n_specifier(va_list *ptr, const unsigned int *count);
char *o_specifier(char **str, va_list *ptr, flag flags, unsigned int *count);
char *x_specifier(char **str, va_list *ptr, flag flags, unsigned int *count);
char *p_specifier(char **str, va_list *ptr, flag flags, unsigned int *count);
char *g_specifier(char **str, va_list *ptr, flag flags, unsigned int *count);
void flag_sharp(flag flags, char **str);
int check_len(int value);

//-----------------------ССКАНФ---------------------------//

// считывает форматированный ввод из строки.
int s21_sscanf(const char *str, const char *format, ...);

//-----------------------Допы--------------------------//
// Спец функции
// Возвращает копию строки (str), преобразованной в верхний регистр. В
// случае какой-либо ошибки следует вернуть значение NULL
void *to_upper(const char *str);

// Возвращает копию строки (str), преобразованной в нижний регистр. В случае
// какой-либо ошибки следует вернуть значение NULL
void *to_lower(const char *str);

// Возвращает новую строку, в которой указанная строка (str) вставлена в
// указанную позицию (start_index) в данной строке (src). В случае какой-либо
// ошибки следует вернуть значение NULL
void *insert(const char *src, const char *str, size_t start_index);

// Возвращает новую строку, в которой удаляются все начальные и конечные
// вхождения набора заданных символов (trim_chars) из данной строки (src). В
// случае какой-либо ошибки следует вернуть значение NULL
void *trim(const char *src, const char *trim_chars);
#endif /*S21_STRING_H*/
