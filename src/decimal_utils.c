#include "decimal.h"

/** в строку
 */
char* _from_decimal_to_string(_decimal dec) {
  char* str = (char*)calloc(MAX_LEN + 3, sizeof(char));
  if (str && dec.value_type == _NORMAL_VALUE) {
    // bits[0] - 0xffffffff: 4294967295
    // каждая 1 среднего рязряда равна: 4294967296
    int const i32[MAX_LEN] = {6, 9, 2, 7, 6, 9, 4, 9, 2, 4};
    // каждая 1 старшего разряда равна: 18446744073709551616
    int const i64[MAX_LEN] = {6, 1, 6, 1, 5, 5, 9, 0, 7, 3,
                              7, 0, 4, 4, 7, 6, 4, 4, 8, 1};
    int decimal[MAX_LEN] = {0};
    unsigned long long carry = 0;
    // получаем инверсионное число без запятой и знака
    for (unsigned int i = 0; i < MAX_LEN; i++) {
      // для каждого разряда от 0 до 28 считаем значение:
      // low
      // + midl * 4294967296
      // + hight * 18446744073709551616
      // + целая часть с предыдущего разряда
      unsigned long long res =
          (dec.bits[0] % 10 + (unsigned long long)dec.bits[1] * i32[i] +
           (unsigned long long)dec.bits[2] * i64[i] + carry);
      // пишем последний знак, остаток от деления
      decimal[i] = res % 10;
      // сохраняем целую часть минус 1 разряд
      carry = res / 10;
      // уменьшаем midl на 1 разряд
      dec.bits[0] /= 10;
    }
    // получаем позицию запятой
    unsigned int exp = (dec.bits[3] & POINTBITS) >> 16;
    if (dec.bits[3] & SIGNBIT) {
      // проверяем не отрицательное ли число
      snprintf(str + strlen(str), MAX_LEN - strlen(str) + 3, "-");
    }
    int first_char = 0;
    for (unsigned int i = 1; i <= MAX_LEN; i++) {
      if (first_char) {
        // первая цифра напечатана, печатаем все остальные
        snprintf(str + strlen(str), MAX_LEN - strlen(str) + 3, "%d",
                 decimal[MAX_LEN - i]);
      } else if (exp == (MAX_LEN - i) && exp) {
        // цифра перед точкой
        first_char = 1;
        snprintf(str + strlen(str), MAX_LEN - strlen(str) + 3, "%d",
                 decimal[MAX_LEN - i]);
      } else if (decimal[MAX_LEN - i]) {
        // если есть что печатать делаем это
        first_char = 1;
        snprintf(str + strlen(str), MAX_LEN - strlen(str) + 3, "%d",
                 decimal[MAX_LEN - i]);
      }
      if ((MAX_LEN - i) == exp && exp) {
        // если дошли до положения точки, печатаем ее
        snprintf(str + strlen(str), MAX_LEN - strlen(str) + 3, ".");
      }
    }
    if (!first_char) {
      // если ниодной цифры не печаталось то число == 0
      snprintf(str + strlen(str), MAX_LEN - strlen(str) + 3, "0");
    }
  } else if (dec.value_type != _NORMAL_VALUE) {
    if (dec.value_type == _INFINITY) snprintf(str, 9, "INFINITY");
    if (dec.value_type == _NEGATIVE_INFINITY)
      snprintf(str, 18, "NEGATIVE_INFINITY");
    if (dec.value_type == _NAN) snprintf(str, 4, "NAN");
  }
  return str;
}

/** смещение
 * влево < 0
 * вправо > 0
 */
int _shift(_decimal* dec, int shift) {
  int res = 0;
  // проверяем куда смещаемся
  int negative = (shift < 0);
  if (negative) shift *= -1;
  // получаем позицию запятой
  unsigned int exp = (dec->bits[3] & POINTBITS) >> 16;
  if ((negative && (shift + exp) < 29) || (!negative && shift <= (int)exp)) {
    _decimal tmp = *dec;
    unsigned long long tran;
    unsigned int carry;
    if (negative) {
      // смещаемся влево
      for (unsigned int s = 0; (int)s < shift && !res; s++, exp++) {
        carry = 0;
        for (int i = 0; i < 3; i++) {
          tran = (unsigned long long)tmp.bits[i] * 10 + carry;
          carry = tran / 0x100000000;
          tmp.bits[i] = tran % 0x100000000;
        }
        if (carry > 0) res = 1;
      }
    } else {
      // смещаемся вправо
      for (unsigned int s = 0; (int)s < shift; s++, exp--) {
        carry = 0;
        for (int i = 2; i >= 0; i--) {
          tran = (unsigned long long)tmp.bits[i] + carry * 0x100000000;
          carry = tran % 10;
          tmp.bits[i] = tran / 10;
        }
      }
    }
    if ((negative && !res) || !negative) {
      // возвращаем запятую
      *dec = tmp;
      dec->bits[3] = (dec->bits[3] & SIGNBIT) | (exp << 16);
    }
  } else {
    res = 1;
  }
  return res;
}

/** нормализация числа
 */
