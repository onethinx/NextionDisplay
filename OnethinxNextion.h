/*
 * OnethinxNextion.h
 *
 *  Created on: 8 feb. 2019
 *  Created by: Jelle Huiberts @ Ontehinx
 *  Intercace between the "Onethinx module" and the nextion display
 */

#ifndef _ONETHINXNEXTION_ONETHINXNEXTION_H_
#define _ONETHINXNEXTION_ONETHINXNEXTION_H_

#include "cy_pdl.h"
#include <string.h>
#include <stdlib.h>

/*
 * NextionConfig
 *
 * Holds a pointer to the UART base
 * Used to communicate with the display
 *
 * Struct is used for future compatibility
 */
typedef struct {
	CySCB_Type *base;
} NextionConfig;

/*******************************************************************************
*                           Function prototypes
*******************************************************************************/

void Nextion_Command(NextionConfig config, char* buffer);
void Nextion_SetText(NextionConfig config, char* obj, char* text);
void Nextion_SetProgressbar(NextionConfig config, char* obj, char* value);
void Nextion_ChangePage(NextionConfig config, char* page);
bool Nextion_Read(NextionConfig config, char* buffer, int size);

/*******************************************************************************
*                           Internal functions
*                           should not be used!
*******************************************************************************/
char* Nextion_ComposeMessage(char* obj, char* specifier, char* value, char* suffix);

/*******************************************************************************
*                    		Function implementations
*******************************************************************************/

/*
 * Sends a command to the display
 *
 * param config
 * The config structure
 * buffer the command in full
 */
void Nextion_Command(NextionConfig config, char* buffer) {
	Cy_SCB_UART_PutString(config.base, buffer);
}

/*
 * Sets the text of a given text-box
 *
 * param config
 * The config structure
 *
 * param obj
 * The name of the text-box
 *
 * param text
 * The new text for the text-box
 */
void Nextion_SetText(NextionConfig config, char* obj, char* text) {
	char* temp = Nextion_ComposeMessage(obj, ".txt=\"", text, "\"\xFF\xFF\xFF");

	Cy_SCB_UART_PutString(config.base, temp);
	free(temp);
}

/*
 * Sets the progress of a given progress-bar
 *
 * param config
 * The config structure
 *
 * param obj
 * The name of the progress-bar
 *
 * param value
 * The value to set the proggress bar to
 */
void Nextion_SetProgressbar(NextionConfig config, char* obj, char* value) {
	char* temp = Nextion_ComposeMessage(obj, ".val=", value, "\xFF\xFF\xFF");

	Cy_SCB_UART_PutString(config.base, temp);
	free(temp);
}

/*
 *  Changes the page
 *
 * param config
 * The config structure
 *
 * param page
 * The index or the name of the page
 * You want to navigate to
 */
void Nextion_ChangePage(NextionConfig config, char* page) {
	char* temp = Nextion_ComposeMessage("page", " ", page, "\xFF\xFF\xFF");

	Cy_SCB_UART_PutString(config.base, temp);
	free(temp);
}

/*
 * Reads data send from the display
 *
 * param config
 * The config structure
 *
 * param buffer
 * The buffer used to read data
 *
 * param size
 * The size of the buffer
 *
 * return whether the buffer was read or not
 */
bool Nextion_Read(NextionConfig config, char* buffer, int size) {
	if (Cy_SCB_UART_GetRxFifoStatus(config.base)) {
		// Read the data.
		Cy_SCB_UART_GetArray(config.base, buffer, size);
		// Clear the buffer.
		Cy_SCB_UART_ClearRxFifo(config.base);
		// Clear the buffer status.
		Cy_SCB_UART_ClearRxFifoStatus(config.base, CY_SCB_UART_RX_NOT_EMPTY);
		return 1;
	} else {
		return 0;
	}
}

/*
 * Creates a string to send to the display
 *
 * Internal function should not be used!
 */
char* Nextion_ComposeMessage(char* obj, char* specifier, char* value, char* suffix) {
	char* temp = (char*)calloc((strlen(obj) + strlen(specifier) + strlen(value) + strlen(suffix)), sizeof(char*));
	int temp_index = 0;
	char* t;

	t = NULL;
	for (t = obj; *t != '\0'; t++) {
		temp[temp_index] = *t;
		temp_index = temp_index + 1;
	}
	t = NULL;
	for (t = specifier; *t != '\0'; t++) {
		temp[temp_index] = *t;
		temp_index = temp_index + 1;
	}
	t = NULL;
	for (t = value; *t != '\0'; t++) {
		temp[temp_index] = *t;
		temp_index = temp_index + 1;
	}
	t = NULL;
	for (t = suffix; *t != '\0'; t++) {
		temp[temp_index] = *t;
		temp_index = temp_index + 1;
	}
	return temp;
}

#endif /* _ONETHINXNEXTION_ONETHINXNEXTION_H_ */
