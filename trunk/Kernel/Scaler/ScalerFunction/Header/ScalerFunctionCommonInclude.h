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
// ID Code      : ScalerFunctionCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "Global.h"
#include "Scaler_List.h"
#include "Project_List.h"
#include "Debug.h"

#if(_SCALER_TYPE == _RL6193_SERIES)
#include "RL6193_Gen_Option.h"
#include "RL6193_Series_FunctionCommonInclude.h"
#elif(_SCALER_TYPE == _RL6410_SERIES)
#include "RL6410_Gen_Option.h"
#include "RL6410_Series_FunctionCommonInclude.h"
#endif
#include "ScalerADCCommonInclude.h"
#include "ScalerAudioCommonInclude.h"
#include "ScalerAutoFuncCommonInclude.h"
#include "ScalerColorCommonInclude.h"
#include "ScalerDDomainCommonInclude.h"
#include "ScalerDDRCommonInclude.h"
#include "ScalerDPRx0HDCP2CommonInclude.h"
#include "ScalerDPRx1HDCP2CommonInclude.h"
#include "ScalerDebugCommonInclude.h"
#include "ScalerDisplayCommonInclude.h"
#include "ScalerDisplayDPTxCommonInclude.h"
#include "ScalerDPCommonInclude.h"
#include "ScalerDPRx0CommonInclude.h"
#include "ScalerDPRx1CommonInclude.h"
#include "ScalerDPRxMSTCommonInclude.h"
#include "ScalerDPTxAuxCommonInclude.h"
#include "ScalerDPTxCommonInclude.h"
#include "ScalerDPTxMSTCommonInclude.h"
#include "ScalerFormatConversionCommonInclude.h"
#include "ScalerFRCCommonInclude.h"
#include "ScalerGDIPHYCommonInclude.h"
#include "ScalerGDIPhyTxCommonInclude.h"
#include "ScalerGlobalCommonInclude.h"
#include "ScalerIDomainCommonInclude.h"
#include "ScalerIOSCCommonInclude.h"
#include "ScalerLDOCommonInclude.h"
#include "ScalerMcuCommonInclude.h"
#include "ScalerMeasureCommonInclude.h"
#include "ScalerMDomainCommonInclude.h"
#include "ScalerMemoryCommonInclude.h"
#include "ScalerMHLRx0CommonInclude.h"
#include "ScalerMHLRx1CommonInclude.h"
#include "ScalerMHLRx2CommonInclude.h"
#include "ScalerMHLRx3CommonInclude.h"
#include "ScalerMHLRx4CommonInclude.h"
#include "ScalerMHLRx5CommonInclude.h"
#include "ScalerNVRamCommonInclude.h"
#include "ScalerODCommonInclude.h"
#include "ScalerOsdCommonInclude.h"
#include "ScalerPinshareCommonInclude.h"
#include "ScalerPLLCommonInclude.h"
#include "ScalerPowerCommonInclude.h"
#include "ScalerRegCommonInclude.h"
#include "ScalerRegionCommonInclude.h"
#include "ScalerRotationCommonInclude.h"
#include "ScalerScalingCommonInclude.h"
#include "ScalerSyncCommonInclude.h"
#include "ScalerSyncProcCommonInclude.h"
#include "ScalerTCONCommonInclude.h"
#include "ScalerTimerFunctionCommonInclude.h"
#include "ScalerTMDSRx0CommonInclude.h"
#include "ScalerTMDSRx1CommonInclude.h"
#include "ScalerTMDSRx2CommonInclude.h"
#include "ScalerTMDSRx3CommonInclude.h"
#include "ScalerTMDSRx4CommonInclude.h"
#include "ScalerTMDSRx5CommonInclude.h"
#include "ScalerVGATopCommonInclude.h"
#include "ScalerVGIPCommonInclude.h"
#include "ScalerHDCP2CommonInclude.h"
#include "ScalerIRCommonInclude.h"
