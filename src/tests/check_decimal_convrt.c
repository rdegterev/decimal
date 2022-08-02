#include "check_decimal.h"

START_TEST(test__from_int_to_decimal) {
  //
  char *str;
  int res, i, i_res;
  _decimal dec = {{0, 0, 0, 0x00000000}, _NORMAL_VALUE};

  i = 0;
  res = _from_int_to_decimal(i, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec), "0");
  DESTROY(str);
  res = _from_decimal_to_int(dec, &i_res);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(i, i_res);

  i = 5;
  res = _from_int_to_decimal(i, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec), "5");
  DESTROY(str);
  res = _from_decimal_to_int(dec, &i_res);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(i, i_res);

  i = 1410065407;
  res = _from_int_to_decimal(i, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec), "1410065407");
  DESTROY(str);
  res = _from_decimal_to_int(dec, &i_res);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(i, i_res);

  i = -2147483647;
  res = _from_int_to_decimal(i, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec), "-2147483647");
  DESTROY(str);
  res = _from_decimal_to_int(dec, &i_res);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(i, i_res);

  i = -124356;
  res = _from_int_to_decimal(i, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec), "-124356");
  DESTROY(str);
  res = _from_decimal_to_int(dec, &i_res);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(i, i_res);

  i = 2147483647;
  res = _from_int_to_decimal(i, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec), "2147483647");
  DESTROY(str);
  res = _from_decimal_to_int(dec, &i_res);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(i, i_res);

  // _from_int_to_decimal(-0, &dec);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec), "-0");
  // DESTROY(str);
  // _from_int_to_decimal(0, &dec);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec), "0");
  // DESTROY(str);
  // _from_int_to_decimal(01, &dec);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec), "1");
  // DESTROY(str);

  // _from_int_to_decimal(-2147483648, &dec);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec), "-2147483648");
  // DESTROY(str);
  // _from_int_to_decimal(2147483647, &dec);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec), "2147483647");
  // DESTROY(str);
  // _from_int_to_decimal(999999999, &dec);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec), "999999999");
  // DESTROY(str);
  // _from_int_to_decimal(34328947, &dec);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec), "34328947");
  // DESTROY(str);
  // _from_int_to_decimal(12857, &dec);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec), "12857");
  // DESTROY(str);
}
END_TEST

