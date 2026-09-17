#include <zephyr/ztest.h>
#include <zephyr/devicetree.h>
#include "bme280_temp.h"

/*
 * 8.2: sanity-check that the BME280 devicetree node is set up correctly.
 * No physical BME280 is attached during this test, so these checks only
 * touch devicetree metadata and the I2C1 bus controller's own init state
 * -- never a real sensor register.
 */

ZTEST(bme280_dt_test_suite, test_bme280_node_enabled)
{
	zassert_true(DT_NODE_HAS_STATUS(DT_NODELABEL(bme280), okay),
		     "bme280 devicetree node is missing or not status = \"okay\"");
}

ZTEST(bme280_dt_test_suite, test_bme280_compatible)
{
	zassert_true(DT_NODE_HAS_COMPAT(DT_NODELABEL(bme280), i2c_device),
		     "bme280 node compatible should be \"i2c-device\"");
}

ZTEST(bme280_dt_test_suite, test_bme280_i2c_address)
{
	zassert_equal(DT_REG_ADDR(DT_NODELABEL(bme280)), 0x77,
		      "bme280 I2C address should be 0x77");
}

ZTEST(bme280_dt_test_suite, test_bme280_i2c_bus_ready)
{
	zassert_true(device_is_ready(bme280.bus),
		     "i2c1 bus controller for the bme280 node is not ready");
}

/*
 * No physical sensor is attached, so instead of reading real calibration
 * and ADC registers, these feed known values straight into the pure
 * compensation function to sanity-check its math.
 */
ZTEST(bme280_dt_test_suite, test_compensate_temperature_zero_coeffs)
{
	int32_t t_fine;
	int32_t temperature = bme280_compensate_temperature(519888, 27504, 0, 0, &t_fine);

	zassert_equal(t_fine, 0, "t_fine should be 0 when dig_T2 and dig_T3 are 0");
	zassert_equal(temperature, 0, "temperature should be 0 when dig_T2 and dig_T3 are 0");
}

ZTEST(bme280_dt_test_suite, test_compensate_temperature_known_value)
{
	int32_t t_fine;
	int32_t temperature = bme280_compensate_temperature(800, 0, 2048, 0, &t_fine);

	zassert_equal(t_fine, 100, "t_fine mismatch for known mocked calibration values");
	zassert_equal(temperature, 2, "temperature mismatch for known mocked calibration values");
}

ZTEST_SUITE(bme280_dt_test_suite, NULL, NULL, NULL, NULL, NULL);
