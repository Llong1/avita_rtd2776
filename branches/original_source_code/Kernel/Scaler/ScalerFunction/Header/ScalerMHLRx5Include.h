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
// ID Code      : ScalerMHLRx5Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of MHL Adopter ID
//--------------------------------------------------
#define GET_MHL_RX5_ADOPTER_ID_DONE()                   (g_bMHLRx5AdopterIDDone)
#define SET_MHL_RX5_ADOPTER_ID_DONE()                   (g_bMHLRx5AdopterIDDone = _TRUE)
#define CLR_MHL_RX5_ADOPTER_ID_DONE()                   (g_bMHLRx5AdopterIDDone = _FALSE)

#define GET_MHL_RX5_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx5CbusResetForHTCDone)
#define SET_MHL_RX5_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx5CbusResetForHTCDone = _TRUE)
#define CLR_MHL_RX5_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx5CbusResetForHTCDone = _FALSE)

#define GET_MHL_RX5_SENT_MSC_DCAP_RDY()                 (g_bMHLRx5SentMscDcapRdy)
#define SET_MHL_RX5_SENT_MSC_DCAP_RDY()                 (g_bMHLRx5SentMscDcapRdy = _TRUE)
#define CLR_MHL_RX5_SENT_MSC_DCAP_RDY()                 (g_bMHLRx5SentMscDcapRdy = _FALSE)

#define GET_MHL_RX5_MHL_VERSION()                       (g_ucMHLRx5MhlVersion)
#define SET_MHL_RX5_MHL_VERSION(x)                      (g_ucMHLRx5MhlVersion = (x))
#define CLR_MHL_RX5_MHL_VERSION()                       (g_ucMHLRx5MhlVersion = 0x00)

#define GET_MHL_RX5_ADOPTER_ID_HBYTE()                  (g_ucMHLRx5AdopterIDH)
#define GET_MHL_RX5_ADOPTER_ID_LBYTE()                  (g_ucMHLRx5AdopterIDL)
#define CLR_MHL_RX5_ADOPTER_ID_HBYTE()                  (g_ucMHLRx5AdopterIDH = 0xFF)
#define CLR_MHL_RX5_ADOPTER_ID_LBYTE()                  (g_ucMHLRx5AdopterIDL = 0xFF)

#define GET_MHL_RX5_PROCESS_STATE()                     (g_stMHLRx5Process.b4MHLProcessState)
#define SET_MHL_RX5_PROCESS_STATE(x)                    (g_stMHLRx5Process.b4MHLProcessState = (x))

#define GET_MHL_RX5_READY_TO_TRANSMIT()                 (g_stMHLRx5Process.b1MHLTransmitStatus)
#define SET_MHL_RX5_READY_TO_TRANSMIT()                 (g_stMHLRx5Process.b1MHLTransmitStatus = _TRUE)
#define CLR_MHL_RX5_READY_TO_TRANSMIT()                 (g_stMHLRx5Process.b1MHLTransmitStatus = _FALSE)

#define GET_MHL_RX5_READY_TO_RESEND()                   (g_stMHLRx5Process.b1MHLResendStatus)
#define SET_MHL_RX5_READY_TO_RESEND()                   (g_stMHLRx5Process.b1MHLResendStatus = _TRUE)
#define CLR_MHL_RX5_READY_TO_RESEND()                   (g_stMHLRx5Process.b1MHLResendStatus = _FALSE)

#define GET_MHL_RX5_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx5Process.b1MHLSwitchPortDiscoveryDoneStatus)
#define SET_MHL_RX5_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx5Process.b1MHLSwitchPortDiscoveryDoneStatus = _TRUE)
#define CLR_MHL_RX5_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx5Process.b1MHLSwitchPortDiscoveryDoneStatus = _FALSE)

#define GET_MHL_RX5_WRITE_BURST_PROCESS_DONE()          (g_bMHLRx5WriteBurstProcessDone)
#define SET_MHL_RX5_WRITE_BURST_PROCESS_DONE()          (g_bMHLRx5WriteBurstProcessDone = _TRUE)
#define CLR_MHL_RX5_WRITE_BURST_PROCESS_DONE()          (g_bMHLRx5WriteBurstProcessDone = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucMHLRx5MhlVersion;
extern BYTE g_ucMHLRx5AdopterIDH;
extern BYTE g_ucMHLRx5AdopterIDL;
extern bit g_bMHLRx5AdopterIDDone;
extern bit g_bMHLRx5CbusResetForHTCDone;
extern bit g_bMHLRx5SentMscDcapRdy;
extern bit g_bMHLRx5WriteBurstProcessDone;

extern StructMHLProcessInfo g_stMHLRx5Process;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerMHLRx5DetectClkMode(void);
extern BYTE ScalerMHLRx5DetectClkMode_EXINT0(void);
extern bit ScalerMHLRx5MscSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue);
extern bit ScalerMHLRx5MscSendWriteBurst(BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode);

#endif // End of #if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

