#include "decimal.h"

/** Меньше
 * Возвращаемое значение:
 * 0 - TRUE
 * 1 - FALSE
 */
int _is_less(_decimal dec1, _decimal dec2) {
  int res = FALSE;
  if (dec1.value_type != _NAN && dec2.value_type != _NAN) {
    if (dec1.value_type == _NORMAL_VALUE &&
        dec2.value_type == _NORMAL_VALUE) {
      if (_is_positive(dec1) == _is_positive(dec2)) {
        int negative = !(_is_positive(dec1) && _is_positive(dec1));
        _decimal left = dec1;
        _decimal right = dec2;
        _normalize(&left, &right);
        if (left.bits[2] == right.bits[2]) {
          if (left.bits[1] == right.bits[1]) {
            if (left.bits[0] == right.bits[0]) {
              res = FALSE;
            } else {
              res = !(negative ^ (left.bits[0] < right.bits[0]));
            }
          } else {
            res = !(negative ^ (left.bits[1] < right.bits[1]));
          }
        } else {
          res = !(negative ^ (left.bits[2] < right.bits[2]));
        }
      } else {
        res = !(_is_positive(dec1) < _is_positive(dec2));
      }
    }
  }
  if (dec2.value_type == _INFINITY && dec1.value_type != _INFINITY)
    res = TRUE;
  if (dec1.value_type == _NEGATIVE_INFINITY &&
      dec2.value_type != _NEGATIVE_INFINITY)
    res = TRUE;
  return res;
}

/** Меньше или равно
 * Возвращаемое значение:
 * 0 - TRUE
 * 1 - FALSE
 */
int _is_less_or_equal(_decimal dec1, _decimal dec2) {
  int res = FALSE;
  if (dec1.value_type != _NAN && dec2.value_type != _NAN) {
    res = !(!_is_less(dec1, dec2) || !_is_equal(dec1, dec2));
  }
  return res;
}

/** Больше
 * Возвращаемое значение:
 * 0 - TRUE
 * 1 - FALSE
 */
int _is_greater(_decimal dec1, _decimal dec2) {
  int res = FALSE;
  if (dec1.value_type != _NAN && dec2.value_type != _NAN) {
    res = !_is_less_or_equal(dec1, dec2);
  }
  return res;
}

/** Больше или равно
 * Возвращаемое значение:
 * 0 - TRUE
 * 1 - FALSE
 */
int _is_greater_or_equal(_decimal dec1, _decimal dec2) {
  int res = FALSE;
  if (dec1.value_type != _NAN && dec2.value_type != _NAN) {
    res = !(!_is_greater(dec1, dec2) || !_is_equal(dec1, dec2));
  }
  return res;
}

/** Равно
 * Возвращаемое значение:
 * 0 - TRUE
 * 1 - FALSE
 */
int _is_equal(_decimal dec1, _decimal dec2) {
  int res = FALSE;
  if (dec1.value_type != _NAN && dec2.value_type != _NAN) {
    if (dec1.value_type == dec2.value_type) {
      _decimal left = dec1;
      _decimal right = dec2;
      _normalize(&left, &right);
      res = !!(memcmp(left.bits, right.bits, sizeof(unsigned int) * 4));
      if (dec1.value_type == _INFINITY) res = TRUE;
      if (dec1.value_type == _NEGATIVE_INFINITY) res = TRUE;
      int flag = 0;
      for (int i = 0; i < 3; i++) {
        flag += ((dec1.bits[i] == 0) && (dec2.bits[i] == 0));
      }
      if (flag == 3) res = TRUE;
    }
  }
  return res;
}

/** Не равно
 * Возвращаемое значение:
 * 0 - TRUE
 * 1 - FALSE
 */
int _is_not_equal(_decimal dec1, _decimal dec2) {
  return !(_is_equal(dec1, dec2));
}
