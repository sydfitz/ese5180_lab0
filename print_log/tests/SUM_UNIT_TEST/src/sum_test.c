#include <zephyr/ztest.h>
#include "sum_log.h"

ZTEST(sum_log_test_suite, test_sum_log_basic)
{
	int result = sum_log(3, 5);

	zassert_equal(result, 8, "sum_log(3, 5) should be 8, got %d", result);
}

ZTEST(sum_log_test_suite, test_sum_log_negative)
{
	int result = sum_log(-3, -5);

	zassert_equal(result, -8, "sum_log(-3, -5) should be -8, got %d", result);
}

ZTEST(sum_log_test_suite, test_sum_log_zero)
{
	int result = sum_log(0, 0);

	zassert_equal(result, 0, "sum_log(0, 0) should be 0, got %d", result);
}

ZTEST_SUITE(sum_log_test_suite, NULL, NULL, NULL, NULL, NULL);
