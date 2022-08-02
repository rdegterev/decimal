#include "check_decimal.h"

START_TEST(test__floor) {
  //
  char *str;
  _decimal dec1 = {{1, 1, 0, 0x00040000}, _NORMAL_VALUE};
  _decimal dec2 = {{1, 1, 0, 0x80040000}, _NORMAL_VALUE};
  _decimal dec3 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00050000},
                      _NORMAL_VALUE};
  _decimal dec4 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80050000},
                      _NORMAL_VALUE};
  _decimal dec5 = {{0, 0xffffffff, 0, 0x001C0000}, _NORMAL_VALUE};
  _decimal dec6 = {{0, 0xffffffff, 0, 0x801C0000}, _NORMAL_VALUE};
  _decimal dec7 = {{0, 0, 0, 0}, _INFINITY};
  _decimal dec8 = {{0, 0, 0, 0}, _NEGATIVE_INFINITY};
  _decimal dec9 = {{0, 0, 0, 0}, _NAN};

  ck_assert_str_eq(str = _from_decimal_to_string(dec1), "429496.7297");
  DESTROY(str);
  dec1 = _floor(dec1);
  ck_assert_str_eq(str = _from_decimal_to_string(dec1), "429496");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec2), "-429496.7297");
  DESTROY(str);
  dec2 = _floor(dec2);
  ck_assert_str_eq(str = _from_decimal_to_string(dec2), "-429497");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec3),
                   "792281625142643375935439.50335");
  DESTROY(str);
  dec3 = _floor(dec3);
  ck_assert_str_eq(str = _from_decimal_to_string(dec3),
                   "792281625142643375935439");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec4),
                   "-792281625142643375935439.50335");
  DESTROY(str);
  dec4 = _floor(dec4);
  ck_assert_str_eq(str = _from_decimal_to_string(dec4),
                   "-792281625142643375935440");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec5),
                   "0.0000000018446744069414584320");
  DESTROY(str);
  dec5 = _floor(dec5);
  ck_assert_str_eq(str = _from_decimal_to_string(dec5), "0");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec6),
                   "-0.0000000018446744069414584320");
  DESTROY(str);
  dec6 = _floor(dec6);
  ck_assert_str_eq(str = _from_decimal_to_string(dec6), "-1");
  DESTROY(str);

  ck_assert_int_eq(dec7.value_type, _INFINITY);
  dec7 = _floor(dec7);
  ck_assert_int_eq(dec7.value_type, _INFINITY);

  ck_assert_int_eq(dec8.value_type, _NEGATIVE_INFINITY);
  dec8 = _floor(dec8);
  ck_assert_int_eq(dec8.value_type, _NEGATIVE_INFINITY);

  ck_assert_int_eq(dec9.value_type, _NAN);
  dec9 = _floor(dec9);
  ck_assert_int_eq(dec9.value_type, _NAN);
}
END_TEST

