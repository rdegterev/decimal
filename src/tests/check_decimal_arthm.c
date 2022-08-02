#include "check_decimal.h"
_decimal dec0 = {{0x0, 0x0, 0x0, 0x0}, _NORMAL_VALUE};  // 0.00000000
_decimal dec1 = {{0x0, 0x1, 0x0, ((1u << 19) + (1u << 31))},
                    _NORMAL_VALUE};  // -42.94967296 42,94967296
_decimal dec2 = {{0x0, 0x1, 0x0, 1u << 19},
                    _NORMAL_VALUE};  // 42.94967296 42,94967296
_decimal dec3 = {{0x0, 0x11, 0x0, 1u << 19},
                    _NORMAL_VALUE};  // 730.14444032 730,14444032
_decimal dec4 = {
    {0x0, 0x1, 0x0, ((1u << 20) + (1u << 31))},
    _NORMAL_VALUE};  // -0.0000004294967296 0,0000004294967296
_decimal dec5 = {
    {0x0, 0x0, 0x1, 1u << 19},
    _NORMAL_VALUE};  // 184467440737.09551616 184467440737,09551616
_decimal dec6 = {{0x0, 0x0, 0x1, 1u << 20},
                    _NORMAL_VALUE};  // 1844.6744073709551616
_decimal dec7 = {{MAXVALUE, 0, 0, 0x00000000},
                    _NORMAL_VALUE};                         // 4294967295
_decimal dec8 = {{1, 0, 0, 0x00000000}, _NORMAL_VALUE};  // 1
_decimal dec9 = {{MAXVALUE, MAXVALUE, 0, 0x00000000},
                    _NORMAL_VALUE};  // 18446744073709551615
_decimal dec10 = {{MAXVALUE, MAXVALUE, MAXVALUE, 0x00000000},
                     _NORMAL_VALUE};  // 79228162514264337593543950335

_decimal dec11 = {{0x2021, 0, 0, 0x00040000}, _NORMAL_VALUE};  // 0,8225
_decimal dec12 = {{0x2022, 0, 0, 0x00040000}, _NORMAL_VALUE};  // 0,8226
_decimal dec13 = {{2, 0, 0, 0}, _NORMAL_VALUE};                // 2

_decimal dec17 = {{1, 1, 0, 0x00040000},
                     _NORMAL_VALUE};  // 429496.7297 429496,7297
_decimal dec18 = {{429496, 0, 0, 0}, _NORMAL_VALUE};  // 429496

_decimal dec19 = {{1, 1, 0, 0x80040000},
                     _NORMAL_VALUE};  // -429496.7297 -429496,7297
_decimal dec20 = {{429496, 0, 0, 0x80000000}, _NORMAL_VALUE};  // -429496
_decimal dec21 = {{MAXVALUE, MAXVALUE, MAXVALUE, 0x80000000},
                     _NORMAL_VALUE};  // -79228162514264337593543950335
_decimal dec23 = {{MAXVALUE, MAXVALUE, 0, 1 << 18},
                     _NORMAL_VALUE};                 // 1844674407370955.1615
_decimal dec24 = {{10, 0, 0, 0}, _NORMAL_VALUE};  // 10
_decimal dec25 = {{3, 0, 0, 0}, _NORMAL_VALUE};   // 3
_decimal dec26 = {{MAXVALUE - 1, MAXVALUE - 2, MAXVALUE - 3, 3 << 19},
                     _NORMAL_VALUE};  // 79228.162458924105363825360894
                                         // 79228,162458924105363825360894
_decimal dec27 = {{MAXVALUE, 100000, 0, 0x000E0000},
                     _NORMAL_VALUE};  // 4.29501024567295 4,29501024567295
_decimal dec28 = {{0, 0, MAXVALUE, 0x00020000},
                     _NORMAL_VALUE};  // 792281624958175935198343987.20
_decimal dec29 = {{0, MAXVALUE, 0, 0x00000000},
                     _NORMAL_VALUE};  // 18446744069414584320
_decimal dec30 = {{42, 0, 0, 0x00000000}, _NORMAL_VALUE};  // 42
_decimal dec31 = {{0x033333333, 0x00f3333333, 0x00028f5c28, 0x00000000},
                     _NORMAL_VALUE};  // 792281624958175935198343987
_decimal dec32 = {{0, 0, MAXVALUE, 0x80020000},
                     _NORMAL_VALUE};  // -792281624958175935198343987.20
_decimal dec33 = {{2, 0, 0, 0x80010000}, _NORMAL_VALUE};  // -0.2
_decimal dec34 = {{0, MAXVALUE, 0, 0x80020000},
                     _NORMAL_VALUE};  // -184467440694145843.20

