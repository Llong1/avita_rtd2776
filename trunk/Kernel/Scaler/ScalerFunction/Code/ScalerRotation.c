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
// ID Code      : ScalerRotation.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __SCALER_ROTATION__

#include "ScalerFunctionInclude.h"

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_MEMORY_BANK == 8)
#define _PICT_SET_WIDTH_SCALE           (16)        // Max: 32
#define _BLOCK_UNIT_WIDTH               (512)       // 64*8 = 512, Unit: Byte
#else
#define _PICT_SET_WIDTH_SCALE           (32)
#define _BLOCK_UNIT_WIDTH               (256)       // 4 Bank, 64*4 = 256
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
StructRotationStatus g_stRotationStatus;

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
bit ScalerRotationCheckStatus(void);
void ScalerRotationCheckVideoCompensation(void);
void ScalerRotationInitial(void);
void ScalerRotationSetPictSet(WORD usWidth, WORD usHeight);
void ScalerRotationControl(const StructSDRAMDataInfo *pstFIFOSize);
void ScalerRotationSetEnable(bit bEn);
void ScalerRotationSetInfo(WORD usHSize, WORD usVSize);
void ScalerRotationFRCInputCtrl(WORD usHorSize, WORD usVerSize);
void ScalerRotationFRCDisplayCtrl(WORD usHorSize, WORD usVerSize);
void ScalerRotationSetDDomainSourceSelect(EnumDDomainSourceSelect enumSourceSelect);
void ScalerRotationSetFRCEn(EnumFRCOnOff enumCapDispOnOff, bit bEn);
void ScalerRotationSetControl(EnumRotationType enumRotationType);
void ScalerRotationDisplayCtrlCW90CW270(void);
void ScalerRotationDisplayCtrlCW180(StructMemoryLineBlockStep stStep, WORD usVerSize);
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
void ScalerRotationDisplayCtrlLRMirror(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Check rotation status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerRotationCheckStatus(void)
{
#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        return _FALSE;
    }
    else
#endif
    {
        // Rotation only in 1P mode
        if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
        {
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
            // Check format conversion E/O status
            if(ScalerFmtCnvFtoPGetStatus(_INPUT_PATH_M1_M2) == _TRUE)
            {
                return (GET_ROT_TYPE() != _ROT_DISABLE);
            }
            else
            {
                switch(GET_ROT_TYPE())
                {
                    case _ROT_CW180:
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
                    case _ROT_HOR_MIRROR:
#endif

#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
                    case _ROT_VER_MIRROR:
#endif
                        return _TRUE;

                    default:
                        return _FALSE;
                }
            }
#else
            return (GET_ROT_TYPE() != _ROT_DISABLE);
#endif
        }

        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Check video compensation field
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerRotationCheckVideoCompensation(void)
{
    // Change video compensation field under rotation
    if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        switch(GET_ROT_TYPE())
        {
            default:
                break;

            case _ROT_DISABLE:
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
            case _ROT_HOR_MIRROR:
#endif
                // For 0
                ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~_BIT6, (GET_MDOMAIN_INPUT_VIDEO_FIELD() == _TRUE) ? _BIT6 : 0);
                break;

            case _ROT_CW180:
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
            case _ROT_VER_MIRROR:
#endif
                // For vertical flip
                ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~_BIT6, (GET_MDOMAIN_INPUT_VIDEO_FIELD() == _TRUE) ? 0 : _BIT6);
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Rotation Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerRotationInitial(void)
{
    // (For Roation using) Merge m1 display frame sync fifo to m2 display frame sync fifo.
    // ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_24_DISP_MAIN_FIFO_LEN_CTRL, ~_BIT1, _BIT1);

    // Rotation FRC Disable
    ScalerSetByte(P20_38_ROT_CAP_M1_CTRL1, 0x00);
    ScalerSetByte(P60_38_ROT_CAP_M2_CTRL1, 0x00);

    // Set Single Buffer Mode
    ScalerSetBit(P20_27_CAP_M1_DDR_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);
    ScalerSetBit(P60_27_CAP_M2_DDR_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

    // Set Line Mode / CAP Start Point to Change Block_sel = 1: Reference to vertical active region
    ScalerSetBit(P20_28_CAP_M1_DDR_CTRL2, ~(_BIT6 | _BIT4 | _BIT1 | _BIT0), _BIT6);
    ScalerSetBit(P60_28_CAP_M2_DDR_CTRL2, ~(_BIT6 | _BIT4 | _BIT1 | _BIT0), _BIT6);

    // Set 3 Buffer Disable
    ScalerSetByte(P20_29_CAP_M1_DDR_CTRL3, 0x00);
    ScalerSetByte(P60_29_CAP_M2_DDR_CTRL3, 0x00);

    // Set Pre-Read line
    ScalerSetByte(P20_A6_DISP_M1_PRRD_VST_H, 0x00);
    ScalerSetByte(P20_A7_DISP_M1_PRRD_VST_L, 0x02);
    ScalerSetByte(P60_A6_DISP_M2_PRRD_VST_H, 0x00);
    ScalerSetByte(P60_A7_DISP_M2_PRRD_VST_L, 0x02);

    // Disable One Frame FRC
    ScalerSetByte(P20_B1_DISP_M1_ONEF_DHF_H, 0x00);
    ScalerSetByte(P60_B1_DISP_M2_ONEF_DHF_H, 0x00);

    // Set Display :(1) Capture data from I-Domain, (2)E/O mode, (3) Disable 3 Buffer
    ScalerSetBit(P20_AF_DISP_M1_DISP_CTRL3, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P60_AF_DISP_M2_DISP_CTRL3, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Set Frame sync with line buffer mode, Set Input Faster
    ScalerSetBit(P20_AC_DISP_M1_DISP_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
    ScalerSetBit(P60_AC_DISP_M2_DISP_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);

    // Enable Display double buffer
    ScalerSetBit(P20_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(P60_AD_DISP_STATUS, ~_BIT4, _BIT4);

    // Wait double buffer
    if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0x00)
    {
        ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _INPUT_PATH_M1_M2);
    }

    // Rotation Disable
    ScalerSetByte(P20_F0_ROTATION_CTRL0, 0x01);
}

//--------------------------------------------------
// Description  : Set Picture Set for Block Mode
// Input Value  : usWidth --> Image Width
// Input Value  : usHeight --> Image Height
// Output Value : None
//--------------------------------------------------
void ScalerRotationSetPictSet(WORD usWidth, WORD usHeight)
{
    BYTE ucPictSetNum = 0;
    WORD usRow = 0;

    if((GET_ROT_TYPE() == _ROT_CW90) || (GET_ROT_TYPE() == _ROT_CW270))
    {
        BYTE ucPictIndex = 0;

        // Calculate Picture-Set Scale (unit: 256Byte)
        // Idea: Total Picture-Set Scale = (usWidth / 2) * 2 / (_BLOCK_UNIT_WIDTH / 8Byte * _PICT_SET_WIDTH_SCALE)
        // Actually : Total Picture-Set Scale = usWidth / _ROTATION_FRC_CAP_BLK_W
        ucPictSetNum = (((DWORD)usWidth) / _ROTATION_FRC_CAP_BLK_W / 10);
        ucPictSetNum += 1;

        // Get DC-Sys Page size selection, unit: Byte
        switch(ScalerGetBit(PA0_05_DC_SYS_MISC, (_BIT1 | _BIT0)))
        {
            case 0x00:
                PDATA_WORD(1) = 512;
                break;

            case _BIT0:
                PDATA_WORD(1) = 1024;
                break;

            case _BIT1:
                PDATA_WORD(1) = 2048;
                break;

            case (_BIT1 | _BIT0):
                PDATA_WORD(1) = 4096;
                break;

            default:
                PDATA_WORD(1) = 512;
                break;
        }

        // Calculate Picture-Set Height (unit: pict block
        PDATA_WORD(2) = (((DWORD)usHeight * GET_MEMORY_DATA_BIT()) / 128);
        PDATA_WORD(2) += ((((DWORD)usHeight * GET_MEMORY_DATA_BIT()) % 128) > 0) ? (1) : (0);

        usRow = (DWORD)PDATA_WORD(2) * _PICT_SET_WIDTH_SCALE / (PDATA_WORD(1) / 64); // pict block width = 64Byte
        usRow += (_PICT_SET_WIDTH_SCALE - (usRow % _PICT_SET_WIDTH_SCALE));

        // Set Picture-Set Info.
        // (M1 3 block + M2 3 block = 6)
        for(ucPictIndex = 0; ucPictIndex < (ucPictSetNum * 6); ucPictIndex++)
        {
            ScalerDDR3DCSysSetPictureSetInfo(ucPictIndex, _PICT_SET_WIDTH_SCALE, ((DWORD)ucPictIndex * usRow));
        }
    }

    // Set FRC M1 Capture fst_pict_idx / sex_pict_idx / thi_pict_idx;
    ScalerSetByte(P20_3F_ROT_CAP_M1_PICT_FST_IDX, 0x00);
    ScalerSetByte(P20_40_ROT_CAP_M1_PICT_SEC_IDX, ucPictSetNum);
    ScalerSetByte(P20_41_ROT_CAP_M1_PICT_THI_IDX, (ucPictSetNum * 2));

    // Set FRC M1 Display fst_pict_idx / sex_pict_idx / thi_pict_idx;
    ScalerSetByte(P20_D4_ROT_DISP_M1_PICT_FST_IDX, 0x00);
    ScalerSetByte(P20_D5_ROT_DISP_M1_PICT_SEC_IDX, ucPictSetNum);
    ScalerSetByte(P20_D6_ROT_DISP_M1_PICT_THI_IDX, (ucPictSetNum * 2));

    // Set FRC M2 Capture fst_pict_idx / sex_pict_idx / thi_pict_idx;
    ScalerSetByte(P60_3F_ROT_CAP_M2_PICT_FST_IDX, (ucPictSetNum * 3));
    ScalerSetByte(P60_40_ROT_CAP_M2_PICT_SEC_IDX, (ucPictSetNum * 4));
    ScalerSetByte(P60_41_ROT_CAP_M2_PICT_THI_IDX, (ucPictSetNum * 5));

    // Set FRC M2 Display fst_pict_idx / sex_pict_idx / thi_pict_idx;
    ScalerSetByte(P60_D4_ROT_DISP_M2_PICT_FST_IDX, (ucPictSetNum * 3));
    ScalerSetByte(P60_D5_ROT_DISP_M2_PICT_SEC_IDX, (ucPictSetNum * 4));
    ScalerSetByte(P60_D6_ROT_DISP_M2_PICT_THI_IDX, (ucPictSetNum * 5));
}

//--------------------------------------------------
// Description  : Rotation control
// Input Value  : stFIFOSize --> FIFO Size
// Output Value : None
//--------------------------------------------------
void ScalerRotationControl(const StructSDRAMDataInfo *pstFIFOSize)
{
    DebugMessageFRC("R_Type", GET_ROT_TYPE());
    DebugMessageFRC("R_Size", GET_ROT_DISP_SIZE());
    DebugMessageFRC("R-IH", pstFIFOSize->usInputHWidth);
    DebugMessageFRC("R_IV", pstFIFOSize->usInputVHeight);
    DebugMessageFRC("R-OH", pstFIFOSize->usOutputHWidth);
    DebugMessageFRC("R_OV", pstFIFOSize->usOutputVHeight);

    // Set FRC path count & page for rotation
    g_ucFRCPathCount = 2;
    g_usFRCPageSelect = 0x2000;

    // Set FRC IVS2DVSDelay
    ScalerFRCAdjustIVS2DVSDelay(pstFIFOSize->usInputVHeight);

    // Set DC_Sys Picture-Set
    ScalerRotationSetPictSet(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);

    // Set Roation info
    ScalerRotationSetInfo(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);

    // Set Roation Enable
    ScalerRotationSetEnable(_ENABLE);

    // Set up FRC Capture
    ScalerRotationFRCInputCtrl(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);

    // Set up FRC Display
    switch(GET_ROT_TYPE())
    {
        case _ROT_CW180:
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _ROT_HOR_MIRROR:
#endif
            // Enable display timing
            ScalerFRCCompareIHFandDHF(pstFIFOSize->usInputVHeight);
            ScalerRotationFRCDisplayCtrl(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);
            break;

        case _ROT_CW90:
        case _ROT_CW270:
        default:
            // Enable display timing
            ScalerFRCCompareIHFandDHF(pstFIFOSize->usInputHWidth);
            ScalerRotationFRCDisplayCtrl(pstFIFOSize->usInputVHeight, pstFIFOSize->usInputHWidth);
            break;
    }

    // Wait I-domain Stable Before FRC Enable
    if(ScalerGetBit(P31_A0_I_DB_CTRL0, _BIT7) == 0)
    {
        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
    }

    // Enable Capture
    ScalerSetBit(P20_27_CAP_M1_DDR_CTRL1, ~(_BIT7), _BIT7);
    ScalerSetBit(P60_27_CAP_M2_DDR_CTRL1, ~(_BIT7), _BIT7);

    // Enable M1/M2 FRC Display
    // Wait _EVENT_DEN_START for FRC Display Enable At The Same Time
    ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_START, _INPUT_PATH_M1_M2);
    ScalerSetBit(P20_AC_DISP_M1_DISP_CTRL1, ~(_BIT0), _BIT0);
    ScalerSetBit(P60_AC_DISP_M2_DISP_CTRL1, ~(_BIT0), _BIT0);

    // Enable M1/M2 Display double buffer
    ScalerSetBit(P20_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(P60_AD_DISP_STATUS, ~_BIT4, _BIT4);

    // Wait _EVENT_IVS For FRC Run In Single Frame Buffer
    if(ScalerGetBit(P31_A0_I_DB_CTRL0, _BIT7) == 0x00)
    {
        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
    }

    // -----------------------
    // Set Double / Single Frame Buffer
    // -----------------------
    // Wait _EVENT_IEN_START Before Double Frame Buffer Setting
    if(ScalerGetBit(P31_A0_I_DB_CTRL0, _BIT7) == 0x00)
    {
        ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_START, GET_MDOMAIN_INPUT_DATA_PATH());
    }

    // Set Double Buffer
    ScalerSetBit(P20_27_CAP_M1_DDR_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);
    ScalerSetBit(P60_27_CAP_M2_DDR_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);
    ScalerSetBit(P20_AC_DISP_M1_DISP_CTRL1, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
    ScalerSetBit(P60_AC_DISP_M2_DISP_CTRL1, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);

    // Set 3 Buffer
    ScalerSetBit(P20_29_CAP_M1_DDR_CTRL3, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P60_29_CAP_M2_DDR_CTRL3, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P20_AF_DISP_M1_DISP_CTRL3, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P60_AF_DISP_M2_DISP_CTRL3, ~(_BIT1 | _BIT0), _BIT0);

    // Enable M1/M2 Display Double Buffer
    ScalerSetBit(P20_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(P60_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _INPUT_PATH_M1_M2);

    // Set Frame tracking function for VFreq < 30Hz
    if(GET_MEMORY_SELECT() == _MN_FRAME_SYNC_MEMORY)
    {
        ScalerMemoryFrameTracking();
        ScalerMemorySetFrameTrackingEnable(_ENABLE);
    }
}

//--------------------------------------------------
// Description  : Set Rotation Enable/Disable
// Input Value  : bEn --> Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerRotationSetEnable(bit bEn)
{
    if(bEn == _DISABLE)
    {
        // Set Rotation Disable
        ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT7), 0x00);

        // Set Roation Type = No Rotation.
        ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT6 | _BIT5), 0x00);
    }
    else
    {
        if(ScalerGetBit(P20_F0_ROTATION_CTRL0, _BIT7) == 0x00)
        {
            // Set Rotation Enable
            ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT7), _BIT7);
        }
    }
}

