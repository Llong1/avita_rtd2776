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
// ID Code      : ScalerVGIP.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_VGIP__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_pucVgipHSetting[4];

EnumInputDataPath g_enumVgipInputPath = _INPUT_PATH_NONE;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerVgipSetInputRegion(EnumDisplayRegion enumDisplayRegion);
void ScalerVgipSetInputPath(EnumInputDataPath enumVgipInputPath);

void ScalerVgipCaptureEnable(bit bEnable);
void ScalerVgipInputInitial(EnumSourceTypeDef enumSourceType);
void ScalerVgipModifyPolarity(EnumSourceTypeDef enumSourceType);

WORD ScalerVgipGetCaptureHStartPosition(void);
void ScalerVgipSetCaptureHStartPosition(WORD usIHstart);

#if(_OVERSCAN_SUPPORT == _ON)
WORD ScalerVgipGetCaptureHWidth(void);
#endif
void ScalerVgipSetCaptureHWidth(WORD usIHwidth);

WORD ScalerVgipGetCaptureHDelay(void);
void ScalerVgipSetCaptureHDelay(WORD usIHSDelay);

void ScalerVgipVsBypassEnable(EnumInputDataPath enumInputDataPath, bit bEnable);

void ScalerVgipSetDigitalCaptureStatus(bit bEnable);
bit ScalerVgipGetDigitalCaptureStatus(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Set VGIP data path for specific display region
// Input Value  : display region
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetInputRegion(EnumDisplayRegion enumDisplayRegion)
{
    g_enumVgipInputPath = ScalerRegionGetInputDataPath(enumDisplayRegion);
}

//--------------------------------------------------
// Description  : Set VGIP data path
// Input Value  : input data path
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetInputPath(EnumInputDataPath enumVgipInputPath)
{
    g_enumVgipInputPath = enumVgipInputPath;
}

//--------------------------------------------------
// Description  : Enable/disable VGIP capture
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerVgipCaptureEnable(bit bEnable)
{
    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M1) == _TRUE)
    {
        ScalerSetBit(P0_10_M1_VGIP_CTRL, ~_BIT0, (bEnable & _BIT0));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M2) == _TRUE)
    {
        ScalerSetBit(P40_10_M2_VGIP_CTRL, ~_BIT0, (bEnable & _BIT0));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S1) == _TRUE)
    {
        ScalerSetBit(P80_10_S1_VGIP_CTRL, ~_BIT0, (bEnable & _BIT0));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S2) == _TRUE)
    {
        ScalerSetBit(PC0_10_S2_VGIP_CTRL, ~_BIT0, (bEnable & _BIT0));
    }
}