_decimal decneginf = {{0x0, 0x1, 0x0, 1u << 19}, _NEGATIVE_INFINITY};
_decimal decinf = {{0x0, 0x1, 0x0, 1u << 19}, _INFINITY};
_decimal decnan = {{0x0, 0x1, 0x0, 1u << 19}, _NAN};

START_TEST(test__add) {
  //
  char *str;
  ck_assert_str_eq(str = _from_decimal_to_string(_add(dec1, dec2)), "0");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_add(dec1, dec3)),
                   "687.19476736");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_add(dec2, dec3)),
                   "773.09411328");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_add(dec3, dec4)),
                   "730.1444398905032704");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_add(dec0, dec4)),
                   "-0.0000004294967296");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_add(dec2, dec2)),
                   "85.89934592");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_add(dec7, dec7)),
                   "8589934590");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_add(decinf, dec2)),
                   "INFINITY");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_add(decnan, dec2)),
                   "NAN");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_add(decneginf, dec2)),
                   "NEGATIVE_INFINITY");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_add(dec7, dec8)),
                   "4294967296");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_add(dec9, dec8)),
                   "18446744073709551616");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_add(dec9, dec9)),
                   "36893488147419103230");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_add(dec10, dec8)),
                   "INFINITY");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_add(dec26, dec26)),
                   "158456.32491784821072765072178");
  DESTROY(str);  // косяк с точностью последней дробной цифры

  ck_assert_str_eq(str = _from_decimal_to_string(dec28),
                   "792281624958175935198343987.20");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(dec29),
                   "18446744069414584320");
  DESTROY(str);
  // 792281624958175935198343987.20 + 18446744069414584320 =
  // 792281606511431865783759667,2
  ck_assert_str_eq(str = _from_decimal_to_string(_add(dec28, dec29)),
                   "792281643404920004612928307.2");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(_add(dec2, dec30)),
                   "84.94967296");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec34),
                   "-184467440694145843.20");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(dec33), "-0.2");
  DESTROY(str);
  // -184467440694145843.20 + (-0.2) = -184467440694145843.40
  ck_assert_str_eq(str = _from_decimal_to_string(_add(dec34, dec33)),
                   "-184467440694145843.40");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec32),
                   "-792281624958175935198343987.20");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(dec33), "-0.2");
  DESTROY(str);
  // 792281624958175935198343987.20 + (-0.2) = 792281624958175935198343987.40
  ck_assert_str_eq(str = _from_decimal_to_string(_add(dec32, dec33)),
                   "-792281624958175935198343987.40");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec28),
                   "792281624958175935198343987.20");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(dec31),
                   "792281624958175935198343987");
  DESTROY(str);
  // 792281624958175935198343987.20 + 792281624958175935198343987 =
  // 1584563249916351870396687974.2
  ck_assert_str_eq(str = _from_decimal_to_string(_add(dec28, dec31)),
                   "1584563249916351870396687974.2");
  DESTROY(str);
}
END_TEST

START_TEST(test__sub) {
  //
  char *str;
  ck_assert_str_eq(str = _from_decimal_to_string(_sub(dec1, dec2)),
                   "-85.89934592");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_sub(dec3, dec2)),
                   "687.19476736");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_sub(dec2, dec1)),
                   "85.89934592");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_sub(dec2, dec2)), "0");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_sub(dec3, dec4)),
                   "730.1444407494967296");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_sub(dec17, dec18)),
                   "0.7297");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_sub(dec20, dec19)),
                   "0.7297");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_sub(dec19, dec20)),
                   "-0.7297");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_sub(dec21, dec21)),
                   "0");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_sub(decinf, dec2)),
                   "INFINITY");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_sub(decnan, dec2)),
                   "NAN");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_sub(decneginf, dec2)),
                   "NEGATIVE_INFINITY");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_sub(dec21, dec2)),
                   "NEGATIVE_INFINITY");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec28),
                   "792281624958175935198343987.20");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(dec29),
                   "18446744069414584320");
  DESTROY(str);
  // 792281624958175935198343987.20 - 18446744069414584320 =
  // 792281606511431865783759667,2
  ck_assert_str_eq(str = _from_decimal_to_string(_sub(dec28, dec29)),
                   "792281606511431865783759667.20");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(_sub(dec2, dec30)),
                   "0.94967296");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec34),
                   "-184467440694145843.20");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(dec33), "-0.2");
  DESTROY(str);
  // -184467440694145843.20 - (-0.2) = -184467440694145843
  ck_assert_str_eq(str = _from_decimal_to_string(_sub(dec34, dec33)),
                   "-184467440694145843.00");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec32),
                   "-792281624958175935198343987.20");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(dec33), "-0.2");
  DESTROY(str);
  // 792281624958175935198343987.20 - (-0.2) = 792281624958175935198343987
  ck_assert_str_eq(str = _from_decimal_to_string(_sub(dec32, dec33)),
                   "-792281624958175935198343987.00");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(dec28),
                   "792281624958175935198343987.20");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(dec31),
                   "792281624958175935198343987");
  DESTROY(str);
  // 792281624958175935198343987.20 - 792281624958175935198343987 = 0.20
  ck_assert_str_eq(str = _from_decimal_to_string(_sub(dec28, dec31)),
                   "0.20");  // 184467440737095516.36 ???
  DESTROY(str);
}
END_TEST

