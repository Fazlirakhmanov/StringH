#include "s21_sscanf.h"

#include "s21_string.h"

int s21_sscanf(const char *inputStr, const char *formatStr, ...) {
  int result = 0;
  Options options = {0, 0, 0, 0, 0, 0, 0, '\0'};
  char *tmpStr = malloc((s21_strlen(inputStr) + 1) * sizeof(char));
  if (!tmpStr) {
    printf("ERROR");
  } else {
    preprocessInputString(inputStr, &tmpStr, &options);
    va_list args;
    va_start(args, formatStr);
    for (; *formatStr; formatStr++) {
      if (handleOptions(&tmpStr, &options, formatStr)) continue;
      if (options.formatType) {
        if ((int)*formatStr > 47 && (int)*formatStr < 58) {
          options.width = options.width * 10 + (int)*formatStr - 48;
          continue;
        }
        result += processFormat(args, &options, &tmpStr, formatStr);
      } else {
        handleNonFormatSymbol(&tmpStr, &options, formatStr);
      }
      if (isBreak(args, &options, &tmpStr, formatStr)) {
        if (!result && options.endFlag) result = -1;
        break;
      }
    }
    free(tmpStr - options.count);
    va_end(args);
  }
  return result;
}

int processIntegerD(va_list args, Options *opt, char **src, int base) {
  int result = 0;
  char *endPtr;
  checkBuffer(src, opt);
  long int value = strtol(*src, &endPtr, base);
  if (endPtr != *src) {
    if (!opt->suppressFlag) {
      result++;
      if (opt->lengthModifier == LENGTH_SHORT)
        *(short int *)va_arg(args, void *) = (short int)value;
      else if (opt->lengthModifier == LENGTH_LONG)
        *(long int *)va_arg(args, void *) = value;
      else if (opt->lengthModifier == LENGTH_LONG_LONG)
        *(long long int *)va_arg(args, void *) = (long long int)value;
      else
        *(int *)va_arg(args, void *) = (int)value;
    }
    opt->count += endPtr - *src;
    *src = endPtr;
  } else {
    opt->errorFlag = 1;
  }
  opt->formatType = 0;
  return result;
}

void preprocessInputString(const char *inputStr, char **tmpStr,
                           Options *options) {
  *tmpStr = util_strcpy(*tmpStr, inputStr);
  handleWhitespace(tmpStr, options);
  if (!**tmpStr) options->endFlag = 1;
  *tmpStr = *tmpStr - options->count;  // Вернуть указатель на начало строки
  options->count = 0;
}

int processUnsignedU(va_list args, Options *opt, char **src, int base) {
  int result = 0;
  char *endPtr;
  checkBuffer(src, opt);
  unsigned long int value = strtoul(*src, &endPtr, base);
  if (endPtr != *src) {
    if (!opt->suppressFlag) {
      if (value || **src == '0') result++;
      if (opt->lengthModifier == LENGTH_SHORT)
        *(unsigned short *)va_arg(args, void *) = (unsigned short)value;
      else if (opt->lengthModifier == LENGTH_LONG)
        *(unsigned long *)va_arg(args, void *) = value;
      else if (opt->lengthModifier == LENGTH_LONG_LONG)
        *(unsigned long long *)va_arg(args, void *) = (unsigned long long)value;
      else
        *(unsigned *)va_arg(args, void *) = (unsigned)value;
    }
    opt->count += endPtr - *src;
    *src = endPtr;
  } else {
    opt->errorFlag = 1;
  }
  opt->formatType = 0;
  return result;
}

int processFloatingF(va_list args, Options *opt, char **src) {
  int result = 0;
  char *endPtr;
  checkBuffer(src, opt);
  long double value = strtold(*src, &endPtr);
  if (endPtr != *src) {
    if (!opt->suppressFlag) {
      result++;
      if (opt->lengthModifier == LENGTH_LONG_DOUBLE)
        *(long double *)va_arg(args, void *) = value;
      else if (opt->lengthModifier == LENGTH_LONG)
        *(double *)va_arg(args, void *) = (double)value;
      else
        *(float *)va_arg(args, void *) = (float)value;
    }
    opt->count += endPtr - *src;
    *src = endPtr;
  } else {
    opt->errorFlag = 1;
  }
  opt->formatType = 0;
  return result;
}

int processPointerP(va_list args, Options *opt, char **src) {
  int result = 0;
  char *endPtr;
  if (isxdigit(**src) ||
      ((*src)[0] == '0' && ((*src)[1] == 'x' || (*src)[1] == 'X'))) {
    checkBuffer(src, opt);
    unsigned long value = strtoul(*src, &endPtr, 16);
    if (endPtr != *src) {
      if (!opt->suppressFlag) {
        result++;
        *(void **)va_arg(args, void **) = (void *)value;
      }
      opt->count += endPtr - *src;
      *src = endPtr;
    } else {
      opt->errorFlag = 1;
    }
  } else {
    opt->errorFlag = 1;
  }
  opt->formatType = 0;
  return result;
}

int processCharC(va_list args, Options *opt, char **src) {
  int result = 0;
  if (!opt->width) opt->width = 2;
  if (!opt->suppressFlag) {
    result++;
    *(char *)va_arg(args, char *) = **src;
  }
  if (**src < 0 && opt->lengthModifier == LENGTH_LONG) {
    (*src)++;
    opt->count++;
  }
  (*src)++;
  opt->count++;
  opt->formatType = 0;
  return result;
}

