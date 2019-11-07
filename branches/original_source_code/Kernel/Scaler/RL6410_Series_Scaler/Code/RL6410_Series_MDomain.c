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
// ID Code      : RL6410_Series_MDomain.c No.0000
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

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerMDomainSetDisplayTimingGenActiveRegion(EnumDisplayDataPath enumDisplayDataPath);
bit ScalerMDomainMemoryCheck(EnumInputDataPath enumInputDataPath);
void ScalerMDomainSetDisplayFormat(BYTE ucMemorySel);

#if(_OD_SUPPORT == _ON)
#if(_FRC_SUPPORT == _ON)
WORD ScalerMDomainGetFRCMemoryBW(void);
#endif // End of #if(_FRC_SUPPORT == _ON)
#endif // End of #if(_OD_SUPPORT == _ON)

#if(_FREESYNC_OD_MEASURE == _ON)
void ScalerMDomainFREESYNCODSetDisplayFormat(WORD usDHtotal, DWORD ulDclk, WORD usTarFreq);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set Display Timgin Gen: Diaplay active region
// Input Value  : display data path
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetDisplayTimingGenActiveRegion(EnumDisplayDataPath enumDisplayDataPath)
{
    switch(enumDisplayDataPath)
    {
        case _DISPLAY_PATH_M1:
            // Main1 Active
            // Set Main1 H Active Start / End
            ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_05_DISPLAY_HOR_ACT_STA_H);
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(GET_MDOMAIN_OUTPUT_HSTART()) & 0x1F));
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(GET_MDOMAIN_OUTPUT_HSTART()));
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(GET_MDOMAIN_OUTPUT_HSTART() + GET_MDOMAIN_OUTPUT_HWIDTH()) & 0x1F));
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(GET_MDOMAIN_OUTPUT_HSTART() + GET_MDOMAIN_OUTPUT_HWIDTH()));

            // Set Main1 V Active Start / End
            ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_10_DISPLAY_VER_ACT_STA_H);
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(GET_MDOMAIN_OUTPUT_VSTART()) & 0x1F));
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(GET_MDOMAIN_OUTPUT_VSTART()));
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()) & 0x1F));
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()));
            break;

#if((_PBP_TB_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))
        case _DISPLAY_PATH_M2:
            // Main2 Active
            // Set Main2 H Active Start / End
            ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_16_DISPLAY_HOR_ACT_STA_H_M2);
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(GET_MDOMAIN_OUTPUT_HSTART()) & 0x1F));
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(GET_MDOMAIN_OUTPUT_HSTART()));
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(GET_MDOMAIN_OUTPUT_HSTART() + GET_MDOMAIN_OUTPUT_HWIDTH()) & 0x1F));
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(GET_MDOMAIN_OUTPUT_HSTART() + GET_MDOMAIN_OUTPUT_HWIDTH()));

            // Set Main2 V Active Start / End
            ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1A_DISPLAY_VER_ACT_STA_H_M2);
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(GET_MDOMAIN_OUTPUT_VSTART()) & 0x1F));
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(GET_MDOMAIN_OUTPUT_VSTART()));
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()) & 0x1F));
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()));
            break;
#endif

#if((_PIP_DISPLAY_SUPPORT == _ON) || (_PBP_LR_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))
        case _DISPLAY_PATH_S1:
            // Sub1 Active
            ScalerMDomainSetSubActiveRegion();
            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_PATH_S2:
            // Sub2 Active
            // Set Sub2 H Active Start / End
            ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_16_DISPLAY_HOR_ACT_STA_H_S2);
            ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(GET_MDOMAIN_OUTPUT_HSTART()) & 0x1F));
            ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(GET_MDOMAIN_OUTPUT_HSTART()));
            ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(GET_MDOMAIN_OUTPUT_HSTART() + GET_MDOMAIN_OUTPUT_HWIDTH()) & 0x1F));
            ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(GET_MDOMAIN_OUTPUT_HSTART() + GET_MDOMAIN_OUTPUT_HWIDTH()));

            // Set Sub2 V Active Start / End
            ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_1A_DISPLAY_VER_ACT_STA_H_S2);
            ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(GET_MDOMAIN_OUTPUT_VSTART()) & 0x1F));
            ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(GET_MDOMAIN_OUTPUT_VSTART()));
            ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()) & 0x1F));
            ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()));
            break;
