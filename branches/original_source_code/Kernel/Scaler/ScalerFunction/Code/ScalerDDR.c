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
// ID Code      : ScalerDDR.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DDR__

#include "ScalerFunctionInclude.h"

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// DDR3 Data Rate
//--------------------------------------------------
#define _DDR3_DATA_RATE_1333M                               1333
#define _DDR3_DATA_RATE_1066M                               1066
#define _DDR3_DATA_RATE_800M                                800


#if(_DDR3_PHASE_CALIBRATION == _ON)

#define _TOTAL_PHASE_NUM                                    64
#define _SEARCH_PHASE_POLLING_TIMEOUT                       45

//--------------------------------------------------
// DDR3 Search Phase - Iteration
//--------------------------------------------------
#define _SEARCH_PHASE_MAX_ITERATION_NUM                     6
#define _SEARCH_PHASE_ITERATION_CONVERGE_THESHOLD           2

//--------------------------------------------------
// DDR3 Search Phase - Write Leveling
//--------------------------------------------------
#define _SEARCH_PHASE_WRITE_LEVELING                        _ON

//--------------------------------------------------
// DDR3 Search Phase - Debug Message of Phase Check
//--------------------------------------------------
#define _SEARCH_PHASE_DEBUG_MSG_OF_PHASE_CHECK              _OFF
#define _SEARCH_PHASE_DEBUG_MSG_OF_WRITE_LEVELING           _OFF


#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_MCU_MODE)
//--------------------------------------------------
// DDR3 Search Phase - MCU Mode
//--------------------------------------------------
#define _MCU_DDR3_DMA_CMD_NOP                               0
#define _MCU_DDR3_DMA_CMD_WRITE                             4
#define _MCU_DDR3_DMA_CMD_READ                              5

#define _MCU_DDR3_DMA_CONFIG_ONE_DDR                        0
#define _MCU_DDR3_DMA_CONFIG_TWO_DDR                        1

#define _MCU_DDR3_DMA_CONFIG_BURST_LEN_2                    2
#define _MCU_DDR3_DMA_CONFIG_BURST_LEN_4                    4

#endif


//--------------------------------------------------
// Macros for DDR Search Phase
//--------------------------------------------------
#define SET_SCAN_RESULT(ucResultArray, ucIndex, ucResult)   (*((BYTE xdata *)((ucResultArray) + ((ucIndex) / 8))) =\
                                                             (*((BYTE xdata *)((ucResultArray) + ((ucIndex) / 8))) & ~(1 << ((ucIndex) % 8))) | (((BYTE)(ucResult)) << ((ucIndex) % 8)))

#define GET_SCAN_RESULT(ucResultArray, ucIndex)             ((*((BYTE xdata *)((ucResultArray) + ((ucIndex) / 8))) & (1 << ((ucIndex) % 8))) >> ((ucIndex) % 8))

#define PHASE_DIFF(ucPhaseTo, ucPhaseFrom)                  (((ucPhaseTo) + _TOTAL_PHASE_NUM - (ucPhaseFrom)) % _TOTAL_PHASE_NUM)

#endif

#if((_DDR3_PHASE_CHECK == _ON) || (_DDR3_PHASE_CALIBRATION == _ON))
//--------------------------------------------------
// DDR Search Phase - Debug Message of Phase Check
//--------------------------------------------------
#define _PHASE_CHECK_DEBUG_MSG                              _ON
#define _TOTAL_CHECK_PHASE_NUM                              (64)
#define _PHASE_CHECK_ITERATION                              (1)
#define _PHASE_CHECK_FRAME_COUNT                            (2)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

#if(_DDR3_PHASE_CALIBRATION == _ON)
//--------------------------------------------------
// DDR3 Search Phase
//--------------------------------------------------
typedef struct
{
    BYTE pucWritePhaseOfClk[6];
    BYTE ucRDQDelayTap;
} StructPhaseInfo;

typedef enum
{
    _PASS_RANGE_GAP_NOT_FOUND,
    _PASS_RANGE_FRONT_GAP_BEGIN_FOUND,
    _PASS_RANGE_FRONT_GAP_END_FOUND,
    _PASS_RANGE_BACK_GAP_BEGIN_FOUND,
} EnumPassRangeGapFindingStatus;

typedef enum
{
    _SCAN_RESULT_WRITE_PHASE,
    _SCAN_RESULT_READ_DELAY_TAP,
} EnumScanResultType;

typedef enum
{
    _PRINT_ITERATION_RESULT,
    _PRINT_FINAL_RESULT,
} EnumPhaseResultPrintType;

#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if((_DDR3_PHASE_CALIBRATION == _ON) && (_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_MCU_MODE))
//--------------------------------------------------
// DDR3 Search Phase
//--------------------------------------------------
BYTE code tDDR_SEARCH_PHASE_TEST_DATA_SEED_EVEN[16] =
{
    0x7C, 0x4D,
    0x39, 0x27,
    0x54, 0x80,
    0xF3, 0xFA,
    0x05, 0xD3,
    0x66, 0x2E,
    0xBC, 0x19,
    0x02, 0x45,
};

BYTE code tDDR_SEARCH_PHASE_TEST_DATA_SEED_ODD[16] =
{
    0x64, 0xF5,
    0x83, 0xC0,
    0xE9, 0x35,
    0x18, 0xA4,
    0xD8, 0x06,
    0x93, 0x5A,
    0x28, 0x84,
    0x37, 0xAA,
};

BYTE code *tDDR_SEARCH_PHASE_TEST_DATA_SEED[] =
{
    tDDR_SEARCH_PHASE_TEST_DATA_SEED_EVEN,
    tDDR_SEARCH_PHASE_TEST_DATA_SEED_ODD,
};

#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

#if(_DDR3_PHASE_CALIBRATION == _ON)
//--------------------------------------------------
// DDR3 Search Phase
//--------------------------------------------------
bit g_bDDRSearchPhaseMCUModeTestDataReset = _FALSE;
bit g_bDDRSearchPhaseDone = _FALSE;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDDR3DCPHYInitial(void);
void ScalerDDR3DCSysInitial(void);
void ScalerDDR3PowerControl(bit bOn);

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
void ScalerDDR3DCSysSetPictureSetInfo(BYTE ucPictNum, BYTE ucPictWidthScale, DWORD ulPictInitPage);
#endif

#if(_DDR3_PHASE_CALIBRATION == _ON)

#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_MCU_MODE)
void ScalerDDR3ScanPhaseMCUModeGenTestData(BYTE *ppucTestData[]);
bit ScalerDDR3PhaseCheckMCUMode(void);
void ScalerDDR3PhaseCalibrationMCUMode(void);
#elif(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE)
bit ScalerDDR3PhaseCheckFRCMode(void);
void ScalerDDR3PhaseCalibrationFRCMode(void);
void ScalerDDR3SearchPhaseFRCModePreprocess(void);
void ScalerDDR3SearchPhaseFRCModePostprocess(void);
void ScalerDDR3ScanPhaseFRCModeDDRClientAccessCtrl(bit bEnable);
#endif

void ScalerDDR3ScanPhaseDDRRelatedBlockReset(void);
void ScalerDDR3ScanPhasePrintSearchPhaseResult(StructPhaseInfo *pstPhaseResult, EnumPhaseResultPrintType enumPrintType);
void ScalerDDR3ScanPhasePrintScanResult(BYTE pucScanResult[8]);
BYTE ScalerDDR3FindCentralValueOfLongestPassRange(BYTE pucScanResult[8], EnumScanResultType enumResultType);
bit ScalerDDR3ScanPhaseResultExistPassRange(BYTE pucScanResult[8]);
bit ScalerDDR3PhaseCheck(void);
void ScalerDDR3PLLOutputCtrl(bit bEnable);
void ScalerDDR3SetWritePhaseReg(BYTE pucPhaseOfClk[6]);
void ScalerDDR3SetReadDQDelayTapReg(BYTE ucRDQDelayTap);
void ScalerDDR3AvoidPadClkDutyIssue(StructPhaseInfo *pstCurrResult);
void ScalerDDR3ExcludePhaseInNoFlyZone(StructPhaseInfo *pstCurrResult);
bit ScalerDDR3ScanPhaseA(StructPhaseInfo *pstPrevResult, StructPhaseInfo *pstCurrResult);

#if(_SEARCH_PHASE_WRITE_LEVELING == _ON)
void ScalerDDR3ScanPhaseWriteLeveling(StructPhaseInfo *pstCurrResult);
BYTE ScalerDDR3ScanPhaseWLFindProperWDQSPhase(BYTE pucWLResult0[8], BYTE pucWLResult1[8]);
#else
bit ScalerDDR3ScanPhaseB(StructPhaseInfo *pstPrevResult, StructPhaseInfo *pstCurrResult);
#endif

bit ScalerDDR3ScanPhaseC(StructPhaseInfo *pstPrevResult, StructPhaseInfo *pstCurrResult);
bit ScalerDDR3ScanPhaseE(StructPhaseInfo *pstCurrResult);
bit ScalerDDR3SearchPhaseConvergenceCheck(StructPhaseInfo *pstPrevResult, StructPhaseInfo *pstCurrResult);
void ScalerDDR3SearchPhase(void);

#endif

#if((_DDR3_PHASE_CHECK == _ON) || (_DDR3_PHASE_CALIBRATION == _ON))
bit ScalerDDR3SCheckFinalPhaseMargin(void);
bit ScalerDDR3SCheckPhase1(void);
bit ScalerDDR3SCheckPhase2(void);
void ScalerDDR3SCheckPhaseSetRelatedBlock(bit bEnable);
void ScalerDDR3CheckPhaseFRCModeDDRClientAccessCtrl(bit bEnable);
void ScalerDDR3CheckMemoryAddressChange(DWORD ulAddress);
void ScalerDDR3CheckSetWritePhaseReg(BYTE pucPhaseOfClk[6]);
void ScalerDDR3CheckPhaseDDRRelatedBlockReset(void);
void ScalerDDR3CheckPLLOutputCtrl(bit bEnable);
void ScalerDDR3CheckSetReadDQDelayTapReg(BYTE ucRDQDelayTap);
bit ScalerDDR3CheckReadWriteFrame(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DC_phy initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3DCPHYInitial(void)
{
    BYTE pucPhaseOfClk[6] = {0};

    DWORD ulWLMuxDQ = 0;
    DWORD ulWLMuxDQOE = 0;
    DWORD ulWLMuxDQS = 0;
    DWORD ulWLMuxDQSOE = 0;

    pucPhaseOfClk[0] = ScalerGetByte(PA5_0B_SYS_PLL_DDR3_4); // refrence Clk
    pucPhaseOfClk[1] = ScalerGetByte(PA5_0A_SYS_PLL_DDR3_3); // Tx Dq01
    pucPhaseOfClk[2] = ScalerGetByte(PA5_09_SYS_PLL_DDR3_2); // Tx Clk
    pucPhaseOfClk[3] = ScalerGetByte(PA5_08_SYS_PLL_DDR3_1); // Tx Dqs01
    pucPhaseOfClk[4] = ScalerGetByte(PA5_0F_SYS_PLL_DDR4_4); // Tx Dqs23
    pucPhaseOfClk[5] = ScalerGetByte(PA5_0E_SYS_PLL_DDR4_3); // Tx Dq23

    //==DC PAD/ZQ/TX Delay Chain Setting ==//
    // DC1 use external REF, ZQ R: 1=external 240ohm;Vref PAD: 1=external;ZQ PAD: 1=power down
    ScalerSetDWord(PA9_24_PAD_ZCTRL_OVRD1, 0x13000000);

    // Trim mode
    ScalerSetDWord(PAB_30_ZQCMP1, 0x0000000b);
    ScalerTimerDelayXms(5);

    // DC1 ZQ Calibration setting use external VREF
    ScalerSetDWord(PA9_24_PAD_ZCTRL_OVRD1, 0x13000000);

    // ZQ group sel=0, all update on refresh cycle
    ScalerSetDWord(PAC_60_ZQ_SEL0_1, 0x00370000);

    // all update after ZQ calibration done
    ScalerSetDWord(PAC_64_ZQ_SEL1_1, 0xffff03ff);
    ScalerSetDWord(PAC_68_ZQ_SEL2_1, 0x000000ff);
    ScalerTimerDelayXms(5);

    // ZQ R: 1=external 240ohm;Vref PAD: 1=external;ZQ PAD: 1=normal
    ScalerSetDWord(PA9_24_PAD_ZCTRL_OVRD1, 0x12000000);

    //For PUPD3, the signals are divided into groups//
    // choose dqs0/1/2/3 and dqs_b0/1/2/3 PMOS to group1, others default is group0
    ScalerSetDWord(PAC_78_ZQGRPSEL3_1, 0x21122112);
    // choose dqs0/1/2/3 and dqs_b0/1/2/3 NMOS to group2, others default is group0
    ScalerSetDWord(PAC_7C_ZQGRPSEL2_1, 0x21122112);
    // choose update which PADs
    ScalerSetDWord(PAC_64_ZQ_SEL1_1, 0xFFFF03FF);
    ScalerSetDWord(PAC_68_ZQ_SEL2_1, 0x000000FF);

    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        // K group 0,OCD 40,ODT 60,ZQ calibration enable
        ScalerSetDWord(PAC_60_ZQ_SEL0_1, 0x00000000);
        ScalerSetDWord(PA9_28_PAD_CTRL_PROG1, 0x42018aaa);
        ScalerSetDWord(PA9_28_PAD_CTRL_PROG1, 0x43018aaa);

        // Wait for Calibration Done
        ScalerTimerPollingFlagProc(5, PA9_2C_PAD_ZCTRL_STATUS1, _BIT7, _TRUE);

        // If auto K compelted with no error
        if((ScalerGetBit(PA9_2C_PAD_ZCTRL_STATUS1, _BIT6) == 0x00))
        {
            break;
        }
    }

    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        // K group 1, OCD 40,ODT 90, ZQ calibration enable
        ScalerSetDWord(PAC_60_ZQ_SEL0_1, 0x00000001);
        ScalerSetDWord(PA9_28_PAD_CTRL_PROG1, 0x42010aaa);
        ScalerSetDWord(PA9_28_PAD_CTRL_PROG1, 0x43010aaa);

        // Wait for Calibration Done
        ScalerTimerPollingFlagProc(5, PA9_2C_PAD_ZCTRL_STATUS1, _BIT7, _TRUE);

        if((ScalerGetBit(PA9_2C_PAD_ZCTRL_STATUS1, _BIT6) == 0x00))
        {
            break;
        }
    }

    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        // K group 2,OCD 40,ODT 60, ZQ calibration enable
        ScalerSetDWord(PAC_60_ZQ_SEL0_1, 0x00000002);
        ScalerSetDWord(PA9_28_PAD_CTRL_PROG1, 0x42018aaa);
        ScalerSetDWord(PA9_28_PAD_CTRL_PROG1, 0x43018aaa);

        // Wait for Calibration Done
        ScalerTimerPollingFlagProc(5, PA9_2C_PAD_ZCTRL_STATUS1, _BIT7, _TRUE);

        if((ScalerGetBit(PA9_2C_PAD_ZCTRL_STATUS1, _BIT6) == 0x00))
        {
            break;
        }
    }

    // DC1 PAD OE
    ScalerSetDWord(PA9_10_PAD_OE_CTL1, 0x00000F8E);
    ScalerSetDWord(PA9_18_PAD_IDDQ0_1, 0x00000000);
    ScalerTimerDelayXms(5);

    // DC1 TX delay Chain adjustment
    ScalerSetDWord(PA9_30_DQ_DLY_SEL0_1, 0x00000000);
    ScalerSetDWord(PA9_34_DQ_DLY_SEL1_1, 0x00000000);
    ScalerSetDWord(PA9_38_DQ_DLY_SEL2_1, 0x00000000);
    ScalerSetDWord(PA9_3C_DQ_DLY_SEL3_1, 0x00000000);
    ScalerSetDWord(PA9_0C_FIFO_DLYN1, 0x00000010);


    //== DC1 Timing Setting Start ==//
#if(_MEMORY_DATA_RATE_SPEED > _DDR3_DATA_RATE_1333M) // 1600 setting

    ScalerSetDWord(PA8_00_TMCTRL0, 0x001CB816);
    ScalerSetDWord(PA8_04_TMCTRL1_1, 0x060A0A22);
    ScalerSetDWord(PA8_08_TMCTRL2_1, 0x0207070C);

#if((_MEMORY_SIZE_CONFIG & _MEMORY_DENSITY_MASK) == _MEMORY_DENSITY_64M_16)
    ScalerSetDWord(PA8_0C_TMCTRL3_1, 0x20017050);
#elif((_MEMORY_SIZE_CONFIG & _MEMORY_DENSITY_MASK) == _MEMORY_DENSITY_128M_16)
    ScalerSetDWord(PA8_0C_TMCTRL3_1, 0x20017075);
#elif((_MEMORY_SIZE_CONFIG & _MEMORY_DENSITY_MASK) == _MEMORY_DENSITY_256M_16)
    ScalerSetDWord(PA8_0C_TMCTRL3_1, 0x200170D5);
#endif

    ScalerSetDWord(PA8_10_TMCTRL4_1, 0x01010D03);
    ScalerSetDWord(PA8_14_TMCTRL5_1, 0x02200400);
    ScalerSetDWord(PA8_18_TMCTRL6_1, 0x96240080);
    ScalerSetDWord(PA8_44_MOD_REG_1, 0x00060F71);
    ScalerSetDWord(PA8_48_MOD23_REG_1, 0x00000018);

#elif((_MEMORY_DATA_RATE_SPEED > _DDR3_DATA_RATE_1066M) && (_MEMORY_DATA_RATE_SPEED <= _DDR3_DATA_RATE_1333M)) // 1333 setting

    ScalerSetDWord(PA8_00_TMCTRL0, 0x00179712);
    ScalerSetDWord(PA8_04_TMCTRL1_1, 0x0608081B);
    ScalerSetDWord(PA8_08_TMCTRL2_1, 0x0206070A);
    ScalerSetDWord(PA8_0C_TMCTRL3_1, 0x19014050);
    ScalerSetDWord(PA8_10_TMCTRL4_1, 0x02020D02);
    ScalerSetDWord(PA8_14_TMCTRL5_1, 0x02200400);
    ScalerSetDWord(PA8_18_TMCTRL6_1, 0x92240080);
    ScalerSetDWord(PA8_44_MOD_REG_1, 0x00060B51);
    ScalerSetDWord(PA8_48_MOD23_REG_1, 0x00000010);

#elif((_MEMORY_DATA_RATE_SPEED > _DDR3_DATA_RATE_800M) && (_MEMORY_DATA_RATE_SPEED <= _DDR3_DATA_RATE_1066M)) // 1066 setting

    ScalerSetDWord(PA8_00_TMCTRL0, 0x0012760E);
    ScalerSetDWord(PA8_04_TMCTRL1_1, 0x04060616);
    ScalerSetDWord(PA8_08_TMCTRL2_1, 0x02050407);
    ScalerSetDWord(PA8_0C_TMCTRL3_1, 0x14010031);
    ScalerSetDWord(PA8_10_TMCTRL4_1, 0x00000C02);
    ScalerSetDWord(PA8_14_TMCTRL5_1, 0x02100200);
    ScalerSetDWord(PA8_18_TMCTRL6_1, 0x8E200040);
    ScalerSetDWord(PA8_44_MOD_REG_1, 0x00060931);
    ScalerSetDWord(PA8_48_MOD23_REG_1, 0x00000008);

#else // 800 setting

    ScalerSetDWord(PA8_00_TMCTRL0, 0x000D550A);
    ScalerSetDWord(PA8_04_TMCTRL1_1, 0x0204040F);
    ScalerSetDWord(PA8_08_TMCTRL2_1, 0x02040305);
    ScalerSetDWord(PA8_0C_TMCTRL3_1, 0x1300C022);
    ScalerSetDWord(PA8_10_TMCTRL4_1, 0x00000C02);
    ScalerSetDWord(PA8_14_TMCTRL5_1, 0x02100200);
    ScalerSetDWord(PA8_18_TMCTRL6_1, 0x8A200040);
    ScalerSetDWord(PA8_44_MOD_REG_1, 0x00060511);
    ScalerSetDWord(PA8_48_MOD23_REG_1, 0x00000000);

