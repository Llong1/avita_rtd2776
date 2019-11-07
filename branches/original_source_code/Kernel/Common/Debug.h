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
// ID Code      : Debug.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __DEBUG_H__
#define __DEBUG_H__

//****************************************************************************
// General Definitions
//****************************************************************************
//--------------------------------------------------
// DDC Channel Select
//--------------------------------------------------
#define _DEBUG_DDC_CHANNEL_SEL                      _DDC3

//--------------------------------------------------
// Debug Message Supported
//--------------------------------------------------
#define _DEBUG_MESSAGE_SYSTEM                       _OFF
#define _DEBUG_MESSAGE_SCALER                       _OFF
#define _DEBUG_MESSAGE_ANALOG                       _OFF
#define _DEBUG_MESSAGE_DIGITAL                      _OFF
#define _DEBUG_MESSAGE_RX0                          _OFF
#define _DEBUG_MESSAGE_RX1                          _OFF
#define _DEBUG_MESSAGE_RX2                          _OFF
#define _DEBUG_MESSAGE_RX3                          _OFF
#define _DEBUG_MESSAGE_RX4                          _OFF
#define _DEBUG_MESSAGE_RX5                          _OFF
#define _DEBUG_MESSAGE_MHL                          _OFF
#define _DEBUG_MESSAGE_MST                          _OFF
#define _DEBUG_MESSAGE_HDCP2                        _OFF
#define _DEBUG_MESSAGE_AUDIO                        _OFF
#define _DEBUG_MESSAGE_MEASURE                      _OFF
#define _DEBUG_MESSAGE_MEMORY                       _OFF
#define _DEBUG_MESSAGE_MEMORY_PHASE_CAL             _OFF
#define _DEBUG_MESSAGE_FRAME_SYNC                   _OFF
#define _DEBUG_MESSAGE_FRC                          _OFF
#define _DEBUG_MESSAGE_OSD                          _OFF
#define _DEBUG_MESSAGE_IR                           _OFF
#define _DEBUG_MESSAGE_HDR                          _OFF

#if(_DEBUG_MESSAGE_SYSTEM == _ON)
#define DebugMessageSystem(x, y)                    ScalerDebugMessage((x), (y))
#else
#define DebugMessageSystem(x, y)                    ;
#endif

#if(_DEBUG_MESSAGE_SCALER == _ON)
#define DebugMessageScaler(x, y)                    ScalerDebugMessage((x), (y))
#else
#define DebugMessageScaler(x, y)                    ;
#endif

#if(_DEBUG_MESSAGE_ANALOG == _ON)
#define DebugMessageAnalog(x, y)                    ScalerDebugMessage((x), (y))
#else
#define DebugMessageAnalog(x, y)                    ;
#endif

#if(_DEBUG_MESSAGE_DIGITAL == _ON)
#define DebugMessageDigital(x, y)                   ScalerDebugMessage((x), (y))
#else
#define DebugMessageDigital(x, y)                   ;
#endif

#if(_DEBUG_MESSAGE_RX0 == _ON)
#define DebugMessageRx0(x, y)                       ScalerDebugMessage((x), (y))
#else
#define DebugMessageRx0(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_RX1 == _ON)
#define DebugMessageRx1(x, y)                       ScalerDebugMessage((x), (y))
#else
#define DebugMessageRx1(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_RX2 == _ON)
#define DebugMessageRx2(x, y)                       ScalerDebugMessage((x), (y))
#else
#define DebugMessageRx2(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_RX3 == _ON)
#define DebugMessageRx3(x, y)                       ScalerDebugMessage((x), (y))
#else
#define DebugMessageRx3(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_RX4 == _ON)
#define DebugMessageRx4(x, y)                       ScalerDebugMessage((x), (y))
#else
#define DebugMessageRx4(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_RX5 == _ON)
#define DebugMessageRx5(x, y)                       ScalerDebugMessage((x), (y))
#else
#define DebugMessageRx5(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_MHL == _ON)
#define DebugMessageMHL(x, y)                       ScalerDebugMessage((x), (y))
#else
#define DebugMessageMHL(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_MST == _ON)
#define DebugMessageMst(x, y)                       ScalerDebugMessage((x), (y))
#else
#define DebugMessageMst(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_HDCP2 == _ON)
#define DebugMessageHDCP2(x, y)                     ScalerDebugMessage((x), (y))
#else
#define DebugMessageHDCP2(x, y)                     ;
#endif