//--------------------------------------------------
// Description  : Initial for VGIP Input
// Input Value  : Input Source Type
// Output Value : None
//--------------------------------------------------
void ScalerVgipInputInitial(EnumSourceTypeDef enumSourceType)
{
    enumSourceType = enumSourceType;

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M1) == _TRUE)
    {
        // Set source from format conversion; Disable Double buffer, Analog Capture, and Stop generate DE
        ScalerSetBit(P0_10_M1_VGIP_CTRL, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

        // Reset field detect edge
        ScalerSetBit(P0_11_M1_VGIP_SIGINV, ~(_BIT5 | _BIT3), 0x00);

#if(_FREESYNC_SUPPORT == _ON)
        if((GET_FREESYNC_ENABLED() == _TRUE) && (enumSourceType == _SOURCE_DP))
        {
            // Enable bypass Vsync
            ScalerVgipVsBypassEnable(GET_VGIP_INPUT_PATH(), _ENABLE);
        }
        else
        {
            // Disable bypass Vsync
            ScalerVgipVsBypassEnable(GET_VGIP_INPUT_PATH(), _DISABLE);
        }

        // Disable M Domain FREESYNC Enable for VGIP IVS Event to be triggered
        ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~_BIT1, 0x00);
#else
        // Disable bypass Vsync
        ScalerVgipVsBypassEnable(GET_VGIP_INPUT_PATH(), _DISABLE);
#endif

        // HS Sync Edge select to Positive, Disable 1 clock Delay Mode
        ScalerSetBit(P0_12_M1_VGIP_DELAY_CTRL, ~(_BIT4 | _BIT3 | _BIT2), 0x00);
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M2) == _TRUE)
    {
        ScalerSetBit(P40_10_M2_VGIP_CTRL, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

        // Reset field detect edge
        ScalerSetBit(P40_11_M2_VGIP_SIGINV, ~(_BIT5 | _BIT3), 0x00);

#if(_FREESYNC_SUPPORT == _ON)
        if((GET_FREESYNC_ENABLED() == _TRUE) && (enumSourceType == _SOURCE_DP))
        {
            // Enable bypass Vsync
            ScalerVgipVsBypassEnable(GET_VGIP_INPUT_PATH(), _ENABLE);
        }
        else
        {
            // Disable bypass Vsync
            ScalerVgipVsBypassEnable(GET_VGIP_INPUT_PATH(), _DISABLE);
        }

        // Disable M Domain FREESYNC Enable for VGIP IVS Event to be triggered
        ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2, ~_BIT1, 0x00);
#else
        // Disable bypass Vsync
        ScalerVgipVsBypassEnable(GET_VGIP_INPUT_PATH(), _DISABLE);
#endif

        // HS Sync Edge select to Positive, Disable 1 clock Delay Mode
        ScalerSetBit(P40_12_M2_VGIP_DELAY_CTRL, ~(_BIT4 | _BIT3 | _BIT2), 0x00);
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S1) == _TRUE)
    {
        ScalerSetBit(P80_10_S1_VGIP_CTRL, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

        // Reset field detect edge
        ScalerSetBit(P80_11_S1_VGIP_SIGINV, ~(_BIT5 | _BIT3), 0x00);

#if(_FREESYNC_SUPPORT == _ON)
        if((GET_FREESYNC_ENABLED() == _TRUE) && (enumSourceType == _SOURCE_DP))
        {
            // Enable bypass Vsync
            ScalerVgipVsBypassEnable(GET_VGIP_INPUT_PATH(), _ENABLE);
        }
        else
        {
            // Disable bypass Vsync
            ScalerVgipVsBypassEnable(GET_VGIP_INPUT_PATH(), _DISABLE);
        }

        // Disable M Domain FREESYNC Enable for VGIP IVS Event to be triggered
        ScalerSetBit(P80_26_SD_FILTER_CONTROL_REG_S1, ~_BIT1, 0x00);
#else
        // Disable bypass Vsync
        ScalerVgipVsBypassEnable(GET_VGIP_INPUT_PATH(), _DISABLE);
#endif

        // HS Sync Edge select to Positive, Disable 1 clock Delay Mode
        ScalerSetBit(P80_12_S1_VGIP_DELAY_CTRL, ~(_BIT4 | _BIT3 | _BIT2), 0x00);
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S2) == _TRUE)
    {
        ScalerSetBit(PC0_10_S2_VGIP_CTRL, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

        // Reset field detect edge
        ScalerSetBit(PC0_11_S2_VGIP_SIGINV, ~(_BIT5 | _BIT3), 0x00);

#if(_FREESYNC_SUPPORT == _ON)
        if((GET_FREESYNC_ENABLED() == _TRUE) && (enumSourceType == _SOURCE_DP))
        {
            // Enable bypass Vsync
            ScalerVgipVsBypassEnable(GET_VGIP_INPUT_PATH(), _ENABLE);
        }
        else
        {
            // Disable bypass Vsync
            ScalerVgipVsBypassEnable(GET_VGIP_INPUT_PATH(), _DISABLE);
        }

        // Disable M Domain FREESYNC Enable for VGIP IVS Event to be triggered
        ScalerSetBit(PC0_26_SD_FILTER_CONTROL_REG_S2, ~_BIT1, 0x00);
#else
        // Disable bypass Vsync
        ScalerVgipVsBypassEnable(GET_VGIP_INPUT_PATH(), _DISABLE);
#endif

        // HS Sync Edge select to Positive, Disable 1 clock Delay Mode
        ScalerSetBit(PC0_12_S2_VGIP_DELAY_CTRL, ~(_BIT4 | _BIT3 | _BIT2), 0x00);
    }

    // Initial IVS/IHS Delay for Capture and Auto
    ScalerVgipSetCaptureHDelay(0x00);
    ScalerVgipSetCaptureVDelay(0x00);

#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        // Apply VGIP DB
        ScalerGlobalIDomainDBApply(GET_VGIP_INPUT_PATH(), _DB_APPLY_POLLING);
    }
    else
