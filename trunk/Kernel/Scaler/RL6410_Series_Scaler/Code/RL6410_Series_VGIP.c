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
// ID Code      : RL6410_Series_VGIP.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

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
BYTE g_pucVgipVSetting[4];
BYTE g_pucVgipDelaySetting[4];
BYTE g_pucVgipMiscSetting[4];

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
WORD ScalerVgipGetCaptureVStartPosition(void);
void ScalerVgipSetCaptureVStartPosition(WORD usIVstart);

WORD ScalerVgipGetCaptureVHeight(void);
void ScalerVgipSetCaptureVHeight(WORD usIVheight);

WORD ScalerVgipGetCaptureVDelay(void);
void ScalerVgipSetCaptureVDelay(WORD usIVSDelay);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get Capture V-Start Position
// Input Value  : None
// Output Value : Capture Start
//--------------------------------------------------
WORD ScalerVgipGetCaptureVStartPosition(void)
{
    WORD usIVstart = 0;

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M1) == _TRUE)
    {
        usIVstart = ((((WORD)(ScalerGetByte(P0_16_M1_IPH_ACT_WID_H) & _BIT6) << 6) | ((WORD)(ScalerGetByte(P0_18_M1_IPV_ACT_STA_H) & 0x0F) << 8) | ScalerGetByte(P0_19_M1_IPV_ACT_STA_L)));
    }
    else if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M2) == _TRUE)
    {
        usIVstart = ((((WORD)(ScalerGetByte(P40_16_M2_IPH_ACT_WID_H) & _BIT6) << 6) | ((WORD)(ScalerGetByte(P40_18_M2_IPV_ACT_STA_H) & 0x0F) << 8) | ScalerGetByte(P40_19_M2_IPV_ACT_STA_L)));
    }
    else if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S1) == _TRUE)
    {
        usIVstart = ((((WORD)(ScalerGetByte(P80_16_S1_IPH_ACT_WID_H) & _BIT6) << 6) | ((WORD)(ScalerGetByte(P80_18_S1_IPV_ACT_STA_H) & 0x0F) << 8) | ScalerGetByte(P80_19_S1_IPV_ACT_STA_L)));
    }
    else if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S2) == _TRUE)
    {
        usIVstart = ((((WORD)(ScalerGetByte(PC0_16_S2_IPH_ACT_WID_H) & _BIT6) << 6) | ((WORD)(ScalerGetByte(PC0_18_S2_IPV_ACT_STA_H) & 0x0F) << 8) | ScalerGetByte(PC0_19_S2_IPV_ACT_STA_L)));
    }

    if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
    {
        return (usIVstart << 1);
    }
    else
    {
        return usIVstart;
    }
}

//--------------------------------------------------
// Description  : Set Capture V-Start Position
// Input Value  : usIVstart --> V capture start
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetCaptureVStartPosition(WORD usIVstart)
{
    if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
    {
        usIVstart = (usIVstart >> 1);
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M1) == _TRUE)
    {
        // Store effective values
        g_pucVgipVSetting[0] = ((g_pucVgipVSetting[0] & 0xF0) | (HIBYTE(usIVstart) & 0x0F));
        g_pucVgipMiscSetting[0] = ((g_pucVgipMiscSetting[0] & 0xBF) | ((HIBYTE(usIVstart) & 0x10) << 2));

        // Set M1 V capture start
        ScalerSetByte(P0_16_M1_IPH_ACT_WID_H, g_pucVgipMiscSetting[0]);
        ScalerSetByte(P0_18_M1_IPV_ACT_STA_H, g_pucVgipVSetting[0]);
        ScalerSetByte(P0_19_M1_IPV_ACT_STA_L, LOBYTE(usIVstart));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M2) == _TRUE)
    {
        // Store effective values
        g_pucVgipVSetting[1] = ((g_pucVgipVSetting[1] & 0xF0) | (HIBYTE(usIVstart) & 0x0F));
        g_pucVgipMiscSetting[1] = ((g_pucVgipMiscSetting[1] & 0xBF) | ((HIBYTE(usIVstart) & 0x10) << 2));

        // Set M2 V capture start
        ScalerSetByte(P40_16_M2_IPH_ACT_WID_H, g_pucVgipMiscSetting[1]);
        ScalerSetByte(P40_18_M2_IPV_ACT_STA_H, g_pucVgipVSetting[1]);
        ScalerSetByte(P40_19_M2_IPV_ACT_STA_L, LOBYTE(usIVstart));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S1) == _TRUE)
    {
        // Store effective values
        g_pucVgipVSetting[2] = ((g_pucVgipVSetting[2] & 0xF0) | (HIBYTE(usIVstart) & 0x0F));
        g_pucVgipMiscSetting[2] = ((g_pucVgipMiscSetting[2] & 0xBF) | ((HIBYTE(usIVstart) & 0x10) << 2));

        // Set M1 V capture start
        ScalerSetByte(P80_16_S1_IPH_ACT_WID_H, g_pucVgipMiscSetting[2]);
        ScalerSetByte(P80_18_S1_IPV_ACT_STA_H, g_pucVgipVSetting[2]);
        ScalerSetByte(P80_19_S1_IPV_ACT_STA_L, LOBYTE(usIVstart));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S2) == _TRUE)
    {
        // Store effective values
        g_pucVgipVSetting[3] = ((g_pucVgipVSetting[3] & 0xF0) | (HIBYTE(usIVstart) & 0x0F));
        g_pucVgipMiscSetting[3] = ((g_pucVgipMiscSetting[3] & 0xBF) | ((HIBYTE(usIVstart) & 0x10) << 2));

        // Set M1 V capture start
        ScalerSetByte(PC0_16_S2_IPH_ACT_WID_H, g_pucVgipMiscSetting[3]);
        ScalerSetByte(PC0_18_S2_IPV_ACT_STA_H, g_pucVgipVSetting[3]);
        ScalerSetByte(PC0_19_S2_IPV_ACT_STA_L, LOBYTE(usIVstart));
    }
}

