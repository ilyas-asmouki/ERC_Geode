/*
 * PowerMonitor.cpp
 *
 *  Created on: Oct 13, 2024
 *      Author: Ilyas Asmouki
 */

#include "PowerMonitor.h"

#define MAX_CURRENT 40   // A
#define SHUNT_VALUE	0.3e-3f // Ohm

#define CURRENT_LSB (MAX_CURRENT >> 15)


PowerMonitor::PowerMonitor(SPI_HandleTypeDef* spi) : Thread("PowerMonitor"), spi(spi), measurements(nullptr) {};


void PowerMonitor::init() {
	osDelay(100 / portTICK_PERIOD_MS);

	uint8_t attempts = 3;
	bool init_success = false;

	while (attempts-- > 0) {
		if (get(INA239_DEVICE_ID_REG) == INA239_DEV_ID) {
			init_success = true;
			break;
		}
	}

	if (init_success) {
		bool config_success = set(INA239_CONFIG_REG, INA239_CONFIG_ADCRANGE);

		uint16_t adc_config = 0;
		adc_config |= INA239_ADCCONFIG_MODE & (0xF << INA239_ADCCONFIG_MODE_BIT);
		adc_config |= INA239_ADCCONFIG_VBUSCT & (0x2 << INA239_ADCCONFIG_VBUSCT_BIT);
		adc_config |= INA239_ADCCONFIG_VSHCT & (0x2 << INA239_ADCCONFIG_VSHCT_BIT);
		adc_config |= INA239_ADCCONFIG_VTCT & (0x7 << INA239_ADCCONFIG_VTCT_BIT);
		adc_config |= INA239_ADCCONFIG_AVG & (0x3 << INA239_ADCCONFIG_AVG_BIT);

		config_success |= set(INA239_ADC_CONFIG_REG, adc_config);

		config_success |= set(INA239_SHUNT_CAL_REG, 4 * SHUNT_CAL_CONST * MAX_CURRENT * SHUNT_VALUE);

		if (config_success) {
			// TODO: print that the device has been initialized successfully
		} else {
			// TODO: print that the device config has failed
			terminate();
		}
	} else {
		// TODO: print that the device hasnt been initialized
		terminate();
	}

	//loop();
}

void PowerMonitor::loop() {
	measurements->shunt_voltage = read_shunt_voltage();
	measurements->bus_voltage = read_bus_voltage();
	measurements->current = read_current();
	measurements->power = read_power();
	measurements->temperature = read_temperature();
}

float PowerMonitor::read_shunt_voltage() {
	return 1.25e-6f * get(INA239_VSHUNT_REG); // [V]
}

float PowerMonitor::read_bus_voltage() {
	return 3.125e-3f * get(INA239_VBUS_REG); // [V]
}

float PowerMonitor::read_current() {
	return (float) CURRENT_LSB * get(INA239_CURRENT_REG); // [A]
}

float PowerMonitor::read_power() {
	int32_t raw_power = 0;
	read(INA239_POWER_REG, (uint8_t*) &raw_power, 3);
	return 0.2f * CURRENT_LSB * raw_power;
}

//x * 2**n == x << n
//
//generally, you can use x * y = x << ilog2(y);

float PowerMonitor::read_temperature() {
	return 125e-3f * ((int16_t) get(INA239_DIETEMP_REG) >> INA239_DIETEMP_BIT); // [deg C]
}

uint16_t PowerMonitor::get(uint8_t reg) {
	uint16_t value = 0;
	read(reg, (uint8_t*) &value, 2);
	return value;
}

bool PowerMonitor::set(uint8_t reg, uint16_t value) {
	return write(reg, (uint8_t*) &value, 2);
}

bool PowerMonitor::write(uint8_t reg, uint8_t* data, uint8_t size) {
	uint8_t tx_buffer[4];
	tx_buffer[0] = (reg << 2) | 0b00;

	for (uint8_t i = 0; i < size; i++) {
		tx_buffer[i+1] = data[size-i-1];
	}

	__disable_irq();
	HAL_StatusTypeDef status = HAL_SPI_Transmit(spi, tx_buffer, size+1, 10 / portTICK_PERIOD_MS);
	__enable_irq();

	return status == HAL_OK;
}

bool PowerMonitor::read(uint8_t reg, uint8_t* data, uint8_t size) {
	uint8_t rx_buffer[4];
	rx_buffer[0] = (reg << 2) | 0b01;

	__disable_irq();
	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(spi, rx_buffer, rx_buffer, size+1, 100 / portTICK_PERIOD_MS);
	__enable_irq();

	for (uint8_t i = 0; i < size; i++) {
		data[i] = rx_buffer[size-i];
	}

	return status == HAL_OK;
}




