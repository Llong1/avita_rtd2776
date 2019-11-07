//--------------------------------------------------
// EDID Type Selection
//--------------------------------------------------
#if(_D2_MHL_VERSION < _MHL_VERSION_3_0)
#define _D2_MHL_EDID_TYPE_SEL                          _EDID_MHL_D2_1920_1080_60HZ
#else
#define _D2_MHL_EDID_TYPE_SEL                          _EDID_MHL3_D2_3840_2160_30HZ
#endif

//--------------------------------------------------
// EDID Table
//--------------------------------------------------
#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) || (_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))

BYTE code tEDID_TABLE_D2_MHL[] =
{
#if(_D2_MHL_EDID_TYPE_SEL == _EDID_MHL_D2_1920_1080_60HZ)
#include "./EDID/EdidMhl/EDID_MHL_1920_1080_60HZ_D2.h"
#elif(_D2_MHL_EDID_TYPE_SEL == _EDID_MHL3_D2_3840_2160_30HZ)
#include "./EDID/EdidMhl/EDID_MHL3_3840_2160_30HZ_D2.h"
#endif
};

#endif
