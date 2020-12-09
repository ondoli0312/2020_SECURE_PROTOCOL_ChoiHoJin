#pragma once
void ECB(DATA* A);
void CBC(DATA* A);
void CFB(DATA* A);
void OFB(DATA* A);
void CTR(DATA* A);

void oneZero_Padding(u8* final_msg, int msglen);
void ANSI_Padding(u8* final_msg, int msglen);
void PKCS7_Padding(u8* final_msg, int msglen);
void ISO_Padding(u8* final_msg, int msglen);
void Setting_DATA(DATA* A, u8* pt, u8* key, u8* IV, u8* ct, int ptLen, int keyLen);
int CTR_ADD(u8* CTR);
void MCT_TEST();