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
// ID Code      : ScalerOSDLibInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __OSD_LIB_INTERFACE__
#define __OSD_LIB_INTERFACE__

//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************

//***************************************************************
// Command
//***************************************************************
//--------------------------------------------------
// Macros of Font Reorder control
//--------------------------------------------------
#define SCALEROSD_FONT_ROTATE_SETTING_GET()                     (MCU_FF03_TRIPLE_BYTES_OPERATION)
#define SCALEROSD_FONT_ROTATE_SETTING_SET(x)                    {\
                                                                    MCU_FF03_TRIPLE_BYTES_OPERATION = (x);\
                                                                }

#define SCALEROSD_FONT_ROTATE_1_2_BITS_SHIFT_SET(x)             {\
                                                                    MCU_FF04_SHIFT_BITS_NUMBER = (x);\
                                                                }

#define SCALEROSD_FONT_ROTATE_3_L_BITS_SHIFT_SET(x)             {\
                                                                    MCU_FF05_SHIFT_BYTE_ADDRESS = (x);\
                                                                }

#define SCALEROSD_FONT_ROTATE_INPUT_SET(x)                      {\
                                                                    MCU_FF06_INPUT_TRIPLE_BYTES = (x);\
                                                                }

#define SCALEROSD_FONT_ROTATE_ONPUT_GET()                       (MCU_FF07_RESULT_TRIPLE_BYTES)


//***************************************************************
// Windows
//***************************************************************
//--------------------------------------------------
// MACRO for Osd Window Number
//--------------------------------------------------
#define X_START(x)                                              (x)
#define Y_START(x)                                              (x)
#define X_END(x)                                                (x)
#define Y_END(x)                                                (x)

#define GET_OSD_WINDOW_NUMBER()                                 (g_stOsdWindow.b5WindowNumber)
#define SET_OSD_WINDOW_NUMBER(x)                                (g_stOsdWindow.b5WindowNumber = (x))

//--------------------------------------------------
// MACRO for Osd Window Enable
//--------------------------------------------------
#define GET_OSD_WINDOW_ENABLE()                                 (g_stOsdWindow.b1WindowEnable)
#define SET_OSD_WINDOW_ENABLE(x)                                (g_stOsdWindow.b1WindowEnable = (x))

//--------------------------------------------------
// MACRO for Osd Window Color
//--------------------------------------------------
// 0 ~ 64
#define GET_OSD_WINDOW_COLOR()                                  (g_stOsdWindow.b6WindowColor)
#define SET_OSD_WINDOW_COLOR(x)                                 (g_stOsdWindow.b6WindowColor = (x))

//--------------------------------------------------
// MACRO for Osd Window Color Shadow
//--------------------------------------------------
// 0 ~ 64
#define GET_OSD_WINDOW_COLOR_SHADOW()                           (g_stOsdWindow.b6WindowColorShadow)
#define SET_OSD_WINDOW_COLOR_SHADOW(x)                          (g_stOsdWindow.b6WindowColorShadow = (x))

//--------------------------------------------------
// MACRO for Osd Window Color Border
//--------------------------------------------------
// 0 ~ 64
#define GET_OSD_WINDOW_COLOR_BORDER()                           (g_stOsdWindow.b6WindowColorBorder)
#define SET_OSD_WINDOW_COLOR_BORDER(x)                          (g_stOsdWindow.b6WindowColorBorder = (x))

//--------------------------------------------------
// MACRO for Osd Window Shadow & Border Pixel Width
//--------------------------------------------------
// 000 ~ 111 : 1 ~ 8 Pixel
#define GET_OSD_WINDOW_SHADOW_BORDER_PIXEL_WIDTH()              (g_stOsdWindow.b3WindowShadowBorderPixelWidth)
#define SET_OSD_WINDOW_SHADOW_BORDER_PIXEL_WIDTH(x)             (g_stOsdWindow.b3WindowShadowBorderPixelWidth = (x))

//--------------------------------------------------
// MACRO for Osd Window Shadow & Border Pixel Height
//--------------------------------------------------
// 000 ~ 111 : 1 ~ 8 Line
#define GET_OSD_WINDOW_SHADOW_BORDER_PIXEL_HEIGHT()             (g_stOsdWindow.b3WindowShadowBorderPixelHeight)
#define SET_OSD_WINDOW_SHADOW_BORDER_PIXEL_HEIGHT(x)            (g_stOsdWindow.b3WindowShadowBorderPixelHeight = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Level Step
//--------------------------------------------------
#define _OSD_WINDOW_GRADIENT_LEVEL_STEP_1                       0
#define _OSD_WINDOW_GRADIENT_LEVEL_STEP_2                       1
#define _OSD_WINDOW_GRADIENT_LEVEL_STEP_3                       2
#define _OSD_WINDOW_GRADIENT_LEVEL_STEP_4                       3

