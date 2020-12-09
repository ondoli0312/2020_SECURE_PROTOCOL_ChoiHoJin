#include "type.h"
#include "ARIA.h"
#include "AES.h"
#include "Mode_of_Operation.h"

void ECB(DATA* A);
void CBC(DATA* A);
void CFB(DATA* A);
void OFB(DATA* A);
void CTR(DATA* A);

void oneZero_Padding(u8* final_msg, int msglen)
{
	int i = 0;
	final_msg[msglen % 16] = 0x80;
	for (i = msglen % 16 +1; i < Block_size; i++)
		final_msg[i] = 0;
}

void ANSI_Padding(u8* final_msg, int msglen) {
	int i = 0;
	for (i = msglen % 16; i < Block_size - 1; i++) {
		final_msg[i] = 0;
	}
	final_msg[Block_size - 1] = (Block_size - (msglen % 16));
}

void PKCS7_Padding(u8* final_msg, int msglen)
{
	int i = 0;
	int flag = msglen % 16;
	for (i = msglen % 16; i < Block_size; i++) {
		final_msg[i] = 16 - flag;
	}
}

void ISO_Padding(u8* final_msg, int msglen) {
	int i = 0;
	for (i = msglen % 16; i < Block_size - 1; i++)
		final_msg[i] = rand() % 0xff;
	final_msg[Block_size-1] = (Block_size - (msglen % 16));
}

void Setting_DATA(DATA* A, u8* pt, u8* key, u8* IV, u8* ct, int ptLen, int keyLen) {
	
	//Padding Setting
	switch (A->padding_Flag)
	{
	case oneZeroPad:
		A->Pad = oneZero_Padding;
		break;
	case ansiPad:
		A->Pad = ANSI_Padding;
		break;
	case pkcs7Pad:
		A->Pad = PKCS7_Padding;
		break;
	case isoPad:
		A->Pad = ISO_Padding;
	default:
		printf("INPUT PARAMETER ERROR\n");
		printf("PADDING SETTING FUNCTION BREAK\n");
		return;
		break;
	}

	//Enc Setting
	switch (A->Enc_Flag)
	{
	case useLEA:
		A->Enc = LEA;
		break;
	case useARIA:
		A->Enc = ARIA;
		break;
	case useAES:
		A->Enc = Encryption_AES_32bit_version;
		break;
	default:
		printf("INPUT PARAMETER ERROR\n");
		printf("ENC SETTING FUNCTION BREAK\n");
		return;
		break;
	}

	//Operation Setting
	switch (A->operation_Flag)
	{
	case useECB:
		A->Operation = ECB;
		break;
	case useCBC:
		A->Operation = CBC;
		break;
	case useCFB:
		A->Operation = CFB;
		break;
	case useOFB:
		A->Operation = OFB;
		break;
	case useCTR:
		A->Operation = CTR;
		break;
	default:
		printf("INPUT PARAMETER ERROR\n");
		printf("OPERATION SETTING FUNCTION BREAK\n");
		return;
		break; 
	}

	int final_ptLen = (ptLen % 16);

	//Msg Setting
	if (ptLen > 16 || ptLen == 16) {

		A->Msg = (u8*)malloc((ptLen / 16) * 16);
		if (A->Msg == NULL) {
			printf("Malloc ERROR\n");
			return;
		}
		A->msgLen = (ptLen / 16) * 16;
		memcpy(A->Msg, pt, A->msgLen);

		memset(A->final_Msg, 0, 16);
		for (int i = 0; i < final_ptLen; i++) {
			A->final_Msg[i] = pt[A->msgLen + i];
		}
		A->Pad(A->final_Msg, final_ptLen);
	}
	else 
	{
		for (int i = 0; i < final_ptLen; i++) {
			A->final_Msg[i] = pt[A->msgLen + i];
		}
		A->Pad(A->final_Msg, final_ptLen);
	}

	//Key Setting
	A->Key = (u8*)malloc(key);
	if (A->Key == NULL) {
		printf("Malloc ERROR\n");
		return;
	}
	A->keyLen = keyLen;
	memcpy(A->Key, key, A->keyLen);

	//IV Setting
	memcpy(A->IV, IV, 16);

	//CT Setting
	A->CT = (u8*)malloc((((ptLen / 16) + 1) * 16));
	A->ctLen = (ptLen / 16 + 1) * 16;
}

