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
// ID Code      : RL6193_Series_FRC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#define __6193_SERIES_FRC__

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
#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
void ScalerFRCInitial(void);
#endif

#if(_FRC_SUPPORT == _ON)
void ScalerFRCControl(const StructSDRAMDataInfo *pstFIFOSize);
void ScalerFRCInputCtrl(WORD usHorSize, WORD usVerSize);
void ScalerFRCDisplayCtrl(WORD usHorSize, WORD usVerSize);

#if(_FREEZE_SUPPORT == _ON)
void ScalerFRCDisplayFreeze(bit bEn);
#endif
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
//--------------------------------------------------
// Description  : FRC Initial
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerFRCInitial(void)
{
    WORD usPageSelect = 0x0000;
    BYTE ucPathCount = 1;
    BYTE ucIndex = 0x00;

    // (For Roation using) Merge m1 display frame sync fifo to m2 display frame sync fifo.
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_24_DISP_MAIN_FIFO_LEN_CTRL, ~_BIT1, 0x00);

    // Calculate Register Page Number
    PDATA_DWORD(0) = ScalerFRCRegPageSelection(GET_MDOMAIN_INPUT_DATA_PATH());
    ucPathCount = pData[3];
    usPageSelect = (PDATA_DWORD(0) >> 8);

    for(ucIndex = 0; ucIndex < ucPathCount; ++ucIndex)
    {
#if(_FRC_SUPPORT == _ON)
        // Cosider Read/Write Address
        if(usPageSelect == _REG_MAIN1_PAGE)
        {
            PDATA_DWORD(0) = _FRC_CAP_M1_1ST_BLOCK_STA_ADDR;
            PDATA_DWORD(1) = _FRC_CAP_M1_2ND_BLOCK_STA_ADDR;
            PDATA_DWORD(2) = 0x00000000;
        }
        else if(usPageSelect == _REG_MAIN2_PAGE)
        {
            PDATA_DWORD(0) = _FRC_CAP_M2_1ST_BLOCK_STA_ADDR;
            PDATA_DWORD(1) = _FRC_CAP_M2_2ND_BLOCK_STA_ADDR;
            PDATA_DWORD(2) = 0x00000000;
        }
        else if(usPageSelect == _REG_SUB1_PAGE)
        {
            PDATA_DWORD(0) = _FRC_CAP_S1_1ST_BLOCK_STA_ADDR;
            PDATA_DWORD(1) = _FRC_CAP_S1_2ND_BLOCK_STA_ADDR;
            PDATA_DWORD(2) = 0x00000000;
        }
        else // if(usPageSelect == _REG_SUB2_PAGE)
        {
            PDATA_DWORD(0) = _FRC_CAP_S2_1ST_BLOCK_STA_ADDR;
            PDATA_DWORD(1) = _FRC_CAP_S2_2ND_BLOCK_STA_ADDR;
            PDATA_DWORD(2) = 0x00000000;
        }

        // Set Read/Write Address
        pData[15] = 0x00;
        for(pData[14] = 0; pData[14] < 2; pData[14]++)
        {
            // Set Write/Read Start Address
            ScalerSetBit((P5_00_CAP_M1_MEM_ADDR_MSB + usPageSelect + pData[15]), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
            ScalerSetByte((P5_01_CAP_M1_MEM_ADDR_H + usPageSelect + pData[15]), pData[1]);
            ScalerSetByte((P5_02_CAP_M1_MEM_ADDR_M + usPageSelect + pData[15]), pData[2]);
            ScalerSetByte((P5_03_CAP_M1_MEM_ADDR_L + usPageSelect + pData[15]), pData[3]);
            // Set Write/Read 2nd Address
            ScalerSetBit((P5_04_CAP_M1_BL2_ADDR_MSB + usPageSelect + pData[15]), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[4] & 0x0F));
            ScalerSetByte((P5_05_CAP_M1_BL2_ADDR_H + usPageSelect + pData[15]), pData[5]);
            ScalerSetByte((P5_06_CAP_M1_BL2_ADDR_M + usPageSelect + pData[15]), pData[6]);
            ScalerSetByte((P5_07_CAP_M1_BL2_ADDR_L + usPageSelect + pData[15]), pData[7]);
            // Set Write/Read 3rd Address
            ScalerSetBit((P5_08_CAP_M1_BL3_ADDR_MSB + usPageSelect + pData[15]), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[8] & 0x0F));
            ScalerSetByte((P5_09_CAP_M1_BL3_ADDR_H + usPageSelect + pData[15]), pData[9]);
            ScalerSetByte((P5_0A_CAP_M1_BL3_ADDR_M + usPageSelect + pData[15]), pData[10]);
            ScalerSetByte((P5_0B_CAP_M1_BL3_ADDR_L + usPageSelect + pData[15]), pData[11]);

            pData[15] = 0x80;
        }
