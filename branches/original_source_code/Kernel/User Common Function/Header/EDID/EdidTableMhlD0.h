//--------------------------------------------------
// EDID Type Selection
//--------------------------------------------------
#if(_D0_MHL_VERSION < _MHL_VERSION_3_0)
#define _D0_MHL_EDID_TYPE_SEL                          _EDID_MHL_D0_1920_1080_60HZ
#else
#define _D0_MHL_EDID_TYPE_SEL                          _EDID_MHL3_D0_3840_2160_30HZ
#endif

//--------------------------------------------------
// EDID Table
//--------------------------------------------------
#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) || (_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))

BYTE code tEDID_TABLE_D0_MHL[] =
{
#if(_D0_MHL_EDID_TYPE_SEL == _EDID_MHL_D0_1920_1080_60HZ)
#include "./EDID/EdidMhl/EDID_MHL_1920_1080_60HZ_D0.h"
#elif(_D0_MHL_EDID_TYPE_SEL == _EDID_MHL3_D0_3840_2160_30HZ)
#include "./EDID/EdidMhl/EDID_MHL3_3840_2160_30HZ_D0.h"
#endif
};

#endif