//--------------------------------------------------
// Description  : Get Capture V-Height Position
// Input Value  : None
// Output Value : Capture Start
//--------------------------------------------------
WORD ScalerVgipGetCaptureVHeight(void)
{
    WORD usIVheight = 0;

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M1) == _TRUE)
    {
        usIVheight = ((((WORD)(ScalerGetByte(P0_16_M1_IPH_ACT_WID_H) & _BIT7) << 5) | ((WORD)(ScalerGetByte(P0_18_M1_IPV_ACT_STA_H) & 0xF0) << 4) | ScalerGetByte(P0_1B_M1_IPV_ACT_LEN_L)));
    }
    else if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M2) == _TRUE)
    {
        usIVheight = ((((WORD)(ScalerGetByte(P40_16_M2_IPH_ACT_WID_H) & _BIT7) << 5) | ((WORD)(ScalerGetByte(P40_18_M2_IPV_ACT_STA_H) & 0xF0) << 4) | ScalerGetByte(P40_1B_M2_IPV_ACT_LEN_L)));
    }
    else if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S1) == _TRUE)
    {
        usIVheight = ((((WORD)(ScalerGetByte(P80_16_S1_IPH_ACT_WID_H) & _BIT7) << 5) | ((WORD)(ScalerGetByte(P80_18_S1_IPV_ACT_STA_H) & 0xF0) << 4) | ScalerGetByte(P80_1B_S1_IPV_ACT_LEN_L)));
    }
    else if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S2) == _TRUE)
    {
        usIVheight = ((((WORD)(ScalerGetByte(PC0_16_S2_IPH_ACT_WID_H) & _BIT7) << 5) | ((WORD)(ScalerGetByte(PC0_18_S2_IPV_ACT_STA_H) & 0xF0) << 4) | ScalerGetByte(PC0_1B_S2_IPV_ACT_LEN_L)));
    }

    if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
    {
        return (usIVheight << 1);
    }
    else
    {
        return usIVheight;
    }
}