#endif // End of #if(_FRC_SUPPORT == _ON)

        // Set Capture Line Step
        ScalerSetBit(P5_19_CAP_M1_LINE_STEP_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte(P5_1A_CAP_M1_LINE_STEP_H + usPageSelect, 0x00);
        ScalerSetByte(P5_1B_CAP_M1_LINE_STEP_M + usPageSelect, 0x00);
        ScalerSetByte(P5_1C_CAP_M1_LINE_STEP_L + usPageSelect, 0x00);

        // Set Display Line Step
        ScalerSetBit(P5_99_DISP_M1_LINE_STEP_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte(P5_9A_DISP_M1_LINE_STEP_H + usPageSelect, 0x00);
        ScalerSetByte(P5_9B_DISP_M1_LINE_STEP_M + usPageSelect, 0x00);
        ScalerSetByte(P5_9C_DISP_M1_LINE_STEP_L + usPageSelect, 0x00);

        // Set Single Buffer Mode
        ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1 + usPageSelect, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

        // Set Line Mode / CAP Start Point to Change Block_sel = 1: Reference to vertical active region
        ScalerSetBit(P5_28_CAP_M1_DDR_CTRL2 + usPageSelect, ~(_BIT6 | _BIT4 | _BIT1 | _BIT0), _BIT6);

        // Set 3 Buffer Disable
        ScalerSetBit(P5_29_CAP_M1_DDR_CTRL3 + usPageSelect, ~(_BIT7 | _BIT2 | _BIT0), 0x00);

        // Disable One Frame FRC
        ScalerSetByte(P5_B1_DISP_M1_ONEF_DHF_H + usPageSelect, 0x00);

        // Set Display :(1) Capture data from I-Domain, (2)E/O mode, (3) Disable 3 Buffer
        ScalerSetBit(P5_AF_DISP_M1_DISP_CTRL3 + usPageSelect, ~(_BIT2 | _BIT0), 0x00);

        // Set double frame buffer disable
        ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

        usPageSelect += _REG_PAGE_OFFSET;
    }

    if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_4P)
    {
        // Set Single Channel Mode
        ScalerSetBit(P5_29_CAP_M1_DDR_CTRL3, ~_BIT1, _BIT1);
        ScalerSetBit(P45_29_CAP_M2_DDR_CTRL3, ~_BIT1, _BIT1);
        ScalerSetBit(P85_29_CAP_S1_DDR_CTRL3, ~_BIT1, _BIT1);
        ScalerSetBit(PC5_29_CAP_S2_DDR_CTRL3, ~_BIT1, _BIT1);

        ScalerSetBit(P5_AF_DISP_M1_DISP_CTRL3, ~_BIT1, _BIT1);
        ScalerSetBit(P45_AF_DISP_M2_DISP_CTRL3, ~_BIT1, _BIT1);
        ScalerSetBit(P85_AF_DISP_S1_DISP_CTRL3, ~_BIT1, _BIT1);
        ScalerSetBit(PC5_AF_DISP_S2_DISP_CTRL3, ~_BIT1, _BIT1);
    }
    else
    {
        // Set Cooperation mode
        ScalerSetBit(P5_29_CAP_M1_DDR_CTRL3, ~_BIT1, 0x00);
        ScalerSetBit(P45_29_CAP_M2_DDR_CTRL3, ~_BIT1, 0x00);
        ScalerSetBit(P85_29_CAP_S1_DDR_CTRL3, ~_BIT1, 0x00);
        ScalerSetBit(PC5_29_CAP_S2_DDR_CTRL3, ~_BIT1, 0x00);

        ScalerSetBit(P5_AF_DISP_M1_DISP_CTRL3, ~_BIT1, 0x00);
        ScalerSetBit(P45_AF_DISP_M2_DISP_CTRL3, ~_BIT1, 0x00);
        ScalerSetBit(P85_AF_DISP_S1_DISP_CTRL3, ~_BIT1, 0x00);
        ScalerSetBit(PC5_AF_DISP_S2_DISP_CTRL3, ~_BIT1, 0x00);
    }

    if(GET_MEMORY_SELECT() == _FRAME_SYNC_LINE_BUFFER)
    {
        ScalerFRCEn(_FRC_ALL_ONOFF, GET_MDOMAIN_INPUT_DATA_PATH(), _ENABLE);
        ScalerFRCSetDDomainSourceSelect(GET_MDOMAIN_INPUT_DATA_PATH(), _DDOMAIN_SRC_FRAM_FRAME_SYNC_MODE);
    }

    // Enable Display double buffer
    ScalerSetBit(P5_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(P45_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(P85_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(PC5_AD_DISP_STATUS, ~_BIT4, _BIT4);

    // Disable M:N frame tracking
    if(GET_MEMORY_SELECT() != _MN_FRAME_SYNC_MEMORY)
    {
        ScalerMemorySetFrameTrackingEnable(_DISABLE);
    }

    // Wait double buffer
    if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0)
    {
        ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, GET_MDOMAIN_INPUT_DATA_PATH());
    }
}
#endif // End of #if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FRC control
// Input Value  : stFIFOSize --> FIFO size
// Output Value : None
//--------------------------------------------------
void ScalerFRCControl(const StructSDRAMDataInfo *pstFIFOSize)
{
    BYTE ucIndex = 0x00;
    WORD usPageSelect = 0x0000;

    // Calculate Register Page Number
    PDATA_DWORD(0) = ScalerFRCRegPageSelection(GET_MDOMAIN_INPUT_DATA_PATH());
    g_ucFRCPathCount = pData[3];
    g_usFRCPageSelect = (PDATA_DWORD(0) >> 8);
    usPageSelect = g_usFRCPageSelect;

    // -----------------------
    // Set FRC IVS2DVSDelay
    // -----------------------
    ScalerFRCAdjustIVS2DVSDelay(pstFIFOSize->usInputVHeight);

    // -----------------------
    // Consider Input Faster Or Slower
    // -----------------------
    ScalerFRCCompareIHFandDHF(pstFIFOSize->usInputVHeight);

    // -----------------------
    // Set Frame tracking function for VFreq < 30Hz
    // -----------------------
    if((GET_MEMORY_SELECT() == _MN_FRAME_SYNC_MEMORY) && (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P))
    {
        ScalerMemoryFrameTracking();
        ScalerMemorySetFrameTrackingEnable(_ENABLE);
    }

    // -----------------------
    // Set Up FRC Capture
    // -----------------------
    ScalerFRCInputCtrl(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);

    // -----------------------
    // Set Up FRC Display
    // -----------------------
    ScalerFRCDisplayCtrl(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);

    // Wait I-domain Stable Before FRC enable
    if(ScalerGetBit(P31_A0_I_DB_CTRL0, _BIT7) == 0)
    {
        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
    }

    // -----------------------
    // Enable FRC
    // -----------------------
    if(GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_M2)
    {
        // Set Capture/Display M2 Enable
        ScalerFRCEn(_FRC_ALL_ONOFF, _INPUT_PATH_M2, _ENABLE);

        // Set Dsiplay M1 Enable
        ScalerFRCEn(_FRC_DISPLAY_ONOFF, _INPUT_PATH_M1, _ENABLE);
    }
    else if(GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S2)
    {
        // Set Capture/Display S2 Enable
        ScalerFRCEn(_FRC_ALL_ONOFF, _INPUT_PATH_S2, _ENABLE);

        // Set Display S1 Enable
        ScalerFRCEn(_FRC_DISPLAY_ONOFF, _INPUT_PATH_S1, _ENABLE);
    }
    else
    {
        // -- 1 -- Enable FRC Capture
        if((ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _FALSE) &&
           ((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PIP) || (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PBP_LR)) &&
           (GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S1_S2))
        {
            ScalerFRCEn(_FRC_CAPTURE_ONOFF, _INPUT_PATH_S1, _ENABLE);
        }
        else
        {
            if((ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _FALSE) &&
               (ScalerGlobalGetIDCode() >= _RL6193_VER_D_ID_CODE))
            {
                ScalerFRCEn(_FRC_CAPTURE_ONOFF, GET_MDOMAIN_INPUT_DATA_PATH() & (_INPUT_PATH_M1 | _INPUT_PATH_S1), _ENABLE);
            }
            else
            {
                ScalerFRCEn(_FRC_CAPTURE_ONOFF, GET_MDOMAIN_INPUT_DATA_PATH(), _ENABLE);
            }
        }

        // -- 2 -- Enable FRC Display
        // Wait _EVENT_DEN_START for FRC Display Enable At The Same Time
        if(((GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_M1_M2) || (GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S1_S2)) &&
           (ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0))
        {
            ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_START, GET_MDOMAIN_INPUT_DATA_PATH());
        }

        if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PBP_TB)
        {
            // Set Dsiplay ALL Enable
            ScalerFRCEn(_FRC_DISPLAY_ONOFF, _INPUT_PATH_ALL, _ENABLE);
        }
        else if(((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PBP_LR) || (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PIP)) &&
                (GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S1_S2))
        {
            ScalerFRCEn(_FRC_DISPLAY_ONOFF, _INPUT_PATH_S1, _ENABLE);
        }
        else
        {
            ScalerFRCEn(_FRC_DISPLAY_ONOFF, GET_MDOMAIN_INPUT_DATA_PATH(), _ENABLE);
        }
    }

    for(ucIndex = 0; ucIndex < g_ucFRCPathCount; ucIndex ++)
    {
        // Enable FRC Display Double buffer
        ScalerSetBit(P5_AD_DISP_STATUS + usPageSelect, ~(_BIT4), _BIT4);
        usPageSelect += _REG_PAGE_OFFSET;
    }

    // Wait _EVENT_IVS For FRC Run In Single Frame Buffer
    if(ScalerGetBit(P31_A0_I_DB_CTRL0, _BIT7) == 0)
    {
        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
    }

    // -----------------------
    // Set Double / Single Frame Buffer
    // -----------------------
    // Wait _EVENT_IEN_START Before Double Frame Buffer Setting
    if(ScalerGetBit(P31_A0_I_DB_CTRL0, _BIT7) == 0)
    {
        ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_START, GET_MDOMAIN_INPUT_DATA_PATH());
    }

    usPageSelect = g_usFRCPageSelect;

    for(ucIndex = 0; ucIndex < g_ucFRCPathCount; ucIndex ++)
    {
        switch(GET_MEMORY_FRAME_BUFFER())
        {
            case _MEMORY_1_FRAME_BUFFER:
            default:

                // Set Single Buffer
                ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1 + usPageSelect, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
                ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
                break;

            case _MEMORY_2_FRAME_BUFFER:

                // Set Double Buffer
                ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1 + usPageSelect, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);
                ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
                break;

            case _MEMORY_3_FRAME_BUFFER:

                // Set Double Buffer
                ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1 + usPageSelect, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);
                ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);

                // Set 3 Buffer
                ScalerSetBit(P5_29_CAP_M1_DDR_CTRL3 + usPageSelect, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                ScalerSetBit(P5_AF_DISP_M1_DISP_CTRL3 + usPageSelect, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                break;
        }

        // Enable FRC Display Double buffer
        ScalerSetBit(P5_AD_DISP_STATUS + usPageSelect, ~(_BIT4), _BIT4);
        usPageSelect += _REG_PAGE_OFFSET;
    }

    if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0)
    {
        // Wait double buffer
        ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, GET_MDOMAIN_INPUT_DATA_PATH());
    }