#define GET_OSD_WINDOW_GRADIENT_LEVEL_SETP()                    (g_stOsdWindow.b2WindowGradientLevelStep)
#define SET_OSD_WINDOW_GRADIENT_LEVEL_SETP(x)                   (g_stOsdWindow.b2WindowGradientLevelStep = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Level Per
//--------------------------------------------------
#define _OSD_WINDOW_GRADIENT_LEVEL_PER_1                        1
#define _OSD_WINDOW_GRADIENT_LEVEL_PER_2                        2
#define _OSD_WINDOW_GRADIENT_LEVEL_PER_3                        3
#define _OSD_WINDOW_GRADIENT_LEVEL_PER_4                        4
#define _OSD_WINDOW_GRADIENT_LEVEL_PER_5                        5
#define _OSD_WINDOW_GRADIENT_LEVEL_PER_6                        6
#define _OSD_WINDOW_GRADIENT_LEVEL_PER_7                        7
#define _OSD_WINDOW_GRADIENT_LEVEL_PER_8                        0

#define GET_OSD_WINDOW_GRADIENT_LEVEL_PER()                     (g_stOsdWindow.b3WindowGradientLevelPer)
#define SET_OSD_WINDOW_GRADIENT_LEVEL_PER(x)                    (g_stOsdWindow.b3WindowGradientLevelPer = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient R
//--------------------------------------------------
#define _OSD_WINDOW_GRADIENT_POLARITY_DECREASE                  0
#define _OSD_WINDOW_GRADIENT_POLARITY_INCREASE                  1

#define GET_OSD_WINDOW_GRADIENT_POLARITY_R()                    (g_stOsdWindow.b1WindowGradientPolarityR)
#define SET_OSD_WINDOW_GRADIENT_POLARITY_R(x)                   (g_stOsdWindow.b1WindowGradientPolarityR = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient G
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_POLARITY_G()                    (g_stOsdWindow.b1WindowGradientPolarityG)
#define SET_OSD_WINDOW_GRADIENT_POLARITY_G(x)                   (g_stOsdWindow.b1WindowGradientPolarityG = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient B
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_POLARITY_B()                    (g_stOsdWindow.b1WindowGradientPolarityB)
#define SET_OSD_WINDOW_GRADIENT_POLARITY_B(x)                   (g_stOsdWindow.b1WindowGradientPolarityB = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Enable R
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_ENABLE_R()                      (g_stOsdWindow.b1WindowGradientEnableR)
#define SET_OSD_WINDOW_GRADIENT_ENABLE_R(x)                     (g_stOsdWindow.b1WindowGradientEnableR = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Enable G
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_ENABLE_G()                      (g_stOsdWindow.b1WindowGradientEnableG)
#define SET_OSD_WINDOW_GRADIENT_ENABLE_G(x)                     (g_stOsdWindow.b1WindowGradientEnableG = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Enable B
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_ENABLE_B()                      (g_stOsdWindow.b1WindowGradientEnableB)
#define SET_OSD_WINDOW_GRADIENT_ENABLE_B(x)                     (g_stOsdWindow.b1WindowGradientEnableB = (x))

//--------------------------------------------------
// MACRO for Osd Window Reference Delay
//--------------------------------------------------
#define GET_OSD_WINDOW_REFERENCE_DELAY()                        (g_stOsdWindow.b1WindowReferenceDelay)
#define SET_OSD_WINDOW_REFERENCE_DELAY(x)                       (g_stOsdWindow.b1WindowReferenceDelay = (x))

//--------------------------------------------------
// MACRO for Osd Window Border Priority
//--------------------------------------------------
#define GET_OSD_WINDOW_BORDER_PRIORITY()                        (g_stOsdWindow.b1WindowBorderPriority)
#define SET_OSD_WINDOW_BORDER_PRIORITY(x)                       (g_stOsdWindow.b1WindowBorderPriority = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Saturated Color Mode
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_MODE()          (g_stOsdWindow.b1WindowGradientSaturatedColorMode)
#define SET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_MODE(x)         (g_stOsdWindow.b1WindowGradientSaturatedColorMode = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Reversed Color Mode
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_REVERSED_COLOR_MODE()           (g_stOsdWindow.b1WindowGradientReversedColorMode)
#define SET_OSD_WINDOW_GRADIENT_REVERSED_COLOR_MODE(x)          (g_stOsdWindow.b1WindowGradientReversedColorMode = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Level Extension
//--------------------------------------------------
#define _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8                  0
#define _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_256                1

#define GET_OSD_WINDOW_GRADIENT_LEVEL_EXTENSION()               (g_stOsdWindow.b1WindowGradientLevelExtension)
#define SET_OSD_WINDOW_GRADIENT_LEVEL_EXTENSION(x)              (g_stOsdWindow.b1WindowGradientLevelExtension = (x))

