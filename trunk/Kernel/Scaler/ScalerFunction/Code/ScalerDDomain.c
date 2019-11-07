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
// ID Code      : ScalerDDomain.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DDOMAIN__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_FREESYNC_OD_MEASURE == _ON)
#define _FREESYNC_OD_MEASURE_GL_ENABLE_REG    P7_F3_DISP_PG_R_INITIAL
#define _FREESYNC_OD_MEASURE_GL_VALUE_REG     P7_F4_DISP_PG_G_INITIAL
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_PANEL_EXIST_MULTIPANEL == _ON)
BYTE g_ucDDomainPanelIndex;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
bit ScalerDDomainGetBackgroundStatus(EnumDisplayDataPath enumDisplayDataPath);
void ScalerDDomainBackgroundEnable(EnumDisplayDataPath enumDisplayDataPath, bit bEnable);
void ScalerDDomainBackgroundSetColor(EnumDisplayDataPath enumDisplayDataPath, BYTE ucRed, BYTE ucGreen, BYTE ucBlue);
void ScalerDDomainPatternGenEnable(bit bEnable);
void ScalerDDomainPatternGenAdjustColor(BYTE ucRed, BYTE ucGreen, BYTE ucBlue);

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
void ScalerDDomainBackgroundSetColor10bit(WORD usRed, WORD usGreen, WORD usBlue);
void ScalerDDomainPatternGenAdjustColor10bit(WORD usRed, WORD usGreen, WORD usBlue);
#endif

