#include <zephyr/logging/log.h>
#include "sum_log.h"

LOG_MODULE_REGISTER(sum_log, CONFIG_LOG_DEFAULT_LEVEL);

int sum_log(int a, int b)
{
	int result = a + b;

	LOG_INF("Computing sum of %d and %d", a, b);
	LOG_HEXDUMP_INF(&a, sizeof(a), "input a");
	LOG_HEXDUMP_INF(&b, sizeof(b), "input b");
	LOG_INF("sum_log: %d + %d = %d", a, b, result);

	return result;
}
