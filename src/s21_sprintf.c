
#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  flag flags = {0};
  flags.precision = -1;
  unsigned int cnt_sym = 0;
  va_list unknown_arg;
  va_start(unknown_arg, format);

  while (format != s21_NULL && *format != '\0') {
    if (format != s21_NULL && *format != '%') {
      *str = *format;
      str++;
      format++;
      cnt_sym++;
    } else {
      //*str = '\0';
      format++;
      // printf("format after = %c\n", *format);
      format = flags_parser(format, &flags, &unknown_arg);
      format = specifiers_parser(format, &flags);
      if (format) {
        str = run_specifiers(&str, flags, &unknown_arg, &cnt_sym);
      }
    }
    flags_clean(&flags);
  }
  va_end(unknown_arg);
  *str = '\0';

  return cnt_sym;
}

const char *flags_parser(const char *format_str, flag *flags, va_list *ptr) {
  while (*format_str == '-' || *format_str == '+' || *format_str == ' ' ||
         *format_str == '0' || *format_str == '#') {
    switch (*format_str) {
      case '-':
        flags->minus = 1;
        break;
      case '+':
        flags->plus = 1;
        break;
      case '0':
        flags->zero = 1;
        break;
      case '#':
        flags->sharp = 1;
        break;
      default:
        flags->space = 1;
        break;
    }
    format_str++;
  }
  // ширина
  // если чар лежит между 1 и 9 - то это ширина
  if ((*format_str >= '1' && *format_str <= '9') || *format_str == '*') {
    format_str = is_width(format_str, flags, ptr);
  }

  // точность
  if (*format_str == '.') {
    format_str = is_precision(format_str, flags, ptr);
  }

  // длина
  if (*format_str == 'h' || *format_str == 'l' || *format_str == 'L') {
    flags->length = *format_str;
    format_str++;
  }
  return format_str;
}

const char *specifiers_parser(const char *format_str, flag *flags) {
  if (isalpha(*format_str)) {
    int find_spec = 0;
    char spec[BUFSIZ] = {'c', 'd', 'f', 's', 'u', 'i', 'n', 'o',
                         'x', 'X', 'p', 'e', 'E', 'g', 'G', '\0'};
    for (unsigned int i = 0; i < s21_strlen(spec); i++) {
      if (*format_str == spec[i]) {
        flags->specifiers = *format_str;
        // printf("flags->specifiers %c\n", flags->specifiers);
        format_str++;
        find_spec++;
      }
    }
    if (find_spec == 0) format_str = NULL;
  }

  return format_str;
}

char *run_specifiers(char **str, flag flags, va_list *ptr,
                     unsigned int *count) {
  if (flags.specifiers) {
    if (flags.specifiers == 'c') *str = char_specifier(str, flags, ptr, count);
    if (flags.specifiers == 's')
      *str = string_specifier(str, flags, ptr, count);
    if (flags.specifiers == 'f') {
      long double fl_arg = 0;
      if (flags.length == 'L')
        fl_arg = va_arg(*ptr, long double);
      else
        fl_arg = va_arg(*ptr, double);
      *str = float_specifier(str, flags, count, fl_arg);
    }
    if (flags.specifiers == 'u') {
      *str = uint_specifier(str, flags, ptr, count);
    }
    if (flags.specifiers == 'i' || flags.specifiers == 'd') {
      *str = int_specifier(str, flags, ptr, count);
    }
    if (flags.specifiers == 'n') {
      n_specifier(ptr, count);
    }
    if (flags.specifiers == 'o') {
      *str = o_specifier(str, ptr, flags, count);
    }
    if (flags.specifiers == 'x' || flags.specifiers == 'X') {
      *str = x_specifier(str, ptr, flags, count);
    }
    if (flags.specifiers == 'p') {
      *str = p_specifier(str, ptr, flags, count);
    }
    if (flags.specifiers == 'e' || flags.specifiers == 'E') {
      long double e_arg = 0;
      if (flags.length == 'L')
        e_arg = va_arg(*ptr, long double);
      else
        e_arg = va_arg(*ptr, double);
      *str = e_specifier(str, flags, count, e_arg);
    }
    // можно вынести в отдельную функцию
    if (flags.specifiers == 'g' || flags.specifiers == 'G') {
      long double fl_arg = 0;
      if (flags.length == 'L')
        fl_arg = va_arg(*ptr, long double);
      else
        fl_arg = va_arg(*ptr, double);
      if (fl_arg <= pow(10, 5) && fl_arg > pow(10, -5)) {
        *str = float_specifier(str, flags, count, fl_arg);
      } else {
        *str = e_specifier(str, flags, count, fl_arg);
      }
    }
  }
  return *str;
}