#endif

    ScalerTimerDelayXms(5);
    ScalerSetDWord(PA8_20_ODT_CTRL0_1, 0x08000fff);
    //== DC1 Timing Setting End ==//

    ScalerSetDWord(PA8_2C_DC_MIS_1, 0x00000011);
    ScalerSetDWord(PA8_30_DC_MISA_1, 0x00000000);
    ScalerSetDWord(PA8_34_DC_MISB_1, 0x10000000);
    //== Read DQS detection Setting ==//
    // PUPD2 Setting
    ScalerSetDWord(PAB_00_PAD_BUS_01, 0x28282828);
    ScalerSetDWord(PA9_4C_PUPD_DLY_NUM1, 0x07330000);
    ScalerSetDWord(PA9_50_DQS_DLYN1, 0x00000000);
    ScalerSetDWord(PA9_44_HALF_CYCLE_CAL_EN1, 0x00000001);
    ScalerSetDWord(PAF_94_DQS_COMPHL_DLY1, 0x00007777);

    // DQS_CAL0~3 setting
    ScalerSetDWord(PAA_50_DQS_CAL31, 0x800011f3);
    ScalerSetDWord(PAA_54_DQS_CAL21, 0x800011f3);
    ScalerSetDWord(PAA_58_DQS_CAL11, 0x800011f3);
    ScalerSetDWord(PAA_5C_DQS_CAL01, 0x800011f3);
    ScalerSetDWord(PA9_54_CAL_MODE1, 0x00000001);       // setting from DV , bit13:1 is pupd1 on;0 is pupd2 on;

    //=================================
    // WL_Mux Settings
    //=================================
    // 1st DDR3: wDQS01, wDQ_0~15
    if(pucPhaseOfClk[3] <= 15)
    {
        ulWLMuxDQS |= 0x00000011;
        ulWLMuxDQSOE |= 0x00000011;

        ulWLMuxDQ |= (pucPhaseOfClk[1] <= 15) ? 0x00000000 :
                     (((pucPhaseOfClk[1] >= 16) && (pucPhaseOfClk[1] <= 47)) ? 0x00000011 : 0x00000022);
        ulWLMuxDQOE |= (pucPhaseOfClk[1] <= 15) ? 0x00000000 :
                       (((pucPhaseOfClk[1] >= 16) && (pucPhaseOfClk[1] <= 47)) ? 0x00000011 : 0x00000022);
    }
    else if((pucPhaseOfClk[3] >= 16) && (pucPhaseOfClk[3] <= 47))
    {
        ulWLMuxDQS |= 0x00000022;
        ulWLMuxDQSOE |= 0x00000022;

        ulWLMuxDQ |= (pucPhaseOfClk[1] <= 15) ? 0x00000000 :
                     (((pucPhaseOfClk[1] >= 16) && (pucPhaseOfClk[1] <= 47)) ? 0x00000011 : 0x00000022);
        ulWLMuxDQOE |= (pucPhaseOfClk[1] <= 15) ? 0x00000000 :
                       (((pucPhaseOfClk[1] >= 16) && (pucPhaseOfClk[1] <= 47)) ? 0x00000011 : 0x00000022);
    }
    else // ((ucPhaseOfClk[3] >= 48) && (ucPhaseOfClk[3] <= 63))
    {
        ulWLMuxDQS |= 0x00000011;
        ulWLMuxDQSOE |= 0x00000011;

        ulWLMuxDQ |= (pucPhaseOfClk[1] <= 15) ? 0x00000000 :
                     (((pucPhaseOfClk[1] >= 16) && (pucPhaseOfClk[1] <= 47)) ? 0x00000011 : 0x00000000);
        ulWLMuxDQOE |= (pucPhaseOfClk[1] <= 15) ? 0x00000000 :
                       (((pucPhaseOfClk[1] >= 16) && (pucPhaseOfClk[1] <= 47)) ? 0x00000011 : 0x00000000);
    }

    // 2nd DDR3: wDQS23, wDQ_16~31
    if(pucPhaseOfClk[4] <= 15)
    {
        ulWLMuxDQS |= 0x00001100;
        ulWLMuxDQSOE |= 0x00001100;

        ulWLMuxDQ |= (pucPhaseOfClk[5] <= 15) ? 0x00000000 :
                     (((pucPhaseOfClk[5] >= 16) && (pucPhaseOfClk[5] <= 47)) ? 0x00001100 : 0x00002200);
        ulWLMuxDQOE |= (pucPhaseOfClk[5] <= 15) ? 0x00000000 :
                       (((pucPhaseOfClk[5] >= 16) && (pucPhaseOfClk[5] <= 47)) ? 0x00001100 : 0x00002200);
    }
    else if((pucPhaseOfClk[4] >= 16) && (pucPhaseOfClk[4] <= 47))
    {
        ulWLMuxDQS |= 0x00002200;
        ulWLMuxDQSOE |= 0x00002200;

        ulWLMuxDQ |= (pucPhaseOfClk[5] <= 15) ? 0x00000000 :
                     (((pucPhaseOfClk[5] >= 16) && (pucPhaseOfClk[5] <= 47)) ? 0x00001100 : 0x00002200);
        ulWLMuxDQOE |= (pucPhaseOfClk[5] <= 15) ? 0x00000000 :
                       (((pucPhaseOfClk[5] >= 16) && (pucPhaseOfClk[5] <= 47)) ? 0x00001100 : 0x00002200);
    }
    else // ((ucPhaseOfClk[4] >= 48) && (ucPhaseOfClk[4] <= 63))
    {
        ulWLMuxDQS |= 0x00001100;
        ulWLMuxDQSOE |= 0x00001100;

        ulWLMuxDQ |= (pucPhaseOfClk[5] <= 15) ? 0x00000000 :
                     (((pucPhaseOfClk[5] >= 16) && (pucPhaseOfClk[5] <= 47)) ? 0x00001100 : 0x00000000);
        ulWLMuxDQOE |= (pucPhaseOfClk[5] <= 15) ? 0x00000000 :
                       (((pucPhaseOfClk[5] >= 16) && (pucPhaseOfClk[5] <= 47)) ? 0x00001100 : 0x00000000);
    }

    // Set WL_Mux
    ScalerSetDWord(PAC_08_WL_CTRL_21, ulWLMuxDQ);
    ScalerSetDWord(PAC_0C_WL_CTRL_31, ulWLMuxDQOE);
    ScalerSetDWord(PAC_10_WL_CTRL_41, ulWLMuxDQS);
    ScalerSetDWord(PAC_14_WL_CTRL_51, ulWLMuxDQSOE);

    // DC1 Read Phase and on the fly calibration
    ScalerSetDWord(PA8_38_DC_MISC_1, 0x07000000);
    ScalerSetDWord(PA9_08_CAL_CTRL1, 0x000000A1);

    // DC1 FIFO CTRL
    ScalerSetDWord(PA8_4C_RFIFO_CTL_1, 0x00000030);
#if(_MEMORY_DATA_RATE_SPEED > _DDR3_DATA_RATE_1333M) // 1600 setting
    ScalerSetDWord(PA9_04_READ_COM_CTRL1, 0x00026880);
#else
    ScalerSetDWord(PA9_04_READ_COM_CTRL1, 0x00023880);
#endif

    // DC1 init
    ScalerSetDWord(PA8_40_DC_DDR3_CTL_1, 0x00000003); // DRAM init
    ScalerTimerDelayXms(2);

    ScalerSetDWord(PA8_40_DC_DDR3_CTL_1, 0x03000000); // end 200us
    ScalerTimerDelayXms(2);

    ScalerSetDWord(PA8_40_DC_DDR3_CTL_1, 0x0c000000); // end 500us
    ScalerTimerDelayXms(5);

    // Add FW solution to fix HW issue
    ScalerSetDWord(PA8_40_DC_DDR3_CTL_1, 0x0A000000);

    ScalerSetDWord(PA9_7C_SYNC_RST_FIFO_PT1, 0x00000001); // sync Reset FIFO

    // Wait for DDR Sync Reset
    ScalerTimerPollingFlagProc(80, PA9_7F_SYNC_RST_FIFO_PT4, _BIT0, _FALSE);
}

//--------------------------------------------------
// Description  : DC Sys initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3DCSysInitial(void)
{
    // ------- Set PA0_04_DC_SYS_MISC -----
    // (_BIT4 | _BIT3 | _BIT2 | _BIT1): Set 1'b1 when using 8G/4G/2G DRAM. DC_sys will use page[n] as bank[2].
    // _BIT0: Set 1'b1 for new pre-arbitration scheme or 1'b0 for the original one.
    // ------- Set PA0_05_DC_SYS_MISC -----
    // _BIT7: Set 1'b1 to disable ve command grouping.
    // _BIT6: Set 1'b1 to enable address mapping of DDR3.
    // _BIT4: Set self_lookback_mode
    // _BIT3: Set DDR number : 0=One-DDR ; 1=Two-DDR.
    // _BIT2: Set pict_offset_en
    // (_BIT1 | _BIT0): Page size selection: 00=512bytes, 01=1024bytes, 10=2048bytes, 11=4096bytes
#if(_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_1PC)
    ScalerMaskSetDWord(PA0_04_DC_SYS_MISC, 0x0000FFFF, 0x00420000);
#elif(_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_2PCS)
    ScalerMaskSetDWord(PA0_04_DC_SYS_MISC, 0x0000FFFF, 0x024B0000);
#elif(_MEMORY_SIZE_CONFIG == _2G_16BIT_GDDR3_1PC)
    ScalerMaskSetDWord(PA0_04_DC_SYS_MISC, 0x0000FFFF, 0x02420000);
#elif(_MEMORY_SIZE_CONFIG == _2G_16BIT_GDDR3_2PCS)
    ScalerMaskSetDWord(PA0_04_DC_SYS_MISC, 0x0000FFFF, 0x084B0000);
#elif(_MEMORY_SIZE_CONFIG == _4G_16BIT_GDDR3_1PC)
    ScalerMaskSetDWord(PA0_04_DC_SYS_MISC, 0x0000FFFF, 0x08420000);
#elif(_MEMORY_SIZE_CONFIG == _4G_16BIT_GDDR3_2PCS)
    ScalerMaskSetDWord(PA0_04_DC_SYS_MISC, 0x0000FFFF, 0x104B0000);
#endif

    // ------- Set PA0_2F_DC_SYS_MISC3 - _BIT3 -----
    // Set 1 to enable bank[2] remap function
    ScalerMaskSetDWord(PA0_2C_DC_SYS_MISC3, 0xFFFFFFF7, 0x08);

    // Request ID: Client2 = System bridge.
    // ------- Set PA0_4A_DC_PRIORITY_c2 / PA0_4B_DC_PRIORITY_c2 -----
    // Set C2-client priority count end/begin value.
    ScalerMaskSetDWord(PA0_48_DC_PRIORITY_C2, 0xFFFF0000, 0xF0FE);

    // Request ID: Client7 = MCU
    // ------- Set PA0_5E_DC_PRIORITY_c7 / PA0_5F_DC_PRIORITY_c7 -----
    ScalerMaskSetDWord(PA0_5C_DC_PRIORITY_C7, 0xFFFF0000, 0xF0FE);

    // ------- Set PA0_63_DC_PRIORITY_CNT_PERIO -----
    // Set Priority Counter downconut period.
    // if req=1 , priority count - 1. per (pri_cnt_period+1) clock
    ScalerMaskSetDWord(PA0_60_DC_PRIORITY_CNT_PERIO, 0xFFFFFF00, 0x10);

    // ------- Set pre_tra_rd_cnt[9:0] / pre_tra_wr_cnt[9:0] -----
    // Set PA0_29_DC_SYS_MISC2[3:0] / PA0_2A_DC_SYS_MISC2 / PA0_2B_DC_SYS_MISC2
    ScalerMaskSetDWord(PA0_28_DC_SYS_MISC2, 0xFFF00000, 0x00020080);
}

//--------------------------------------------------
// Description  : DDR Power On/Off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3PowerControl(bit bOn)
{
    if(bOn == _ON)
    {
        // Set MPLL CLK
        ScalerPLLSetMPLLFreq((DWORD)_MEMORY_PLL_CLOCK * 1000);

        // Set DDR PLL CLK
        ScalerPLLSetDDRPLLFreq((DWORD)_MEMORY_DATA_RATE_SPEED * 1000);

        //------------------------------
        // System Bridge Initial
        //------------------------------
        ScalerDDR3SystemBridgeInitial();

        //------------------------------
        // DC Sys Initial
        //------------------------------
        ScalerDDR3DCSysInitial();

        //------------------------------
        // DC PHY Initial
        //------------------------------
        ScalerDDR3DCPHYInitial();


#if((_DDR3_PHASE_CALIBRATION == _ON) && (_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_MCU_MODE))
        ScalerDDR3PhaseCalibrationMCUMode();
#endif
    }
    else
    {
        // DDR PLL Disable CLK output, Reset PLL, Disable PLL
        ScalerSetDWord(PA5_00_SYS_PLL_DDR1_1, 0x000000FC);

        // Power off MPLL
        ScalerSetBit(P0_F8_MPLL_WD, ~_BIT0, _BIT0);
    }
}

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Picture Set Size Information
// Input Value  : ucPictNum --> The Specific Picture Set Index
// Input Value  : ucPictWidthScale --> The Specific Picture Set Width (unit: 256Byte)
// Input Value  : ulPictInitPage  --> The Specific Picture Set Start Address (unit: Row)
// Output Value : None
//--------------------------------------------------
void ScalerDDR3DCSysSetPictureSetInfo(BYTE ucPictNum, BYTE ucPictWidthScale, DWORD ulPictInitPage)
{
    PDATA_DWORD(0) = 0x00;

    // Set PA0_00_DC_PICT_SET
    // Set Picture index number
    pData[0] = ucPictNum;

    // Set PA0_01_DC_PICT_SET[7] = 0
    // Perform write operation
    // Set PA0_01_DC_PICT_SET[6:1]
    // Set Picture width scale. 256byte/unit. Set 0 result in 32.
    pData[1] = (((ucPictWidthScale == 32) ? (0) : (ucPictWidthScale & 0x3F)) << 1);

    // Set PA0_01_DC_PICT_SET[0] / PA0_02_DC_PICT_SET / PA0_03_DC_PICT_SET
    // Set Picture start page number
    pData[1] |= ((ulPictInitPage >> 16) & _BIT0);
    pData[2] = ((ulPictInitPage >> 8) & 0xFF);
    pData[3] = (ulPictInitPage & 0xFF);

    ScalerSetDWord(PA0_00_DC_PICT_SET, PDATA_DWORD(0));
}

#endif // End of #if(_FRC_SUPPORT == _ON)


#if(_DDR3_PHASE_CALIBRATION == _ON)

#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_MCU_MODE)
//--------------------------------------------------
// Description  : Generate test data for DDR search phase check functions
// Input Value  : Pointer of two test data array
// Output Value : None
//--------------------------------------------------
void ScalerDDR3ScanPhaseMCUModeGenTestData(BYTE *ppucTestData[])
{
    static BYTE sucEvenOddFuncPhase = 0;
    BYTE ucTableSel0 = sucEvenOddFuncPhase & _BIT0;
    BYTE ucTableSel1 = (sucEvenOddFuncPhase + 1) & _BIT0;
    BYTE ucDataBufOffset = 0;

    // 16 bytes for keeping raw data, and 1 byte served as
    // temp buffer during circular shift.
    static BYTE spucRawDataA[17];
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
    static BYTE spucRawDataB[17];
#endif


    if(g_bDDRSearchPhaseMCUModeTestDataReset == _TRUE)
    {
        // Initial value of raw data buffer
        for(ucDataBufOffset = 0; ucDataBufOffset < 16; ucDataBufOffset++)
        {
            spucRawDataA[ucDataBufOffset] = tDDR_SEARCH_PHASE_TEST_DATA_SEED[0][ucDataBufOffset];

#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
            spucRawDataB[ucDataBufOffset] = tDDR_SEARCH_PHASE_TEST_DATA_SEED[1][ucDataBufOffset];
#endif
        }

        g_bDDRSearchPhaseMCUModeTestDataReset = _FALSE;
    }
    else
    {
        // Equivalently right circular shift one byte of data in the raw data buffer
        // when calculate next R/W testing data
        spucRawDataA[16] = spucRawDataA[0];
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
        spucRawDataB[16] = spucRawDataB[0];
#endif

        // Generate data for R/W testing
        for(ucDataBufOffset = 0; ucDataBufOffset < 16; ucDataBufOffset++)
        {
            spucRawDataA[ucDataBufOffset] = (BYTE)((((WORD)spucRawDataA[ucDataBufOffset + 1] * (WORD)tDDR_SEARCH_PHASE_TEST_DATA_SEED[ucTableSel0][ucDataBufOffset] + 17 * sucEvenOddFuncPhase) %
                                                    (((WORD)tDDR_SEARCH_PHASE_TEST_DATA_SEED[ucTableSel1][ucDataBufOffset] << 1) + 1)) & 0xFF);


#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
            spucRawDataB[ucDataBufOffset] = (BYTE)((((WORD)spucRawDataB[ucDataBufOffset + 1] * (WORD)tDDR_SEARCH_PHASE_TEST_DATA_SEED[ucTableSel1][ucDataBufOffset] + 17 * sucEvenOddFuncPhase) %
                                                    (((WORD)tDDR_SEARCH_PHASE_TEST_DATA_SEED[ucTableSel0][ucDataBufOffset] << 1) + 1)) & 0xFF);
#endif
        }
    }

    for(ucDataBufOffset = 0; ucDataBufOffset < 16; ucDataBufOffset++)
    {
        ppucTestData[0][ucDataBufOffset] = spucRawDataA[ucDataBufOffset];

#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
        ppucTestData[1][ucDataBufOffset] = spucRawDataB[ucDataBufOffset];
#endif
    }

    sucEvenOddFuncPhase++;
}


