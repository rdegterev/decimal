#include "decimal.h"

/** Сложение
 * При ошибке во время операции в переменную value_type записывается тип ошибки
 */
_decimal _add(_decimal dec1, _decimal dec2) {
  //
  _decimal result = {{0x0, 0x0, 0x0, 0x0}, _NORMAL_VALUE};
  if (dec1.value_type == _NORMAL_VALUE &&
      dec2.value_type == _NORMAL_VALUE) {
    if (_is_positive(dec1) && _is_positive(dec2)) {
      _decimal left = dec1;
      _decimal right = dec2;
      _normalize(&left, &right);
      int in_mind = 0;
      result.bits[3] = left.bits[3];
      in_mind = _plus(left, right, &result, 0);

      if (in_mind != 0) {
        if (give_exp(result) > 0) {
          _plus(left, right, &result, in_mind);
        } else {
          _set_init_and_type(&result, _INFINITY);
        }
      }
    } else {
      if (!_is_positive(dec1)) {
        dec1.bits[3] ^= SIGNBIT;
        result = _sub(dec2, dec1);
      } else {
        dec2.bits[3] ^= SIGNBIT;
        result = _sub(dec1, dec2);
      }
    }
  } else {
    result = _other_type(dec1, dec2);
  }
  return result;
}

/** Вычитание
 * При ошибке во время операции в переменную value_type записывается тип ошибки
 */
_decimal _sub(_decimal dec1, _decimal dec2) {
  _decimal result = {{0x0, 0x0, 0x0, 0x0}, _NORMAL_VALUE};
  _decimal left, right;
  if (dec1.value_type == _NORMAL_VALUE &&
      dec2.value_type == _NORMAL_VALUE) {
    if (_is_positive(dec1) == _is_positive(dec2)) {
      if (!_is_positive(dec1)) {
        left = dec2;
        right = dec1;
        left.bits[3] ^= SIGNBIT;
        right.bits[3] ^= SIGNBIT;
      } else {
        left = dec1;
        right = dec2;
      }
      _normalize(&left, &right);
      if (!_is_greater(left, right)) {
        result = _minus(left, right);
      } else if (!_is_equal(dec1, dec2)) {
        _set_init_and_type(&result, 0);
      } else {
        result = _minus(right, left);
        result.bits[3] ^= SIGNBIT;
      }
    } else {
      left = _make_positive(dec1);
      right = _make_positive(dec2);
      result = _add(left, right);
      if (_is_positive(dec2)) {
        if (result.value_type == _INFINITY) {
          result.value_type = _NEGATIVE_INFINITY;
        } else {
          result.bits[3] ^= SIGNBIT;
        }
      }
    }
  } else {
    result = _other_type(dec1, dec2);
  }
  return result;
}

/** Умножение
 * При ошибке во время операции в переменную value_type записывается тип
 * ошибки
 */
_decimal _mul(_decimal dec1, _decimal dec2) {
  _decimal zero = {{0x0, 0x0, 0x0, 0x0}, _NORMAL_VALUE};
  _decimal ans = zero;

  int sign_flag = (_is_positive(dec1) ^ _is_positive(dec2));

  _decimal tmp1 = dec1;
  _decimal tmp2 = dec2;
  tmp1.bits[3] = tmp2.bits[3] = 0;

  while (_is_equal(tmp2, zero)) {
    if (tmp2.bits[0] & 1u) {
      ans = _add(ans, tmp1);
    }
    tmp1 = shift(tmp1, 1);
    tmp2 = shift(tmp2, 0);
  }

  int exp = give_exp(dec1) + give_exp(dec2);
  if (exp > 28) {
    ans.bits[3] = (exp - 28) << 16;
    ans = _truncate(ans);
    exp = 28;
  }
  ans.bits[3] = exp << 16;

  if (sign_flag) ans.bits[3] = ans.bits[3] | (1u << 31);
  return ans;
}

/** Деление
 * При ошибке во время операции в переменную value_type записывается тип
 * ошибки
 */
