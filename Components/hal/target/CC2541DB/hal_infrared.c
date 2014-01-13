/**************************************************************************************************
 Filename:       hal_INF.c
 Revised:        $Date: 2013-04-05 07:25:57 -0700 (Fri, 05 Apr 2013) $
 Revision:       $Revision: 33773 $

 Description:    Driver for the TI TMP06 infrared thermophile sensor.


 Copyright 2012-2013 Texas Instruments Incorporated. All rights reserved.

 IMPORTANT: Your use of this Software is limited to those specific rights
 granted under the terms of a software license agreement between the user
 who downloaded the software, his/her employer (which must be your employer)
 and Texas Instruments Incorporated (the "License").  You may not use this
 Software unless you agree to abide by the terms of the License. The License
 limits your use, and you acknowledge, that the Software may not be modified,
 copied or distributed unless embedded on a Texas Instruments microcontroller
 or used solely and exclusively in conjunction with a Texas Instruments radio
 frequency transceiver, which is integrated into your product.  Other than for
 the foregoing purpose, you may not use, reproduce, copy, prepare derivative
 works of, modify, distribute, perform, display or sell this Software and/or
 its documentation for any purpose.

 YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
 PROVIDED �AS IS� WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
 NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
 TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
 NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
 LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
 INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
 OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
 OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
 (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

 Should you have any questions regarding your right to use this Software,
 contact Texas Instruments Incorporated at www.TI.com.
 **************************************************************************************************/

/* ------------------------------------------------------------------------------------------------
 *                                          Includes
 * ------------------------------------------------------------------------------------------------
 */
#include "hal_infrared.h"
#include "hal_i2c.h"
#include "hal_sensor.h"

/* ------------------------------------------------------------------------------------------------
 *                                           Constants
 * ------------------------------------------------------------------------------------------------
 */

/* Slave address */
#define TMP006_I2C_ADDRESS              0x44

/* TMP006 register addresses */
#define TMP006_REG_ADDR_VOLTAGE         0x00
#define TMP006_REG_ADDR_TEMPERATURE     0x01
#define TMP006_REG_ADDR_CONFIG          0x02
#define TMP006_REG_MANF_ID              0xFE
#define TMP006_REG_PROD_ID              0xFE

/* TMP006 register values */
#define TMP006_VAL_CONFIG_RESET         0x7400  // Sensor reset state
#define TMP006_VAL_CONFIG_ON            0x7000  // Sensor on state
#define TMP006_VAL_CONFIG_OFF           0x0000  // Sensor off state
#define TMP006_VAL_MANF_ID              0x5449  // Manufacturer ID
#define TMP006_VAL_PROD_ID              0x0067  // Product ID
/* Bit values */
#define DATA_RDY_BIT                    0x8000 // Data ready
/* Register length */
#define INF_REG_LEN                  2

/* ------------------------------------------------------------------------------------------------
 *                                           Local Functions
 * ------------------------------------------------------------------------------------------------
 */
static void HalINFSelect(void);

/* ------------------------------------------------------------------------------------------------
 *                                           Local Variables
 * ------------------------------------------------------------------------------------------------
 */
/* ------------------------------------------------------------------------------------------------
 *                                           Public functions
 * -------------------------------------------------------------------------------------------------
 */

/**************************************************************************************************
 * @fn          HalINFTurnOn
 *
 * @brief       Turn the sensor on
 *
 * @return      none
 **************************************************************************************************/
void HalINFTurnOn(void) {
	HalINFSelect();
}

/**************************************************************************************************
 * @fn          HalINFTurnOff
 *
 * @brief       Turn the sensor off
 *
 * @return      none
 **************************************************************************************************/
void HalINFTurnOff(void) {
	HalINFSelect();
}

/**************************************************************************************************
 * @fn          HalINFWrite
 *
 * @brief       Read the sensor voltage and sensor temperature registers
 *
 * @param       Voltage and temperature in raw format (2 + 2 bytes)
 *
 * @return      TRUE if valid data
 **************************************************************************************************/
bool HalINFWrite(uint8 addr, uint8 *pBuf, uint8 nBytes) {
	bool success;
	HalINFTurnOn();
	success = HalSensorWriteReg(addr, pBuf, nBytes);
	return success;
}

/**************************************************************************************************
 * @fn          HalINFRead
 *
 * @brief       Read the sensor voltage and sensor temperature registers
 *
 * @param       Voltage and temperature in raw format (2 + 2 bytes)
 *
 * @return      TRUE if valid data
 **************************************************************************************************/
bool HalINFRead(uint8 addr, uint8 *pBuf, uint8 nBytes) {
	bool success;
	HalINFTurnOn();
	// Read the sensor registers
	success = HalSensorReadReg(addr, pBuf, 1);
	if (success) {
	}
	return success;
}

/* ------------------------------------------------------------------------------------------------
 *                                           Private functions
 * -------------------------------------------------------------------------------------------------
 */

/**************************************************************************************************
 * @fn          HalINFSelect
 *
 * @brief       Select the TMP006 slave and set the I2C bus speed
 *
 * @return      none
 **************************************************************************************************/
static void HalINFSelect(void) {
	// Select slave and set clock rate
	HalI2CInit(0x50, i2cClock_533KHZ);
}
