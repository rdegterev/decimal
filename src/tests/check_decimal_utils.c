
#include "check_decimal.h"

START_TEST(test__from_decimal_to_string) {
  //
  char *str;
  _decimal dec0 = {{1, 1, 0, 0x00000000}, _NORMAL_VALUE};
  ck_assert_str_eq(str = _from_decimal_to_string(dec0), "4294967297");
  DESTROY(str);
  _decimal dec1 = {{0, 0xffffffff, 0, 0x000a0000}, _NORMAL_VALUE};
  ck_assert_str_eq(str = _from_decimal_to_string(dec1),
                   "1844674406.9414584320");
  DESTROY(str);
  _decimal dec2 = {{0, 0xffffffff, 0, 0x800a0000}, _NORMAL_VALUE};
  ck_assert_str_eq(str = _from_decimal_to_string(dec2),
                   "-1844674406.9414584320");
  DESTROY(str);
  _decimal dec3 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000},
                      _NORMAL_VALUE};
  ck_assert_str_eq(str = _from_decimal_to_string(dec3),
                   "79228162514264337593543950335");
  DESTROY(str);
  _decimal dec4 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000},
                      _NORMAL_VALUE};
  ck_assert_str_eq(str = _from_decimal_to_string(dec4),
                   "-79228162514264337593543950335");
  DESTROY(str);
  _decimal dec5 = {{0, 0, 0, 0}, _NORMAL_VALUE};
  ck_assert_str_eq(str = _from_decimal_to_string(dec5), "0");
  DESTROY(str);
  _decimal dec6 = {{0, 0, 0, 0x80000000}, _NORMAL_VALUE};
  ck_assert_str_eq(str = _from_decimal_to_string(dec6), "-0");
  DESTROY(str);
  _decimal dec7 = {{0x00000000, 0, 0, 0x80050000}, _NORMAL_VALUE};
  ck_assert_str_eq(str = _from_decimal_to_string(dec7), "-0.00000");
  DESTROY(str);
  _decimal dec8 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x801C0000},
                      _NORMAL_VALUE};
  ck_assert_str_eq(str = _from_decimal_to_string(dec8),
                   "-7.9228162514264337593543950335");
  DESTROY(str);
  _decimal dec9 = {{1, 0, 0, 0x801C0000}, _NORMAL_VALUE};
  ck_assert_str_eq(str = _from_decimal_to_string(dec9),
                   "-0.0000000000000000000000000001");
  DESTROY(str);
  _decimal dec10 = {{MAXVALUE, 100000, 0, 0x000E0000}, _NORMAL_VALUE};
  ck_assert_str_eq(str = _from_decimal_to_string(dec10), "4.29501024567295");
  DESTROY(str);
}
END_TEST

START_TEST(test__shift) {
  //
  char *str;
  int res;
  _decimal dec1 = {{0, 0xffffffff, 0, 0x000a0000}, _NORMAL_VALUE};
  ck_assert_str_eq(str = _from_decimal_to_string(dec1),
                   "1844674406.9414584320");
  DESTROY(str);
  _shift(&dec1, -2);
  ck_assert_str_eq(str = _from_decimal_to_string(dec1),
                   "1844674406.941458432000");
  DESTROY(str);
  _shift(&dec1, 3);
  ck_assert_str_eq(str = _from_decimal_to_string(dec1),
                   "1844674406.941458432");
  DESTROY(str);
  res = _shift(&dec1, 10);
  ck_assert_int_eq(res, 1);
  ck_assert_str_eq(str = _from_decimal_to_string(dec1),
                   "1844674406.941458432");
  DESTROY(str);
  res = _shift(&dec1, 9);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec1), "1844674406");
  DESTROY(str);
  res = _shift(&dec1, -15);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec1),
                   "1844674406.000000000000000");
  DESTROY(str);
  res = _shift(&dec1, -5);
  ck_assert_int_eq(res, 1);
  ck_assert_str_eq(str = _from_decimal_to_string(dec1),
                   "1844674406.000000000000000");
  DESTROY(str);
}
END_TEST

START_TEST(test__normalize) {
  char *str;
  int res;
  _decimal dec1 = {{0, 0xffffffff, 0, 0x000a0000}, _NORMAL_VALUE};
  _decimal dec2 = {{100, 1, 0, 0x00020000}, _NORMAL_VALUE};
  _decimal dec3 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00060000},
                      _NORMAL_VALUE};
  _decimal dec5 = {{0, 0, 0, 0x80000000}, _NORMAL_VALUE};
  _decimal dec6 = {{1, 1, 0, 0x00040000}, _NORMAL_VALUE};  // 429496.7297
  _decimal dec7 = {{429496, 0, 0, 0}, _NORMAL_VALUE};      // 429496
  _decimal dec8 = {{0, 0, MAXVALUE, 0x00020000},
                      _NORMAL_VALUE};  // 792281624958175935198343987.20
  _decimal dec9 = {{2, 0, 0, 0x00010000}, _NORMAL_VALUE};  // 0.2
  _decimal dec10 = {{0, 0, MAXVALUE, 0x80020000},
                       _NORMAL_VALUE};  // -792281624958175935198343987.20
  _decimal dec11 = {{2, 0, 0, 0x80010000}, _NORMAL_VALUE};  // 0.2

  ck_assert_str_eq(str = _from_decimal_to_string(dec1),
                   "1844674406.9414584320");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(dec2), "42949673.96");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(dec3),
                   "79228162514264337593543.950335");
  DESTROY(str);

  res = _normalize(&dec1, &dec2);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec1),
                   "1844674406.9414584320");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(dec2),
                   "42949673.9600000000");
  DESTROY(str);

  res = _normalize(&dec1, &dec3);
  ck_assert_int_eq(res, 1);
  ck_assert_str_eq(str = _from_decimal_to_string(dec1), "1844674406.941458");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(dec3),
                   "79228162514264337593543.950335");
  DESTROY(str);

  res = _normalize(&dec3, &dec5);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec3),
                   "79228162514264337593543.950335");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(dec5), "0.000000");
  DESTROY(str);

  res = _normalize(&dec6, &dec7);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec6), "429496.7297");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(dec7), "429496.0000");
  DESTROY(str);

  res = _normalize(&dec8, &dec9);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec8),
                   "792281624958175935198343987.20");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(dec9), "0.20");
  DESTROY(str);

  res = _normalize(&dec10, &dec11);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec10),
                   "-792281624958175935198343987.20");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(dec11), "-0.20");
  DESTROY(str);
}
END_TEST

TCase *decimal_utils_tests(void) {
  TCase *t_case = tcase_create("Utils_functions");

  tcase_add_test(t_case, test__from_decimal_to_string);
  tcase_add_test(t_case, test__shift);
  tcase_add_test(t_case, test__normalize);

  return t_case;
}
