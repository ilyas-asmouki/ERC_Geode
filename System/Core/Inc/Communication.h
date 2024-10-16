/*
 * Communication.h
 *
 *  Created on: Oct 16, 2024
 *      Author: Ilyas Asmouki
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_


#include "fdcan.h"
#include "stm32g4xx_hal_fdcan.h"
#include <cstring>

typedef enum {
	STATUS = 0,
	UNKNOWN
} Command;

Command to_enum(const char* command) {
	if (std::strcmp(command, "STATUS") == 0) return STATUS;
	else return UNKNOWN;
}

class FDCANTerminal {
public:
	FDCANTerminal(FDCAN_HandleTypeDef* fdcanHandle);
    void init();
    void process();

private:
    FDCAN_HandleTypeDef *fdcan;
    void send_response(const char* response);
    void handle_message(const char* message);
    void execute_command(Command command);
};


#endif /* COMMUNICATION_H_ */