//--------------------------------------------------
// Description  : Check DDR R/W correctness with MCU DDR DMA
// Input Value  : None
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerDDR3PhaseCheckMCUMode(void)
{
    // Configurations
    BYTE ucMCUDDRDMAAddrMSB = 0x00;
    BYTE ucMCUDDRDMAAddrH = 0x00;
    BYTE ucMCUDDRDMAAddrM = 0xEA;
    BYTE ucMCUDDRDMAAddrL = 0x36;

    BYTE ucMCUDDRDMACmd = _MCU_DDR3_DMA_CMD_NOP;

#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_1PC)
    BYTE ucMCUDDRDMAConfigDDRNum = _MCU_DDR3_DMA_CONFIG_ONE_DDR;
    BYTE ucMCUDDRDMAConfigBurstLen = _MCU_DDR3_DMA_CONFIG_BURST_LEN_2;
#elif((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
    BYTE ucMCUDDRDMAConfigDDRNum = _MCU_DDR3_DMA_CONFIG_TWO_DDR;
    BYTE ucMCUDDRDMAConfigBurstLen = _MCU_DDR3_DMA_CONFIG_BURST_LEN_4;
#endif

    // Read data buffer
    BYTE pucWriteDataA[16];
    BYTE pucReadDataA[16];
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
    BYTE pucWriteDataB[16];
    BYTE pucReadDataB[16];
#endif

    BYTE *ppucWriteData[] =
    {
        pucWriteDataA,
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
        pucWriteDataB,
#endif
    };

    BYTE ucDataBufRegOffset = 0;

    // Read status flags
    bit bReadDoneA = _TRUE;
    bit bReadDoneB = _TRUE;

    // Phase check result
    bit bPhaseChkResultA = _SUCCESS;
    bit bPhaseChkResultB = _SUCCESS;

    // Set DDR config
    ScalerSetByte(P37_01_MCU_DC_LEN, ((ucMCUDDRDMAConfigDDRNum << 7) | ucMCUDDRDMAConfigBurstLen));

    // Set target memory address
    ScalerSetByte(P37_04_MCU_DC_ADDR_H, ucMCUDDRDMAAddrMSB);
    ScalerSetByte(P37_05_MCU_DC_ADDR_M, ucMCUDDRDMAAddrH);
    ScalerSetByte(P37_06_MCU_DC_ADDR_L, ucMCUDDRDMAAddrM);
    ScalerSetByte(P37_07_MCU_DC_ADDR, ucMCUDDRDMAAddrL);

    //-------------------------------------------------------------------------
    // Prepare Data For Write Test
    //-------------------------------------------------------------------------
    ScalerDDR3ScanPhaseMCUModeGenTestData(ppucWriteData);

    //-------------------------------------------------------------------------
    // Write Data
    // ------------------------------------------------------------------------
    // Write data to DDR data buffer
    for(ucDataBufRegOffset = 0; ucDataBufRegOffset < 16; ucDataBufRegOffset++)
    {
        ScalerSetByte((P37_10_MCU_DC_DATABUF_A_00 + ucDataBufRegOffset), pucWriteDataA[ucDataBufRegOffset]);

#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
        ScalerSetByte((P37_20_MCU_DC_DATABUF_B_00 + ucDataBufRegOffset), pucWriteDataB[ucDataBufRegOffset]);
#endif
    }

    // Send DDR write request
    ucMCUDDRDMACmd = _MCU_DDR3_DMA_CMD_WRITE;
    ScalerSetByte(P37_00_MCU_DC_CMD, (ucMCUDDRDMACmd << 5));

    // Polling qack of write request
    if(ScalerTimerPollingFlagProc(_SEARCH_PHASE_POLLING_TIMEOUT, P37_00_MCU_DC_CMD, (_BIT7 | _BIT6 | _BIT5), _FALSE) == _FALSE)
    {
        DebugMessageMemoryPhaseCal("DDR3 DMA Write Fail !! Timeout", 0);
    }
    // Delay 5 us to ensure that write process is finished
    Delay5us(g_ucDelay5usN);


    //-------------------------------------------------------------------------
    // Read Data
    // ------------------------------------------------------------------------
    // Read data buffer to clear uncleared ready-to-read flag (if it exists).
    for(ucDataBufRegOffset = 0; ucDataBufRegOffset < 16; ucDataBufRegOffset++)
    {
        pucReadDataA[ucDataBufRegOffset] = ScalerGetByte((P37_10_MCU_DC_DATABUF_A_00 + ucDataBufRegOffset));
        pucReadDataA[ucDataBufRegOffset] = 0x00;

#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
        pucReadDataB[ucDataBufRegOffset] = ScalerGetByte((P37_20_MCU_DC_DATABUF_B_00 + ucDataBufRegOffset));
        pucReadDataB[ucDataBufRegOffset] = 0x00;
#endif
    }

    // Send DDR read request
    ucMCUDDRDMACmd = _MCU_DDR3_DMA_CMD_READ;
    ScalerSetByte(P37_00_MCU_DC_CMD, (ucMCUDDRDMACmd << 5));

    // Polling ready-to-read flag
    bReadDoneA = ScalerTimerPollingFlagProc(_SEARCH_PHASE_POLLING_TIMEOUT, P37_34_MCU_DC_READ_FLAG_A, _BIT0, _TRUE);
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
    bReadDoneB = ScalerTimerPollingFlagProc(_SEARCH_PHASE_POLLING_TIMEOUT, P37_35_MCU_DC_READ_FLAG_B, _BIT0, _TRUE);
#endif

    if((bReadDoneA == _FALSE) || (bReadDoneB == _FALSE))
    {
        DebugMessageMemoryPhaseCal("DDR3 DMA Read Fail !! Timeout", 0);
    }
    // Delay 5 us to ensure that read process is finished
    Delay5us(g_ucDelay5usN);


    // Read data from DDR data buffer
    for(ucDataBufRegOffset = 0; ucDataBufRegOffset < 16; ucDataBufRegOffset++)
    {
        pucReadDataA[ucDataBufRegOffset] = ScalerGetByte((P37_10_MCU_DC_DATABUF_A_00 + ucDataBufRegOffset));

#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
        pucReadDataB[ucDataBufRegOffset] = ScalerGetByte((P37_20_MCU_DC_DATABUF_B_00 + ucDataBufRegOffset));
#endif
    }

    //-------------------------------------------------------------------------
    // Compare read data with writed data
    // ------------------------------------------------------------------------
    bPhaseChkResultA = (memcmp(pucReadDataA, pucWriteDataA, 16) == 0) ? _SUCCESS : _FAIL;
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
    bPhaseChkResultB = (memcmp(pucReadDataB, pucWriteDataB, 16) == 0) ? _SUCCESS : _FAIL;
#endif

    if((bPhaseChkResultA == _SUCCESS) && (bPhaseChkResultB == _SUCCESS))
    {
        return _SUCCESS;
    }
    else
    {
#if(_SEARCH_PHASE_DEBUG_MSG_OF_PHASE_CHECK == _ON)
        // If failed, dump read data
        DebugMessageMemoryPhaseCal("** MCU Phase Check Failed.", 0);

        if(bPhaseChkResultA != _SUCCESS)
        {
            DebugMessageMemoryPhaseCal("Write Data A:", 0);
            DebugMessageMemoryPhaseCal("15~12", (((DWORD)pucWriteDataA[15] << 24) | ((DWORD)pucWriteDataA[14] << 16) | ((DWORD)pucWriteDataA[13] << 8) | pucWriteDataA[12]));
            DebugMessageMemoryPhaseCal("11~08", (((DWORD)pucWriteDataA[11] << 24) | ((DWORD)pucWriteDataA[10] << 16) | ((DWORD)pucWriteDataA[9] << 8) | pucWriteDataA[8]));
            DebugMessageMemoryPhaseCal("07~04", (((DWORD)pucWriteDataA[7] << 24) | ((DWORD)pucWriteDataA[6] << 16) | ((DWORD)pucWriteDataA[5] << 8) | pucWriteDataA[4]));
            DebugMessageMemoryPhaseCal("03~00", (((DWORD)pucWriteDataA[3] << 24) | ((DWORD)pucWriteDataA[2] << 16) | ((DWORD)pucWriteDataA[1] << 8) | pucWriteDataA[0]));

            DebugMessageMemoryPhaseCal("Dump read data A:", 0);
            DebugMessageMemoryPhaseCal("15~12", (((DWORD)pucReadDataA[15] << 24) | ((DWORD)pucReadDataA[14] << 16) | ((DWORD)pucReadDataA[13] << 8) | pucReadDataA[12]));
            DebugMessageMemoryPhaseCal("11~08", (((DWORD)pucReadDataA[11] << 24) | ((DWORD)pucReadDataA[10] << 16) | ((DWORD)pucReadDataA[9] << 8) | pucReadDataA[8]));
            DebugMessageMemoryPhaseCal("07~04", (((DWORD)pucReadDataA[7] << 24) | ((DWORD)pucReadDataA[6] << 16) | ((DWORD)pucReadDataA[5] << 8) | pucReadDataA[4]));
            DebugMessageMemoryPhaseCal("03~00", (((DWORD)pucReadDataA[3] << 24) | ((DWORD)pucReadDataA[2] << 16) | ((DWORD)pucReadDataA[1] << 8) | pucReadDataA[0]));
        }
        else
        {
            DebugMessageMemoryPhaseCal("DDR A Passed", 0);
        }

#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
        if(bPhaseChkResultB != _SUCCESS)
        {
            DebugMessageMemoryPhaseCal("Write Data B:", 0);
            DebugMessageMemoryPhaseCal("15~12", (((DWORD)pucWriteDataB[15] << 24) | ((DWORD)pucWriteDataB[14] << 16) | ((DWORD)pucWriteDataB[13] << 8) | pucWriteDataB[12]));
            DebugMessageMemoryPhaseCal("11~08", (((DWORD)pucWriteDataB[11] << 24) | ((DWORD)pucWriteDataB[10] << 16) | ((DWORD)pucWriteDataB[9] << 8) | pucWriteDataB[8]));
            DebugMessageMemoryPhaseCal("07~04", (((DWORD)pucWriteDataB[7] << 24) | ((DWORD)pucWriteDataB[6] << 16) | ((DWORD)pucWriteDataB[5] << 8) | pucWriteDataB[4]));
            DebugMessageMemoryPhaseCal("03~00", (((DWORD)pucWriteDataB[3] << 24) | ((DWORD)pucWriteDataB[2] << 16) | ((DWORD)pucWriteDataB[1] << 8) | pucWriteDataB[0]));

            DebugMessageMemoryPhaseCal("Dump read data B:", 0);
            DebugMessageMemoryPhaseCal("15~12", (((DWORD)pucReadDataB[15] << 24) | ((DWORD)pucReadDataB[14] << 16) | ((DWORD)pucReadDataB[13] << 8) | pucReadDataB[12]));
            DebugMessageMemoryPhaseCal("11~08", (((DWORD)pucReadDataB[11] << 24) | ((DWORD)pucReadDataB[10] << 16) | ((DWORD)pucReadDataB[9] << 8) | pucReadDataB[8]));
            DebugMessageMemoryPhaseCal("07~04", (((DWORD)pucReadDataB[7] << 24) | ((DWORD)pucReadDataB[6] << 16) | ((DWORD)pucReadDataB[5] << 8) | pucReadDataB[4]));
            DebugMessageMemoryPhaseCal("03~00", (((DWORD)pucReadDataB[3] << 24) | ((DWORD)pucReadDataB[2] << 16) | ((DWORD)pucReadDataB[1] << 8) | pucReadDataB[0]));
        }
        else
        {
            DebugMessageMemoryPhaseCal("DDR B Passed", 0);
        }
#endif // End of #if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)

#endif // End of #if(_SEARCH_PHASE_DEBUG_MSG_OF_PHASE_CHECK == _ON)
        return _FAIL;
    }
}


//--------------------------------------------------
// Description  : DDR search phase MCU Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3PhaseCalibrationMCUMode(void)
{
    if(g_bDDRSearchPhaseDone == _TRUE)
    {
        return;
    }

    //===========================================
    // Process before searching phase
    //===========================================
    // Disable all clients on DDR system bridge
    ScalerSetByte(PA4_03_SB_ARB_CR03, 0x00);
    ScalerSetByte(PA4_04_SB_ARB_CR04, 0x00);

    //===========================================
    // Search phase
    //===========================================
    ScalerDDR3SearchPhase();

    //===========================================
    // Process after searching phase
    //===========================================
    // Resume arbitration of all clients on DDR system bridge
    ScalerSetByte(PA4_03_SB_ARB_CR03, 0x7F);
    ScalerSetByte(PA4_04_SB_ARB_CR04, 0xFF);

    // Search phase done, udate status flag
    g_bDDRSearchPhaseDone = _TRUE;
}


#elif(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE)
//--------------------------------------------------
// Description  : Check DDR R/W correctness with FRC
// Input Value  : None
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerDDR3PhaseCheckFRCMode(void)
{
    BYTE ucCRCRegOffset = 0x00;
    BYTE pucIDomainCRCValue[6];
    BYTE pucMDomainCRCValue[6];

    BYTE ucGlobalDDomainDBCtrlBackup = 0x00;

    //===========================================
    // Set D-domain global DB event = "DVS"
    //===========================================
    // Backup D-domain global DB setting
    ucGlobalDDomainDBCtrlBackup = ScalerGetBit(P31_B0_D_DB_CTRL0, (_BIT7 | _BIT5));
    // Set D-domain global DB event to DVS
    ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT7 | _BIT5), (_BIT7));

    //===========================================
    // Get I-domain CRC
    //===========================================
    // Wait until IEN_STOP
    ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_STOP, _INPUT_PATH_M1_M2);

    // Enable M1, M2 FRC Capture
    ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~_BIT7, _BIT7);
    ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~_BIT7, _BIT7);

    // Enable M1, M2 I-domain CRC output
    ScalerSetByte(P36_00_I_CRC_CTRL, 0x8C);


    // Wait until IEN_START
    ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_START, _INPUT_PATH_M1_M2);

    // Get FRC cap current block num, and set to FRC display block num
    ScalerSetBit(P5_AE_DISP_M1_DISP_CTRL2, ~_BIT3, (ScalerGetBit(P5_2A_CAP_M1_STATUS, _BIT6) >> 3));
    ScalerSetBit(P45_AE_DISP_M2_DISP_CTRL2, ~_BIT3, (ScalerGetBit(P45_2A_CAP_M2_STATUS, _BIT6) >> 3));


    // Wait 1 IVS
    ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);

    // Disable M1_M2 FRC Capture
    ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~_BIT7, 0x00);
    ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~_BIT7, 0x00);

    // Read I-domain CRC (First 3 Bytes of M1 and M2 CRC)
    for(ucCRCRegOffset = 0; ucCRCRegOffset < 3; ucCRCRegOffset++)
    {
        pucIDomainCRCValue[ucCRCRegOffset] = ScalerGetByte(P36_01_I_MAIN1_CRC_1 + ucCRCRegOffset);
        pucIDomainCRCValue[ucCRCRegOffset + 3] = ScalerGetByte(P36_07_I_MAIN2_CRC_1 + ucCRCRegOffset);
    }

    // Disable M1, M2 I-domain CRC output
    ScalerSetByte(P36_00_I_CRC_CTRL, 0x80);

    //===========================================
    // Get M-domain CRC
    //===========================================
    // Wait until DEN_START
    ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_START, _INPUT_PATH_M1_M2);

    // Enable M1, M2 FRC Display
    ScalerSetBit(P5_AE_DISP_M1_DISP_CTRL2, ~_BIT2, _BIT2);
    ScalerSetBit(P5_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(P45_AE_DISP_M2_DISP_CTRL2, ~_BIT2, _BIT2);
    ScalerSetBit(P45_AD_DISP_STATUS, ~_BIT4, _BIT4);

    ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~_BIT0, _BIT0);
    ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~_BIT0, _BIT0);
    // DB apply no polling
    ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT6, _BIT6);

    // Enable M1, M2 M-domain CRC output
    ScalerSetByte(P36_40_M_CRC_CTRL, 0x0C);

    // Wait 1 DVS
    ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _INPUT_PATH_M1_M2);

    // Disable M1, M2 FRC Display
    ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~_BIT0, 0x00);
    ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~_BIT0, 0x00);
    // DB apply no polling
    ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT6, _BIT6);

    // Wait 1 DVS
    ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _INPUT_PATH_M1_M2);

    // Read M-domain CRC (First 3 Bytes of M1 and M2 CRC)
    for(ucCRCRegOffset = 0; ucCRCRegOffset < 3; ucCRCRegOffset++)
    {
        pucMDomainCRCValue[ucCRCRegOffset] = ScalerGetByte(P36_41_M_M1_CRC_1 + ucCRCRegOffset);
        pucMDomainCRCValue[ucCRCRegOffset + 3] = ScalerGetByte(P36_47_M_M2_CRC_1 + ucCRCRegOffset);
    }

    // Disable M1, M2 M-domain CRC output
    ScalerSetByte(P36_40_M_CRC_CTRL, 0x00);

    //===========================================
    // Resume D-domain global DB setting
    //===========================================
    ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT7 | _BIT5), ucGlobalDDomainDBCtrlBackup);

    //===========================================
    // Compare I-domain CRC with  M-domain CRC
    //===========================================
    if(memcmp(pucIDomainCRCValue, pucMDomainCRCValue, 6) == 0)
    {
        return _SUCCESS;
    }
    else
    {
#if(_SEARCH_PHASE_DEBUG_MSG_OF_PHASE_CHECK == _ON)
        // If failed, dump read data
        DebugMessageMemoryPhaseCal("** FRC Phase Check Failed.", 0);

        DebugMessageMemoryPhaseCal("I-domain CRC:", 0);
        pData[0] = 0x00;
        for(ucCRCRegOffset = 0; ucCRCRegOffset < 6; ucCRCRegOffset++)
        {
            pData[(ucCRCRegOffset % 3) + 1] = pucIDomainCRCValue[ucCRCRegOffset];

            if((ucCRCRegOffset % 3) == 2)
            {
                DebugMessageMemoryPhaseCal("=== Dump CRC ===", PDATA_DWORD(0));
            }
        }

        DebugMessageMemoryPhaseCal("M-domain CRC:", 0);
        pData[0] = 0x00;
        for(ucCRCRegOffset = 0; ucCRCRegOffset < 6; ucCRCRegOffset++)
        {
            pData[(ucCRCRegOffset % 3) + 1] = pucMDomainCRCValue[ucCRCRegOffset];

            if((ucCRCRegOffset % 3) == 2)
            {
                DebugMessageMemoryPhaseCal("=== Dump CRC ===", PDATA_DWORD(0));
            }
        }

        DebugMessageMemoryPhaseCal("#####################", 0);
#endif // End of #if(_SEARCH_PHASE_DEBUG_MSG_OF_PHASE_CHECK == _ON)

        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : DDR search phase FRC Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3PhaseCalibrationFRCMode(void)
{
    if(g_bDDRSearchPhaseDone == _TRUE)
    {
        return;
    }

#if(_OD_SUPPORT == _ON)
    //===========================================
    // Disable OD
    //===========================================
    ScalerODEnable(_FUNCTION_OFF);
#endif

    //===========================================
    // Process before searching phase
    //===========================================
    ScalerDDR3SearchPhaseFRCModePreprocess();

    //===========================================
    // Search phase
    //===========================================
    ScalerDDR3SearchPhase();

    //===========================================
    // Process after searching phase
    //===========================================
    ScalerDDR3SearchPhaseFRCModePostprocess();

    // Search phase done, udate status flag
    g_bDDRSearchPhaseDone = _TRUE;

    // Check DDR phase
    ScalerDDR3SCheckFinalPhaseMargin();
}

//--------------------------------------------------
// Description  : Preprocess of DDR search phase FRC mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3SearchPhaseFRCModePreprocess(void)
{
#if(_DDR3_PHASE_CAL_FRC_MODE_INTERNAL_PG == _ON)
    // Enable I-domain random gen
    ScalerSetBit(P0_10_M1_VGIP_CTRL, ~_BIT7, _BIT7);
    ScalerSetBit(P40_10_M2_VGIP_CTRL, ~_BIT7, _BIT7);

    // Set I-domain random gen R != G != B
    ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_10_I_PG_CTRL_0_M1, ~_BIT6, _BIT6);
    ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_10_I_PG_CTRL_0_M2, ~_BIT6, _BIT6);
    // Set I-domain random gen pattern reset num
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_17_PATTERN_RESET_M1, 0xFC);
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_15_INITIAL_RGB_M_M1, 0x1E);
    ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_17_PATTERN_RESET_M2, 0xFF);
#endif

    // Disable I-dither
    ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~_BIT5, 0x00);
    ScalerSetBit(P40_89_I_DITHER_COMMON_CTRL1_M2, ~_BIT5, 0x00);

    // Disable Watch Dog
    ScalerGlobalPathWatchDog(_INPUT_PATH_ALL, _DISABLE);
}


//--------------------------------------------------
// Description  : Postprocess of DDR search phase FRC mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3SearchPhaseFRCModePostprocess(void)
{
#if(_DDR3_PHASE_CAL_FRC_MODE_INTERNAL_PG == _ON)
    // Disable I-domain random gen
    ScalerSetBit(P0_10_M1_VGIP_CTRL, ~_BIT7, 0x00);
    ScalerSetBit(P40_10_M2_VGIP_CTRL, ~_BIT7, 0x00);
    // Clear I-domain random gen pattern reset num
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_17_PATTERN_RESET_M1, 0x00);
    ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_17_PATTERN_RESET_M2, 0x00);
#endif

    // Enable I-dither
    ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~_BIT5, _BIT5);
    ScalerSetBit(P40_89_I_DITHER_COMMON_CTRL1_M2, ~_BIT5, _BIT5);

    // Enable Watch Dog
    ScalerGlobalPathWatchDog(_INPUT_PATH_ALL, _ENABLE);
}

//--------------------------------------------------
// Description  : FRC(M1, M2) client access control
// Input Value  : Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerDDR3ScanPhaseFRCModeDDRClientAccessCtrl(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable M1, M2 FRC Capture
        ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_STOP, _INPUT_PATH_M1_M2);
        ScalerFRCEn(_FRC_CAPTURE_ONOFF, _INPUT_PATH_M1_M2, _ENABLE);

        // Enable M1, M2 FRC Display
        ScalerFRCEn(_FRC_DISPLAY_ONOFF, _INPUT_PATH_M1_M2, _ENABLE);
        ScalerGlobalDDomainDBApply(_DB_APPLY_POLLING);
    }
    else
    {
        // Disable M1, M2, S1 and S2 FRC Capture
        ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_STOP, _INPUT_PATH_M1_M2);
        ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~_BIT7, 0x00);
        ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~_BIT7, 0x00);
        ScalerSetBit(P85_27_CAP_S1_DDR_CTRL1, ~_BIT7, 0x00);
        ScalerSetBit(PC5_27_CAP_S2_DDR_CTRL1, ~_BIT7, 0x00);

        // Disable M1, M2, S1 and S2 FRC Display
        ScalerFRCEn(_FRC_DISPLAY_ONOFF, _INPUT_PATH_ALL, _DISABLE);
        ScalerGlobalDDomainDBApply(_DB_APPLY_POLLING);
    }
}
#endif // End of #if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_MCU_MODE)

