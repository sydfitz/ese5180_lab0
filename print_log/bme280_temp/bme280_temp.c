#include <zephyr/kernel.h>
#include "bme280_temp.h"

/* BME280 register map from datasheet */
const struct i2c_dt_spec bme280 = I2C_DT_SPEC_GET(DT_NODELABEL(bme280));

int32_t bme280_compensate_temperature(int32_t adc_T, uint16_t dig_T1,
				       int16_t dig_T2, int16_t dig_T3,
				       int32_t *t_fine)
{
	int32_t var1, var2, T;

	var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
	var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) * ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) *
		((int32_t)dig_T3)) >> 14;
	*t_fine = var1 + var2;
	T = (*t_fine * 5 + 128) >> 8;

	return T;
}

void bme280_print_temperature(void)
{
	uint8_t calib[6];
	uint8_t ctrl_meas = 0x27; /* osrs_t=001, osrs_p=001, mode=11 (normal) */
	uint8_t temp_raw[3];
	uint16_t dig_T1;
	int16_t dig_T2, dig_T3;
	int32_t adc_T, t_fine, temperature;

	/* calibration data  starting at CALIB00 */
	i2c_burst_read_dt(&bme280, BME280_REG_CALIB00, calib, sizeof(calib));
	dig_T1 = (uint16_t)(calib[0] | (calib[1] << 8));
	dig_T2 = (int16_t)(calib[2] | (calib[3] << 8));
	dig_T3 = (int16_t)(calib[4] | (calib[5] << 8));

	/* I2C write to CTRL_MEAS */
	i2c_write_dt(&bme280, (uint8_t[]){ BME280_REG_CTRL_MEAS, ctrl_meas }, 2);

	/* buffer for time to write */
	k_msleep(100);

	/* I2C burst read to TEMP_MSB */
	i2c_burst_read_dt(&bme280, BME280_REG_TEMP_MSB, temp_raw, sizeof(temp_raw));
	adc_T = ((int32_t)temp_raw[0] << 12) | ((int32_t)temp_raw[1] << 4) | (temp_raw[2] >> 4);

	temperature = bme280_compensate_temperature(adc_T, dig_T1, dig_T2, dig_T3, &t_fine);

	printk("BME280 temperature: %.2f C\n", temperature / 100.0);
}