//--------------------------------------------------
// Description  : Set Rotation Information
// Input Value  : usHSize --> Image Width
// Input Value  : usVSize --> Image Height
// Output Value : None
//--------------------------------------------------
void ScalerRotationSetInfo(WORD usHSize, WORD usVSize)
{
    // Set Roation Type
    switch(GET_ROT_TYPE())
    {
        default:
        case _ROT_CW90:
            ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT6 | _BIT5), _BIT5);
            break;

        case _ROT_CW180:
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _ROT_HOR_MIRROR:
#endif
            ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT6 | _BIT5), _BIT6);
            break;

        case _ROT_CW270:
            ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
            break;
    }

    // Set Rotation Line buffer merge.
    // It can merge 2 line buffer (1088+1088) as 1 line buffer (2176 *60bits).
    ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT4), ((usHSize > 2176) ? (_BIT4) : 0x00));

    // Set Rotation support bit
    if(GET_MEMORY_DATA_BIT() == (_COLOR_DEPTH_10_BITS * 3))
    {
        ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT3), _BIT3);
    }
    else
    {
        ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT3), 0x00);
    }

    // Set Rotation Source pixel number
    ScalerSetBit(P20_F1_ROTATION_IN_WID_H, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usHSize >> 8) & 0x1F);
    ScalerSetByte(P20_F2_ROTATION_IN_WID_L, (usHSize & 0xFF));

    // Set Rotation Source line number
    if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
    {
        // (usVSize / 2) : E/O mode
        ScalerSetBit(P20_F3_ROTATION_IN_LEN_H, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((usVSize / 2) >> 8) & 0x1F);
        ScalerSetByte(P20_F4_ROTATION_IN_LEN_L, ((usVSize / 2) & 0xFF));
    }
    else
    {
        ScalerSetBit(P20_F3_ROTATION_IN_LEN_H, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((usVSize) >> 8) & 0x1F);
        ScalerSetByte(P20_F4_ROTATION_IN_LEN_L, ((usVSize) & 0xFF));
    }

    // Set Rotation pixel remain
    if(GET_ROT_TYPE() == _ROT_CW270)
    {
        if(GET_MEMORY_DATA_BIT() == (_COLOR_DEPTH_10_BITS * 3))
        {
            pData[0] = (((usVSize % 64) == 0) ? (0x3F) : ((usVSize % 64) - 1));
        }
        else
        {
            pData[0] = (((usVSize % 16) == 0) ? (0x3F) : ((usVSize % 16) - 1));
        }
    }
    else
    {
        pData[0] = 0;
    }

    ScalerSetBit(P20_F5_ROTATION_CTRL1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pData[0]);

    // Set Vertical Rotation Factor For Reading Line Buffer
    // Bits per pixel * 2 * HWidth = 120 * Factor * HTotal
    // --> 24bit: Factor = (2 * HWidth / (5 * HTotal)) * 2^8.
    // --> 30bit: Factor = (HWidth / (2*Htoal)) * 2^8.
    if(GET_MEMORY_DATA_BIT() == (_COLOR_DEPTH_10_BITS * 3))
    {
        pData[0] = ((DWORD)g_stMDomainInputData.usHWidth << 8) / 2 / g_stMDomainInputData.usHTotal;
    }
    else
    {
        pData[0] = ((DWORD)g_stMDomainInputData.usHWidth << 8) / 5 * 2 / g_stMDomainInputData.usHTotal;
    }

    ScalerSetByte(P20_F6_ROTATION_CTRL2, pData[0]);
}