START_TEST(test__round) {
  //
  char *str;
  _decimal dec1 = {{1, 1, 0, 0x00040000}, _NORMAL_VALUE};
  _decimal dec2 = {{1, 1, 0, 0x80040000}, _NORMAL_VALUE};
  _decimal dec3 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00050000},
                      _NORMAL_VALUE};
  _decimal dec4 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80050000},
                      _NORMAL_VALUE};
  _decimal dec5 = {{0, 0xffffffff, 0, 0x001C0000}, _NORMAL_VALUE};
  _decimal dec6 = {{0, 0xffffffff, 0, 0x801C0000}, _NORMAL_VALUE};
  _decimal dec7 = {{0, 0, 0, 0}, _INFINITY};
  _decimal dec8 = {{0, 0, 0, 0}, _NEGATIVE_INFINITY};
  _decimal dec9 = {{0, 0, 0, 0}, _NAN};
  _decimal dec10 = {{0, 0, 0, 0}, _NORMAL_VALUE};
  _decimal dec11 = {{99, 0, 0, 0x00020000}, _NORMAL_VALUE};
  _decimal dec12 = {{555555, 0, 0, 0x00060000}, _NORMAL_VALUE};
  _decimal dec13 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x801C0000},
                       _NORMAL_VALUE};
  _decimal dec14 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00010000},
                       _NORMAL_VALUE};
  _decimal dec15 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000},
                       _NORMAL_VALUE};
  _decimal dec16 = {{9, 0, 0, 0x00010000}, _NORMAL_VALUE};
  _decimal dec19 = {{5, 0, 0, 0x00010000}, _NORMAL_VALUE};
  _decimal dec20 = {{15, 0, 0, 0x00010000}, _NORMAL_VALUE};
  _decimal dec21 = {{5, 0, 0, 0x80010000}, _NORMAL_VALUE};
  _decimal dec22 = {{15, 0, 0, 0x80010000}, _NORMAL_VALUE};
  _decimal dec23 = {{51, 0, 0, 0x80020000}, _NORMAL_VALUE};
  _decimal dec24 = {{151, 0, 0, 0x80020000}, _NORMAL_VALUE};
  _decimal dec25 = {{0, MAXVALUE, 0, 0x00020000}, _NORMAL_VALUE};
  _decimal dec26 = {{MAXVALUE, MAXVALUE, MAXVALUE - 1, 0x00020000},
                       _NORMAL_VALUE};
  _decimal dec27 = {{0, MAXVALUE, 0, 0x00030000}, _NORMAL_VALUE};
  _decimal dec28 = {{0, 0, MAXVALUE, 0x00030000}, _NORMAL_VALUE};
  _decimal dec29 = {{0, 0, MAXVALUE, 0x00020000}, _NORMAL_VALUE};

  ck_assert_str_eq(str = _from_decimal_to_string(dec1), "429496.7297");
  DESTROY(str);
  dec1 = _round(dec1);
  ck_assert_str_eq(str = _from_decimal_to_string(dec1), "429497");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec2), "-429496.7297");
  DESTROY(str);
  dec2 = _round(dec2);
  ck_assert_str_eq(str = _from_decimal_to_string(dec2), "-429497");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec3),
                   "792281625142643375935439.50335");
  DESTROY(str);
  dec3 = _round(dec3);
  ck_assert_str_eq(str = _from_decimal_to_string(dec3),
                   "792281625142643375935440");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec4),
                   "-792281625142643375935439.50335");
  DESTROY(str);
  dec4 = _round(dec4);
  ck_assert_str_eq(str = _from_decimal_to_string(dec4),
                   "-792281625142643375935440");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec5),
                   "0.0000000018446744069414584320");
  DESTROY(str);
  dec5 = _round(dec5);
  ck_assert_str_eq(str = _from_decimal_to_string(dec5), "0");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec6),
                   "-0.0000000018446744069414584320");
  DESTROY(str);
  dec6 = _round(dec6);
  ck_assert_str_eq(str = _from_decimal_to_string(dec6), "0");
  DESTROY(str);

  ck_assert_int_eq(dec7.value_type, _INFINITY);
  dec7 = _round(dec7);
  ck_assert_int_eq(dec7.value_type, _INFINITY);
  ck_assert_str_eq(str = _from_decimal_to_string(dec7), "INFINITY");
  DESTROY(str);

  ck_assert_int_eq(dec8.value_type, _NEGATIVE_INFINITY);
  dec8 = _round(dec8);
  ck_assert_int_eq(dec8.value_type, _NEGATIVE_INFINITY);
  ck_assert_str_eq(str = _from_decimal_to_string(dec8), "NEGATIVE_INFINITY");
  DESTROY(str);

  ck_assert_int_eq(dec9.value_type, _NAN);
  dec9 = _round(dec9);
  ck_assert_int_eq(dec9.value_type, _NAN);
  ck_assert_str_eq(str = _from_decimal_to_string(dec9), "NAN");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec10), "0");
  DESTROY(str);
  dec10 = _round(dec10);
  ck_assert_str_eq(str = _from_decimal_to_string(dec10), "0");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec11), "0.99");
  DESTROY(str);
  dec11 = _round(dec11);
  ck_assert_str_eq(str = _from_decimal_to_string(dec11), "1");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec12), "0.555555");
  DESTROY(str);
  dec12 = _round(dec12);
  ck_assert_str_eq(str = _from_decimal_to_string(dec12), "1");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec13),
                   "-7.9228162514264337593543950335");
  DESTROY(str);
  dec13 = _round(dec13);
  ck_assert_str_eq(str = _from_decimal_to_string(dec13), "-8");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec14),
                   "7922816251426433759354395033.5");
  DESTROY(str);
  dec14 = _round(dec14);
  ck_assert_str_eq(str = _from_decimal_to_string(dec14),
                   "7922816251426433759354395034");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec15),
                   "79228162514264337593543950335");
  DESTROY(str);
  dec15 = _round(dec15);
  ck_assert_str_eq(str = _from_decimal_to_string(dec15),
                   "79228162514264337593543950335");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec16), "0.9");
  DESTROY(str);
  dec16 = _round(dec16);
  ck_assert_str_eq(str = _from_decimal_to_string(dec16), "1");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec24), "-1.51");
  DESTROY(str);
  dec24 = _round(dec24);
  ck_assert_str_eq(str = _from_decimal_to_string(dec24), "-2");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec22), "-1.5");
  DESTROY(str);
  dec22 = _round(dec22);
  ck_assert_str_eq(str = _from_decimal_to_string(dec22), "-2");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec23), "-0.51");
  DESTROY(str);
  dec23 = _round(dec23);
  ck_assert_str_eq(str = _from_decimal_to_string(dec23), "-1");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec21), "-0.5");
  DESTROY(str);
  dec21 = _round(dec21);
  ck_assert_str_eq(str = _from_decimal_to_string(dec21), "0");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec19), "0.5");
  DESTROY(str);
  dec19 = _round(dec19);
  ck_assert_str_eq(str = _from_decimal_to_string(dec19), "0");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec20), "1.5");
  DESTROY(str);
  dec20 = _round(dec20);
  ck_assert_str_eq(str = _from_decimal_to_string(dec20), "2");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec25),
                   "184467440694145843.20");
  DESTROY(str);
  dec25 = _round(dec25);
  ck_assert_str_eq(str = _from_decimal_to_string(dec25),
                   "184467440694145843");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec26),
                   "792281624958175935198343987.19");
  DESTROY(str);
  dec26 = _round(dec26);
  ck_assert_str_eq(str = _from_decimal_to_string(dec26),
                   "792281624958175935198343987");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec27),
                   "18446744069414584.320");
  DESTROY(str);
  dec27 = _round(dec27);
  ck_assert_str_eq(str = _from_decimal_to_string(dec27),
                   "18446744069414584");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec28),
                   "79228162495817593519834398.720");
  DESTROY(str);
  dec28 = _round(dec28);
  ck_assert_str_eq(str = _from_decimal_to_string(dec28),
                   "79228162495817593519834399");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec29),
                   "792281624958175935198343987.20");
  DESTROY(str);
  dec29 = _round(dec29);
  ck_assert_str_eq(str = _from_decimal_to_string(dec29),
                   "792281624958175935198343987");
  DESTROY(str);
}
END_TEST