// спецификаторы
char *char_specifier(char **str, flag flags, va_list *ptr,
                     unsigned int *count) {
  // нельзя передать char, va_arg по умолчанию
  // увеличивает до int
  wchar_t symbol = va_arg(*ptr, wchar_t);
  // wchar_t - тип данных для представления широких символов
  if (flags.length !=
      'l')  // если флаг длины l выключен, то символ имеет обычный чар размер
  {
    symbol = (char)symbol;
  }
  //  добавить условие >127
  if (flags.minus == 0) {
    flag_zero_width_sharp(flags, str, 1, count);
    *(*str) = symbol;
    (*str)++;
    (**str) = '\0';
    (*count)++;
  } else {
    *(*str) = symbol;
    (*str)++;
    (**str) = '\0';
    (*count)++;
    flag_zero_width_sharp(flags, str, 1, count);
  }

  return *str;
}

char *string_specifier(char **str, flag flags, va_list *ptr,
                       unsigned int *count) {
  char *str_ptr = va_arg(*ptr, char *);
  int str_len = s21_strlen(str_ptr);
  int i = 0;
  char A[BUFSIZ] = {0};
  int diff = str_len - flags.precision;
  if (diff == str_len) {
    diff = 0;
  }
  if (diff < str_len) {
    for (; i < str_len - diff; i++) {
      A[i] = str_ptr[i];
    }
  } else {
    for (; i < str_len; i++) {
      A[i] = str_ptr[i];
    }
  }
  str_len = s21_strlen(A);
  if (flags.minus == 0) {
    flag_zero_width_sharp(flags, str, str_len, count);
    s21_strncpy(*str, A, str_len);
    *str += str_len;
    *count += str_len;
  } else {
    s21_strncpy(*str, A, str_len);
    *str += str_len;
    *count += str_len;
    flag_zero_width_sharp(flags, str, str_len, count);
  }
  return *str;
}

// по умолчанию выводит дробное число с точностью до 6 знаков включительно
char *float_specifier(char **str, flag flags, unsigned int *count,
                      long double fl_arg) {
  int precision = 6;
  char *arr = calloc(BUFSIZ, sizeof(char));
  // если указана точность, то меняем, нет - по умолчанию 6
  if (flags.is_precision) {
    precision = flags.precision;
  }
  convertint_double_into_string(fl_arg, arr, precision, flags);
  unsigned int str_len = s21_strlen(arr);
  // финишная прямая, проверяем все для записи в str
  if (flags.minus == 0) {
    flag_space_or_plus(flags, str, fl_arg > 0, &str_len, count);
    flag_zero_width_sharp(flags, str, str_len, count);
    s21_strncpy(*str, arr, str_len);
    *str += str_len;
    *count += str_len;
  } else {
    flag_space_or_plus(flags, str, fl_arg > 0, &str_len, count);
    s21_strncpy(*str, arr, str_len);
    *str += str_len;
    *count += str_len;
    flag_zero_width_sharp(flags, str, str_len, count);
  }
  free(arr);
  return *str;
}

