/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* Button poll interval, in msec (used to be the button on/off interval) */
#define SLEEP_TIME_MS   50

/* The devicetree node identifier for the "led5180" alias. */
#define LED0_NODE DT_ALIAS(led5180)

/* The devicetree node identifier for the "button5180" alias. */
#define BUTTON0_NODE DT_ALIAS(button5180)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(BUTTON0_NODE, gpios);

int main(void)
{
	int ret;
	bool led_state = false;
	bool button_was_pressed = false;

	// Hardware failures
	if (!gpio_is_ready_dt(&led) || !gpio_is_ready_dt(&button)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
	if (ret < 0) {
		return 0;
	}

	while (1) {
		bool button_is_pressed = gpio_pin_get_dt(&button) > 0;

		if (button_is_pressed && !button_was_pressed) {
			gpio_pin_toggle_dt(&led);
			led_state = !led_state;
			printf("LED state: %s\n", led_state ? "ON" : "OFF");
		}
		button_was_pressed = button_is_pressed;

		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