START_TEST(test__truncate) {
  //
  char *str;
  _decimal dec1 = {{0, 0xffffffff, 0, 0x800a0000}, _NORMAL_VALUE};
  _decimal dec2 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x000a0000},
                      _NORMAL_VALUE};
  _decimal dec3 = {{0, 0xffffffff, 0, 0x001C0000}, _NORMAL_VALUE};
  _decimal dec4 = {{0, 0, 0, 0}, _NORMAL_VALUE};
  _decimal dec5 = {{0, 0, 0, 0}, _INFINITY};
  _decimal dec6 = {{0, 0, 0, 0}, _NEGATIVE_INFINITY};
  _decimal dec7 = {{0, 0, 0, 0}, _NAN};

  ck_assert_str_eq(str = _from_decimal_to_string(dec1),
                   "-1844674406.9414584320");
  DESTROY(str);
  dec1 = _truncate(dec1);
  ck_assert_str_eq(str = _from_decimal_to_string(dec1), "-1844674406");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec2),
                   "7922816251426433759.3543950335");
  DESTROY(str);
  dec2 = _truncate(dec2);
  ck_assert_str_eq(str = _from_decimal_to_string(dec2),
                   "7922816251426433759");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec3),
                   "0.0000000018446744069414584320");
  DESTROY(str);
  dec3 = _truncate(dec3);
  ck_assert_str_eq(str = _from_decimal_to_string(dec3), "0");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec4), "0");
  DESTROY(str);
  dec4 = _truncate(dec4);
  ck_assert_str_eq(str = _from_decimal_to_string(dec4), "0");
  DESTROY(str);

  ck_assert_int_eq(dec5.value_type, _INFINITY);
  dec5 = _truncate(dec5);
  ck_assert_int_eq(dec5.value_type, _INFINITY);

  ck_assert_int_eq(dec6.value_type, _NEGATIVE_INFINITY);
  dec6 = _truncate(dec6);
  ck_assert_int_eq(dec6.value_type, _NEGATIVE_INFINITY);

  ck_assert_int_eq(dec7.value_type, _NAN);
  dec7 = _truncate(dec7);
  ck_assert_int_eq(dec7.value_type, _NAN);
}
END_TEST