_decimal _div(_decimal dec1, _decimal dec2) {
  _decimal zero = {{0x0, 0x0, 0x0, 0x0}, _NORMAL_VALUE};
  _decimal ten = {{10, 0, 0, 0}, _NORMAL_VALUE};
  _decimal one = {{1, 0, 0, 0}, _NORMAL_VALUE};
  _decimal power_of_ten = {{268435456, 1042612833, 542101086, 0},
                              _NORMAL_VALUE};
  _decimal ans = zero;
  _decimal reminder = zero;

  if (_is_zero(dec2)) {
    _set_init_and_type(&ans, _NAN);
  } else {
    int sign_flag = (_is_positive(dec1) ^ _is_positive(dec2));

    _decimal dividend = dec1;
    _decimal divisor = dec2;
    dividend.bits[3] = divisor.bits[3] = 0;

    int exp = give_exp(dec1) - give_exp(dec2);

    int num_bits = 96;

    if (_is_less(dividend, divisor)) {
      give_num_bits(&reminder, divisor, &dividend, &num_bits);
      make_division(&reminder, divisor, &dividend, &ans, num_bits);
    } else {
      ans = zero;
      reminder = dividend;
    }

    while (_is_equal(reminder, zero) && exp < 28 &&
           !_is_less(ans, power_of_ten)) {
      set_fractional_part(&reminder, divisor, &ans);
      exp++;
    }
    if (_is_equal(reminder, zero)) {
      _decimal tmp_ans = zero;
      set_fractional_part(&reminder, divisor, &tmp_ans);
      if (_is_less(tmp_ans, shift(ten, 0))) {
        ans = _add(ans, one);
      }
    }
    if (exp < 0) {
      while (exp < 0) {
        ans = _mul(ans, ten);
        exp++;
      }
    } else {
      ans.bits[3] = exp << 16;
    }
    if (sign_flag) ans.bits[3] = ans.bits[3] | (1u << 31);
  }
  return ans;
}

void give_num_bits(_decimal* reminder, _decimal divisor,
                   _decimal* dividend, int* num_bits) {
  _decimal bit, d;
  _set_init_and_type(&bit, 0);
  _set_init_and_type(&d, 0);
  while (!_is_less(*reminder, divisor)) {
    bit = _bitwise_shift(*dividend, 95);
    *reminder = shift(*reminder, 1);
    reminder->bits[0] = reminder->bits[0] | bit.bits[0];
    d = *dividend;
    *dividend = shift(*dividend, 1);
    *num_bits = *num_bits - 1;
  }

  *dividend = d;
  *reminder = shift(*reminder, 0);
  *num_bits = *num_bits + 1;
}

void make_division(_decimal* reminder, _decimal divisor,
                   _decimal* dividend, _decimal* ans, int num_bits) {
  _decimal bit, t;
  for (int i = 0; i < num_bits; i++) {
    int q = 0;
    bit = _bitwise_shift(*dividend, 95);
    *reminder = shift(*reminder, 1);
    reminder->bits[0] = reminder->bits[0] | bit.bits[0];
    t = _sub(*reminder, divisor);
    q = _is_positive(t);
    *dividend = shift(*dividend, 1);
    *ans = shift(*ans, 1);
    ans->bits[0] = ans->bits[0] | q;
    if (q) *reminder = t;
  }
}

void set_fractional_part(_decimal* reminder, _decimal divisor,
                         _decimal* ans) {
  _decimal zero = {{0x0, 0x0, 0x0, 0x0}, _NORMAL_VALUE};
  _decimal ten = {{10, 0, 0, 0}, _NORMAL_VALUE};
  _decimal new_dividend = _mul(*reminder, ten);
  _decimal new_ans = zero;
  *reminder = zero;
  int num_bits = 96;
  if (_is_less(new_dividend, divisor)) {
    give_num_bits(reminder, divisor, &new_dividend, &num_bits);
    make_division(reminder, divisor, &new_dividend, &new_ans, num_bits);
  } else {
    new_ans = zero;
    *reminder = new_dividend;
  }
  *ans = _mul(*ans, ten);
  *ans = _add(*ans, new_ans);
}
/** Остаток от деления
 * При ошибке во время операции в переменную value_type записывается тип
 * ошибки
 */
_decimal _mod(_decimal dec1, _decimal dec2) {
  _decimal ans;
  if (_is_zero(dec2)) {
    _set_init_and_type(&ans, _NAN);
  } else {
    int sign_flag = 0;
    if (!_is_positive(dec1)) sign_flag++;
    _decimal tmp1 = _make_positive(dec1);
    _decimal tmp2 = _make_positive(dec2);
    if (!_is_less(tmp1, tmp2)) {
      ans = tmp1;
    } else {
      while (!_is_less_or_equal(tmp2, tmp1)) {
        tmp1 = _sub(tmp1, tmp2);
      }
      ans = tmp1;
    }
    if (sign_flag) ans.bits[3] = ans.bits[3] | (1u << 31);
  }
  return ans;
}