//--------------------------------------------------
// MACRO for Osd Window Blend Enable
//--------------------------------------------------
#define GET_OSD_WINDOW_BLEND_ENABLE()                           (g_stOsdWindow.b1WindowBlend)
#define SET_OSD_WINDOW_BLEND_ENABLE(x)                          (g_stOsdWindow.b1WindowBlend = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Enable
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_ENABLE()                        (g_stOsdWindow.b1WindowGradient)
#define SET_OSD_WINDOW_GRADIENT_ENABLE(x)                       (g_stOsdWindow.b1WindowGradient = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Direction
//--------------------------------------------------
#define _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL               0
#define _OSD_WINDOW_GRADIENT_DIRECTION_VERTICAL                 1

#define GET_OSD_WINDOW_GRADIENT_DIRECTION()                     (g_stOsdWindow.b1WindowGradientDirection)
#define SET_OSD_WINDOW_GRADIENT_DIRECTION(x)                    (g_stOsdWindow.b1WindowGradientDirection = (x))

//--------------------------------------------------
// MACRO for Osd Window Shadow/Border/3D
//--------------------------------------------------
#define GET_OSD_WINDOW_BUTTON_ENABLE()                          (g_stOsdWindow.b1WindowButtonEnable)
#define SET_OSD_WINDOW_BUTTON_ENABLE(x)                         (g_stOsdWindow.b1WindowButtonEnable = (x))

//--------------------------------------------------
// MACRO for Osd Window Shadow/Border/3D
//--------------------------------------------------
#define _OSD_WINDOW_BUTTON_TYPE_SHADOW_1                        0
#define _OSD_WINDOW_BUTTON_TYPE_SHADOW_2                        1
#define _OSD_WINDOW_BUTTON_TYPE_SHADOW_3                        2
#define _OSD_WINDOW_BUTTON_TYPE_SHADOW_4                        3
#define _OSD_WINDOW_BUTTON_TYPE_3D_BUTTON_1                     4
#define _OSD_WINDOW_BUTTON_TYPE_3D_BUTTON_2                     5
#define _OSD_WINDOW_BUTTON_TYPE_RESERVED                        6
#define _OSD_WINDOW_BUTTON_TYPE_BORDER                          7

#define GET_OSD_WINDOW_BUTTON_TYPE()                            (g_stOsdWindow.b3WindowType)
#define SET_OSD_WINDOW_BUTTON_TYPE(x)                           (g_stOsdWindow.b3WindowType = (x))

//--------------------------------------------------
// MACRO for Osd Window Rotation Function Enable
//--------------------------------------------------
#define GET_OSD_WINDOW_ROTATION_FUNCTION_ENABLE()               (g_stOsdWindow.b1WindowRotationFunctionEnable)
#define SET_OSD_WINDOW_ROTATION_FUNCTION_ENABLE(x)              (g_stOsdWindow.b1WindowRotationFunctionEnable = (x))

//--------------------------------------------------
// MACRO for Osd Grid Window Number
//--------------------------------------------------
#define GET_OSD_GRID_WINDOW_NUMBER()                            (g_stOsdGridWindow.b3GridLineWindowNumber)
#define SET_OSD_GRID_WINDOW_NUMBER(x)                           (g_stOsdGridWindow.b3GridLineWindowNumber = (x))

//--------------------------------------------------
// MACRO for Osd Grid Line Width
//--------------------------------------------------
#define GET_OSD_GRID_LINE_WIDTH()                               (g_stOsdGridWindow.b2GridLineWidth)
#define SET_OSD_GRID_LINE_WIDTH(x)                              (g_stOsdGridWindow.b2GridLineWidth = (x))

//--------------------------------------------------
// MACRO for Osd Grid Line Color
//--------------------------------------------------
#define GET_OSD_GRID_LINE_COLOR()                               (g_stOsdGridWindow.b6GridLineColor)
#define SET_OSD_GRID_LINE_COLOR(x)                              (g_stOsdGridWindow.b6GridLineColor = (x))

//--------------------------------------------------
// MACRO for Osd Grid Line Horizontal Enable
//--------------------------------------------------
#define GET_OSD_GRID_LINE_HORIZONTAL_ENABLE()                   (g_stOsdGridWindow.b1GridLineHorizontalEnable)
#define SET_OSD_GRID_LINE_HORIZONTAL_ENABLE(x)                  (g_stOsdGridWindow.b1GridLineHorizontalEnable = (x))

//--------------------------------------------------
// MACRO for Osd Grid Line Vertical Enable
//--------------------------------------------------
#define GET_OSD_GRID_LINE_VERTICAL_ENABLE()                     (g_stOsdGridWindow.b1GridLineVerticalEnable)
#define SET_OSD_GRID_LINE_VERTICAL_ENABLE(x)                    (g_stOsdGridWindow.b1GridLineVerticalEnable = (x))

//--------------------------------------------------
// MACRO for Osd Grid Line Offset
//--------------------------------------------------
#define GET_OSD_GRID_LINE_OFFSET()                              (g_stOsdGridWindow.b6GridLineOffset)
#define SET_OSD_GRID_LINE_OFFSET(x)                             (g_stOsdGridWindow.b6GridLineOffset = (x))

