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
// ID Code      : RL6193_Series_DisplayInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_LVDS)

extern void ScalerDisplayLvdsInitialTable(void);

extern void ScalerDisplayLvdsSetVcoBand(BYTE ucVcoBand);
extern void ScalerDisplayLvdsSetPhaseBand(BYTE ucPhaseBand);
extern bit ScalerDisplayGetLvdsPowerStatus(void);
extern void ScalerDisplayLvdsPLL(bit bOn);


#elif(_PANEL_STYLE == _PANEL_VBO)

extern void ScalerDisplayVboInitialTable(void);
extern bit ScalerDisplayGetVboPowerStatus(void);
extern void ScalerDisplayVboPLL(bit bOn);
extern void ScalerDisplaySetVboPLLSSC(bit bDclkSpreadSpeed, BYTE ucSpreadRange);
extern void ScalerDisplayVboPower(bit bOn);

#endif // #if(_PANEL_STYLE == _PANEL_LVDS)