#endif

        default:
            break;
    }

#if(_ULTRA_VIVID_SUPPORT == _ON)
#if((_PBP_TB_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))
    if((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_4P) ||
       (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PBP_TB))
    {
        // Modify First Line of Bottom for D-SHP Enable
        ScalerColorSHPHStartAdjust(enumDisplayDataPath);
    }
#endif
#endif
}

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Check memory
// Input Value  : None
// Output Value : Memory check pass or fail
//--------------------------------------------------
bit ScalerMDomainMemoryCheck(EnumInputDataPath enumInputDataPath)
{
    WORD usReg_02 = P0_02_STATUS0;

    switch(enumInputDataPath)
    {
        case _INPUT_PATH_ALL:
            usReg_02 = P0_02_STATUS0;
            break;

        case _INPUT_PATH_M1_M2:
        case _INPUT_PATH_M1:
        default:
            usReg_02 = P0_02_STATUS0;
            break;

        case _INPUT_PATH_M2:
            usReg_02 = P40_02_M2_STATUS0;
            break;

        case _INPUT_PATH_S1_S2:
        case _INPUT_PATH_S1:
            usReg_02 = P80_02_S1_STATUS0;
            break;

        case _INPUT_PATH_S2:
            usReg_02 = PC0_02_S2_STATUS0;
            break;
    }

    // Check fifo underflow and Input HVsync error flag, Display Vsync timeout flag
    if((ScalerGetBit(usReg_02, (_BIT6 | _BIT5 | _BIT0)) != 0x00) || (ScalerGetBit(P0_0C_WATCH_DOG_CTRL0, _BIT0) != 0x00))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Display Format
// Input Value  : free run/ frame sync line buffer/ frame sync frame buffer /
//                MN frame sync/ free run no input
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetDisplayFormat(BYTE ucMemorySel)
{
    BYTE ucDpllSscgDiv = ScalerMDomainGetDpllSscgDivMode();
    bit bDispFotmatDoubleBuf = 0;
    DWORD ulDclkSscgMax = 0;
    DWORD ulDclkSscgMin = 0;
    WORD usFreerunDvt = 0;
    WORD usWatchDogDvt = 0;
    DWORD ulDclk = 0;

#if(_FRAME_SYNC_LINE_BUFFER_SUPPORT == _ON)
    WORD usDhtotalBackup = 0;

    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H, 2, &pData[0], _AUTOINC);
    usDhtotalBackup = PDATA_WORD(0) & 0x1FFF;
#endif

    if((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P) && (GET_MDOMAIN_OUTPUT_VBHEIGHT() == GET_MDOMAIN_OUTPUT_VHEIGHT()))
    {
        SET_MDOMAIN_OUTPUT_VBSTART(GET_MDOMAIN_OUTPUT_VSTART());
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE) &&
       ((GET_ROT_TYPE() != _ROT_DISABLE) && (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)))
    {
        SET_MDOMAIN_OUTPUT_VBSTART(_PANEL_DV_START);
    }
