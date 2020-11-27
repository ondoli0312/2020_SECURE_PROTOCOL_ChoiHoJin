#pragma once
#include "type.h"
struct aes_key_st {
	u8 rd_key[16 * 11];
	int rounds;
};
typedef struct aes_key_st AES_KEY;

int Encryption_AES_32bit_version(u8* plaintext, unsigned char* key, u8* out, u32 KeyLen);