START_TEST(test__negate) {
  //
  char *str;
  _decimal dec1 = {{0, 0xffffffff, 0, 0x800a0000}, _NORMAL_VALUE};
  _decimal dec2 = {{0, 0, 0, 0}, _NORMAL_VALUE};
  _decimal dec3 = {{0, 0, 0, 0}, _INFINITY};
  _decimal dec4 = {{0, 0, 0, 0}, _NAN};
  _decimal dec5 = {{0, 0, 0, 0}, _NEGATIVE_INFINITY};

  ck_assert_str_eq(str = _from_decimal_to_string(dec1),
                   "-1844674406.9414584320");
  DESTROY(str);
  dec1 = _negate(dec1);
  ck_assert_str_eq(str = _from_decimal_to_string(dec1),
                   "1844674406.9414584320");
  DESTROY(str);
  dec1 = _negate(dec1);
  ck_assert_str_eq(str = _from_decimal_to_string(dec1),
                   "-1844674406.9414584320");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec2), "0");
  DESTROY(str);
  dec2 = _negate(dec2);
  ck_assert_str_eq(str = _from_decimal_to_string(dec2), "-0");
  DESTROY(str);
  dec2 = _negate(dec2);
  ck_assert_str_eq(str = _from_decimal_to_string(dec2), "0");
  DESTROY(str);

  ck_assert_int_eq(dec3.value_type, _INFINITY);
  dec3 = _negate(dec3);
  ck_assert_int_eq(dec3.value_type, _NEGATIVE_INFINITY);
  dec3 = _negate(dec3);
  ck_assert_int_eq(dec3.value_type, _INFINITY);

  ck_assert_int_eq(dec4.value_type, _NAN);
  dec4 = _negate(dec4);
  ck_assert_int_eq(dec4.value_type, _NAN);

  ck_assert_int_eq(dec5.value_type, _NEGATIVE_INFINITY);
  dec5 = _negate(dec5);
  ck_assert_int_eq(dec5.value_type, _INFINITY);
  dec5 = _negate(dec5);
  ck_assert_int_eq(dec5.value_type, _NEGATIVE_INFINITY);
}
END_TEST

TCase *decimal_other_tests(void) {
  TCase *t_case = tcase_create("Other_functions");

  tcase_add_test(t_case, test__floor);
  tcase_add_test(t_case, test__round);
  tcase_add_test(t_case, test__truncate);
  tcase_add_test(t_case, test__negate);

  return t_case;
}