#endif

    switch(ucMemorySel)
    {
        case _FRAME_SYNC_LINE_BUFFER:

            // Set DVTotal
            PDATA_WORD(2) = (DWORD)g_stMDomainInputData.usVTotal * (DWORD)(g_stMDomainOutputData.usVHeight) / g_stMDomainInputData.usVHeight;

#if(_FREESYNC_SUPPORT == _ON)
            if(GET_FREESYNC_ENABLED() == _TRUE)
            {
                // DVtotal for WD setting
                usWatchDogDvt = _PANEL_DV_TOTAL_MAX + 64;

                // DVtotal for free run setting
                usFreerunDvt = _PANEL_DV_TOTAL_MAX;
            }
            else
#endif
            {
                // DVtotal for WD setting
                usWatchDogDvt = PDATA_WORD(2) + 64;

                // DVtotal for free run setting
                usFreerunDvt = PDATA_WORD(2);
            }

            // Enable Display Timing, Set Frame sync
            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

            // Calculate Dclk
            // PDATA_DWORD(0) = (DWORD)(g_stMDomainOutputData.usHTotal) * (DWORD)g_stMDomainInputData.usHFreq * (DWORD)(g_stMDomainOutputData.usVHeight) / g_stMDomainInputData.usVHeight / 10;
            ulDclk = (DWORD)(g_stMDomainOutputData.usHTotal) * (DWORD)g_stMDomainInputData.usHFreq / 10;/** (DWORD)(g_stMDomainOutputData.usVHeight) / g_stMDomainInputData.usVHeight / 10; */
            ulDclk = ulDclk / g_stMDomainInputData.usVHeight;
            ulDclk = ulDclk * (DWORD)(g_stMDomainOutputData.usVHeight);

            break;

#if(_FRC_SUPPORT == _ON)

        case _MN_FRAME_SYNC_MEMORY:

            if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
            {
                // DVtotal for WD setting
                usWatchDogDvt = _PANEL_DV_TOTAL + 64;

                if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_25_MN_FRAME_RATE_EN, _BIT7) == _BIT7)
                {
                    // DVtotal for free run setting
                    GET_FREE_RUN_DVTOTAL(usFreerunDvt);

                    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H, 2, &pData[4], _AUTOINC);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
                    SET_MDOMAIN_OUTPUT_HTOTAL((PDATA_WORD(2) & 0x1FFF) + 8);
#else
                    SET_MDOMAIN_OUTPUT_HTOTAL((PDATA_WORD(2) & 0x1FFF) + 4);
