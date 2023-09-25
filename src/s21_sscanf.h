#ifndef SRC_HEADERS_S21_SSCANF_H_
#define SRC_HEADERS_S21_SSCANF_H_

#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum length_parametrs {
  NONE_LENGTH,
  LENGTH_SHORT,
  LENGTH_LONG,
  LENGTH_LONG_LONG,
  LENGTH_DOUBLE,
  LENGTH_LONG_DOUBLE
} length_parametrs;

typedef struct {
  int formatType;
  long count;
  int endFlag;
  int suppressFlag;
  int width;
  length_parametrs lengthModifier;
  int errorFlag;
  char bufferChar;
} Options;

typedef long unsigned s21_size_t;

int s21_sscanf(const char *str, const char *format, ...);
bool isWhitespace(char c);
void handleWhitespace(char **src, Options *opt);
void preprocessInputString(const char *inputStr, char **tmpStr,
                           Options *options);
int processFormat(va_list args, Options *opt, char **src, const char *format);
int processIntegerD(va_list args, Options *opt, char **src, int base);
int processUnsignedU(va_list args, Options *opt, char **src, int base);
int processFloatingF(va_list args, Options *opt, char **src);
int processPointerP(va_list args, Options *opt, char **src);
int processCharC(va_list args, Options *opt, char **src);
int processStringS(va_list args, Options *opt, char **src);
void processLength(const char **format, Options *opt);
void handlePercentage(char **src, Options *opt, const char *format);
int handleOptions(char **src, Options *opt, const char *format);
void handleNumber(va_list args, Options *opt);
void handleNonFormatSymbol(char **src, Options *opt, const char *format);
int isBreak(va_list args, Options *opt, char **src, const char *format);
void checkBuffer(char **src, Options *opt);
char *util_strcpy(char *dest, const char *src);

#endif  // SRC_HEADERS_S21_SSCANF_H_
