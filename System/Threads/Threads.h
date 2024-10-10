/*
 * Threads.h
 *
 *  Created on: Oct 10, 2024
 *      Author: Ilyas Asmouki
 */

#ifndef SYSTEM_THREADS_THREADS_H_
#define SYSTEM_THREADS_THREADS_H_


#include "FreeRTOS.h"


class Thread {
public:
	Thread(const char* name);
	Thread(const char* name, osPriority priority);
	Thread(const char* name, uint32_t stackSize);
	Thread(const char* name, osPriority priority, uint32_t stackSize);

	virtual void init() = 0;
	virtual void loop() = 0;

	bool isRunning();
	void terminate();

	void setTickDelay(uint32_t ms);
	uint32_t getTickDelay();

private:
	uint32_t delay;
	osThreadAttr_t thread_attributes;
	bool running = true;
	const char* name;
	osThreadId handle;

};

#endif /* SYSTEM_THREADS_THREADS_H_ */