#if(_FREESYNC_OD_MEASURE == _ON)
void ScalerDDomainFREESYNCODSetBackgroundGrayLevel(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get Display Background Status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDDomainGetBackgroundStatus(EnumDisplayDataPath enumDisplayDataPath)
{
    if((enumDisplayDataPath & _DISPLAY_PATH_M1) == _DISPLAY_PATH_M1)
    {
        return (ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT5));
    }

    if((enumDisplayDataPath & _DISPLAY_PATH_M2) == _DISPLAY_PATH_M2)
    {
        return (ScalerGetBit(P40_28_VIDEO_DISPLAY_CONTROL_REG_M2, _BIT5));
    }

    if((enumDisplayDataPath & _DISPLAY_PATH_S1) == _DISPLAY_PATH_S1)
    {
        return (ScalerGetBit(P80_28_VIDEO_DISPLAY_CONTROL_REG_S1, _BIT5));
    }

    if((enumDisplayDataPath & _DISPLAY_PATH_S2) == _DISPLAY_PATH_S2)
    {
        return (ScalerGetBit(PC0_28_VIDEO_DISPLAY_CONTROL_REG_S2, _BIT5));
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Display Force to Background Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDDomainBackgroundEnable(EnumDisplayDataPath enumDisplayDataPath, bit bEnable)
{
    if((enumDisplayDataPath & _DISPLAY_PATH_M1) == _DISPLAY_PATH_M1)
    {
        if(bEnable == _ENABLE)
        {
            // M1 Enable Force to Back Ground
            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, _BIT5);
        }
        else
        {
            // M1 Disable Force to Back Ground
            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, 0x00);
        }
    }

    if((enumDisplayDataPath & _DISPLAY_PATH_M2) == _DISPLAY_PATH_M2)
    {
        if(bEnable == _ENABLE)
        {
            // M2 Enable Force to Back Ground
            ScalerSetBit(P40_28_VIDEO_DISPLAY_CONTROL_REG_M2, ~_BIT5, _BIT5);
        }
        else
        {
            // M2 Disable Force to Back Ground
            ScalerSetBit(P40_28_VIDEO_DISPLAY_CONTROL_REG_M2, ~_BIT5, 0x00);
        }
    }

    if((enumDisplayDataPath & _DISPLAY_PATH_S1) == _DISPLAY_PATH_S1)
    {
        if(bEnable == _ENABLE)
        {
            // S1 Enable Force to Back Ground
            ScalerSetBit(P80_28_VIDEO_DISPLAY_CONTROL_REG_S1, ~_BIT5, _BIT5);
        }
        else
        {
            // S1 Disable Force to Back Ground
            ScalerSetBit(P80_28_VIDEO_DISPLAY_CONTROL_REG_S1, ~_BIT5, 0x00);
        }
    }

    if((enumDisplayDataPath & _DISPLAY_PATH_S2) == _DISPLAY_PATH_S2)
    {
        if(bEnable == _ENABLE)
        {
            // S2 Enable Force to Back Ground
            ScalerSetBit(PC0_28_VIDEO_DISPLAY_CONTROL_REG_S2, ~_BIT5, _BIT5);
        }
        else
        {
            // S2 Disable Force to Back Ground
            ScalerSetBit(PC0_28_VIDEO_DISPLAY_CONTROL_REG_S2, ~_BIT5, 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Set Display Background Color
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void ScalerDDomainBackgroundSetColor(EnumDisplayDataPath enumDisplayDataPath, BYTE ucRed, BYTE ucGreen, BYTE ucBlue)
{
    if((enumDisplayDataPath & _DISPLAY_PATH_M1) == _DISPLAY_PATH_M1)
    {
        // M1 Reset Port index
        ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT5, 0x00);
        ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT5, _BIT5);

        // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
        ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT_M1, ucRed);
        ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT_M1, ucGreen);
        ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT_M1, ucBlue);
        ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT_M1, 0x00);

        ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT5, 0x00);
    }

    if((enumDisplayDataPath & _DISPLAY_PATH_M2) == _DISPLAY_PATH_M2)
    {
        // M2 Reset Port index
        ScalerSetBit(P40_6C_BG_COLOR_ACCESS_EN_M2, ~_BIT5, 0x00);
        ScalerSetBit(P40_6C_BG_COLOR_ACCESS_EN_M2, ~_BIT5, _BIT5);

        // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
        ScalerSetByte(P40_6D_BG_COLOR_DATA_PORT_M2, ucRed);
        ScalerSetByte(P40_6D_BG_COLOR_DATA_PORT_M2, ucGreen);
        ScalerSetByte(P40_6D_BG_COLOR_DATA_PORT_M2, ucBlue);
        ScalerSetByte(P40_6D_BG_COLOR_DATA_PORT_M2, 0x00);

        ScalerSetBit(P40_6C_BG_COLOR_ACCESS_EN_M2, ~_BIT5, 0x00);
    }

    if((enumDisplayDataPath & _DISPLAY_PATH_S1) == _DISPLAY_PATH_S1)
    {
        // S1 Reset Port index
        ScalerSetBit(P80_6C_BG_COLOR_ACCESS_EN_S1, ~_BIT5, 0x00);
        ScalerSetBit(P80_6C_BG_COLOR_ACCESS_EN_S1, ~_BIT5, _BIT5);

        // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
        ScalerSetByte(P80_6D_BG_COLOR_DATA_PORT_S1, ucRed);
        ScalerSetByte(P80_6D_BG_COLOR_DATA_PORT_S1, ucGreen);
        ScalerSetByte(P80_6D_BG_COLOR_DATA_PORT_S1, ucBlue);
        ScalerSetByte(P80_6D_BG_COLOR_DATA_PORT_S1, 0x00);

        ScalerSetBit(P80_6C_BG_COLOR_ACCESS_EN_S1, ~_BIT5, 0x00);
    }

    if((enumDisplayDataPath & _DISPLAY_PATH_S2) == _DISPLAY_PATH_S2)
    {
        // S2 Reset Port index
        ScalerSetBit(PC0_6C_BG_COLOR_ACCESS_EN_S2, ~_BIT5, 0x00);
        ScalerSetBit(PC0_6C_BG_COLOR_ACCESS_EN_S2, ~_BIT5, _BIT5);

        // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
        ScalerSetByte(PC0_6D_BG_COLOR_DATA_PORT_S2, ucRed);
        ScalerSetByte(PC0_6D_BG_COLOR_DATA_PORT_S2, ucGreen);
        ScalerSetByte(PC0_6D_BG_COLOR_DATA_PORT_S2, ucBlue);
        ScalerSetByte(PC0_6D_BG_COLOR_DATA_PORT_S2, 0x00);

        ScalerSetBit(PC0_6C_BG_COLOR_ACCESS_EN_S2, ~_BIT5, 0x00);
    }
}

