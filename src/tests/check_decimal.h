#include <check.h>

#include "../decimal.h"

#ifndef SRC_TESTS_CHECK__DECIMAL_H_
#define SRC_TESTS_CHECK__DECIMAL_H_

TCase *decimal_arthm_tests(void);
TCase *decimal_compr_tests(void);
TCase *decimal_convrt_tests(void);
TCase *decimal_other_tests(void);
TCase *decimal_utils_tests(void);

#endif  // SRC_TESTS_CHECK__DECIMAL_H_
