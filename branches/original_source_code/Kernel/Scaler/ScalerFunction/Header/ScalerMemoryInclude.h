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
// ID Code      : ScalerMemoryInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// M domain Fifo bit
//--------------------------------------------------
#define _M_DOMAMAIN_FIFO_BIT                        (131072) // 512*128*2 bit

//--------------------------------------------------
// Memory Speed
//--------------------------------------------------
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
#define _DDR_PLL_CLOCK                              _MEMORY_SPEED_800MHZ
#define _MEMORY_DATA_RATE_SPEED                     (_DDR_PLL_CLOCK * 2)
#define _MEMORY_PLL_CLOCK                           (_DDR_PLL_CLOCK / 2)
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)
#define _MEMORY_PLL_CLOCK                           _MEMORY_SPEED_198MHZ
#define _MEMORY_DATA_RATE_SPEED                     _MEMORY_PLL_CLOCK
#endif

//--------------------------------------------------
// Memory Size
//--------------------------------------------------
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#define _MEMORY_BUS_WIDTH                           0
#define _MEMORY_SIZE                                0
#define _MEMORY_BIT_NUM                             0
#define _MEMORY_BANK                                0
#define _MEMORY_COL_PER_BANK                        256
#define _MEMORY_ROW                                 2048
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)

#if(_MEMORY_SIZE_CONFIG == _1M_16BIT_SDRAM)
#define _MEMORY_BUS_WIDTH                           16
#define _MEMORY_SIZE                                _MEMORY_16MB
#define _MEMORY_BIT_NUM                             16
#define _MEMORY_BANK                                2
#define _MEMORY_COL_PER_BANK                        256
#define _MEMORY_ROW                                 2048
#endif

#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)

#if(_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_1PC)
#define _MEMORY_BUS_WIDTH                           (16)
#define _MEMORY_SIZE                                (_MEMORY_1GB)
#define _MEMORY_BIT_NUM                             (16)
#define _MEMORY_BANK                                8
#define _MEMORY_COL_PER_BANK                        1024
#define _MEMORY_ROW                                 8192
#elif(_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_2PCS)
#define _MEMORY_BUS_WIDTH                           (16 * 2)
#define _MEMORY_SIZE                                (_MEMORY_1GB * 2)
#define _MEMORY_BIT_NUM                             (16 * 2)
#define _MEMORY_BANK                                8
#define _MEMORY_COL_PER_BANK                        1024
#define _MEMORY_ROW                                 8192
#elif(_MEMORY_SIZE_CONFIG == _2G_16BIT_GDDR3_1PC)
#define _MEMORY_BUS_WIDTH                           (16)
#define _MEMORY_SIZE                                (_MEMORY_2GB)
#define _MEMORY_BIT_NUM                             (16)
#define _MEMORY_BANK                                8
#define _MEMORY_COL_PER_BANK                        1024
#define _MEMORY_ROW                                 16384
#elif(_MEMORY_SIZE_CONFIG == _2G_16BIT_GDDR3_2PCS)
#define _MEMORY_BUS_WIDTH                           (16 * 2)
#define _MEMORY_SIZE                                (_MEMORY_2GB * 2)
#define _MEMORY_BIT_NUM                             (16 * 2)
#define _MEMORY_BANK                                8
#define _MEMORY_COL_PER_BANK                        1024
#define _MEMORY_ROW                                 16384
#elif(_MEMORY_SIZE_CONFIG == _4G_16BIT_GDDR3_1PC)
#define _MEMORY_BUS_WIDTH                           (16)
#define _MEMORY_SIZE                                (_MEMORY_4GB)
#define _MEMORY_BIT_NUM                             (16)
#define _MEMORY_BANK                                8
#define _MEMORY_COL_PER_BANK                        1024
#define _MEMORY_ROW                                 32768
#elif(_MEMORY_SIZE_CONFIG == _4G_16BIT_GDDR3_2PCS)
#define _MEMORY_BUS_WIDTH                           (16 * 2)
#define _MEMORY_SIZE                                (_MEMORY_4GB * 2)
#define _MEMORY_BIT_NUM                             (16 * 2)
#define _MEMORY_BANK                                8
#define _MEMORY_COL_PER_BANK                        1024
#define _MEMORY_ROW                                 32768
#endif

