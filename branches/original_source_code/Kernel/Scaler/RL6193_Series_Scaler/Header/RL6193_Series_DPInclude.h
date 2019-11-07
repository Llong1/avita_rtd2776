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
// ID Code      : RL6193_Series_DPInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_DP_FREESYNC_SUPPORT == _ON)
#define _DP_FREESYNC_IVSTART                            1
#endif

//--------------------------------------------------
// Definitions for DP training Pattern 1 FLD Reference Clock Select
//--------------------------------------------------
typedef enum
{
    _DP_NF_REF_XTAL = 0x00,
    _DP_NF_REF_D10_2,
} EnumDpNFCodeRef;

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpPowerSwitch(EnumPowerAction enumPowerAction);
extern EnumDpRefLinkClock ScalerDpLinkClockValid(void);

#if(_DP_FREESYNC_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpTxSSTSetAmdSpdInfo(bit bPlayback);
#endif
#endif
#endif // End of #if(_DP_SUPPORT == _ON)
