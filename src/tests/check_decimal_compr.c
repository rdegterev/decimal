#include "check_decimal.h"

START_TEST(test__is_less) {
  //
  _decimal dec1 = {{0x0, 0x1, 0x0, ((1u << 19) + (1u << 31))},
                      _NORMAL_VALUE};  // -42.94967296
  _decimal dec2 = {{0x0, 0x1, 0x0, 1u << 19},
                      _NORMAL_VALUE};  // 42.94967296
  _decimal dec3 = {{0x0, 0x11, 0x0, 1u << 19},
                      _NORMAL_VALUE};  // 730.14444032
  _decimal dec4 = {{0x0, 0x1, 0x0, ((1u << 20) + (1u << 31))},
                      _NORMAL_VALUE};  // -0.0000004294967296
  _decimal dec5 = {{0x0, 0x0, 0x1, 1u << 19},
                      _NORMAL_VALUE};  // 184467440737.09551616
  _decimal dec6 = {{0x0, 0x0, 0x1, 1u << 20},
                      _NORMAL_VALUE};  // 1844.6744073709551616
  _decimal dec7 = {{1, 1, 0, 0x00040000}, _NORMAL_VALUE};  // 429496.7297
  _decimal dec8 = {{0x68db8, 0, 0, 0}, _NORMAL_VALUE};     // 429496
  _decimal dec9 = {{5, 0, 0, 0x80010000}, _NORMAL_VALUE};  // -0,5
  _decimal dec10 = {{MAXVALUE - 1, MAXVALUE, MAXVALUE, 0x00000000},
                       _NORMAL_VALUE};  // 79228162514264337593543950334
  _decimal dec11 = {{MAXVALUE, MAXVALUE, MAXVALUE, 0x00000000},
                       _NORMAL_VALUE};  // 79228162514264337593543950335

  _decimal decneginf = {{0x0, 0x1, 0x0, 1u << 19}, _NEGATIVE_INFINITY};
  _decimal decinf = {{0x0, 0x1, 0x0, 1u << 19}, _INFINITY};
  _decimal decnan = {{0x0, 0x1, 0x0, 1u << 19}, _NAN};

  ck_assert_int_eq(_is_less(dec1, dec2),
                   TRUE);  // dec1 отрицательное, dec2 положительные
  ck_assert_int_eq(_is_less(dec2, dec1),
                   FALSE);  // dec2 положительные, dec1 отрицательное
  ck_assert_int_eq(_is_less(dec2, dec3), TRUE);    // dec2 меньше dec3
  ck_assert_int_eq(_is_less(dec3, dec2), FALSE);   // dec2 меньше dec3
  ck_assert_int_eq(_is_less(dec3, dec2), FALSE);   // dec2 меньше dec3
  ck_assert_int_eq(_is_less(dec1, decinf), TRUE);  // dec1 меньше INF
  ck_assert_int_eq(_is_less(dec1, decneginf),
                   FALSE);  // dec1 не меньше NEGATIVE INF
  ck_assert_int_eq(_is_less(decneginf, decinf),
                   TRUE);  // NEGATIVE INF меньше INF
  ck_assert_int_eq(_is_less(decnan, dec1),
                   FALSE);  // NAN всегда FALSE
  ck_assert_int_eq(_is_less(dec6, dec5),
                   TRUE);  // dec6 меньше dec5 по положению точки
  ck_assert_int_eq(
      _is_less(dec1, dec4),
      TRUE);  // dec1 меньше dec4 по положению точки оба отрицательные
  ck_assert_int_eq(_is_less(dec8, dec7), TRUE);    // dec8 меньше dec7
  ck_assert_int_eq(_is_less(dec10, dec11), TRUE);  // dec10 меньше dec11
  ck_assert_int_eq(_is_less(dec11, dec10), FALSE);  // dec10 меньше dec11
  ck_assert_int_eq(_is_less(dec11, dec11), FALSE);  // dec11 равен dec11
  ck_assert_int_eq(_is_less(dec9, dec9), FALSE);    // dec9 равен dec9
}
END_TEST

