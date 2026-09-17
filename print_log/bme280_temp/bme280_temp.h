#ifndef BME280_TEMP_H_
#define BME280_TEMP_H_

#include <stdint.h>
#include <zephyr/drivers/i2c.h>

#define BME280_REG_CALIB00   0x88
#define BME280_REG_CTRL_MEAS 0xF4
#define BME280_REG_TEMP_MSB  0xFA

extern const struct i2c_dt_spec bme280;

int32_t bme280_compensate_temperature(int32_t adc_T, uint16_t dig_T1,
				       int16_t dig_T2, int16_t dig_T3,
				       int32_t *t_fine);

void bme280_print_temperature(void);

#endif /* BME280_TEMP_H_ */
