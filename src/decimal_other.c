#include "decimal.h"

/** Округляет указанное Decimal число до ближайшего целого числа
 * в сторону отрицательной бесконечности.
 */
_decimal _floor(_decimal dec) {
  unsigned int exp = (dec.bits[3] & POINTBITS) >> 16;
  if (exp) {
    _decimal zero = {{0, 0, 0, 0}, _NORMAL_VALUE};
    _decimal one = {{1, 0, 0, 0}, _NORMAL_VALUE};
    _decimal temp = dec;
    _shift(&dec, exp);
    if (!_is_less(dec, zero)) {
      if (!_is_not_equal(temp, dec)) dec = _sub(dec, one);
    }
  }
  return dec;
}

/** Округляет Decimal до ближайшего целого числа.
 */
_decimal _round(_decimal dec) {
  if (dec.value_type == _NORMAL_VALUE) {
    unsigned int exp = (dec.bits[3] & POINTBITS) >> 16;
    _decimal zero = {{0, 0, 0, 0}, _NORMAL_VALUE};
    if (exp) {
      _decimal temp = dec;
      _decimal one = {{1, 0, 0, 0}, _NORMAL_VALUE};
      _decimal hf = {{5, 0, 0, 0x0010000}, _NORMAL_VALUE};
      _shift(&dec, exp);
      temp = _sub(temp, dec);
      if (_is_not_equal(temp, zero) == TRUE) {
        int mod = dec.bits[0] & 1u;
        if (!_is_positive(dec)) {
          if (_is_less(temp, _negate(hf)) == TRUE ||
              (_is_equal(temp, _negate(hf)) == TRUE && mod == 1)) {
            dec = _sub(dec, one);
          }
        } else {
          if (_is_greater(temp, hf) == TRUE ||
              (_is_equal(temp, hf) == TRUE && mod == 1)) {
            dec = _add(dec, one);
          }
        }
      }
    }
    if (_is_equal(dec, zero) == TRUE) {
      dec = zero;
    }
  } else {
    if (dec.value_type == _INFINITY)
      _set_init_and_type(&dec, _INFINITY);
    else if (dec.value_type == _NEGATIVE_INFINITY)
      _set_init_and_type(&dec, _NEGATIVE_INFINITY);
    else
      _set_init_and_type(&dec, _NAN);
  }
  return dec;
}

/** Возвращает целые цифры указанного Decimal числа;
 * любые дробные цифры отбрасываются.
 */
_decimal _truncate(_decimal dec) {
  unsigned int exp = (dec.bits[3] & POINTBITS) >> 16;
  if (exp > 0) _shift(&dec, exp);
  return dec;
}

/** Возвращает результат умножения указанного Decimal на -1
 */
_decimal _negate(_decimal dec) {
  if (dec.value_type == _NORMAL_VALUE) {
    dec.bits[3] ^= SIGNBIT;
  } else if (dec.value_type == _INFINITY) {
    dec.value_type = _NEGATIVE_INFINITY;
  } else if (dec.value_type == _NEGATIVE_INFINITY) {
    dec.value_type = _INFINITY;
  }
  return dec;
}