//--------------------------------------------------
// Description  : Display Pattern Gen Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDDomainPatternGenEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable D Domain PG
        ScalerSetBit(P7_F0_DISP_PG_R_CTRL, ~_BIT7, _BIT7);
        ScalerSetBit(P87_F0_DISP_PG_R_CTRL_SUB, ~_BIT7, _BIT7);
    }
    else
    {
        // Disable D Domain PG
        ScalerSetBit(P7_F0_DISP_PG_R_CTRL, ~_BIT7, 0x00);
        ScalerSetBit(P87_F0_DISP_PG_R_CTRL_SUB, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Set Display Pattern Gen Color
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void ScalerDDomainPatternGenAdjustColor(BYTE ucRed, BYTE ucGreen, BYTE ucBlue)
{
    ScalerSetByte(P7_F3_DISP_PG_R_INITIAL, ucRed);
    ScalerSetByte(P7_F4_DISP_PG_G_INITIAL, ucGreen);
    ScalerSetByte(P7_F5_DISP_PG_B_INITIAL, ucBlue);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    ScalerSetByte(P87_F3_DISP_PG_R_INITIAL_SUB, ucRed);
    ScalerSetByte(P87_F4_DISP_PG_G_INITIAL_SUB, ucGreen);
    ScalerSetByte(P87_F5_DISP_PG_B_INITIAL_SUB, ucBlue);
#endif
}


#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set Display Background Color (10bit)
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void ScalerDDomainBackgroundSetColor10bit(WORD usRed, WORD usGreen, WORD usBlue) // 10bit
{
    // M1 Reset Port index
    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT5, 0x00);
    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT5, _BIT5);

    // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
    ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT_M1, (usRed >> 2));
    ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT_M1, (usGreen >> 2));
    ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT_M1, (usBlue >> 2));
    ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT_M1, ((usRed & 0x03) << 6) | ((usGreen & 0x03) << 4) | ((usBlue & 0x03) << 2));

    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT5, 0x00);

    // M2 Reset Port index
    ScalerSetBit(P40_6C_BG_COLOR_ACCESS_EN_M2, ~_BIT5, 0x00);
    ScalerSetBit(P40_6C_BG_COLOR_ACCESS_EN_M2, ~_BIT5, _BIT5);

    // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
    ScalerSetByte(P40_6D_BG_COLOR_DATA_PORT_M2, (usRed >> 2));
    ScalerSetByte(P40_6D_BG_COLOR_DATA_PORT_M2, (usGreen >> 2));
    ScalerSetByte(P40_6D_BG_COLOR_DATA_PORT_M2, (usBlue >> 2));
    ScalerSetByte(P40_6D_BG_COLOR_DATA_PORT_M2, ((usRed & 0x03) << 6) | ((usGreen & 0x03) << 4) | ((usBlue & 0x03) << 2));

    ScalerSetBit(P40_6C_BG_COLOR_ACCESS_EN_M2, ~_BIT5, 0x00);

    // S1 Reset Port index
    ScalerSetBit(P80_6C_BG_COLOR_ACCESS_EN_S1, ~_BIT5, 0x00);
    ScalerSetBit(P80_6C_BG_COLOR_ACCESS_EN_S1, ~_BIT5, _BIT5);

    // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
    ScalerSetByte(P80_6D_BG_COLOR_DATA_PORT_S1, (usRed >> 2));
    ScalerSetByte(P80_6D_BG_COLOR_DATA_PORT_S1, (usGreen >> 2));
    ScalerSetByte(P80_6D_BG_COLOR_DATA_PORT_S1, (usBlue >> 2));
    ScalerSetByte(P80_6D_BG_COLOR_DATA_PORT_S1, ((usRed & 0x03) << 6) | ((usGreen & 0x03) << 4) | ((usBlue & 0x03) << 2));

    ScalerSetBit(P80_6C_BG_COLOR_ACCESS_EN_S1, ~_BIT5, 0x00);

    // S2 Reset Port index
    ScalerSetBit(PC0_6C_BG_COLOR_ACCESS_EN_S2, ~_BIT5, 0x00);
    ScalerSetBit(PC0_6C_BG_COLOR_ACCESS_EN_S2, ~_BIT5, _BIT5);

    // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
    ScalerSetByte(PC0_6D_BG_COLOR_DATA_PORT_S2, (usRed >> 2));
    ScalerSetByte(PC0_6D_BG_COLOR_DATA_PORT_S2, (usGreen >> 2));
    ScalerSetByte(PC0_6D_BG_COLOR_DATA_PORT_S2, (usBlue >> 2));
    ScalerSetByte(PC0_6D_BG_COLOR_DATA_PORT_S2, ((usRed & 0x03) << 6) | ((usGreen & 0x03) << 4) | ((usBlue & 0x03) << 2));

    ScalerSetBit(PC0_6C_BG_COLOR_ACCESS_EN_S2, ~_BIT5, 0x00);
}