void ECB(DATA* A){
	u8 temp[16] = { 0, };
	int i = 0;
	for (i = 0; i < A->msgLen / 16; i++) {
		A->Enc(A->Msg + (16*i), A->Key, temp, A->keyLen);
		memcpy(A->CT + (i * 16), temp, 16);
	}

	//Final_Byte
	A->Enc(A->final_Msg, A->Key, temp, A->keyLen);
	memcpy(A->CT + (i * 16), temp, 16);

}

void CBC(DATA* A) {
	u8 IV[16] = { 0, };
	u8 ct_temp[16] = { 0, };
	memcpy(IV, A->IV, 16);
	int i = 0;
	for (i = 0; i < A->msgLen / 16; i++) {
		for (int j = 0; j < 16; j++) {
			IV[j] = A->Msg[j +(16*i)] ^ IV[j];
		}
		A->Enc(IV, A->Key, ct_temp, A->keyLen);
		memcpy(A->CT + (i * 16), ct_temp, 16);
		memcpy(IV, ct_temp, 16);
	}

	for (int j = 0; j < 16; j++) {
		IV[j] = A->final_Msg[j] ^ ct_temp[j];
	}
	A->Enc(A->final_Msg, A->Key, ct_temp, A->keyLen);
	memcpy(A->CT + (i * 16), ct_temp, 16);
}

void CFB(DATA* A) {
	u8 IV[16] = { 0, };
	u8 temp[16] = { 0, };
	int i = 0;

	memcpy(IV, A->IV, 16);
	for (i = 0; i < A->msgLen / 16; i++) {
		A->Enc(IV, A->Key, temp, A->keyLen);
		for (int j = 0; j < 16; j++) {
			A->CT[j + (16 * i)] = A->Msg[j + (16 * i)] ^ temp[j];
			IV[j] = temp[j];
		}
	}

	A->Enc(IV, A->Key, temp, A->keyLen);
	for (int j = 0; j < 16; j++) {
		A->CT[j + (16 * i)] = A->final_Msg[j] ^ temp[j];
	}

}

void OFB(DATA* A) {
	u8 IV[16] = { 0, };
	u8 ct_temp[16] = { 0, };
	int i = 0;

	memcpy(IV, A->IV, 16);
	for (i = 0; i < A->msgLen / 16; i++) {
		A->Enc(IV, A->Key, ct_temp, A->keyLen);
		for (int j = 0; j < 16; j++) {
			A->CT[j + (16 * i)] = A->Msg[j + (16 * i)] ^ ct_temp[j];
		}
		memcpy(IV, ct_temp, 16);
	}

	A->Enc(IV, A->Key, ct_temp, A->keyLen);
	for (int j = 0; j < 16; j++) {
		A->CT[j + (16 * i)] = A->final_Msg[j] ^ ct_temp[j];
	}
}

int CTR_ADD(u8* CTR)
{
	int cnt = 0;
	while (1)
	{
		if (CTR[15 - cnt] != 0xff)
			break;
		cnt = cnt + 1;
		if (cnt == 16)
			return -1;
	}
	for (int i = 15; i > 15 - cnt; i--)
	{
		CTR[i] = 0;
	}
	CTR[15 - cnt] = CTR[15 - cnt] + 1;
}

void CTR(DATA* A) {
	u8 IV[16] = { 0, };
	u8 ct_temp[16] = { 0, };
	int i = 0;

	memcpy(IV, A->IV, 16);

	for (i = 0; i < A->msgLen / 16; i++) {
		A->Enc(IV, A->Key, ct_temp, A->keyLen);
		for (int j = 0; j < 16; j++) {
			A->CT[j + (16 * i)] = A->Msg[j + (16 * i)] ^ ct_temp[j];
		}
		CTR_ADD(IV);
	}
	A->Enc(IV, A->Key, ct_temp, A->keyLen);
	for (int j = 0; j < 16; j++) {
		A->CT[j + (16 * i)] = A->final_Msg[j] ^ ct_temp[j];
	}
}