int _normalize(_decimal* dec1, _decimal* dec2) {
  int res = 0;
  if (!dec1->bits[0] && !dec1->bits[1] && !dec1->bits[2]) {
    dec1->bits[3] &= ~(dec1->bits[3] & SIGNBIT);  //  -0.0 -> 0.0
  }
  if (!dec2->bits[0] && !dec2->bits[1] && !dec2->bits[2]) {
    dec2->bits[3] &= ~(dec2->bits[3] & SIGNBIT);  //  -0.0 -> 0.0
  }
  unsigned int exp1 = (dec1->bits[3] & POINTBITS) >> 16;
  unsigned int exp2 = (dec2->bits[3] & POINTBITS) >> 16;
  if (exp1 < exp2) {
    for (; exp1 != exp2 && !_shift(dec1, -1);
         exp1 = (dec1->bits[3] & POINTBITS) >> 16) {
    }
    if (exp1 != exp2) {
      for (; exp1 != exp2; exp2 = (dec2->bits[3] & POINTBITS) >> 16) {
        _shift(dec2, 1);
        res = 1;
      }
    }
  } else {
    for (; exp1 != exp2 && !_shift(dec2, -1);
         exp2 = (dec2->bits[3] & POINTBITS) >> 16) {
    }
    if (exp1 != exp2) {
      for (; exp1 != exp2; exp1 = (dec1->bits[3] & POINTBITS) >> 16) {
        _shift(dec1, 1);
        res = 1;
      }
    }
  }
  return res;
}

/** Возвращает 1, когда decimal положительный
 * 0, когда decimal отрицательный
 */
int _is_positive(_decimal dec) {
  unsigned int mask = 1u << 31;
  return !(mask & dec.bits[3]);
}

/** Возвращает значение бита по index в диапазоне от 0 до 96
 */
int _get_bit(_decimal dec, int index) {
  int res = 0;
  if (index < 96) {
    unsigned int mask = 1u << (index % 32);
    res = ((mask & dec.bits[index / 32]) > 0);
  }
  return res;
}

/** Устанавливает значение бита на 1 по index в диапазоне от 0 до 96
 */
void _set_bit(_decimal* dec, int index) {
  if (index < 96) {
    unsigned int mask = 1u << (index % 32);
    dec->bits[index / 32] |= mask;
  }
}

/** Делает переменную decimal типом INF NEG_INF или NAN
 */
void _set_init_and_type(_decimal* dec, int type) {
  dec->value_type = type;
  dec->bits[0] = 0;
  dec->bits[1] = 0;
  dec->bits[2] = 0;
  dec->bits[3] = 0;
}

_decimal _make_positive(_decimal dec) {
  _decimal result = dec;
  if (!_is_positive(dec)) result.bits[3] ^= SIGNBIT;
  return result;
}

int _plus(_decimal left, _decimal right, _decimal* result,
             int shift) {
  if (shift) {
    _set_init_and_type(result, 0);
    _shift(&left, shift);
    _shift(&right, shift);
    result->bits[3] = left.bits[3];
  }
  int in_mind = 0;
  for (int i = 0; i < 96; i++) {
    in_mind += _get_bit(left, i) + _get_bit(right, i);
    if (in_mind == 1) {
      _set_bit(result, i);
      in_mind = 0;
    } else if (in_mind == 2) {
      in_mind = 1;
    } else if (in_mind > 2) {
      _set_bit(result, i);
      in_mind = 1;
    }
  }
  return in_mind;
}

_decimal _minus(_decimal left, _decimal right) {
  _decimal result;
  _set_init_and_type(&result, 0);
  result.bits[3] = left.bits[3];
  int in_mind = 0;
  for (int i = 0; i < 96; i++) {
    in_mind += _get_bit(left, i) - _get_bit(right, i);
    if (in_mind == -2) {
      in_mind = -1;
    } else if (in_mind == -1) {
      _set_bit(&result, i);
    } else if (in_mind == 1) {
      in_mind = 0;
      _set_bit(&result, i);
    }
  }
  return result;
}

short _is_zero(_decimal dec) {
  return (dec.bits[0] == 0 && dec.bits[1] == 0 && dec.bits[2] == 0);
}

_decimal _other_type(_decimal left, _decimal right) {
  _decimal result;
  if (left.value_type == _INFINITY && right.value_type < 2) {
    _set_init_and_type(&result, _INFINITY);
  } else if (right.value_type == _INFINITY && left.value_type < 2) {
    _set_init_and_type(&result, _INFINITY);
  } else if (left.value_type == _NEGATIVE_INFINITY &&
             (right.value_type == _NEGATIVE_INFINITY ||
              right.value_type == _NORMAL_VALUE)) {
    _set_init_and_type(&result, _NEGATIVE_INFINITY);
  } else if (right.value_type == _NEGATIVE_INFINITY &&
             (left.value_type == _NEGATIVE_INFINITY ||
              left.value_type == _NORMAL_VALUE)) {
    _set_init_and_type(&result, _NEGATIVE_INFINITY);
  } else {
    _set_init_and_type(&result, _NAN);
  }
  return result;
}

_decimal _bitwise_shift(_decimal src, int i) {
  int flag = 0;
  if (i < 0) {
    flag = 1;
    i = -i;
  }
  _decimal dec = src;
  while (i > 0) {
    dec = shift(dec, flag);
    i--;
  }
  return dec;
}

_decimal shift(_decimal src, int flag) {
  _decimal dec = src;
  if (flag) {
    dec.bits[2] = dec.bits[2] << 1;
    if (dec.bits[1] >> 31 == 1) dec.bits[2] = dec.bits[2] | 1;
    dec.bits[1] = dec.bits[1] << 1;
    if (dec.bits[0] >> 31 == 1) dec.bits[1] = dec.bits[1] | 1;
    dec.bits[0] = dec.bits[0] << 1;
  } else {
    dec.bits[0] = dec.bits[0] >> 1;
    if (dec.bits[1] & 1u) dec.bits[0] = dec.bits[0] | (1u << 31);
    dec.bits[1] = dec.bits[1] >> 1;
    if (dec.bits[2] & 1u) dec.bits[1] = dec.bits[1] | (1u << 31);
    dec.bits[2] = dec.bits[2] >> 1;
  }
  return dec;
}

int give_exp(_decimal dec) {
  dec = _make_positive(dec);
  return dec.bits[3] >> 16;
}
