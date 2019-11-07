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
// ID Code      : RTD2014Project.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define _OSD_3D_FUNCTION                            _OFF
#define _FACTORY_ONE_PIECE_MARK_SUPPORT             _OFF

//-------------------------------------------------
// Define OSD Rotate Type
//-------------------------------------------------
#define _OSD_ROTATE_FUNCTION                        _OSD_ROTATE_HARDWARE

//--------------------------------------------------
// Definitions of IR Protocal
//--------------------------------------------------
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
#define _IR_NEC_DTV328                              0
#define _IR_SONY_B102P                              1
#define _IR_PHILIPS_RC6                             2

#define _IR_PROTOCAL                               _IR_NEC_DTV328
#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)

//--------------------------------------------------
// Definitions of EDID switch Menu
//--------------------------------------------------
#if((_HDMI_SUPPORT == _ON)||(_DP_SUPPORT == _ON))
#define _EDID_SWITCH_BY_PORT_ITEM                  _ON
#else
#define _EDID_SWITCH_BY_PORT_ITEM                  _OFF
#endif