START_TEST(test__mul) {
  //
  char *str;
  ck_assert_str_eq(str = _from_decimal_to_string(_mul(dec1, dec2)),
                   "-1844.6744073709551616");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_mul(dec3, dec2)),
                   "31359.4649253062377472");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_mul(dec2, dec1)),
                   "-1844.6744073709551616");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_mul(dec0, dec2)),
                   "0.00000000");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_mul(dec3, dec4)),
                   "-0.000313594649253062377472");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_mul(dec17, dec18)),
                   "184467127419.2312");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_mul(dec19, dec20)),
                   "184467127419.2312");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_mul(dec11, dec12)),
                   "0.67658850");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_mul(dec11, dec13)),
                   "1.6450");
  DESTROY(str);
  // ck_assert_str_eq(str = _from_decimal_to_string(_mul(dec26, dec26)),
  //                  "6277101726.6176709415517837492");
  // DESTROY(str);
  // ck_assert_str_eq(str = _from_decimal_to_string(_mul(dec27, dec27)),
  //                  "18.447113010435614314198361702");
  // DESTROY(str);
}
END_TEST

START_TEST(test__div) {
  // 10/23
  char *str;
  ck_assert_str_eq(str = _from_decimal_to_string(_div(dec10, dec23)),
                   "42949672960000.000002328306436");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_div(dec0, dec1)), "-0");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_div(dec3, dec2)), "17");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_div(dec3, dec4)),
                   "-1700000000");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_div(dec5, dec9)),
                   "0.0000000100000000000000000005");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_div(dec17, dec13)),
                   "214748.36485");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_div(dec7, dec3)),
                   "5882352.9398068785667419433594");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_div(dec24, dec25)),
                   "3.3333333333333333333333333333");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_div(dec17, dec24)),
                   "42949.67297");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_div(dec11, dec12)),
                   "0.9998784342329200097252613664");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_div(dec27, dec0)),
                   "NAN");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(_div(dec26, dec27)),
                   "18446.559595228740387839559170");
  DESTROY(str);
}
END_TEST

START_TEST(test__mod) {
  //
  char *str;

  // ck_assert_str_eq(str = _from_decimal_to_string(_mod(dec11, dec12)),
  //                  "0.8225");
  // DESTROY(str);

  // ck_assert_str_eq(str = _from_decimal_to_string(_mod(dec7, dec3)),
  //                  "686.19476736");
  // DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(_mod(dec5, dec9)),
                   "184467440737.09551616");
  DESTROY(str);

  // ck_assert_str_eq(str = _from_decimal_to_string(_mod(dec9, dec5)),
  //                  "184467440736.09551616");
  // DESTROY(str);

  // ck_assert_str_eq(str = _from_decimal_to_string(_mod(dec10, dec13)),
  //                  "1");
  // DESTROY(str);

  // 0 % 2
  ck_assert_str_eq(str = _from_decimal_to_string(_mod(dec0, dec13)), "0");
  DESTROY(str);

  // ck_assert_str_eq(str = _from_decimal_to_string(_mod(dec10, dec23)),
  //                  "4294967295");
  // DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(_mod(dec0, dec1)), "0");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(_mod(dec3, dec2)), "0");
  DESTROY(str);

  // ck_assert_str_eq(str = _from_decimal_to_string(_mod(dec3, dec4)),
  // "0"); DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(_mod(dec5, dec9)),
                   "184467440737.09551616");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(_mod(dec17, dec13)),
                   "0.7297");
  DESTROY(str);

  // ck_assert_str_eq(str = _from_decimal_to_string(_mod(dec7, dec3)),
  // "686,19476736");
  // DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(_mod(dec24, dec25)),
                   "1");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(_mod(dec17, dec24)),
                   "6.7297");
  DESTROY(str);

  ck_assert_str_eq(str = _from_decimal_to_string(_mod(dec11, dec12)),
                   "0.8225");
  DESTROY(str);

  // ck_assert_str_eq(str = _from_decimal_to_string(_mod(dec27, dec0)),
  //                  "NAN");
  // DESTROY(str);
}
END_TEST

TCase *decimal_arthm_tests(void) {
  TCase *t_case = tcase_create("Arithmetic_functions");

  tcase_add_test(t_case, test__add);
  tcase_add_test(t_case, test__sub);
  tcase_add_test(t_case, test__mul);
  tcase_add_test(t_case, test__div);
  tcase_add_test(t_case, test__mod);

  return t_case;
}
