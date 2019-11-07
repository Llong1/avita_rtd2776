//--------------------------------------------------
// EDID Type Selection
//--------------------------------------------------
#define _EDID_SEGMENT_SIZE_384                           _EDID_DP_5120_2880_60HZ_384
#define _EDID_SEGMENT_SIZE_256                           _EDID_DP_5120_2880_60HZ_256

#define _EDID_D7_D0_TYPE_SEL                             ((_D7_D0_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384) ? _EDID_SEGMENT_SIZE_384 : _EDID_SEGMENT_SIZE_256)
#define _EDID_D7_D1_TYPE_SEL                             ((_D7_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384) ? _EDID_SEGMENT_SIZE_384 : _EDID_SEGMENT_SIZE_256)

//--------------------------------------------------
// EDID Table
//--------------------------------------------------
#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) ||\
    ((_D7_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
     (_D7_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
     (_D7_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)))

BYTE code tEDID_TABLE_D7_D0[] =
{
#if(_EDID_D7_D0_TYPE_SEL == _EDID_DP_5120_2880_60HZ_256)
#include "./EDID/EdidDp/EDID_DP_5120_2880_60HZ_256.h"
#elif(_EDID_D7_D0_TYPE_SEL == _EDID_DP_5120_2880_60HZ_384)
#include "./EDID/EdidDp/EDID_DP_5120_2880_60HZ_384.h"
#elif(_EDID_D7_D0_TYPE_SEL == _EDID_DP_3840_2160_144HZ_256)
#include "./EDID/EdidDp/EDID_DP_3840_2160_144HZ_256h"
#elif(_EDID_D7_D0_TYPE_SEL == _EDID_DP_3840_2160_144HZ_384)
#include "./EDID/EdidDp/EDID_DP_3840_2160_144HZ_384.h"
#endif
};

BYTE code tEDID_TABLE_D7_D1[] =
{
#if(_EDID_D7_D1_TYPE_SEL == _EDID_DP_5120_2880_60HZ_256)
#include "./EDID/EdidDp/EDID_DP_5120_2880_60HZ_256.h"
#elif(_EDID_D7_D1_TYPE_SEL == _EDID_DP_5120_2880_60HZ_384)
#include "./EDID/EdidDp/EDID_DP_5120_2880_60HZ_384.h"
#elif(_EDID_D7_D1_TYPE_SEL == _EDID_DP_3840_2160_144HZ_256)
#include "./EDID/EdidDp/EDID_DP_3840_2160_144HZ_256.h"
#elif(_EDID_D7_D1_TYPE_SEL == _EDID_DP_3840_2160_144HZ_384)
#include "./EDID/EdidDp/EDID_DP_3840_2160_144HZ_384.h"
#endif
};

#endif