//--------------------------------------------------
// Description  : Rotation FRC Capture FIFO Setting for Rotation Mode
// Input Value  : ucHorSize --> Horizontal size
// Input Value  : ucVerSize --> Vertical Size
// Output Value : None
//--------------------------------------------------
void ScalerRotationFRCInputCtrl(WORD usHorSize, WORD usVerSize)
{
    StructMemoryLineBlockStep stStep = {0};
    DWORD ulTemp = 0;
    bit bHor4Mutiple = _FALSE;

    switch(GET_ROT_TYPE())
    {
        case _ROT_CW180:
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _ROT_HOR_MIRROR:
#endif
            // E/O mode
            if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
            {
                usVerSize = usVerSize >> 1;
            }

            // Calculate Line Mode Size
            // One Line total pixel for SDRAM (unit : 64 bits)
            ulTemp = ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() % 64) ?
                     (((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64) + 1) :
                     ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64);

            // Calculate Line Step and Block Step
            ScalerMemoryCalculateLineStepAndBlockStep(ulTemp, usVerSize, &stStep);

            // Calculate Number of One Line and Remain of One Line
            ulTemp = ScalerMemoryCalculateNumberAndRemain(ulTemp, _ROTATION_WRITE_LENGTH_CW180, 1);

            break;

        default:
            break;
    }

    if((usHorSize % 4) != 0)
    {
        bHor4Mutiple = _TRUE;
        usHorSize += (4 - (usHorSize % 4));
    }

    //***********************************
    // Main 1 / Main 2
    //***********************************
    // Disable FRC M1/M2 Capture block
    ScalerSetByte(P5_27_CAP_M1_DDR_CTRL1, 0x02);
    ScalerSetByte(P45_27_CAP_M2_DDR_CTRL1, 0x02);

    // Set M1/M2 Capture FIFO source, 0: From I-Domain, 1: From Rotation
    ScalerSetBit(P5_29_CAP_M1_DDR_CTRL3, ~_BIT2, _BIT2);
    ScalerSetBit(P45_29_CAP_M2_DDR_CTRL3, ~_BIT2, _BIT2);

    // Set M1/M2 Line Mode
    ScalerSetBit(P20_28_CAP_M1_DDR_CTRL2, ~(_BIT4), 0x00);
    ScalerSetBit(P60_28_CAP_M2_DDR_CTRL2, ~(_BIT4), 0x00);

    // Set M1/M2 Block Step
    ScalerMaskSetDWord(P20_15_CAP_M1_BLOCK_STEP_MSB, 0xF0000000, stStep.ulBlockStep);
    ScalerMaskSetDWord(P60_15_CAP_M2_BLOCK_STEP_MSB, 0xF0000000, stStep.ulBlockStep);

    switch(GET_ROT_TYPE())
    {
        case _ROT_CW180:
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _ROT_HOR_MIRROR:
#endif
            // Set M1/M2 Line Step
            ScalerMaskSetDWord(P20_19_CAP_M1_LINE_STEP_MSB, 0xF0000000, ((~stStep.ulLineStep) + 1));
            ScalerMaskSetDWord(P60_19_CAP_M2_LINE_STEP_MSB, 0xF0000000, ((~stStep.ulLineStep) + 1));

            // Set M1/M2 Water level
            ScalerSetBit(P20_1D_CAP_M1_WATER_LEVEL_H, ~(_BIT0), ((((WORD)_ROTATION_WRITE_LENGTH_CW180 / 2) >> 8) & 0x01));
            ScalerSetByte(P20_1E_CAP_M1_WATER_LEVEL_L, (((WORD)_ROTATION_WRITE_LENGTH_CW180 / 2) & 0xFF));
            ScalerSetBit(P60_1D_CAP_M2_WATER_LEVEL_H, ~(_BIT0), ((((WORD)_ROTATION_WRITE_LENGTH_CW180 / 2) >> 8) & 0x01));
            ScalerSetByte(P60_1E_CAP_M2_WATER_LEVEL_L, (((WORD)_ROTATION_WRITE_LENGTH_CW180 / 2) & 0xFF));

            // Set M1/M2 Pixel Nmber
            ScalerSetWord(P20_1F_CAP_M1_PIXEL_NUM_H, usHorSize);
            ScalerSetWord(P60_1F_CAP_M2_PIXEL_NUM_H, usHorSize);

            // Set M1/M2 Line Number
            ScalerSetWord(P20_21_CAP_M1_LINE_NUM_H, usVerSize);
            ScalerSetWord(P60_21_CAP_M2_LINE_NUM_H, usVerSize);

            // Set M1/M2 Length
            ScalerSetByte(P20_25_CAP_M1_WR_LEN, _ROTATION_WRITE_LENGTH_CW180);
            ScalerSetByte(P60_25_CAP_M2_WR_LEN, _ROTATION_WRITE_LENGTH_CW180);

            break;

        case _ROT_CW90:
        case _ROT_CW270:
        default:

            // Set M1/M2 Line Step
            ScalerSetDWord(P20_19_CAP_M1_LINE_STEP_MSB, 0x00);
            ScalerSetDWord(P60_19_CAP_M2_LINE_STEP_MSB, 0x00);

            // Set M1/M2 Water level
            // Water Level = (blk_w * blk_lr) / 2.    (blk_lr = 1)
            // Water Level = blk_w / 2
            ScalerSetBit(P20_1D_CAP_M1_WATER_LEVEL_H, ~(_BIT0), ((((WORD)_ROTATION_FRC_CAP_BLK_W / 2) >> 8) & 0x01));
            ScalerSetByte(P20_1E_CAP_M1_WATER_LEVEL_L, (((WORD)_ROTATION_FRC_CAP_BLK_W / 2) & 0xFF));
            ScalerSetBit(P60_1D_CAP_M2_WATER_LEVEL_H, ~(_BIT0), ((((WORD)_ROTATION_FRC_CAP_BLK_W / 2) >> 8) & 0x01));
            ScalerSetByte(P60_1E_CAP_M2_WATER_LEVEL_L, (((WORD)_ROTATION_FRC_CAP_BLK_W / 2) & 0xFF));

            // Set M1/M2 Pixel Nmber
            PDATA_WORD(0) = (usHorSize / 2);
            ScalerSetByte(P20_1F_CAP_M1_PIXEL_NUM_H, pData[0]);
            ScalerSetByte(P20_20_CAP_M1_PIXEL_NUM_L, pData[1]);
            if(bHor4Mutiple == _TRUE)
            {
                ScalerSetByte(P60_1F_CAP_M2_PIXEL_NUM_H, pData[0]);
                ScalerSetByte(P60_20_CAP_M2_PIXEL_NUM_L, (pData[1] - 2));
            }
            else
            {
                ScalerSetByte(P60_1F_CAP_M2_PIXEL_NUM_H, pData[0]);
                ScalerSetByte(P60_20_CAP_M2_PIXEL_NUM_L, pData[1]);
            }

            // Set M1/M2 Line Number
            PDATA_WORD(0) = ((DWORD)usVerSize * GET_MEMORY_DATA_BIT() / 128);
            PDATA_WORD(0) += ((((DWORD)usVerSize * GET_MEMORY_DATA_BIT() % 128) == 0) ? (0) : (1));
            ScalerSetWord(P20_21_CAP_M1_LINE_NUM_H, PDATA_WORD(0));
            ScalerSetWord(P60_21_CAP_M2_LINE_NUM_H, PDATA_WORD(0));

            // Set M1/M2 Length
            ScalerSetByte(P20_25_CAP_M1_WR_LEN, _ROTATION_FRC_CAP_BLK_W);
            ScalerSetByte(P60_25_CAP_M2_WR_LEN, _ROTATION_FRC_CAP_BLK_W);

            break;
    }

    // Set M1/M2 Number
    ScalerSetByte(P20_23_CAP_M1_WR_NUM_H, ((ulTemp >> 8) & 0xFF));
    ScalerSetByte(P20_24_CAP_M1_WR_NUM_L, (ulTemp & 0xFF));
    ScalerSetByte(P60_23_CAP_M2_WR_NUM_H, ((ulTemp >> 8) & 0xFF));
    ScalerSetByte(P60_24_CAP_M2_WR_NUM_L, (ulTemp & 0xFF));

    // Set M1/M2 Remain
    ScalerSetByte(P20_26_CAP_M1_WR_REMAIN, ((ulTemp >> 16) & 0xFF));
    ScalerSetByte(P60_26_CAP_M2_WR_REMAIN, ((ulTemp >> 16) & 0xFF));

    // Set M1/M2 Start Address
    if((GET_ROT_TYPE() == _ROT_CW90) || (GET_ROT_TYPE() == _ROT_CW270))
    {
        ScalerSetDWord(P20_00_CAP_M1_MEM_ADDR_MSB, 0x00);
        ScalerSetDWord(P20_04_CAP_M1_BL2_ADDR_MSB, 0x00);
        ScalerSetDWord(P20_08_CAP_M1_BL3_ADDR_MSB, 0x00);
        ScalerSetDWord(P60_00_CAP_M2_MEM_ADDR_MSB, 0x00);
        ScalerSetDWord(P60_04_CAP_M2_BL2_ADDR_MSB, 0x00);
        ScalerSetDWord(P60_08_CAP_M2_BL3_ADDR_MSB, 0x00);
    }
    else
    {
        ScalerSetDWord(P20_00_CAP_M1_MEM_ADDR_MSB, stStep.ulBlockStep);
        ScalerSetDWord(P20_04_CAP_M1_BL2_ADDR_MSB, (stStep.ulBlockStep * 2));
        ScalerSetDWord(P20_08_CAP_M1_BL3_ADDR_MSB, (stStep.ulBlockStep * 3));

        if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
        {
            ScalerSetDWord(P60_00_CAP_M2_MEM_ADDR_MSB, (stStep.ulBlockStep * 4));
            ScalerSetDWord(P60_04_CAP_M2_BL2_ADDR_MSB, (stStep.ulBlockStep * 5));
            ScalerSetDWord(P60_08_CAP_M2_BL3_ADDR_MSB, (stStep.ulBlockStep * 6));
        }
    }

