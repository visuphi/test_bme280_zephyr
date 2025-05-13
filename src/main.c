/*
 * Copyright (c) 2024 ZHAW InES
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

static const struct device *const bme280_dev = DEVICE_DT_GET_ONE(bosch_bme280);


int main (void) {

	int rc;
	char buffer[32];
	struct sensor_value temperature;
	struct sensor_value humidity;
	struct sensor_value pressure;
	struct sensor_value gas_resistance;

	if (!device_is_ready(bme280_dev)) {
		LOG_ERR("BME280 not ready");
		return -ENODEV;
	}
	while (1) {

		rc = sensor_sample_fetch(bme280_dev);
		if (rc) {
			LOG_ERR("sensor_sample_fetch() bme280 failed: %d", rc);
		}

		rc = sensor_channel_get(bme280_dev, SENSOR_CHAN_AMBIENT_TEMP, &temperature);
		if (rc) {
			LOG_ERR("sensor_channel_get() bme280 temp failed: %d", rc);
		}

		rc = sensor_channel_get(bme280_dev, SENSOR_CHAN_HUMIDITY, &humidity);
		if (rc) {
			LOG_ERR("sensor_channel_get() bme280 hum failed: %d", rc);
		}

		rc = sensor_channel_get(bme280_dev, SENSOR_CHAN_PRESS, &pressure);
		if (rc) {
			LOG_ERR("sensor_channel_get() bme680 press failed: %d", rc);
		}

		sensor_channel_get(bme280_dev, SENSOR_CHAN_GAS_RES, &gas_resistance);
		if (rc) {
			LOG_ERR("sensor_channel_get() bme680 gas failed: %d", rc);
		}

		snprintf(buffer, sizeof(buffer), "%f", sensor_value_to_double(&temperature));
		LOG_INF("temperature: %s", buffer);
		snprintf(buffer, sizeof(buffer), "%f", sensor_value_to_double(&humidity));
		LOG_INF("humidity: %s", buffer);
		snprintf(buffer, sizeof(buffer), "%f", sensor_value_to_double(&pressure));
		LOG_INF("pressure: %s", buffer);

		k_sleep(K_SECONDS(2));
	}

}