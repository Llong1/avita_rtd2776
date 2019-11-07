//--------------------------------------------------
// EDID Type Selection
//--------------------------------------------------
#if(_D5_MHL_VERSION < _MHL_VERSION_3_0)
#define _D5_MHL_EDID_TYPE_SEL                          _EDID_MHL_D5_1920_1080_60HZ
#else
#define _D5_MHL_EDID_TYPE_SEL                          _EDID_MHL3_D5_3840_2160_30HZ
#endif

//--------------------------------------------------
// EDID Table
//--------------------------------------------------
#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) || (_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))

BYTE code tEDID_TABLE_D5_MHL[] =
{
#if(_D5_MHL_EDID_TYPE_SEL == _EDID_MHL_D5_1920_1080_60HZ)
#include "./EDID/EdidMhl/EDID_MHL_1920_1080_60HZ_D5.h"
#elif(_D5_MHL_EDID_TYPE_SEL == _EDID_MHL3_D5_3840_2160_30HZ)
#include "./EDID/EdidMhl/EDID_MHL3_3840_2160_30HZ_D5.h"
#endif
};

#endif
