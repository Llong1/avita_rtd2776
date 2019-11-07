/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2012>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerPinshare.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_PINSHARE__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************

void ScalerPinshareAdjustFlashDrive(EnumConfigSPIPinType enumConfigFlashDrive, EnumFlashDriveConfigType enumFlashDriveConfig);
void ScalerPinshareConfig(BYTE ucPorStatus);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Adjust Flash Drive config
// Input Value  : enumConfigPin  --> Pin num
//                enumConfigFlashDrive --> Drine Current
// Output Value : None
//--------------------------------------------------
void ScalerPinshareAdjustFlashDrive(EnumConfigSPIPinType enumConfigFlashDrive, EnumFlashDriveConfigType enumFlashDriveConfig)
{
    switch(enumConfigFlashDrive)
    {
        case _CONFIG_PIN_SPI_CLK:

            switch(enumFlashDriveConfig)
            {
                case _SPI_DRIVE_3_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
                    break;

                case _SPI_DRIVE_3_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT5 | _BIT4 | _BIT3), _BIT4 | _BIT3);
                    break;

                case _SPI_DRIVE_4_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT5 | _BIT4 | _BIT3), _BIT5);
                    break;

                case _SPI_DRIVE_4_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT5 | _BIT4 | _BIT3), _BIT5 | _BIT3);
                    break;

                case _SPI_DRIVE_5_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT5 | _BIT4 | _BIT3), _BIT5 | _BIT4);
                    break;

                case _SPI_DRIVE_5_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT5 | _BIT4 | _BIT3), _BIT5 | _BIT4 | _BIT3);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_SPI_SI_SO_CEB:

            switch(enumFlashDriveConfig)
            {
                case _SPI_DRIVE_3_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _SPI_DRIVE_3_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT2 | _BIT1 | _BIT0), _BIT1 | _BIT0);
                    break;

                case _SPI_DRIVE_4_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                case _SPI_DRIVE_4_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT0);
                    break;

                case _SPI_DRIVE_5_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT1);
                    break;

                case _SPI_DRIVE_5_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT1 | _BIT0);
                    break;

                default:
                    break;
            }

            break;

        default:
            break;
    }
}
//--------------------------------------------------
// Description  : Low Leakage or Normal Pin Config.
// Input Value  : ON --> Low Leakage Config. ; OFF --> Normal Operation
// Output Value : None
//--------------------------------------------------
void ScalerPinshareConfig(BYTE ucPorStatus)
{
    // GPIO Config
    if(ucPorStatus == _POWER_STATUS_NORMAL)
    {
        PCB_GPIO_SETTING_POWER_NORMAL();
    }
    else if(ucPorStatus == _POWER_STATUS_SAVING)
    {
        PCB_GPIO_SETTING_POWER_SAVING();
    }
    else if(ucPorStatus == _POWER_STATUS_AC_ON)
    {
        ScalerPinshareAdjustFlashDrive(_CONFIG_PIN_SPI_CLK, _SPI_DRIVE_4_0MA);
        ScalerPinshareAdjustFlashDrive(_CONFIG_PIN_SPI_SI_SO_CEB, _SPI_DRIVE_4_0MA);
        PCB_GPIO_SETTING_POWER_AC_ON();
    }
    else // Power Down
    {
        PCB_GPIO_SETTING_POWER_DOWN();
    }
}
