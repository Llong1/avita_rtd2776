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
// ID Code      : ScalerMeasureCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define GET_INPUT_TIMING_HWIDTH()                    (g_pstRegionTimingInfoPointer->stTimingInfo.usHWidth)
#define GET_INPUT_TIMING_HSTART()                    (g_pstRegionTimingInfoPointer->stTimingInfo.usHStart)
#define GET_INPUT_TIMING_VHEIGHT()                   (g_pstRegionTimingInfoPointer->stTimingInfo.usVHeight)
#define GET_INPUT_TIMING_VSTART()                    (g_pstRegionTimingInfoPointer->stTimingInfo.usVStart)
#define GET_INPUT_TIMING_INTERLACE_FLG()             (g_pstRegionTimingInfoPointer->stTimingInfo.b1Interlace)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructRegionTimingInfo *g_pstRegionTimingInfoPointer;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