//--------------------------------------------------
// Description  : Set Capture V-Height Position
// Input Value  : usIVheight --> Capture Height
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetCaptureVHeight(WORD usIVheight)
{
    if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
    {
        usIVheight = (usIVheight >> 1);
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M1) == _TRUE)
    {
        g_pucVgipVSetting[0] = ScalerGetByte(P0_18_M1_IPV_ACT_STA_H);
        g_pucVgipMiscSetting[0] = ScalerGetByte(P0_16_M1_IPH_ACT_WID_H);

        // Store effective values
        g_pucVgipVSetting[0] = ((g_pucVgipVSetting[0] & 0x0F) | ((HIBYTE(usIVheight) & 0x0F) << 4));
        g_pucVgipMiscSetting[0] = ((g_pucVgipMiscSetting[0] & 0x3F) | ((HIBYTE(usIVheight) & 0x10) << 3));

        // Set M1 V capture height
        ScalerSetByte(P0_16_M1_IPH_ACT_WID_H, g_pucVgipMiscSetting[0]);
        ScalerSetByte(P0_18_M1_IPV_ACT_STA_H, g_pucVgipVSetting[0]);
        ScalerSetByte(P0_1B_M1_IPV_ACT_LEN_L, LOBYTE(usIVheight));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M2) == _TRUE)
    {
        g_pucVgipVSetting[1] = ScalerGetByte(P40_18_M2_IPV_ACT_STA_H);
        g_pucVgipMiscSetting[1] = ScalerGetByte(P40_16_M2_IPH_ACT_WID_H);

        // Store effective values
        g_pucVgipVSetting[1] = ((g_pucVgipVSetting[1] & 0x0F) | ((HIBYTE(usIVheight) & 0x0F) << 4));
        g_pucVgipMiscSetting[1] = ((g_pucVgipMiscSetting[1] & 0x3F) | ((HIBYTE(usIVheight) & 0x10) << 3));

        // Set M1 V capture height
        ScalerSetByte(P40_16_M2_IPH_ACT_WID_H, g_pucVgipMiscSetting[1]);
        ScalerSetByte(P40_18_M2_IPV_ACT_STA_H, g_pucVgipVSetting[1]);
        ScalerSetByte(P40_1B_M2_IPV_ACT_LEN_L, LOBYTE(usIVheight));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S1) == _TRUE)
    {
        g_pucVgipVSetting[2] = ScalerGetByte(P80_18_S1_IPV_ACT_STA_H);
        g_pucVgipMiscSetting[2] = ScalerGetByte(P80_16_S1_IPH_ACT_WID_H);

        // Store effective values
        g_pucVgipVSetting[2] = ((g_pucVgipVSetting[2] & 0x0F) | ((HIBYTE(usIVheight) & 0x0F) << 4));
        g_pucVgipMiscSetting[2] = ((g_pucVgipMiscSetting[2] & 0x3F) | ((HIBYTE(usIVheight) & 0x10) << 3));

        // Set M1 V capture height
        ScalerSetByte(P80_16_S1_IPH_ACT_WID_H, g_pucVgipMiscSetting[2]);
        ScalerSetByte(P80_18_S1_IPV_ACT_STA_H, g_pucVgipVSetting[2]);
        ScalerSetByte(P80_1B_S1_IPV_ACT_LEN_L, LOBYTE(usIVheight));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S2) == _TRUE)
    {
        g_pucVgipVSetting[3] = ScalerGetByte(PC0_18_S2_IPV_ACT_STA_H);
        g_pucVgipMiscSetting[3] = ScalerGetByte(PC0_16_S2_IPH_ACT_WID_H);

        // Store effective values
        g_pucVgipVSetting[3] = ((g_pucVgipVSetting[3] & 0x0F) | ((HIBYTE(usIVheight) & 0x0F) << 4));
        g_pucVgipMiscSetting[3] = ((g_pucVgipMiscSetting[3] & 0x3F) | ((HIBYTE(usIVheight) & 0x10) << 3));

        // Set M1 V capture height
        ScalerSetByte(PC0_16_S2_IPH_ACT_WID_H, g_pucVgipMiscSetting[3]);
        ScalerSetByte(PC0_18_S2_IPV_ACT_STA_H, g_pucVgipVSetting[3]);
        ScalerSetByte(PC0_1B_S2_IPV_ACT_LEN_L, LOBYTE(usIVheight));
    }
}

//--------------------------------------------------
// Description  : Get Capture V Delay
// Input Value  : None
// Output Value : Capture V Delay
//--------------------------------------------------
WORD ScalerVgipGetCaptureVDelay(void)
{
    WORD usIVSDelay = 0;

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M1) == _TRUE)
    {
        usIVSDelay = (((((WORD)(ScalerGetByte(P0_16_M1_IPH_ACT_WID_H) & _BIT5)) << 4) | (((WORD)(ScalerGetByte(P0_1E_M1_VGIP_HV_DELAY) & _BIT1)) << 7) | ScalerGetByte(P0_1C_M1_IVS_DELAY)));
    }
    else if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M2) == _TRUE)
    {
        usIVSDelay = (((((WORD)(ScalerGetByte(P40_16_M2_IPH_ACT_WID_H) & _BIT5)) << 4) | (((WORD)(ScalerGetByte(P40_1E_M2_VGIP_HV_DELAY) & _BIT1)) << 7) | ScalerGetByte(P40_1C_M2_IVS_DELAY)));
    }
    else if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S1) == _TRUE)
    {
        usIVSDelay = (((((WORD)(ScalerGetByte(P80_16_S1_IPH_ACT_WID_H) & _BIT5)) << 4) | (((WORD)(ScalerGetByte(P80_1E_S1_VGIP_HV_DELAY) & _BIT1)) << 7) | ScalerGetByte(P80_1C_S1_IVS_DELAY)));
    }
    else if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S2) == _TRUE)
    {
        usIVSDelay = (((((WORD)(ScalerGetByte(PC0_16_S2_IPH_ACT_WID_H) & _BIT5)) << 4) | (((WORD)(ScalerGetByte(PC0_1E_S2_VGIP_HV_DELAY) & _BIT1)) << 7) | ScalerGetByte(PC0_1C_S2_IVS_DELAY)));
    }

    if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
    {
        return (usIVSDelay << 1);
    }
    else
    {
        return usIVSDelay;
    }
}