START_TEST(test__from_float_to_decimal) {
  //
  /*
  -3.402823E+38 is out of range of the Decimal type.
  Converted the Single value -3E+10 to -30000000000.
  Converted the Single value -1093.54 to -1093.54.
  Converted the Single value 0 to 0.
  Converted the Single value 0.001 to 0.001.
  Converted the Single value 1034.23 to 1034.23.
  Converted the Single value -0.1919192 to -0.1919192.
  Converted the Single value 100500 to 100500.
  Converted the Single value 1.234568 to 1.234568.
  Converted the Single value -10 to -10.
  Converted the Single value 10 to 10.
  Converted the Single value -1E-11 to -0.000000000010.
  3.402823E+38 is out of range of the Decimal type.
  */

  char *str;
  int res;
  float fl, fl_res;
  _decimal dec = {{0, 0, 0, 0x00000000}, _NORMAL_VALUE};
  _decimal zero = {{0, 0, 0, 0x00000000}, _NORMAL_VALUE};

  fl = -3.402823E+38;
  res = _from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(res, 1);
  res = _is_equal(dec, zero);
  ck_assert_int_eq(res, 0);

  fl = 3.402823E+38;
  res = _from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(res, 1);
  res = _is_equal(dec, zero);
  ck_assert_int_eq(res, 0);

  fl = 0;
  res = _from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec), "0.000000");
  DESTROY(str);
  res = _from_decimal_to_float(dec, &fl_res);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(fl, fl_res, 0.000001);

  fl = -3E+10;
  res = _from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec), "-30000000000");
  DESTROY(str);
  res = _from_decimal_to_float(dec, &fl_res);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(fl, fl_res, 0.000001);

  fl = -1093.54;
  res = _from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec), "-1093.540");
  DESTROY(str);
  res = _from_decimal_to_float(dec, &fl_res);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(fl, fl_res, 0.000001);

  fl = 0.001;
  res = _from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec), "0.001000000");
  DESTROY(str);
  res = _from_decimal_to_float(dec, &fl_res);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(fl, fl_res, 0.000001);

  fl = 1034.23;
  res = _from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec), "1034.230");
  DESTROY(str);
  res = _from_decimal_to_float(dec, &fl_res);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(fl, fl_res, 0.000001);

  fl = -0.1919192;
  res = _from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec), "-0.1919192");
  DESTROY(str);
  res = _from_decimal_to_float(dec, &fl_res);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(fl, fl_res, 0.000001);

  fl = 100500;
  res = _from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec), "100500.0");
  DESTROY(str);
  res = _from_decimal_to_float(dec, &fl_res);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(fl, fl_res, 0.000001);

  fl = 1.234568;
  res = _from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec), "1.234568");
  DESTROY(str);
  res = _from_decimal_to_float(dec, &fl_res);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(fl, fl_res, 0.000001);

  fl = 1.000005;
  res = _from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec), "1.000005");
  DESTROY(str);
  res = _from_decimal_to_float(dec, &fl_res);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(fl, fl_res, 0.000001);

  fl = 2.000005;
  res = _from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec), "2.000005");
  DESTROY(str);
  res = _from_decimal_to_float(dec, &fl_res);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(fl, fl_res, 0.000001);

  fl = -10;
  res = _from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec), "-10.00000");
  DESTROY(str);
  res = _from_decimal_to_float(dec, &fl_res);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(fl, fl_res, 0.000001);

  fl = 10;
  res = _from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec), "10.00000");
  DESTROY(str);
  res = _from_decimal_to_float(dec, &fl_res);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(fl, fl_res, 0.000001);
  ck_assert_double_eq(fl, fl_res);

  fl = 0.1234567;
  res = _from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec), "0.1234567");
  DESTROY(str);
  res = _from_decimal_to_float(dec, &fl_res);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(fl, fl_res, 0.000001);
  ck_assert_double_eq(fl, fl_res);

  fl = -1E-11;
  res = _from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(res, 0);
  ck_assert_str_eq(str = _from_decimal_to_string(dec),
                   "-0.00000000001000000");
  DESTROY(str);
  res = _from_decimal_to_float(dec, &fl_res);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(fl, fl_res, 0.000001);

  // res = _from_float_to_decimal(, &dec);
  // ck_assert_int_eq(res, -3E+10);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec), "-30000000000");
  // DESTROY(str);

  // res = _from_float_to_decimal(, &dec);
  // ck_assert_int_eq(res, -3E+10);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec), "-30000000000");
  // DESTROY(str);

  // _from_float_to_decimal(-0.0, &dec);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec),
  // "-0.000000000000000000000000000");
  // DESTROY(str);

  // _from_float_to_decimal(0.0, &dec);
  // ck_assert_int_eq(res, 0);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec),
  //                  "0.000000000000000000000000000");
  // DESTROY(str);

  // res = _from_float_to_decimal(1e-28, &dec);
  // ck_assert_int_eq(res, 0);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec),
  //                  "0.0000000000000000000000000001");
  // DESTROY(str);

  // res = _from_float_to_decimal(-1e-28, &dec);
  // ck_assert_int_eq(res, 1);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec),
  //                  "-0.0000000000000000000000000001");
  // DESTROY(str);

  // res = _from_float_to_decimal(7.899e28, &dec);
  // ck_assert_int_eq(res, 0);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec),
  //                  "78989999405433772776481619968");
  // DESTROY(str);
  // res = _from_float_to_decimal(-7.899e28, &dec);
  // ck_assert_int_eq(res, 0);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec),
  //                  "-78989999405433772776481619968");
  // DESTROY(str);

  // res = _from_float_to_decimal(80e29, &dec);
  // ck_assert_int_eq(res, 1);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec), "0");
  // DESTROY(str);

  // res = _from_float_to_decimal(-10e29, &dec);
  // ck_assert_int_eq(res, 1);
  // // ck_assert_int_eq(dec.value_type, _NEGATIVE_INFINITY);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec), "0");
  // DESTROY(str);

  // res = _from_float_to_decimal(12857, &dec);
  // ck_assert_int_eq(res, 0);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec),
  //                  "12857.00000000000000000000000");
  // DESTROY(str);

  // res = _from_float_to_decimal(NAN, &dec);
  // ck_assert_int_eq(res, 0);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec), "NAN");
  // DESTROY(str);
  // res = _from_float_to_decimal(INFINITY, &dec);
  // ck_assert_int_eq(res, 0);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec), "INFINITY");
  // DESTROY(str);
  // res = _from_float_to_decimal(-INFINITY, &dec);
  // ck_assert_int_eq(res, 0);
  // ck_assert_str_eq(str = _from_decimal_to_string(dec),
  // "NEGATIVE_INFINITY"); DESTROY(str);
}
END_TEST