//--------------------------------------------------
// MACRO for Osd Grid Line Pitch
//--------------------------------------------------
#define GET_OSD_GRID_LINE_PITCH()                               (g_stOsdGridWindow.b15GridLinePitch)
#define SET_OSD_GRID_LINE_PITCH(x)                              (g_stOsdGridWindow.b15GridLinePitch = (x))

//--------------------------------------------------
// MACRO for Osd Grid Line Function Enable
//--------------------------------------------------
#define GET_OSD_GRID_LINE_FUNCTION_ENABLE()                     (g_stOsdGridWindow.b1GridFunctionEnable)
#define SET_OSD_GRID_LINE_FUNCTION_ENABLE(x)                    (g_stOsdGridWindow.b1GridFunctionEnable = (x))



//***************************************************************
// SRAM
//***************************************************************
//--------------------------------------------------
// ScalerOsdSramAddressCount.c
//--------------------------------------------------
#define _OSD_MAP_B_ROW_OFFSET                                   100

#define ROW_MAPA(x)                                             (x)
#define ROW_MAPB(x)                                             ((x) + _OSD_MAP_B_ROW_OFFSET)

#define GET_OSD_MAPA_COL_MAX()                                  (g_ucColAMax)
#define SET_OSD_MAPA_COL_MAX(x)                                 (g_ucColAMax = (x))

#define GET_OSD_MAPB_COL_MAX()                                  (g_ucColBMax)
#define SET_OSD_MAPB_COL_MAX(x)                                 (g_ucColBMax = (x))

//--------------------------------------------------
// ScalerOsdHardwareVLC.c
//--------------------------------------------------
#define _OSD_ROTATE_HARDWARE_ROTATION_DISABLE                   (0x00)
#define _OSD_ROTATE_HARDWARE_ROTATION_ENABLE                    (_BIT2)

#define _OSD_ROTATE_NORMAL                                      (0x00)
#define _OSD_ROTATE_ROTATION                                    (_BIT0)

#define _OSD_COMPRESSION_DISABLE                                (0x00)
#define _OSD_COMPRESSION_ENABLE                                 (_BIT0)


#define VLC_TABLE_SIZE(x)                                       (((WORD)(x)[8] << 8) + (x)[9])

//--------------------------------------------------
// ScalerOsdChange4BitColor.c
//--------------------------------------------------
#define _OSD_4BIT_PALETTE_00_01_02_03                           0
#define _OSD_4BIT_PALETTE_16_17_18_19                           _BIT0
#define _OSD_4BIT_PALETTE_32_33_34_35                           _BIT1
#define _OSD_4BIT_PALETTE_48_49_50_51                           (_BIT1 | _BIT0)

#define _OSD_4BIT_PALETTE_04_05_06_07                           0
#define _OSD_4BIT_PALETTE_20_21_22_23                           _BIT2
#define _OSD_4BIT_PALETTE_36_37_38_39                           _BIT3
#define _OSD_4BIT_PALETTE_52_53_54_55                           (_BIT3 | _BIT2)

#define _OSD_4BIT_PALETTE_08_09_10_11                           0
#define _OSD_4BIT_PALETTE_24_25_26_27                           _BIT4
#define _OSD_4BIT_PALETTE_40_41_42_43                           _BIT5
#define _OSD_4BIT_PALETTE_56_57_58_59                           (_BIT5 | _BIT4)

#define _OSD_4BIT_PALETTE_12_13_14_15                           0
#define _OSD_4BIT_PALETTE_28_29_30_31                           _BIT6
#define _OSD_4BIT_PALETTE_44_45_46_47                           _BIT7
#define _OSD_4BIT_PALETTE_50_61_62_63                           (_BIT7 | _BIT6)

//--------------------------------------------------
// ScalerOsdChange1BitColor.c
//--------------------------------------------------
#define FG_COLOR(x)                                             (x)
#define BG_COLOR(x)                                             (x)

//--------------------------------------------------
// ScalerOsdChange2BitColor.c
//--------------------------------------------------
#define COLOR_00(x)                                             (x)
#define COLOR_01(x)                                             (x)
#define COLOR_10(x)                                             (x)
#define COLOR_11(x)                                             (x)


//***************************************************************
// Function
//***************************************************************
//--------------------------------------------------
// ScalerOsdPosition.c
//--------------------------------------------------
#define X_POS(x)                                                (x)
#define Y_POS(x)                                                (x)
//****************************************************************************
// INTERFACE STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Osd Options
//--------------------------------------------------
typedef enum
{
    _OSD_A,
    _OSD_B,
} EnumOsdMapType;

typedef enum
{
    _OSD_ROTATE_DEGREE_0,
    _OSD_ROTATE_DEGREE_90,
    _OSD_ROTATE_DEGREE_270,
    _OSD_ROTATE_DEGREE_180,
} EnumOsdRotateType;