//--------------------------------------------------
// Description  : Set Capture V Delay
// Input Value  : usIVSDelay --> V Delay
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetCaptureVDelay(WORD usIVSDelay)
{
    if(ScalerVgipGetDigitalCaptureStatus() == _TRUE)
    {
        return;
    }

    if(ScalerFmtCnvFtoPGetStatus(GET_VGIP_INPUT_PATH()) == _TRUE)
    {
        usIVSDelay = (usIVSDelay >> 1);
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M1) == _TRUE)
    {
        // Store effective values
        g_pucVgipDelaySetting[0] = ((g_pucVgipDelaySetting[0] & ~_BIT1) | ((HIBYTE(usIVSDelay) & _BIT0) << 1));
        g_pucVgipMiscSetting[0] = ((g_pucVgipMiscSetting[0] & ~_BIT5) | ((HIBYTE(usIVSDelay) & _BIT1) << 4));

        // Set M1 capture V delay
        ScalerSetByte(P0_16_M1_IPH_ACT_WID_H, g_pucVgipMiscSetting[0]);
        ScalerSetByte(P0_1E_M1_VGIP_HV_DELAY, g_pucVgipDelaySetting[0]);
        ScalerSetByte(P0_1C_M1_IVS_DELAY, LOBYTE(usIVSDelay));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_M2) == _TRUE)
    {
        // Store effective values
        g_pucVgipDelaySetting[1] = ((g_pucVgipDelaySetting[1] & ~_BIT1) | ((HIBYTE(usIVSDelay) & _BIT0) << 1));
        g_pucVgipMiscSetting[1] = ((g_pucVgipMiscSetting[1] & ~_BIT5) | ((HIBYTE(usIVSDelay) & _BIT1) << 4));

        // Set M1 capture V delay
        ScalerSetByte(P40_16_M2_IPH_ACT_WID_H, g_pucVgipMiscSetting[1]);
        ScalerSetByte(P40_1E_M2_VGIP_HV_DELAY, g_pucVgipDelaySetting[1]);
        ScalerSetByte(P40_1C_M2_IVS_DELAY, LOBYTE(usIVSDelay));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S1) == _TRUE)
    {
        // Store effective values
        g_pucVgipDelaySetting[2] = ((g_pucVgipDelaySetting[2] & ~_BIT1) | ((HIBYTE(usIVSDelay) & _BIT0) << 1));
        g_pucVgipMiscSetting[2] = ((g_pucVgipMiscSetting[2] & ~_BIT5) | ((HIBYTE(usIVSDelay) & _BIT1) << 4));

        // Set M1 capture V delay
        ScalerSetByte(P80_16_S1_IPH_ACT_WID_H, g_pucVgipMiscSetting[2]);
        ScalerSetByte(P80_1E_S1_VGIP_HV_DELAY, g_pucVgipDelaySetting[2]);
        ScalerSetByte(P80_1C_S1_IVS_DELAY, LOBYTE(usIVSDelay));
    }

    if(CHK_VGIP_INPUT_PATH(_INPUT_PATH_S2) == _TRUE)
    {
        // Store effective values
        g_pucVgipDelaySetting[3] = ((g_pucVgipDelaySetting[3] & ~_BIT1) | ((HIBYTE(usIVSDelay) & _BIT0) << 1));
        g_pucVgipMiscSetting[3] = ((g_pucVgipMiscSetting[3] & ~_BIT5) | ((HIBYTE(usIVSDelay) & _BIT1) << 4));

        // Set M1 capture V delay
        ScalerSetByte(PC0_16_S2_IPH_ACT_WID_H, g_pucVgipMiscSetting[3]);
        ScalerSetByte(PC0_1E_S2_VGIP_HV_DELAY, g_pucVgipDelaySetting[3]);
        ScalerSetByte(PC0_1C_S2_IVS_DELAY, LOBYTE(usIVSDelay));
    }
}

