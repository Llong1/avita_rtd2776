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
// ID Code      : ScalerFunctionInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionLibInterface.h"

#include "ScalerHDCP2Interface.h"
#include "ScalerDPRx0HDCP2Interface.h"
#include "ScalerDPRx1HDCP2Interface.h"

#if(_SCALER_TYPE == _RL6193_SERIES)
#include "RL6193_Series_FunctionInterface.h"
#elif(_SCALER_TYPE == _RL6410_SERIES)
#include "RL6410_Series_FunctionInterface.h"
#endif
#include "ScalerADCInterface.h"
#include "ScalerAudioInterface.h"
#include "ScalerAutoFuncInterface.h"
#include "ScalerColorInterface.h"
#include "ScalerDDomainInterface.h"
#include "ScalerDDRInterface.h"
#include "ScalerDebugInterface.h"
#include "ScalerDisplayInterface.h"
#include "ScalerDisplayDPTxInterface.h"
#include "ScalerDPInterface.h"
#include "ScalerDPRx0Interface.h"
#include "ScalerDPRx1Interface.h"
#include "ScalerDPRxMSTInterface.h"
#include "ScalerDPTxAuxInterface.h"
#include "ScalerDPTxInterface.h"
#include "ScalerDPTxMSTInterface.h"
#include "ScalerFormatConversionInterface.h"
#include "ScalerFRCInterface.h"
#include "ScalerGDIPHYInterface.h"
#include "ScalerGDIPhyTxInterface.h"
#include "ScalerGlobalInterface.h"
#include "ScalerIDomainInterface.h"
#include "ScalerIOSCInterface.h"
#include "ScalerLDOInterface.h"
#include "ScalerMcuInterface.h"
#include "ScalerMeasureInterface.h"
#include "ScalerMDomainInterface.h"
#include "ScalerMemoryInterface.h"
#include "ScalerMHLRx0Interface.h"
#include "ScalerMHLRx1Interface.h"
#include "ScalerMHLRx2Interface.h"
#include "ScalerMHLRx3Interface.h"
#include "ScalerMHLRx4Interface.h"
#include "ScalerMHLRx5Interface.h"
#include "ScalerNVRamInterface.h"
#include "ScalerODInterface.h"
#include "ScalerOsdInterface.h"
#include "ScalerPinshareInterface.h"
#include "ScalerPLLInterface.h"
#include "ScalerPowerInterface.h"
#include "ScalerRegInterface.h"
#include "ScalerRegionInterface.h"
#include "ScalerRotationInterface.h"
#include "ScalerScalingInterface.h"
#include "ScalerSyncInterface.h"
#include "ScalerSyncProcInterface.h"
#include "ScalerTCONInterface.h"
#include "ScalerTimerFunctionInterface.h"
#include "ScalerTMDSRx0Interface.h"
#include "ScalerTMDSRx1Interface.h"
#include "ScalerTMDSRx2Interface.h"
#include "ScalerTMDSRx3Interface.h"
#include "ScalerTMDSRx4Interface.h"
#include "ScalerTMDSRx5Interface.h"
#include "ScalerVGATopInterface.h"
#include "ScalerVGIPInterface.h"
#include "ScalerIRInterface.h"