int processStringS(va_list args, Options *opt, char **src) {
  int result = 0;
  char *new_str = malloc(sizeof(char));
  if (new_str) {
    handleWhitespace(src, opt);
    int i = 0;
    for (; **src && !isWhitespace(**src) && (opt->width == 0 || i < opt->width);
         i++, (*src)++) {
      new_str[i] = **src;
      new_str = realloc(new_str, (i + 2) * sizeof(char));
      if (!new_str) exit(0);
    }
    new_str[i] = '\0';
    int k = s21_strlen(new_str) + 1;
    va_list tmp_list;
    va_copy(tmp_list, args);
    for (int j = 0; j < k; j++) {
      if (!opt->suppressFlag) {
        if (!opt->lengthModifier)
          *((char *)va_arg(tmp_list, char *) + j) = new_str[j];
        if (j + 1 < k) {
          va_end(tmp_list);
          va_copy(tmp_list, args);
        }
      }
    }
    va_end(args);
    va_copy(args, tmp_list);
    free(new_str);
    if (!opt->suppressFlag) result++;
    opt->count += k - 1;
    opt->formatType = 0;
    va_end(tmp_list);
  }
  return result;
}

void handleWhitespace(char **src, Options *opt) {
  while (isWhitespace(**src)) {
    (*src)++;
    opt->count++;
  }
}

void handlePercentage(char **src, Options *opt, const char *format) {
  handleWhitespace(src, opt);
  if (*format == **src) {
    opt->count++;
    (*src)++;
  } else {
    opt->errorFlag = 1;
  }
  opt->formatType = 0;
}

int handleOptions(char **src, Options *opt, const char *format) {
  int result = 0;
  if (*format == '%' && !opt->formatType) {
    result++;
    opt->formatType = 1;
    opt->suppressFlag = 0;
    opt->lengthModifier = NONE_LENGTH;
    if (opt->bufferChar) {
      *(*src + s21_strlen(*src)) = opt->bufferChar;
      opt->bufferChar = '\0';
    }
    opt->width = 0;
  }
  return result;
}

void handleNumber(va_list args, Options *opt) {
  if (!opt->suppressFlag) {
    *(int *)va_arg(args, void *) = opt->count;
  }
  opt->formatType = 0;
}

void handleNonFormatSymbol(char **src, Options *opt, const char *format) {
  if (*format == ' ' || *format == '\t' || *format == '\n' || *format == '\r' ||
      *format == '\x0B') {
    while (*format == **src) {
      (*src)++;
      opt->count++;
    }
  } else if (**src == *format) {
    (*src)++;
    opt->count++;
  } else {
    opt->errorFlag = 1;
  }
}

int isBreak(va_list args, Options *opt, char **src, const char *format) {
  int result = 0;
  va_list backup;
  va_copy(backup, args);
  if ((!**src && !opt->bufferChar &&
       (s21_strstr(format, "%n") != s21_strchr(format, '%') ||
        !s21_strstr(format, "%n"))) ||
      !va_arg(backup, void *) || opt->errorFlag) {
    result = 1;
  }
  va_end(backup);
  return result;
}

int processFormat(va_list args, Options *opt, char **src, const char *format) {
  int result = 0;
  if (*format == 'c') {
    result += processCharC(args, opt, src);
  } else if (*format == 'd') {
    result += processIntegerD(args, opt, src, 10);
  } else if (*format == 'i') {
    result += processIntegerD(args, opt, src, 0);
  } else if (*format == 'e' || *format == 'E' || *format == 'f' ||
             *format == 'g' || *format == 'G') {
    result += processFloatingF(args, opt, src);
  } else if (*format == 'o') {
    result += processUnsignedU(args, opt, src, 8);
  } else if (*format == 's') {
    result += processStringS(args, opt, src);
  } else if (*format == 'x' || *format == 'X') {
    result += processUnsignedU(args, opt, src, 16);
  } else if (*format == 'p') {
    result += processPointerP(args, opt, src);
  } else if (*format == 'u') {
    result += processUnsignedU(args, opt, src, 10);
  } else if (*format == 'n') {
    handleNumber(args, opt);
  } else if (*format == '%') {
    handlePercentage(src, opt, format);
  } else if (*format == 'h' || *format == 'l' || *format == 'L') {
    processLength(&format, opt);
  } else if (*format == '*') {
    opt->suppressFlag = 1;
  }
  return result;
}

void processLength(const char **format, Options *opt) {
  if (**format == 'h') {
    opt->lengthModifier = LENGTH_SHORT;
  } else if (**format == 'l' && *(*format - 1) != 'l') {
    opt->lengthModifier = LENGTH_LONG;
    if (*(*format + 1) == 'l') opt->lengthModifier = LENGTH_LONG_LONG;
  } else if (**format == 'L') {
    opt->lengthModifier = LENGTH_LONG_DOUBLE;
  }
}

void checkBuffer(char **src, Options *opt) {
  handleWhitespace(src, opt);
  if (!opt->bufferChar && opt->width && opt->width < (int)s21_strlen(*src)) {
    opt->bufferChar = *(*src + opt->width);
    *(*src + opt->width) = '\0';
  }
}

bool isWhitespace(char c) {
  return (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\x0B' ||
          c == '\f');
}

char *util_strcpy(char *dest, const char *src) {
  int length = s21_strlen(src);
  if (dest != NULL && src != NULL) {
    for (int i = 0; i <= length; i++) dest[i] = src[i];
  }
  return dest;
}
