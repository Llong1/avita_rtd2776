#ifndef __w74m00av_H
#define __w74m00av_H

enum
{
	RESULT_ERR =0,
	RESULT_OK =1,
};



#define W74M_CS_OUT_HIGH  //PE3=1
#define W74M_CS_OUT_LOW   //PE3=0



//w74m00av

uint8_t W74M_Write_Read_Byte(uint8_t Write_data);
uint8_t WB_RPMC_ReadRPMCstatus(uint8_t checkall);
void WB_RPMC_ReqCounter(uint8_t cadr, uint8_t*hmackey,uint8_t *input_tag);
uint8_t WB_RPMC_WrRootKey(uint8_t cadr,uint8_t *rootkey);
uint8_t WB_RPMC_UpHMACkey(uint8_t cadr,uint8_t *rootkey,uint8_t *hmac4,uint8_t *hmackey);
uint8_t WB_RPMC_IncCounter(uint8_t cadr,uint8_t *hmackey,uint8_t *input_tag);
uint8_t WB_RPMC_Challenge(uint8_t cadr, uint8_t *hmackey,uint8_t *input_tag);
//uint8_t RPMC_Write_RootKey(uint8_t RootKey_location,uint8_t *Root_key);
uint8_t secure_boot(uint8_t RootKey_location);    






#endif