//--------------------------------------------------
// Description  : Reset DDR related block (DC Sys, DC Phy, System Bridge..)
// Input Value  : Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerDDR3ScanPhaseDDRRelatedBlockReset(void)
{
    // Set MPLL CLK
    ScalerPLLSetMPLLFreq((DWORD)_MEMORY_PLL_CLOCK * 1000);

    // Reset System Bridge
    ScalerSetBit(P37_A0_M_DOMAIN_SB_RESET, ~_BIT0, _BIT0);
    ScalerTimerDelayXms(2);
    ScalerSetBit(P37_A0_M_DOMAIN_SB_RESET, ~_BIT0, 0x00);
    ScalerTimerDelayXms(2);
    ScalerDDR3SystemBridgeInitial();

    // Reset DC Sys
    ScalerSetBit(P37_A0_M_DOMAIN_SB_RESET, ~_BIT1, _BIT1);
    ScalerTimerDelayXms(2);
    ScalerSetBit(P37_A0_M_DOMAIN_SB_RESET, ~_BIT1, 0x00);
    ScalerTimerDelayXms(2);
    ScalerDDR3DCSysInitial();

    // DDR PLL Disable CLK output, Reset PLL, Disable PLL
    ScalerSetDWord(PA5_00_SYS_PLL_DDR1_1, 0x000000FC);

    // Reset DC Phy
    ScalerSetBit(P37_90_M_DOMAIN_MCLK_SET, ~_BIT2, 0x00);
    ScalerTimerDelayXms(2);
    ScalerSetBit(P37_90_M_DOMAIN_MCLK_SET, ~_BIT2, _BIT2);
    ScalerTimerDelayXms(2);

    // Set DDR PLL CLK
    ScalerPLLSetDDRPLLFreq((DWORD)_MEMORY_DATA_RATE_SPEED * 1000);
}

//--------------------------------------------------
// Description  : Print search phase result
// Input Value  : Array of scan phase result
// Output Value : None
//--------------------------------------------------
void ScalerDDR3ScanPhasePrintSearchPhaseResult(StructPhaseInfo *pstPhaseResult, EnumPhaseResultPrintType enumPrintType)
{
    BYTE ucSyncSel = 0;

    switch(enumPrintType)
    {
        case _PRINT_ITERATION_RESULT:
            DebugMessageMemoryPhaseCal("*******************", 0);
            DebugMessageMemoryPhaseCal("***Search Result***", 0);
            DebugMessageMemoryPhaseCal("***** Clk0 Phase = ", pstPhaseResult->pucWritePhaseOfClk[0]);
            DebugMessageMemoryPhaseCal("***** Clk1 Phase = ", pstPhaseResult->pucWritePhaseOfClk[1]);
            DebugMessageMemoryPhaseCal("***** Clk2 Phase = ", pstPhaseResult->pucWritePhaseOfClk[2]);
            DebugMessageMemoryPhaseCal("***** Clk3 Phase = ", pstPhaseResult->pucWritePhaseOfClk[3]);
            DebugMessageMemoryPhaseCal("***** Clk4 Phase = ", pstPhaseResult->pucWritePhaseOfClk[4]);
            DebugMessageMemoryPhaseCal("***** Clk5 Phase = ", pstPhaseResult->pucWritePhaseOfClk[5]);
            DebugMessageMemoryPhaseCal("** rDQ Delay Tap = ", pstPhaseResult->ucRDQDelayTap);
            DebugMessageMemoryPhaseCal("*******************", 0);
            break;

        case _PRINT_FINAL_RESULT:
            pData[0] = pstPhaseResult->pucWritePhaseOfClk[3];
            pData[1] = pstPhaseResult->pucWritePhaseOfClk[2];
            pData[2] = pstPhaseResult->pucWritePhaseOfClk[1];
            pData[3] = pstPhaseResult->pucWritePhaseOfClk[0];
            DebugMessageMemoryPhaseCal("_DDR3_PLL_INITIAL_PHASE_0 = ", PDATA_DWORD(0));

            // Fast version of "if((16 <= phase <= 31) OR (48 <= phase <= 63)), then corresponding sync sel bit is set to 1"
            ucSyncSel = 0x00;
            ucSyncSel |= (((pstPhaseResult->pucWritePhaseOfClk[0] & _BIT4) == _BIT4) ? _BIT0 : 0x00);
            ucSyncSel |= (((pstPhaseResult->pucWritePhaseOfClk[1] & _BIT4) == _BIT4) ? _BIT1 : 0x00);
            ucSyncSel |= (((pstPhaseResult->pucWritePhaseOfClk[2] & _BIT4) == _BIT4) ? _BIT2 : 0x00);
            ucSyncSel |= (((pstPhaseResult->pucWritePhaseOfClk[3] & _BIT4) == _BIT4) ? _BIT3 : 0x00);
            ucSyncSel |= (((pstPhaseResult->pucWritePhaseOfClk[4] & _BIT4) == _BIT4) ? _BIT4 : 0x00);
            ucSyncSel |= (((pstPhaseResult->pucWritePhaseOfClk[5] & _BIT4) == _BIT4) ? _BIT5 : 0x00);

            pData[0] = ucSyncSel;
            pData[1] = 0x00;
            pData[2] = pstPhaseResult->pucWritePhaseOfClk[5];
            pData[3] = pstPhaseResult->pucWritePhaseOfClk[4];
            DebugMessageMemoryPhaseCal("_DDR3_PLL_INITIAL_PHASE_1 = ", PDATA_DWORD(0));

            pData[0] = pstPhaseResult->ucRDQDelayTap;
            pData[1] = pstPhaseResult->ucRDQDelayTap;
            pData[2] = pstPhaseResult->ucRDQDelayTap;
            pData[3] = pstPhaseResult->ucRDQDelayTap;
            DebugMessageMemoryPhaseCal("_DDR3_READ_DQ_DLYN_TAP = ", PDATA_DWORD(0));
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Print scan phase result of search phase subroutine
// Input Value  : Array of scan phase result
// Output Value : None
//--------------------------------------------------
void ScalerDDR3ScanPhasePrintScanResult(BYTE pucScanResult[8])
{
    pucScanResult = pucScanResult;

    DebugMessageMemoryPhaseCal("=====Scan Result=====", 0);
    DebugMessageMemoryPhaseCal("63~32", (((DWORD)pucScanResult[7] << 24) | ((DWORD)pucScanResult[6] << 16) | ((DWORD)pucScanResult[5] << 8) | pucScanResult[4]));
    DebugMessageMemoryPhaseCal("31~00", (((DWORD)pucScanResult[3] << 24) | ((DWORD)pucScanResult[2] << 16) | ((DWORD)pucScanResult[1] << 8) | pucScanResult[0]));
}


//--------------------------------------------------
// Description  : Find central value of longest pass range according to scan result
// Input Value  : Array of scan result
// Output Value : The central value of longest pass range
//--------------------------------------------------
BYTE ScalerDDR3FindCentralValueOfLongestPassRange(BYTE pucScanResult[8], EnumScanResultType enumResultType)
{
    BYTE ucLongestPassIntvlStart = 0;
    BYTE ucLongestPassIntvlEnd = 0;
    BYTE ucLongestPassIntvlLength = 0;
    BYTE ucCentralValue = 0;

    BYTE ucPassIntvlStart = 0;
    BYTE ucPassIntvlEnd = 0;
    BYTE ucPassIntvlLength = 0;

    BYTE ucScanResultIndex = 0;

    if(GET_SCAN_RESULT(pucScanResult, 0) == _SUCCESS)
    {
        ucPassIntvlStart = 0;
    }

    for(ucScanResultIndex = 1; ucScanResultIndex < (_TOTAL_PHASE_NUM * 2); ucScanResultIndex++)
    {
        if((GET_SCAN_RESULT(pucScanResult, (ucScanResultIndex % _TOTAL_PHASE_NUM)) == _SUCCESS) && (GET_SCAN_RESULT(pucScanResult, ((ucScanResultIndex - 1) % _TOTAL_PHASE_NUM)) == _FAIL))
        {
            ucPassIntvlStart = ucScanResultIndex;
        }
        else if((GET_SCAN_RESULT(pucScanResult, (ucScanResultIndex % _TOTAL_PHASE_NUM)) == _FAIL) && (GET_SCAN_RESULT(pucScanResult, ((ucScanResultIndex - 1) % _TOTAL_PHASE_NUM)) == _SUCCESS))
        {
            ucPassIntvlEnd = ucScanResultIndex - 1;
            ucPassIntvlLength = ucPassIntvlEnd - ucPassIntvlStart + 1;

            if(ucPassIntvlLength > ucLongestPassIntvlLength)
            {
                ucLongestPassIntvlLength = ucPassIntvlLength;
                ucLongestPassIntvlStart = ucPassIntvlStart;
                ucLongestPassIntvlEnd = ucPassIntvlEnd;
            }
        }
    }

    ucCentralValue = ((ucLongestPassIntvlStart + ucLongestPassIntvlEnd) / 2) % _TOTAL_PHASE_NUM;

    DebugMessageMemoryPhaseCal("Pass Intvl Start:", (ucLongestPassIntvlStart % _TOTAL_PHASE_NUM));
    DebugMessageMemoryPhaseCal("Pass Intvl End:", (ucLongestPassIntvlEnd % _TOTAL_PHASE_NUM));
    if(enumResultType == _SCAN_RESULT_WRITE_PHASE)
    {
        DebugMessageMemoryPhaseCal("Best Phase:", ucCentralValue);
    }
    else // enumResultType == _SCAN_RESULT_READ_DELAY_TAP
    {
        DebugMessageMemoryPhaseCal("Best Delay Tap:", ucCentralValue);
    }

    return ucCentralValue;
}

//--------------------------------------------------
// Description  : Check if scan phase result exist pass range
// Input Value  : Array of scan phase result
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerDDR3ScanPhaseResultExistPassRange(BYTE pucScanResult[8])
{
    BYTE ucScanResultIndex = 0x00;

    for(ucScanResultIndex = 0; ucScanResultIndex < 8; ucScanResultIndex++)
    {
        if(pucScanResult[ucScanResultIndex] != 0x00)
        {
            return _TRUE;
        }
    }

    DebugMessageMemoryPhaseCal("Fail to find pass range!", 0);
    return _FALSE;
}

//--------------------------------------------------
// Description  : Check DDR R/W correctness of specific phase set
// Input Value  : None
// Output Value : Phase check result
//--------------------------------------------------
bit ScalerDDR3PhaseCheck(void)
{
    bit bPhaseChkResult = _FAIL;

#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_MCU_MODE)
    bPhaseChkResult = ScalerDDR3PhaseCheckMCUMode();
#elif(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE)
    bPhaseChkResult = ScalerDDR3PhaseCheckFRCMode();
#endif

    // DebugMessageMemoryPhaseCal("Check Result: Pass(1)/Fail(0)", bPhaseChkResult);
    return bPhaseChkResult;
}

//--------------------------------------------------
// Description  : DDR3PLL Output Control
// Input Value  : Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerDDR3PLLOutputCtrl(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        ScalerMaskSetDWord(PA5_00_SYS_PLL_DDR1_1, 0xFFFFFF07, 0x00000000);

        for(pData[0] = 0; pData[0] < 5; pData[0]++)
        {
            Delay5us(g_ucDelay5usN);
        }
    }
    else // Disable
    {
        ScalerMaskSetDWord(PA5_00_SYS_PLL_DDR1_1, 0xFFFFFF07, 0x000000F8);

        Delay5us(g_ucDelay5usN);
    }
}

//--------------------------------------------------
// Description  : Set control registers of specific phase set
// Input Value  : Phase of Clk0~Clk5(range: 0~63)
// Output Value : None
//--------------------------------------------------
void ScalerDDR3SetWritePhaseReg(BYTE pucPhaseOfClk[6])
{
    BYTE ucSyncSel = 0x00;
    BYTE ucPart3OfSysPllSetting5 = 0x01;
    BYTE ucPart4OfSysPllSetting5 = 0x11;

    ScalerDDR3ScanPhaseDDRRelatedBlockReset();

    ScalerDDR3PLLOutputCtrl(_DISABLE);

    //====================================================
    // Set DDR PLL phase setting
    //====================================================
    pData[0] = pucPhaseOfClk[3];
    pData[1] = pucPhaseOfClk[2];
    pData[2] = pucPhaseOfClk[1];
    pData[3] = pucPhaseOfClk[0];
    ScalerSetDWord(PA5_08_SYS_PLL_DDR3_1, PDATA_DWORD(0));

    // Fast version of "if((16 <= phase <= 31) OR (48 <= phase <= 63)), then corresponding SyncSel bit is set to 1"
    ucSyncSel |= (((pucPhaseOfClk[0] & _BIT4) == _BIT4) ? _BIT0 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[1] & _BIT4) == _BIT4) ? _BIT1 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[2] & _BIT4) == _BIT4) ? _BIT2 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[3] & _BIT4) == _BIT4) ? _BIT3 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[4] & _BIT4) == _BIT4) ? _BIT4 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[5] & _BIT4) == _BIT4) ? _BIT5 : 0x00);

    pData[0] = ucSyncSel;
    pData[1] = 0x00;
    pData[2] = pucPhaseOfClk[5];
    pData[3] = pucPhaseOfClk[4];
    ScalerSetDWord(PA5_0C_SYS_PLL_DDR4_1, PDATA_DWORD(0));


    ucPart3OfSysPllSetting5 |= (((pucPhaseOfClk[4] > 31) && (pucPhaseOfClk[4] < 64)) ? 0x02 : 0x00);
    ucPart4OfSysPllSetting5 |= (((pucPhaseOfClk[3] > 31) && (pucPhaseOfClk[3] < 64)) ? 0x20 : 0x00);
    ucPart4OfSysPllSetting5 |= (((pucPhaseOfClk[2] > 31) && (pucPhaseOfClk[2] < 64)) ? 0x02 : 0x00);
    pData[0] = 0x00;
    pData[1] = 0x00;
    pData[2] = ucPart3OfSysPllSetting5;
    pData[3] = ucPart4OfSysPllSetting5;
    ScalerSetDWord(PA5_1C_SYS_PLL5_1, PDATA_DWORD(0));

    ScalerDDR3PLLOutputCtrl(_ENABLE);

    ScalerDDR3DCPHYInitial();
}


//--------------------------------------------------
// Description  : Set rDQ delay tap control registers
// Input Value  : rDQ delay tap
// Output Value : None
//--------------------------------------------------
void ScalerDDR3SetReadDQDelayTapReg(BYTE ucRDQDelayTap)
{
    // Set read delay tap
    pData[0] = ucRDQDelayTap;
    pData[1] = ucRDQDelayTap;
    pData[2] = ucRDQDelayTap;
    pData[3] = ucRDQDelayTap;
    ScalerSetDWord(PA8_80_DQ0_1_DLYN_1, PDATA_DWORD(0));
    ScalerSetDWord(PA8_38_DC_MISC_1, 0x07000000);
}


//--------------------------------------------------
// Description  : Avoid duty issue of pad clock (clk2)
// Input Value  : Current phase search result
// Output Value : None
//--------------------------------------------------
void ScalerDDR3AvoidPadClkDutyIssue(StructPhaseInfo *pstCurrResult)
{
    BYTE ucClkIndex = 0;
    BYTE ucClk2ShiftNum = 0;
    BYTE ucPhaseOfClk2 = pstCurrResult->pucWritePhaseOfClk[2];

    // Avoid setting clk2 between 32-63
    if((ucPhaseOfClk2 > 31) && (ucPhaseOfClk2 < 64))
    {
        if((64 - ucPhaseOfClk2) < (ucPhaseOfClk2 - 31))
        {
            // If phase of clk2 is closer to 64(0), it is shifted to 0.
            ucClk2ShiftNum = 64 - ucPhaseOfClk2;
        }
        else
        {
            // Otherwise, it is shifted to 31.
            ucClk2ShiftNum = 31 + _TOTAL_PHASE_NUM - ucPhaseOfClk2;
        }

        // clk0 is fixed to 0
        for(ucClkIndex = 1; ucClkIndex < 6; ucClkIndex++)
        {
            // clk1 ~ clk5 shift with clk2
            pstCurrResult->pucWritePhaseOfClk[ucClkIndex] = (pstCurrResult->pucWritePhaseOfClk[ucClkIndex] + ucClk2ShiftNum) % _TOTAL_PHASE_NUM;
        }
    }
}

//--------------------------------------------------
// Description  : Exclude write phase in no-fly zone
// Input Value  : Current phase search result
// Output Value : None
//--------------------------------------------------
void ScalerDDR3ExcludePhaseInNoFlyZone(StructPhaseInfo *pstCurrResult)
{
    BYTE ucClkIndex = 0;

    for(ucClkIndex = 1; ucClkIndex < 6; ucClkIndex++)
    {
        // Exclude phase in no-fly zone (i.e. 14, 15, 30 and 31)
        switch(pstCurrResult->pucWritePhaseOfClk[ucClkIndex])
        {
            case 14:
                pstCurrResult->pucWritePhaseOfClk[ucClkIndex] = 13;
                break;

            case 15:
                pstCurrResult->pucWritePhaseOfClk[ucClkIndex] = 16;
                break;

            case 30:
                pstCurrResult->pucWritePhaseOfClk[ucClkIndex] = 29;
                break;

            case 31:
                pstCurrResult->pucWritePhaseOfClk[ucClkIndex] = 32;
                break;

            default:
                break;
        }
    }
}


//--------------------------------------------------
// Description  : DDR SDRAM Scan Phase A, search DDR_CK phase
// Input Value  : Previous phase search result, current phase search result
// Output Value : If found pass range -> _SUCCESS
//                If not              -> _FAIL
//--------------------------------------------------
bit ScalerDDR3ScanPhaseA(StructPhaseInfo *pstPrevResult, StructPhaseInfo *pstCurrResult)
{
    BYTE ucPhaseIndex = 0;
    BYTE pucInitPhaseOfClk[6];
    BYTE pucPhaseOfClk[6];
    BYTE ucPhaseDiffFromInitToScannedResult = 0x00;

    BYTE pucScanResultClk2[8] = {0};

    memcpy(pucInitPhaseOfClk, pstPrevResult->pucWritePhaseOfClk, 6);

    //=================================================================
    // Scan for Clk2 pass region, phase of Clk0 is fixed to pass value
    //=================================================================
    pucPhaseOfClk[0] = pucInitPhaseOfClk[0];

    for(ucPhaseIndex = 0; ucPhaseIndex < _TOTAL_PHASE_NUM; ucPhaseIndex++)
    {
        // ucPhaseOfClk[0] is fixed.
        pucPhaseOfClk[1] = (pucInitPhaseOfClk[1] + ucPhaseIndex) % _TOTAL_PHASE_NUM;
        pucPhaseOfClk[2] = (pucInitPhaseOfClk[2] + ucPhaseIndex) % _TOTAL_PHASE_NUM;
        pucPhaseOfClk[3] = (pucInitPhaseOfClk[3] + ucPhaseIndex) % _TOTAL_PHASE_NUM;
        pucPhaseOfClk[4] = (pucInitPhaseOfClk[4] + ucPhaseIndex) % _TOTAL_PHASE_NUM;
        pucPhaseOfClk[5] = (pucInitPhaseOfClk[5] + ucPhaseIndex) % _TOTAL_PHASE_NUM;

        // DebugMessageMemoryPhaseCal("ScanPhaseA  Phase= ", ucPhaseOfClk[2]);

        ScalerDDR3SetWritePhaseReg(pucPhaseOfClk);
        ScalerDDR3SetReadDQDelayTapReg(pstPrevResult->ucRDQDelayTap);

        SET_SCAN_RESULT(pucScanResultClk2, pucPhaseOfClk[2], ScalerDDR3PhaseCheck());
    }

    //====================================
    // Phase of Clk0 is fixed to 0
    //====================================
    pstCurrResult->pucWritePhaseOfClk[0] = 0;


    //====================================
    // Pass range of Clk2
    //====================================
    ScalerDDR3ScanPhasePrintScanResult(pucScanResultClk2);


    DebugMessageMemoryPhaseCal("*** Clk2 ***", 0);

    if(ScalerDDR3ScanPhaseResultExistPassRange(pucScanResultClk2) == _FALSE)
    {
        return _FAIL;
    }

    pstCurrResult->pucWritePhaseOfClk[2] = ScalerDDR3FindCentralValueOfLongestPassRange(pucScanResultClk2, _SCAN_RESULT_WRITE_PHASE);

    //====================================
    // Set Clk2 phase to scanned best phase
    //====================================
    ucPhaseDiffFromInitToScannedResult = PHASE_DIFF(pstCurrResult->pucWritePhaseOfClk[2], pucInitPhaseOfClk[2]);

    pucPhaseOfClk[0] = pucInitPhaseOfClk[0];
    pucPhaseOfClk[1] = (pucInitPhaseOfClk[1] + ucPhaseDiffFromInitToScannedResult) % _TOTAL_PHASE_NUM;
    pucPhaseOfClk[2] = pstCurrResult->pucWritePhaseOfClk[2];
    pucPhaseOfClk[3] = (pucInitPhaseOfClk[3] + ucPhaseDiffFromInitToScannedResult) % _TOTAL_PHASE_NUM;
    pucPhaseOfClk[4] = (pucInitPhaseOfClk[4] + ucPhaseDiffFromInitToScannedResult) % _TOTAL_PHASE_NUM;
    pucPhaseOfClk[5] = (pucInitPhaseOfClk[5] + ucPhaseDiffFromInitToScannedResult) % _TOTAL_PHASE_NUM;

    // DebugMessageMemoryPhaseCal("**Set Clk2 Phase**", ucPhaseOfClk[2]);
    ScalerDDR3SetWritePhaseReg(pucPhaseOfClk);
    ScalerDDR3SetReadDQDelayTapReg(pstPrevResult->ucRDQDelayTap);

    return _SUCCESS;
}


