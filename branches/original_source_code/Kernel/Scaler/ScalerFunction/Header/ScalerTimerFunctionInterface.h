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
// ID Code      : ScalerTimerFunctionInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// INTERFACE STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
extern bit g_bNotifyTimer2Int;
extern volatile WORD data g_usTimerCounter;

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
extern BYTE data g_ucTimerQuarterCount;
#endif

#if(_INSTANT_TIMER_EVENT_0 == _ON)
extern BYTE g_ucTimerCountHByte0;
extern BYTE g_ucTimerCountLByte0;
extern WORD g_usTimerEventPeriod0;
extern WORD g_usTimerAxisCnt0;
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
extern BYTE g_ucTimerCountHByte1;
extern BYTE g_ucTimerCountLByte1;
extern WORD g_usTimerEventPeriod1;
extern WORD g_usTimerAxisCnt1;
#endif
//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
#if(_WD_TIMER_INT_SUPPORT == _ON)
extern void ScalerTimerWDEventProc_WDINT(void);
#endif

#if(_INSTANT_TIMER_EVENT_0 == _ON)
extern void ScalerTimer0SetTimerCount(WORD usTimerMs);
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
extern void ScalerTimer1SetTimerCount(WORD usTimerMs);
#endif

extern void ScalerTimerSetTimerCount(EnumScalerTimerOperationMode enumOperationMode);

#if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)
extern void ScalerTimerAddTimerCounter(void);
#endif

extern void ScalerTimerEventProc(EnumScalerTimerEventID enumEventID);
extern WORD ScalerTimerGetEventTime(BYTE ucEventIndex);
extern void ScalerTimerClrEventValid(BYTE ucEventIndex);
extern bit ScalerTimerCheckEventValid(BYTE ucEventIndex);
extern void ScalerTimerActiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID);
extern void ScalerTimerReactiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID);
extern void ScalerTimerCancelTimerEvent(EnumScalerTimerEventID enumEventID);
extern WORD ScalerTimerGetEventRemainTime(EnumScalerTimerEventID enumEventID);
extern bit ScalerTimerSearchActiveTimerEvent(EnumScalerTimerEventID enumEventID);

extern WORD ScalerTimerGetTimerCounter(void);
extern BYTE ScalerTimerGetEventID(BYTE ucEventIndex);
extern void ScalerTimerInitialTimerEvent(void);
extern void ScalerTimerDelayXms(WORD usNum);

#if(_HDCP_2_2_SUPPORT == _ON)
extern BYTE ScalerTimerPollingFlagProc_EXINT0(WORD usTimeout, WORD usRegister, BYTE ucBit, bit bSuccess);
#endif

extern bit ScalerTimerWaitForEvent(EnumWaitEventType enumEvent);
extern void ScalerTimerWaitForActiveTimerEvent(EnumScalerTimerEventID enumEventID);
extern void ScalerTimerClrEventStatus(EnumWaitEventType enumEvent);
extern BYTE ScalerTimerGetEventStatus(EnumWaitEventType enumEvent);
extern bit ScalerTimerWaitForIDDomainEvent(EnumWaitEventType enumEvent, BYTE ucDataPath);