START_TEST(test__is_less_or_equal) {
  //
  _decimal dec1 = {{0x0, 0x1, 0x0, ((1u << 19) + (1u << 31))},
                      _NORMAL_VALUE};  // -42.94967296
  _decimal dec2 = {{0x0, 0x1, 0x0, 1u << 19},
                      _NORMAL_VALUE};  // 42.94967296
  _decimal dec3 = {{0x0, 0x11, 0x0, 1u << 19},
                      _NORMAL_VALUE};  // 730.14444032
  _decimal dec4 = {{0x0, 0x1, 0x0, ((1u << 20) + (1u << 31))},
                      _NORMAL_VALUE};  // -0.0000004294967296
  _decimal dec5 = {{0x0, 0x0, 0x1, 1u << 19},
                      _NORMAL_VALUE};  // 184467440737.09551616
  _decimal dec6 = {{0x0, 0x0, 0x1, 1u << 20},
                      _NORMAL_VALUE};  // 1844.6744073709551616

  _decimal decneginf = {{0x0, 0x1, 0x0, 1u << 19}, _NEGATIVE_INFINITY};
  _decimal decinf = {{0x0, 0x1, 0x0, 1u << 19}, _INFINITY};
  _decimal decnan = {{0x0, 0x1, 0x0, 1u << 19}, _NAN};

  ck_assert_int_eq(_is_less_or_equal(dec1, dec2),
                   TRUE);  // dec1 отрицательное, dec2 положительные
  ck_assert_int_eq(_is_less_or_equal(dec1, dec1),
                   TRUE);  // dec1 == dec1 отрицательное
  ck_assert_int_eq(_is_less_or_equal(dec2, dec2),
                   TRUE);  // dec2 == dec2 положительные
  ck_assert_int_eq(_is_less_or_equal(dec2, dec3),
                   TRUE);  // dec3 > dec2
  ck_assert_int_eq(_is_less_or_equal(dec1, decneginf),
                   FALSE);  // dec1 не меньше NEGATIVE INF
  ck_assert_int_eq(_is_less_or_equal(dec6, dec5),
                   TRUE);  // dec6 меньше dec5 по положению точки
  ck_assert_int_eq(
      _is_less_or_equal(dec1, dec4),
      TRUE);  // dec1 меньше dec4 по положению точки оба отрицательные
  ck_assert_int_eq(_is_less_or_equal(decneginf, decinf),
                   TRUE);  // NEGATIVE INF меньше INF
  ck_assert_int_eq(_is_less_or_equal(decinf, decinf),
                   TRUE);  // INF равен INF
  ck_assert_int_eq(_is_less_or_equal(decneginf, decneginf),
                   TRUE);  // NEGATIVE INF равен NEGATIVE INF
  ck_assert_int_eq(_is_less_or_equal(decnan, decnan),
                   FALSE);  // NAN всегда FALSE
  ck_assert_int_eq(_is_less_or_equal(dec1, decnan),
                   FALSE);  // NAN всегда FALSE
  ck_assert_int_eq(_is_less_or_equal(decnan, decinf),
                   FALSE);  // NAN всегда FALSE
}
END_TEST

