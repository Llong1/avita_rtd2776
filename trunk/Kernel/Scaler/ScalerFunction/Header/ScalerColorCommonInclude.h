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
// ID Code      : ScalerColorCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro of Color Space
//--------------------------------------------------
#define GET_COLOR_SPACE(port)                       (g_pstColorInfo[port].b3ColorSpace)
#define SET_COLOR_SPACE(port, x)                    (g_pstColorInfo[port].b3ColorSpace = (x))
#define CLR_COLOR_SPACE(port)                       (g_pstColorInfo[port].b3ColorSpace = 0)
#define GET_COLOR_SPACE_RGB(x)                      (((x) == _COLOR_SPACE_RGB) || ((x) == _COLOR_SPACE_Y_ONLY) || ((x) == _COLOR_SPACE_RAW))

//--------------------------------------------------
// Macro of Colorimetry Data
//--------------------------------------------------
#define GET_COLORIMETRY(port)                       (g_pstColorInfo[port].b4Colorimetry)
#define SET_COLORIMETRY(port, x)                    (g_pstColorInfo[port].b4Colorimetry = (x))
#define CLR_COLORIMETRY(port)                       (g_pstColorInfo[port].b4Colorimetry = 0)

//--------------------------------------------------
// Macro of Extended Colorimetry
//--------------------------------------------------
#define GET_EXT_COLORIMETRY(port)                   (g_pstColorInfo[port].b5ExtColorimetry)
#define SET_EXT_COLORIMETRY(port, x)                (g_pstColorInfo[port].b5ExtColorimetry = (x))
#define CLR_EXT_COLORIMETRY(port)                   (g_pstColorInfo[port].b5ExtColorimetry = 0)

//--------------------------------------------------
// Macro of Color Depth
//--------------------------------------------------
#define GET_COLOR_DEPTH(port)                       (g_pstColorInfo[port].b5ColorDepth)
#define SET_COLOR_DEPTH(port, x)                    (g_pstColorInfo[port].b5ColorDepth = (x))
#define CLR_COLOR_DEPTH(port)                       (g_pstColorInfo[port].b5ColorDepth = 0)

//--------------------------------------------------
// Macro of RGB Quantization Range
//--------------------------------------------------
#define GET_COLOR_RGB_QUANTIZATION_RANGE(port)      (g_pstColorInfo[port].b2RgbQuantizationRange)
#define SET_COLOR_RGB_QUANTIZATION_RANGE(port, x)   (g_pstColorInfo[port].b2RgbQuantizationRange = (x))
#define CLR_COLOR_RGB_QUANTIZATION_RANGE(port)      (g_pstColorInfo[port].b2RgbQuantizationRange = 0)

//--------------------------------------------------
// Macro of RGB Limit Range User
//--------------------------------------------------
#define GET_COLOR_RGB_LIMIT_RANGE_USER(port)        (g_pstColorInfo[port].b1RgbLimitRangeUser)
#define SET_COLOR_RGB_LIMIT_RANGE_USER(port, x)     (g_pstColorInfo[port].b1RgbLimitRangeUser = (x))

//--------------------------------------------------
// Macro of YCC Quantization Range
//--------------------------------------------------
#define GET_COLOR_YCC_QUANTIZATION_RANGE(port)      (g_pstColorInfo[port].b1YccQuantizationRange)
#define SET_COLOR_YCC_QUANTIZATION_RANGE(port, x)   (g_pstColorInfo[port].b1YccQuantizationRange = (x))

//--------------------------------------------------
// Macro of YCC Full Range User
//--------------------------------------------------
#define GET_COLOR_YCC_FULL_RANGE_USER(port)         (g_pstColorInfo[port].b1YccFullRangeUser)
#define SET_COLOR_YCC_FULL_RANGE_USER(port, x)      (g_pstColorInfo[port].b1YccFullRangeUser = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b3ColorSpace : 3;
    BYTE b5ColorDepth : 5;
    BYTE b5ExtColorimetry : 5;
    BYTE b2RgbQuantizationRange : 2;
    BYTE b1RgbLimitRangeUser : 1;
    BYTE b1YccQuantizationRange : 1;
    BYTE b1YccFullRangeUser : 1;
    BYTE b4Colorimetry : 4;
} StructColorInfo;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructColorInfo g_pstColorInfo[];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerColorHLWAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight, EnumDBApply enumDBApply);