void convertint_double_into_string(double value, char *arr, int precision,
                                   flag flags) {
  // округляем, учитывая точность
  long double new_value = value * pow(10, precision);
  new_value = round(new_value);
  new_value /= pow(10, precision);
  // находим целую и дробную части
  long long int whole_part = llabs((long long int)new_value);
  long double tail = fabsl(new_value - whole_part);
  // запись целой части
  int ptr = 0;
  if (llabs(whole_part) > 0) {
    for (; whole_part != 0; ptr++, whole_part /= 10) {
      arr[ptr] = whole_part % 10 + 48;
    }
  } else {
    arr[ptr++] = '0';
  }
  // ставим знак в конце. чтобы после реверса все ставло на свои места
  if (new_value < 0) {
    arr[ptr++] = '-';
  }
  reverse(arr);
  if (flags.specifiers == 'g' || flags.specifiers == 'G') {
    if (tail > 0) arr[ptr++] = '.';
    // printf("here2\n");
  } else if (flags.sharp || precision > 0) {
    arr[ptr++] = '.';
    // printf("here\n");
  }
  long long int whole_tail = round(tail * pow(10, precision));
  int tmp_tail = whole_tail;
  int tail_len = check_len(tmp_tail);
  // запись хвоста в string
  if (flags.specifiers != 'g' && flags.specifiers != 'G') {
    for (int i = precision - 1; i >= 0; ptr++, i--) {
      arr[ptr] = (whole_tail / (long long int)pow(10, i)) % 10 + 48;
    }
  } else {
    for (int i = tail_len; i > 0; ptr++, i--) {
      arr[ptr] = (whole_tail / (long long int)pow(10, i)) % 10 + 48;
    }
  }
  arr[ptr] = '\0';
}

char *int_specifier(char **str, flag flags, va_list *ptr, unsigned int *count) {
  long int res = 0, d_len = 0;

  // получение аргумента
  res = va_arg(*ptr, long int);

  // длина
  if (flags.length == 'h')
    res = (short)res;
  else if (flags.length == 0)
    res = (int)res;
  // получаем длину int
  long int res_tmp = res;
  while (res_tmp != 0) {
    res_tmp /= 10;
    d_len++;
  }

  char *cres = calloc(BUFSIZ, sizeof(char));

  from_int_to_str(res, cres, count, flags, d_len);

  int length_cres = s21_strlen(cres);

  if (flags.minus == 0) {
    flag_zero_width_sharp(flags, str, length_cres, count);
    s21_strncpy(*str, cres, length_cres);
    *str += length_cres;
  } else {
    s21_strncpy(*str, cres, length_cres);
    *str += length_cres;
    flag_zero_width_sharp(flags, str, length_cres, count);
  }
  free(cres);
  return *str;
}

char *uint_specifier(char **str, flag flags, va_list *ptr,
                     unsigned int *count) {
  long unsigned int unres = 0;
  long int d_len = 0;
  // получение аргумента

  unres = va_arg(*ptr, long unsigned int);
  // длина
  if (flags.length == 'h')
    unres = (unsigned short)unres;

  else if (flags.length == 0)
    unres = (unsigned int)unres;

  // длина числа

  long unsigned int unres_tmp = unres;
  while (unres_tmp != 0) {
    unres_tmp /= 10;
    d_len++;
  }

  char *cres = calloc(BUFSIZ, sizeof(char));

  from_int_to_str(unres, cres, count, flags, d_len);

  int length_cres = s21_strlen(cres);

  if (flags.minus == 0) {
    flag_zero_width_sharp(flags, str, length_cres, count);
    s21_strncpy(*str, cres, length_cres);
    *str += length_cres;
  } else {
    s21_strncpy(*str, cres, length_cres);
    *str += length_cres;
    flag_zero_width_sharp(flags, str, length_cres, count);
  }
  free(cres);
  return *str;
}

void from_int_to_str(long int integer, char *buffer, unsigned int *count,
                     flag flags, int numlength) {
  if (integer == 0 && flags.specifiers != 'u') {
    // если аргумент = 0
    buffer[0] = '0';
    (*count)++;
  } else {
    int negative = 0;
    int i = 0;
    if (flags.specifiers == 'i' || flags.specifiers == 'd' ||
        flags.specifiers == 'e' || flags.specifiers == 'E') {
      long int value_int = integer;
      // минус
      if (value_int < 0) {
        value_int *= -1;
        (*count)++;
        negative++;
      }
      while (value_int) {
        int remainder = value_int % 10;  // Вычисляем остаток от деления на 10
        buffer[i++] = 48 + remainder;  // Добавляем цифру от '0' до '9'
        value_int /= 10;               // Делаем деление на 10
        (*count)++;
      }
    } else if (flags.specifiers == 'u') {
      long unsigned int value_uint = integer;
      while (value_uint) {
        int remainder = value_uint % 10;  // Вычисляем остаток от деления на 10
        buffer[i++] = 48 + remainder;  // Добавляем цифру от '0' до '9'
        value_uint /= 10;              // Делаем деление на 10
        (*count)++;
      }
    }
    // точность
    precision_for_int(buffer, count, flags, numlength, &i);
    if (negative) buffer[i] = '-';
    reverse(buffer);
  }
}