START_TEST(test__is_greater) {
  //
  _decimal dec1 = {{0x0, 0x1, 0x0, ((1u << 19) + (1u << 31))},
                      _NORMAL_VALUE};  // -42.94967296
  _decimal dec2 = {{0x0, 0x1, 0x0, 1u << 19},
                      _NORMAL_VALUE};  // 42.94967296
  _decimal dec3 = {{0x0, 0x11, 0x0, 1u << 19},
                      _NORMAL_VALUE};  // 730.14444032
  _decimal dec4 = {{0x0, 0x1, 0x0, ((1u << 20) + (1u << 31))},
                      _NORMAL_VALUE};  // -0.0000004294967296
  _decimal dec5 = {{0x0, 0x0, 0x1, 1u << 19},
                      _NORMAL_VALUE};  // 184467440737.09551616
  _decimal dec6 = {{0x0, 0x0, 0x1, 1u << 20},
                      _NORMAL_VALUE};  // 1844.6744073709551616
  _decimal dec7 = {{1, 1, 0, 0x00040000}, _NORMAL_VALUE};  // 429496.7297
  _decimal dec8 = {{0x68db8, 0, 0, 0}, _NORMAL_VALUE};     // 429496

  _decimal decneginf = {{0x0, 0x1, 0x0, 1u << 19}, _NEGATIVE_INFINITY};
  _decimal decinf = {{0x0, 0x1, 0x0, 1u << 19}, _INFINITY};
  _decimal decnan = {{0x0, 0x1, 0x0, 1u << 19}, _NAN};

  ck_assert_int_eq(_is_greater(dec1, dec2),
                   FALSE);  // dec1 отрицательное, dec2 положительные
  ck_assert_int_eq(_is_greater(dec2, dec1),
                   TRUE);  // dec2 положительные, dec1 отрицательное
  ck_assert_int_eq(_is_greater(dec2, dec3), FALSE);  // dec2 меньше dec3
  ck_assert_int_eq(_is_greater(dec3, dec2), TRUE);  // dec2 меньше dec3
  ck_assert_int_eq(_is_greater(dec3, dec2), TRUE);  // dec2 меньше dec3
  ck_assert_int_eq(_is_greater(dec1, decinf), FALSE);  // dec1 меньше INF
  ck_assert_int_eq(_is_greater(dec1, decneginf),
                   TRUE);  // dec1 не меньше NEGATIVE INF
  ck_assert_int_eq(_is_greater(decneginf, decinf),
                   FALSE);  // NEGATIVE INF меньше INF
  ck_assert_int_eq(_is_greater(decnan, dec1),
                   FALSE);  // NAN всегда FALSE
  ck_assert_int_eq(_is_greater(dec6, dec5),
                   FALSE);  // dec6 меньше dec5 по положению точки
  ck_assert_int_eq(
      _is_greater(dec1, dec4),
      FALSE);  // dec1 меньше dec4 по положению точки оба отрицательные
  ck_assert_int_eq(_is_greater(dec7, dec8),
                   TRUE);  // dec7 большн dec8
}
END_TEST

START_TEST(test__is_greater_or_equal) {
  //
  //
  _decimal dec1 = {{0x0, 0x1, 0x0, ((1u << 19) + (1u << 31))},
                      _NORMAL_VALUE};  // -42.94967296
  _decimal dec2 = {{0x0, 0x1, 0x0, 1u << 19},
                      _NORMAL_VALUE};  // 42.94967296
  _decimal dec4 = {{0x0, 0x1, 0x0, ((1u << 20) + (1u << 31))},
                      _NORMAL_VALUE};  // -0.0000004294967296
  _decimal dec5 = {{0x0, 0x0, 0x1, 1u << 19},
                      _NORMAL_VALUE};  // 184467440737.09551616
  _decimal dec6 = {{0x0, 0x0, 0x1, 1u << 20},
                      _NORMAL_VALUE};  // 1844.6744073709551616

  _decimal decneginf = {{0x0, 0x1, 0x0, 1u << 19}, _NEGATIVE_INFINITY};
  _decimal decinf = {{0x0, 0x1, 0x0, 1u << 19}, _INFINITY};
  _decimal decnan = {{0x0, 0x1, 0x0, 1u << 19}, _NAN};

  ck_assert_int_eq(_is_greater_or_equal(dec1, dec2),
                   FALSE);  // dec1 отрицательное, dec2 положительные
  ck_assert_int_eq(_is_greater_or_equal(dec1, dec1),
                   TRUE);  // dec1 == dec1 отрицательное
  ck_assert_int_eq(_is_greater_or_equal(dec2, dec2),
                   TRUE);  // dec2 == dec2 положительные
  ck_assert_int_eq(_is_greater_or_equal(dec1, decneginf),
                   TRUE);  // dec1 не меньше NEGATIVE INF
  ck_assert_int_eq(_is_greater_or_equal(dec6, dec5),
                   FALSE);  // dec6 меньше dec5 по положению точки
  ck_assert_int_eq(
      _is_greater_or_equal(dec1, dec4),
      FALSE);  // dec1 меньше dec4 по положению точки оба отрицательные
  ck_assert_int_eq(_is_greater_or_equal(decneginf, decinf),
                   FALSE);  // NEGATIVE INF меньше INF
  ck_assert_int_eq(_is_greater_or_equal(decinf, decinf),
                   TRUE);  // INF равен INF
  ck_assert_int_eq(_is_greater_or_equal(decneginf, decneginf),
                   TRUE);  // NEGATIVE INF равен NEGATIVE INF
  ck_assert_int_eq(_is_greater_or_equal(decnan, decnan),
                   FALSE);  // NAN всегда FALSE
  ck_assert_int_eq(_is_greater_or_equal(dec1, decnan),
                   FALSE);  // NAN всегда FALSE
  ck_assert_int_eq(_is_greater_or_equal(decnan, decinf),
                   FALSE);  // NAN всегда FALSE
}
END_TEST