typedef enum
{
    _OSD_BLANK_FONT = 0x00,
    _OSD_BLANK_ALIGN = _BIT0,
} EnumOsdBlankType;

typedef enum
{
    _OSD_1BIT_SHRINK_BY_MIDDLE,
    _OSD_1BIT_SHRINK_BY_LEFT,
    _OSD_1BIT_SHRINK_BY_RIGHT,
} EnumOsd1BitShrinkType;

typedef enum
{
    _OSD_2BIT_CHAR_BIT7_BY_CHANGE_PALETTE,
    _OSD_2BIT_CHAR_BIT7_BY_SELECT_FONT,
} EnumOsd2BitCharBit7Type;

typedef enum
{
    _OSD_4BIT_BACKGROUND_TO_BYTE2,
    _OSD_4BIT_BACKGROUND_TO_BYTE0,
} EnumOsd4BitBackgroundType;

typedef enum
{
    _OSD_MAP_A_REMAPPING_DISABLE,
    _OSD_MAP_A_REMAPPING_ENABLE,
} EnumOsdRotateMapA;

typedef enum
{
    _OSD_MAP_B_REMAPPING_DISABLE,
    _OSD_MAP_B_REMAPPING_ENABLE,
} EnumOsdRotateMapB;

typedef enum
{
    _OSD_FONT_LIB_ROTATION_DISABLE,
    _OSD_FONT_LIB_ROTATION_ENABLE,
} EnumOsdRotateFontLib;

typedef enum
{
    _OSD_VSYNC_SELECT_DVS,
    _OSD_VSYNC_SELECT_ENA,
} EnumOsdVsyncSelectType;

typedef enum
{
    _OSD_WINDOW_0,
    _OSD_WINDOW_1,
    _OSD_WINDOW_2,
    _OSD_WINDOW_3,
    _OSD_WINDOW_4,
    _OSD_WINDOW_5,
    _OSD_WINDOW_6,
    _OSD_WINDOW_7,
    _OSD_WINDOW_8,
    _OSD_WINDOW_9,

    _OSD_WINDOW_4_1,
    _OSD_WINDOW_4_2,
    _OSD_WINDOW_4_3,
    _OSD_WINDOW_4_4,
    _OSD_WINDOW_4_5,
    _OSD_WINDOW_4_6,
    _OSD_WINDOW_4_7,
    _OSD_WINDOW_4_8,

#if(_OSD_WINDOW_5_1_5_8_SUPPORT == _ON)
    _OSD_WINDOW_5_1,
    _OSD_WINDOW_5_2,
    _OSD_WINDOW_5_3,
    _OSD_WINDOW_5_4,
    _OSD_WINDOW_5_5,
    _OSD_WINDOW_5_6,
    _OSD_WINDOW_5_7,
    _OSD_WINDOW_5_8,
#endif

    _OSD_WINDOW_ALL,
} EnumOsdWindowsType;

typedef enum
{
    _OSD_WINDOW_6_FUNCTION_DISABLE,
    _OSD_WINDOW_6_FUNCTION_NO_BLENDING_BOTH,
    _OSD_WINDOW_6_FUNCTION_NO_BLENDING_FOREGROUND,
    _OSD_WINDOW_6_FUNCTION_NO_BLENDING_BACKGROUND,
    _OSD_WINDOW_6_FUNCTION_BLENDING_BOTH,
} EnumOsdWindow6FunctionType;

typedef enum
{
    _OSD_WINDOW_7_FUNCTION_DISABLE,
    _OSD_WINDOW_7_FUNCTION_NO_BLENDING_BOTH,
    _OSD_WINDOW_7_FUNCTION_NO_BLENDING_FOREGROUND,
    _OSD_WINDOW_7_FUNCTION_NO_BLENDING_BACKGROUND,
    _OSD_WINDOW_7_FUNCTION_BLENDING_BOTH,
    _OSD_WINDOW_7_FUNCTION_MASK_REGION_APPEAR,
    _OSD_WINDOW_7_FUNCTION_MASK_REGION_TRANSPARENT_ALL,
    _OSD_WINDOW_7_FUNCTION_MASK_REGION_TRANSPARENT_FONT,
} EnumOsdWindow7FunctionType;

typedef enum
{
    _OSD_WINDOW_PRIORITY_LOWER_THAN_FONT,
    _OSD_WINDOW_PRIORITY_HIGHTER_THAN_FONT,
} EnumOsdWindowPriorityType;

typedef enum
{
    _OSD_TRANSPARENCY_DISABLE = 0x00,
    _OSD_TRANSPARENCY_ONLY_WINDOW = _BIT2,
    _OSD_TRANSPARENCY_ALL = _BIT3,
    _OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND = (_BIT3 | _BIT2),
} EnumOsdTransparencyType;