#if(_SEARCH_PHASE_WRITE_LEVELING == _ON)
//--------------------------------------------------
// Description  : DDR SDRAM Scan Phase Write Leveling,
//                calibrates wDQS phase with write leveling function
// Input Value  : Previous phase search result, current phase search result
// Output Value : None
//--------------------------------------------------
void ScalerDDR3ScanPhaseWriteLeveling(StructPhaseInfo *pstCurrResult)
{
    BYTE ucPhaseIndex = 0;
    BYTE pucPhaseOfClk[6];

    BYTE ucSyncSel = 0;
    BYTE ucPart3OfSysPllSetting5 = 0;
    BYTE ucPart4OfSysPllSetting5 = 0;

    BYTE pucWLResultDQS0[8] = {0};
    BYTE pucWLResultDQS1[8] = {0};
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
    BYTE pucWLResultDQS2[8] = {0};
    BYTE pucWLResultDQS3[8] = {0};
#endif

    // Enable write leveling (DRAM MR1 bit7 = 1)
    ScalerMaskSetDWord(PA8_44_MOD_REG_1, 0xFF7FFFFF, 0x00800000);
    // Write MR1 to DRAM
    ScalerSetDWord(PA8_40_DC_DDR3_CTL_1, 0x00000030);
    ScalerTimerDelayXms(2);

    // Wait until write leveling mode ready
    ScalerTimerPollingFlagProc(_SEARCH_PHASE_POLLING_TIMEOUT, PA8_57_DC_WRITE_LEVE_4, _BIT0, _TRUE);
    ScalerTimerDelayXms(2);

    // ODT setting in write leveling mode
    ScalerMaskSetDWord(PA8_20_ODT_CTRL0_1, 0xFCFFFFFF, 0x03000000);

    //=================================================================
    // Scan for proper phase of wDQS(Clk3, Clk4) , phase of Clk0,
    // Clk1, Clk2, and Clk5 are fixed
    //=================================================================
    pucPhaseOfClk[0] = pstCurrResult->pucWritePhaseOfClk[0];
    pucPhaseOfClk[1] = 0;
    pucPhaseOfClk[2] = pstCurrResult->pucWritePhaseOfClk[2];
    pucPhaseOfClk[5] = 0;

    for(ucPhaseIndex = 0; ucPhaseIndex < _TOTAL_PHASE_NUM; ucPhaseIndex++)
    {
        // ucPhaseOfClk[0] is fixed.
        // ucPhaseOfClk[1] is fixed;
        // ucPhaseOfClk[2] is fixed.
        pucPhaseOfClk[3] = ucPhaseIndex;
        pucPhaseOfClk[4] = ucPhaseIndex;
        // ucPhaseOfClk[5] is fixed.

        ucSyncSel = 0x00;
        ucPart3OfSysPllSetting5 = 0x01;
        ucPart4OfSysPllSetting5 = 0x11;

        // disable DQS01,DQS23 output
        ScalerSetDWord(PA5_00_SYS_PLL_DDR1_1, 0x00000063);

        //====================================================
        // Set DDR PLL phase setting
        //====================================================
        pData[0] = pucPhaseOfClk[3];
        pData[1] = pucPhaseOfClk[2];
        pData[2] = pucPhaseOfClk[1];
        pData[3] = pucPhaseOfClk[0];
        ScalerSetDWord(PA5_08_SYS_PLL_DDR3_1, PDATA_DWORD(0));


        // Fast version of "if((16 <= phase <= 31) OR (48 <= phase <= 63)), then corresponding SyncSel bit is set to 1"
        ucSyncSel |= (((pucPhaseOfClk[0] & _BIT4) == _BIT4) ? _BIT0 : 0x00);
        ucSyncSel |= (((pucPhaseOfClk[1] & _BIT4) == _BIT4) ? _BIT1 : 0x00);
        ucSyncSel |= (((pucPhaseOfClk[2] & _BIT4) == _BIT4) ? _BIT2 : 0x00);
        ucSyncSel |= (((pucPhaseOfClk[3] & _BIT4) == _BIT4) ? _BIT3 : 0x00);
        ucSyncSel |= (((pucPhaseOfClk[4] & _BIT4) == _BIT4) ? _BIT4 : 0x00);
        ucSyncSel |= (((pucPhaseOfClk[5] & _BIT4) == _BIT4) ? _BIT5 : 0x00);

        pData[0] = ucSyncSel;
        pData[1] = 0x00;
        pData[2] = pucPhaseOfClk[5];
        pData[3] = pucPhaseOfClk[4];
        ScalerSetDWord(PA5_0C_SYS_PLL_DDR4_1, PDATA_DWORD(0));


        ucPart3OfSysPllSetting5 |= (((pucPhaseOfClk[4] > 31) && (pucPhaseOfClk[4] < 64)) ? 0x02 : 0x00);
        ucPart4OfSysPllSetting5 |= (((pucPhaseOfClk[3] > 31) && (pucPhaseOfClk[3] < 64)) ? 0x20 : 0x00);
        ucPart4OfSysPllSetting5 |= (((pucPhaseOfClk[2] > 31) && (pucPhaseOfClk[2] < 64)) ? 0x02 : 0x00);
        pData[0] = 0x00;
        pData[1] = 0x00;
        pData[2] = ucPart3OfSysPllSetting5;
        pData[3] = ucPart4OfSysPllSetting5;
        ScalerSetDWord(PA5_1C_SYS_PLL5_1, PDATA_DWORD(0));


        // enable DQS01,DQS23 output
        ScalerSetDWord(PA5_00_SYS_PLL_DDR1_1, 0x00000003);

        // Wait until wr_level_rdy=1, 8854 bit0=1
        ScalerTimerPollingFlagProc(_SEARCH_PHASE_POLLING_TIMEOUT, PA8_57_DC_WRITE_LEVE_4, _BIT0, _TRUE);

        // trig-wr_level to 1, dc_phy send one dqs high pulse to DRAM
        ScalerSetDWord(PA8_54_DC_WRITE_LEVE_1, 0x00000002);
        ScalerTimerPollingFlagProc(_SEARCH_PHASE_POLLING_TIMEOUT, PA8_57_DC_WRITE_LEVE_4, _BIT1, _FALSE);

        // dq_value_output by DRAM
        PDATA_DWORD(0) = ScalerGetDWord(PAC_04_WL_CTRL_11);

        SET_SCAN_RESULT(pucWLResultDQS0, ucPhaseIndex, ((pData[3] != 0x00) ? _SUCCESS : _FAIL));
        SET_SCAN_RESULT(pucWLResultDQS1, ucPhaseIndex, ((pData[2] != 0x00) ? _SUCCESS : _FAIL));
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
        SET_SCAN_RESULT(pucWLResultDQS2, ucPhaseIndex, ((pData[1] != 0x00) ? _SUCCESS : _FAIL));
        SET_SCAN_RESULT(pucWLResultDQS3, ucPhaseIndex, ((pData[0] != 0x00) ? _SUCCESS : _FAIL));
#endif

#if(_SEARCH_PHASE_DEBUG_MSG_OF_WRITE_LEVELING == _ON)
        DebugMessageMemoryPhaseCal("ScanPhase WL, Phase= ", ucPhaseIndex);
        DebugMessageMemoryPhaseCal("DQ Value Output by DDR3", ScalerGetDWord(PAC_04_WL_CTRL_11));
#endif
    }

    // ODT setting when exiting write leveling mode
    ScalerMaskSetDWord(PA8_20_ODT_CTRL0_1, 0xFCFFFFFF, 0x00000000);
    ScalerTimerDelayXms(2);

    // Disable write leveling (DRAM MR1 bit7 = 0)
    ScalerMaskSetDWord(PA8_44_MOD_REG_1, 0xFF7FFFFF, 0x00000000);

    // Write MR1 to DRAM
    ScalerSetDWord(PA8_40_DC_DDR3_CTL_1, 0x00000030);
    ScalerTimerDelayXms(2);


    //=================================================================
    // Write leveling result
    //=================================================================
    ScalerDDR3ScanPhasePrintScanResult(pucWLResultDQS0);
    ScalerDDR3ScanPhasePrintScanResult(pucWLResultDQS1);

    DebugMessageMemoryPhaseCal("*** Clk3 ***", 0);
    pstCurrResult->pucWritePhaseOfClk[3] = ScalerDDR3ScanPhaseWLFindProperWDQSPhase(pucWLResultDQS0, pucWLResultDQS1);

#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_1PC)

    // Clk 4
    // 1pc DDR case, search result of Clk4 is set to the same value of Clk3
    pstCurrResult->pucWritePhaseOfClk[4] = pstCurrResult->pucWritePhaseOfClk[3];

#elif((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)

    // Clk 4
    ScalerDDR3ScanPhasePrintScanResult(pucWLResultDQS2);
    ScalerDDR3ScanPhasePrintScanResult(pucWLResultDQS3);

    DebugMessageMemoryPhaseCal("*** Clk4 ***", 0);
    pstCurrResult->pucWritePhaseOfClk[4] = ScalerDDR3ScanPhaseWLFindProperWDQSPhase(pucWLResultDQS2, pucWLResultDQS3);

#endif
}


//--------------------------------------------------
// Description  : Find proper wDQS phase according to write leveling result
// Input Value  : Array of write leveling result
// Output Value : The central phase of longest pass range
//--------------------------------------------------
BYTE ScalerDDR3ScanPhaseWLFindProperWDQSPhase(BYTE pucWLResult0[8], BYTE pucWLResult1[8])
{
    BYTE ucPhaseAlignWithCLK = 0;
    BYTE ucTransPtDQS0 = 0;
    BYTE ucTransPtDQS1 = 0;
    bit bFoundTransPtDQS0 = _FALSE;
    bit bFoundTransPtDQS1 = _FALSE;
    BYTE ucWLResultIndex = 0;

    BYTE ucTransPtLess = 0;
    BYTE ucTransPtGreater = 0;
    BYTE ucTransPtDiff = 0;

    for(ucWLResultIndex = 1; ucWLResultIndex < (_TOTAL_PHASE_NUM * 2); ucWLResultIndex++)
    {
        if((bFoundTransPtDQS0 == _FALSE) &&
           (GET_SCAN_RESULT(pucWLResult0, (ucWLResultIndex % _TOTAL_PHASE_NUM)) == _SUCCESS) &&
           (GET_SCAN_RESULT(pucWLResult0, ((ucWLResultIndex - 1) % _TOTAL_PHASE_NUM)) == _FAIL))
        {
            ucTransPtDQS0 = ucWLResultIndex % _TOTAL_PHASE_NUM;
            bFoundTransPtDQS0 = _TRUE;
        }

        if((bFoundTransPtDQS1 == _FALSE) &&
           (GET_SCAN_RESULT(pucWLResult1, (ucWLResultIndex % _TOTAL_PHASE_NUM)) == _SUCCESS) &&
           (GET_SCAN_RESULT(pucWLResult1, ((ucWLResultIndex - 1) % _TOTAL_PHASE_NUM)) == _FAIL))
        {
            ucTransPtDQS1 = ucWLResultIndex % _TOTAL_PHASE_NUM;
            bFoundTransPtDQS1 = _TRUE;
        }

        if((bFoundTransPtDQS0 == _TRUE) && (bFoundTransPtDQS1 == _TRUE))
        {
            break;
        }
    }

    ucTransPtLess = (ucTransPtDQS0 < ucTransPtDQS1) ? ucTransPtDQS0 : ucTransPtDQS1;
    ucTransPtGreater = (ucTransPtDQS0 < ucTransPtDQS1) ? ucTransPtDQS1 : ucTransPtDQS0;
    ucTransPtDiff = PHASE_DIFF(ucTransPtGreater, ucTransPtLess);
    if(ucTransPtDiff > (_TOTAL_PHASE_NUM - ucTransPtDiff))
    {
        ucPhaseAlignWithCLK = (((ucTransPtLess + _TOTAL_PHASE_NUM) + ucTransPtGreater) / 2) % _TOTAL_PHASE_NUM;
    }
    else
    {
        ucPhaseAlignWithCLK = ((ucTransPtLess + ucTransPtGreater) / 2) % _TOTAL_PHASE_NUM;
    }

    DebugMessageMemoryPhaseCal("Best Phase:", ucPhaseAlignWithCLK);

    return ucPhaseAlignWithCLK;
}

#else // Else of #if(_SEARCH_PHASE_WRITE_LEVELING == _ON)

//--------------------------------------------------
// Description  : DDR SDRAM Scan Phase B, search wDQS phase
// Input Value  : Previous phase search result, current phase search result
// Output Value : If found pass range -> _SUCCESS
//                If not              -> _FAIL
//--------------------------------------------------
bit ScalerDDR3ScanPhaseB(StructPhaseInfo *pstPrevResult, StructPhaseInfo *pstCurrResult)
{
    BYTE ucPhaseIndex = 0;
    BYTE pucInitPhaseOfClk[6];
    BYTE pucPhaseOfClk[6];
    bit bPhaseCheckResult = _FAIL;

    BYTE pucScanResultClk3[8] = {0};
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
    BYTE pucScanResultClk4[8] = {0};
#endif

    pucInitPhaseOfClk[0] = pstCurrResult->pucWritePhaseOfClk[0];
    pucInitPhaseOfClk[1] = (pstCurrResult->pucWritePhaseOfClk[2] + PHASE_DIFF(pstPrevResult->pucWritePhaseOfClk[1], pstPrevResult->pucWritePhaseOfClk[2])) % _TOTAL_PHASE_NUM;
    pucInitPhaseOfClk[2] = pstCurrResult->pucWritePhaseOfClk[2];
    pucInitPhaseOfClk[3] = (pstCurrResult->pucWritePhaseOfClk[2] + PHASE_DIFF(pstPrevResult->pucWritePhaseOfClk[3], pstPrevResult->pucWritePhaseOfClk[2])) % _TOTAL_PHASE_NUM;
    pucInitPhaseOfClk[4] = (pstCurrResult->pucWritePhaseOfClk[2] + PHASE_DIFF(pstPrevResult->pucWritePhaseOfClk[4], pstPrevResult->pucWritePhaseOfClk[2])) % _TOTAL_PHASE_NUM;
    pucInitPhaseOfClk[5] = (pstCurrResult->pucWritePhaseOfClk[2] + PHASE_DIFF(pstPrevResult->pucWritePhaseOfClk[5], pstPrevResult->pucWritePhaseOfClk[2])) % _TOTAL_PHASE_NUM;

    //=================================================================
    // Scan for Clk3 & Clk4 pass region, phase of Clk0 and Clk2 are
    // fixed to pass value
    //=================================================================
    pucPhaseOfClk[0] = pucInitPhaseOfClk[0];
    pucPhaseOfClk[2] = pucInitPhaseOfClk[2];

    for(ucPhaseIndex = 0; ucPhaseIndex < _TOTAL_PHASE_NUM; ucPhaseIndex++)
    {
        // ucPhaseOfClk[0] is fixed.
        pucPhaseOfClk[1] = (pucInitPhaseOfClk[1] + ucPhaseIndex) % _TOTAL_PHASE_NUM;
        // ucPhaseOfClk[2] is fixed.
        pucPhaseOfClk[3] = (pucInitPhaseOfClk[3] + ucPhaseIndex) % _TOTAL_PHASE_NUM;
        pucPhaseOfClk[4] = (pucInitPhaseOfClk[4] + ucPhaseIndex) % _TOTAL_PHASE_NUM;
        pucPhaseOfClk[5] = (pucInitPhaseOfClk[5] + ucPhaseIndex) % _TOTAL_PHASE_NUM;

        ScalerDDR3SetWritePhaseReg(pucPhaseOfClk);
        ScalerDDR3SetReadDQDelayTapReg(pstPrevResult->ucRDQDelayTap);

        bPhaseCheckResult = ScalerDDR3PhaseCheck();
        SET_SCAN_RESULT(pucScanResultClk3, pucPhaseOfClk[3], bPhaseCheckResult);
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
        SET_SCAN_RESULT(pucScanResultClk4, pucPhaseOfClk[4], bPhaseCheckResult);
#endif
    }

#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_1PC)

    //=================================================================
    // 1pc DDR case, pass range of Clk3
    //=================================================================
    ScalerDDR3ScanPhasePrintScanResult(pucScanResultClk3);

    DebugMessageMemoryPhaseCal("*** Clk3 ***", 0);

    if(ScalerDDR3ScanPhaseResultExistPassRange(pucScanResultClk3) == _FALSE)
    {
        return _FAIL;
    }

    pstCurrResult->pucWritePhaseOfClk[3] = ScalerDDR3FindCentralValueOfLongestPassRange(pucScanResultClk3, _SCAN_RESULT_WRITE_PHASE);

    // 1pc DDR case, search result of Clk4 is set to the same value of Clk3
    pstCurrResult->pucWritePhaseOfClk[4] = pstCurrResult->pucWritePhaseOfClk[3];


#elif((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)

    //=================================================================
    // 2pcs DDR case, "Safe Zone" of Clk3 & Clk4
    //=================================================================
    if((ScalerDDR3ScanPhaseResultExistPassRange(pucScanResultClk3) == _FALSE) ||
       (ScalerDDR3ScanPhaseResultExistPassRange(pucScanResultClk4) == _FALSE))
    {
        return _FAIL;
    }

    ScalerDDR3ScanPhasePrintScanResult(pucScanResultClk3);
    DebugMessageMemoryPhaseCal("*** SafeZone_Clk3 ***", 0);
    pstCurrResult->pucWritePhaseOfClk[3] = ScalerDDR3FindCentralValueOfLongestPassRange(pucScanResultClk3, _SCAN_RESULT_WRITE_PHASE);

    ScalerDDR3ScanPhasePrintScanResult(pucScanResultClk4);
    DebugMessageMemoryPhaseCal("*** SafeZone_Clk4 ***", 0);
    pstCurrResult->pucWritePhaseOfClk[4] = ScalerDDR3FindCentralValueOfLongestPassRange(pucScanResultClk4, _SCAN_RESULT_WRITE_PHASE);

    DebugMessageMemoryPhaseCal("===================", 0);

    //=================================================================
    // Scan for full Clk3 pass region, Phase of Clk0, Clk2, Clk4 and Clk5
    // are fixed to pass value
    //=================================================================
    pucPhaseOfClk[0] = pucInitPhaseOfClk[0];
    pucPhaseOfClk[2] = pucInitPhaseOfClk[2];
    pucPhaseOfClk[4] = pstCurrResult->pucWritePhaseOfClk[4];
    pucPhaseOfClk[5] = (pucPhaseOfClk[4] + PHASE_DIFF(pstPrevResult->pucWritePhaseOfClk[5], pstPrevResult->pucWritePhaseOfClk[4])) % _TOTAL_PHASE_NUM;

    for(ucPhaseIndex = 0; ucPhaseIndex < _TOTAL_PHASE_NUM; ucPhaseIndex++)
    {
        // ucPhaseOfClk[0] is fixed.
        pucPhaseOfClk[1] = (pucInitPhaseOfClk[1] + ucPhaseIndex) % _TOTAL_PHASE_NUM;
        // ucPhaseOfClk[2] is fixed.
        pucPhaseOfClk[3] = (pucInitPhaseOfClk[3] + ucPhaseIndex) % _TOTAL_PHASE_NUM;
        // ucPhaseOfClk[4] is fixed.
        // ucPhaseOfClk[5] is fixed.

        // DebugMessageMemoryPhaseCal("ScanPhaseB-Clk3, Phase= ", ucPhaseOfClk[3]);

        ScalerDDR3SetWritePhaseReg(pucPhaseOfClk);
        ScalerDDR3SetReadDQDelayTapReg(pstPrevResult->ucRDQDelayTap);

        SET_SCAN_RESULT(pucScanResultClk3, pucPhaseOfClk[3], ScalerDDR3PhaseCheck());
    }

    // Clk 3
    ScalerDDR3ScanPhasePrintScanResult(pucScanResultClk3);

    DebugMessageMemoryPhaseCal("*** Clk3 ***", 0);

    if(ScalerDDR3ScanPhaseResultExistPassRange(pucScanResultClk3) == _FALSE)
    {
        return _FAIL;
    }

    pstCurrResult->pucWritePhaseOfClk[3] = ScalerDDR3FindCentralValueOfLongestPassRange(pucScanResultClk3, _SCAN_RESULT_WRITE_PHASE);

    //=================================================================
    // Scan for full Clk4 pass region, phase of Clk0, Clk1, Clk2 and Clk3
    // are fixed to pass value
    //=================================================================
    pucPhaseOfClk[0] = pucInitPhaseOfClk[0];
    pucPhaseOfClk[2] = pucInitPhaseOfClk[2];
    pucPhaseOfClk[3] = pstCurrResult->pucWritePhaseOfClk[3];
    pucPhaseOfClk[1] = (pucPhaseOfClk[3] + PHASE_DIFF(pstPrevResult->pucWritePhaseOfClk[1], pstPrevResult->pucWritePhaseOfClk[3])) % _TOTAL_PHASE_NUM;

    for(ucPhaseIndex = 0; ucPhaseIndex < _TOTAL_PHASE_NUM; ucPhaseIndex++)
    {
        // ucPhaseOfClk[0] is fixed.
        // ucPhaseOfClk[1] is fixed;
        // ucPhaseOfClk[2] is fixed.
        // ucPhaseOfClk[3] is fixed.
        pucPhaseOfClk[4] = (pucInitPhaseOfClk[4] + ucPhaseIndex) % _TOTAL_PHASE_NUM;
        pucPhaseOfClk[5] = (pucInitPhaseOfClk[5] + ucPhaseIndex) % _TOTAL_PHASE_NUM;

        // DebugMessageMemoryPhaseCal("ScanPhaseB-Clk4, Phase= ", ucPhaseOfClk[4]);

        ScalerDDR3SetWritePhaseReg(pucPhaseOfClk);
        ScalerDDR3SetReadDQDelayTapReg(pstPrevResult->ucRDQDelayTap);

        SET_SCAN_RESULT(pucScanResultClk4, pucPhaseOfClk[4], ScalerDDR3PhaseCheck());
    }

    // Clk 4
    ScalerDDR3ScanPhasePrintScanResult(pucScanResultClk4);

    DebugMessageMemoryPhaseCal("*** Clk4 ***", 0);

    if(ScalerDDR3ScanPhaseResultExistPassRange(pucScanResultClk4) == _FALSE)
    {
        return _FAIL;
    }

    pstCurrResult->pucWritePhaseOfClk[4] = ScalerDDR3FindCentralValueOfLongestPassRange(pucScanResultClk4, _SCAN_RESULT_WRITE_PHASE);

#endif

    return _SUCCESS;
}

