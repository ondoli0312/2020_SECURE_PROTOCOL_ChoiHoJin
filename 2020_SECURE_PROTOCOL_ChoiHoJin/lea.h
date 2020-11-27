#pragma once
typedef struct lea_key_st
{
	unsigned int rk[192];
	unsigned int round;
}LEA_KEY;


#define ROR(W,i) (((W) >> (i)) | ((W) << (32 - (i))))
#define ROL(W,i) (((W) << (i)) | ((W) >> (32 - (i))))
#define loadU32(v)	((unsigned int)((((unsigned char*)(&v))[3]<<24)|(((unsigned char*)(&v))[2]<<16)|(((unsigned char*)(&v))[1]<<8)|(((unsigned char*)(&v))[0])))