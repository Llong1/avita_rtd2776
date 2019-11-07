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
// ID Code      : Scaler_Test_Function.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////
// DDR3 //
//////////

//--------------------------------------------------
// DDR3 Phase Calibration or Phase Check (_ON : For All DDR3 Project)
//--------------------------------------------------
#define _DDR3_PHASE_CALIBRATION                                 _OFF
#define _DDR3_PHASE_CHECK                                       _OFF

#if((_MEMORY_TYPE_CONFIG == _MEMORY_DDR3) && ((_DDR3_PHASE_CALIBRATION == _ON) || (_DDR3_PHASE_CHECK == _ON)))
#undef _MEMORY_PHASE_CALIBRATION_MODE
#define _MEMORY_PHASE_CALIBRATION_MODE                          _MEMORY_PHASE_CALIBRATION_FRC_MODE
#endif

#define _DDR3_PHASE_CAL_FRC_MODE_INTERNAL_PG                    _ON

#define _DDR3_PHASE_CAL_INIT_PHASE_CLK0                         0x00
#define _DDR3_PHASE_CAL_INIT_PHASE_CLK1                         0x2A
#define _DDR3_PHASE_CAL_INIT_PHASE_CLK2                         0x06
#define _DDR3_PHASE_CAL_INIT_PHASE_CLK3                         0x1C
#define _DDR3_PHASE_CAL_INIT_PHASE_CLK4                         0x1C
#define _DDR3_PHASE_CAL_INIT_PHASE_CLK5                         0x2A
#define _DDR3_PHASE_CAL_INIT_RDQ_DELAY_TAP                      0x20

#if(((_DDR3_PHASE_CALIBRATION == _ON) || (_DDR3_PHASE_CHECK == _ON)) &&\
    (_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE))

#if(_FORMAT_CONVERSION_FORCE_EO_MODE == _OFF)
#undef _FORMAT_CONVERSION_FORCE_EO_MODE
#define _FORMAT_CONVERSION_FORCE_EO_MODE                        _ON
#endif

#if(_FRAME_SYNC_LINE_BUFFER_SUPPORT == _ON)
#warning "_FRAME_SYNC_LINE_BUFFER_SUPPORT Should Be _OFF!!!"
#endif

#endif

#if(_DDR3_PHASE_CALIBRATION == _ON)
#warning "_DDR3_PHASE_CALIBRATION is _ON!!!"
#endif

#if(_DDR3_PHASE_CHECK == _ON)
#warning "_DDR3_PHASE_CHECK is _ON!!!"
#endif

#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#if(_SDRAM_PHASE_CALIBRATION == _ON)
#warning "_SDRAM_PHASE_CALIBRATION Can Not Be Supported With No Memory!!!"
#endif

#if(_DDR1_PHASE_CALIBRATION == _ON)
#warning "_DDR1_PHASE_CALIBRATION Can Not Be Supported With No Memory!!!"
#endif

#if(_DDR3_PHASE_CALIBRATION == _ON)
#warning "_DDR3_PHASE_CALIBRATION Can Not Be Supported With No Memory!!!"
#endif

#if(_DDR3_PHASE_CHECK == _ON)
#warning "_DDR3_PHASE_CHECK Can Not Be Supported With No Memory!!!"
#endif
#endif // End of #if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)


/////////////////
// FreeSync OD //
/////////////////

//--------------------------------------------------
// FreeSync Mode Measure OD Table (_ON : For FreeSync OD Measure)
//--------------------------------------------------
#define _FREESYNC_OD_MEASURE                                    _OFF

#if(_FREESYNC_OD_MEASURE == _ON)
#warning "_FREESYNC_OD_MEASURE is _ON!!!"

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
#warning "_DEBUG_MESSAGE_SUPPORT should be _ON!!!"
#endif
#endif


////////////////
// Audio Test //
////////////////

//--------------------------------------------------
// Audio Test by Internal Audio Generator
//--------------------------------------------------
#define _INTERNAL_AUDIO_TEST_SUPPORT                            _OFF

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
#warning "_INTERNAL_AUDIO_TEST_SUPPORT is _ON!!!"
#endif


///////////////
// TMDS Test //
///////////////

//--------------------------------------------------
// Debug Option For TMDS Low Speed Port (_ON : 340MHz ; _OFF : 600MHz)
//--------------------------------------------------
#define _TMDS_LOW_SPEED_PORT_SPEED_LIMIT                        _ON


//////////////
// MHL Test //
//////////////

//--------------------------------------------------
// Debug Option For MHL (_ON : No CBUS Handshake ; _OFF : Need CBUS Handshake)
//--------------------------------------------------
#define _MHL_DEBUG_WITHOUT_CBUS_MODE                            _OFF

