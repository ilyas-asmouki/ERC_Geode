/*
 * Thread.h
 *
 *  Created on: Oct 10, 2024
 *      Author: Ilyas Asmouki
 */

#ifndef SYSTEM_THREADS_THREADS_H_
#define SYSTEM_THREADS_THREADS_H_


#include "FreeRTOS.h"
#include "cmsis_os2.h"


class Thread {
public:
	Thread(const char* name);
	Thread(const char* name, osPriority_t priority);
	Thread(const char* name, uint32_t stack_size);
	Thread(const char* name, osPriority_t priority, uint32_t stack_size);
	virtual ~Thread() {};

	virtual void init() = 0;
	virtual void loop() = 0;

	bool is_running();
	void terminate();

	osThreadId_t get_handle();

	void set_tick_delay(uint32_t ms);
	uint32_t get_tick_delay();

private:
	osThreadId_t handle;
	const char* name;
	bool running = true;
	uint32_t delay;
	osThreadAttr_t thread_attributes;
};

#endif /* SYSTEM_THREADS_THREADS_H_ */
