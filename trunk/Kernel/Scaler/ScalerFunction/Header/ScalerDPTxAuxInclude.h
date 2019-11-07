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
// ID Code      : ScalerDPTxAuxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************



//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
//extern BYTE data g_ucEDIDPreferTiming[18];


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#if(_DP_TX_SUPPORT == _ON)
extern bit ScalerDpTxAuxNativeWrite(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
extern bit ScalerDpTxAuxNativeRead(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
extern bit ScalerDpTxAuxI2CoverWrite(BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray, bit bMOT);
extern bit ScalerDpTxAuxI2CoverRead(BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray, bit bMOT);
extern BYTE ScalerDpTxAuxNativeRead_EXINT0(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
#endif