#endif
    {
        // Bypass VS for DB apply
        ScalerVgipVsBypassEnable(GET_VGIP_INPUT_PATH(), _ENABLE);

        // Apply VGIP DB
        ScalerGlobalIDomainDBApply(GET_VGIP_INPUT_PATH(), _DB_APPLY_POLLING);

        // Disable VS bypass
        ScalerVgipVsBypassEnable(GET_VGIP_INPUT_PATH(), _DISABLE);
    }
}

//--------------------------------------------------
// Description  : Modify HS/VS Polarity
// Input Value  : Input Source Type
// Output Value : None
//--------------------------------------------------
void ScalerVgipModifyPolarity(EnumSourceTypeDef enumSourceType)
{
#if(_VGA_SUPPORT == _ON)
    if(enumSourceType == _SOURCE_VGA)
    {
        if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M1) == _TRUE)
        {
            // HS No Invert in VGIP
            ScalerSetBit(P0_11_M1_VGIP_SIGINV, ~_BIT2, 0x00);

            // VS No Invert in VGIP
            ScalerSetBit(P0_11_M1_VGIP_SIGINV, ~_BIT3, 0x00);
        }

        if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M2) == _TRUE)
        {
            ScalerSetBit(P40_11_M2_VGIP_SIGINV, ~_BIT2, 0x00);
            ScalerSetBit(P40_11_M2_VGIP_SIGINV, ~_BIT3, 0x00);
        }

        if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S1) == _TRUE)
        {
            ScalerSetBit(P80_11_S1_VGIP_SIGINV, ~_BIT2, 0x00);
            ScalerSetBit(P80_11_S1_VGIP_SIGINV, ~_BIT3, 0x00);
        }

        if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S2) == _TRUE)
        {
            ScalerSetBit(PC0_11_S2_VGIP_SIGINV, ~_BIT2, 0x00);
            ScalerSetBit(PC0_11_S2_VGIP_SIGINV, ~_BIT3, 0x00);
        }
    }
    else