#if(_FALSE)
    // Set Down limit = default value 0x0000000
    ScalerSetDWord(P20_0C_CAP_M1_BOUNDARY_ADDR1_MSB, 0x00);
    ScalerSetDWord(P60_0C_CAP_M2_BOUNDARY_ADDR1_MSB, 0x00);

    // Set Up limit = default value = 0xFFFFFFF
    ScalerSetDWord(P20_10_CAP_M1_BOUNDARY_ADDR2_MSB, 0x0FFFFFFF);
    ScalerSetDWord(P60_10_CAP_M2_BOUNDARY_ADDR2_MSB, 0x0FFFFFFF);

#endif

    // (_BIT6 | _BIT5 | _BIT4 | _BIT3): Set Single Buffer
    // _BIT1: Use IVS as synchronous reset
    ScalerSetBit(P20_27_CAP_M1_DDR_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1), _BIT1);
    ScalerSetBit(P60_27_CAP_M2_DDR_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1), _BIT1);

    if((GET_ROT_TYPE() == _ROT_CW90) || (GET_ROT_TYPE() == _ROT_CW270))
    {
        // Set blk_strt_x
        ScalerSetBit(P20_32_ROT_CAP_M1_BLK_STRT_X_MSB, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte(P20_33_ROT_CAP_M1_BLK_STRT_X_LSB, 0x00);
        ScalerSetBit(P60_32_ROT_CAP_M2_BLK_STRT_X_MSB, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte(P60_33_ROT_CAP_M2_BLK_STRT_X_LSB, 0x00);

        // Set blk_strt_y
        if(GET_ROT_TYPE() == _ROT_CW270)
        {
            PDATA_WORD(0) = (((ScalerGetByte(P20_21_CAP_M1_LINE_NUM_H) << 8) | (ScalerGetByte(P20_22_CAP_M1_LINE_NUM_L))) - 1);
        }
        else
        {
            PDATA_WORD(0) = 0;
        }

        ScalerSetBit(P20_34_ROT_CAP_M1_BLK_STRT_Y_MSB, ~(_BIT2 | _BIT1 | _BIT0), (pData[0] & 0x07));
        ScalerSetByte(P20_35_ROT_CAP_M1_BLK_STRT_Y_LSB, pData[1]);
        ScalerSetBit(P60_34_ROT_CAP_M2_BLK_STRT_Y_MSB, ~(_BIT2 | _BIT1 | _BIT0), (pData[0] & 0x07));
        ScalerSetByte(P60_35_ROT_CAP_M2_BLK_STRT_Y_LSB, pData[1]);

        // Set blk_w
        ScalerSetByte(P20_36_ROT_CAP_M1_BLK_W, _ROTATION_FRC_CAP_BLK_W);
        ScalerSetByte(P60_36_ROT_CAP_M2_BLK_W, _ROTATION_FRC_CAP_BLK_W);

        // Set blk_lr
        ScalerSetByte(P20_37_ROT_CAP_M1_BLK_LR, 0x01);
        ScalerSetByte(P60_37_ROT_CAP_M2_BLK_LR, 0x01);

        // _BIT1: Set blk_mode, 0:16x1 mode, 1: 8x2 mode
        // _Bit0: Set blk_offset, 0: Frame mode, 1: Field mode
        ScalerSetBit(P20_38_ROT_CAP_M1_CTRL1, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit(P60_38_ROT_CAP_M2_CTRL1, ~(_BIT1 | _BIT0), 0x00);

        // ((Hwidth /2)*128/64) = Hwidth = pict_num * (GPNum * GPLen + GPRem) + (RPNum * RPLen + RPRem)
        // --> GPLen = RPLen = GPRem.
        // --> (Hwidth) / GPLen = Total_pict_num.
        // --> (Hwidth) % GPLen = RPRem.
        // --> Total_pict_num / 10 = pict_num.
        // --> Total_pict_num % 10 = RPNum.
        // --> GPNum = 9
        PDATA_WORD(4) = ((DWORD)usHorSize) / _ROTATION_FRC_CAP_BLK_W;
        PDATA_WORD(5) = ((DWORD)usHorSize) % _ROTATION_FRC_CAP_BLK_W;

        if(bHor4Mutiple == _TRUE)
        {
            PDATA_WORD(6) = ((DWORD)usHorSize - 4) / _ROTATION_FRC_CAP_BLK_W;
            PDATA_WORD(7) = ((DWORD)usHorSize - 4) % _ROTATION_FRC_CAP_BLK_W;
        }
        else
        {
            PDATA_WORD(6) = PDATA_WORD(4);
            PDATA_WORD(7) = PDATA_WORD(5);
        }

        // Remain cannot be 0.
        if(PDATA_WORD(5) == 0)
        {
            PDATA_WORD(4) -= 1;
            PDATA_WORD(5) = _ROTATION_FRC_CAP_BLK_W;
        }

        if(PDATA_WORD(7) == 0)
        {
            PDATA_WORD(6) -= 1;
            PDATA_WORD(7) = _ROTATION_FRC_CAP_BLK_W;
        }

        if(PDATA_WORD(4) >= 10)
        {
            // Note: For _ROTATION_FRC_CAP_BLK_W = 0x60.
            // Max PICT width  = 256B * 32 = 1024 * 8Byte --> (GPNum * GPLen + GPRem) < 1024.
            // Set GP_BLK_LEN
            ScalerSetByte(P20_3A_ROT_CAP_M1_GENERALPICT_LEN, _ROTATION_FRC_CAP_BLK_W);
            // Set GP_BLK_NUM
            ScalerSetByte(P20_39_ROT_CAP_M1_GENERALPICT_NUM, 0x09);
            // Set GP_BLK_REM
            ScalerSetByte(P20_3B_ROT_CAP_M1_GENERALPICT_REM, _ROTATION_FRC_CAP_BLK_W);
            // Set PICT_NUM
            ScalerSetByte(P20_42_ROT_CAP_M1_PICT_NUM, ((PDATA_WORD(4) / 10) & 0xFF));
        }
        else
        {
            // Set GP_BLK_LEN
            ScalerSetByte(P20_3A_ROT_CAP_M1_GENERALPICT_LEN, 0x00);
            // Set GP_BLK_NUM
            ScalerSetByte(P20_39_ROT_CAP_M1_GENERALPICT_NUM, 0x00);
            // Set GP_BLK_REM
            ScalerSetByte(P20_3B_ROT_CAP_M1_GENERALPICT_REM, 0x00);
            // Set PICT_NUM
            ScalerSetByte(P20_42_ROT_CAP_M1_PICT_NUM, 0x00); // 1 pict set
        }

        if(PDATA_WORD(6) >= 10)
        {
            // Note: For _ROTATION_FRC_CAP_BLK_W = 0x60.
            // Max PICT width  = 256B * 32 = 1024 * 8Byte --> (GPNum * GPLen + GPRem) < 1024.
            // Set GP_BLK_LEN
            ScalerSetByte(P60_3A_ROT_CAP_M2_GENERALPICT_LEN, _ROTATION_FRC_CAP_BLK_W);
            // Set GP_BLK_NUM
            ScalerSetByte(P60_39_ROT_CAP_M2_GENERALPICT_NUM, 0x09);
            // Set GP_BLK_REM
            ScalerSetByte(P60_3B_ROT_CAP_M2_GENERALPICT_REM, _ROTATION_FRC_CAP_BLK_W);
            // Set PICT_NUM
            ScalerSetByte(P60_42_ROT_CAP_M2_PICT_NUM, ((PDATA_WORD(6) / 10) & 0xFF));
        }
        else
        {
            // Set GP_BLK_LEN
            ScalerSetByte(P60_3A_ROT_CAP_M2_GENERALPICT_LEN, 0x00);
            // Set GP_BLK_NUM
            ScalerSetByte(P60_39_ROT_CAP_M2_GENERALPICT_NUM, 0x00);
            // Set GP_BLK_REM
            ScalerSetByte(P60_3B_ROT_CAP_M2_GENERALPICT_REM, 0x00);
            // Set PICT_NUM
            ScalerSetByte(P60_42_ROT_CAP_M2_PICT_NUM, 0x00);
        }

        // Set RP_BLK_NUM
        ScalerSetByte(P20_3C_ROT_CAP_M1_REMAINPICT_NUM, ((PDATA_WORD(4) % 10) & 0xFF));
        ScalerSetByte(P60_3C_ROT_CAP_M2_REMAINPICT_NUM, ((PDATA_WORD(6) % 10) & 0xFF));

        // Set RP_BLK_LEN
        ScalerSetByte(P20_3D_ROT_CAP_M1_REMAINPICT_LEN, _ROTATION_FRC_CAP_BLK_W);
        ScalerSetByte(P60_3D_ROT_CAP_M2_REMAINPICT_LEN, _ROTATION_FRC_CAP_BLK_W);

        // Set RP_BLK_REM
        ScalerSetByte(P20_3E_ROT_CAP_M1_REMAINPICT_REM, PDATA_WORD(5));
        ScalerSetByte(P60_3E_ROT_CAP_M2_REMAINPICT_REM, PDATA_WORD(7));
    }

    // Set M1/M2 Rotation Type, 00: no roation, 01: cw90, 10:cw180, 11: cw270
    ScalerRotationSetControl(GET_ROT_TYPE());

    ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);
}

//--------------------------------------------------
// Description  : Rotation Display FIFO Setting for Rotation Mode
// Input Value  : usHorSize --> Horizontal size
// Input Value  : usVerSize --> Vertical Size
// Output Value : None
//--------------------------------------------------
void ScalerRotationFRCDisplayCtrl(WORD usHorSize, WORD usVerSize)
{
    StructMemoryLineBlockStep stStep = {0};
    DWORD ulTemp = 0;
    WORD usCapLine = 0;
    WORD usPreReadLine = 0;

    usPreReadLine = ScalerFRCCalculatePreReadLine(usVerSize);

    // E/O mode
    usVerSize = usVerSize >> 1;

    switch(GET_ROT_TYPE())
    {
        case _ROT_CW180:
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _ROT_HOR_MIRROR:
#endif
            // Calculate Line Mode Size
            // One Line total pixel for SDRAM (unit : 64 bits)
            ulTemp = ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() % 64) ?
                     (((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64) + 1) :
                     ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64);

            // Calculate Line Step And Block Step
            if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
            {
                ScalerMemoryCalculateLineStepAndBlockStep(ulTemp, usVerSize, &stStep);
            }
            else
            {
                ScalerMemoryCalculateLineStepAndBlockStep(ulTemp, (usVerSize * 2), &stStep);

                stStep.ulLineStep = stStep.ulLineStep << 1;
            }

            // Calculate Number of One Line and Remain of One Line
            ulTemp = ScalerMemoryCalculateNumberAndRemain(ulTemp, _ROTATION_READ_LENGTH_CW180, 0);

            break;

        case _ROT_CW90:
        case _ROT_CW270:
        default:

            break;
    }

    //***********************************
    // Main 1 / Main 2
    //***********************************
    // Disable FRC M1/M2 Display
    ScalerSetByte(P5_AC_DISP_M1_DISP_CTRL1, 0x00);
    ScalerSetByte(P45_AC_DISP_M2_DISP_CTRL1, 0x00);

    // _BIT2: Disp fifo source, 0: form FRC, 1: from Rotation
    // _BIT1: Disp cooperation mode, 0: Cooperation mode, 1: Single mode
    // _BIT0: 3buf enable
    ScalerSetBit(P5_AF_DISP_M1_DISP_CTRL3, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
    ScalerSetBit(P45_AF_DISP_M2_DISP_CTRL3, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    // Set M1/M2 Block Step
    ScalerMaskSetDWord(P20_95_DISP_M1_BLOCK_STEP_MSB, 0xF0000000, stStep.ulBlockStep);
    ScalerMaskSetDWord(P60_95_DISP_M2_BLOCK_STEP_MSB, 0xF0000000, stStep.ulBlockStep);

    // Set M1/M2 Line Step
    ScalerMaskSetDWord(P20_99_DISP_M1_LINE_STEP_MSB, 0xF0000000, stStep.ulLineStep);
    ScalerMaskSetDWord(P60_99_DISP_M2_LINE_STEP_MSB, 0xF0000000, stStep.ulLineStep);

    // Set M1/M2 Pixel Number
    ScalerSetWord(P20_A2_DISP_M1_PXL_NUM_H, usHorSize);
    ScalerSetWord(P60_A2_DISP_M2_PXL_NUM_H, usHorSize);

    // Set M1/M2 Line number
    ScalerSetWord(P20_A4_DISP_M1_LINE_NUM_H, usVerSize);
    ScalerSetWord(P60_A4_DISP_M2_LINE_NUM_H, usVerSize);

    // Set M1/M2 Pre-read
    ScalerSetWord(P20_A6_DISP_M1_PRRD_VST_H, usPreReadLine);
    ScalerSetWord(P60_A6_DISP_M2_PRRD_VST_H, usPreReadLine);

    // Set M1/M2 Number
    ScalerSetByte(P20_A8_DISP_M1_READ_NUM_H, ((ulTemp >> 8) & 0xFF));
    ScalerSetByte(P20_A9_DISP_M1_READ_NUM_L, (ulTemp & 0xFF));
    ScalerSetByte(P60_A8_DISP_M2_READ_NUM_H, ((ulTemp >> 8) & 0xFF));
    ScalerSetByte(P60_A9_DISP_M2_READ_NUM_L, (ulTemp & 0xFF));

    // Set M1/M2 Length, Remain
    ScalerSetByte(P20_AA_DISP_M1_READ_LEN, _ROTATION_READ_LENGTH_CW180);
    ScalerSetByte(P20_AB_DISP_M1_READ_REMAIN, ((ulTemp >> 16) & 0xFF));
    ScalerSetByte(P60_AA_DISP_M2_READ_LEN, _ROTATION_READ_LENGTH_CW180);
    ScalerSetByte(P60_AB_DISP_M2_READ_REMAIN, ((ulTemp >> 16) & 0xFF));

    // Set M1/M2 Read Start Address
    switch(GET_ROT_TYPE())
    {
        case _ROT_CW90:
        case _ROT_CW270:
            ScalerRotationDisplayCtrlCW90CW270();
            break;

#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _ROT_HOR_MIRROR:
            ScalerRotationDisplayCtrlLRMirror();
            break;
#endif

        case _ROT_CW180:
        default:
            ScalerRotationDisplayCtrlCW180(stStep, usVerSize);
            break;
    }

#if(_FALSE)
    // Set Down limit = default value 0x0000000
    ScalerSetDWord(P20_8C_DISP_M1_BOUNDARY_ADDR1_MSB, 0x00);
    ScalerSetDWord(P60_8C_DISP_M2_BOUNDARY_ADDR1_MSB, 0x00);

    // Set Up limit = default value = 0xFFFFFFF
    ScalerSetDWord(P20_90_DISP_M1_BOUNDARY_ADDR2_MSB, 0x0FFFFFFF);
    ScalerSetDWord(P60_90_DISP_M2_BOUNDARY_ADDR2_MSB, 0x0FFFFFFF);

#endif

    // _BIT7: Set Line Mode
    // (_BIT6 | _BIT5 | _BIT4): Set Single Buffer
    ScalerSetBit(P20_AC_DISP_M1_DISP_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(P60_AC_DISP_M2_DISP_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Use Information From FRC Capture
    ScalerRotationSetDDomainSourceSelect(_DDOMAIN_SRC_FRAM_FRC);

    // Set M1/M2 Input Format 30 Bit
    if(GET_MEMORY_DATA_BIT() == (_COLOR_DEPTH_10_BITS * 3))
    {
        ScalerSetBit(P20_AE_DISP_M1_DISP_CTRL2, ~_BIT7, _BIT7);
        ScalerSetBit(P60_AE_DISP_M2_DISP_CTRL2, ~_BIT7, _BIT7);
    }
    else
    {
        ScalerSetBit(P20_AE_DISP_M1_DISP_CTRL2, ~_BIT7, 0x00);
        ScalerSetBit(P60_AE_DISP_M2_DISP_CTRL2, ~_BIT7, 0x00);
    }

    // Disable M1/M2 One Frame FRC
    ScalerSetBit(P20_B1_DISP_M1_ONEF_DHF_H, ~_BIT7, 0x00);
    ScalerSetBit(P60_B1_DISP_M2_ONEF_DHF_H, ~_BIT7, 0x00);

    if((GET_ROT_TYPE() == _ROT_CW90) || (GET_ROT_TYPE() == _ROT_CW270))
    {
        // Set blk_strt_x
        ScalerSetBit(P20_CA_ROT_DISP_M1_BLK_STRT_X_MSB, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte(P20_CB_ROT_DISP_M1_BLK_STRT_X_LSB, 0x00);
        ScalerSetBit(P60_CA_ROT_DISP_M2_BLK_STRT_X_MSB, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte(P60_CB_ROT_DISP_M2_BLK_STRT_X_LSB, 0x00);

        // Set blk_strt_y
        ScalerSetBit(P20_CC_ROT_DISP_M1_BLK_STRT_Y_MSB, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte(P20_CD_ROT_DISP_M1_BLK_STRT_Y_LSB, 0x00);
        ScalerSetBit(P60_CC_ROT_DISP_M2_BLK_STRT_Y_MSB, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte(P60_CD_ROT_DISP_M2_BLK_STRT_Y_LSB, 0x00);

        // Set blk_w
        ScalerSetBit(P20_CE_ROT_DISP_M1_BLK_W, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _ROTATION_FRC_DISP_BLK_W);
        ScalerSetBit(P60_CE_ROT_DISP_M2_BLK_W, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _ROTATION_FRC_DISP_BLK_W);

        // Set blk_lr
        ScalerSetBit(P20_CF_ROT_DISP_M1_BLK_LR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00); // useless
        ScalerSetBit(P60_CF_ROT_DISP_M2_BLK_LR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00); // useless

        // _BIT1: blk mode, 0:16x1 mode, 1:8x2 mode
        // _BIT0: blk_offset, 0:Frame mode, 1: Field mode
        ScalerSetBit(P20_D0_ROT_DISP_M1_CTRL1, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit(P60_D0_ROT_DISP_M2_CTRL1, ~(_BIT1 | _BIT0), 0x00);

        // Set blk_height = cap_linenum
        // Get cap_linenum
        usCapLine = ((ScalerGetByte(P20_21_CAP_M1_LINE_NUM_H) << 8) | (ScalerGetByte(P20_22_CAP_M1_LINE_NUM_L)));
        ScalerSetWord(P20_DA_ROT_DISP_M1_AR_HEIGHT_H, usCapLine);
        ScalerSetWord(P60_DA_ROT_DISP_M2_AR_HEIGHT_H, usCapLine);

        // Calculate blk_num/blk_rem
        // cal_linnum * blk_w = blk_num * blk_len' + blk_rem
        // blk_len = blk_len' / blk_w
        // blk_rem = blk_rem' / blk_w
        PDATA_WORD(1) = (usCapLine * _ROTATION_FRC_DISP_BLK_W);

        // blk_num
        if((PDATA_WORD(1) % _ROTATION_BLK_LENGTH) != 0)
        {
            // blk_num
            PDATA_WORD(2) = PDATA_WORD(1) / _ROTATION_BLK_LENGTH;
            // blk_rem'
            PDATA_WORD(3) = (PDATA_WORD(1) % _ROTATION_BLK_LENGTH);
        }
        else
        {
            PDATA_WORD(1) = PDATA_WORD(1) - _ROTATION_BLK_LENGTH;
            // blk_num
            PDATA_WORD(2) = PDATA_WORD(1) / _ROTATION_BLK_LENGTH;
            // blk_rem'
            PDATA_WORD(3) = _ROTATION_BLK_LENGTH;
        }

        // Set blk_num
        ScalerSetByte(P20_D1_ROT_DISP_M1_GENERALPICT_NUM, PDATA_WORD(2));
        ScalerSetByte(P60_D1_ROT_DISP_M2_GENERALPICT_NUM, PDATA_WORD(2));

        // Set blk_len (blk_len = blk_len' / blk_w)
        ScalerSetByte(P20_D2_ROT_DISP_M1_GENERALPICT_LEN, (_ROTATION_BLK_LENGTH / _ROTATION_FRC_DISP_BLK_W));
        ScalerSetByte(P60_D2_ROT_DISP_M2_GENERALPICT_LEN, (_ROTATION_BLK_LENGTH / _ROTATION_FRC_DISP_BLK_W));

        // Set blk_rem (blk_rem = blk_rem' / blk_w)
        ScalerSetByte(P20_D3_ROT_DISP_M1_GENERALPICT_REM, (PDATA_WORD(3) / _ROTATION_FRC_DISP_BLK_W));
        ScalerSetByte(P60_D3_ROT_DISP_M2_GENERALPICT_REM, (PDATA_WORD(3) / _ROTATION_FRC_DISP_BLK_W));

        // Set Water Level
        // Water level = FIFO depth - (blk_w * blk_lr) / 2
        // --> blk_w = _ROTATION_FRC_DISP_BLK_W = 4.
        // --> blk_lr = ((blk_num > 0) ? blk_len :blk_rem.
        // FIFO depth = 512 * 128bit
        PDATA_WORD(0) = ((PDATA_WORD(2) > 0) ? (_ROTATION_BLK_LENGTH) : (PDATA_WORD(3) / _ROTATION_FRC_DISP_BLK_W));
        PDATA_WORD(0) = 511 - ((DWORD)_ROTATION_FRC_DISP_BLK_W * PDATA_WORD(0) / 2); // 511: margin

        ScalerSetBit(P20_A0_DISP_M1_WTLVL_H, ~(_BIT0), (pData[0] & 0x01));
        ScalerSetByte(P20_A1_DISP_M1_WTLVL_L, pData[1]);
        ScalerSetBit(P60_A0_DISP_M2_WTLVL_H, ~(_BIT0), (pData[0] & 0x01));
        ScalerSetByte(P60_A1_DISP_M2_WTLVL_L, pData[1]);

        // Set pict_wid
        // ((Hwidth /2)*128/64) = Hwidth = pict_num * (GPNum * GPLen + GPRem) + (RPNum * RPLen + RPRem)
        PDATA_WORD(1) = (((usVerSize % 4) != 0) ? (usVerSize + 4 - (usVerSize % 4)) : (usVerSize));
        PDATA_WORD(0) = (DWORD)PDATA_WORD(1) * 2 / _ROTATION_FRC_CAP_BLK_W;

        if(PDATA_WORD(0) < 10)
        {
            // pict_wid = (RPNum * RPLen + RPRem)
            PDATA_WORD(1) = (PDATA_WORD(1) << 1);
            ScalerSetBit(P20_D7_ROT_DISP_M1_PICT_FST_WID_H, ~(_BIT2 | _BIT1 | _BIT0), (pData[2] & 0x07));
            ScalerSetByte(P20_D8_ROT_DISP_M1_PICT_FST_WID_L, (pData[3] & 0xFF));
            ScalerSetBit(P60_D7_ROT_DISP_M2_PICT_FST_WID_H, ~(_BIT2 | _BIT1 | _BIT0), (pData[2] & 0x07));
            ScalerSetByte(P60_D8_ROT_DISP_M2_PICT_FST_WID_L, (pData[3] & 0xFF));
        }
        else
        {
            // pict_wid = (GPNum * GPLen + GPRem)
            PDATA_WORD(0) = _ROTATION_FRC_CAP_BLK_W * 10;
            ScalerSetBit(P20_D7_ROT_DISP_M1_PICT_FST_WID_H, ~(_BIT2 | _BIT1 | _BIT0), (pData[0] & 0x07));
            ScalerSetByte(P20_D8_ROT_DISP_M1_PICT_FST_WID_L, pData[1]);
            ScalerSetBit(P60_D7_ROT_DISP_M2_PICT_FST_WID_H, ~(_BIT2 | _BIT1 | _BIT0), (pData[0] & 0x07));
            ScalerSetByte(P60_D8_ROT_DISP_M2_PICT_FST_WID_L, pData[1]);
        }

        // Set Pic_num
        pData[0] = ScalerGetBit(P20_42_ROT_CAP_M1_PICT_NUM, (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P20_D9_ROT_DISP_M1_PICT_NUM, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pData[0]);
        ScalerSetBit(P60_D9_ROT_DISP_M2_PICT_NUM, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pData[0]);
    }
    else
    {
        // Set Water Level
        // Water level = FIFO depth - disp_wr_len / 2¡C
        PDATA_WORD(0) = 511 - _ROTATION_READ_LENGTH_CW180 / 2;
        ScalerSetBit(P20_A0_DISP_M1_WTLVL_H, ~(_BIT0), (pData[0] & 0x01));
        ScalerSetByte(P20_A1_DISP_M1_WTLVL_L, pData[1]);
        ScalerSetBit(P60_A0_DISP_M2_WTLVL_H, ~(_BIT0), (pData[0] & 0x01));
        ScalerSetByte(P60_A1_DISP_M2_WTLVL_L, pData[1]);
    }

    // Enable M1/M2 Display double buffer
    ScalerSetBit(P20_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(P60_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _INPUT_PATH_M1_M2);
}

//--------------------------------------------------
// Description  : D Domain Source Select
// Input Value  : enumSourceSelect --> D-domain source select
// Output Value : None
//--------------------------------------------------
void ScalerRotationSetDDomainSourceSelect(EnumDDomainSourceSelect enumSourceSelect)
{
    if(enumSourceSelect == _DDOMAIN_SRC_FRAM_FRAME_SYNC_MODE)
    {
        ScalerSetBit(P20_AC_DISP_M1_DISP_CTRL1, ~(_BIT2 | _BIT1), _BIT2);
        ScalerSetBit(P60_AC_DISP_M2_DISP_CTRL1, ~(_BIT2 | _BIT1), _BIT2);
    }
    else
    {
        ScalerSetBit(P20_AC_DISP_M1_DISP_CTRL1, ~(_BIT2 | _BIT1), 0x00);
        ScalerSetBit(P60_AC_DISP_M2_DISP_CTRL1, ~(_BIT2 | _BIT1), 0x00);
    }

    // Apply Double buffer
    ScalerSetBit(P20_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(P60_AD_DISP_STATUS, ~_BIT4, _BIT4);
}

//--------------------------------------------------
// Description  : Rotation Set FRC function enable/disable
// Input Value  : ucSettingPath: path
// Input Value  : bEn: enable/disable
// Output Value : None
//--------------------------------------------------
void ScalerRotationSetFRCEn(EnumFRCOnOff enumCapDispOnOff, bit bEn)
{
    if(bEn == _DISABLE)
    {
        if((enumCapDispOnOff & _FRC_CAPTURE_ONOFF) == _FRC_CAPTURE_ONOFF)
        {
            // Wait _EVENT_IEN_STOP before FRC Capture Disable
            if((ScalerGetBit(P31_A0_I_DB_CTRL0, _BIT7) == 0x00) && (ScalerGetBit(P0_10_M1_VGIP_CTRL, _BIT0) == _BIT0))
            {
                ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_STOP, _INPUT_PATH_M1_M2);
            }

            // Disable Capture Block
            ScalerSetBit(P20_27_CAP_M1_DDR_CTRL1, ~(_BIT7), 0x00);
            ScalerSetBit(P60_27_CAP_M2_DDR_CTRL1, ~(_BIT7), 0x00);
        }

        if((enumCapDispOnOff & _FRC_DISPLAY_ONOFF) == _FRC_DISPLAY_ONOFF)
        {
            // Disable Display Block
            ScalerSetBit(P20_AC_DISP_M1_DISP_CTRL1, ~(_BIT0), 0x00);
            ScalerSetBit(P60_AC_DISP_M2_DISP_CTRL1, ~(_BIT0), 0x00);
        }
    }
    else
    {
        if((enumCapDispOnOff & _FRC_CAPTURE_ONOFF) == _FRC_CAPTURE_ONOFF)
        {
            ScalerSetBit(P20_27_CAP_M1_DDR_CTRL1, ~(_BIT7), _BIT7);
            ScalerSetBit(P60_27_CAP_M2_DDR_CTRL1, ~(_BIT7), _BIT7);
        }

        if((enumCapDispOnOff & _FRC_DISPLAY_ONOFF) == _FRC_DISPLAY_ONOFF)
        {
            ScalerSetBit(P20_AC_DISP_M1_DISP_CTRL1, ~(_BIT0), _BIT0);
            ScalerSetBit(P60_AC_DISP_M2_DISP_CTRL1, ~(_BIT0), _BIT0);
        }
    } // End of if(bEn == _DISABLE)

    // Enable Double buffer
    ScalerSetBit(P20_AD_DISP_STATUS, ~(_BIT4), _BIT4);
    ScalerSetBit(P60_AD_DISP_STATUS, ~(_BIT4), _BIT4);

    if(((enumCapDispOnOff & _FRC_DISPLAY_ONOFF) != 0) && (ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0))
    {
        // Wait double buffer
        ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _INPUT_PATH_M1_M2);
    }

    if(bEn == _DISABLE)
    {
        // Disable Rotation Control
        ScalerRotationSetControl(_ROT_DISABLE);
    }
}

//--------------------------------------------------
// Description  : Set Rotation Control
// Input Value  : enumRotationType, bEn --> Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerRotationSetControl(EnumRotationType enumRotationType)
{
    switch(enumRotationType)
    {
        case _ROT_DISABLE:
        default:

            ScalerSetBit(P20_38_ROT_CAP_M1_CTRL1, ~(_BIT6 | _BIT5), 0x00);
            ScalerSetBit(P60_38_ROT_CAP_M2_CTRL1, ~(_BIT6 | _BIT5), 0x00);

            ScalerSetBit(P20_38_ROT_CAP_M1_CTRL1, ~_BIT7, 0x00);
            ScalerSetBit(P60_38_ROT_CAP_M2_CTRL1, ~_BIT7, 0x00);
            break;

        case _ROT_CW90:

            ScalerSetBit(P20_38_ROT_CAP_M1_CTRL1, ~(_BIT6 | _BIT5), _BIT5);
            ScalerSetBit(P60_38_ROT_CAP_M2_CTRL1, ~(_BIT6 | _BIT5), _BIT5);

            ScalerSetBit(P20_38_ROT_CAP_M1_CTRL1, ~_BIT7, _BIT7);
            ScalerSetBit(P60_38_ROT_CAP_M2_CTRL1, ~_BIT7, _BIT7);
            break;

        case _ROT_CW180:
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _ROT_HOR_MIRROR:
#endif

            ScalerSetBit(P20_38_ROT_CAP_M1_CTRL1, ~(_BIT6 | _BIT5), _BIT6);
            ScalerSetBit(P60_38_ROT_CAP_M2_CTRL1, ~(_BIT6 | _BIT5), _BIT6);

            ScalerSetBit(P20_38_ROT_CAP_M1_CTRL1, ~_BIT7, _BIT7);
            ScalerSetBit(P60_38_ROT_CAP_M2_CTRL1, ~_BIT7, _BIT7);
            break;

        case _ROT_CW270:

            ScalerSetBit(P20_38_ROT_CAP_M1_CTRL1, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
            ScalerSetBit(P60_38_ROT_CAP_M2_CTRL1, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

            ScalerSetBit(P20_38_ROT_CAP_M1_CTRL1, ~_BIT7, _BIT7);
            ScalerSetBit(P60_38_ROT_CAP_M2_CTRL1, ~_BIT7, _BIT7);
            break;
    }
}

//--------------------------------------------------
// Description  : Set Rotation 90 & 270
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerRotationDisplayCtrlCW90CW270(void)
{
    // Set M1/M2 Read Start Address
    ScalerSetDWord(P20_80_DISP_M1_READ_ADDR_MSB, 0x00);
    ScalerSetDWord(P20_84_DISP_M1_BL2_ADDR_MSB, 0x00);
    ScalerSetDWord(P20_88_DISP_M1_BL3_ADDR_MSB, 0x00);
    ScalerSetDWord(P60_80_DISP_M2_READ_ADDR_MSB, 0x00);
    ScalerSetDWord(P60_84_DISP_M2_BL2_ADDR_MSB, 0x00);
    ScalerSetDWord(P60_88_DISP_M2_BL3_ADDR_MSB, 0x00);
}

//--------------------------------------------------
// Description  : Set Rotation 180
// Input Value  : line step/ block step/ Versize
// Output Value : None
//--------------------------------------------------
void ScalerRotationDisplayCtrlCW180(StructMemoryLineBlockStep stStep, WORD usVerSize)
{
    // M1 Disp = M2 start - line num + 1
    // M2 Disp = M1 start - line num + 1
    DWORD ulDisp_addr = 0;
    DWORD ulFrame = (stStep.ulLineStep * (usVerSize - 1));

    if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
    {
        ulDisp_addr = (stStep.ulBlockStep * 4 - ulFrame);
    }
    else
    {
        ulDisp_addr = (stStep.ulBlockStep - ulFrame) - (stStep.ulLineStep >> 1);
    }

    ScalerMaskSetDWord(P20_80_DISP_M1_READ_ADDR_MSB, 0xF0000000, ulDisp_addr);
    ScalerMaskSetDWord(P20_84_DISP_M1_BL2_ADDR_MSB, 0xF0000000, ulDisp_addr + stStep.ulBlockStep);
    ScalerMaskSetDWord(P20_88_DISP_M1_BL3_ADDR_MSB, 0xF0000000, ulDisp_addr + stStep.ulBlockStep * 2);

    ulDisp_addr = (stStep.ulBlockStep - ulFrame);

    ScalerMaskSetDWord(P60_80_DISP_M2_READ_ADDR_MSB, 0xF0000000, ulDisp_addr);
    ScalerMaskSetDWord(P60_84_DISP_M2_BL2_ADDR_MSB, 0xF0000000, ulDisp_addr + stStep.ulBlockStep);
    ScalerMaskSetDWord(P60_88_DISP_M2_BL3_ADDR_MSB, 0xF0000000, ulDisp_addr + stStep.ulBlockStep * 2);
}

#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Left/ Right Mirror
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerRotationDisplayCtrlLRMirror(void)
{
    DWORD ulDisp_addr1 = 0;
    DWORD ulDisp_addr2 = 0;
    DWORD ulDisp_addr3 = 0;
    DWORD ulLineStep = (ScalerGetDWord(P20_99_DISP_M1_LINE_STEP_MSB) & 0x0FFFFFFF);

    // M1
    ulDisp_addr1 = ScalerGetDWord(P20_00_CAP_M1_MEM_ADDR_MSB);
    ulDisp_addr2 = ScalerGetDWord(P20_04_CAP_M1_BL2_ADDR_MSB);
    ulDisp_addr3 = ScalerGetDWord(P20_08_CAP_M1_BL3_ADDR_MSB);

    ScalerMaskSetDWord(P20_80_DISP_M1_READ_ADDR_MSB, 0xF0000000, ulDisp_addr1);
    ScalerMaskSetDWord(P20_84_DISP_M1_BL2_ADDR_MSB, 0xF0000000, ulDisp_addr2);
    ScalerMaskSetDWord(P20_88_DISP_M1_BL3_ADDR_MSB, 0xF0000000, ulDisp_addr3);

    // M2
    if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
    {
        ulDisp_addr1 = ScalerGetDWord(P60_00_CAP_M2_MEM_ADDR_MSB);
        ulDisp_addr2 = ScalerGetDWord(P60_04_CAP_M2_BL2_ADDR_MSB);
        ulDisp_addr3 = ScalerGetDWord(P60_08_CAP_M2_BL3_ADDR_MSB);
    }
    else
    {
        ulDisp_addr1 = ulDisp_addr1 - (ulLineStep >> 1);
        ulDisp_addr2 = ulDisp_addr2 - (ulLineStep >> 1);
        ulDisp_addr3 = ulDisp_addr3 - (ulLineStep >> 1);
    }

    ScalerMaskSetDWord(P60_80_DISP_M2_READ_ADDR_MSB, 0xF0000000, ulDisp_addr1);
    ScalerMaskSetDWord(P60_84_DISP_M2_BL2_ADDR_MSB, 0xF0000000, ulDisp_addr2);
    ScalerMaskSetDWord(P60_88_DISP_M2_BL3_ADDR_MSB, 0xF0000000, ulDisp_addr3);

    // Set M1/M2 Line Step
    ScalerMaskSetDWord(P20_99_DISP_M1_LINE_STEP_MSB, 0xF0000000, ((~ulLineStep) + 1));
    ScalerMaskSetDWord(P60_99_DISP_M2_LINE_STEP_MSB, 0xF0000000, ((~ulLineStep) + 1));
}
#endif
#endif // End of #if(_DISPLAY_ROTATION_SUPPORT == _ON)
