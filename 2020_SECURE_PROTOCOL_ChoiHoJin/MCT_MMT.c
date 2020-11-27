#define _CRT_SECURE_NO_WARNINGS
#include "ARIA.h"
#include "type.h"
#include "Mode_of_Operation.h"
#include <assert.h>

void MCT_ECB128()
{
	FILE* fp_req = NULL;
	FILE* fp_rsp = NULL;
	unsigned char* ptr = NULL;

	u8 output[16] = { 0, };
	u8 buf[100] = { 0, };
	u8 temp[16] = { 0, };

	DATA* A = NULL;
	A = (DATA*)malloc(sizeof(DATA));
	A->Msg = (u8*)calloc(16, sizeof(u8));
	A->CT = (u8*)calloc(32, sizeof(u8));
	A->Key = (u8*)calloc(16, sizeof(u8));
	A->ctLen = 32;
	A->keyLen = 16;
	A->msgLen = 16;
	A->Enc = ARIA;

	int count = 0;
	int i = 0, j = 0;

	fp_req = fopen("ARIA128(ECB)MCT.req", "r");
	assert(fp_req != NULL);
	fp_rsp = fopen("ARIA128(ECB)MCT.rsp", "w");
	assert(fp_rsp != NULL);

	//KEY Copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 32, A->Key);

	//PT copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 32, A->Msg);

	for (count = 0; count < 100; count++)
	{
		fprintf(fp_rsp, "COUNT = %d\n", count);

		//key
		fprintf(fp_rsp, "KEY = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->Key[j]);
		fprintf(fp_rsp, "\n");

		//pt
		fprintf(fp_rsp, "PT = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->Msg[j]);
		fprintf(fp_rsp, "\n");

		//ECB는 암호화를 한번 하는 것과 같으므로
		for (i = 0; i < 1000; i++)
		{
			ECB(A);
			memcpy(A->Msg, A->CT, 16);
		}

		//키 재설정
		for (int x = 0; x < 16; x++)
			A->Key[x] = A->Key[x] ^ A->CT[x];

		fprintf(fp_rsp, "CT = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->CT[j]);
		fprintf(fp_rsp, "\n\n");

	}


	if (fp_req != NULL)
		fclose(fp_req);

	if (fp_rsp != NULL)
		fclose(fp_rsp);
}
void MCT_ECB192()
{
	FILE* fp_req = NULL;
	FILE* fp_rsp = NULL;
	unsigned char* ptr = NULL;

	u8 output[16] = { 0, };
	u8 buf[100] = { 0, };
	u8 temp[16] = { 0, };

	int count = 0;
	int i = 0, j = 0;


	DATA* A = NULL;
	A = (DATA*)malloc(sizeof(DATA));
	A->Msg = (u8*)calloc(16, sizeof(u8));
	A->CT = (u8*)calloc(32, sizeof(u8));
	A->Key = (u8*)calloc(24, sizeof(u8));
	A->ctLen = 32;
	A->keyLen = 24;
	A->msgLen = 16;
	A->Enc = ARIA;

	fp_req = fopen("ARIA192(ECB)MCT.req", "r");
	assert(fp_req != NULL);
	fp_rsp = fopen("ARIA192(ECB)MCT.rsp", "w");
	assert(fp_rsp != NULL);

	//KEY Copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 48, A->Key);

	//PT copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 32, A->Msg);

	for (count = 0; count < 100; count++)
	{
		fprintf(fp_rsp, "COUNT = %d\n", count);

		//key
		fprintf(fp_rsp, "KEY = ");
		for (j = 0; j < 24; j++)
			fprintf(fp_rsp, "%02X", A->Key[j]);
		fprintf(fp_rsp, "\n");

		//pt
		fprintf(fp_rsp, "PT = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->Msg[j]);
		fprintf(fp_rsp, "\n");


		for (i = 0; i < 1000; i++)
		{
			ECB(A);
			memcpy(A->Msg, A->CT, 16);
			if (i == 998)
				memcpy(temp, A->CT, 16);
			//키 설정을 위한 값 저장
		}

		//192bit key 설정
		for (int x = 0; x < 8; x++)
			A->Key[x] = A->Key[x] ^ temp[x + 8];

		for (int x = 8; x < 24; x++)
			A->Key[x] = A->Key[x] ^ A->CT[x - 8];


		fprintf(fp_rsp, "CT = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->CT[j]);
		fprintf(fp_rsp, "\n\n");

	}


	if (fp_req != NULL)
		fclose(fp_req);

	if (fp_rsp != NULL)
		fclose(fp_rsp);
}
void MCT_ECB256()
{
	FILE* fp_req = NULL;
	FILE* fp_rsp = NULL;
	unsigned char* ptr = NULL;

	u8 output[16] = { 0, };
	u8 buf[100] = { 0, };
	u8 temp[16] = { 0, };

	int count = 0;
	int i = 0, j = 0;

	DATA* A = NULL;
	A = (DATA*)malloc(sizeof(DATA));
	A->Msg = (u8*)calloc(16, sizeof(u8));
	A->CT = (u8*)calloc(32, sizeof(u8));
	A->Key = (u8*)calloc(32, sizeof(u8));
	A->ctLen = 32;
	A->keyLen = 32;
	A->msgLen = 16;
	A->Enc = ARIA;

	fp_req = fopen("ARIA256(ECB)MCT.req", "r");
	assert(fp_req != NULL);
	fp_rsp = fopen("ARIA256(ECB)MCT.rsp", "w");
	assert(fp_rsp != NULL);

	//KEY Copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 64, A->Key);

	//PT copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 32, A->Msg);

	for (count = 0; count < 100; count++)
	{
		fprintf(fp_rsp, "COUNT = %d\n", count);

		//key
		fprintf(fp_rsp, "KEY = ");
		for (j = 0; j < 32; j++)
			fprintf(fp_rsp, "%02X", A->Key[j]);
		fprintf(fp_rsp, "\n");

		//pt
		fprintf(fp_rsp, "PT = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->Msg[j]);
		fprintf(fp_rsp, "\n");
		memcpy(temp, A->Msg, 16);
		
		for (i = 0; i < 1000; i++)
		{
			ECB(A);
			memcpy(A->Msg, A->CT, 16);
			if (i == 998)
				memcpy(temp, A->CT, 16);
		}

		//256bit key 설정
		for (int x = 0; x < 16; x++)
			A->Key[x] = A->Key[x] ^ temp[x];

		for (int x = 16; x < 32; x++)
			A->Key[x] = A->Key[x] ^ A->CT[x - 16];

		fprintf(fp_rsp, "CT = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->CT[j]);
		fprintf(fp_rsp, "\n\n");

	}


	if (fp_req != NULL)
		fclose(fp_req);

	if (fp_rsp != NULL)
		fclose(fp_rsp);
}

void MCT_CBC128()
{
	FILE* fp_req = NULL;
	FILE* fp_rsp = NULL;
	unsigned char* ptr = NULL;

	u8 buf[200] = { 0, };

	u8 value[16] = { 0, };
	u8 temp[16] = { 0, };
	u8 output[16] = { 0, };

	DATA* A = NULL;
	A = (DATA*)malloc(sizeof(DATA));
	A->Msg = (u8*)calloc(16, sizeof(u8));
	A->CT = (u8*)calloc(32, sizeof(u8));
	A->Key = (u8*)calloc(16, sizeof(u8));
	A->ctLen = 32;
	A->keyLen = 16;
	A->msgLen = 16;
	A->Enc = ARIA;

	int count = 0;
	int i = 0;
	int j = 0;

	fp_req = fopen("ARIA128(CBC)MCT.req", "r");
	assert(fp_req != NULL);
	fp_rsp = fopen("ARIA128(CBC)MCT.rsp", "w");
	assert(fp_rsp != NULL);

	//KEY Copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 32, A->Key);

	//IV Copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 32, A->IV);

	//PT copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 32, A->Msg);

	for (count = 0; count < 100; count++)
	{

		fprintf(fp_rsp, "COUNT = %d\n", count);

#if 1
		//key
		fprintf(fp_rsp, "KEY = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->Key[j]);
		fprintf(fp_rsp, "\n");

		///IV
		fprintf(fp_rsp, "IV = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->IV[j]);
		fprintf(fp_rsp, "\n");

		//PT
		fprintf(fp_rsp, "PT = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->Msg[j]);
		fprintf(fp_rsp, "\n");

#endif
#if 1


		for (i = 0; i < 1000; i++)
		{
			if (i == 0)
			{
				//CBC구조대로
				CBC(A);
				memcpy(A->Msg, A->IV, 16);
			}

			else
			{
				memcpy(temp, A->CT, 16);	
				memcpy(A->IV, A->CT, 16);
				CBC(A);
				memcpy(A->Msg, temp, 16);
			}
			if (i == 998)
				memcpy(value, A->CT, 16);	
		}

		//key세팅
		for (int x = 0; x < 16; x++)
			A->Key[x] = A->Key[x] ^ A->CT[x];

		memcpy(A->IV, A->CT, 16);
		memcpy(A->Msg, value, 16);

		fprintf(fp_rsp, "CT = ");

		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->CT[j]);
		fprintf(fp_rsp, "\n\n");

#endif
	}


	if (fp_req != NULL)
		fclose(fp_req);

	if (fp_rsp != NULL)
		fclose(fp_rsp);

}

void MCT_CBC192()
{
	FILE* fp_req = NULL;
	FILE* fp_rsp = NULL;
	unsigned char* ptr = NULL;

	u8 buf[200] = { 0, };

	u8 value[16] = { 0, };
	u8 temp[16] = { 0, };
	u8 output[16] = { 0, };

	DATA* A = NULL;
	A = (DATA*)malloc(sizeof(DATA));
	A->Msg = (u8*)calloc(16, sizeof(u8));
	A->CT = (u8*)calloc(32, sizeof(u8));
	A->Key = (u8*)calloc(24, sizeof(u8));
	A->ctLen = 32;
	A->keyLen = 24;
	A->msgLen = 16;
	A->Enc = ARIA;


	int count = 0;
	int i = 0;
	int j = 0;

	fp_req = fopen("ARIA192(CBC)MCT.req", "r");
	assert(fp_req != NULL);
	fp_rsp = fopen("ARIA192(CBC)MCT.rsp", "w");
	assert(fp_rsp != NULL);

	//KEY Copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 48, A->Key);

	//IV Copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 32, A->IV);

	//PT copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 32, A->Msg);


	for (count = 0; count < 100; count++)
	{

		fprintf(fp_rsp, "COUNT = %d\n", count);

#if 1
		//key
		fprintf(fp_rsp, "KEY = ");
		for (j = 0; j < 24; j++)
			fprintf(fp_rsp, "%02X", A->Key[j]);
		fprintf(fp_rsp, "\n");

		///IV
		fprintf(fp_rsp, "IV = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->IV[j]);
		fprintf(fp_rsp, "\n");

		//PT
		fprintf(fp_rsp, "PT = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->Msg[j]);
		fprintf(fp_rsp, "\n");

#endif
#if 1


		for (i = 0; i < 1000; i++)
		{
			if (i == 0)
			{
				CBC(A);
				memcpy(A->Msg, A->IV, 16);
			}

			else
			{
				memcpy(temp, A->CT, 16);
				memcpy(A->IV, A->CT, 16);
				CBC(A);
				memcpy(A->Msg, temp, 16);
			}
		}

		//key 재설정
		for (int x = 0; x < 8; x++)
			A->Key[x] = A->Key[x] ^ A->Msg[x + 8];
		for (int x = 8; x < 24; x++)
			A->Key[x] = A->Key[x] ^ A->CT[x - 8];

		memcpy(A->IV, A->Msg, 16);
		memcpy(A->Msg, A->CT, 16);

		fprintf(fp_rsp, "CT = ");

		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->CT[j]);
		fprintf(fp_rsp, "\n\n");

#endif
	}

	if (fp_req != NULL)
		fclose(fp_req);

	if (fp_rsp != NULL)
		fclose(fp_rsp);

}

void MCT_CBC256()
{
	FILE* fp_req = NULL;
	FILE* fp_rsp = NULL;
	unsigned char* ptr = NULL;

	u8 buf[200] = { 0, };

	u8 value[16] = { 0, };
	u8 temp[16] = { 0, };
	u8 output[16] = { 0, };

	DATA* A = NULL;
	A = (DATA*)malloc(sizeof(DATA));
	A->Msg = (u8*)calloc(16, sizeof(u8));
	A->CT = (u8*)calloc(32, sizeof(u8));
	A->Key = (u8*)calloc(32, sizeof(u8));
	A->ctLen = 32;
	A->keyLen = 32;
	A->msgLen = 16;
	A->Enc = ARIA;

	int count = 0;
	int i = 0;
	int j = 0;

	fp_req = fopen("ARIA256(CBC)MCT.req", "r");
	assert(fp_req != NULL);
	fp_rsp = fopen("ARIA256(CBC)MCT.rsp", "w");
	assert(fp_rsp != NULL);

	//KEY Copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 64, A->Key);

	//IV Copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 32, A->IV);

	//PT copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 32, A->Msg);


	for (count = 0; count < 100; count++)
	{

		fprintf(fp_rsp, "COUNT = %d\n", count);

#if 1
		//key
		fprintf(fp_rsp, "KEY = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->Key[j]);
		fprintf(fp_rsp, "\n");

		///IV
		fprintf(fp_rsp, "IV = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->IV[j]);
		fprintf(fp_rsp, "\n");

		//PT
		fprintf(fp_rsp, "PT = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->Msg[j]);
		fprintf(fp_rsp, "\n");

#endif
#if 1
		for (i = 0; i < 1000; i++)
		{
			if (i == 0)
			{
				CBC(A);
				memcpy(A->Msg, A->IV, 16);
			}

			else
			{
				memcpy(temp, A->CT, 16);
				memcpy(A->IV, A->CT, 16);
				CBC(A);
				memcpy(A->Msg, temp, 16);
			}
			if (i == 998)
				memcpy(value, A->CT, 16);
		}

		//key세팅
		for (int x = 0; x < 16; x++)
			A->Key[x] = A->Key[x] ^ value[x];
		for (int x = 16; x < 32; x++)
			A->Key[x] = A->Key[x] ^ A->CT[x - 16];

		memcpy(A->IV, A->CT, 16);
		memcpy(A->Msg, value, 16);

		fprintf(fp_rsp, "CT = ");

		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->CT[j]);
		fprintf(fp_rsp, "\n\n");

#endif
	}

	if (fp_req != NULL)
		fclose(fp_req);

	if (fp_rsp != NULL)
		fclose(fp_rsp);

}


void OFB128()
{
	FILE* fp_req = NULL;
	FILE* fp_rsp = NULL;
	unsigned char* ptr = NULL;

	u8 buf[200] = { 0, };

	u8 value[16] = { 0, };
	u8 temp[16] = { 0, };
	u8 output[16] = { 0, };
	u8 OT[16] = { 0, };
	DATA* A = NULL;
	A = (DATA*)malloc(sizeof(DATA));
	A->Msg = (u8*)calloc(16, sizeof(u8));
	A->CT = (u8*)calloc(32, sizeof(u8));
	A->Key = (u8*)calloc(16, sizeof(u8));
	A->ctLen = 32;
	A->keyLen = 16;
	A->msgLen = 16;
	A->Enc = ARIA;

	int count = 0;
	int i = 0;
	int j = 0;

	fp_req = fopen("ARIA128(OFB)MCT.req", "r");
	assert(fp_req != NULL);
	fp_rsp = fopen("ARIA128(OFB)MCT.rsp", "w");
	assert(fp_rsp != NULL);


	//KEY Copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 32, A->Key);

	//IV Copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 32, A->IV);

	//PT copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 32, A->Msg);

	for (count = 0; count < 100; count++)
	{

		fprintf(fp_rsp, "COUNT = %d\n", count);

		//key
		fprintf(fp_rsp, "KEY = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->Key[j]);
		fprintf(fp_rsp, "\n");

		///IV
		fprintf(fp_rsp, "IV = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->IV[j]);
		fprintf(fp_rsp, "\n");

		//PT
		fprintf(fp_rsp, "PT = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->Msg[j]);
		fprintf(fp_rsp, "\n");

		for (i = 0; i < 1000; i++)
		{
			if (i == 0)
			{
				//모듈에 맞춘 코딩 값
				ARIA(IV, mk, OT, 128);
				for (int z = 0; z < 16; z++)
					CT[z] = pt[z] ^ OT[z];
				copy(pt, IV, 16);
				copy(OT_1, OT, 16);
			}
			else
			{
				//OT_1 => Ot-1, OT=> OTi
				copy(temp, CT, 16);
				copy(OT_1, OT, 16);
				ARIA(OT_1, mk, OT, 128);
				for (int z = 0; z < 16; z++)
					CT[z] = pt[z] ^ OT[z];
				copy(pt, temp, 16);
			}
		}

		//key 재설정
		for (int x = 0; x < 16; x++)
			mk[x] = mk[x] ^ CT[x];

		copy(IV, CT, 16);
		fprintf(fp_rsp, "CT = ");

		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", CT[j]);
		fprintf(fp_rsp, "\n\n");
	}

}

void OFB192()
{
	FILE* fp_req = NULL;
	FILE* fp_rsp = NULL;
	unsigned char* ptr = NULL;

	Byte buf[200] = { 0, };

	Byte mk[24] = { 0, };
	Byte IV[16] = { 0, };

	Byte temp[16] = { 0, };
	Byte temp_1[16] = { 0, };
	Byte OT[16] = { 0, };
	Byte OT_1[16] = { 0, };
	Byte pt[16] = { 0, };
	Byte CT[16] = { 0, };

	int count = 0;
	int i = 0;
	int j = 0;

	fp_req = fopen("ARIA192(OFB)MCT.req", "r");
	assert(fp_req != NULL);
	fp_rsp = fopen("ARIA192(OFB)MCT.rsp", "w");
	assert(fp_rsp != NULL);

	//KEY Copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 48, mk);

	//IV Copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 32, IV);

	//PT copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 32, pt);

	for (count = 0; count < 100; count++)
	{

		fprintf(fp_rsp, "COUNT = %d\n", count);

		//key
		fprintf(fp_rsp, "KEY = ");
		for (j = 0; j < 24; j++)
			fprintf(fp_rsp, "%02X", mk[j]);
		fprintf(fp_rsp, "\n");

		///IV
		fprintf(fp_rsp, "IV = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", IV[j]);
		fprintf(fp_rsp, "\n");

		//PT
		fprintf(fp_rsp, "PT = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", pt[j]);
		fprintf(fp_rsp, "\n");

		for (i = 0; i < 1000; i++)
		{
			if (i == 0)
			{
				ARIA(IV, mk, OT, 192);
				for (int z = 0; z < 16; z++)
					CT[z] = pt[z] ^ OT[z];
				copy(pt, IV, 16);
				copy(OT_1, OT, 16);
			}
			else
			{
				copy(temp, CT, 16);
				copy(OT_1, OT, 16);
				ARIA(OT_1, mk, OT, 192);
				for (int z = 0; z < 16; z++)
					CT[z] = pt[z] ^ OT[z];
				copy(pt, temp, 16);
			}
			if (i == 998)
				copy(temp_1, CT, 16);
		}

		copy(IV, CT, 16);

		for (int x = 0; x < 8; x++)
			mk[x] ^= temp_1[x + 8];
		for (int x = 8; x < 24; x++)
			mk[x] ^= CT[x - 8];

		fprintf(fp_rsp, "CT = ");

		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", CT[j]);
		fprintf(fp_rsp, "\n\n");
	}

}

void OFB256()
{
	FILE* fp_req = NULL;
	FILE* fp_rsp = NULL;
	unsigned char* ptr = NULL;

	Byte buf[200] = { 0, };

	Byte mk[32] = { 0, };
	Byte IV[16] = { 0, };

	Byte temp[16] = { 0, };
	Byte temp_1[16] = { 0, };
	Byte OT[16] = { 0, };
	Byte OT_1[16] = { 0, };
	Byte pt[16] = { 0, };
	Byte CT[16] = { 0, };

	int count = 0;
	int i = 0;
	int j = 0;

	fp_req = fopen("ARIA256(OFB)MCT.req", "r");
	assert(fp_req != NULL);
	fp_rsp = fopen("ARIA256(OFB)MCT.rsp", "w");
	assert(fp_rsp != NULL);

	//KEY Copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 64, mk);

	//IV Copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 32, IV);

	//PT copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 32, pt);

	for (count = 0; count < 100; count++)
	{

		fprintf(fp_rsp, "COUNT = %d\n", count);

		//key
		fprintf(fp_rsp, "KEY = ");
		for (j = 0; j < 32; j++)
			fprintf(fp_rsp, "%02X", mk[j]);
		fprintf(fp_rsp, "\n");

		///IV
		fprintf(fp_rsp, "IV = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", IV[j]);
		fprintf(fp_rsp, "\n");

		//PT
		fprintf(fp_rsp, "PT = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", pt[j]);
		fprintf(fp_rsp, "\n");

		for (i = 0; i < 1000; i++)
		{
			if (i == 0)
			{
				ARIA(IV, mk, OT, 256);
				for (int z = 0; z < 16; z++)
					CT[z] = pt[z] ^ OT[z];
				copy(pt, IV, 16);
				copy(OT_1, OT, 16);
			}
			else
			{
				copy(temp, CT, 16);
				copy(OT_1, OT, 16);
				ARIA(OT_1, mk, OT, 256);
				for (int z = 0; z < 16; z++)
					CT[z] = pt[z] ^ OT[z];
				copy(pt, temp, 16);
			}

			if (i == 998)
			{
				for (int x = 0; x < 16; x++)
					temp_1[x] = CT[x];
			}
		}

		copy(IV, CT, 16);


		for (int x = 0; x < 16; x++)
			mk[x] ^= temp_1[x];
		for (int x = 16; x < 32; x++)
			mk[x] ^= CT[x - 16];

		fprintf(fp_rsp, "CT = ");

		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", CT[j]);
		fprintf(fp_rsp, "\n\n");
	}
}

int main()
{
	//MCT_ECB128();
	//MCT_ECB192();
	//MCT_ECB256();
	//MCT_CBC128();
	//MCT_CBC192();
	//MCT_CBC256();

}