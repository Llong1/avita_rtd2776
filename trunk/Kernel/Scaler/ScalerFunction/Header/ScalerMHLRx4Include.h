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
// ID Code      : ScalerMHLRx4Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of MHL Adopter ID
//--------------------------------------------------
//--------------------------------------------------
// Macros of MHL Adopter ID
//--------------------------------------------------
#define GET_MHL_RX4_ADOPTER_ID_DONE()                   (g_bMHLRx4AdopterIDDone)
#define SET_MHL_RX4_ADOPTER_ID_DONE()                   (g_bMHLRx4AdopterIDDone = _TRUE)
#define CLR_MHL_RX4_ADOPTER_ID_DONE()                   (g_bMHLRx4AdopterIDDone = _FALSE)

#define GET_MHL_RX4_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx4CbusResetForHTCDone)
#define SET_MHL_RX4_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx4CbusResetForHTCDone = _TRUE)
#define CLR_MHL_RX4_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx4CbusResetForHTCDone = _FALSE)

#define GET_MHL_RX4_SENT_MSC_DCAP_RDY()                 (g_bMHLRx4SentMscDcapRdy)
#define SET_MHL_RX4_SENT_MSC_DCAP_RDY()                 (g_bMHLRx4SentMscDcapRdy = _TRUE)
#define CLR_MHL_RX4_SENT_MSC_DCAP_RDY()                 (g_bMHLRx4SentMscDcapRdy = _FALSE)

#define GET_MHL_RX4_MHL_VERSION()                       (g_ucMHLRx4MhlVersion)
#define SET_MHL_RX4_MHL_VERSION(x)                      (g_ucMHLRx4MhlVersion = (x))
#define CLR_MHL_RX4_MHL_VERSION()                       (g_ucMHLRx4MhlVersion = 0x00)

#define GET_MHL_RX4_ADOPTER_ID_HBYTE()                  (g_ucMHLRx4AdopterIDH)
#define GET_MHL_RX4_ADOPTER_ID_LBYTE()                  (g_ucMHLRx4AdopterIDL)
#define CLR_MHL_RX4_ADOPTER_ID_HBYTE()                  (g_ucMHLRx4AdopterIDH = 0xFF)
#define CLR_MHL_RX4_ADOPTER_ID_LBYTE()                  (g_ucMHLRx4AdopterIDL = 0xFF)

#define GET_MHL_RX4_PROCESS_STATE()                     (g_stMHLRx4Process.b4MHLProcessState)
#define SET_MHL_RX4_PROCESS_STATE(x)                    (g_stMHLRx4Process.b4MHLProcessState = (x))

#define GET_MHL_RX4_READY_TO_TRANSMIT()                 (g_stMHLRx4Process.b1MHLTransmitStatus)
#define SET_MHL_RX4_READY_TO_TRANSMIT()                 (g_stMHLRx4Process.b1MHLTransmitStatus = _TRUE)
#define CLR_MHL_RX4_READY_TO_TRANSMIT()                 (g_stMHLRx4Process.b1MHLTransmitStatus = _FALSE)

#define GET_MHL_RX4_READY_TO_RESEND()                   (g_stMHLRx4Process.b1MHLResendStatus)
#define SET_MHL_RX4_READY_TO_RESEND()                   (g_stMHLRx4Process.b1MHLResendStatus = _TRUE)
#define CLR_MHL_RX4_READY_TO_RESEND()                   (g_stMHLRx4Process.b1MHLResendStatus = _FALSE)

#define GET_MHL_RX4_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx4Process.b1MHLSwitchPortDiscoveryDoneStatus)
#define SET_MHL_RX4_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx4Process.b1MHLSwitchPortDiscoveryDoneStatus = _TRUE)
#define CLR_MHL_RX4_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx4Process.b1MHLSwitchPortDiscoveryDoneStatus = _FALSE)

#define GET_MHL_RX4_WRITE_BURST_PROCESS_DONE()          (g_bMHLRx4WriteBurstProcessDone)
#define SET_MHL_RX4_WRITE_BURST_PROCESS_DONE()          (g_bMHLRx4WriteBurstProcessDone = _TRUE)
#define CLR_MHL_RX4_WRITE_BURST_PROCESS_DONE()          (g_bMHLRx4WriteBurstProcessDone = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucMHLRx4MhlVersion;
extern BYTE g_ucMHLRx4AdopterIDH;
extern BYTE g_ucMHLRx4AdopterIDL;
extern bit g_bMHLRx4AdopterIDDone;
extern bit g_bMHLRx4CbusResetForHTCDone;
extern bit g_bMHLRx4SentMscDcapRdy;
extern bit g_bMHLRx4WriteBurstProcessDone;

extern StructMHLProcessInfo g_stMHLRx4Process;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerMHLRx4DetectClkMode(void);
extern BYTE ScalerMHLRx4DetectClkMode_EXINT0(void);
extern bit ScalerMHLRx4MscSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue);
extern bit ScalerMHLRx4MscSendWriteBurst(BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode);

#endif // End of #if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

