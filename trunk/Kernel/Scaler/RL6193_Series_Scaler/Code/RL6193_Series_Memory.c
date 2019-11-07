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
// ID Code      : RL6193_Series_Memory.c No.0000
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
void ScalerMemoryFrameSyncSetDt(void);
DWORD ScalerMemoryGetIVS2DVSDelayPixel(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Setup Frame Sync Dt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemoryFrameSyncSetDt(void)
{
    DWORD ulIVStoDVSPixels = 0;
    DWORD ulIVstart = 0;
    DWORD ulDVstart = 0;
    BYTE ucEOshift = 0;

    // Calculate DVS to DH Active in ICLK
    ulDVstart = ((DWORD)g_stMDomainOutputData.usHTotal * g_stMDomainOutputData.usVStart) + g_stMDomainOutputData.usHStart;
    ulDVstart = ulDVstart * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVHeight * g_stMDomainInputData.usHTotal / g_stMDomainOutputData.usHTotal;

    // Calculate IVS to IH Active in ICLK
    ulIVstart = ((DWORD)g_stMDomainInputData.usHTotal * g_stMDomainInputData.usVStart) + g_stMDomainInputData.usHStart;

    // IVS2DVS line skip disable
    ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT3, _BIT3);

    // Frame Sync Memory Settings
    if(GET_V_SCALE_UP() == _TRUE)    // Vertical Scaling Up
    {
        ulIVstart += (DWORD)g_stMDomainInputData.usHTotal * ScalerMemoryGetScaleUpDt() / 100;
    }
    else
    {
        if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
        {
            // get FIFI Width
            PDATA_WORD(4) = (g_stMDomainInputData.usHWidth > g_stMDomainOutputData.usHWidth) ? g_stMDomainOutputData.usHWidth : g_stMDomainInputData.usHWidth;

            if(GET_V_SCALE_DOWN() == _TRUE)    // Vertical Scaling Down
            {
                ulIVstart += g_stMDomainInputData.usHTotal * 2 + ((DWORD)g_stMDomainInputData.usHTotal * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVHeight * _M_DOMAMAIN_FIFO_BIT / GET_MEMORY_DATA_BIT() / PDATA_WORD(4));
            }
            else    // Vertical Scaling Bypass
            {
                ulIVstart += g_stMDomainInputData.usHTotal * 2 + ((DWORD)g_stMDomainInputData.usHTotal * _M_DOMAMAIN_FIFO_BIT / GET_MEMORY_DATA_BIT() / PDATA_WORD(4));
            }
        }
        else
        {
            if(GET_V_SCALE_DOWN() == _TRUE)    // Vertical Scaling Down
            {
                ulIVstart += g_stMDomainInputData.usHTotal * 2 + ((DWORD)g_stMDomainInputData.usHTotal * g_stMDomainInputData.usVHeight / (g_stMDomainOutputData.usVHeight * 2));
            }
            else    // Vertical Scaling Bypass
            {
                ulIVstart += g_stMDomainInputData.usHTotal * 2 + g_stMDomainInputData.usHTotal / 2;
            }
        }
    }

#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        if(ulIVstart <= ulDVstart)
        {
            // DVst - (IVst + Dt) in D-line
            PDATA_DWORD(3) = (ulDVstart - ulIVstart) * g_stMDomainOutputData.usVHeight / g_stMDomainInputData.usVHeight / g_stMDomainInputData.usHTotal + 1;

            if(g_stMDomainOutputData.usVStart > PDATA_DWORD(3))
            {
                g_stMDomainOutputData.usVStart -= PDATA_DWORD(3);
            }
            else
            {
                g_stMDomainOutputData.usVStart = 1;
                DebugMessageFS("FREESYNC Dt warning", 0);
            }
        }
        else
        {
            // (IVst + Dt) - DVst in D-line
            PDATA_DWORD(3) = (ulIVstart - ulDVstart) * g_stMDomainOutputData.usVHeight / g_stMDomainInputData.usVHeight / g_stMDomainInputData.usHTotal;
            g_stMDomainOutputData.usVStart += PDATA_DWORD(3);
        }

        // Calculate DVS to DH Active in ICLK
        ulDVstart = ((DWORD)g_stMDomainOutputData.usHTotal * g_stMDomainOutputData.usVStart) + g_stMDomainOutputData.usHStart;
        ulDVstart = ulDVstart * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVHeight * g_stMDomainInputData.usHTotal / g_stMDomainOutputData.usHTotal;

        // IVS2DVS delay
        ulIVStoDVSPixels = (ulIVstart > ulDVstart) ? (ulIVstart - ulDVstart) : 0;

        if(ulIVStoDVSPixels > (g_stMDomainInputData.usHTotal * 9 / 10))
        {
            g_stMDomainOutputData.usVStart += 1;

            // Calculate DVS to DH Active in ICLK
            ulDVstart = ((DWORD)g_stMDomainOutputData.usHTotal * g_stMDomainOutputData.usVStart) + g_stMDomainOutputData.usHStart;
            ulDVstart = ulDVstart * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVHeight * g_stMDomainInputData.usHTotal / g_stMDomainOutputData.usHTotal;

            // IVS2DVS delay
            ulIVStoDVSPixels = (ulIVstart > ulDVstart) ? (ulIVstart - ulDVstart) : 0;

            DebugMessageFS("FREESYNC IVS2DVS delay close to 1 line, modify IVS2DVS delay", ulIVStoDVSPixels);
        }
    }
    else
