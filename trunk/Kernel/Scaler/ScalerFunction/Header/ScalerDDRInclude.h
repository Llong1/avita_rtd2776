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
// ID Code      : ScalerDDRInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// DDR3 Search Phase Options
//--------------------------------------------------


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _DC_SYS_CLEINT_MCU,
    _DC_SYS_CLEINT_SB,
} EnumDCSysClientType;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
extern void ScalerDDR3PowerControl(bit bOn);

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
extern void ScalerDDR3DCSysSetPictureSetInfo(BYTE ucPictNum, BYTE ucPictWidthScale, DWORD ulPictInitPage);
#endif

#endif // End of #if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)