//--------------------------------------------------
// Description  : Set Display Pattern Gen Color (10bit)
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void ScalerDDomainPatternGenAdjustColor10bit(WORD usRed, WORD usGreen, WORD usBlue) // 10bit
{
    ScalerSetByte(P7_F3_DISP_PG_R_INITIAL, (usRed >> 2));
    ScalerSetByte(P7_F4_DISP_PG_G_INITIAL, (usGreen >> 2));
    ScalerSetByte(P7_F5_DISP_PG_B_INITIAL, (usBlue >> 2));
    ScalerSetByte(P7_FC_D_PG_INITIAL_M_STEP_L, ((usRed & 0x03) << 4) | ((usGreen & 0x03) << 2) | (usBlue & 0x03));
    ScalerSetByte(P7_FD_D_PG_INITIAL_L_CTRL, 0x00);

    ScalerSetByte(P87_F3_DISP_PG_R_INITIAL_SUB, (usRed >> 2));
    ScalerSetByte(P87_F4_DISP_PG_G_INITIAL_SUB, (usGreen >> 2));
    ScalerSetByte(P87_F5_DISP_PG_B_INITIAL_SUB, (usBlue >> 2));
    ScalerSetByte(P87_FC_D_PG_INITIAL_M_STEP_L_SUB, ((usRed & 0x03) << 4) | ((usGreen & 0x03) << 2) | (usBlue & 0x03));
    ScalerSetByte(P87_FD_D_PG_INITIAL_L_CTRL_SUB, 0x00);
}
#endif

#if(_FREESYNC_OD_MEASURE == _ON)
//--------------------------------------------------
// Description  : Set Background to Gray Level
//                Specified by OD Calibration Tool
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDomainFREESYNCODSetBackgroundGrayLevel(void)
{
    static BYTE sucSelectedBGGrayLevel = 0x00;
    static BYTE sucPreviousBGGrayLevel = 0x00;

    // This function borrows two registers from "D-domain pattern generator"
    // 1. P7_F3_DISP_PG_R_INITIAL served as "specified gray level"
    // 2. _BIT7 of P7_F4_DISP_PG_G_INITIAL served as "function enable" control bit
    // OD calibration tool will use these two registers to communicate with firmware

    // Enable Background
    ScalerDDomainBackgroundEnable(_DISPLAY_PATH_M1_M2, _ENABLE);

    if(ScalerGetBit(_FREESYNC_OD_MEASURE_GL_ENABLE_REG, _BIT7) == _BIT7)
    {
        sucPreviousBGGrayLevel = sucSelectedBGGrayLevel;
        sucSelectedBGGrayLevel = ScalerGetByte(_FREESYNC_OD_MEASURE_GL_VALUE_REG);

        if(sucPreviousBGGrayLevel != sucSelectedBGGrayLevel)
        {
            ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_STOP, _DISPLAY_PATH_M1_M2);
            ScalerDDomainBackgroundSetColor(_DISPLAY_PATH_M1_M2, sucSelectedBGGrayLevel, sucSelectedBGGrayLevel, sucSelectedBGGrayLevel);
        }
    }
    else
    {
        // Enable Red Background
        ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_STOP, _DISPLAY_PATH_M1_M2);
        ScalerDDomainBackgroundSetColor(_DISPLAY_PATH_M1_M2, 0xFF, 0x00, 0x00);
    }
}
#endif

