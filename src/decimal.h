#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SRC_CAT__DECIMAL_H_
#define SRC_CAT__DECIMAL_H_

#define TRUE 0
#define FALSE 1

#define MAX_LEN 29u
#define POINTBITS 0x00ff0000
#define SIGNBIT 0x80000000
#define MAXVALUE 0xffffffff

typedef enum {
  _NORMAL_VALUE = 0,
  _INFINITY = 1,
  _NEGATIVE_INFINITY = 2,
  _NAN = 3
} value_type_t;

typedef struct {
  unsigned int bits[4];
  value_type_t value_type;
} _decimal;

#define DESTROY(VALUE) \
  if (VALUE) free(VALUE)

// Арифметические операторы

_decimal _add(_decimal, _decimal);
_decimal _sub(_decimal, _decimal);
_decimal _mul(_decimal, _decimal);
_decimal _div(_decimal, _decimal);
_decimal _mod(_decimal, _decimal);

// Операторы сравнение

int _is_less(_decimal, _decimal);
int _is_less_or_equal(_decimal, _decimal);
int _is_greater(_decimal, _decimal);
int _is_greater_or_equal(_decimal, _decimal);
int _is_equal(_decimal, _decimal);
int _is_not_equal(_decimal, _decimal);

// Преобразователи

int _from_int_to_decimal(int, _decimal*);
int _from_float_to_decimal(float, _decimal*);
int _from_decimal_to_int(_decimal, int*);
int _from_decimal_to_float(_decimal, float*);

// Другие функции

_decimal _floor(_decimal);
_decimal _round(_decimal);
_decimal _truncate(_decimal);
_decimal _negate(_decimal);

// utils

char* _from_decimal_to_string(_decimal);
int _shift(_decimal*, int);
_decimal _bitwise_shift(_decimal, int);
_decimal shift(_decimal, int);
int _normalize(_decimal*, _decimal*);
void _swap(_decimal*, _decimal*);
void give_num_bits(_decimal*, _decimal, _decimal*, int*);
void make_division(_decimal*, _decimal, _decimal*, _decimal*, int);
void set_fractional_part(_decimal*, _decimal, _decimal*);
void make_convert_from_float(_decimal*, const char*, int);

int _is_positive(_decimal);
int _get_bit(_decimal, int);
int give_exp(_decimal);
void _set_bit(_decimal*, int);
void _set_init_and_type(_decimal*, int);
_decimal _make_positive(_decimal);
_decimal _minus(_decimal, _decimal);
_decimal _other_type(_decimal, _decimal);
int _plus(_decimal, _decimal, _decimal*, int);
short _is_zero(_decimal);

// Отладочные

void print_dec(_decimal);

#endif  // SRC_CAT__DECIMAL_H_