#endif // End of #if(_SEARCH_PHASE_WRITE_LEVELING == _ON)

//--------------------------------------------------
// Description  : DDR SDRAM Scan Phase C, search wDQ phase
// Input Value  : Previous phase search result, current phase search result
// Output Value : If found pass range -> _SUCCESS
//                If not              -> _FAIL
//--------------------------------------------------
bit ScalerDDR3ScanPhaseC(StructPhaseInfo *pstPrevResult, StructPhaseInfo *pstCurrResult)
{
    BYTE ucPhaseIndex = 0;
    BYTE pucInitPhaseOfClk[6];
    BYTE pucPhaseOfClk[6];
    bit bPhaseCheckResult = _FAIL;

    BYTE pucScanResultClk1[8] = {0};
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
    BYTE pucScanResultClk5[8] = {0};
#endif

    pucInitPhaseOfClk[0] = pstCurrResult->pucWritePhaseOfClk[0];
    pucInitPhaseOfClk[1] = (pstCurrResult->pucWritePhaseOfClk[3] + PHASE_DIFF(pstPrevResult->pucWritePhaseOfClk[1], pstPrevResult->pucWritePhaseOfClk[3])) % _TOTAL_PHASE_NUM;
    pucInitPhaseOfClk[2] = pstCurrResult->pucWritePhaseOfClk[2];
    pucInitPhaseOfClk[3] = pstCurrResult->pucWritePhaseOfClk[3];
    pucInitPhaseOfClk[4] = pstCurrResult->pucWritePhaseOfClk[4];
    pucInitPhaseOfClk[5] = (pstCurrResult->pucWritePhaseOfClk[4] + PHASE_DIFF(pstPrevResult->pucWritePhaseOfClk[5], pstPrevResult->pucWritePhaseOfClk[4])) % _TOTAL_PHASE_NUM;

    //=================================================================
    // Scan for Clk1 & Clk5 pass region, phase of Clk0, Clk2, Clk3
    // and Clk4 are fixed to pass value
    //=================================================================
    pucPhaseOfClk[0] = pucInitPhaseOfClk[0];
    pucPhaseOfClk[2] = pucInitPhaseOfClk[2];
    pucPhaseOfClk[3] = pucInitPhaseOfClk[3];
    pucPhaseOfClk[4] = pucInitPhaseOfClk[4];

    for(ucPhaseIndex = 0; ucPhaseIndex < _TOTAL_PHASE_NUM; ucPhaseIndex++)
    {
        // ucPhaseOfClk[0] is fixed.
        pucPhaseOfClk[1] = (pucInitPhaseOfClk[1] + ucPhaseIndex) % _TOTAL_PHASE_NUM;
        // ucPhaseOfClk[2] is fixed.
        // ucPhaseOfClk[3] is fixed.
        // ucPhaseOfClk[4] is fixed.
        pucPhaseOfClk[5] = (pucInitPhaseOfClk[5] + ucPhaseIndex) % _TOTAL_PHASE_NUM;

        ScalerDDR3SetWritePhaseReg(pucPhaseOfClk);
        ScalerDDR3SetReadDQDelayTapReg(pstPrevResult->ucRDQDelayTap);

        bPhaseCheckResult = ScalerDDR3PhaseCheck();
        SET_SCAN_RESULT(pucScanResultClk1, pucPhaseOfClk[1], bPhaseCheckResult);
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
        SET_SCAN_RESULT(pucScanResultClk5, pucPhaseOfClk[5], bPhaseCheckResult);
#endif
    }


#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_1PC)

    //=================================================================
    // 1pc DDR case, pass range of Clk1
    //=================================================================
    ScalerDDR3ScanPhasePrintScanResult(pucScanResultClk1);

    DebugMessageMemoryPhaseCal("*** Clk1 ***", 0);

    if(ScalerDDR3ScanPhaseResultExistPassRange(pucScanResultClk1) == _FALSE)
    {
        return _FAIL;
    }

    pstCurrResult->pucWritePhaseOfClk[1] = ScalerDDR3FindCentralValueOfLongestPassRange(pucScanResultClk1, _SCAN_RESULT_WRITE_PHASE);

    // 1pc DDR case, search result of Clk5 is set to the same value of Clk1
    pstCurrResult->pucWritePhaseOfClk[5] = pstCurrResult->pucWritePhaseOfClk[1];


#elif((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)

    //=================================================================
    // 2pcs DDR case, "Safe Zone" of Clk1 & Clk5
    //=================================================================
    if((ScalerDDR3ScanPhaseResultExistPassRange(pucScanResultClk1) == _FALSE) ||
       (ScalerDDR3ScanPhaseResultExistPassRange(pucScanResultClk5) == _FALSE))
    {
        return _FAIL;
    }

    ScalerDDR3ScanPhasePrintScanResult(pucScanResultClk1);
    DebugMessageMemoryPhaseCal("*** SafeZone_Clk1 ***", 0);
    pstCurrResult->pucWritePhaseOfClk[1] = ScalerDDR3FindCentralValueOfLongestPassRange(pucScanResultClk1, _SCAN_RESULT_WRITE_PHASE);

    ScalerDDR3ScanPhasePrintScanResult(pucScanResultClk5);
    DebugMessageMemoryPhaseCal("*** SafeZone_Clk5 ***", 0);
    pstCurrResult->pucWritePhaseOfClk[5] = ScalerDDR3FindCentralValueOfLongestPassRange(pucScanResultClk5, _SCAN_RESULT_WRITE_PHASE);

    DebugMessageMemoryPhaseCal("===================", 0);

    //=================================================================
    // Scan for full Clk1 pass region, phase of Clk0, Clk2, Clk3, Clk4
    // and Clk5 are fixed to pass value
    //=================================================================
    pucPhaseOfClk[0] = pucInitPhaseOfClk[0];
    pucPhaseOfClk[2] = pucInitPhaseOfClk[2];
    pucPhaseOfClk[3] = pucInitPhaseOfClk[3];
    pucPhaseOfClk[4] = pucInitPhaseOfClk[4];
    pucPhaseOfClk[5] = pstCurrResult->pucWritePhaseOfClk[5];

    for(ucPhaseIndex = 0; ucPhaseIndex < _TOTAL_PHASE_NUM; ucPhaseIndex++)
    {
        // ucPhaseOfClk[0] is fixed.
        pucPhaseOfClk[1] = (pucInitPhaseOfClk[1] + ucPhaseIndex) % _TOTAL_PHASE_NUM;
        // ucPhaseOfClk[2] is fixed.
        // ucPhaseOfClk[3] is fixed.
        // ucPhaseOfClk[4] is fixed.
        // ucPhaseOfClk[5] is fixed.

        ScalerDDR3SetWritePhaseReg(pucPhaseOfClk);
        ScalerDDR3SetReadDQDelayTapReg(pstPrevResult->ucRDQDelayTap);

        SET_SCAN_RESULT(pucScanResultClk1, pucPhaseOfClk[1], ScalerDDR3PhaseCheck());
    }

    // Clk 1
    ScalerDDR3ScanPhasePrintScanResult(pucScanResultClk1);

    DebugMessageMemoryPhaseCal("*** Clk1 ***", 0);

    if(ScalerDDR3ScanPhaseResultExistPassRange(pucScanResultClk1) == _FALSE)
    {
        return _FAIL;
    }

    pstCurrResult->pucWritePhaseOfClk[1] = ScalerDDR3FindCentralValueOfLongestPassRange(pucScanResultClk1, _SCAN_RESULT_WRITE_PHASE);

    //=================================================================
    // Scan for full Clk5 pass region, Clk1 phase is fixed to pass value
    //=================================================================
    //=================================================================
    // Scan for Clk5 pass region, phase of Clk0, Clk1, Clk2, Clk3
    // and Clk4 are fixed to pass value
    //=================================================================
    pucPhaseOfClk[0] = pucInitPhaseOfClk[0];
    pucPhaseOfClk[2] = pucInitPhaseOfClk[2];
    pucPhaseOfClk[3] = pucInitPhaseOfClk[3];
    pucPhaseOfClk[4] = pucInitPhaseOfClk[4];
    pucPhaseOfClk[1] = pstCurrResult->pucWritePhaseOfClk[1];

    for(ucPhaseIndex = 0; ucPhaseIndex < _TOTAL_PHASE_NUM; ucPhaseIndex++)
    {
        // ucPhaseOfClk[0] is fixed.
        // ucPhaseOfClk[1] is fixed.
        // ucPhaseOfClk[2] is fixed.
        // ucPhaseOfClk[3] is fixed.
        // ucPhaseOfClk[4] is fixed.
        pucPhaseOfClk[5] = (pucInitPhaseOfClk[5] + ucPhaseIndex) % _TOTAL_PHASE_NUM;

        // DebugMessageMemoryPhaseCal("ScanPhaseC-Clk5, Phase= ", ucPhaseOfClk[5]);

        ScalerDDR3SetWritePhaseReg(pucPhaseOfClk);
        ScalerDDR3SetReadDQDelayTapReg(pstPrevResult->ucRDQDelayTap);

        SET_SCAN_RESULT(pucScanResultClk5, pucPhaseOfClk[5], ScalerDDR3PhaseCheck());
    }

    // Clk 5
    ScalerDDR3ScanPhasePrintScanResult(pucScanResultClk5);

    DebugMessageMemoryPhaseCal("*** Clk5 ***", 0);

    if(ScalerDDR3ScanPhaseResultExistPassRange(pucScanResultClk5) == _FALSE)
    {
        return _FAIL;
    }

    pstCurrResult->pucWritePhaseOfClk[5] = ScalerDDR3FindCentralValueOfLongestPassRange(pucScanResultClk5, _SCAN_RESULT_WRITE_PHASE);

#endif

    return _SUCCESS;
}


