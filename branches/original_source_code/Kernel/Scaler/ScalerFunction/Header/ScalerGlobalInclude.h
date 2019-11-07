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
// ID Code      : ScalerGlobalInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of System Clock Frequency
//--------------------------------------------------
#define _GDI_CLK_DIV                                (ScalerGetBit(P80_06_GDI_CLK_DIVIDER, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) // GDI Clock Divider
#define _SYS_CLK_DIV                                (ScalerGetBit(P0_22_M1_FIFO_CLOCK_SELECT, (_BIT6 | _BIT5 | _BIT4 | _BIT3)) >> 3) // System Clock Divider
#define _SYS_USE_ISO_CLK                            ((bit)ScalerGetBit(P0_09_GA_POWER_CTRL, _BIT3) ? _TRUE : _FALSE)
#define _SYS_CLK_KHZ                                (DWORD)((bit)ScalerGetBit(P0_22_M1_FIFO_CLOCK_SELECT, _BIT2) ? (((DWORD)1000 * _M2PLL_CLK_MHZ) / _SYS_CLK_DIV) : (_SYS_USE_ISO_CLK ? _INTERNAL_OSC_XTAL : _EXT_XTAL))

#define _DOUBLE_BUFFER_WAIT_TIME                    100

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

typedef struct
{
    BYTE ucGroupNum;
    EnumInputDataPath penumGroup[4];
} StructDBDataPathGroup;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerGlobalIRQControl(bit bEn);
extern void ScalerGlobalResetPortMapping(void);
extern void ScalerGlobalOsdInitial(void);

#if((_DISPLAY_ROTATION_SUPPORT == _ON) || (_DDR3_PHASE_CHECK == _ON) || (_DDR3_PHASE_CALIBRATION == _ON) || (_FREESYNC_OD_MEASURE == _ON))
extern void ScalerGlobalDoubleBufferEnable(bit bEn);
#endif

extern void ScalerGlobalIDDomainDBSetTriggerEvent(EnumInputDataPath enumSelectedDataPath, EnumDBIDomainTriggerEvent enumTriggerEvent);

extern void ScalerGlobalIDDomainDBSetBufferAddress(StructDBDataPathGroup *pstDataPathGroupInfo);
extern void ScalerGlobalIDDomainDBGetDataPathGroup(EnumInputDataPath enumSelectedDataPath, StructDBDataPathGroup *pstDataPathGroupInfo);

#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
extern void ScalerGlobalSetInterrupt(EnumIRQ enumIRQType, BYTE ucEn);
#endif

extern bit ScalerGlobalGetDBStatus(void);
extern void ScalerGlobalIDDomainDBClearReadyBit(EnumInputDataPath enumSelectedDataPath);