#endif
    {
        if(GET_SYNC_H_POLARITY() == _POSITIVE)
        {
            if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M1) == _TRUE)
            {
                // HS No Invert
                ScalerSetBit(P0_11_M1_VGIP_SIGINV, ~_BIT2, 0x00);
            }

            if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M2) == _TRUE)
            {
                ScalerSetBit(P40_11_M2_VGIP_SIGINV, ~_BIT2, 0x00);
            }

            if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S1) == _TRUE)
            {
                ScalerSetBit(P80_11_S1_VGIP_SIGINV, ~_BIT2, 0x00);
            }

            if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S2) == _TRUE)
            {
                ScalerSetBit(PC0_11_S2_VGIP_SIGINV, ~_BIT2, 0x00);
            }
        }
        else
        {
            if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M1) == _TRUE)
            {
                // HS Invert
                ScalerSetBit(P0_11_M1_VGIP_SIGINV, ~_BIT2, _BIT2);
            }

            if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M2) == _TRUE)
            {
                ScalerSetBit(P40_11_M2_VGIP_SIGINV, ~_BIT2, _BIT2);
            }

            if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S1) == _TRUE)
            {
                ScalerSetBit(P80_11_S1_VGIP_SIGINV, ~_BIT2, _BIT2);
            }

            if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S2) == _TRUE)
            {
                ScalerSetBit(PC0_11_S2_VGIP_SIGINV, ~_BIT2, _BIT2);
            }
        }

        if((enumSourceType == _SOURCE_DP) ||
           ((GET_SYNC_V_POLARITY() ^ (bit)ScalerGetBit(P0_4F_STABLE_MEASURE, _BIT2)) == _POSITIVE))
        {
            if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M1) == _TRUE)
            {
                // VS No Invert
                ScalerSetBit(P0_11_M1_VGIP_SIGINV, ~_BIT3, 0x00);
            }

            if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M2) == _TRUE)
            {
                ScalerSetBit(P40_11_M2_VGIP_SIGINV, ~_BIT3, 0x00);
            }

            if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S1) == _TRUE)
            {
                ScalerSetBit(P80_11_S1_VGIP_SIGINV, ~_BIT3, 0x00);
            }

            if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S2) == _TRUE)
            {
                ScalerSetBit(PC0_11_S2_VGIP_SIGINV, ~_BIT3, 0x00);
            }
        }
        else
        {
            if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M1) == _TRUE)
            {
                // VS Invert
                ScalerSetBit(P0_11_M1_VGIP_SIGINV, ~_BIT3, _BIT3);
            }

            if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M2) == _TRUE)
            {
                ScalerSetBit(P40_11_M2_VGIP_SIGINV, ~_BIT3, _BIT3);
            }

            if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S1) == _TRUE)
            {
                ScalerSetBit(P80_11_S1_VGIP_SIGINV, ~_BIT3, _BIT3);
            }

            if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S2) == _TRUE)
            {
                ScalerSetBit(PC0_11_S2_VGIP_SIGINV, ~_BIT3, _BIT3);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Get Capture H-Start Position
// Input Value  : None
// Output Value : Capture H Start
//--------------------------------------------------
WORD ScalerVgipGetCaptureHStartPosition(void)
{
    WORD usHstart = 0;

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M1) == _TRUE)
    {
        usHstart = ((((ScalerGetByte(P0_14_M1_IPH_ACT_STA_H) & 0x0F) << 8) | ScalerGetByte(P0_15_M1_IPH_ACT_STA_L)));
    }
    else if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M2) == _TRUE)
    {
        usHstart = ((((ScalerGetByte(P40_14_M2_IPH_ACT_STA_H) & 0x0F) << 8) | ScalerGetByte(P40_15_M2_IPH_ACT_STA_L)));
    }
#if(_MULTI_DISPLAY_MAX > 0x01)
    else if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S1) == _TRUE)
    {
        usHstart = ((((ScalerGetByte(P80_14_S1_IPH_ACT_STA_H) & 0x0F) << 8) | ScalerGetByte(P80_15_S1_IPH_ACT_STA_L)));
    }
    else if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S2) == _TRUE)
    {
        usHstart = ((((ScalerGetByte(PC0_14_S2_IPH_ACT_STA_H) & 0x0F) << 8) | ScalerGetByte(PC0_15_S2_IPH_ACT_STA_L)));
    }
#endif

    // H-start in analog capture starts from 2
    if(ScalerVgipGetDigitalCaptureStatus() == _FALSE)
    {
        usHstart += 2;
    }

    if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
    {
        return (usHstart << 1);
    }
    else
    {
        return usHstart;
    }
}

//--------------------------------------------------
// Description  : Set Capture H-Start Position
// Input Value  : usIHstart --> Capture H start
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetCaptureHStartPosition(WORD usIHstart)
{
    // Modify H start under analog capture
    if(ScalerVgipGetDigitalCaptureStatus() == _FALSE)
    {
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
        {
            usIHstart = (usIHstart >> 1);
        }
#endif

        if(usIHstart >= 2)
        {
            usIHstart -= 2;
        }
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M1) == _TRUE)
    {
        // Store effective values
        g_pucVgipHSetting[0] = ((g_pucVgipHSetting[0] & 0xF0) | (HIBYTE(usIHstart) & 0x0F));

        // Set M1 H capture start
        ScalerSetByte(P0_14_M1_IPH_ACT_STA_H, g_pucVgipHSetting[0]);
        ScalerSetByte(P0_15_M1_IPH_ACT_STA_L, LOBYTE(usIHstart));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M2) == _TRUE)
    {
        // Store effective values
        g_pucVgipHSetting[1] = ((g_pucVgipHSetting[1] & 0xF0) | (HIBYTE(usIHstart) & 0x0F));

        // Set M1 H capture start
        ScalerSetByte(P40_14_M2_IPH_ACT_STA_H, g_pucVgipHSetting[1]);
        ScalerSetByte(P40_15_M2_IPH_ACT_STA_L, LOBYTE(usIHstart));
    }

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        // VGIP H start = 0 for S1/S2
        usIHstart = 0;
    }