#if(_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
    // Set Frame tracking function for VFreq < 30Hz
    if((GET_MEMORY_SELECT() == _MN_FRAME_SYNC_MEMORY) && (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P))
    {
        if((GET_MEMORY_DVF_SELECT() == _2_5_IVF) || (GET_MEMORY_DVF_SELECT() == _3_IVF))
        {
            ScalerMemorySetDisplayAutoBlkToggleEnable(_ENABLE);
        }
    }
#endif

    DebugMessageFRC("FRC-H", pstFIFOSize->usInputHWidth);
    DebugMessageFRC("FRC-V", pstFIFOSize->usInputVHeight);
}

//--------------------------------------------------
// Description  : IN1 FIFO Setting for FRC Mode
// Input Value  : ucSettingPath --> Path
//                ucHorSize --> Horizontal size
//                ucVerSize --> Vertical Size
// Output Value : None
//--------------------------------------------------
void ScalerFRCInputCtrl(WORD usHorSize, WORD usVerSize)
{
    StructMemoryLineBlockStep stStep;
    DWORD ulTemp = 0;
    WORD usPageSelect = 0x0000;
    BYTE ucPathCount = 1;
    BYTE ucIndex = 0x00;
    memset(&stStep, 0, sizeof(StructMemoryLineBlockStep));

    if((ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE) &&
       ((GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_M1_M2) || (GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S1_S2)))
    {
        // E/O Mode
        usVerSize = usVerSize >> 1;

        // Let E/O setting complete in VSync period
        if(ScalerGetBit(P31_A0_I_DB_CTRL0, _BIT7) == 0)
        {
            ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_START, (GET_MDOMAIN_INPUT_DATA_PATH() & (_INPUT_PATH_M2 | _INPUT_PATH_S2)));
        }
    }

    // Calculate Register Page Number
    ucPathCount = g_ucFRCPathCount;
    if((ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _FALSE) &&
       (ScalerGlobalGetIDCode() >= _RL6193_VER_D_ID_CODE))
    {
        ucPathCount = 1;
    }
    usPageSelect = g_usFRCPageSelect;

    // Calculate Line Mode Size
    // One Line total pixel for Memory (FRC unit : 64 bits)
    ulTemp = ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() % 64) ?
             (((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64) + 1) :
             ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64);

    // Calculate Line Step and Block Step
    ScalerMemoryCalculateLineStepAndBlockStep(ulTemp, usVerSize, &stStep);

    // Calculate Number of One Line and Remain of One Line
    ulTemp = ScalerMemoryCalculateNumberAndRemain(ulTemp, _FRC_ACCESS_WRITE_LENGTH, 1);

    for(ucIndex = 0; ucIndex < ucPathCount; ++ucIndex)
    {
        // Set Line Mode
        ScalerSetBit(P5_28_CAP_M1_DDR_CTRL2 + usPageSelect, ~(_BIT4), 0x00);

        // Set Block Step
        ScalerSetBit(P5_15_CAP_M1_BLOCK_STEP_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((stStep.ulBlockStep >> 24) & 0x0F));
        ScalerSetByte(P5_16_CAP_M1_BLOCK_STEP_H + usPageSelect, ((stStep.ulBlockStep >> 16) & 0xFF));
        ScalerSetByte(P5_17_CAP_M1_BLOCK_STEP_M + usPageSelect, ((stStep.ulBlockStep >> 8) & 0xFF));
        ScalerSetByte(P5_18_CAP_M1_BLOCK_STEP_L + usPageSelect, (stStep.ulBlockStep & 0xFF));

        // Set Water level
        ScalerSetBit(P5_1D_CAP_M1_WATER_LEVEL_H + usPageSelect, ~(_BIT0), ((((WORD)_FRC_ACCESS_WRITE_LENGTH / 2) >> 8) & 0x01));
        ScalerSetByte(P5_1E_CAP_M1_WATER_LEVEL_L + usPageSelect, (((WORD)_FRC_ACCESS_WRITE_LENGTH / 2) & 0xFF));

        // Set Pixel Nmber
        ScalerSetByte(P5_1F_CAP_M1_PIXEL_NUM_H + usPageSelect, HIBYTE(usHorSize));
        ScalerSetByte(P5_20_CAP_M1_PIXEL_NUM_L + usPageSelect, LOBYTE(usHorSize));

        // Set Line Number
        ScalerSetByte(P5_21_CAP_M1_LINE_NUM_H + usPageSelect, HIBYTE(usVerSize));
        ScalerSetByte(P5_22_CAP_M1_LINE_NUM_L + usPageSelect, LOBYTE(usVerSize));

        // Set Number
        ScalerSetByte(P5_23_CAP_M1_WR_NUM_H + usPageSelect, ((ulTemp >> 8) & 0xFF));
        ScalerSetByte(P5_24_CAP_M1_WR_NUM_L + usPageSelect, (ulTemp & 0xFF));

        // Set Length, Remain
        ScalerSetByte(P5_25_CAP_M1_WR_LEN + usPageSelect, _FRC_ACCESS_WRITE_LENGTH);
        ScalerSetByte(P5_26_CAP_M1_WR_REMAIN + usPageSelect, ((ulTemp >> 16) & 0xFF));

#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
        if((ScalerRotationCheckStatus() == _TRUE) && (GET_ROT_TYPE() == _ROT_VER_MIRROR))
        {
            // Set M1/M2 Line Step
            PDATA_DWORD(0) = (((~stStep.ulLineStep) + 1) & 0xFFFFFFF);
            ScalerSetBit(P5_19_CAP_M1_LINE_STEP_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
            ScalerSetByte(P5_1A_CAP_M1_LINE_STEP_H + usPageSelect, pData[1]);
            ScalerSetByte(P5_1B_CAP_M1_LINE_STEP_M + usPageSelect, pData[2]);
            ScalerSetByte(P5_1C_CAP_M1_LINE_STEP_L + usPageSelect, pData[3]);

            // Set M1 Start Address
            PDATA_DWORD(0) = (stStep.ulBlockStep * (1 + ((usPageSelect >> 14) * 3)));
            ScalerSetBit(P5_00_CAP_M1_MEM_ADDR_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
            ScalerSetByte(P5_01_CAP_M1_MEM_ADDR_H + usPageSelect, pData[1]);
            ScalerSetByte(P5_02_CAP_M1_MEM_ADDR_M + usPageSelect, pData[2]);
            ScalerSetByte(P5_03_CAP_M1_MEM_ADDR_L + usPageSelect, pData[3]);

            // Set M1 2nd Address
            PDATA_DWORD(0) = (stStep.ulBlockStep * (2 + ((usPageSelect >> 14) * 3)));
            ScalerSetBit(P5_04_CAP_M1_BL2_ADDR_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
            ScalerSetByte(P5_05_CAP_M1_BL2_ADDR_H + usPageSelect, pData[1]);
            ScalerSetByte(P5_06_CAP_M1_BL2_ADDR_M + usPageSelect, pData[2]);
            ScalerSetByte(P5_07_CAP_M1_BL2_ADDR_L + usPageSelect, pData[3]);

            // Set M1 3rd Address
            PDATA_DWORD(0) = (stStep.ulBlockStep * (3 + ((usPageSelect >> 14) * 3)));
            ScalerSetBit(P5_08_CAP_M1_BL3_ADDR_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
            ScalerSetByte(P5_09_CAP_M1_BL3_ADDR_H + usPageSelect, pData[1]);
            ScalerSetByte(P5_0A_CAP_M1_BL3_ADDR_M + usPageSelect, pData[2]);
            ScalerSetByte(P5_0B_CAP_M1_BL3_ADDR_L + usPageSelect, pData[3]);

            // (_BIT6 | _BIT5 | _BIT4 | _BIT3): Set Single Buffer
            // _BIT1: Use IVS as synchronous reset
            ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1 + usPageSelect, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1), _BIT1);
        }
        else
#endif
        {
#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
            if((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PBP_TB) &&
               (ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _FALSE) &&
               (usPageSelect == _REG_SUB2_PAGE) &&
               (ScalerDDomainGetBackgroundStatus(GET_MDOMAIN_OUTPUT_DATA_PATH()) == _TRUE))
            {
                PDATA_DWORD(0) = _FRC_ADDR_PBP_TB;

                // Set Write/Read Start Address
                ScalerSetBit((P5_00_CAP_M1_MEM_ADDR_MSB + usPageSelect), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
                ScalerSetByte((P5_01_CAP_M1_MEM_ADDR_H + usPageSelect), pData[1]);
                ScalerSetByte((P5_02_CAP_M1_MEM_ADDR_M + usPageSelect), pData[2]);
                ScalerSetByte((P5_03_CAP_M1_MEM_ADDR_L + usPageSelect), pData[3]);

                // Set Write/Read 2nd Address
                ScalerSetBit((P5_04_CAP_M1_BL2_ADDR_MSB + usPageSelect), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
                ScalerSetByte((P5_05_CAP_M1_BL2_ADDR_H + usPageSelect), pData[1]);
                ScalerSetByte((P5_06_CAP_M1_BL2_ADDR_M + usPageSelect), pData[2]);
                ScalerSetByte((P5_07_CAP_M1_BL2_ADDR_L + usPageSelect), pData[3]);
            }
#endif

            if((GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S1_S2) &&
               ((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PIP) || (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PBP_LR)))
            {
                if(usPageSelect == _REG_SUB2_PAGE)
                {
                    if(ScalerDDomainGetBackgroundStatus(GET_MDOMAIN_OUTPUT_DATA_PATH()) == _FALSE)
                    {
                        PDATA_DWORD(0) = ((DWORD)ScalerGetBit(P5_00_CAP_M1_MEM_ADDR_MSB + usPageSelect, 0x0F) << 24) |
                                         ((DWORD)ScalerGetByte(P5_01_CAP_M1_MEM_ADDR_H + usPageSelect) << 16) |
                                         ((DWORD)ScalerGetByte(P5_02_CAP_M1_MEM_ADDR_M + usPageSelect) << 8) |
                                         ((DWORD)ScalerGetByte(P5_03_CAP_M1_MEM_ADDR_L + usPageSelect));
                        PDATA_DWORD(1) = ((DWORD)ScalerGetBit(P5_04_CAP_M1_BL2_ADDR_MSB + usPageSelect, 0x0F) << 24) |
                                         ((DWORD)ScalerGetByte(P5_05_CAP_M1_BL2_ADDR_H + usPageSelect) << 16) |
                                         ((DWORD)ScalerGetByte(P5_06_CAP_M1_BL2_ADDR_M + usPageSelect) << 8) |
                                         ((DWORD)ScalerGetByte(P5_07_CAP_M1_BL2_ADDR_L + usPageSelect));

                        if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
                        {
                            // Get pervious line step
                            PDATA_DWORD(2) = ((DWORD)ScalerGetBit(P5_19_CAP_M1_LINE_STEP_MSB + usPageSelect, 0x0F) << 24) |
                                             ((DWORD)ScalerGetByte(P5_1A_CAP_M1_LINE_STEP_H + usPageSelect) << 16) |
                                             ((DWORD)ScalerGetByte(P5_1B_CAP_M1_LINE_STEP_M + usPageSelect) << 8) |
                                             ((DWORD)ScalerGetByte(P5_1C_CAP_M1_LINE_STEP_L + usPageSelect));
                            PDATA_DWORD(0) = (PDATA_DWORD(0) - (PDATA_DWORD(2) >> 1) + stStep.ulLineStep);
                            PDATA_DWORD(1) = (PDATA_DWORD(1) - (PDATA_DWORD(2) >> 1) + stStep.ulLineStep);
                        }
                    }
                    else
                    {
                        PDATA_DWORD(0) = _FRC_CAP_S1_1ST_BLOCK_STA_ADDR;
                        PDATA_DWORD(1) = _FRC_CAP_S1_2ND_BLOCK_STA_ADDR;

                        if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
                        {
                            PDATA_DWORD(0) += (stStep.ulLineStep);
                            PDATA_DWORD(1) += (stStep.ulLineStep);
                        }
                    }

                    // Set Write/Read Start Address
                    ScalerSetBit((P5_00_CAP_M1_MEM_ADDR_MSB + usPageSelect), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
                    ScalerSetByte((P5_01_CAP_M1_MEM_ADDR_H + usPageSelect), pData[1]);
                    ScalerSetByte((P5_02_CAP_M1_MEM_ADDR_M + usPageSelect), pData[2]);
                    ScalerSetByte((P5_03_CAP_M1_MEM_ADDR_L + usPageSelect), pData[3]);
                    // Set Write/Read 2nd Address
                    ScalerSetBit((P5_04_CAP_M1_BL2_ADDR_MSB + usPageSelect), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[4] & 0x0F));
                    ScalerSetByte((P5_05_CAP_M1_BL2_ADDR_H + usPageSelect), pData[5]);
                    ScalerSetByte((P5_06_CAP_M1_BL2_ADDR_M + usPageSelect), pData[6]);
                    ScalerSetByte((P5_07_CAP_M1_BL2_ADDR_L + usPageSelect), pData[7]);
                }

                if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _FALSE)
                {
                    // Set Line Step
                    ScalerSetBit(P5_19_CAP_M1_LINE_STEP_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((stStep.ulLineStep >> 24) & 0x0F));
                    ScalerSetByte(P5_1A_CAP_M1_LINE_STEP_H + usPageSelect, ((stStep.ulLineStep >> 16) & 0xFF));
                    ScalerSetByte(P5_1B_CAP_M1_LINE_STEP_M + usPageSelect, ((stStep.ulLineStep >> 8) & 0xFF));
                    ScalerSetByte(P5_1C_CAP_M1_LINE_STEP_L + usPageSelect, (stStep.ulLineStep & 0xFF));
                }
                else
                {
                    // Set Line Step
                    ScalerSetBit(P5_19_CAP_M1_LINE_STEP_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (((stStep.ulLineStep * 2) >> 24) & 0x0F));
                    ScalerSetByte(P5_1A_CAP_M1_LINE_STEP_H + usPageSelect, (((stStep.ulLineStep * 2) >> 16) & 0xFF));
                    ScalerSetByte(P5_1B_CAP_M1_LINE_STEP_M + usPageSelect, (((stStep.ulLineStep * 2) >> 8) & 0xFF));
                    ScalerSetByte(P5_1C_CAP_M1_LINE_STEP_L + usPageSelect, ((stStep.ulLineStep * 2) & 0xFF));
                }
            }
            else
            {
                // Set Line Step
                ScalerSetBit(P5_19_CAP_M1_LINE_STEP_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((stStep.ulLineStep >> 24) & 0x0F));
                ScalerSetByte(P5_1A_CAP_M1_LINE_STEP_H + usPageSelect, ((stStep.ulLineStep >> 16) & 0xFF));
                ScalerSetByte(P5_1B_CAP_M1_LINE_STEP_M + usPageSelect, ((stStep.ulLineStep >> 8) & 0xFF));
                ScalerSetByte(P5_1C_CAP_M1_LINE_STEP_L + usPageSelect, (stStep.ulLineStep & 0xFF));
            }

            if((ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _FALSE) &&
               (GET_MDOMAIN_DISPLAY_MODE() != _DISPLAY_MODE_4P) &&
               (ScalerDDomainGetBackgroundStatus(GET_MDOMAIN_OUTPUT_DATA_PATH()) == _TRUE))
            {
                // Check Data Size < (_FRC_CAP_M1_2ND_BLOCK_STA_ADDR - _FRC_CAP_M1_1ST_BLOCK_STA_ADDR)
                PDATA_DWORD(0) = (((DWORD)usHorSize * usVerSize * GET_MEMORY_DATA_BIT()) / _MEMORY_BIT_NUM / _MEMORY_BANK / _MEMORY_COL_PER_BANK);
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
                PDATA_DWORD(0) = (PDATA_DWORD(0) << 12);
#else
                PDATA_DWORD(0) = (PDATA_DWORD(0) << 11);
#endif

                if(PDATA_DWORD(0) > (_FRC_CAP_M1_2ND_BLOCK_STA_ADDR - _FRC_CAP_M1_1ST_BLOCK_STA_ADDR))
                {
                    if(usPageSelect == _REG_MAIN1_PAGE)
                    {
                        PDATA_DWORD(0) = _FRC_CAP_M1_1ST_BLOCK_STA_ADDR;
                        PDATA_DWORD(1) = _FRC_CAP_M2_1ST_BLOCK_STA_ADDR;
                    }
                    else // if(usPageSelect == _REG_MAIN2_PAGE)
                    {
                        PDATA_DWORD(0) = _FRC_ADDR_PBP_TB;
                        PDATA_DWORD(1) = _FRC_ADDR_PBP_TB;
                    }

                    // Set Write/Read Start Address
                    ScalerSetBit((P5_00_CAP_M1_MEM_ADDR_MSB + usPageSelect), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
                    ScalerSetByte((P5_01_CAP_M1_MEM_ADDR_H + usPageSelect), pData[1]);
                    ScalerSetByte((P5_02_CAP_M1_MEM_ADDR_M + usPageSelect), pData[2]);
                    ScalerSetByte((P5_03_CAP_M1_MEM_ADDR_L + usPageSelect), pData[3]);

                    // Set Write/Read 2nd Address
                    ScalerSetBit((P5_04_CAP_M1_BL2_ADDR_MSB + usPageSelect), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[4] & 0x0F));
                    ScalerSetByte((P5_05_CAP_M1_BL2_ADDR_H + usPageSelect), pData[5]);
                    ScalerSetByte((P5_06_CAP_M1_BL2_ADDR_M + usPageSelect), pData[6]);
                    ScalerSetByte((P5_07_CAP_M1_BL2_ADDR_L + usPageSelect), pData[7]);
                }
            }

#if(_FALSE)
            // Set Down limit = default value 0x0000000
            ScalerSetBit(P5_0C_CAP_M1_BOUNDARY_ADDR1_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte(P5_0D_CAP_M1_BOUNDARY_ADDR1_H + usPageSelect, 0x00);
            ScalerSetByte(P5_0E_CAP_M1_BOUNDARY_ADDR1_M + usPageSelect, 0x00);
            ScalerSetByte(P5_0F_CAP_M1_BOUNDARY_ADDR1_L + usPageSelect, 0x00);

            // Set Up limit = default value = 0xFFFFFFF
            ScalerSetBit(P5_10_CAP_M1_BOUNDARY_ADDR2_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
            ScalerSetByte(P5_11_CAP_M1_BOUNDARY_ADDR2_H + usPageSelect, 0xFF);
            ScalerSetByte(P5_12_CAP_M1_BOUNDARY_ADDR2_M + usPageSelect, 0xFF);
            ScalerSetByte(P5_13_CAP_M1_BOUNDARY_ADDR2_L + usPageSelect, 0xFF);
#endif

            // Use IVS as synchronous reset
            ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1 + usPageSelect, ~(_BIT1), _BIT1);
        }

        usPageSelect += _REG_PAGE_OFFSET;
    }
}

//--------------------------------------------------
// Description  : MAIN FIFO Setting for FRC Mode
// Input Value  : usHorSize --> Horizontal size
//                usVerSize --> Vertical Size
// Output Value : None
//--------------------------------------------------
void ScalerFRCDisplayCtrl(WORD usHorSize, WORD usVerSize)
{
    StructMemoryLineBlockStep stStep;
    DWORD ulTemp = 0x00000000;
    WORD usPageSelect = 0x0000;
    BYTE ucPathCount = 0;
    WORD usPreReadLine = 0;
    BYTE ucIndex = 0x00;
    DWORD ulFmcvtStartAddr = 0x00000000;
    memset(&stStep, 0, sizeof(StructMemoryLineBlockStep));

    usPreReadLine = ScalerFRCCalculatePreReadLine(usVerSize);

    // Set Register Page Number
    ucPathCount = g_ucFRCPathCount;
    usPageSelect = g_usFRCPageSelect;

    if(GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_M1_M2)
    {
        // E/O Mode
        usVerSize = usVerSize >> 1;

        // Let E/O setting complete in VSync period
        if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0)
        {
            ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_START, GET_MDOMAIN_INPUT_DATA_PATH());
        }
    }
    else if(GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S1_S2)
    {
        if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PBP_TB)
        {
            usVerSize = usVerSize >> 1;
        }

        // Let E/O setting complete in VSync period
        if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0)
        {
            ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_START, GET_MDOMAIN_INPUT_DATA_PATH());
        }
    }

    // Calculate Line Mode Size
    // One Line total pixel for Memory (FRC unit : 64 bits)
    ulTemp = ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() % 64) ?
             (((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64) + 1) :
             ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64);

    // Calculate Line Step And Block Step
    if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
    {
        ScalerMemoryCalculateLineStepAndBlockStep(ulTemp, usVerSize, &stStep);
        ulFmcvtStartAddr = stStep.ulLineStep;
    }
    else
    {
        ScalerMemoryCalculateLineStepAndBlockStep(ulTemp, (usVerSize * 2), &stStep);
        ulFmcvtStartAddr = stStep.ulLineStep;

        if((GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_M1_M2) ||
           ((GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S1_S2) && (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PBP_TB)))
        {
            stStep.ulLineStep = stStep.ulLineStep << 1;
        }
    }

    // Calculate Number of One Line and Remain of One Line
    ulTemp = ScalerMemoryCalculateNumberAndRemain(ulTemp, _FRC_ACCESS_READ_LENGTH, 0);

    for(ucIndex = 0; ucIndex < ucPathCount; ++ucIndex)
    {
        // Set Block Step
        ScalerSetBit(P5_95_DISP_M1_BLOCK_STEP_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((stStep.ulBlockStep >> 24) & 0x0F));
        ScalerSetByte(P5_96_DISP_M1_BLOCK_STEP_H + usPageSelect, ((stStep.ulBlockStep >> 16) & 0xFF));
        ScalerSetByte(P5_97_DISP_M1_BLOCK_STEP_M + usPageSelect, ((stStep.ulBlockStep >> 8) & 0xFF));
        ScalerSetByte(P5_98_DISP_M1_BLOCK_STEP_L + usPageSelect, (stStep.ulBlockStep & 0xFF));

        // Set Line Step
        ScalerSetBit(P5_99_DISP_M1_LINE_STEP_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((stStep.ulLineStep >> 24) & 0x0F));
        ScalerSetByte(P5_9A_DISP_M1_LINE_STEP_H + usPageSelect, ((stStep.ulLineStep >> 16) & 0xFF));
        ScalerSetByte(P5_9B_DISP_M1_LINE_STEP_M + usPageSelect, ((stStep.ulLineStep >> 8) & 0xFF));
        ScalerSetByte(P5_9C_DISP_M1_LINE_STEP_L + usPageSelect, (stStep.ulLineStep & 0xFF));

        // Set Water Level
        // Display Water Level < FIFO Depth (512) - Length / 2
        ScalerSetBit(P5_A0_DISP_M1_WTLVL_H + usPageSelect, ~(_BIT0), ((510 - _FRC_ACCESS_READ_LENGTH / 2) >> 8) & 0x01);
        ScalerSetByte(P5_A1_DISP_M1_WTLVL_L + usPageSelect, (BYTE)((510 - _FRC_ACCESS_READ_LENGTH / 2) & 0xFF));

        // Set Pixel Number
        ScalerSetByte(P5_A2_DISP_M1_PXL_NUM_H + usPageSelect, HIBYTE(usHorSize));
        ScalerSetByte(P5_A3_DISP_M1_PXL_NUM_L + usPageSelect, LOBYTE(usHorSize));

        // Set Line number
        ScalerSetByte(P5_A4_DISP_M1_LINE_NUM_H + usPageSelect, HIBYTE(usVerSize));
        ScalerSetByte(P5_A5_DISP_M1_LINE_NUM_L + usPageSelect, LOBYTE(usVerSize));

        // Set Pre-read
        ScalerSetByte(P5_A6_DISP_M1_PRRD_VST_H + usPageSelect, HIBYTE(usPreReadLine));
        ScalerSetByte(P5_A7_DISP_M1_PRRD_VST_L + usPageSelect, LOBYTE(usPreReadLine));

        // Set Number
        ScalerSetByte(P5_A8_DISP_M1_READ_NUM_H + usPageSelect, ((ulTemp >> 8) & 0xFF));
        ScalerSetByte(P5_A9_DISP_M1_READ_NUM_L + usPageSelect, (ulTemp & 0xFF));

        // Set Length, Remain
        ScalerSetByte(P5_AA_DISP_M1_READ_LEN + usPageSelect, _FRC_ACCESS_READ_LENGTH);
        ScalerSetByte(P5_AB_DISP_M1_READ_REMAIN + usPageSelect, ((ulTemp >> 16) & 0xFF));

#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
        if((ScalerRotationCheckStatus() == _TRUE) && (GET_ROT_TYPE() == _ROT_VER_MIRROR))
        {
            // M1 Disp = M2 start - line num + 1
            // M2 Disp = M1 start - line num + 1

            PDATA_DWORD(1) = (stStep.ulLineStep * (usVerSize - 1));

            if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
            {
                // Set M1/M2 Read Start Address
                PDATA_DWORD(0) = (stStep.ulBlockStep * (4 - ((usPageSelect >> 14) * 3)) - PDATA_DWORD(1));
            }
            else
            {
                // Set M1/M2 Read Start Address
                PDATA_DWORD(0) = (stStep.ulBlockStep - PDATA_DWORD(1));

                if(usPageSelect == _REG_MAIN1_PAGE)
                {
                    PDATA_DWORD(0) -= ulFmcvtStartAddr;
                }
            }

            ScalerSetBit(P5_80_DISP_M1_READ_ADDR_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
            ScalerSetByte(P5_81_DISP_M1_READ_ADDR_H + usPageSelect, pData[1]);
            ScalerSetByte(P5_82_DISP_M1_READ_ADDR_M + usPageSelect, pData[2]);
            ScalerSetByte(P5_83_DISP_M1_READ_ADDR_L + usPageSelect, pData[3]);

            // Set M1/M2 2nd address
            PDATA_DWORD(0) += stStep.ulBlockStep;
            ScalerSetBit(P5_84_DISP_M1_BL2_ADDR_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
            ScalerSetByte(P5_85_DISP_M1_BL2_ADDR_H + usPageSelect, pData[1]);
            ScalerSetByte(P5_86_DISP_M1_BL2_ADDR_M + usPageSelect, pData[2]);
            ScalerSetByte(P5_87_DISP_M1_BL2_ADDR_L + usPageSelect, pData[3]);

            // Set M1/M2 3rd address
            PDATA_DWORD(0) += stStep.ulBlockStep;
            ScalerSetBit(P5_88_DISP_M1_BL3_ADDR_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
            ScalerSetByte(P5_89_DISP_M1_BL3_ADDR_H + usPageSelect, pData[1]);
            ScalerSetByte(P5_8A_DISP_M1_BL3_ADDR_M + usPageSelect, pData[2]);
            ScalerSetByte(P5_8B_DISP_M1_BL3_ADDR_L + usPageSelect, pData[3]);

            // _BIT7: Set Line Mode
            // (_BIT6 | _BIT5 | _BIT4): Set Single Buffer
            ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
        }
        else
#endif
        {
            if((ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _FALSE) &&
               ((GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_M1_M2) || (GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S1_S2)) &&
               (ScalerDDomainGetBackgroundStatus(GET_MDOMAIN_OUTPUT_DATA_PATH()) == _TRUE))
            {
                // Check Data Size < (_FRC_CAP_M1_2ND_BLOCK_STA_ADDR - _FRC_CAP_M1_1ST_BLOCK_STA_ADDR)
                PDATA_DWORD(0) = (((DWORD)usHorSize * (usVerSize << 1) * GET_MEMORY_DATA_BIT()) / _MEMORY_BIT_NUM / _MEMORY_BANK / _MEMORY_COL_PER_BANK);
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
                PDATA_DWORD(0) = (PDATA_DWORD(0) << 12);
#else
                PDATA_DWORD(0) = (PDATA_DWORD(0) << 11);
#endif

                if(PDATA_DWORD(0) > (_FRC_CAP_M1_2ND_BLOCK_STA_ADDR - _FRC_CAP_M1_1ST_BLOCK_STA_ADDR))
                {
                    if(usPageSelect == _REG_MAIN1_PAGE)
                    {
                        PDATA_DWORD(0) = _FRC_CAP_M1_1ST_BLOCK_STA_ADDR;
                        PDATA_DWORD(1) = _FRC_CAP_M2_1ST_BLOCK_STA_ADDR;

                        // Set Write/Read Start Address
                        ScalerSetBit((P5_80_DISP_M1_READ_ADDR_MSB), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
                        ScalerSetByte((P5_81_DISP_M1_READ_ADDR_H), pData[1]);
                        ScalerSetByte((P5_82_DISP_M1_READ_ADDR_M), pData[2]);
                        ScalerSetByte((P5_83_DISP_M1_READ_ADDR_L), pData[3]);

                        // Set Write/Read 2nd Address
                        ScalerSetBit((P5_84_DISP_M1_BL2_ADDR_MSB), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[4] & 0x0F));
                        ScalerSetByte((P5_85_DISP_M1_BL2_ADDR_H), pData[5]);
                        ScalerSetByte((P5_86_DISP_M1_BL2_ADDR_M), pData[6]);
                        ScalerSetByte((P5_87_DISP_M1_BL2_ADDR_L), pData[7]);
                    }
                    else if(usPageSelect == _REG_MAIN2_PAGE)
                    {
                        PDATA_DWORD(0) = _FRC_CAP_M1_1ST_BLOCK_STA_ADDR + ulFmcvtStartAddr;
                        PDATA_DWORD(1) = _FRC_CAP_M2_1ST_BLOCK_STA_ADDR + ulFmcvtStartAddr;

                        // Set Write/Read Start Address
                        ScalerSetBit(P45_80_DISP_M2_READ_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
                        ScalerSetByte(P45_81_DISP_M2_READ_ADDR_H, pData[1]);
                        ScalerSetByte(P45_82_DISP_M2_READ_ADDR_M, pData[2]);
                        ScalerSetByte(P45_83_DISP_M2_READ_ADDR_L, pData[3]);
                        // Set Write/Read 2nd Address
                        ScalerSetBit((P45_84_DISP_M2_BL2_ADDR_MSB), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[4] & 0x0F));
                        ScalerSetByte(P45_85_DISP_M2_BL2_ADDR_H, pData[5]);
                        ScalerSetByte(P45_86_DISP_M2_BL2_ADDR_M, pData[6]);
                        ScalerSetByte(P45_87_DISP_M2_BL2_ADDR_L, pData[7]);
                    }
                }
                else
                {
                    if(usPageSelect == _REG_MAIN2_PAGE)
                    {
                        PDATA_DWORD(0) = _FRC_CAP_M1_1ST_BLOCK_STA_ADDR + ulFmcvtStartAddr;
                        PDATA_DWORD(1) = _FRC_CAP_M1_2ND_BLOCK_STA_ADDR + ulFmcvtStartAddr;

                        // Set Write/Read Start Address
                        ScalerSetBit(P45_80_DISP_M2_READ_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
                        ScalerSetByte(P45_81_DISP_M2_READ_ADDR_H, pData[1]);
                        ScalerSetByte(P45_82_DISP_M2_READ_ADDR_M, pData[2]);
                        ScalerSetByte(P45_83_DISP_M2_READ_ADDR_L, pData[3]);
                        // Set Write/Read 2nd Address
                        ScalerSetBit((P45_84_DISP_M2_BL2_ADDR_MSB), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[4] & 0x0F));
                        ScalerSetByte(P45_85_DISP_M2_BL2_ADDR_H, pData[5]);
                        ScalerSetByte(P45_86_DISP_M2_BL2_ADDR_M, pData[6]);
                        ScalerSetByte(P45_87_DISP_M2_BL2_ADDR_L, pData[7]);
                    }
                    else if(usPageSelect == _REG_SUB2_PAGE)
                    {
                        PDATA_DWORD(0) = _FRC_CAP_S1_1ST_BLOCK_STA_ADDR + ulFmcvtStartAddr;
                        PDATA_DWORD(1) = _FRC_CAP_S1_2ND_BLOCK_STA_ADDR + ulFmcvtStartAddr;

                        // Set Write/Read Start Address
                        ScalerSetBit(PC5_80_DISP_S2_READ_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
                        ScalerSetByte(PC5_81_DISP_S2_READ_ADDR_H, pData[1]);
                        ScalerSetByte(PC5_82_DISP_S2_READ_ADDR_M, pData[2]);
                        ScalerSetByte(PC5_83_DISP_S2_READ_ADDR_L, pData[3]);
                        // Set Write/Read 2nd Address
                        ScalerSetBit((PC5_84_DISP_S2_BL2_ADDR_MSB), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[4] & 0x0F));
                        ScalerSetByte(PC5_85_DISP_S2_BL2_ADDR_H, pData[5]);
                        ScalerSetByte(PC5_86_DISP_S2_BL2_ADDR_M, pData[6]);
                        ScalerSetByte(PC5_87_DISP_S2_BL2_ADDR_L, pData[7]);
                    }
                }
            }
#if(_FALSE)
            // Set Down limit = default value 0x0000000
            ScalerSetBit(P5_8C_DISP_M1_BOUNDARY_ADDR1_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte(P5_8D_DISP_M1_BOUNDARY_ADDR1_H + usPageSelect, 0x00);
            ScalerSetByte(P5_8E_DISP_M1_BOUNDARY_ADDR1_M + usPageSelect, 0x00);
            ScalerSetByte(P5_8F_DISP_M1_BOUNDARY_ADDR1_L + usPageSelect, 0x00);

            // Set Up limit = default value = 0xFFFFFFF
            ScalerSetBit(P5_90_DISP_M1_BOUNDARY_ADDR2_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
            ScalerSetByte(P5_91_DISP_M1_BOUNDARY_ADDR2_H + usPageSelect, 0xFF);
            ScalerSetByte(P5_92_DISP_M1_BOUNDARY_ADDR2_M + usPageSelect, 0xFF);
            ScalerSetByte(P5_93_DISP_M1_BOUNDARY_ADDR2_L + usPageSelect, 0xFF);
#endif
        }

        // Set Line mode
        ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~_BIT7, 0x00);

        usPageSelect += _REG_PAGE_OFFSET;
    }

    // Use Information From FRC Capture
    if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PBP_TB)
    {
        // Set All Path Using Information From FRC Capture
        ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~(_BIT2 | _BIT1), 0x00);
        ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~(_BIT2 | _BIT1), 0x00);
        ScalerSetBit(P85_AC_DISP_S1_DISP_CTRL1, ~(_BIT2 | _BIT1), 0x00);
        ScalerSetBit(PC5_AC_DISP_S2_DISP_CTRL1, ~(_BIT2 | _BIT1), 0x00);
    }
    else
    {
        switch(GET_MDOMAIN_INPUT_DATA_PATH())
        {
            case _INPUT_PATH_M2:
                // Set M1/M2 Using Information From FRC Capture
                ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~(_BIT2 | _BIT1), 0x00);
                ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~(_BIT2 | _BIT1), 0x00);
                break;

            case _INPUT_PATH_S2:
                // Set S1/S2 Using Information From FRC Capture
                ScalerSetBit(P85_AC_DISP_S1_DISP_CTRL1, ~(_BIT2 | _BIT1), 0x00);
                ScalerSetBit(PC5_AC_DISP_S2_DISP_CTRL1, ~(_BIT2 | _BIT1), 0x00);
                break;

            default:
                // Set Using Information From FRC Capture
                ScalerFRCSetDDomainSourceSelect(GET_MDOMAIN_INPUT_DATA_PATH(), _DDOMAIN_SRC_FRAM_FRC);
                break;
        }
    }


    // Wait double buffer apply
    if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0)
    {
        // Set Register Page Number
        usPageSelect = g_usFRCPageSelect;

        // Enable FRC Display double buffer
        for(ucIndex = 0; ucIndex < ucPathCount; ++ucIndex)
        {
            ScalerSetBit(P5_AD_DISP_STATUS + usPageSelect, ~_BIT4, _BIT4);
            usPageSelect += _REG_PAGE_OFFSET;
        }

        ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, GET_MDOMAIN_INPUT_DATA_PATH());
    }
}

