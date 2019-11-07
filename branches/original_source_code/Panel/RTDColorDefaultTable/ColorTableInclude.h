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
// Color Temp Default Value
//----------------------------------------------------------------------------------------------------
#include "ColorTempDefault.h"

#ifdef __USER_PANEL__

#if(_DCC_FUNCTION == _ON)
//----------------------------------------------------------------------------------------------------
// DCC Table
//----------------------------------------------------------------------------------------------------
BYTE code tDCC_GAME[] =
{
#include "./DCC/DccModeGame.h"
};

BYTE code tDCC_MOVIE[] =
{
#include "./DCC/DccModeMovie.h"
};

BYTE code tDCC_PHOTO[] =
{
#include "./DCC/DccModePhoto.h"
};

BYTE code tDCC_VIVID[] =
{
#include "./DCC/DccModeVivid.h"
};

code BYTE *tDCC_TABLE[] =
{
    NULL,  // Standard
    tDCC_GAME,
    tDCC_MOVIE,
    tDCC_PHOTO,
    tDCC_VIVID,
};
#endif // End of #if(_DCC_FUNCTION == _ON)

#if(_ICM_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// ICM Table
//----------------------------------------------------------------------------------------------------
BYTE code tICM_GAME[] =
{
#include "./ICM/IcmModeGame.h"
};

BYTE code tICM_MOVIE[] =
{
#include "./ICM/IcmModeMovie.h"
};

BYTE code tICM_PHOTO[] =
{
#include "./ICM/IcmModePhoto.h"
};

BYTE code tICM_VIVID[] =
{
#include "./ICM/IcmModeVivid.h"
};

code BYTE *tICM_TABLE[] =
{
    NULL,  // Standard
    tICM_GAME,
    tICM_MOVIE,
    tICM_PHOTO,
    tICM_VIVID,
};

//----------------------------------------------------------------------------------------------------
// SCM Table
//----------------------------------------------------------------------------------------------------
BYTE code tSCM_VIVID[] =
{
#include "./ICM/ScmModeVivid.h"
};

code BYTE *tSCM_TABLE[] =
{
    NULL,  // Standard
    NULL,  // Game
    NULL,  // Movie
    NULL,  // Photo
    tSCM_VIVID,
};

#endif // End of #if(_ICM_SUPPORT == _ON)



#if(_OD_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// OD Table
//----------------------------------------------------------------------------------------------------
#include "ODTable.h"

code BYTE *tOD_TABLE[] =
{
    tOD_TABLE_COMMON,
};

#if(_FREESYNC_SUPPORT == _ON)
code BYTE *tOD_FREESYNC_TABLE[] =
{
    tOD_TABLE_FREESYNC,
};
#endif
#endif // End of #if(_OD_SUPPORT == _ON)

#endif // End of #ifdef __USER_PANEL__

#ifdef __USER_COMMON_ADJUST__

//----------------------------------------------------------------------------------------------------
// Dithering Table
//----------------------------------------------------------------------------------------------------
#if(_I_DITHER_SUPPORT == _ON)
BYTE code tIDITHER_TABLE_FIFO8[] =
{
#if((_IDITHER_TYPE == _IDITHER_GEN_0_1_SEQ_TRUNCATE_2_0_BIT) || (_IDITHER_TYPE == _IDITHER_GEN_2_1_SEQ_NO_TEMPO_TRUNCATE_2_0_BIT))
#include "./IDither/IDitherTableGen0Fifo8.h"
#elif(_IDITHER_TYPE == _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT)
#include "./IDither/IDitherTableGen1Fifo8.h"
#endif
};

BYTE code tIDITHER_TABLE_FIFO10[] =
{
#if((_IDITHER_TYPE == _IDITHER_GEN_0_1_SEQ_TRUNCATE_2_0_BIT) || (_IDITHER_TYPE == _IDITHER_GEN_2_1_SEQ_NO_TEMPO_TRUNCATE_2_0_BIT))
#include "./IDither/IDitherTableGen0Fifo10.h"
#elif(_IDITHER_TYPE == _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT)
#include "./IDither/IDitherTableGen1Fifo10.h"
#endif
};

BYTE code tIDITHER_SEQ_TABLE[] =
{
#if((_IDITHER_TYPE == _IDITHER_GEN_0_1_SEQ_TRUNCATE_2_0_BIT) || (_IDITHER_TYPE == _IDITHER_GEN_2_1_SEQ_NO_TEMPO_TRUNCATE_2_0_BIT))
#include "./IDither/IDitherTableSeq1.h"
#elif(_IDITHER_TYPE == _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT)
#if(((_I_DITHER_MULTI_SEQ_ENABLE == _DISABLE) && (_I_DITHER_SERIES_SEQ_ENABLE == _DISABLE)))
#include "./IDither/IDitherTableSeq1.h"
#else
#include "./IDither/IDitherTableSeq4.h"
#endif
#endif
};

