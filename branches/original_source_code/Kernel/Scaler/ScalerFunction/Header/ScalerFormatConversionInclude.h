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
// ID Code      : ScalerFormatConversionInclude.h No.0000
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

#if(_FORMAT_CONVERSION_SUPPORT == _ON)

#if(_MULTI_DISPLAY_MAX != 0x01)
extern void ScalerFmtCnvDuplicateSetting(EnumInputDataPath enumInputDataPath, EnumInputDataPath enumDuplicatePath);
#endif
extern void ScalerFmtCnvResetPath(EnumInputDataPath enumInputDataPath, bit bEnable);
extern void ScalerFmtCnvHalfSDControl(EnumInputDataPath enumInputDataPath, bit bEnable);
extern void ScalerFmtCnvHalfSDSetFirstPixel(EnumInputDataPath enumInputDataPath, WORD usHstart);

extern bit ScalerFmtCnvHalfSDGetStatus(EnumInputDataPath enumInputDataPath);
extern void ScalerFmtCnvFtoPSetFifo(EnumInputDataPath enumInputDataPath, WORD usHwidth, WORD usVstart);
extern bit ScalerFmtCnvFtoPGetStatus(EnumInputDataPath enumInputDataPath);
extern void ScalerFmtCnvFtoPInterlaceSetting(EnumInputDataPath enumInputDataPath);
#endif

#if(_VGA_CHROMA_PATTERN12_SUPPORT == _ON)
extern EnumInputDataPath ScalerFmtCnvGetInputPath(EnumSourceSearchPort enumSourceSearchPort);
#endif