#endif
    {
        // If DVSt > (IVSt + Dt) means no further IVS2DVSDelay can be added!!
        // Preserve 2 line margin in advance
        PDATA_DWORD(3) = ulDVstart + 2 * g_stMDomainInputData.usHTotal;

        if(PDATA_DWORD(3) > ulIVstart)
        {
            // Calculate insufficient line number
            WORD usInsufficientLines = (PDATA_DWORD(3) - ulIVstart) / g_stMDomainInputData.usHTotal + 1;

            DebugMessageFS("2. No Further IVS2DVSDelay Can Be Added", 0x00);

            // Enlarge IVSt for insufficient lines
            g_stMDomainInputData.usVStart += usInsufficientLines;

            if(ScalerVgipGetDigitalCaptureStatus() == _FALSE)
            {
                // Set new IVSt under analog capture
                ScalerVgipSetCaptureVStartPosition(g_stMDomainInputData.usVStart);
            }
            else
            {
                // Set new IVSt under digital capture
                ScalerVgipSetCaptureVStartPosition((GET_INPUT_TIMING_VHEIGHT() - GET_MDOMAIN_INPUT_VHEIGHT()) / 2 + usInsufficientLines);
            }

            // Modify Original (IVSt + Dt) Value
            ulIVstart += (DWORD)usInsufficientLines * g_stMDomainInputData.usHTotal;
        }

        // Set IVS to DVS Delay
        PDATA_DWORD(0) = (ulIVstart > ulDVstart) ? (ulIVstart - ulDVstart) : 0;

        DebugMessageFS("Target IVS to DVS Delay Value", PDATA_DWORD(0) * 10 / g_stMDomainInputData.usHTotal);

        // Get Current IVS2DVS Delay + DVS Width in Input Lines (Get Ceiling Value) + 1 line for margin
        PDATA_WORD(2) = (PDATA_DWORD(0) + (DWORD)(_PANEL_DV_SYNC_HEIGHT) * g_stMDomainInputData.usVHeight * g_stMDomainInputData.usHTotal / g_stMDomainOutputData.usVHeight) / g_stMDomainInputData.usHTotal + 1;
        PDATA_WORD(2) &= 0x1FFF;

        // Enlarge DVSt if IVS2DVS Delay + DVS Width is larger than IVSt
        if(PDATA_WORD(2) >= (g_stMDomainInputData.usVStart))
        {
            DebugMessageFS("2. Target IVS2DVS Delay too Large", pData[5]);

            // Get the difference between IVS2DVS Delay and IVSt
            PDATA_WORD(2) = PDATA_WORD(2) - g_stMDomainInputData.usVStart + 1;

            // Get Required Increment of DVSt
            PDATA_WORD(2) = PDATA_WORD(2) * g_stMDomainOutputData.usVHeight / g_stMDomainInputData.usVHeight + 1;

            // Modify DVSt & background DVSt
            g_stMDomainOutputData.usVStart += PDATA_WORD(2);
            g_stMDomainOutputData.usVBackStart += PDATA_WORD(2);

            // Check VStart to be even. Avoid OSD win0/5/6/7/8/9 & CW270 lost data.
            g_stMDomainOutputData.usVStart = ((g_stMDomainOutputData.usVStart + 1) & 0xFFFE);
            g_stMDomainOutputData.usVBackStart = ((g_stMDomainOutputData.usVBackStart + 1) & 0xFFFE);

            // Modify IVS2DVS Delay
            PDATA_DWORD(0) -= (DWORD)PDATA_WORD(2) * g_stMDomainInputData.usHTotal * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVHeight;
        }

        // Store IVS-to-DVS pixels
        ulIVStoDVSPixels = PDATA_DWORD(0);
    }

    // Before is frame sync mode, current is frame sync mode, check IVS2DVS delay change
    if(ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT3) == _BIT3)
    {
        // Get Old IVS2DVS + IVSdelay (I line)
        PDATA_WORD(0) = (ScalerMemoryGetIVS2DVSDelayPixel() / g_stMDomainInputData.usHTotal);

        // Calculate current frame sync fine-tune value
        PDATA_WORD(1) = (ulIVStoDVSPixels / g_stMDomainInputData.usHTotal);

        // IVS2DVS Change Limit (Convert DVline limit to IVline)
        PDATA_WORD(2) = (DWORD)_PANEL_DV_LINE_CHG_LIMIT * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVHeight;

        ScalerMemoryFineTuneIVS2DVSDelay(PDATA_WORD(0), PDATA_WORD(1), PDATA_WORD(2));
    }

    if(GET_INTERLACED_MODE() == _TRUE)
    {
        // Video Compensation on Even Field
        if(ScalerGetBit(P0_32_SCALE_CONTROL_REG, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Enable Frame Sync Fine Tune on Odd Field
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        // Video Compensation on Odd Field
        else if(ScalerGetBit(P0_32_SCALE_CONTROL_REG, (_BIT7 | _BIT6)) == _BIT7)
        {
            // Enable Frame Sync Fine Tune on Even Field
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~(_BIT1 | _BIT0), _BIT1);
        }
        else
        {
            // Disable Frame Sync Fine Tune
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT1, 0x00);
        }
    }
    else
    {
        // Disable Frame Sync Fine Tune
        ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT1, 0x00);
    }

    if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
    {
        ucEOshift = 1;
        ulIVStoDVSPixels = (ulIVStoDVSPixels >> 1);
    }

    if((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P) &&
       (ScalerGetBit(P0_43_FS_DELAY_FINE_TUNE, _BIT1) == _BIT1) &&
       (ulIVStoDVSPixels >= (((g_stMDomainInputData.usHTotal >> 1) + 64) >> ucEOshift)))
    {
        // Preserve 0.5 lines + 64 pixel in Fine Tune Byte
        PDATA_WORD(2) = (ulIVStoDVSPixels - (((g_stMDomainInputData.usHTotal >> 1) + 64) >> ucEOshift)) / g_stMDomainInputData.usHTotal;
        PDATA_WORD(3) = (ulIVStoDVSPixels - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2))) >> 4;
        PDATA_WORD(4) = (ulIVStoDVSPixels - (g_stMDomainInputData.usHTotal >> (1 + ucEOshift)) - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2))) >> 4;
        pData[10] = ulIVStoDVSPixels - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2)) - (PDATA_WORD(3) << 4);
        pData[11] = ulIVStoDVSPixels - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2)) - (PDATA_WORD(4) << 4);
    }
    else
    {
        PDATA_WORD(2) = ulIVStoDVSPixels / g_stMDomainInputData.usHTotal;
        PDATA_WORD(3) = (ulIVStoDVSPixels - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2))) >> 4;
        PDATA_WORD(4) = 0x0000;
        pData[10] = ulIVStoDVSPixels - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2)) - (PDATA_WORD(3) << 4);
        pData[11] = 0x00;
    }

    //-------------------------------------------------
    // Apply updated Delay
    //-------------------------------------------------
    // IVS2DVS line delay, unit: line
    ScalerSetByte(P0_3E_IVS2DVS_DLY_LINE_H, (pData[4] & 0x1F));
    ScalerSetByte(P0_40_IVS2DVS_DLY_LINE_L, pData[5]);

    // IVS2DVS 16iclk1 delay, unit: 16 pixel
    PDATA_WORD(3) -= (PDATA_WORD(3) >= 1) ? 1 : 0;
    SET_IVS2DVS_DELAY_16ICLK1(PDATA_WORD(3));

    // IVS2DVS 16iclk2 delay, unit: 16 pixel
    PDATA_WORD(4) -= (PDATA_WORD(4) >= 1) ? 1 : 0;
    SET_IVS2DVS_DELAY_16ICLK2(PDATA_WORD(4));

    // IVS2DVS iclk1 delay, unit: 1 pixel
    ScalerSetBit(P0_3D_IV_DV_DELAY_CLK_FINE, ~0xF0, ((pData[10] & 0x0F) << 4));

    // IVS2DVS iclk2 delay, unit: 1 pixel
    ScalerSetBit(P0_3D_IV_DV_DELAY_CLK_FINE, ~0x0F, (pData[11] & 0x0F));
}

//--------------------------------------------------
// Description  : Get IVS2DVS delay, unit: pixel
// Input Value  : None
// Output Value : IVS2DVS delay, unit: pixel
//--------------------------------------------------
DWORD ScalerMemoryGetIVS2DVSDelayPixel(void)
{
    DWORD ulIVS2DVSDelayPixel = 0;

    // Get Initial Dt Fine Tune Value
    ulIVS2DVSDelayPixel = (((((DWORD)ScalerGetByte(P0_3E_IVS2DVS_DLY_LINE_H) << 8) & 0x1F00) | ScalerGetByte(P0_40_IVS2DVS_DLY_LINE_L)) * g_stMDomainInputData.usHTotal) +
                          ((((((DWORD)ScalerGetByte(P0_3F_DISPLAY_ALIGN_CONTROL) << 4) & 0x100) | ScalerGetByte(P0_41_IVS2DVS_DLY_TUNE_ODD)) + 1) * 16) +
                          ((ScalerGetByte(P0_3D_IV_DV_DELAY_CLK_FINE) >> 4) & 0x0F);

    if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
    {
        ulIVS2DVSDelayPixel = (ulIVS2DVSDelayPixel << 1);
    }

    return ulIVS2DVSDelayPixel;
}