#endif

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S1) == _TRUE)
    {
        // Store effective values
        g_pucVgipHSetting[2] = ((g_pucVgipHSetting[2] & 0xF0) | (HIBYTE(usIHstart) & 0x0F));

        // Set M1 H capture start
        ScalerSetByte(P80_14_S1_IPH_ACT_STA_H, g_pucVgipHSetting[2]);
        ScalerSetByte(P80_15_S1_IPH_ACT_STA_L, LOBYTE(usIHstart));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S2) == _TRUE)
    {
        // Store effective values
        g_pucVgipHSetting[3] = ((g_pucVgipHSetting[3] & 0xF0) | (HIBYTE(usIHstart) & 0x0F));

        // Set M1 H capture start
        ScalerSetByte(PC0_14_S2_IPH_ACT_STA_H, g_pucVgipHSetting[3]);
        ScalerSetByte(PC0_15_S2_IPH_ACT_STA_L, LOBYTE(usIHstart));
    }
}

#if(_OVERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Capture H Width
// Input Value  : None
// Output Value : H capture Width
//--------------------------------------------------
WORD ScalerVgipGetCaptureHWidth(void)
{
    WORD usHwidth = 0;

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M1) == _TRUE)
    {
        usHwidth = (((WORD)ScalerGetBit(P0_16_M1_IPH_ACT_WID_H, _BIT0) << 12) | (((WORD)ScalerGetByte(P0_14_M1_IPH_ACT_STA_H) & 0xF0) << 4) | ScalerGetByte(P0_17_M1_IPH_ACT_WID_L));
    }
    else if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M2) == _TRUE)
    {
        usHwidth = (((WORD)ScalerGetBit(P40_16_M2_IPH_ACT_WID_H, _BIT0) << 12) | (((WORD)ScalerGetByte(P40_14_M2_IPH_ACT_STA_H) & 0xF0) << 4) | ScalerGetByte(P40_17_M2_IPH_ACT_WID_L));
    }
#if(_MULTI_DISPLAY_MAX > 0x01)
    else if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S1) == _TRUE)
    {
        usHwidth = (((WORD)ScalerGetBit(P80_16_S1_IPH_ACT_WID_H, _BIT0) << 12) | (((WORD)ScalerGetByte(P80_14_S1_IPH_ACT_STA_H) & 0xF0) << 4) | ScalerGetByte(P80_17_S1_IPH_ACT_WID_L));
    }
    else if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S2) == _TRUE)
    {
        usHwidth = (((WORD)ScalerGetBit(PC0_16_S2_IPH_ACT_WID_H, _BIT0) << 12) | (((WORD)ScalerGetByte(PC0_14_S2_IPH_ACT_STA_H) & 0xF0) << 4) | ScalerGetByte(PC0_17_S2_IPH_ACT_WID_L));
    }
#endif

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if(ScalerFmtCnvFBGetStatus() == _TRUE)
    {
        usHwidth = (usHwidth - GET_FMTCNV_EXTENSION_LEN()) * 2;
    }
#endif

    return usHwidth;
}
#endif