#if((_IDITHER_TYPE == _IDITHER_GEN_0_1_SEQ_TRUNCATE_2_0_BIT) || (_IDITHER_TYPE == _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT))
BYTE code tIDITHER_TEMPOFFSET_TABLE[] =
{
#include "./IDither/IDitherTableTempo.h"
};
#endif
#endif // End of #if(_I_DITHER_SUPPORT == _ON)

#if(_D_DITHER_SUPPORT == _ON)

#if(_PANEL_EXIST_MULTIPANEL == _OFF)

BYTE code tDDITHER_TABLE[] =
{
#if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT)

#if((_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) || (_DDITHER_TYPE == _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL))
#include "./DDither/DDitherGen0Dither18Bit.h"
#endif

#elif(_PANEL_DISP_BIT_MODE == _PANEL_DISP_24_BIT)

#if((_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) || (_DDITHER_TYPE == _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL))
#include "./DDither/DDitherGen0Dither24Bit.h"
#elif(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)
#include "./DDither/DDitherGen1Dither24Bit.h"
#endif

#elif(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)

#if((_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) || (_DDITHER_TYPE == _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL))
#include "./DDither/DDitherGen0Dither30Bit.h"
#elif(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)
#include "./DDither/DDitherGen1Dither30Bit.h"
#endif

#endif
};

#else // Else of #if(_PANEL_EXIST_MULTIPANEL == _OFF)

#if(_DDITHER_TYPE != _DDITHER_GEN_1_6BIT_DITHERTBL)
BYTE code tDDITHER_TABLE18Bit[] =
{
#if((_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) || (_DDITHER_TYPE == _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL))
#include "./DDither/DDitherGen0Dither18Bit.h"
#endif
};
#endif

BYTE code tDDITHER_TABLE24Bit[] =
{
#if((_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) || (_DDITHER_TYPE == _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL))
#include "./DDither/DDitherGen0Dither24Bit.h"
#elif(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)
#include "./DDither/DDitherGen1Dither24Bit.h"
#endif
};

BYTE code tDDITHER_TABLE30Bit[] =
{
#if((_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) || (_DDITHER_TYPE == _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL))
#include "./DDither/DDitherGen0Dither30Bit.h"
#elif(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)
#include "./DDither/DDitherGen1Dither30Bit.h"
#endif
};

#endif // End of #if(_PANEL_EXIST_MULTIPANEL == _OFF)

BYTE code tDDITHER_SEQ_TABLE[] =
{
#if((_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) || (_DDITHER_TYPE == _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL))
#if(_D_DITHER_MULTI_SEQ_ENABLE == _DISABLE)
#include "./DDither/DDitherGen0Seq1.h"
#else
#include "./DDither/DDitherGen0Seq4.h"
#endif
#elif(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)
#if(((_D_DITHER_MULTI_SEQ_ENABLE == _DISABLE) && (_D_DITHER_SERIES_SEQ_ENABLE == _DISABLE)) && (_D_DITHER_ADVANCE_SETTING_ENABLE != _ENABLE))
#include "./DDither/DDitherGen1Seq1.h"
#else
#include "./DDither/DDitherGen1Seq4.h"
#endif
#endif
};

#if((_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) || (_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL))
BYTE code tDDITHER_TEMPOFFSET_TABLE[] =
{
#if(_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL)
#include "./DDither/DDitherGen0Tempo.h"
#elif(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)
#include "./DDither/DDitherGen1Tempo.h"
#endif
};
#endif

#if(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)
#if(_D_DITHER_ADVANCE_SETTING_ENABLE == _ENABLE)
BYTE code tDDITHER_REALIGN_TABLE[] =
{
#include "./DDither/DDitherGen1Realign.h"
};

BYTE code tDDITHER_REALIGN_TEMPO_TABLE[] =
{
#include "./DDither/DDitherGen1RealignTempo.h"
};

#if(_PANEL_EXIST_MULTIPANEL == _OFF)

BYTE code tDDITHER_LSB_TABLE[] =
{
#if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_24_BIT)
#include "./DDither/DDitherGen1LSB24Bit.h"
#elif(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
#include "./DDither/DDitherGen1LSB30Bit.h"
#endif
};

BYTE code tDDITHER_ADVANCE_SETTING_TABLE[] =
{
#if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_24_BIT)
#include "./DDither/DDitherGen1Advance24Bit.h"
#elif(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
#include "./DDither/DDitherGen1Advance30Bit.h"
#endif
};

#else // Else of #if(_PANEL_EXIST_MULTIPANEL == _OFF)