START_TEST(test__is_equal) {
  //
  char *str;
  _decimal dec1 = {{5, 0xffffffff, 1, 0x000a0000}, _NORMAL_VALUE};
  _decimal dec2 = {{55, 1, 0, 0x00020000}, _NORMAL_VALUE};
  _decimal dec4 = {{55, 1, 0, 0x80020000}, _NORMAL_VALUE};
  _decimal dec5 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00020000},
                      _NORMAL_VALUE};
  _decimal dec6 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00050000},
                      _NORMAL_VALUE};

  _decimal dec9 = {{0, 0, 0, 0x00000000}, _INFINITY};
  _decimal dec10 = {{0, 1, 0, 0x00000000}, _INFINITY};
  _decimal dec11 = {{0, 1, 0, 0x00000000}, _NORMAL_VALUE};
  _decimal dec13 = {{0, 0, 0, 0x00000000}, _NEGATIVE_INFINITY};
  _decimal dec14 = {{0, 0, 0, 0x00000000}, _NORMAL_VALUE};
  _decimal dec15 = {{0, 0, 0, 0x00110000}, _NORMAL_VALUE};
  _decimal dec16 = {{0, 0, 0, 0x80000000}, _NORMAL_VALUE};
  _decimal dec17 = {{0, 0, 0, 0x80050000}, _NORMAL_VALUE};
  _decimal dec18 = {{0, 0, 0, 0x00000000}, _NAN};
  _decimal dec19 = {{0, 1, 0, 0x00000000}, _NAN};
  _decimal dec20 = {{0, 0, 0, 0x00000000}, _NORMAL_VALUE};
  _decimal dec21 = {{0, 0, 0, 0x80000000}, _NORMAL_VALUE};
  _decimal dec22 = {{1, 0, 0, 0x00010000}, _NORMAL_VALUE};
  _decimal dec23 = {{100000, 0, 0, 0x00060000}, _NORMAL_VALUE};
  _decimal dec24 = {{1, 0, 0, 0x80010000}, _NORMAL_VALUE};
  _decimal dec25 = {{100000, 0, 0, 0x80060000}, _NORMAL_VALUE};

  ck_assert_int_eq(_is_equal(dec1, dec2),
                   FALSE);  // одинаковые числа с разными знаками
  ck_assert_int_eq(_is_equal(dec2, dec4), FALSE);  // разные числа
  ck_assert_int_eq(_is_equal(dec1, dec1), TRUE);  // число само с собой
  ck_assert_int_eq(_is_equal(dec5, dec6), FALSE);  // разная разрядность
  ck_assert_int_eq(_is_equal(dec1, dec10), FALSE);   // NORM != INF
  ck_assert_int_eq(_is_equal(dec9, dec10), TRUE);    // +INF == +INF
  ck_assert_int_eq(_is_equal(dec18, dec19), FALSE);  // NAN != NAN
  ck_assert_int_eq(_is_equal(dec10, dec11), FALSE);  // INF != NORM
  ck_assert_int_eq(_is_equal(dec20, dec21), TRUE);   // 0 == -0
  ck_assert_int_eq(_is_equal(dec13, dec14), FALSE);  // NEGINF != NORM
  ck_assert_int_eq(_is_equal(dec15, dec16), TRUE);   // 0.000 == -0
  ck_assert_int_eq(_is_equal(dec16, dec17), TRUE);   // 0.000 == -0.000

  ck_assert_str_eq(str = _from_decimal_to_string(dec22), "0.1");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(dec23), "0.100000");
  DESTROY(str);
  ck_assert_int_eq(_is_equal(dec22, dec23), TRUE);  // 0.1 == 0.100000

  ck_assert_str_eq(str = _from_decimal_to_string(dec24), "-0.1");
  DESTROY(str);
  ck_assert_str_eq(str = _from_decimal_to_string(dec25), "-0.100000");
  DESTROY(str);
  ck_assert_int_eq(_is_equal(dec24, dec25), TRUE);  // -0.1 == -0.100000
}
END_TEST