//--------------------------------------------------
// Description  : Set Capture H Width
// Input Value  : usIHwidth --> H capture width
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetCaptureHWidth(WORD usIHwidth)
{
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if(ScalerFmtCnvFBGetStatus() == _TRUE)
    {
        usIHwidth = usIHwidth / 2 + GET_FMTCNV_EXTENSION_LEN();
    }
#endif

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M1) == _TRUE)
    {
        g_pucVgipHSetting[0] = ScalerGetByte(P0_14_M1_IPH_ACT_STA_H);

        // Store effective values
        g_pucVgipHSetting[0] = ((g_pucVgipHSetting[0] & 0x0F) | ((HIBYTE(usIHwidth) & 0x0F) << 4));

        // Set M1 H capture width
        ScalerSetByte(P0_14_M1_IPH_ACT_STA_H, g_pucVgipHSetting[0]);
        ScalerSetBit(P0_16_M1_IPH_ACT_WID_H, ~_BIT0, ((HIBYTE(usIHwidth) & _BIT4) >> 4));
        ScalerSetByte(P0_17_M1_IPH_ACT_WID_L, LOBYTE(usIHwidth));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M2) == _TRUE)
    {
        g_pucVgipHSetting[1] = ScalerGetByte(P40_14_M2_IPH_ACT_STA_H);

        // Store effective values
        g_pucVgipHSetting[1] = ((g_pucVgipHSetting[1] & 0x0F) | ((HIBYTE(usIHwidth) & 0x0F) << 4));

        // Set M2 H capture width
        ScalerSetByte(P40_14_M2_IPH_ACT_STA_H, g_pucVgipHSetting[1]);
        ScalerSetBit(P40_16_M2_IPH_ACT_WID_H, ~_BIT0, ((HIBYTE(usIHwidth) & _BIT4) >> 4));
        ScalerSetByte(P40_17_M2_IPH_ACT_WID_L, LOBYTE(usIHwidth));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S1) == _TRUE)
    {
        g_pucVgipHSetting[2] = ScalerGetByte(P80_14_S1_IPH_ACT_STA_H);

        // Store effective values
        g_pucVgipHSetting[2] = ((g_pucVgipHSetting[2] & 0x0F) | ((HIBYTE(usIHwidth) & 0x0F) << 4));

        // Set M2 H capture width
        ScalerSetByte(P80_14_S1_IPH_ACT_STA_H, g_pucVgipHSetting[2]);
        ScalerSetBit(P80_16_S1_IPH_ACT_WID_H, ~_BIT0, ((HIBYTE(usIHwidth) & _BIT4) >> 4));
        ScalerSetByte(P80_17_S1_IPH_ACT_WID_L, LOBYTE(usIHwidth));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S2) == _TRUE)
    {
        g_pucVgipHSetting[3] = ScalerGetByte(PC0_14_S2_IPH_ACT_STA_H);

        // Store effective values
        g_pucVgipHSetting[3] = ((g_pucVgipHSetting[3] & 0x0F) | ((HIBYTE(usIHwidth) & 0x0F) << 4));

        // Set M2 H capture width
        ScalerSetByte(PC0_14_S2_IPH_ACT_STA_H, g_pucVgipHSetting[3]);
        ScalerSetBit(PC0_16_S2_IPH_ACT_WID_H, ~_BIT0, ((HIBYTE(usIHwidth) & _BIT4) >> 4));
        ScalerSetByte(PC0_17_S2_IPH_ACT_WID_L, LOBYTE(usIHwidth));
    }
}

//--------------------------------------------------
// Description  : Get Capture H Delay
// Input Value  : None
// Output Value : H Delay
//--------------------------------------------------
WORD ScalerVgipGetCaptureHDelay(void)
{
    WORD usHdelay = 0;

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M1) == _TRUE)
    {
        usHdelay = ((((WORD)ScalerGetByte(P0_1E_M1_VGIP_HV_DELAY) & _BIT2) << 7) | (((WORD)ScalerGetByte(P0_1E_M1_VGIP_HV_DELAY) & _BIT0) << 8) | ScalerGetByte(P0_1D_M1_IHS_DELAY));
    }
    else if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M2) == _TRUE)
    {
        usHdelay = ((((WORD)ScalerGetByte(P40_1E_M2_VGIP_HV_DELAY) & _BIT2) << 7) | (((WORD)ScalerGetByte(P40_1E_M2_VGIP_HV_DELAY) & _BIT0) << 8) | ScalerGetByte(P40_1D_M2_IHS_DELAY));
    }