void precision_for_int(char *buffer, unsigned int *count, flag flags,
                       int numlength, int *i) {
  if (flags.precision > 0) {
    while (numlength < flags.precision) {
      buffer[numlength] = '0';
      numlength++;
      (*count)++;
      (*i)++;
    }
  }
}

// флаги с шириной и точностью

void flag_zero_width_sharp(flag flags, char **str, unsigned int str_len,
                           unsigned int *count) {
  if (flags.plus || flags.space) {
    str_len++;
  }
  if (str_len < flags.width && (flags.sharp == 0 || flags.minus)) {
    for (int i = flags.width - str_len; i > 0; i--) {
      if (flags.zero == 0 ||
          ((flags.specifiers == 'c' || flags.specifiers == 's') &&
           flags.minus == 1) ||
          ((flags.specifiers == 'd' || flags.specifiers == 'u'))) {
        (**str) = ' ';
      } else {
        (**str) = '0';
      }
      (*str)++;
      (*count)++;
    }
  } else if (str_len < flags.width && flags.sharp == 1 && flags.minus == 0 &&
             (flags.specifiers == 'x' || flags.specifiers == 'X')) {
    str_len += 2;
    if (flags.zero == 0 || flags.precision) {
      for (int i = flags.width - str_len; i > 0; i--) {
        (**str) = ' ';
        (*str)++;
        (*count)++;
      }
      flag_sharp(flags, str);
      (*count) += 2;
    } else if (flags.zero == 1) {
      flag_sharp(flags, str);
      (*count) += 2;
      for (int i = flags.width - str_len; i > 0; i--) {
        (**str) = '0';
        (*str)++;
        (*count)++;
      }
    }
  } else if (str_len > flags.width && flags.minus == 0 &&
             (flags.specifiers == 'x' || flags.specifiers == 'X')) {
    flag_sharp(flags, str);
  }
}

void flag_space_or_plus(flag flags, char **str, int true_for_space,
                        const unsigned int *str_len, unsigned int *count) {
  if (*str_len >= flags.width) {
    if (flags.plus) {
      if (true_for_space) {
        (**str) = '+';
        (*str)++;
        (*count)++;
      }
    } else if (flags.space) {
      if (true_for_space) {
        (**str) = ' ';
        (*str)++;
        (*count)++;
      }
    }
  } else {
    if (flags.plus) {
      if (true_for_space) {
        (**str) = '+';
        (*str)++;
        (*count)++;
      }
    }
    if (flags.space) {
      if (true_for_space) {
        (**str) = ' ';
        (*str)++;
        (*count)++;
      }
    }
  }
}

const char *is_precision(const char *format_str, flag *flags, va_list *ptr) {
  flags->is_precision = 1;
  format_str++;
  if (*format_str == '*') {
    flags->precision = va_arg(*ptr, int);
    format_str++;
  } else if (*format_str >= '0' && *format_str <= '9') {
    flags->precision = atoi(format_str);
    // если точность больше 9, передвигаем указатель format на спецификатор
    int prec = flags->precision;
    if (prec == 0) format_str++;
    while (prec != 0) {
      format_str++;
      prec /= 10;
    }
  } else {
    flags->precision = 0;
  }
  return format_str;
}

const char *is_width(const char *format_str, flag *flags, va_list *ptr) {
  if (*format_str == '*') {
    flags->width = va_arg(*ptr, int);
    format_str++;
  } else {
    flags->width = atoi(format_str);
    int width = flags->width;
    while (width != 0) {
      format_str++;
      width /= 10;
    }
  }
  return format_str;
}

// дополнительные функции

void reverse(char *s) {
  int length = s21_strlen(s);
  int i, j;
  for (i = 0, j = length - 1; i < j; i++, j--) {
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
  }
}

