#include "bcomdef.h"
#include "OSAL.h"
#include "OSAL_PwrMgr.h"
#include "osal_snv.h"

#include "OnBoard.h"
#include "hal_adc.h"
#include "hal_led.h"
#include "hal_key.h"
#include "hal_lcd.h"
#include "hal_i2c.h"
#include "gatt.h"
#include "hci.h"
#include "gapgattserver.h"
#include "gattservapp.h"
#include "devinfoservice.h"
#include "simpleGATTprofile.h"
#include "peripheral.h"
#include "gapbondmgr.h"
#include "aicoDevice.h"
#include "hal_infrared.h"

/*********************************************************************
 * LOCAL VARIABLES
 */
static uint8 simpleBLEPeripheral_TaskID; // Task ID for internal task/event processing

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static void simpleBLEPeripheral_ProcessOSALMsg(osal_event_hdr_t *pMsg);

void SimpleBLEPeripheral_Init(uint8 task_id) {
	simpleBLEPeripheral_TaskID = task_id;

	//HalLcdWriteStringValue( "BLE Peri-B", OAD_VER_NUM( _imgHdr.ver ), 16, HAL_LCD_LINE_1 );
	HalLcdWriteString("i2c start", HAL_LCD_LINE_1);

	uint8 i2cdata[4] = { 0x01, 0x02, 0x03, 0x04 };

	bool success;

	success = HalINFWrite(0, i2cdata, 4);

	HalLcdWriteStringValue("HalINFWrite: ", success, 16, HAL_LCD_LINE_2);

	uint8 k = 0;
	HalINFRead(0x03, &k, 1);
	HalLcdWriteStringValue("HalINFRead: ", k, 16, HAL_LCD_LINE_3);
}

uint16 SimpleBLEPeripheral_ProcessEvent(uint8 task_id, uint16 events) {

	VOID task_id; // OSAL required parameter that isn't used in this function

	if (events & SYS_EVENT_MSG) {
		uint8 *pMsg;
		if ((pMsg = osal_msg_receive(simpleBLEPeripheral_TaskID)) != NULL) {
			simpleBLEPeripheral_ProcessOSALMsg((osal_event_hdr_t *) pMsg);
			VOID osal_msg_deallocate(pMsg);
		}
		// return unprocessed events
		return (events ^ SYS_EVENT_MSG);
	}

	// Discard unknown events
	return 0;
}

static void simpleBLEPeripheral_ProcessOSALMsg(osal_event_hdr_t *pMsg) {
	switch (pMsg->event) {
	case KEY_CHANGE:
		//simpleBLEPeripheral_HandleKeys(((keyChange_t *) pMsg)->state, ((keyChange_t *) pMsg)->keys);
		break;
	default:
		// do nothing
		break;
	}
}

