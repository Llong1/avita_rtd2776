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
// ID Code      : EnergyStarTable.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// CODE TABLES
//****************************************************************************

#ifdef __USER_COMMON_ADJUST__

BYTE code tENERGY_STAR_ACTIVE_RANGE[] =
{
// The average of (R+G+B) value to setting different backlight.
//  0   1   2   3   4    5    6    7    8    9    10   11   12   13   14
    43, 59, 76, 85, 97, 104, 111, 120, 125, 133, 138, 143, 150, 154, 160,
};

BYTE code tENERGY_STAR_BACKLIGHT_TABLE[] =
{
// The percentage of OSD backlight value in each average of (R+G+B) value. (unit: %)
//  0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15
    64, 66, 68, 71, 73, 76, 78, 80, 83, 85, 88, 90, 92, 95, 97, 100,
};

#endif

