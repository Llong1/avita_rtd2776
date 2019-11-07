/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerPowerInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define POLLING_VCCK_OFF_STATUS(timeout)                {\
                                                            BYTE ucLocalTimeOut = (timeout);\
                                                            ScalerSetByte(_POLLING_VCCK_ADDR, _POLLING_VCCK_VALUE);\
                                                            while((ScalerGetByte(_POLLING_VCCK_ADDR) != _POLLING_VCCK_VALUE) && ((ucLocalTimeOut)-- != 0))\
                                                            {\
                                                                ScalerSetByte(_POLLING_VCCK_ADDR, _POLLING_VCCK_VALUE);\
                                                                ScalerTimerDelayXms(1);\
                                                            }\
                                                            ScalerTimerDelayXms(10);\
                                                        }

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

extern void ScalerPowerXtalPower(BYTE ucOn);

extern void ScalerPowerGroupAIsolation(BYTE ucOn);
extern void ScalerPowerGroupBIsolation(BYTE ucOn);
extern void ScalerPowerGroupBPowerCut(BYTE ucOn);
