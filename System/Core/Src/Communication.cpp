/*
 * Communication.cpp
 *
 *  Created on: Oct 16, 2024
 *      Author: Ilyas Asmouki
 */


#include "Communication.h"

FDCANTerminal::FDCANTerminal(FDCAN_HandleTypeDef* fdcanHandle) : fdcan(fdcanHandle) {}


void FDCANTerminal::init() {
    FDCAN_FilterTypeDef sFilterConfig;
    sFilterConfig.IdType = FDCAN_STANDARD_ID;
    sFilterConfig.FilterIndex = 0;
    sFilterConfig.FilterType = FDCAN_FILTER_MASK;
    sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    sFilterConfig.FilterID1 = 0x123; // EXAMPLE ID
    sFilterConfig.FilterID2 = 0x7FF; // GENERAL ID
    HAL_FDCAN_ConfigFilter(fdcan, &sFilterConfig);
    HAL_FDCAN_Start(fdcan);
    HAL_FDCAN_ActivateNotification(fdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
}

void FDCANTerminal::process() {
    FDCAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];

    if (HAL_FDCAN_GetRxMessage(fdcan, FDCAN_RX_FIFO0, &rx_header, rx_data) == HAL_OK) {
        char message[9];
        std::memcpy(message, rx_data, rx_header.DataLength >> 16);
        message[rx_header.DataLength >> 16] = '\0';
        handle_message(message);
    }
}

void FDCANTerminal::send_response(const char* response) {
    FDCAN_TxHeaderTypeDef tx_header;
    tx_header.Identifier = 0x321; // EXAMPLE ID
    tx_header.IdType = FDCAN_STANDARD_ID;
    tx_header.TxFrameType = FDCAN_DATA_FRAME;
    tx_header.DataLength = std::strlen(response) << 16;
    tx_header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    tx_header.BitRateSwitch = FDCAN_BRS_OFF;
    tx_header.FDFormat = FDCAN_CLASSIC_CAN;
    tx_header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    tx_header.MessageMarker = 0;

    uint8_t tx_data[8];
    std::memcpy(tx_data, response, std::strlen(response));

    HAL_FDCAN_AddMessageToTxFifoQ(fdcan, &tx_header, tx_data);
}

void FDCANTerminal::handle_message(const char* message) {
    char trimmed[9]; // trim trailing characters
    std::strncpy(trimmed, message, std::strlen(message));
    trimmed[std::strlen(message)] = '\0';
    Command command = to_enum(trimmed);
    execute_command(command);
}

void FDCANTerminal::execute_command(Command command) {
	switch (command) {
	case STATUS:
		send_response("System is running");
		break;
	case UNKNOWN:
	default:
		send_response("Unknown command");
		break;
	}
}