typedef enum
{
    _OSD_POSITION_GLOBAL_A,
    _OSD_POSITION_GLOBAL_B,
    _OSD_POSITION_FONT_A,
    _OSD_POSITION_FONT_B,
} EnumOsdPositionType;

typedef enum
{
    _OSD_DOUBLE_WIDTH_DISABLE,
    _OSD_DOUBLE_WIDTH_ENABLE,
} EnumOsdDoubleWidthType;

typedef enum
{
    _OSD_DOUBLE_HEIGHT_DISABLE,
    _OSD_DOUBLE_HEIGHT_ENABLE,
} EnumOsdDoubleHeightType;

typedef enum
{
    _OSD_FIRST_DELAY,
    _OSD_SECOND_DELAY,
} EnumOsdReferenceType;

typedef enum
{
    _OSD_HORIZONTAL_DELAY_STEP_4_PIXEL,
    _OSD_HORIZONTAL_DELAY_STEP_1_PIXEL,
} EnumOsdHorizontalDelayStepType;

typedef enum
{
    _OSD_ROUNDED_WIN_SIZE_8X8 = 0x00,
    _OSD_ROUNDED_WIN_SIZE_16X16 = _BIT1,

#if(_OSD_WINDOW_ROUNED_PATTERN_32X32_SUPPORT == _ON)
    _OSD_ROUNDED_WIN_SIZE_32X32 = _BIT2,
#endif

} EnumOsdRoundedWindowType;

typedef enum
{
    _OSD_SPECIAL_COLOR_MASK_AND_OPERATION,
    _OSD_SPECIAL_COLOR_MASK_OR_OPERATION,
} EnumOsdSpecialColorMaskOperation;

typedef enum
{
    _OSD_DECODE_COMPRESSED = 0x00,
    _OSD_DECODE_NON_COMPRESSED = _BIT1,
} EnumOsdDecodeCompressionType;

//--------------------------------------------------
// ScalerOsdDrawWindow.c
//--------------------------------------------------
typedef struct
{
    BYTE b5WindowNumber                      : 5;
    BYTE b1WindowEnable                      : 1;

    BYTE b6WindowColor                       : 6;
    BYTE b6WindowColorShadow                 : 6;
    BYTE b6WindowColorBorder                 : 6;
    BYTE b3WindowShadowBorderPixelWidth      : 3;
    BYTE b3WindowShadowBorderPixelHeight     : 3;

    BYTE b2WindowGradientLevelStep           : 2;
    BYTE b3WindowGradientLevelPer            : 3;
    BYTE b1WindowGradientPolarityR           : 1;
    BYTE b1WindowGradientPolarityG           : 1;
    BYTE b1WindowGradientPolarityB           : 1;
    BYTE b1WindowGradientEnableR             : 1;
    BYTE b1WindowGradientEnableG             : 1;
    BYTE b1WindowGradientEnableB             : 1;

    BYTE b1WindowGradientSaturatedColorMode  : 1;
    BYTE b1WindowGradientReversedColorMode   : 1;
    BYTE b1WindowReferenceDelay              : 1;
    BYTE b1WindowBorderPriority              : 1;
    BYTE b1WindowGradientLevelExtension      : 1;

    BYTE b1WindowBlend                       : 1;
    BYTE b1WindowGradient                    : 1;
    BYTE b1WindowGradientDirection           : 1;
    BYTE b1WindowButtonEnable                : 1;
    BYTE b3WindowType                        : 3;

    BYTE b1WindowRotationFunctionEnable      : 1;

} StructOsdWindow;

//--------------------------------------------------
// ScalerOsdDrawGridLine.c
//--------------------------------------------------
typedef struct
{
    BYTE b3GridLineWindowNumber             : 3;
    BYTE b2GridLineWidth                    : 2;
    BYTE b6GridLineColor                    : 6;
    BYTE b1GridLineHorizontalEnable         : 1;
    BYTE b1GridLineVerticalEnable           : 1;
    BYTE b6GridLineOffset                   : 6;
    WORD b15GridLinePitch                   : 15;
    BYTE b1GridFunctionEnable               : 1;

} StructOsdGridWindow;


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
//--------------------------------------------------
// ScalerOsdSramAddressCount.c
//--------------------------------------------------
extern BYTE g_ucColAMax;
extern BYTE g_ucColBMax;

//--------------------------------------------------
// ScalerOsdDrawWindow.c
//--------------------------------------------------
extern StructOsdWindow g_stOsdWindow;

