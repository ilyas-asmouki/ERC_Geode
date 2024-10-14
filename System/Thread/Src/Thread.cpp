/*
 * Thread.cpp
 *
 *  Created on: Oct 10, 2024
 *      Author: Ilyas Asmouki
 */

#include "Thread.h"
#include "task.h"


#define DEFAULT_STACK_SIZE (1024)

void __task_run(void* arg) {
	Thread* thread = (Thread*) arg;

	osDelay(100 / portTICK_PERIOD_MS);

	thread->init();

	while(thread->is_running()) {
		thread->loop();
		osDelay(thread->get_tick_delay() / portTICK_PERIOD_MS);
	}

	delete thread;

	vTaskDelete(nullptr);

	while(true) {
		osDelay(1000 / portTICK_PERIOD_MS);
	}
}


Thread::Thread(const char* name) : Thread(name, (osPriority_t) osPriorityNormal) {};


Thread::Thread(const char* name, osPriority_t priority) : Thread(name, priority, DEFAULT_STACK_SIZE) {};


Thread::Thread(const char* name, uint32_t stack_size) : Thread(name, (osPriority_t) osPriorityNormal, stack_size) {};


Thread::Thread(const char* name, osPriority_t priority, uint32_t stack_size) {
	const osThreadAttr_t thread_attributes = {
		.name = (char*) name,
		.stack_size = stack_size,
		.priority = (osPriority_t) priority,
	};
	this->handle = (osThreadId_t) osThreadNew(&__task_run, this, &thread_attributes);
	this->name = name;
}

bool Thread::is_running() {
	return running;
}

void Thread::terminate() {
	running = false;
}

osThreadId_t Thread::get_handle() {
	return handle;
}

void Thread::set_tick_delay(uint32_t ms) {
	delay = ms;
}

uint32_t Thread::get_tick_delay() {
	return delay;
}