#endif
                }
                else
                {
                    // DVtotal for free run setting
                    usFreerunDvt = usWatchDogDvt + 1;
                }

                // Calculate Dclk
                ulDclk = (DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * _PANEL_DV_TOTAL / 10 * g_usDVFreq / 1000;
            }

            break;

        case _FRAME_SYNC_MEMORY:

            if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
            {
#if(_FREESYNC_SUPPORT == _ON)
                if(GET_FREESYNC_ENABLED() == _TRUE)
                {
                    if((ScalerMDomainFSLineBufferDclkDvtotalCheck() == _TRUE) &&
                       (g_stMDomainOutputData.usVBackHeight == g_stMDomainOutputData.usVHeight))
                    {
                        // According Frame sync line buffer to Calculate Dclk
                        ulDclk = (DWORD)g_stMDomainOutputData.usHTotal * g_stMDomainInputData.usHFreq / 10 / g_stMDomainInputData.usVHeight * g_stMDomainOutputData.usVHeight;
                    }
                    else
                    {
                        // Calculate Dclk
                        ulDclk = (((DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * _PANEL_DV_TOTAL) + _LAST_LINE_TARGET) / 10 * g_usDVFreq / 1000;
                    }

                    // DVtotal for WD setting
                    usWatchDogDvt = _PANEL_DV_TOTAL_MAX + 64;
                }
                else
#endif
                {
                    // Calculate Dclk
                    ulDclk = (((DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * _PANEL_DV_TOTAL) + _LAST_LINE_TARGET) / 10 * g_usDVFreq / 1000;

                    // DVtotal for WD setting
                    usWatchDogDvt = _PANEL_DV_TOTAL + 64;
                }

                // DVtotal for free run setting
                usFreerunDvt = usWatchDogDvt + 1;
            }

            break;

        case _FREE_RUN_MEMORY:

            if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
            {
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
                if((ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE) &&
                   ((GET_ROT_TYPE() != _ROT_DISABLE) && (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)))
                {
                    PDATA_WORD(2) = _PANEL_DV_TOTAL;
                }
                else
#endif
                {
                    if((GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER) &&
                       (g_stMDomainOutputData.usVHeight == _PANEL_DV_HEIGHT) &&
                       (g_stMDomainInputData.usVFreq > _PANEL_MAX_FRAME_RATE))
                    {
                        PDATA_WORD(2) = ScalerFRCSetOneFrameDVTotal();
                    }
                    else if((GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER) &&
                            (((g_stMDomainOutputData.usVHeight < _PANEL_DV_HEIGHT) && (g_stMDomainInputData.usVFreq > _PANEL_MAX_FRAME_RATE)) || (g_stMDomainInputData.usVFreq < _PANEL_MIN_FRAME_RATE)))
                    {
                        PDATA_WORD(2) = _PANEL_DV_TOTAL_MIN;
                    }
                    else
                    {
                        PDATA_WORD(2) = _PANEL_DV_TOTAL;
                    }
                }

                // DVtotal for WD setting
                usWatchDogDvt = PDATA_WORD(2) + 64;

                // DVtotal for free run setting
                usFreerunDvt = PDATA_WORD(2);

                // Calculate Dclk
                ulDclk = (DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * PDATA_WORD(2) / 10 * g_usDVFreq / 1000;
            }
            break;

#endif // End of #if(_FRC_SUPPORT == _ON)

        case _FREE_RUN_NO_INPUT:
        default:
            ScalerMDomainSetDisplayTimingGenBackground(GET_MDOMAIN_DISPLAY_MODE());

            // Disable Interlaced_FS_Delay_Fine_Tuning
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT1, 0x00);

            // PDATA_WORD(2): Calculate DVtotal
            PDATA_WORD(2) = GET_MDOMAIN_OUTPUT_VTOTAL();

            // DVtotal for WD setting
            usWatchDogDvt = PDATA_WORD(2) + 64;

            // DVtotal for free run setting
            usFreerunDvt = PDATA_WORD(2) + 1;

            // Enable Display Timing, and enable free run mode
            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

            // Disable M:N frame sync mode
            ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_25_MN_FRAME_RATE_EN, ~_BIT7, 0x00);

            // Calculate Dclk
            ulDclk = (DWORD)_PANEL_DH_TOTAL * _PANEL_DV_TOTAL / 10 * _PANEL_TYP_FRAME_RATE / 1000;

            break;
    }

    // If global double buffer off, turn on display double buffer
    if((ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0) && (ucMemorySel != _FREE_RUN_NO_INPUT))
    {
        bDispFotmatDoubleBuf = (bit)ScalerGetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, _BIT7);
        ScalerSetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, ~_BIT7, _BIT7);
    }

#if(_PIP_DISPLAY_SUPPORT == _ON)
    // Display timing gen setting
    if((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PIP) &&
       (GET_MDOMAIN_OUTPUT_DATA_PATH() == _DISPLAY_PATH_S1))
    {
        ScalerMDomainSetSubBackground();
    }
#endif

    ScalerMDomainSetDisplayTimingGen(GET_MDOMAIN_OUTPUT_DATA_PATH());

    if((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P) || (ucMemorySel == _FREE_RUN_NO_INPUT))
    {
#if(_FRC_SUPPORT == _ON)
        // M:N case reset to display setting, no need to set M:N tracking again
        if((ucMemorySel != _MN_FRAME_SYNC_MEMORY) ||
           (ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_25_MN_FRAME_RATE_EN, _BIT7) != _BIT7))