START_TEST(test__is_not_equal) {
  //
  char *str;
  _decimal dec1 = {{5, 0xffffffff, 1, 0x000a0000}, _NORMAL_VALUE};
  _decimal dec2 = {{55, 1, 0, 0x00020000}, _NORMAL_VALUE};
  _decimal dec5 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00020000},
                      _NORMAL_VALUE};
  _decimal dec6 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00050000},
                      _NORMAL_VALUE};
  _decimal dec9 = {{0, 0, 0, 0x00000000}, _INFINITY};
  _decimal dec10 = {{0, 1, 0, 0x00000000}, _INFINITY};
  _decimal dec11 = {{0, 1, 0, 0x00000000}, _NORMAL_VALUE};

  _decimal dec13 = {{0, 0, 0, 0x00000000}, _NEGATIVE_INFINITY};
  _decimal dec14 = {{0, 0, 0, 0x00000000}, _NORMAL_VALUE};
  _decimal dec15 = {{0, 0, 0, 0x00110000}, _NORMAL_VALUE};
  _decimal dec16 = {{0, 0, 0, 0x80000000}, _NORMAL_VALUE};
  _decimal dec17 = {{0, 0, 0, 0x80050000}, _NORMAL_VALUE};
  _decimal dec18 = {{0, 0, 0, 0x00000000}, _NAN};
  _decimal dec19 = {{0, 1, 0, 0x00000000}, _NAN};
  _decimal dec20 = {{7297, 0, 0, 0x00040000}, _NORMAL_VALUE};

  ck_assert_int_eq(_is_not_equal(dec1, dec2), TRUE);  // разные числа
  ck_assert_int_eq(_is_not_equal(dec1, dec1),
                   FALSE);  // число само с собой
  ck_assert_int_eq(_is_not_equal(dec5, dec6), TRUE);  // разная разрядность
  ck_assert_int_eq(_is_not_equal(dec1, dec10), TRUE);    // NORM != INF
  ck_assert_int_eq(_is_not_equal(dec9, dec10), FALSE);   // +INF == +INF
  ck_assert_int_eq(_is_not_equal(dec18, dec19), TRUE);   // NAN != NAN
  ck_assert_int_eq(_is_not_equal(dec10, dec11), TRUE);   // INF != NORM
  ck_assert_int_eq(_is_not_equal(dec13, dec14), TRUE);   // NEGINF != NORM
  ck_assert_int_eq(_is_not_equal(dec15, dec16), FALSE);  // 0.000 == -0
  ck_assert_int_eq(_is_not_equal(dec16, dec17), FALSE);  // 0.000 == -0.000

  ck_assert_str_eq(str = _from_decimal_to_string(dec20), "0.7297");
  DESTROY(str);
  ck_assert_int_eq(_is_not_equal(dec14, dec20), TRUE);  // 0 != 0.7297
}
END_TEST

TCase *decimal_compr_tests(void) {
  TCase *t_case = tcase_create("Compare_functions");

  tcase_add_test(t_case, test__is_less);
  tcase_add_test(t_case, test__is_less_or_equal);
  tcase_add_test(t_case, test__is_greater);
  tcase_add_test(t_case, test__is_greater_or_equal);
  tcase_add_test(t_case, test__is_equal);
  tcase_add_test(t_case, test__is_not_equal);

  return t_case;
}