//--------------------------------------------------
// ScalerOsdDrawGridLine.c
//--------------------------------------------------
extern StructOsdGridWindow g_stOsdGridWindow;

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
//--------------------------------------------------
// Command
//--------------------------------------------------
extern void ScalerOsdAddrMsb(BYTE ucValue);
extern void ScalerOsdAddrLsb(BYTE ucValue);
extern void ScalerOsdAddrSet(EnumOsdAddrIndicateType enumAddrIndicator, EnumOsdWriteType enumByteSel, WORD usAddress, EnumOsdDBufType enumDbufEnable);
extern void ScalerOsdDataPort(BYTE ucValue);
extern void ScalerOsdScrambleLoadFontAddrHsbClr(void);
extern void ScalerOsdScrambleLoadFontAddrHsbSet(void);
extern void ScalerOsdBurstWriteDataPort(BYTE *pucAddress, WORD usWriteLength, BYTE ucBankNum, BYTE ucTableType, bit bTableLocation);
extern void ScalerOsdWriteByte(BYTE ucIndicateAndWriteByte, EnumOsdDBufType enumDBuf, WORD usAddr, BYTE ucData);
extern void ScalerOsdWriteAllByte(BYTE ucIndicateAndDbuf, WORD usAddr, BYTE ucByte0, BYTE ucByte1, BYTE ucByte2);
extern void ScalerOsdWriteProtection(bit bEnable, EnumOsdWriteType enumOsdWriteType, BYTE ucBitSelect);
extern BYTE ScalerOsdFrameControlByteGet(WORD usAddr, EnumOsdWriteType enumOsdWriteType);
extern void ScalerOsdFrameControlByte(WORD usAddr, EnumOsdWriteType enumOsdWriteType, BYTE ucData);
extern void ScalerOsdFrameControlAllByte(WORD usAddr, EnumOsdDBufType enumDoubleBuffer, BYTE ucByte0, BYTE ucByte1, BYTE ucByte2);

//--------------------------------------------------
// Windows
//--------------------------------------------------
extern void ScalerOsdWindowDisable(EnumOsdWindowsType enumOsdWindowsType);
extern void ScalerOsdDrawWindow(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd);
extern void ScalerOsdWindow6SpecialFunction(EnumOsdWindow6FunctionType enumOsdWindow6FunctionType);
extern void ScalerOsdWindow7SpecialFunction(EnumOsdWindow7FunctionType enumOsdWindow7FunctionType);
extern void ScalerOsdWindowChessboard(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucChessBoardColor1, BYTE ucChessBoardColor2);
extern void ScalerOsdWindowHighlightFunction(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucForegroundColor, BYTE ucBackgroundColor, BYTE ucCharactorBorderColor);
extern void ScalerOsdWindowSaturatedColorSelect(EnumOsdWindowsType enumOsdWindowsType, BYTE ucColorR, BYTE ucColorG, BYTE ucColorB);
extern void ScalerOsdWindowPriority(EnumOsdWindowsType enumOsdWindowsType, EnumOsdWindowPriorityType enumOsdWindowPriorityType);
extern void ScalerOsdRotationWindowSize(EnumOsdMapType enumOsdMapType, WORD usLength, WORD usWidth);
extern void ScalerOsdDrawGridLine(void);
extern void ScalerOsdDrawGridLinePanelPitch(WORD usPitchHorizontal, WORD usPitchVertical);
extern void ScalerOsdWindowBorderPriority(EnumOsdWindowsType enumOsdWindowsType, bit bBorderrPriorityEnable);
extern void ScalerOsdWindowGradientLevel(EnumOsdWindowsType enumOsdWindowsType, BYTE ucLevelR, BYTE ucLevelG, BYTE ucLevelB);

extern void ScalerOsdRoundedWindowOnOff(EnumOsdWindowsType enumOsdWindowsType, bit bOnOff, bit bUpperLeft, bit bLowerLeft, bit bUpperRight, bit bLowerRight);
extern void ScalerOsdRoundedWindowPattern8x8(BYTE ucIdx, BYTE ucType);
extern void ScalerOsdRoundedWindowPattern16x16(BYTE ucIdx, BYTE ucType);
extern void ScalerOsdRoundedWindowPattern32x32(BYTE ucIdx, BYTE ucType);
extern void ScalerOsdRoundedWindowSize(EnumOsdWindowsType enumOsdWindowsType, EnumOsdRoundedWindowType enumRoundedWinSize);
extern void ScalerOsdWindowGrayLevel(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucPixelStep, BYTE ucDecimalPart);
extern void ScalerOsdWindowGradientStep(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucStep);
extern void ScalerOsdWindowSpecialColorMask(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, EnumOsdSpecialColorMaskOperation enumOsdSpecialColorMaskOperation);