START_TEST(test__from_decimal_to_int) {
  //
  char *str;
  int res;

  _decimal dec1 = {{0, 0xffffffff, 0, 0x000a0000}, _NORMAL_VALUE};
  _decimal dec2 = {{0, 0xffffffff, 0, 0x800a0000}, _NORMAL_VALUE};
  _decimal dec3 = {{0, 0, 0, 0x00000000}, _NORMAL_VALUE};
  _decimal dec4 = {{0, 0, 0, 0x80000000}, _NORMAL_VALUE};
  _decimal dec5 = {{0, 0, 0, 0x00010000}, _NORMAL_VALUE};
  _decimal dec6 = {{0, 0, 0, 0x80010000}, _NORMAL_VALUE};
  _decimal dec7 = {{0xffffffff, 0, 0, 0x00000000}, _NORMAL_VALUE};
  _decimal dec8 = {{1, 1, 0, 0x00040000}, _NORMAL_VALUE};
  _decimal dec9 = {{1, 1, 0, 0x80040000}, _NORMAL_VALUE};

  ck_assert_str_eq(str = _from_decimal_to_string(dec1),
                   "1844674406.9414584320");
  DESTROY(str);
  _from_decimal_to_int(dec1, &res);
  ck_assert_int_eq(res, 1844674406);

  ck_assert_str_eq(str = _from_decimal_to_string(dec2),
                   "-1844674406.9414584320");
  DESTROY(str);
  _from_decimal_to_int(dec2, &res);
  ck_assert_int_eq(res, -1844674406);

  ck_assert_str_eq(str = _from_decimal_to_string(dec3), "0");
  DESTROY(str);
  _from_decimal_to_int(dec3, &res);
  ck_assert_int_eq(res, 0);

  ck_assert_str_eq(str = _from_decimal_to_string(dec4), "-0");
  DESTROY(str);
  _from_decimal_to_int(dec4, &res);
  ck_assert_int_eq(res, -0);

  ck_assert_str_eq(str = _from_decimal_to_string(dec5), "0.0");
  DESTROY(str);
  _from_decimal_to_int(dec5, &res);
  ck_assert_int_eq(res, 0);

  ck_assert_str_eq(str = _from_decimal_to_string(dec6), "-0.0");
  DESTROY(str);
  _from_decimal_to_int(dec6, &res);
  ck_assert_int_eq(res, -0);

  // CONVERTING ERROR
  ck_assert_str_eq(str = _from_decimal_to_string(dec7), "4294967295");
  DESTROY(str);
  ck_assert_int_eq(_from_decimal_to_int(dec7, &res), 1);

  ck_assert_str_eq(str = _from_decimal_to_string(dec8), "429496.7297");
  DESTROY(str);
  _from_decimal_to_int(dec8, &res);
  ck_assert_int_eq(res, 429496);

  ck_assert_str_eq(str = _from_decimal_to_string(dec9), "-429496.7297");
  DESTROY(str);
  _from_decimal_to_int(dec9, &res);
  ck_assert_int_eq(res, -429496);
}
END_TEST

START_TEST(test__from_decimal_to_float) {
  //
  char *str;
  float res;
  int result;

  _decimal dec1 = {{3569467, 0, 0, 0x00000000}, _NORMAL_VALUE};
  _decimal dec2 = {{12345678, 0, 0, 0x80040000}, _NORMAL_VALUE};
  _decimal dec4 = {{0xb0400000, 0xe8dfebfd, 0x661d8d, 0x801c0000},
                      _NORMAL_VALUE};
  _decimal dec5 = {{1, 1, 0, 0x00040000}, _NORMAL_VALUE};
  _decimal dec6 = {{1, 1, 0, 0x80040000}, _NORMAL_VALUE};

  ck_assert_str_eq(str = _from_decimal_to_string(dec1), "3569467");
  DESTROY(str);
  result = _from_decimal_to_float(dec1, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(res, 3569467.000000);

  ck_assert_str_eq(str = _from_decimal_to_string(dec2), "-1234.5678");
  DESTROY(str);
  result = _from_decimal_to_float(dec2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(res, -1234.567749);

  ck_assert_str_eq(str = _from_decimal_to_string(dec5), "429496.7297");
  DESTROY(str);
  result = _from_decimal_to_float(dec5, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(res, 429496.7297);

  ck_assert_str_eq(str = _from_decimal_to_string(dec6), "-429496.7297");
  DESTROY(str);
  result = _from_decimal_to_float(dec6, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(res, -429496.7297);

  ck_assert_str_eq(str = _from_decimal_to_string(dec4),
                   "-0.0123450000000000000000000000");
  DESTROY(str);
  result = _from_decimal_to_float(dec4, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(res, -0.012345);
}
END_TEST

TCase *decimal_convrt_tests(void) {
  TCase *t_case = tcase_create("Convert_functions");

  tcase_add_test(t_case, test__from_int_to_decimal);
  tcase_add_test(t_case, test__from_float_to_decimal);
  tcase_add_test(t_case, test__from_decimal_to_int);
  tcase_add_test(t_case, test__from_decimal_to_float);

  return t_case;
}