void flags_clean(flag *flags) {
  flags->width = 0;
  flags->minus = 0;
  flags->plus = 0;
  flags->precision = -1;
  flags->is_precision = 0;
  flags->space = 0;
  flags->specifiers = 0;
  flags->zero = 0;
}

// дополнительные спецификаторы по заданию

void n_specifier(va_list *ptr, const unsigned int *count) {
  int *res = NULL;
  res = va_arg(*ptr, int *);
  if (res) {
    (*res) = *count;
  }
}

char *o_specifier(char **str, va_list *ptr, flag flags, unsigned int *count) {
  unsigned int dec_num = va_arg(*ptr, unsigned int);
  char *octal_num = calloc(BUFSIZ, sizeof(char));
  int ptr_arr = 0;
  if (dec_num > 0) {
    int len_dec = 0;
    unsigned int dec_num_tmp = dec_num;
    // поиск длины числа
    while (dec_num_tmp != 0) {
      dec_num_tmp /= 10;
      len_dec++;
    }
    // флаг #
    if (flags.sharp) {
      octal_num[len_dec] = '0';
      len_dec += 1;
    }
    // точность
    while (len_dec < flags.precision) {
      octal_num[len_dec] = '0';
      len_dec++;
    }
    // запись в стрингу
    for (ptr_arr = 0; dec_num != 0; ptr_arr++, dec_num /= 8) {
      octal_num[ptr_arr] = (dec_num % 8) + 48;
    }
  } else {
    octal_num[ptr_arr] = '0';
  }
  reverse(octal_num);
  //  запись в стрингу учитывая ширину 0 и минус
  unsigned int str_len = s21_strlen(octal_num);

  if (flags.minus == 0) {
    if (str_len < flags.width) {
      for (int i = flags.width - str_len; i > 0; i--) {
        if (flags.zero == 0) {
          (**str) = ' ';
        } else {
          (**str) = '0';
        }
        (*str)++;
        (*count)++;
      }
      s21_strncpy(*str, octal_num, str_len);
      *str += str_len;
      *count += str_len;
    }
  } else {
    s21_strncpy(*str, octal_num, str_len);
    *str += str_len;
    *count += str_len;
    if (str_len < flags.width) {
      for (int i = flags.width - str_len; i > 0; i--) {
        if (flags.zero == 0) {
          (**str) = ' ';
        } else {
          (**str) = '0';
        }
        (*str)++;
        (*count)++;
      }
    }
  }
  free(octal_num);
  return *str;
}

char *x_specifier(char **str, va_list *ptr, flag flags, unsigned int *count) {
  unsigned int dec_num = va_arg(*ptr, unsigned int), ptr_arr = 0;
  char *hex_num = calloc(BUFSIZ, sizeof(char));
  int len_dec = 0;
  unsigned int dec_num_tmp = dec_num;
  if (dec_num > 0) {
    // запись числа
    for (ptr_arr = 0; dec_num != 0; ptr_arr++, dec_num /= 16) {
      if (dec_num % 16 >= 10 && flags.specifiers == 'x')
        hex_num[ptr_arr] = (dec_num % 16) + 87;
      else if ((dec_num % 16) < 10)
        hex_num[ptr_arr] = (dec_num % 16) + 48;
      else if (flags.specifiers == 'X')
        hex_num[ptr_arr] = (dec_num % 16) + 55;
    }

  } else {
    hex_num[ptr_arr] = '0';
  }
  // поиск длины числа
  while (dec_num_tmp != 0) {
    dec_num_tmp /= 16;
    len_dec++;
  }
  // точность
  while (len_dec < flags.precision) {
    hex_num[len_dec] = '0';
    len_dec++;
  }
  reverse(hex_num);
  unsigned int str_len = s21_strlen(hex_num);
  if (flags.minus == 0) {
    flag_zero_width_sharp(flags, str, str_len, count);
    s21_strncpy(*str, hex_num, str_len);
    *str += str_len;
    *count += str_len;
  } else {
    flag_sharp(flags, str);
    s21_strncpy(*str, hex_num, str_len);
    *str += str_len;
    if (flags.sharp) str_len += 2;
    *count += str_len;
    flag_zero_width_sharp(flags, str, str_len, count);
  }
  free(hex_num);
  return *str;
}
char *p_specifier(char **str, va_list *ptr, flag flags, unsigned int *count) {
  unsigned long long res = (unsigned long long)va_arg(*ptr, void *);
  char *ptr_string = calloc(BUFSIZ, sizeof(char));
  int point = 0;
  // запись числа через перевод из десятичной в шестнадцатиричную
  for (; res != 0; point++, res /= 16) {
    if ((res % 16) < 10)
      ptr_string[point] = (res % 16) + 48;
    else {
      ptr_string[point] = (res % 16) + 87;
    }
  }
  ptr_string[point] = 'x';
  ptr_string[point + 1] = '0';
  reverse(ptr_string);
  unsigned int str_len = s21_strlen(ptr_string);
  if (flags.minus == 0) {
    flag_zero_width_sharp(flags, str, str_len, count);
    s21_strncpy(*str, ptr_string, str_len);
    *str += str_len;
    *count += str_len;
  } else {
    s21_strncpy(*str, ptr_string, str_len);
    *str += str_len;
    *count += str_len;
    flag_zero_width_sharp(flags, str, str_len, count);
  }
  free(ptr_string);
  return *str;
}

