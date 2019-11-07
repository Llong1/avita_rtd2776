//--------------------------------------------------
// EDID Type Selection
//--------------------------------------------------
#if(_D3_MHL_VERSION < _MHL_VERSION_3_0)
#define _D3_MHL_EDID_TYPE_SEL                          _EDID_MHL_D3_1920_1080_60HZ
#else
#define _D3_MHL_EDID_TYPE_SEL                          _EDID_MHL3_D3_3840_2160_30HZ
#endif

//--------------------------------------------------
// EDID Table
//--------------------------------------------------
#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) || (_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))

BYTE code tEDID_TABLE_D3_MHL[] =
{
#if(_D3_MHL_EDID_TYPE_SEL == _EDID_MHL_D3_1920_1080_60HZ)
#include "./EDID/EdidMhl/EDID_MHL_1920_1080_60HZ_D3.h"
#elif(_D3_MHL_EDID_TYPE_SEL == _EDID_MHL3_D3_3840_2160_30HZ)
#include "./EDID/EdidMhl/EDID_MHL3_3840_2160_30HZ_D3.h"
#endif
};

#endif