BYTE code tDDITHER_LSB_TABLE24Bit[] =
{
#include "./DDither/DDitherGen1LSB24Bit.h"
};

BYTE code tDDITHER_LSB_TABLE30Bit[] =
{
#include "./DDither/DDitherGen1LSB30Bit.h"
};

BYTE code tDDITHER_ADVANCE_SETTING_TABLE24Bit[] =
{
#include "./DDither/DDitherGen1Advance24Bit.h"
};

BYTE code tDDITHER_ADVANCE_SETTING_TABLE30Bit[] =
{
#include "./DDither/DDitherGen1Advance30Bit.h"
};

#endif // End of #if(_PANEL_EXIST_MULTIPANEL == _OFF)

#endif
#endif
#endif

#endif // End of #ifdef __USER_COMMON_ADJUST__

#ifdef __USER_ADJUST_OUTPUT_GAMMA__

#if(_GAMMA_FUNCTION == _ON)
//----------------------------------------------------------------------------------------------------
// Gamma Table
//----------------------------------------------------------------------------------------------------
BYTE code tLUTGAMMA_18_TABLE[] =
{
#include "./GAMMA/Gamma18.h"
};

BYTE code tLUTGAMMA_20_TABLE[] =
{
#include "./GAMMA/Gamma20.h"
};

BYTE code tLUTGAMMA_22_TABLE[] =
{
#include "./GAMMA/Gamma22.h"
};

BYTE code tLUTGAMMA_24_TABLE[] =
{
#include "./GAMMA/Gamma24.h"
};

code BYTE *tGAMMA_TABLE[] =
{
    tLUTGAMMA_18_TABLE,
    tLUTGAMMA_20_TABLE,
    tLUTGAMMA_22_TABLE,
    tLUTGAMMA_24_TABLE,
};
#endif // End of #if(_GAMMA_FUNCTION == _ON)

#if(_PCM_FUNCTION == _ON)
//----------------------------------------------------------------------------------------------------
// PCM Table
//----------------------------------------------------------------------------------------------------
BYTE code tPCM_USER_INPUT_GAMMA_TABLE[] =
{
#include "./PCM/PCMUserInputGammaTable.h"
};

BYTE code tPCM_USER_MATRIX[] =
{
#include "./PCM/PCMUserColorMatrixTable.h"
};

BYTE code tPCM_USER_OUTPUT_GAMMA_TABLE[] =
{
#include "./PCM/PCMUserOutputGammaTable.h"
};

code BYTE *tPCM_USER_TABLE[] =
{
    tPCM_USER_INPUT_GAMMA_TABLE,    tPCM_USER_OUTPUT_GAMMA_TABLE,   tPCM_USER_MATRIX,
};
#endif // End of #if(_PCM_FUNCTION == _ON)

#endif // End of #ifdef __USER_ADJUST_OUTPUT_GAMMA__

#ifdef __USER_ADJUST_RGB_GAMMA__

#if(_RGB_GAMMA_FUNCTION == _ON)

BYTE code tLUTRGBGAMMA_18_TABLE[] =
{
#include "./GAMMA/RGBGamma18.h"
};

BYTE code tLUTRGBGAMMA_20_TABLE[] =
{
#include "./GAMMA/RGBGamma20.h"
};

BYTE code tLUTRGBGAMMA_22_TABLE[] =
{
#include "./GAMMA/RGBGamma22.h"
};

BYTE code tLUTRGBGAMMA_24_TABLE[] =
{
#include "./GAMMA/RGBGamma24.h"
};

code BYTE *tRGBGAMMA_TABLE[] =
{
    tLUTRGBGAMMA_18_TABLE,
    tLUTRGBGAMMA_20_TABLE,
    tLUTRGBGAMMA_22_TABLE,
    tLUTRGBGAMMA_24_TABLE,
};
#endif// End of #if(_RGB_GAMMA_FUNCTION == _ON)

#endif // End of #ifdef __USER_ADJUST_RGB_GAMMA__


#ifdef __USER_ADJUST_3D_GAMMA__

#if(_RGB_3D_GAMMA == _ON)

BYTE code tRGB3DGAMMA_MODE0_TABLE[] =
{
#include "./GAMMA/3DGammaMode0.h"
};

BYTE code tRGB3DGAMMA_MODE1_TABLE[] =
{
#include "./GAMMA/3DGammaMode1.h"
};

code BYTE *tRGB3DGAMMA_TABLE[] =
{
    tRGB3DGAMMA_MODE0_TABLE,
    tRGB3DGAMMA_MODE1_TABLE,
};

#endif // End of #if(_RGB_3D_GAMMA == _ON)
#endif // End of #ifdef __USER_ADJUST_3D_GAMMA__

