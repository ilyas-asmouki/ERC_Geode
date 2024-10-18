/*
 * Communication.h
 *
 *  Created on: Oct 16, 2024
 *      Author: Ilyas Asmouki
 */

#ifndef SYSTEM_THREAD_INC_FDCANTERMINAL_H_
#define SYSTEM_THREAD_INC_FDCANTERMINAL_H_


#include "Thread.h"
#include "fdcan.h"
#include "stm32g4xx_hal_fdcan.h"
#include <cstring>

typedef enum {
	STATUS = 0,
	UNKNOWN
} Command;

Command to_enum(const char* command);

class FDCANTerminal : public Thread {
public:
	FDCANTerminal(FDCAN_HandleTypeDef* fdcan_handle);
    void init();
    void loop();
    void process();

private:
    FDCAN_HandleTypeDef* fdcan;
    void send_response(const char* response);
    void handle_message(const char* message);
    void execute_command(Command command);
};


#endif /* SYSTEM_THREAD_INC_FDCANTERMINAL_H_ */
