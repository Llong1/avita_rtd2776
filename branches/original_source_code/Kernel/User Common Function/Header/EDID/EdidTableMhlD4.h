//--------------------------------------------------
// EDID Type Selection
//--------------------------------------------------
#if(_D4_MHL_VERSION < _MHL_VERSION_3_0)
#define _D4_MHL_EDID_TYPE_SEL                          _EDID_MHL_D4_1920_1080_60HZ
#else
#define _D4_MHL_EDID_TYPE_SEL                          _EDID_MHL3_D4_3840_2160_30HZ
#endif

//--------------------------------------------------
// EDID Table
//--------------------------------------------------
#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) || (_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))

BYTE code tEDID_TABLE_D4_MHL[] =
{
#if(_D4_MHL_EDID_TYPE_SEL == _EDID_MHL_D4_1920_1080_60HZ)
#include "./EDID/EdidMhl/EDID_MHL_1920_1080_60HZ_D4.h"
#elif(_D4_MHL_EDID_TYPE_SEL == _EDID_MHL3_D4_3840_2160_30HZ)
#include "./EDID/EdidMhl/EDID_MHL3_3840_2160_30HZ_D4.h"
#endif
};

#endif