#endif

//--------------------------------------------------
// Memory Efficiency
//--------------------------------------------------
#define _MEMORY_EFFICIENCY_1P                       (85)
#define _MEMORY_EFFICIENCY_MULTI_P                  (80)

#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
#define _MEMORY_EFFICIENCY                          ((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P) ? (_MEMORY_EFFICIENCY_1P) : (_MEMORY_EFFICIENCY_MULTI_P))
#else
#define _MEMORY_EFFICIENCY                          (_MEMORY_EFFICIENCY_1P)
#endif


#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
//--------------------------------------------------
// Define Total Bandwidth
//--------------------------------------------------
#define _MEMORY_TOTAL_BW                            (1UL * _MEMORY_DATA_RATE_SPEED * _MEMORY_EFFICIENCY / 10)
#define _MEMORY_TOTAL_BW_PIP                        (1UL * _MEMORY_DATA_RATE_SPEED * _MEMORY_EFFICIENCY_MULTI_P / 10)

//--------------------------------------------------
// Define FRC Bandwidth
//--------------------------------------------------
#define _FRC_CAP_BW                                 ((1UL * _PANEL_DH_WIDTH * _PANEL_DV_TOTAL * (_COLOR_DEPTH_10_BITS * 3) / _MEMORY_BUS_WIDTH / 10) * _PANEL_TYP_FRAME_RATE / 100)
#define _FRC_DISP_BW                                ((1UL * _PANEL_DH_WIDTH * _PANEL_DV_TOTAL * (_COLOR_DEPTH_10_BITS * 3) / _MEMORY_BUS_WIDTH / 10) * _PANEL_TYP_FRAME_RATE / 100)
#define _FRC_DISP_SSCG_BW                           (_FRC_DISP_BW * ((_DCLK_SPREAD_RANGE / _DIV_1) + _DCLK_SPREAD_RANGE_MARGIN) / 4 / 100)
#define _FRC_MAIN_BW                                ((_FRC_CAP_BW + _FRC_DISP_BW + _FRC_DISP_SSCG_BW) / 1000)// unit:100k

//--------------------------------------------------
// Define PIP Main Bandwidth By Panel
//--------------------------------------------------
#define _PIP_MAIN_BW                                (_FRC_MAIN_BW + _FRC_MAIN_BW / 20) // 5% margin

//--------------------------------------------------
// PIP Mode : Check Main Bandwidth
//--------------------------------------------------
#if(_PANEL_EXIST_MULTIPANEL == _OFF)
#if((_PIP_DISPLAY_SUPPORT == _ON) && (_PIP_MAIN_BW > _MEMORY_TOTAL_BW_PIP))
#warning "_PIP_DISPLAY_SUPPORT should be _OFF"
#endif
#endif

#endif // End of #if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    DWORD ulLineStep;
    DWORD ulBlockStep;
} StructMemoryLineBlockStep;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMemorySetFIFOFreq(EnumScalerFIFOFreq enumFIFOFreq);
extern void ScalerMemoryInitial(void);
extern WORD ScalerMemoryGetScaleUpDt(void);
extern void ScalerMemorySetFifoCapture(EnumInputDataPath enumInputDataPath, WORD usHWidth, WORD usVHeight);
extern void ScalerMemoryCompensateDtForLastLine(DWORD ulTargetLastLine, DWORD ulCurrentLastLine);
extern void ScalerMemorySetIVS2DVSLineDelay(WORD usIVS2DVSDelay);
extern void ScalerMemoryFineTuneIVS2DVSDelay(WORD usOldIVS2DVSDelay, WORD usNewIVS2DVSDelay, WORD usIVS2DVSChgLimit);

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
extern void ScalerMemoryReset(void);
extern void ScalerMemorySetFrameTrackingEnable(bit bEn);
#endif

#if(_FRC_SUPPORT == _ON)
extern void ScalerMemoryFrameTracking(void);
extern WORD ScalerMemoryGetMNRatio(void);
extern void ScalerMemoryCalculateLineStepAndBlockStep(DWORD ulHorSize, WORD usVerSize, StructMemoryLineBlockStep *pstMemoryLineBlockStep);
#endif