char *e_specifier(char **str, flag flags, unsigned int *count,
                  long double e_arg) {
  int precision = 6;
  int znak = '+';
  // long double e_arg = 0;
  // if (flags.length == 'L')
  //   e_arg = va_arg(*ptr, long double);
  // else
  //   e_arg = va_arg(*ptr, double);
  char *arr = calloc(BUFSIZ, sizeof(char));
  if (flags.is_precision) {
    precision = flags.precision;
  }
  int cnt = 0;
  minus_and_cnt_for_spec_e(&cnt, &e_arg, &znak);

  convertint_double_into_string(e_arg, arr, precision, flags);
  unsigned int str_len = s21_strlen(arr);
  if (flags.specifiers == 'e' || flags.specifiers == 'g')
    arr[str_len] = 'e';
  else
    arr[str_len] = 'E';
  arr[str_len + 1] = znak;
  if (cnt <= 9) arr[str_len + 2] = '0';
  str_len = s21_strlen(arr);
  unsigned int i = 0;  // костыль
  char *cnt_str = calloc(BUFSIZ, sizeof(char));
  from_int_to_str(cnt, cnt_str, &i, flags, str_len);
  s21_strncat(arr, cnt_str, str_len);

  str_len = s21_strlen(arr);
  // возможно поменять на новый хваост Вероники в double
  if (flags.minus == 0) {
    flag_space_or_plus(flags, str, e_arg > 0, &str_len, count);
    flag_zero_width_sharp(flags, str, str_len, count);
    s21_strncpy(*str, arr, str_len);
    *str += str_len;
    *count += str_len;
  } else {
    flag_space_or_plus(flags, str, e_arg > 0, &str_len, count);
    s21_strncpy(*str, arr, str_len);
    *str += str_len;
    *count += str_len;
    flag_zero_width_sharp(flags, str, str_len, count);
  }
  free(arr);
  return *str;
}

void minus_and_cnt_for_spec_e(int *cnt, long double *e_arg, int *znak) {
  int minus = 0;
  if (*e_arg < 0) {
    *e_arg *= -1;
    minus = 1;
  }
  if ((long int)*e_arg >= 1) {
    while ((long int)*e_arg > 9) {
      *e_arg /= 10;
      (*cnt)++;
    }
  } else if (*e_arg < 1 && *e_arg > 0) {
    *znak = '-';
    while (*e_arg < 0.999999) {
      *e_arg *= 10;
      (*cnt)++;
    }
  }
  if (minus) *e_arg *= -1;
}

void flag_sharp(flag flags, char **str) {
  if (flags.sharp && (flags.specifiers == 'x' || flags.specifiers == 'X')) {
    (**str) = '0';
    (*str)++;
    if (flags.specifiers != 'X') {
      (**str) = 'x';
    } else {
      (**str) = 'X';
    }
    (*str)++;
  }
}

int check_len(int value) {
  long int result = 0;
  while (value != 0) {
    long int tmp = value % 10;
    result = result * 10 + tmp;
    value = value / 10;
  }
  int len_tail = 0;
  while (result != 0) {
    result /= 10;
    len_tail++;
  }
  return len_tail;
}
