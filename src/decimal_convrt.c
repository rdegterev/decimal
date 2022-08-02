#include "decimal.h"
/** Из int
 * Возвращаемое значение - код ошибки:
 * 0 - SUCCESS
 * 1 - CONVERTING ERROR
 */
int _from_int_to_decimal(int src, _decimal *dst) {
  int flag = 0;
  if (dst != NULL) {
    if (src < 0) {
      dst->bits[3] = 1u << 31;
      src = -src;
    } else {
      dst->bits[3] = 0;
    }
    dst->bits[0] = src;
    dst->bits[1] = dst->bits[2] = 0;
  } else {
    flag = 1;
  }
  return flag;
}

/** Из float
 * Возвращаемое значение - код ошибки:
 * 0 - SUCCESS
 * 1 - CONVERTING ERROR
 */
int _from_float_to_decimal(float src, _decimal *dst) {
  _decimal zero = {{0, 0, 0, 0}, _NORMAL_VALUE};
  *dst = zero;
  int flag = 0;
  int sign_flag = 0;
  if (src < 0.0) {
    sign_flag++;
    src = -src;
  }
  char float_str[20];
  int error = snprintf(float_str, 15, "%.6e", src);
  if (error >= 0) {
    if (src > 79228162514264337593543950335.0 || (src > 0.0 && src < 1e-28) ||
        src != src) {
      *dst = zero;
      flag++;
    } else {
      make_convert_from_float(dst, float_str, sign_flag);
    }
  } else {
    flag = 1;
  }
  return flag;
}

void make_convert_from_float(_decimal *dst, const char *float_str,
                             int sign_flag) {
  _decimal zero = {{0, 0, 0, 0}, _NORMAL_VALUE};
  _decimal ten = {{10, 0, 0, 0}, _NORMAL_VALUE};
  int i = 2;
  dst->bits[0] = float_str[0] - '0';
  int scale = float_str[10] - '0';
  scale = (scale * 10 + (float_str[11] - '0')) * (44 - float_str[9]);
  while (i <= 29 + scale && float_str[i] != 'e') {
    _decimal tmp = zero;
    tmp.bits[0] = float_str[i] - '0';
    *dst = _mul(*dst, ten);
    *dst = _add(*dst, tmp);
    i++;
  }
  if (scale <= -23) {
    dst->bits[3] = 28 << 16;
  } else if (scale <= 0) {
    dst->bits[3] = (-scale + 6) << 16;
  } else if (scale < 7) {
    dst->bits[3] = (6 - scale) << 16;
  } else {
    while (scale - 6) {
      *dst = _mul(*dst, ten);
      scale--;
    }
  }
  if (sign_flag) dst->bits[3] = dst->bits[3] | (1u << 31);
}
/** В int
 * Возвращаемое значение - код ошибки:
 * 0 - SUCCESS
 * 1 - CONVERTING ERROR
 */
int _from_decimal_to_int(_decimal src, int *dst) {
  int flag = 0;
  _decimal int_part = _truncate(src);
  int_part = _make_positive(int_part);
  if (int_part.bits[1] == 0 && int_part.bits[2] == 0 &&
      (int_part.bits[0] < (1u << 31)) && int_part.value_type == 0) {
    memcpy(dst, &(int_part.bits[0]), 4);
    if (!_is_positive(src)) *dst = -(*dst);
  } else {
    flag++;
  }
  return flag;
}

/** В float
 * Возвращаемое значение - код ошибки:
 * 0 - SUCCESS
 * 1 - CONVERTING ERROR
 */
int _from_decimal_to_float(_decimal src, float *dst) {
  int sign_flag = 0;
  if (!_is_positive(src)) {
    sign_flag++;
    src = _make_positive(src);
  }
  int flag = 0;

  if (src.value_type == 0) {
    int i = 1;
    char *dec_str = _from_decimal_to_string(src);
    double tmp = (double)(dec_str[0] - '0');
    while (dec_str[i] != '\0') {
      if (dec_str[i] != '.') tmp = (tmp * 10.0) + (double)(dec_str[i] - '0');
      i++;
    }
    DESTROY(dec_str);
    int exp = give_exp(src);
    while (exp) {
      tmp /= 10.0;
      exp--;
    }
    *dst = (float)tmp;
    if (sign_flag) *dst = -(*dst);
  } else {
    flag = 1;
  }

  return flag;
}