//--------------------------------------------------
// Description  : DDR SDRAM Scan Phase E, search rDQ delay tap
// Input Value  : Current phase search result
// Output Value : If found pass range -> _SUCCESS
//                If not              -> _FAIL
//--------------------------------------------------
bit ScalerDDR3ScanPhaseE(StructPhaseInfo *pstCurrResult)
{
    BYTE ucPhaseIndex = 0;
    static BYTE spucScanResultRead[8] = {0};

    // Disable on the fly calibration function
    ScalerMaskSetDWord(PA9_08_CAL_CTRL1, 0xfffffffe, 0x00000000);
    Delay5us(g_ucDelay5usN);

    //=================================================================
    // Search rDQ delay tap
    //=================================================================
    for(ucPhaseIndex = 0; ucPhaseIndex < _TOTAL_PHASE_NUM; ucPhaseIndex++)
    {
        ScalerDDR3SetWritePhaseReg(pstCurrResult->pucWritePhaseOfClk);

        ScalerDDR3SetReadDQDelayTapReg(ucPhaseIndex);

        SET_SCAN_RESULT(spucScanResultRead, ucPhaseIndex, ScalerDDR3PhaseCheck());
    }

    //=================================================================
    // Summary scan result
    //=================================================================
    ScalerDDR3ScanPhasePrintScanResult(spucScanResultRead);

    DebugMessageMemoryPhaseCal("*** rDQ Delay Tap ***", 0);

    if(ScalerDDR3ScanPhaseResultExistPassRange(spucScanResultRead) == _FALSE)
    {
        return _FAIL;
    }

    pstCurrResult->ucRDQDelayTap = ScalerDDR3FindCentralValueOfLongestPassRange(spucScanResultRead, _SCAN_RESULT_READ_DELAY_TAP);

    //=================================================================
    // Set rDQ delay tap according to searched result
    //=================================================================
    ScalerDDR3SetReadDQDelayTapReg(pstCurrResult->ucRDQDelayTap);

    // Enable on the fly calibration function
    ScalerMaskSetDWord(PA9_08_CAL_CTRL1, 0xfffffffe, 0x00000001);
    Delay5us(g_ucDelay5usN);

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Check if search phase process has converged
// Input Value  : Previous phase search result, current phase search result
// Output Value : Process has converged -> _SUCCESS
//                If not                -> _FAIL
//--------------------------------------------------
bit ScalerDDR3SearchPhaseConvergenceCheck(StructPhaseInfo *pstPrevResult, StructPhaseInfo *pstCurrResult)
{
    BYTE ucClkIndex = 0;
    BYTE ucPrevValue = 0;
    BYTE ucCurrValue = 0;
    BYTE ucSearchResultDiff = 0;

    //=======================================================
    // Calculate difference between current result and
    // previous result
    //=======================================================
    for(ucClkIndex = 0; ucClkIndex < 7; ucClkIndex++)
    {
        if(ucClkIndex < 6)
        {
            ucCurrValue = pstCurrResult->pucWritePhaseOfClk[ucClkIndex];
            ucPrevValue = pstPrevResult->pucWritePhaseOfClk[ucClkIndex];
        }
        else
        {
            ucCurrValue = pstCurrResult->ucRDQDelayTap;
            ucPrevValue = pstPrevResult->ucRDQDelayTap;
        }

        ucSearchResultDiff = PHASE_DIFF(ucCurrValue, ucPrevValue);
        ucSearchResultDiff = (ucSearchResultDiff > (_TOTAL_PHASE_NUM - ucSearchResultDiff)) ? (_TOTAL_PHASE_NUM - ucSearchResultDiff) : ucSearchResultDiff;

        //=======================================================
        // If the difference exceeds the threshold, return _FAIL
        //=======================================================
        if(ucSearchResultDiff > _SEARCH_PHASE_ITERATION_CONVERGE_THESHOLD)
        {
            return _FAIL;
        }
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DDR search phase
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3SearchPhase(void)
{
    StructPhaseInfo structPrevFoundPhase;
    StructPhaseInfo structCurrFoundPhase;

    BYTE ucIterationIndex = 0;
    bit bSearchPhaseStatus = _FALSE;

    // Reset search phase test data
    g_bDDRSearchPhaseMCUModeTestDataReset = _TRUE;

    //===========================================
    // Set initial phase
    //===========================================
    structPrevFoundPhase.pucWritePhaseOfClk[0] = _DDR3_PHASE_CAL_INIT_PHASE_CLK0;    // Internal Clock
    structPrevFoundPhase.pucWritePhaseOfClk[1] = _DDR3_PHASE_CAL_INIT_PHASE_CLK1;    // wDQ01
    structPrevFoundPhase.pucWritePhaseOfClk[2] = _DDR3_PHASE_CAL_INIT_PHASE_CLK2;    // Pad Clock
    structPrevFoundPhase.pucWritePhaseOfClk[3] = _DDR3_PHASE_CAL_INIT_PHASE_CLK3;    // wDQS01
    structPrevFoundPhase.pucWritePhaseOfClk[4] = _DDR3_PHASE_CAL_INIT_PHASE_CLK4;    // wDQS23
    structPrevFoundPhase.pucWritePhaseOfClk[5] = _DDR3_PHASE_CAL_INIT_PHASE_CLK5;    // wDQ23
    structPrevFoundPhase.ucRDQDelayTap = _DDR3_PHASE_CAL_INIT_RDQ_DELAY_TAP;        // rDQ delay tap

#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE)
    ScalerDDR3ScanPhaseFRCModeDDRClientAccessCtrl(_DISABLE);
#endif

    for(ucIterationIndex = 0; ucIterationIndex < _SEARCH_PHASE_MAX_ITERATION_NUM; ucIterationIndex++)
    {
        bSearchPhaseStatus = _SUCCESS;

        //===========================================
        // Search phase
        //===========================================
        DebugMessageMemoryPhaseCal("===================", 0);
#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_MCU_MODE)
        DebugMessageMemoryPhaseCal("_____MCU_Mode_____", 0);
#elif(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE)
        DebugMessageMemoryPhaseCal("_____FRC_Mode_____", 0);
#endif
        DebugMessageMemoryPhaseCal("___________Version:", 20150625);
        DebugMessageMemoryPhaseCal("___________Iteration:", ucIterationIndex);
        DebugMessageMemoryPhaseCal("===================", 0);

        //===========================================
        // Search phase - CLK
        //===========================================
        DebugMessageMemoryPhaseCal("====ScanPhase A====", 0);
        if(ScalerDDR3ScanPhaseA(&structPrevFoundPhase, &structCurrFoundPhase) == _FAIL)
        {
            bSearchPhaseStatus = _FAIL;
            continue;
        }

        //===========================================
        // Search phase - wDQS
        //===========================================
        DebugMessageMemoryPhaseCal("===================", 0);
#if(_SEARCH_PHASE_WRITE_LEVELING == _OFF)
        DebugMessageMemoryPhaseCal("====ScanPhase B====", 0);
        if(ScalerDDR3ScanPhaseB(&structPrevFoundPhase, &structCurrFoundPhase) == _FAIL)
        {
            bSearchPhaseStatus = _FAIL;
            continue;
        }
#else
        DebugMessageMemoryPhaseCal("====ScanPhase WL===", 0);
        ScalerDDR3ScanPhaseWriteLeveling(&structCurrFoundPhase);
#endif

        //===========================================
        // Search phase - wDQ
        //===========================================
        DebugMessageMemoryPhaseCal("===================", 0);
        DebugMessageMemoryPhaseCal("====ScanPhase C====", 0);
        if(ScalerDDR3ScanPhaseC(&structPrevFoundPhase, &structCurrFoundPhase) == _FAIL)
        {
            bSearchPhaseStatus = _FAIL;
            continue;
        }

        //===========================================
        // Search phase - rDQ delay tap
        //===========================================
        DebugMessageMemoryPhaseCal("===================", 0);
        DebugMessageMemoryPhaseCal("====ScanPhase E====", 0);
        if(ScalerDDR3ScanPhaseE(&structCurrFoundPhase) == _FAIL)
        {
            bSearchPhaseStatus = _FAIL;
            continue;
        }

        //===========================================
        // Print result of current iteration
        //===========================================
        ScalerDDR3ScanPhasePrintSearchPhaseResult(&structCurrFoundPhase, _PRINT_ITERATION_RESULT);

        //===========================================
        // Stop iteration if result has converged
        //===========================================
        if(ScalerDDR3SearchPhaseConvergenceCheck(&structPrevFoundPhase, &structCurrFoundPhase) == _SUCCESS)
        {
            DebugMessageMemoryPhaseCal("**Result Converged!! ", 0);
            break;
        }

        //===========================================
        // If has not yet converged, start next iteration,
        // update "previous found phase"
        //===========================================
        structPrevFoundPhase = structCurrFoundPhase;
    }

    //===========================================
    // Print final result
    //===========================================
    DebugMessageMemoryPhaseCal("===================", 0);

    if(bSearchPhaseStatus == _SUCCESS)
    {
        ScalerDDR3AvoidPadClkDutyIssue(&structCurrFoundPhase);

        ScalerDDR3ExcludePhaseInNoFlyZone(&structCurrFoundPhase);

        ScalerDDR3SetWritePhaseReg(structCurrFoundPhase.pucWritePhaseOfClk);

        ScalerDDR3SetReadDQDelayTapReg(structCurrFoundPhase.ucRDQDelayTap);

        ScalerDDR3ScanPhasePrintSearchPhaseResult(&structCurrFoundPhase, _PRINT_FINAL_RESULT);
    }
    else
    {
        DebugMessageMemoryPhaseCal("Search Phase Fail!!", 0);
    }

    DebugMessageMemoryPhaseCal("===================", 0);

#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE)
    ScalerDDR3ScanPhaseFRCModeDDRClientAccessCtrl(_ENABLE);
#endif
}
#endif

#if((_DDR3_PHASE_CHECK == _ON) || (_DDR3_PHASE_CALIBRATION == _ON))
//--------------------------------------------------
// Description  : Check Final Phase Margin
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDDR3SCheckFinalPhaseMargin(void)
{
    bit bCheck1Result = _FALSE;
    bit bCheck2Result = _FALSE;

    bCheck1Result = ScalerDDR3SCheckPhase1();
    bCheck2Result = ScalerDDR3SCheckPhase2();

    if((bCheck1Result == _SUCCESS) && (bCheck2Result == _SUCCESS))
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Check Phase 1
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDDR3SCheckPhase1(void)
{
    bit bPhaseSearch = _FALSE;
    BYTE pucCheckPhase[6] = {0};
    BYTE ucCheckAdrCnt = 0;
    BYTE ucCheckInteration = 0;
    BYTE ucCheckStartGood = 0;
    BYTE ucCheckStartBad = 0;
    BYTE ucTxClkCheckDiff = 0;
    BYTE ucRxCheckDiff = 0;
    BYTE ucCheckBest = 0;
    BYTE ucCheckResult = _FALSE;
    BYTE pucInitialCheckPhase[6] = {0};
    BYTE ucInitialRxDelayTap = 0;

    pucInitialCheckPhase[0] = ScalerGetByte(PA5_0B_SYS_PLL_DDR3_4);   // refrence Clk
    pucInitialCheckPhase[1] = ScalerGetByte(PA5_0A_SYS_PLL_DDR3_3);   // Tx Dq01
    pucInitialCheckPhase[2] = ScalerGetByte(PA5_09_SYS_PLL_DDR3_2);   // Tx Clk
    pucInitialCheckPhase[3] = ScalerGetByte(PA5_08_SYS_PLL_DDR3_1);   // Tx Dqs01
    pucInitialCheckPhase[4] = ScalerGetByte(PA5_0F_SYS_PLL_DDR4_4);   // Tx Dqs23
    pucInitialCheckPhase[5] = ScalerGetByte(PA5_0E_SYS_PLL_DDR4_3);   // Tx Dq23
    ucInitialRxDelayTap = ScalerGetByte(PA8_80_DQ0_1_DLYN_1);       // Rx Dq

#if(_PHASE_CHECK_DEBUG_MSG == _ON)
    DebugMessageMemoryPhaseCal("***** Check Phase1 Start= ", 0x00);
    DebugMessageMemoryPhaseCal("***** Clk0 Phase = ", pucInitialCheckPhase[0]);
    DebugMessageMemoryPhaseCal("***** Clk1 Phase = ", pucInitialCheckPhase[1]);
    DebugMessageMemoryPhaseCal("***** Clk2 Phase = ", pucInitialCheckPhase[2]);
    DebugMessageMemoryPhaseCal("***** Clk3 Phase = ", pucInitialCheckPhase[3]);
    DebugMessageMemoryPhaseCal("***** Clk4 Phase = ", pucInitialCheckPhase[4]);
    DebugMessageMemoryPhaseCal("***** Clk5 Phase = ", pucInitialCheckPhase[5]);
    DebugMessageMemoryPhaseCal("** rDQ Delay Tap = ", ucInitialRxDelayTap);
#endif

    // Disable Related Block & Enable Idomain PG
    ScalerDDR3SCheckPhaseSetRelatedBlock(_OFF);

    // Enable on the fly calibration function
    ScalerMaskSetDWord(PA9_08_CAL_CTRL1, 0xfffffffe, 0x00000001);
    Delay5us(g_ucDelay5usN);

    //===========================================
    // Tx Clk Searching phase Check
    //===========================================
    for(ucCheckAdrCnt = 0; ucCheckAdrCnt < ((_TOTAL_CHECK_PHASE_NUM * 2) - 1); ucCheckAdrCnt++)
    {
        for(ucCheckInteration = 1; ucCheckInteration <= _PHASE_CHECK_ITERATION; ucCheckInteration++)
        {
            ScalerDDR3CheckPhaseFRCModeDDRClientAccessCtrl(_DISABLE);

            pucCheckPhase[1] = ((pucInitialCheckPhase[1] + ucCheckAdrCnt) % _TOTAL_CHECK_PHASE_NUM);
            pucCheckPhase[2] = ((pucInitialCheckPhase[2] + ucCheckAdrCnt) % _TOTAL_CHECK_PHASE_NUM);
            pucCheckPhase[3] = ((pucInitialCheckPhase[3] + ucCheckAdrCnt) % _TOTAL_CHECK_PHASE_NUM);
            pucCheckPhase[4] = ((pucInitialCheckPhase[4] + ucCheckAdrCnt) % _TOTAL_CHECK_PHASE_NUM);
            pucCheckPhase[5] = ((pucInitialCheckPhase[5] + ucCheckAdrCnt) % _TOTAL_CHECK_PHASE_NUM);

            ScalerDDR3CheckMemoryAddressChange((ucCheckAdrCnt % _TOTAL_CHECK_PHASE_NUM));

            ScalerDDR3CheckSetWritePhaseReg(pucCheckPhase);

            // DDR3 Rx Delay Tap Change
            ScalerDDR3CheckSetReadDQDelayTapReg(ucInitialRxDelayTap);

            ScalerDDR3CheckPhaseFRCModeDDRClientAccessCtrl(_ENABLE);

            pData[1] = ScalerDDR3CheckReadWriteFrame();

            if(pData[1] == _SUCCESS)
            {
                break;
            }
        }

        // Check Start Good Phase
        if((pData[1] == _SUCCESS) && (bPhaseSearch == _FALSE))
        {
            ucCheckStartGood = ucCheckAdrCnt;

            bPhaseSearch = _TRUE;
        }

        // Check Start Bad Phase
        if((pData[1] == _FALSE) && (bPhaseSearch == _TRUE))
        {
            ucCheckStartBad = ucCheckAdrCnt;

            pData[2] = ucCheckStartBad - ucCheckStartGood;

            if(pData[2] > ucTxClkCheckDiff)
            {
                ucTxClkCheckDiff = pData[2];

                ucCheckBest = (((ucCheckStartGood + ucCheckStartBad) / 2) % _TOTAL_CHECK_PHASE_NUM);
            }

            bPhaseSearch = _FALSE;
        }
    }

#if(_PHASE_CHECK_DEBUG_MSG == _ON)
    DebugMessageMemoryPhaseCal("Tx Clk Best Phase", (pucInitialCheckPhase[2] + ucCheckBest) % _TOTAL_CHECK_PHASE_NUM);
    DebugMessageMemoryPhaseCal("Tx Clk Good Pass Range", ucTxClkCheckDiff % _TOTAL_CHECK_PHASE_NUM);
    DebugMessageMemoryPhaseCal("Tx Clk Start Good Phase", ucCheckStartGood % _TOTAL_CHECK_PHASE_NUM);
    DebugMessageMemoryPhaseCal("Tx Clk End Good Phase", (ucCheckStartBad - 1) % _TOTAL_CHECK_PHASE_NUM);
#endif

    // For Rx Config Initial
    ucCheckStartGood = 0;
    ucCheckStartBad = 0;
    ucCheckBest = 0;
    bPhaseSearch = _FALSE;

    //===========================================
    // Rx Searching phase Check
    //===========================================
    // Disable on the fly calibration function
    ScalerMaskSetDWord(PA9_08_CAL_CTRL1, 0xfffffffe, 0x00000000);
    Delay5us(g_ucDelay5usN);

    // For Rx Check
    for(ucCheckAdrCnt = 0; ucCheckAdrCnt < _TOTAL_CHECK_PHASE_NUM; ucCheckAdrCnt++)
    {
        for(ucCheckInteration = 1; ucCheckInteration <= _PHASE_CHECK_ITERATION; ucCheckInteration++)
        {
            // Disable All FRC Client
            ScalerDDR3CheckPhaseFRCModeDDRClientAccessCtrl(_DISABLE);

            // DDR3 Memory Row Address And Mux Change
            ScalerDDR3CheckMemoryAddressChange(ucCheckAdrCnt);

            // DDR3 PLL Tx Phase Change
            ScalerDDR3CheckSetWritePhaseReg(pucInitialCheckPhase);

            // DDR3 Rx Delay Tap Change
            ScalerDDR3CheckSetReadDQDelayTapReg(ucCheckAdrCnt);

            // Enable FRC Client
            ScalerDDR3CheckPhaseFRCModeDDRClientAccessCtrl(_ENABLE);

            // FRC Frame Check
            pData[1] = ScalerDDR3CheckReadWriteFrame();

            if(pData[1] == _SUCCESS)
            {
                break;
            }
        }

        // Check Rx Start Good Phase
        if((pData[1] == _SUCCESS) && (bPhaseSearch == _FALSE))
        {
            ucCheckStartGood = ucCheckAdrCnt;

            bPhaseSearch = _TRUE;
        }

        // Check Rx Start Bad Phase
        if((pData[1] == _FALSE) && (bPhaseSearch == _TRUE))
        {
            ucCheckStartBad = ucCheckAdrCnt;

            pData[2] = ucCheckStartBad - ucCheckStartGood;

            if(pData[2] > ucRxCheckDiff)
            {
                ucRxCheckDiff = pData[2];

                ucCheckBest = (((ucCheckStartGood + ucCheckStartBad) / 2) % _TOTAL_CHECK_PHASE_NUM);
            }

            bPhaseSearch = _FALSE;
        }
    }

#if(_PHASE_CHECK_DEBUG_MSG == _ON)
    DebugMessageMemoryPhaseCal("Rx Best Phase", ucCheckBest);
    DebugMessageMemoryPhaseCal("Rx Good Pass Range", ucRxCheckDiff);
    DebugMessageMemoryPhaseCal("Rx Start Good Phase", ucCheckStartGood);
    DebugMessageMemoryPhaseCal("Rx End Good Phase", ucCheckStartBad - 1);
#endif

    // Check Phase1 Criterion Tx +- 16/Rx +- 5
    if((ucTxClkCheckDiff >= 32) && (ucRxCheckDiff >= 10))
    {
        ucCheckResult = _SUCCESS;
    }

    ScalerDDR3CheckPhaseFRCModeDDRClientAccessCtrl(_DISABLE);

    // DDR3 Restore Tx Phase
    ScalerDDR3CheckSetWritePhaseReg(pucInitialCheckPhase);

    // DDR3 Restore Rx Delay Tap
    ScalerDDR3CheckSetReadDQDelayTapReg(ucInitialRxDelayTap);

    // Enable on the fly calibration function
    ScalerMaskSetDWord(PA9_08_CAL_CTRL1, 0xfffffffe, 0x00000001);
    Delay5us(g_ucDelay5usN);

    // Enable Related Block & Disable Idomain PG
    ScalerDDR3SCheckPhaseSetRelatedBlock(_ON);

    // Enable All FRC Client
    ScalerDDR3CheckPhaseFRCModeDDRClientAccessCtrl(_ENABLE);

    if(ucCheckResult == _SUCCESS)
    {
        DebugMessageMemoryPhaseCal("Check Phase1 PASS", 0x00);
        return _SUCCESS;
    }
    else
    {
        DebugMessageMemoryPhaseCal("Check Phase1 FAIL", 0x00);
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Check Phase 2
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDDR3SCheckPhase2(void)
{
    BYTE pucCheckPhase[6] = {0};
    BYTE ucCheckInitialPhase = 0;
    BYTE ucCheckInitialPhase2 = 0;
    BYTE ucCheckAdrCnt = 0;
    BYTE ucCheckInteration = 0;
    BYTE ucCheckPhaseResult = 0;
    BYTE ucChecClkCont = 32;
    BYTE ucChecDqsCont = 10;
    BYTE pucInitialCheckPhase[6] = {0};
    BYTE ucInitialRxDelayTap = 0;

    pucInitialCheckPhase[0] = ScalerGetByte(PA5_0B_SYS_PLL_DDR3_4);   // refrence Clk
    pucInitialCheckPhase[1] = ScalerGetByte(PA5_0A_SYS_PLL_DDR3_3);   // Tx Dq01
    pucInitialCheckPhase[2] = ScalerGetByte(PA5_09_SYS_PLL_DDR3_2);   // Tx Clk
    pucInitialCheckPhase[3] = ScalerGetByte(PA5_08_SYS_PLL_DDR3_1);   // Tx Dqs01
    pucInitialCheckPhase[4] = ScalerGetByte(PA5_0F_SYS_PLL_DDR4_4);   // Tx Dqs23
    pucInitialCheckPhase[5] = ScalerGetByte(PA5_0E_SYS_PLL_DDR4_3);   // Tx Dq23
    ucInitialRxDelayTap = ScalerGetByte(PA8_80_DQ0_1_DLYN_1);        // Rx Dq

#if(_PHASE_CHECK_DEBUG_MSG == _ON)
    DebugMessageMemoryPhaseCal("***** Check Phase2 Start= ", 0x00);
    DebugMessageMemoryPhaseCal("***** Clk0 Phase = ", pucInitialCheckPhase[0]);
    DebugMessageMemoryPhaseCal("***** Clk1 Phase = ", pucInitialCheckPhase[1]);
    DebugMessageMemoryPhaseCal("***** Clk2 Phase = ", pucInitialCheckPhase[2]);
    DebugMessageMemoryPhaseCal("***** Clk3 Phase = ", pucInitialCheckPhase[3]);
    DebugMessageMemoryPhaseCal("***** Clk4 Phase = ", pucInitialCheckPhase[4]);
    DebugMessageMemoryPhaseCal("***** Clk5 Phase = ", pucInitialCheckPhase[5]);
    DebugMessageMemoryPhaseCal("** rDQ Delay Tap = ", ucInitialRxDelayTap);
#endif

    // Disable Related Block & Enable Idomain PG
    ScalerDDR3SCheckPhaseSetRelatedBlock(_OFF);

    //===========================================
    // Tx Clk Searching phase Check
    //===========================================
    // Enable on the fly calibration function
    ScalerMaskSetDWord(PA9_08_CAL_CTRL1, 0xfffffffe, 0x00000001);
    Delay5us(g_ucDelay5usN);

    ucCheckInitialPhase = ((pucInitialCheckPhase[2] + _TOTAL_CHECK_PHASE_NUM - (ucChecClkCont / 2)) % _TOTAL_CHECK_PHASE_NUM);

    for(ucCheckAdrCnt = 0; ucCheckAdrCnt < ucChecClkCont; ucCheckAdrCnt++)
    {
        for(ucCheckInteration = 1; ucCheckInteration <= _PHASE_CHECK_ITERATION; ucCheckInteration++)
        {
            ScalerDDR3CheckPhaseFRCModeDDRClientAccessCtrl(_DISABLE);

            pucCheckPhase[1] = pucInitialCheckPhase[1];
            pucCheckPhase[2] = ((ucCheckInitialPhase + ucCheckAdrCnt) % _TOTAL_CHECK_PHASE_NUM);
            pucCheckPhase[3] = pucInitialCheckPhase[3];
            pucCheckPhase[4] = pucInitialCheckPhase[4];
            pucCheckPhase[5] = pucInitialCheckPhase[5];

            ScalerDDR3CheckMemoryAddressChange(ucCheckAdrCnt);

            ScalerDDR3CheckSetWritePhaseReg(pucCheckPhase);

            // DDR3 Rx Delay Tap Change
            ScalerDDR3CheckSetReadDQDelayTapReg(ucInitialRxDelayTap);

            ScalerDDR3CheckPhaseFRCModeDDRClientAccessCtrl(_ENABLE);

            pData[1] = ScalerDDR3CheckReadWriteFrame();

            if(pData[1] == _SUCCESS)
            {
                break;
            }
            else
            {
                if(ucCheckInteration == _PHASE_CHECK_ITERATION)
                {
                    // Tx Clk Fail
                    ucCheckPhaseResult |= _BIT0;
                }
            }
        }
    }

    //===========================================
    // Tx Dqs Searching phase Check
    //===========================================
    ucCheckInitialPhase = ((pucInitialCheckPhase[3] + _TOTAL_CHECK_PHASE_NUM - (ucChecDqsCont / 2)) % _TOTAL_CHECK_PHASE_NUM);
    ucCheckInitialPhase2 = ((pucInitialCheckPhase[4] + _TOTAL_CHECK_PHASE_NUM - (ucChecDqsCont / 2)) % _TOTAL_CHECK_PHASE_NUM);

    for(ucCheckAdrCnt = 0; ucCheckAdrCnt < ucChecDqsCont; ucCheckAdrCnt++)
    {
        for(ucCheckInteration = 1; ucCheckInteration <= _PHASE_CHECK_ITERATION; ucCheckInteration++)
        {
            ScalerDDR3CheckPhaseFRCModeDDRClientAccessCtrl(_DISABLE);

            pucCheckPhase[1] = pucInitialCheckPhase[1];
            pucCheckPhase[2] = pucInitialCheckPhase[2];
            pucCheckPhase[3] = ((ucCheckInitialPhase + ucCheckAdrCnt) % _TOTAL_CHECK_PHASE_NUM);
            pucCheckPhase[4] = ((ucCheckInitialPhase2 + ucCheckAdrCnt) % _TOTAL_CHECK_PHASE_NUM);
            pucCheckPhase[5] = pucInitialCheckPhase[5];

            ScalerDDR3CheckMemoryAddressChange(ucCheckAdrCnt);

            ScalerDDR3CheckSetWritePhaseReg(pucCheckPhase);

            // DDR3 Rx Delay Tap Change
            ScalerDDR3CheckSetReadDQDelayTapReg(ucInitialRxDelayTap);

            ScalerDDR3CheckPhaseFRCModeDDRClientAccessCtrl(_ENABLE);

            pData[1] = ScalerDDR3CheckReadWriteFrame();

            if(pData[1] == _SUCCESS)
            {
                break;
            }
            else
            {
                if(ucCheckInteration == _PHASE_CHECK_ITERATION)
                {
                    // Tx Dqs Fail
                    ucCheckPhaseResult |= _BIT1;
                }
            }
        }
    }

    //===========================================
    // Tx Dq Searching phase Check
    //===========================================
    ucCheckInitialPhase = ((pucInitialCheckPhase[1] + _TOTAL_CHECK_PHASE_NUM - (ucChecDqsCont / 2)) % _TOTAL_CHECK_PHASE_NUM);
    ucCheckInitialPhase2 = ((pucInitialCheckPhase[5] + _TOTAL_CHECK_PHASE_NUM - (ucChecDqsCont / 2)) % _TOTAL_CHECK_PHASE_NUM);

    for(ucCheckAdrCnt = 0; ucCheckAdrCnt < ucChecDqsCont; ucCheckAdrCnt++)
    {
        for(ucCheckInteration = 1; ucCheckInteration <= _PHASE_CHECK_ITERATION; ucCheckInteration++)
        {
            ScalerDDR3CheckPhaseFRCModeDDRClientAccessCtrl(_DISABLE);

            pucCheckPhase[1] = ((ucCheckInitialPhase + ucCheckAdrCnt) % _TOTAL_CHECK_PHASE_NUM);
            pucCheckPhase[2] = pucInitialCheckPhase[2];
            pucCheckPhase[3] = pucInitialCheckPhase[3];
            pucCheckPhase[4] = pucInitialCheckPhase[4];
            pucCheckPhase[5] = ((ucCheckInitialPhase2 + ucCheckAdrCnt) % _TOTAL_CHECK_PHASE_NUM);

            ScalerDDR3CheckMemoryAddressChange(ucCheckAdrCnt);

            ScalerDDR3CheckSetWritePhaseReg(pucCheckPhase);

            // DDR3 Rx Delay Tap Change
            ScalerDDR3CheckSetReadDQDelayTapReg(ucInitialRxDelayTap);

            ScalerDDR3CheckPhaseFRCModeDDRClientAccessCtrl(_ENABLE);

            pData[1] = ScalerDDR3CheckReadWriteFrame();

            if(pData[1] == _SUCCESS)
            {
                break;
            }
            else
            {
                if(ucCheckInteration == _PHASE_CHECK_ITERATION)
                {
                    // Tx Dq Fail
                    ucCheckPhaseResult |= _BIT2;
                }
            }
        }
    }

    //===========================================
    // Rx Searching phase Check
    //===========================================
    // Disable on the fly calibration function
    ScalerMaskSetDWord(PA9_08_CAL_CTRL1, 0xfffffffe, 0x00000000);
    Delay5us(g_ucDelay5usN);

    ucCheckInitialPhase = ((ucInitialRxDelayTap + _TOTAL_CHECK_PHASE_NUM - (ucChecDqsCont / 2)) % _TOTAL_CHECK_PHASE_NUM);

    for(ucCheckAdrCnt = 0; ucCheckAdrCnt < ucChecDqsCont; ucCheckAdrCnt++)
    {
        for(ucCheckInteration = 1; ucCheckInteration <= _PHASE_CHECK_ITERATION; ucCheckInteration++)
        {
            ScalerDDR3CheckPhaseFRCModeDDRClientAccessCtrl(_DISABLE);

            ScalerDDR3CheckMemoryAddressChange(ucCheckAdrCnt);

            ScalerDDR3CheckSetWritePhaseReg(pucInitialCheckPhase);

            pData[0] = ((ucCheckInitialPhase + ucCheckAdrCnt) % _TOTAL_CHECK_PHASE_NUM);

            // DDR3 Rx Delay Tap Change
            ScalerDDR3CheckSetReadDQDelayTapReg(pData[0]);

            ScalerDDR3CheckPhaseFRCModeDDRClientAccessCtrl(_ENABLE);

            pData[1] = ScalerDDR3CheckReadWriteFrame();

            if(pData[1] == _SUCCESS)
            {
                break;
            }
            else
            {
                if(ucCheckInteration == _PHASE_CHECK_ITERATION)
                {
                    // Rx Dq Fail
                    ucCheckPhaseResult |= _BIT3;
                }
            }
        }
    }

    ScalerDDR3CheckPhaseFRCModeDDRClientAccessCtrl(_DISABLE);
    ScalerDDR3CheckSetWritePhaseReg(pucInitialCheckPhase);
    ScalerDDR3CheckMemoryAddressChange(ucInitialRxDelayTap);

    // Enable on the fly calibration function
    ScalerMaskSetDWord(PA9_08_CAL_CTRL1, 0xfffffffe, 0x00000001);
    Delay5us(g_ucDelay5usN);

    // Enable Related Block & Disable Idomain PG
    ScalerDDR3SCheckPhaseSetRelatedBlock(_ON);

    // Enable All FRC Client
    ScalerDDR3CheckPhaseFRCModeDDRClientAccessCtrl(_ENABLE);

    if(ucCheckPhaseResult == 0x00)
    {
        DebugMessageMemoryPhaseCal("Check Phase2 PASS", 0x00);
        return _SUCCESS;
    }
    else
    {
        DebugMessageMemoryPhaseCal("Check Phase2 FAIL", ucCheckPhaseResult);
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Check Phase Set
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDDR3SCheckPhaseSetRelatedBlock(bit bEnable)
{
    if(bEnable == _ON)
    {
#if(_OD_SUPPORT == _ON)
        // Enable OD Function
        ScalerODEnable(_FUNCTION_ON);
#endif

        // Enable I-dither
        ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~_BIT5, _BIT5);
        ScalerSetBit(P40_89_I_DITHER_COMMON_CTRL1_M2, ~_BIT5, _BIT5);

        // Enalbe Global Double Buffer
        ScalerGlobalDoubleBufferEnable(_ENABLE);

        // Enable Watch Dog
        ScalerGlobalPathWatchDog(_INPUT_PATH_ALL, _ENABLE);

        // Disable I-domain random gen
        ScalerSetBit(P0_10_M1_VGIP_CTRL, ~_BIT7, 0x00);
        ScalerSetBit(P40_10_M2_VGIP_CTRL, ~_BIT7, 0x00);
    }
    else
    {
#if(_OD_SUPPORT == _ON)
        //===========================================
        // Disable OD
        //===========================================
        ScalerODEnable(_FUNCTION_OFF);
#endif

        // Disable I-dither
        ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~_BIT5, 0x00);
        ScalerSetBit(P40_89_I_DITHER_COMMON_CTRL1_M2, ~_BIT5, 0x00);

        // Disable Global Double
        ScalerGlobalDoubleBufferEnable(_DISABLE);

        // Disable Watch Dog
        ScalerGlobalPathWatchDog(_INPUT_PATH_ALL, _DISABLE);

#if(_DDR3_PHASE_CAL_FRC_MODE_INTERNAL_PG == _ON)
        // Enable I-domain random gen
        ScalerSetBit(P0_10_M1_VGIP_CTRL, ~_BIT7, _BIT7);
        ScalerSetBit(P40_10_M2_VGIP_CTRL, ~_BIT7, _BIT7);
#else
        // Disable I-domain random gen
        ScalerSetBit(P0_10_M1_VGIP_CTRL, ~_BIT7, 0x00);
        ScalerSetBit(P40_10_M2_VGIP_CTRL, ~_BIT7, 0x00);
#endif
    }
}

//--------------------------------------------------
// Description  : FRC(M1, M2) client access control
// Input Value  : Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerDDR3CheckPhaseFRCModeDDRClientAccessCtrl(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable M1, M2 FRC Capture
        ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_STOP, _INPUT_PATH_M1_M2);
        ScalerFRCEn(_FRC_CAPTURE_ONOFF, _INPUT_PATH_M1_M2, _ENABLE);

        // Enable M1, M2 FRC Display
        ScalerFRCEn(_FRC_DISPLAY_ONOFF, _INPUT_PATH_M1_M2, _ENABLE);
        ScalerGlobalDDomainDBApply(_DB_APPLY_POLLING);
    }
    else
    {
        // Disable M1, M2, S1 and S2 FRC Capture
        ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_STOP, _INPUT_PATH_M1_M2);
        ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~_BIT7, 0x00);
        ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~_BIT7, 0x00);
        ScalerSetBit(P85_27_CAP_S1_DDR_CTRL1, ~_BIT7, 0x00);
        ScalerSetBit(PC5_27_CAP_S2_DDR_CTRL1, ~_BIT7, 0x00);

        // Disable M1, M2, S1 and S2 FRC Display
        ScalerFRCEn(_FRC_DISPLAY_ONOFF, _INPUT_PATH_ALL, _DISABLE);
        ScalerGlobalDDomainDBApply(_DB_APPLY_POLLING);
    }
}

