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
// ID Code      : ScalerFunctionInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "Global.h"
#include "Project.h"
#include "ScalerFunctionCommonInclude.h"
#include "ScalerFunctionLibInclude.h"

#include "ScalerSyncInclude.h"
#include "ScalerDpTxInclude.h"
#include "ScalerGDIPhyTxInclude.h"
#include "ScalerDisplayDPTxInclude.h"
#include "ScalerTimerFunctionInclude.h"

#include "ScalerHDCP2Include.h"
#include "ScalerDPRx0HDCP2Include.h"
#include "ScalerDPRx1HDCP2Include.h"

#if(_SCALER_TYPE == _RL6193_SERIES)
#include "RL6193_Series_FunctionInclude.h"
#elif(_SCALER_TYPE == _RL6410_SERIES)
#include "RL6410_Series_FunctionInclude.h"
#endif

#include "ScalerADCInclude.h"
#include "ScalerAudioInclude.h"
#include "ScalerAutoFuncInclude.h"
#include "ScalerColorInclude.h"
#include "ScalerDDomainInclude.h"
#include "ScalerDDRInclude.h"
#include "ScalerDebugInclude.h"
#include "ScalerDisplayInclude.h"
#include "ScalerDPInclude.h"
#include "ScalerDPRx0Include.h"
#include "ScalerDPRx1Include.h"
#include "ScalerDPRxMSTInclude.h"
#include "ScalerDPTxAuxInclude.h"
#include "ScalerDPTxMSTInclude.h"
#include "ScalerFormatConversionInclude.h"
#include "ScalerFRCInclude.h"
#include "ScalerGDIPHYInclude.h"
#include "ScalerGlobalInclude.h"
#include "ScalerIDomainInclude.h"
#include "ScalerIOSCInclude.h"
#include "ScalerLDOInclude.h"
#include "ScalerMcuInclude.h"
#include "ScalerMeasureInclude.h"
#include "ScalerMDomainInclude.h"
#include "ScalerMemoryInclude.h"
#include "ScalerMHLRx0Include.h"
#include "ScalerMHLRx1Include.h"
#include "ScalerMHLRx2Include.h"
#include "ScalerMHLRx3Include.h"
#include "ScalerMHLRx4Include.h"
#include "ScalerMHLRx5Include.h"
#include "ScalerNVRamInclude.h"
#include "ScalerODInclude.h"
#include "ScalerOsdInclude.h"
#include "ScalerPinshareInclude.h"
#include "ScalerPLLInclude.h"
#include "ScalerPowerInclude.h"
#include "ScalerRegInclude.h"
#include "ScalerRegionInclude.h"
#include "ScalerRotationInclude.h"
#include "ScalerScalingInclude.h"
#include "ScalerSyncProcInclude.h"
#include "ScalerTCONInclude.h"
#include "ScalerTMDSRx0Include.h"
#include "ScalerTMDSRx1Include.h"
#include "ScalerTMDSRx2Include.h"
#include "ScalerTMDSRx3Include.h"
#include "ScalerTMDSRx4Include.h"
#include "ScalerTMDSRx5Include.h"
#include "ScalerVGATopInclude.h"
#include "ScalerVGIPInclude.h"
#include "ScalerIRInclude.h"
