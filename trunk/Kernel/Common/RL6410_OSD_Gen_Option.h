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
// ID Code      : RL6410_Series_OSD_Gen_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __RL6410_OSD_GEN_OPTION__
#define __RL6410_OSD_GEN_OPTION__

//--------------------------------------------------
// OSD Register Gen
//--------------------------------------------------
#define _OSD_REG_MAPPING_GEN                                    _USER_OSD_GEN_2

//--------------------------------------------------
// OSD CW180
//--------------------------------------------------
#define _OSD_ROTATE_CW180_SUPPORT                               _ON

//--------------------------------------------------
// OSD Window 5-1 ~5-8 Support
//--------------------------------------------------
#define _OSD_WINDOW_5_1_5_8_SUPPORT                             _ON

//--------------------------------------------------
// OSD Window Rouned window pattern 32x32 Support
//--------------------------------------------------
#define _OSD_WINDOW_ROUNED_PATTERN_32X32_SUPPORT                _ON

//--------------------------------------------------
// OSD Window Chessboard Win 8/9 Support
//--------------------------------------------------
#define _OSD_WINDOW_CHESSBORAD_WIN8_WIND9_SUPPORT               _ON

//--------------------------------------------------
// OSD Window Color palette index bit number
//--------------------------------------------------
#define _OSD_WINDOW_COLOR_PALETTE_INDEX_BIT                     (6)

#endif // End of #ifndef __RL6410_OSD_GEN_OPTION__