#endif
        {
            ulDclkSscgMax = ((DWORD)_PANEL_PIXEL_CLOCK_MAX_KHZ - ((DWORD)_PANEL_PIXEL_CLOCK_MAX_KHZ / 100) - (_PANEL_PIXEL_CLOCK_MAX_KHZ * _DCLK_SPREAD_RANGE * 5 / 2000 / ucDpllSscgDiv));
            ulDclkSscgMin = ((DWORD)_PANEL_PIXEL_CLOCK_MIN_KHZ + ((DWORD)_PANEL_PIXEL_CLOCK_MIN_KHZ / 100) + (_PANEL_PIXEL_CLOCK_MIN_KHZ * _DCLK_SPREAD_RANGE * 5 / 2000 / ucDpllSscgDiv));

            // If DClk Out of Panel Spec => Try Modifying DHTotal
            if((ulDclk >= ulDclkSscgMax) || (ulDclk <= ulDclkSscgMin))
            {
                // DClk >= Panel Max with Max SSC ((_DCLK_SPREAD_RANGE / ucDpllSscgDiv) / 2 each Side plus 1 % margin)
                if(ulDclk >= ulDclkSscgMax)
                {
                    // Calculate Target DHTotal
                    PDATA_WORD(5) = (GET_MDOMAIN_OUTPUT_HTOTAL() * ulDclkSscgMax / ulDclk);

                    // Make Sure DHTotal to be multiple of output port
                    PDATA_WORD(5) -= (PDATA_WORD(5) % _DHTOTAL_MULTIPLE);

                    PDATA_WORD(5) = ((PDATA_WORD(5) < _PANEL_DH_TOTAL_MIN) ? _PANEL_DH_TOTAL_MIN : PDATA_WORD(5));

                    DebugMessageScaler("D Clock Larger Than Panel Spec => Modify Htotal", PDATA_WORD(5));
                }
                else // DClk <= Panel Min plus Max SSC (plus margin)
                {
                    // Calculate Target DHTotal
                    PDATA_WORD(5) = g_stMDomainOutputData.usHTotal * ulDclkSscgMin / ulDclk;

                    // Make Sure DHTotal to be multiple of output port
                    PDATA_WORD(5) = PDATA_WORD(5) + _DHTOTAL_MULTIPLE - (PDATA_WORD(5) % _DHTOTAL_MULTIPLE);

                    PDATA_WORD(5) = ((PDATA_WORD(5) > _PANEL_DH_TOTAL_MAX) ? _PANEL_DH_TOTAL_MAX : PDATA_WORD(5));

                    DebugMessageScaler("D Clock Smaller Than Panel Spec => Modify Htotal", PDATA_WORD(5));
                }

                // Calculate Target Dclk
                ulDclk = (ulDclk / g_stMDomainOutputData.usHTotal * PDATA_WORD(5)) +
                         ((ulDclk % g_stMDomainOutputData.usHTotal) * PDATA_WORD(5) / g_stMDomainOutputData.usHTotal);

                SET_MDOMAIN_OUTPUT_HTOTAL(PDATA_WORD(5));

                // Check Dclk
                if(((ucMemorySel == _FRAME_SYNC_MEMORY) || (ucMemorySel == _MN_FRAME_SYNC_MEMORY)) &&
                   (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P) &&
                   ((ulDclk >= ulDclkSscgMax) || (ulDclk <= ulDclkSscgMin)))
                {
                    if(ulDclk >= ulDclkSscgMax)
                    {
                        // Calculate Target DVTotal
                        PDATA_WORD(6) = ((DWORD)_PANEL_DV_TOTAL * ulDclkSscgMax / ulDclk);
                        PDATA_WORD(6) = ((PDATA_WORD(6) < _PANEL_DV_TOTAL_MIN) ? _PANEL_DV_TOTAL_MIN : PDATA_WORD(6));
                    }
                    else // if(ulDclk <= ulDclkSscgMin)
                    {
                        // Calculate Target DVTotal
                        PDATA_WORD(6) = (DWORD)_PANEL_DV_TOTAL * ulDclkSscgMin / ulDclk + 1;
                        PDATA_WORD(6) = ((PDATA_WORD(6) > _PANEL_DV_TOTAL_MAX) ? _PANEL_DV_TOTAL_MAX : PDATA_WORD(6));
                    }
                    ulDclk = (DWORD)g_stMDomainOutputData.usHTotal * PDATA_WORD(6) / 10 * g_usDVFreq / 1000;

#if(_FREESYNC_SUPPORT == _ON)
                    if(GET_FREESYNC_ENABLED() == _TRUE)
                    {
                        // DVtotal for WD setting
                        PDATA_WORD(6) = _PANEL_DV_TOTAL_MAX;
                    }
#endif

                    usWatchDogDvt = PDATA_WORD(6) + 64;
                    usFreerunDvt = PDATA_WORD(6) + 1;
                }
            }

            // Set DHtotal
            ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(GET_MDOMAIN_OUTPUT_HTOTAL() - 8) & 0x1F));
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(GET_MDOMAIN_OUTPUT_HTOTAL() - 8));
#else
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(GET_MDOMAIN_OUTPUT_HTOTAL() - 4) & 0x1F));
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(GET_MDOMAIN_OUTPUT_HTOTAL() - 4));
#endif

            // Set Last line for free run
            ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_32_FIXED_LAST_LINE_MSB);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(GET_MDOMAIN_OUTPUT_HTOTAL() - 8) & 0x1F));
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(GET_MDOMAIN_OUTPUT_HTOTAL() - 8));
#else
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(GET_MDOMAIN_OUTPUT_HTOTAL() - 4) & 0x1F));
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(GET_MDOMAIN_OUTPUT_HTOTAL() - 4));
#endif

            // Set Frame Sync Watch Dog
            ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0B_DISPLAY_VER_TOTAL_H);
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usWatchDogDvt) & 0x3F));
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usWatchDogDvt));

            // Set DVtotal for free run
            ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_30_FIXED_DVTOTAL_MSB);
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usFreerunDvt) & 0x3F));
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usFreerunDvt));