#if(_FREEZE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FRC freeze mode
// Input Value  : ON --> Freeze
// Output Value : None
//--------------------------------------------------
void ScalerFRCDisplayFreeze(bit bEn)
{
    ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_STOP, _INPUT_PATH_M1_M2);

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    // Get Rotation status
    if(ScalerRotationCheckStatus() == _TRUE)
    {
        if(bEn == _ON)
        {
            ScalerSetBit(P20_27_CAP_M1_DDR_CTRL1, ~_BIT2, _BIT2);
            ScalerSetBit(P60_27_CAP_M2_DDR_CTRL1, ~_BIT2, _BIT2);
        }
        else
        {
#if(_ROTATION_FREEZE_FORCE_TO_BACKGROUND == _ON)
            // Check background status
            if(ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT5) == 0x00)
            {
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, _BIT5);

                ScalerSetBit(P20_27_CAP_M1_DDR_CTRL1, ~_BIT2, 0x00);
                ScalerSetBit(P60_27_CAP_M2_DDR_CTRL1, ~_BIT2, 0x00);

                // Check capture running
                ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P20_2A_CAP_M1_STATUS, _BIT5, 0);

                // Input fast, wait 3 slow frame
                if(ScalerGetBit(P20_AC_DISP_M1_DISP_CTRL1, _BIT3) == _BIT3)
                {
                    ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _INPUT_PATH_M1_M2);
                    ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _INPUT_PATH_M1_M2);
                    ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _INPUT_PATH_M1_M2);
                    ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _INPUT_PATH_M1_M2);
                }
                else
                {
                    ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);
                    ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);
                    ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);
                    ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);
                }

                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, 0x00);
            }
            else
#endif
            {
                ScalerSetBit(P20_27_CAP_M1_DDR_CTRL1, ~_BIT2, 0x00);
                ScalerSetBit(P60_27_CAP_M2_DDR_CTRL1, ~_BIT2, 0x00);

                // Check capture running
                ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P20_2A_CAP_M1_STATUS, _BIT5, 0);
            }
        }
    }
    else
#endif
    {
        if(bEn == _ON)
        {
            ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~_BIT2, _BIT2);
            ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~_BIT2, _BIT2);
        }
        else
        {
            ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~_BIT2, 0x00);
            ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~_BIT2, 0x00);
        }
    }
}
#endif // End of #if(_FREEZE_SUPPORT == _ON)

#endif // End of #if(_FRC_SUPPORT == _ON)

