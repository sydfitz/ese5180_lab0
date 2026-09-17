#include <zephyr/kernel.h>

#ifdef CONFIG_SUM_PRINT
#include "sum_printk.h"
#elif defined(CONFIG_SUM_LOG)
#include "sum_log.h"
#endif

#ifdef CONFIG_TEMP_READ
#include "bme280_temp.h"
#endif

int main(void)
{
#ifdef CONFIG_SUM_PRINT
	sum_printk(3, 5);
#elif defined(CONFIG_SUM_LOG)
	sum_log(3, 5);
#endif

#ifdef CONFIG_TEMP_READ
	bme280_print_temperature();
#endif

	return 0;
}
