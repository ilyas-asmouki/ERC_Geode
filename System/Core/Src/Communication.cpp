/*
 * Communication.cpp
 *
 *  Created on: Oct 18, 2024
 *      Author: Ilyas Asmouki
 */


#include "Communication.h"
#include "Thread.h"
#include "FDCANTerminal.h"


void Communication::init(void) {
	static FDCANTerminal* fdcanterm = new FDCANTerminal(&hfdcan1);
	fdcanterm->set_tick_delay(100);
}


