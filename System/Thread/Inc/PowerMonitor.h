/*
 * PowerMonitor.h
 *
 *  Created on: Oct 13, 2024
 *      Author: Ilyas Asmouki
 */

#ifndef SYSTEM_THREAD_INC_POWERMONITOR_H_
#define SYSTEM_THREAD_INC_POWERMONITOR_H_


#include "Thread.h"
#include "ina239.h"
#include <spi.h>
#include "stm32g4xx_hal_spi.h"

typedef struct {
	float shunt_voltage;
	float bus_voltage;
	float current;
	float power;
	float temperature;
} Measurements;


class PowerMonitor : public Thread {
public:
	PowerMonitor(SPI_HandleTypeDef* spi);
	void init() override;
	void loop() override;

	float read_shunt_voltage();
	float read_bus_voltage();
	float read_current();
	float read_power();
	float read_temperature();

private:
	SPI_HandleTypeDef* spi;
	Measurements* measurements;

	uint16_t get(uint8_t reg);
	bool set(uint8_t reg, uint16_t value);

	bool write(uint8_t reg, uint8_t* data, uint8_t size);
	bool read(uint8_t reg, uint8_t* data, uint8_t size);
};



#endif /* SYSTEM_THREAD_INC_POWERMONITOR_H_ */