//--------------------------------------------------
// SRAM
//--------------------------------------------------
extern void ScalerOsdScrambleDoubleBufferDepth(BYTE ucValue);
extern void ScalerOsdSramAddressSet(WORD usSramAddress, EnumOsdWriteType enumOsdWriteType);
extern void ScalerOsdSramAddressCount(BYTE ucRow, BYTE ucCol, EnumOsdWriteType enumOsdWriteType);
extern void ScalerOsdCommandByte(WORD usAddr, EnumOsdWriteType enumOsdWriteType, BYTE ucData);
extern void ScalerOsdCommandAllByte(WORD usCharAddr, BYTE ucByte0, BYTE ucByte1, BYTE ucByte2);
extern void ScalerOsdCharCommandByteSeries(WORD usCharAddr, EnumOsdWriteType enumOsdWriteType, BYTE ucData, WORD usLength);
extern void ScalerOsdCharCommandAllByteSeries(WORD usCharAddr, BYTE ucByte0, BYTE ucByte1, BYTE ucByte2, WORD usLength);
extern void ScalerOsdCharShadowBorderColor(BYTE ucIndex);
extern void ScalerOsd2BitFontOffset(WORD usOffset);
extern void ScalerOsdSramDataValue(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucValue, EnumOsdWriteType enumOsdWriteType);
extern void ScalerOsdSramDataValue2Byte(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucValue1, BYTE ucValue2, EnumOsdWriteType enumOsdWriteType);
extern void ScalerOsdBlankFont(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucHeight, BYTE ucPixelLength, BYTE ucBackgroundColor, EnumOsdBlankType enumOsdBlankingType);
extern void ScalerOsdChange1BitColor(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucHeight, BYTE ucForegroundColor, BYTE ucBackgroundColor);
extern void ScalerOsdChange1BitColorFont256_511(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucHeight, BYTE ucForegroundColor, BYTE ucBackgroundColor);
extern void ScalerOsdChange2BitColor(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucHeight, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);
extern void ScalerOsdChange4BitColor(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucHeight, BYTE ucBackgroundColor, BYTE ucColorPaletteType);
extern void ScalerOsd1BitFontShrink(EnumOsd1BitShrinkType enumOsd1BitShrinkType);
extern void ScalerOsd2BitFontByte1Bit7Swap(EnumOsd2BitCharBit7Type enumOsd2BitCharBit7Type);
extern void ScalerOsdSetBlinking(bit bEnable);
extern void ScalerOsdBlankCommandColorExtension(bit bEnable);
extern void ScalerReference4BitBackground(EnumOsd4BitBackgroundType enumOsd4BitBackgroundType);
extern void ScalerOsdRowHeight(BYTE ucRow, BYTE ucHeight, BYTE ucLength);
extern void ScalerOsdCharacterWidth(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucLength);
extern void ScalerOsdFontLibraryRotation(void);
extern void ScalerOsdAlignMark(bit bEnableDisable);
extern void ScalerOsdFontMaskRegionSet(EnumOsdMapType enumOsdMapType, BYTE ucRowStart, BYTE ucRowEnd, BYTE ucColumnStart, BYTE ucColumnEnd);
extern void ScalerOsdFontMaskRegionOnOff(EnumOsdMapType enumOsdMapType, bit bOnOff);
extern void ScalerOsdChange2BitColor16_31(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucHeight, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);
extern void ScalerOsdCompressionCtrl(EnumOsdDecodeCompressionType enumDecodeCompression, bit bCompressionEnable);

//--------------------------------------------------
// Function
//--------------------------------------------------
extern void ScalerOsdCircuitActivated(bit bEnable);
extern bit  ScalerOsdGetOsdEnable(void);
extern void ScalerOsdEnableOsd(void);
extern void ScalerOsdDisableOsd(void);
extern void ScalerOsdVerticalStartSelect(EnumOsdVsyncSelectType enumOsdVsyncSelectType);
extern void ScalerOsdSetTransparencyType(EnumOsdTransparencyType enumOsdTransparencyType);
extern void ScalerOsdSetColorPalette(BYTE ucIndex, BYTE ucColorR, BYTE ucColorG, BYTE ucColorB);
extern BYTE ScalerOsdPositionOffsetVerticalAlignByDVBGStart(BYTE ucVOffset);
extern void ScalerOsd2FontFunction(bit bEnable);
extern void ScalerOsdPopOn(bit bEnable, EnumOsdMapType enumOsdMapType);
extern void ScalerOsdRollUp(bit bEnable, BYTE ucRowStart, BYTE ucRowBack);
extern void ScalerOsdVerticalBoundarySize(WORD usUpperBoundary, WORD usLowerBoundary);
extern void ScalerOsdSpecificColorBlending(bit bEnable, BYTE ucIndex);
extern void ScalerOsdReferenceDelay(EnumOsdMapType enumOsdMapType, EnumOsdReferenceType enumOsdReferenceType);
extern EnumOsdHorizontalDelayStepType ScalerOsdGetHorizontalDelayStep(void);
extern void ScalerOsdHorizontalDelayStep(EnumOsdHorizontalDelayStepType enumOsdHorizontalDelayStepType);
extern void ScalerOsdDoubleBufferOnOff(EnumOsdDBufType enumOnOff);
extern void ScalerOsdGlobalDoubleBuffer(bit bEnableDisable);
extern void ScalerOsdFontWindowVericalAlignemnt(bit bOnOff);
extern bit ScalerOsdGetDoubleFunctionH(void);
extern bit ScalerOsdGetDoubleFunctionV(void);


#endif