#if(_FRAME_SYNC_LINE_BUFFER_SUPPORT == _ON)
            if(GET_MEMORY_SELECT() == _FRAME_SYNC_LINE_BUFFER)
            {
                ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H, 2, &pData[0], _AUTOINC);

                // Frame sync line buffer need to fine tune Dclk according I-active-region & D-active-region
                if(usDhtotalBackup != (PDATA_WORD(0) & 0x1FFF))
                {
                    ScalerGlobalDDomainDBApply(_DB_APPLY_POLLING);
                }
            }
#endif

            SET_D_CLK_FREQ(ulDclk);

            DebugMessageScaler("DCLK", GET_D_CLK_FREQ());

            // Set DClk
            ScalerPLLSetDPLLFreq(GET_D_CLK_FREQ());
        }

    } // End of if((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P) || (ucMemorySel == _FREE_RUN_NO_INPUT)

    if((ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0) && (ucMemorySel != _FREE_RUN_NO_INPUT))
    {
        ScalerSetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, ~_BIT6, _BIT6);
        ScalerTimerPollingFlagProc(20, P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, _BIT6, 0);

        ScalerSetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, ~_BIT7, ((BYTE)bDispFotmatDoubleBuf << 7));
    }
}

#if(_OD_SUPPORT == _ON)
#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Calculate FRC use memory BW
// Input Value  : IVF, IVheight and IHwidth
// Output Value : FRC use memory BW, unit: Bit_Num / Memory_Bus_bit, 100k
//--------------------------------------------------
WORD ScalerMDomainGetFRCMemoryBW(void)
{
    BYTE ucDpllSscgDiv = ScalerMDomainGetDpllSscgDivMode();
    WORD usIVtotal = 0;

    //-----------------------------------------------------------------------------
    // FRC write BW = IVtotal * Fifo_width * Bit_Num / Memory_Bus_bit * IVF
    // FRC read BW  = DVtotal * Fifo_width * Bit_Num / Memory_Bus_bit * DVF * (1 + (SSCG_Range + margin) / 2)
    //-----------------------------------------------------------------------------

    PDATA_WORD(0) = ((g_stMDomainInputData.usHWidth < g_stMDomainOutputData.usHWidth) ? g_stMDomainInputData.usHWidth : g_stMDomainOutputData.usHWidth);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        PDATA_WORD(0) += (GET_MDOMAIN_EXTENSION_LEN() * 2);
    }
#endif

#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        usIVtotal = (DWORD)g_stMDomainInputData.usVHeight * 105 / 100;
    }
    else