#if(_MULTI_DISPLAY_MAX > 0x01)
    else if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S1) == _TRUE)
    {
        usHdelay = ((((WORD)ScalerGetByte(P80_1E_S1_VGIP_HV_DELAY) & _BIT2) << 7) | (((WORD)ScalerGetByte(P80_1E_S1_VGIP_HV_DELAY) & _BIT0) << 8) | ScalerGetByte(P80_1D_S1_IHS_DELAY));
    }
    else if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S2) == _TRUE)
    {
        usHdelay = ((((WORD)ScalerGetByte(PC0_1E_S2_VGIP_HV_DELAY) & _BIT2) << 7) | (((WORD)ScalerGetByte(PC0_1E_S2_VGIP_HV_DELAY) & _BIT0) << 8) | ScalerGetByte(PC0_1D_S2_IHS_DELAY));
    }
#endif

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
    {
        return (usHdelay << 1);
    }
    else
#endif
    {
        return usHdelay;
    }
}

//--------------------------------------------------
// Description  : Set Capture V Delay
// Input Value  : usIHSDelay --> H Delay
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetCaptureHDelay(WORD usIHSDelay)
{
    if(ScalerVgipGetDigitalCaptureStatus() == _TRUE)
    {
        return;
    }

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
    {
        usIHSDelay = (usIHSDelay >> 1);
    }
#endif

    if(usIHSDelay > _VGIP_IH_DELAY_MAX_VALUE)
    {
        ScalerIDomainFineTuneHCaptureStart(usIHSDelay - _VGIP_IH_DELAY_MAX_VALUE);

        usIHSDelay = _VGIP_IH_DELAY_MAX_VALUE;
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M1) == _TRUE)
    {
        // Store effective values
        g_pucVgipDelaySetting[0] = ((g_pucVgipDelaySetting[0] & ~(_BIT2 | _BIT0)) | (((HIBYTE(usIHSDelay) & _BIT1) << 1) | (HIBYTE(usIHSDelay) & _BIT0)));

        // Set M1 capture H delay
        ScalerSetByte(P0_1E_M1_VGIP_HV_DELAY, g_pucVgipDelaySetting[0]);
        ScalerSetByte(P0_1D_M1_IHS_DELAY, LOBYTE(usIHSDelay));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M2) == _TRUE)
    {
        // Store effective values
        g_pucVgipDelaySetting[1] = ((g_pucVgipDelaySetting[1] & ~(_BIT2 | _BIT0)) | (((HIBYTE(usIHSDelay) & _BIT1) << 1) | (HIBYTE(usIHSDelay) & _BIT0)));

        // Set M2 capture H delay
        ScalerSetByte(P40_1E_M2_VGIP_HV_DELAY, g_pucVgipDelaySetting[1]);
        ScalerSetByte(P40_1D_M2_IHS_DELAY, LOBYTE(usIHSDelay));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S1) == _TRUE)
    {
        // Store effective values
        g_pucVgipDelaySetting[2] = ((g_pucVgipDelaySetting[2] & ~(_BIT2 | _BIT0)) | (((HIBYTE(usIHSDelay) & _BIT1) << 1) | (HIBYTE(usIHSDelay) & _BIT0)));

        // Set M2 capture H delay
        ScalerSetByte(P80_1E_S1_VGIP_HV_DELAY, g_pucVgipDelaySetting[2]);
        ScalerSetByte(P80_1D_S1_IHS_DELAY, LOBYTE(usIHSDelay));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S2) == _TRUE)
    {
        // Store effective values
        g_pucVgipDelaySetting[3] = ((g_pucVgipDelaySetting[3] & ~(_BIT2 | _BIT0)) | (((HIBYTE(usIHSDelay) & _BIT1) << 1) | (HIBYTE(usIHSDelay) & _BIT0)));

        // Set M2 capture H delay
        ScalerSetByte(PC0_1E_S2_VGIP_HV_DELAY, g_pucVgipDelaySetting[3]);
        ScalerSetByte(PC0_1D_S2_IHS_DELAY, LOBYTE(usIHSDelay));
    }
}