#if(_DEBUG_MESSAGE_AUDIO == _ON)
#define DebugMessageAudio(x, y)                     ScalerDebugMessage((x), (y))
#else
#define DebugMessageAudio(x, y)                     ;
#endif

#if(_DEBUG_MESSAGE_MEASURE == _ON)
#define DebugMessageMeasure(x, y)                   ScalerDebugMessage((x), (y))
#else
#define DebugMessageMeasure(x, y)                   ;
#endif

#if(_DEBUG_MESSAGE_MEMORY == _ON)
#define DebugMessageMemory(x, y)                    ScalerDebugMessage((x), (y))
#else
#define DebugMessageMemory(x, y)                    ;
#endif

#if(_DEBUG_MESSAGE_MEMORY_PHASE_CAL == _ON)
#define DebugMessageMemoryPhaseCal(x, y)            ScalerDebugMessage((x), (y))
#else
#define DebugMessageMemoryPhaseCal(x, y)            ;
#endif

#if(_DEBUG_MESSAGE_FRAME_SYNC == _ON)
#define DebugMessageFS(x, y)                        ScalerDebugMessage((x), (y))
#else
#define DebugMessageFS(x, y)                        ;
#endif

#if(_DEBUG_MESSAGE_FRC == _ON)
#define DebugMessageFRC(x, y)                       ScalerDebugMessage((x), (y))
#else
#define DebugMessageFRC(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_OSD == _ON)
#define DebugMessageOsd(x, y)                       ScalerDebugMessage((x), (y))
#else
#define DebugMessageOsd(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_IR == _ON)
#define DebugMessageIR(x, y)                        ScalerDebugMessage((x), (y))
#else
#define DebugMessageIR(x, y)                        ;
#endif

#if(_DEBUG_MESSAGE_HDR == _ON)
#define DebugMessageHDR(x, y)                       ScalerDebugMessage((x), (y))
#else
#define DebugMessageHDR(x, y)                       ;
#endif

#if((_DEBUG_MESSAGE_SYSTEM == _ON) ||\
    (_DEBUG_MESSAGE_SCALER == _ON) ||\
    (_DEBUG_MESSAGE_ANALOG == _ON) ||\
    (_DEBUG_MESSAGE_DIGITAL == _ON) ||\
    (_DEBUG_MESSAGE_RX0 == _ON) ||\
    (_DEBUG_MESSAGE_RX1 == _ON) ||\
    (_DEBUG_MESSAGE_RX2 == _ON) ||\
    (_DEBUG_MESSAGE_RX3 == _ON) ||\
    (_DEBUG_MESSAGE_RX4 == _ON) ||\
    (_DEBUG_MESSAGE_RX5 == _ON) ||\
    (_DEBUG_MESSAGE_MHL == _ON) ||\
    (_DEBUG_MESSAGE_MST == _ON) ||\
    (_DEBUG_MESSAGE_HDCP2 == _ON) ||\
    (_DEBUG_MESSAGE_AUDIO == _ON) ||\
    (_DEBUG_MESSAGE_MEASURE == _ON) ||\
    (_DEBUG_MESSAGE_MEMORY == _ON) ||\
    (_DEBUG_MESSAGE_MEMORY_PHASE_CAL == _ON) ||\
    (_DEBUG_MESSAGE_FRAME_SYNC == _ON) ||\
    (_DEBUG_MESSAGE_FRC == _ON) ||\
    (_DEBUG_MESSAGE_OSD == _ON) ||\
    (_DEBUG_MESSAGE_IR == _ON) ||\
    (_DEBUG_MESSAGE_HDR == _ON))
#define _DEBUG_MESSAGE_SUPPORT                      _ON
#else
#define _DEBUG_MESSAGE_SUPPORT                      _OFF
#endif

#endif // End of #ifndef __DEBUG_H__
