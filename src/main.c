
#include "s21_decimal.h"

int main() {
  // s21_decimal ten = {{10, 0, 0, 0}, S21_NORMAL_VALUE};
  // s21_decimal five = {{5, 0, 0, 0}, S21_NORMAL_VALUE};
  s21_decimal tmp = {{3589934592, 705032702, 1, 0}, S21_NORMAL_VALUE};
  // s21_decimal dec0 = {{2884901888, 1410065405, 2, 0x0},
  //                     S21_NORMAL_VALUE};  // 0.00000000
  // s21_decimal dec1 = {{0x0, 0x1, 0x0, ((1u << 19) + (1u << 31))},
  //                     S21_NORMAL_VALUE};  // -42.94967296 42,94967296
  // s21_decimal dec2 = {{0x0, 0x1, 0x0, 1u << 19},
  //                     S21_NORMAL_VALUE};  // 42.94967296
  // s21_decimal dec3 = {{0x0, 0x11, 0x0, 1u << 19},
  //                     S21_NORMAL_VALUE};  // 730.14444032 730,14444032
  // s21_decimal dec4 = {{0x0, 0x1, 0x0, ((1u << 20) + (1u << 31))},
  //                     S21_NORMAL_VALUE};  // -0.0000004294967296
  // s21_decimal dec5 = {{0x0, 0x0, 0x1, 1u << 19},
  //                     S21_NORMAL_VALUE};  // 184467440737.09551616
  // s21_decimal dec6 = {{0x0, 0x0, 0x1, 1u << 20},
  //                     S21_NORMAL_VALUE};  // 1844.6744073709551616
  // s21_decimal dec7 = {{MAXVALUE, 0, 0, 0x00000000},
  //                     S21_NORMAL_VALUE};                         //
  //                     4294967295
  // s21_decimal dec8 = {{1, 0, 0, 0x00000000}, S21_NORMAL_VALUE};  // 1
  // s21_decimal dec9 = {{MAXVALUE, MAXVALUE, 0, 0x00000000},
  //                     S21_NORMAL_VALUE};  // 18446744073709551615
  // s21_decimal dec10 = {{MAXVALUE, MAXVALUE, MAXVALUE, 0x00000000},
  //                      S21_NORMAL_VALUE};  // 79228162514264337593543950335

  // s21_decimal dec11 = {{0x2021, 0, 0, 0x00040000}, S21_NORMAL_VALUE};  //
  // 0,8225 s21_decimal dec12 = {{0x2022, 0, 0, 0x00040000}, S21_NORMAL_VALUE};
  // // 0,8226 s21_decimal dec13 = {{2, 0, 0, 0}, S21_NORMAL_VALUE}; // 2

  // s21_decimal dec17 = {{1, 1, 0, 0x00040000}, S21_NORMAL_VALUE};  //
  // 429496.7297 s21_decimal dec18 = {{429496, 0, 0, 0}, S21_NORMAL_VALUE}; //
  // 429496

  // s21_decimal dec19 = {{1, 1, 0, 0x80040000},
  //                      S21_NORMAL_VALUE};  // -429496.7297 -429496,7297
  // s21_decimal dec20 = {{429496, 0, 0, 0x80000000},
  //                      S21_NORMAL_VALUE};  // -429496
  // s21_decimal dec21 = {{MAXVALUE, MAXVALUE, MAXVALUE, 0x80000000},
  //                      S21_NORMAL_VALUE};  // -79228162514264337593543950335
  s21_decimal dec23 = {{MAXVALUE, MAXVALUE, 0, 0},
                       S21_NORMAL_VALUE};  // 1844674407370955.1615
  // s21_decimal dec24 = {{10, 0, 0, 0}, S21_NORMAL_VALUE};  // 10
  // s21_decimal dec25 = {{3, 0, 0, 0}, S21_NORMAL_VALUE};   // 3
  // s21_decimal dec26 = {{MAXVALUE - 1, MAXVALUE - 2, MAXVALUE - 3, 3 << 19},
  //                      S21_NORMAL_VALUE};  // 79228.162458924105363825360894
  // s21_decimal dec27 = {{MAXVALUE, 100000, 0, 0x000E0000},
  //                      S21_NORMAL_VALUE};  // 4.29501024567295
  // s21_decimal zero = {{0, 0, 0, 0}, S21_NORMAL_VALUE};
  // s21_from_float_to_decimal(x, &test);
  // float x = -123.4567;
  s21_decimal test1 = s21_sub(tmp, dec23);
  print_dec(test1);
  printf("\n%d_____%s\n", s21_is_positive(zero),
         s21_from_decimal_to_string(test1));
  // printf("%d\n", x);

  // unsigned int mask = 0x80000000;
  // dec.bits[3] = dec.bits[3] ^ mask;
  return 0;
}

/** Выводит на экран десятичное, шестнадцатеричное и двоичное представление
 * массива bits
 */
void print_dec(s21_decimal dec) {
  char a[4][32] = {0};

  for (int j = 0; j < 4; j++) {
    unsigned int tmp = dec.bits[j];
    for (int i = 0; tmp > 0; i++) {
      a[j][i] = tmp % 2;
      tmp = tmp / 2;
    }
  }
  for (int j = 0; j < 4; j++) {
    if (j == 0) printf("LOW  - ");
    if (j == 1) printf("MID  - ");
    if (j == 2) printf("HIGH - ");
    if (j == 3) printf("INFO - ");

    printf("%010u - %010x - ", dec.bits[j], dec.bits[j]);
    for (int i = 31; i >= 0; i--) {
      printf("%d ", a[j][i]);
    }
    printf("\n");
  }
}