#endif
    {
        usIVtotal = g_stMDomainInputData.usVTotal;
    }

    // FRC write BW
    PDATA_DWORD(1) = (((DWORD)usIVtotal * PDATA_WORD(0) * GET_MEMORY_DATA_BIT() / _MEMORY_BUS_WIDTH / 10) * g_stMDomainInputData.usVFreq / 100);

    // FRC read BW
    PDATA_DWORD(2) = ((((DWORD)g_stMDomainOutputData.usVTotal * PDATA_WORD(0) * GET_MEMORY_DATA_BIT() / _MEMORY_BUS_WIDTH / 10) * g_usDVFreq / 100) +
                      (((DWORD)g_stMDomainOutputData.usVTotal * PDATA_WORD(0) * GET_MEMORY_DATA_BIT() / _MEMORY_BUS_WIDTH / 100) * g_usDVFreq * ((_DCLK_SPREAD_RANGE / ucDpllSscgDiv) + _DCLK_SPREAD_RANGE_MARGIN) / 4 / 100 / 10));
    PDATA_DWORD(0) = ((PDATA_DWORD(1) + PDATA_DWORD(2)) / 1000) + (((PDATA_DWORD(1) + PDATA_DWORD(2)) % 1000) ? 1 : 0); // unit:100k

    DebugMessageFRC("4.FRC BW", (PDATA_DWORD(0)));

    return (PDATA_DWORD(0) & 0xFFFF);
}

#endif // End of #if(_OD_SUPPORT == _ON)
#endif // End of #if(_FRC_SUPPORT == _ON)

#if(_FREESYNC_OD_MEASURE == _ON)
//--------------------------------------------------
// Description  : Set Display Format for FREESYNC OD measure
// Input Value  : Current DHtotal(pixel)/ Current Dclk(kHz)/ Target Measure VFreq(0.1Hz)
// Output Value : None
//--------------------------------------------------
void ScalerMDomainFREESYNCODSetDisplayFormat(WORD usDHtotal, DWORD ulDclk, WORD usTarFreq)
{
    ScalerGlobalDoubleBufferEnable(_DISABLE);
    ScalerGlobalPathWatchDog(_INPUT_PATH_ALL, _DISABLE);

    // Calculate FREESYNC DVtotal for OD measure
    PDATA_WORD(4) = (DWORD)ulDclk * 1000 / usDHtotal * 10 / usTarFreq;

    if(PDATA_WORD(4) < _PANEL_DV_TOTAL_MIN)
    {
        PDATA_WORD(4) = _PANEL_DV_TOTAL_MIN;
    }

    // DVtotal for WD setting
    PDATA_WORD(3) = PDATA_WORD(4) + 64;

    // Set Frame Sync Watch Dog
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0B_DISPLAY_VER_TOTAL_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(PDATA_WORD(3)) & 0x3F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(PDATA_WORD(3)));

    // Set DVtotal for free run
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_30_FIXED_DVTOTAL_MSB);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(PDATA_WORD(4)) & 0x3F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(PDATA_WORD(4)));

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    // Set DHtotal
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDHtotal - 8) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDHtotal - 8));

    // Set Last line for free run
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_32_FIXED_LAST_LINE_MSB);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDHtotal - 8) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDHtotal - 8));
#else
    // Set DHtotal
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDHtotal - 4) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDHtotal - 4));

    // Set Last line for free run
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_32_FIXED_LAST_LINE_MSB);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDHtotal - 4) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDHtotal - 4));
#endif

    SET_D_CLK_FREQ(ulDclk);

    // Set DClk
    ScalerPLLSetDPLLFreq(GET_D_CLK_FREQ());

    // Set Free Run Mode
    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, 0x00);

    // Clear fifo flag
    ScalerSetByte(P0_02_STATUS0, 0xFF);
    ScalerSetByte(P40_02_M2_STATUS0, 0xFF);

    // Clear Display Vsync timeout flag
    ScalerSetBit(P0_0C_WATCH_DOG_CTRL0, ~_BIT0, _BIT0);

    ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
    ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
}
#endif
