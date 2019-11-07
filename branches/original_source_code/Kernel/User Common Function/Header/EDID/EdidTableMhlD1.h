//--------------------------------------------------
// EDID Type Selection
//--------------------------------------------------
#if(_D1_MHL_VERSION < _MHL_VERSION_3_0)
#define _D1_MHL_EDID_TYPE_SEL                          _EDID_MHL_D1_1920_1080_60HZ
#else
#define _D1_MHL_EDID_TYPE_SEL                          _EDID_MHL3_D1_3840_2160_30HZ
#endif

//--------------------------------------------------
// EDID Table
//--------------------------------------------------
#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) || (_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))

BYTE code tEDID_TABLE_D1_MHL[] =
{
#if(_D1_MHL_EDID_TYPE_SEL == _EDID_MHL_D1_1920_1080_60HZ)
#include "./EDID/EdidMhl/EDID_MHL_1920_1080_60HZ_D1.h"
#elif(_D1_MHL_EDID_TYPE_SEL == _EDID_MHL3_D1_3840_2160_30HZ)
#include "./EDID/EdidMhl/EDID_MHL3_3840_2160_30HZ_D1.h"
#endif
};

#endif
