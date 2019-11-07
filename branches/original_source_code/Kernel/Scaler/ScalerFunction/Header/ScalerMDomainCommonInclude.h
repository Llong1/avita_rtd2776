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
// ID Code      : ScalerMDomainCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define GET_INTERLACED_MODE()                       (g_stMDomainInputData.b1Interlace)

#define GET_H_SCALE_UP()                            (g_stMDomainInfo.b1HSU)
#define SET_H_SCALE_UP()                            (g_stMDomainInfo.b1HSU = _TRUE)
#define CLR_H_SCALE_UP()                            (g_stMDomainInfo.b1HSU = _FALSE)

#define GET_H_SCALE_DOWN()                          (g_stMDomainInfo.b1HSD)
#define SET_H_SCALE_DOWN()                          (g_stMDomainInfo.b1HSD = _TRUE)
#define CLR_H_SCALE_DOWN()                          (g_stMDomainInfo.b1HSD = _FALSE)

#define GET_V_SCALE_UP()                            (g_stMDomainInfo.b1VSU)
#define SET_V_SCALE_UP()                            (g_stMDomainInfo.b1VSU = _TRUE)
#define CLR_V_SCALE_UP()                            (g_stMDomainInfo.b1VSU = _FALSE)

#define GET_V_SCALE_DOWN()                          (g_stMDomainInfo.b1VSD)
#define SET_V_SCALE_DOWN()                          (g_stMDomainInfo.b1VSD = _TRUE)
#define CLR_V_SCALE_DOWN()                          (g_stMDomainInfo.b1VSD = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructMDomainInfo g_stMDomainInfo;
extern StructTimingInfo g_stMDomainInputData;
extern StructDisplayInfo g_stMDomainOutputData;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern BYTE ScalerMDomainGetColorDepth(void);