//--------------------------------------------------
// Description  : Set VGA VS bypass VGIP
// Input Value  : enumInputDataPath --> input data path
//                bEnable --> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerVgipVsBypassEnable(EnumInputDataPath enumInputDataPath, bit bEnable)
{
    BYTE ucSwitch = ((bEnable == _ENABLE) ? _BIT6 : 0x00);

    // Switch VGIP VS bypass
    if((enumInputDataPath & _INPUT_PATH_M1) != 0x00)
    {
        ScalerSetBit(P0_11_M1_VGIP_SIGINV, ~_BIT6, ucSwitch);
    }

    if((enumInputDataPath & _INPUT_PATH_M2) != 0x00)
    {
        ScalerSetBit(P40_11_M2_VGIP_SIGINV, ~_BIT6, ucSwitch);
    }

    if((enumInputDataPath & _INPUT_PATH_S1) != 0x00)
    {
        ScalerSetBit(P80_11_S1_VGIP_SIGINV, ~_BIT6, ucSwitch);
    }

    if((enumInputDataPath & _INPUT_PATH_S2) != 0x00)
    {
        ScalerSetBit(PC0_11_S2_VGIP_SIGINV, ~_BIT6, ucSwitch);
    }
}

//--------------------------------------------------
// Description  : Set VGA VS bypass VGIP
// Input Value  : enumInputDataPath --> input data path
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetDigitalCaptureStatus(bit bEnable)
{
    BYTE ucEnableOption = ((bEnable == _ENABLE) ? _BIT1 : 0);

    // Set Digital Capture
    if((GET_VGIP_INPUT_PATH() & _INPUT_PATH_M1) != 0x00)
    {
        ScalerSetBit(P0_10_M1_VGIP_CTRL, ~_BIT1, ucEnableOption);
    }

    if((GET_VGIP_INPUT_PATH() & _INPUT_PATH_M2) != 0x00)
    {
        ScalerSetBit(P40_10_M2_VGIP_CTRL, ~_BIT1, ucEnableOption);
    }

    if((GET_VGIP_INPUT_PATH() & _INPUT_PATH_S1) != 0x00)
    {
        ScalerSetBit(P80_10_S1_VGIP_CTRL, ~_BIT1, ucEnableOption);
    }

    if((GET_VGIP_INPUT_PATH() & _INPUT_PATH_S2) != 0x00)
    {
        ScalerSetBit(PC0_10_S2_VGIP_CTRL, ~_BIT1, ucEnableOption);
    }
}

//--------------------------------------------------
// Description  : Set VGA VS bypass VGIP
// Input Value  : enumInputDataPath --> input data path
// Output Value : None
//--------------------------------------------------
bit ScalerVgipGetDigitalCaptureStatus(void)
{
    if((GET_VGIP_INPUT_PATH() & _INPUT_PATH_M1) != 0x00)
    {
        return (ScalerGetBit(P0_10_M1_VGIP_CTRL, _BIT1) == _BIT1);
    }
    else if((GET_VGIP_INPUT_PATH() & _INPUT_PATH_M2) != 0x00)
    {
        return (ScalerGetBit(P40_10_M2_VGIP_CTRL, _BIT1) == _BIT1);
    }
#if(_MULTI_DISPLAY_MAX > 0x01)
    else if((GET_VGIP_INPUT_PATH() & _INPUT_PATH_S1) != 0x00)
    {
        return (ScalerGetBit(P80_10_S1_VGIP_CTRL, _BIT1) == _BIT1);
    }
    else if((GET_VGIP_INPUT_PATH() & _INPUT_PATH_S2) != 0x00)
    {
        return (ScalerGetBit(PC0_10_S2_VGIP_CTRL, _BIT1) == _BIT1);
    }
#endif

    return _FALSE;
}