//--------------------------------------------------
// Description  : Write Address Change
// Input Value  : ucAddress
// Output Value : None
//--------------------------------------------------
void ScalerDDR3CheckMemoryAddressChange(DWORD ulAddress)
{
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
    ScalerSetDWord(P5_00_CAP_M1_MEM_ADDR_MSB, (ulAddress << 12));
    ScalerSetDWord(P60_00_CAP_M2_MEM_ADDR_MSB, ((ulAddress + 341) << 12));
    ScalerSetDWord(P5_80_DISP_M1_READ_ADDR_MSB, (ulAddress << 12));
    ScalerSetDWord(P60_80_DISP_M2_READ_ADDR_MSB, ((ulAddress + 341) << 12));

#elif((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_1PC)
    ScalerSetDWord(P5_00_CAP_M1_MEM_ADDR_MSB, (ulAddress << 11));
    ScalerSetDWord(P60_00_CAP_M2_MEM_ADDR_MSB, ((ulAddress + 341) << 11));
    ScalerSetDWord(P5_80_DISP_M1_READ_ADDR_MSB, (ulAddress << 11));
    ScalerSetDWord(P60_80_DISP_M2_READ_ADDR_MSB, ((ulAddress + 341) << 11));
#endif
}

//--------------------------------------------------
// Description  : Set control registers of specific phase set
// Input Value  : Phase of Clk0~Clk5(range: 0~63)
// Output Value : None
//--------------------------------------------------
void ScalerDDR3CheckSetWritePhaseReg(BYTE pucPhaseOfClk[6])
{
    BYTE ucSyncSel = 0x00;
    BYTE ucPart3OfSysPllSetting5 = 0x01;
    BYTE ucPart4OfSysPllSetting5 = 0x11;

    ScalerDDR3CheckPhaseDDRRelatedBlockReset();

    ScalerDDR3CheckPLLOutputCtrl(_DISABLE);

    //====================================================
    // Set DDR PLL phase setting
    //====================================================
    pData[0] = pucPhaseOfClk[3];
    pData[1] = pucPhaseOfClk[2];
    pData[2] = pucPhaseOfClk[1];
    pData[3] = pucPhaseOfClk[0];
    ScalerSetDWord(PA5_08_SYS_PLL_DDR3_1, PDATA_DWORD(0));

    // Fast version of "if((16 <= phase <= 31) OR (48 <= phase <= 63)), then corresponding SyncSel bit is set to 1"
    ucSyncSel |= (((pucPhaseOfClk[0] & _BIT4) == _BIT4) ? _BIT0 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[1] & _BIT4) == _BIT4) ? _BIT1 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[2] & _BIT4) == _BIT4) ? _BIT2 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[3] & _BIT4) == _BIT4) ? _BIT3 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[4] & _BIT4) == _BIT4) ? _BIT4 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[5] & _BIT4) == _BIT4) ? _BIT5 : 0x00);

    pData[0] = ucSyncSel;
    pData[1] = 0x00;
    pData[2] = pucPhaseOfClk[5];
    pData[3] = pucPhaseOfClk[4];
    ScalerSetDWord(PA5_0C_SYS_PLL_DDR4_1, PDATA_DWORD(0));


    ucPart3OfSysPllSetting5 |= (((pucPhaseOfClk[4] > 31) && (pucPhaseOfClk[4] < 64)) ? 0x02 : 0x00);
    ucPart4OfSysPllSetting5 |= (((pucPhaseOfClk[3] > 31) && (pucPhaseOfClk[3] < 64)) ? 0x20 : 0x00);
    ucPart4OfSysPllSetting5 |= (((pucPhaseOfClk[2] > 31) && (pucPhaseOfClk[2] < 64)) ? 0x02 : 0x00);
    pData[0] = 0x00;
    pData[1] = 0x00;
    pData[2] = ucPart3OfSysPllSetting5;
    pData[3] = ucPart4OfSysPllSetting5;
    ScalerSetDWord(PA5_1C_SYS_PLL5_1, PDATA_DWORD(0));

    ScalerDDR3CheckPLLOutputCtrl(_ENABLE);

    ScalerDDR3DCPHYInitial();
}

//--------------------------------------------------
// Description  : Reset DDR related block (DC Sys, DC Phy, System Bridge..)
// Input Value  : Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerDDR3CheckPhaseDDRRelatedBlockReset(void)
{
    // Set MPLL CLK
    ScalerPLLSetMPLLFreq((DWORD)_MEMORY_PLL_CLOCK * 1000);

    // Reset System Bridge
    ScalerSetBit(P37_A0_M_DOMAIN_SB_RESET, ~_BIT0, _BIT0);
    ScalerTimerDelayXms(2);
    ScalerSetBit(P37_A0_M_DOMAIN_SB_RESET, ~_BIT0, 0x00);
    ScalerTimerDelayXms(2);
    ScalerDDR3SystemBridgeInitial();

    // Reset DC Sys
    ScalerSetBit(P37_A0_M_DOMAIN_SB_RESET, ~_BIT1, _BIT1);
    ScalerTimerDelayXms(2);
    ScalerSetBit(P37_A0_M_DOMAIN_SB_RESET, ~_BIT1, 0x00);
    ScalerTimerDelayXms(2);
    ScalerDDR3DCSysInitial();

    // DDR PLL Disable CLK output, Reset PLL, Disable PLL
    ScalerSetDWord(PA5_00_SYS_PLL_DDR1_1, 0x000000FC);

    // Reset DC Phy
    ScalerSetBit(P37_90_M_DOMAIN_MCLK_SET, ~_BIT2, 0x00);
    ScalerTimerDelayXms(2);
    ScalerSetBit(P37_90_M_DOMAIN_MCLK_SET, ~_BIT2, _BIT2);
    ScalerTimerDelayXms(2);

    // Set DDR PLL CLK
    ScalerPLLSetDDRPLLFreq((DWORD)_MEMORY_DATA_RATE_SPEED * 1000);
}

//--------------------------------------------------
// Description  : DDR3PLL Output Control
// Input Value  : Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerDDR3CheckPLLOutputCtrl(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        ScalerMaskSetDWord(PA5_00_SYS_PLL_DDR1_1, 0xFFFFFF07, 0x00000000);

        for(pData[0] = 0; pData[0] < 5; pData[0]++)
        {
            Delay5us(g_ucDelay5usN);
        }
    }
    else // Disable
    {
        ScalerMaskSetDWord(PA5_00_SYS_PLL_DDR1_1, 0xFFFFFF07, 0x000000F8);

        Delay5us(g_ucDelay5usN);
    }
}

//--------------------------------------------------
// Description  : Set rDQ delay tap control registers
// Input Value  : rDQ delay tap
// Output Value : None
//--------------------------------------------------
void ScalerDDR3CheckSetReadDQDelayTapReg(BYTE ucRDQDelayTap)
{
    // Set read delay tap
    pData[0] = ucRDQDelayTap;
    pData[1] = ucRDQDelayTap;
    pData[2] = ucRDQDelayTap;
    pData[3] = ucRDQDelayTap;
    ScalerSetDWord(PA8_80_DQ0_1_DLYN_1, PDATA_DWORD(0));
    ScalerSetDWord(PA8_38_DC_MISC_1, 0x07000000);
}

//--------------------------------------------------
// Description  : Read Write Frame Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDDR3CheckReadWriteFrame(void)
{
    BYTE ucCRCRegOffset = 0;
    BYTE pucIDomainCRCValue[6] = {0};
    BYTE pucMDomainCRCValue[6] = {0};

    // Enable M1, M2 I-domain CRC output
    ScalerSetByte(P36_00_I_CRC_CTRL, 0x8C);

    // Enable M1, M2 M-domain CRC output
    ScalerSetByte(P36_40_M_CRC_CTRL, 0x0C);

    for(pData[0] = 0; pData[0] < _PHASE_CHECK_FRAME_COUNT; pData[0]++)
    {
        for(pData[1] = 0; pData[1] < sizeof(pucIDomainCRCValue); pData[1]++)
        {
            pucIDomainCRCValue[pData[1]] = 0;
            pucMDomainCRCValue[pData[1]] = 0;
        }

        //===========================================
        // Get I-domain CRC
        //===========================================
        // Wait until IVS_START
        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);
        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);
        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);

        // Read I-domain CRC (First 3 Bytes of M1 and M2 CRC)
        for(ucCRCRegOffset = 0; ucCRCRegOffset < (sizeof(pucIDomainCRCValue) / 2); ucCRCRegOffset++)
        {
            pucIDomainCRCValue[ucCRCRegOffset] = ScalerGetByte(P36_01_I_MAIN1_CRC_1 + ucCRCRegOffset);
            pucIDomainCRCValue[ucCRCRegOffset + (sizeof(pucIDomainCRCValue) / 2)] = ScalerGetByte(P36_07_I_MAIN2_CRC_1 + ucCRCRegOffset);
        }

        //===========================================
        // Get M-domain CRC
        //===========================================
        // Wait until DVS_START
        ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _DISPLAY_PATH_ALL);
        ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _DISPLAY_PATH_ALL);
        ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _DISPLAY_PATH_ALL);

        // Read M-domain CRC (First 3 Bytes of M1 and M2 CRC)
        for(ucCRCRegOffset = 0; ucCRCRegOffset < (sizeof(pucIDomainCRCValue) / 2); ucCRCRegOffset++)
        {
            pucMDomainCRCValue[ucCRCRegOffset] = ScalerGetByte(P36_41_M_M1_CRC_1 + ucCRCRegOffset);
            pucMDomainCRCValue[ucCRCRegOffset + (sizeof(pucIDomainCRCValue) / 2)] = ScalerGetByte(P36_47_M_M2_CRC_1 + ucCRCRegOffset);
        }

        //===========================================
        // Compare I-domain CRC with  M-domain CRC
        //===========================================
        if(memcmp(pucIDomainCRCValue, pucMDomainCRCValue, sizeof(pucIDomainCRCValue)) != 0)
        {
            // Disable M1, M2 I-domain CRC output
            ScalerSetByte(P36_00_I_CRC_CTRL, 0x00);

            // Disable M1, M2 M-domain CRC output
            ScalerSetByte(P36_40_M_CRC_CTRL, 0x00);

            return _FAIL;
        }
    }

    // Disable M1, M2 I-domain CRC output
    ScalerSetByte(P36_00_I_CRC_CTRL, 0x00);

    // Disable M1, M2 M-domain CRC output
    ScalerSetByte(P36_40_M_CRC_CTRL, 0x00);

    return _SUCCESS;
}
#endif // End of #if((_DDR3_PHASE_CHECK == _ON) || (_DDR3_PHASE_CALIBRATION == _ON))

#endif // End of #if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)


