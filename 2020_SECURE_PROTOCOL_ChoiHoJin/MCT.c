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


void MCT_CFB128()
{
	FILE* fp_req = NULL;
	FILE* fp_rsp = NULL;
	unsigned char* ptr = NULL;

	u8 buffer = 0;
	u8 key[16] = { 0, };
	u8 buf[200] = { 0, };

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
	int z = 0;

	fp_req = fopen("ARIA128(CFB8)MCT.req", "r");
	assert(fp_req != NULL);
	fp_rsp = fopen("ARIA128(CFB8)MCT.rsp", "w");
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
	convertStr2Byte(ptr, 2, A->Msg);

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
		fprintf(fp_rsp, "%02X", A->Msg[0]);
		fprintf(fp_rsp, "\n");


		for (j = 0; j < 1000; j++)
		{
			if (j == 0)
			{
				CFB(A);
				A->Msg[0] = A->IV[0];
				
				for (int z = 0; z < 15; z++)
					A->IV[z] = A->IV[z + 1];
				A->IV[15] = A->CT[0];
			}

			else
			{
				CFB(A);
				A->Msg[0] = A->IV[0];

				for (int z = 0; z < 15; z++)
					A->IV[z] = A->IV[z + 1];

				A->IV[15] = A->CT[0];
			}

			//key 재설정과 pt재설정
			if (j == 983)
				buffer = A->CT[0];
			if (j > 983)
				key[j - 984] = A->CT[0];
		}

		for (int c = 0; c < 16; c++)
			A->Key[c] = A->Key[c] ^ key[c];
		
		for (int c = 0; c < 16; c++)
			A->IV[c] = key[c];

		A->Msg[0] = buffer;

		//CT
		fprintf(fp_rsp, "CT = ");
		fprintf(fp_rsp, "%02X", A->CT[0]);
		fprintf(fp_rsp, "\n\n");


	}

	if (fp_req != NULL)
		fclose(fp_req);

	if (fp_rsp != NULL)
		fclose(fp_rsp);

}

void MCT_CFB192()
{
	FILE* fp_req = NULL;
	FILE* fp_rsp = NULL;
	unsigned char* ptr = NULL;

	u8 buffer = 0;
	u8 key[24] = { 0, };
	u8 buf[200] = { 0, };

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
	int z = 0;

	fp_req = fopen("ARIA192(CFB8)MCT.req", "r");
	assert(fp_req != NULL);
	fp_rsp = fopen("ARIA192(CFB8)MCT.rsp", "w");
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
	convertStr2Byte(ptr, 2, A->Msg);

	for (count = 0; count < 100; count++)
	{

		fprintf(fp_rsp, "COUNT = %d\n", count);

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
		fprintf(fp_rsp, "%02X", A->Msg[0]);
		fprintf(fp_rsp, "\n");


		for (j = 0; j < 1000; j++)
		{
			if (j == 0)
			{
				CFB(A);
				A->Msg[0] = A->IV[0];

				for (int z = 0; z < 15; z++)
					A->IV[z] = A->IV[z + 1];
				A->IV[15] = A->CT[0];
			}

			else
			{
				CFB(A);
				A->Msg[0] = A->IV[0];

				for (int z = 0; z < 15; z++)
					A->IV[z] = A->IV[z + 1];

				A->IV[15] = A->CT[0];
			}
			//key 재설정과 pt재설정
			if (j == 983)
				buffer = A->CT[0];
			if (j > 975)
				key[j - 976] = A->CT[0];
		}

		for (int c = 0; c < 24; c++)
			A->Key[c] = A->Key[c] ^ key[c];

		for (int c = 0; c < 16; c++)
			A->IV[c] = key[c + 8];

		A->Msg[0] = buffer;

		//CT
		fprintf(fp_rsp, "CT = ");
		fprintf(fp_rsp, "%02X", A->CT[0]);
		fprintf(fp_rsp, "\n\n");


	}

	if (fp_req != NULL)
		fclose(fp_req);

	if (fp_rsp != NULL)
		fclose(fp_rsp);

}

void MCT_CFB256()
{
	FILE* fp_req = NULL;
	FILE* fp_rsp = NULL;
	unsigned char* ptr = NULL;

	u8 buffer = 0;
	u8 key[32] = { 0, };
	u8 buf[200] = { 0, };

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
	int z = 0;

	fp_req = fopen("ARIA256(CFB8)MCT.req", "r");
	assert(fp_req != NULL);
	fp_rsp = fopen("ARIA256(CFB8)MCT.rsp", "w");
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
	convertStr2Byte(ptr, 2, A->Msg);

	for (count = 0; count < 100; count++)
	{

		fprintf(fp_rsp, "COUNT = %d\n", count);

		//key
		fprintf(fp_rsp, "KEY = ");
		for (j = 0; j < 32; j++)
			fprintf(fp_rsp, "%02X", A->Key[j]);
		fprintf(fp_rsp, "\n");

		///IV
		fprintf(fp_rsp, "IV = ");
		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->IV[j]);
		fprintf(fp_rsp, "\n");

		//PT
		fprintf(fp_rsp, "PT = ");
		fprintf(fp_rsp, "%02X", A->Msg[0]);
		fprintf(fp_rsp, "\n");


		for (j = 0; j < 1000; j++)
		{
			if (j == 0)
			{
				CFB(A);
				A->Msg[0] = A->IV[0];

				for (int z = 0; z < 15; z++)
					A->IV[z] = A->IV[z + 1];
				A->IV[15] = A->CT[0];
			}

			else
			{
				CFB(A);
				A->Msg[0] = A->IV[0];

				for (int z = 0; z < 15; z++)
					A->IV[z] = A->IV[z + 1];

				A->IV[15] = A->CT[0];
			}
			//key 재설정과 pt재설정
			if (j == 983)
				buffer = A->CT[0];
			if (j > 967)
				key[j - 968] = A->CT[0];
		}

		for (int c = 0; c < 32; c++)
			A->Key[c] = A->Key[c] ^ key[c];

		for (int c = 0; c < 16; c++)
			A->IV[c] = key[c + 16];

		A->Msg[0] = buffer;

		//CT
		fprintf(fp_rsp, "CT = ");
		fprintf(fp_rsp, "%02X", A->CT[0]);
		fprintf(fp_rsp, "\n\n");


	}

	if (fp_req != NULL)
		fclose(fp_req);

	if (fp_rsp != NULL)
		fclose(fp_rsp);

}

void MCT_OFB128()
{
	FILE* fp_req = NULL;
	FILE* fp_rsp = NULL;
	unsigned char* ptr = NULL;

	u8 buf[200] = { 0, };
	u8 temp[16] = { 0, };

	u8 OT[16] = { 0, };
	u8 OT_1[16] = { 0 };

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
				OFB(A); 
				for (int j = 0; j < 16; j++) {
					A->Msg[j] = A->IV[j];
				}
				ARIA(A->IV, A->Key, OT, 16);
			}
			else
			{
				for (int j = 0; j < 16; j++)
					temp[j] = A->CT[j];

				for (int j = 0; j < 16; j++)
					A->IV[j] = OT[j];
				
				OFB(A);
				ARIA(A->IV, A->Key, OT, 16);
				for (int j = 0; j < 16; j++)
					A->Msg[j] = temp[j];
			}
		}
	
		//key 재설정
		for (int x = 0; x < 16; x++)
			A->Key[x] = A->Key[x] ^ A->CT[x];

		for (int x = 0; x < 16; x++)
			A->IV[x] = A->CT[x];
		fprintf(fp_rsp, "CT = ");

		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->CT[j]);
		fprintf(fp_rsp, "\n\n");
	}

}

void MCT_OFB192()
{
	FILE* fp_req = NULL;
	FILE* fp_rsp = NULL;
	unsigned char* ptr = NULL;

	u8 buf[200] = { 0, };
	u8 temp[16] = { 0, };

	u8 OT[16] = { 0, };
	u8 OT_1[16] = { 0 };

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

	fp_req = fopen("ARIA192(OFB)MCT.req", "r");
	assert(fp_req != NULL);
	fp_rsp = fopen("ARIA192(OFB)MCT.rsp", "w");
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

		for (i = 0; i < 1000; i++)
		{
			if (i == 0)
			{
				OFB(A);
				for (int j = 0; j < 16; j++) {
					A->Msg[j] = A->IV[j];
				}
				ARIA(A->IV, A->Key, OT, 24);
			}
			else
			{
				for (int j = 0; j < 16; j++)
					temp[j] = A->CT[j];

				for (int j = 0; j < 16; j++)
					A->IV[j] = OT[j];

				OFB(A);
				ARIA(A->IV, A->Key, OT, 24);
				for (int j = 0; j < 16; j++)
					A->Msg[j] = temp[j];
			}
			if (i == 998)
				for (int j = 0; j < 16; j++)
					OT_1[j] = A->CT[j];
		}

		//key 재설정
		for (int x = 0; x < 8; x++)
			A->Key[x] = A->Key[x] ^ OT_1[x + 8];
		for (int x = 8; x < 24; x++)
			A->Key[x] = A->Key[x] ^ A->CT[x-8];

		for (int x = 0; x < 16; x++)
			A->IV[x] = A->CT[x];
		fprintf(fp_rsp, "CT = ");

		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->CT[j]);
		fprintf(fp_rsp, "\n\n");
	}

}

void MCT_OFB256()
{
	FILE* fp_req = NULL;
	FILE* fp_rsp = NULL;
	unsigned char* ptr = NULL;

	u8 buf[200] = { 0, };
	u8 temp[16] = { 0, };

	u8 OT[16] = { 0, };
	u8 OT_1[16] = { 0 };

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

	fp_req = fopen("ARIA256(OFB)MCT.req", "r");
	assert(fp_req != NULL);
	fp_rsp = fopen("ARIA256(OFB)MCT.rsp", "w");
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

		//key
		fprintf(fp_rsp, "KEY = ");
		for (j = 0; j < 32; j++)
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
				OFB(A);
				for (int j = 0; j < 16; j++) {
					A->Msg[j] = A->IV[j];
				}
				ARIA(A->IV, A->Key, OT, 32);
			}
			else
			{
				for (int j = 0; j < 16; j++)
					temp[j] = A->CT[j];

				for (int j = 0; j < 16; j++)
					A->IV[j] = OT[j];

				OFB(A);
				ARIA(A->IV, A->Key, OT, 32);
				for (int j = 0; j < 16; j++)
					A->Msg[j] = temp[j];
			}
			if (i == 998)
				for (int j = 0; j < 16; j++)
					OT_1[j] = A->CT[j];
		}

		//key 재설정
		for (int x = 0; x < 16; x++)
			A->Key[x] = A->Key[x] ^ OT_1[x];
		for (int x = 16; x < 32; x++)
			A->Key[x] = A->Key[x] ^ A->CT[x - 16];

		for (int x = 0; x < 16; x++)
			A->IV[x] = A->CT[x];
		fprintf(fp_rsp, "CT = ");

		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->CT[j]);
		fprintf(fp_rsp, "\n\n");
	}

}

void MCT_CTR128() {

	FILE* fp_req = NULL;
	FILE* fp_rsp = NULL;
	unsigned char* ptr = NULL;

	u8 buf[200] = { 0, };

		
	DATA* A = NULL;
	A = (DATA*)malloc(sizeof(DATA));
	A->Msg = (u8*)calloc(16, sizeof(u8));
	A->CT = (u8*)calloc(32, sizeof(u8));
	A->Key = (u8*)calloc(24, sizeof(u8));
	A->ctLen = 32;
	A->keyLen = 16;
	A->msgLen = 16;
	A->Enc = ARIA;

	int count = 0;
	int i = 0;
	int j = 0;

	fp_req = fopen("ARIA128(CTR)MCT.req", "r");
	assert(fp_req != NULL);
	fp_rsp = fopen("ARIA128(CTR)MCT.rsp", "w");
	assert(fp_rsp != NULL);

	//KEY Copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 32, A->Key);

	//CTR Copy
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
		fprintf(fp_rsp, "CTR = ");
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
			//모듈 코딩 값
			CTR(A);
			for (j = 0; j < 16; j++)
				A->Msg[j] = A->CT[j];
			CTR_ADD(A->IV);
			
		}

		//key 재설정
		for (int x = 0; x < 16; x++)
			A->Key[x] ^= A->CT[x];


		fprintf(fp_rsp, "CT = ");

		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->CT[j]);
		fprintf(fp_rsp, "\n\n");
	}

}

void MCT_CTR192() {

	FILE* fp_req = NULL;
	FILE* fp_rsp = NULL;
	unsigned char* ptr = NULL;

	u8 buf[200] = { 0, };
	u8 temp[16] = { 0, };


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

	fp_req = fopen("ARIA192(CTR)MCT.req", "r");
	assert(fp_req != NULL);
	fp_rsp = fopen("ARIA192(CTR)MCT.rsp", "w");
	assert(fp_rsp != NULL);

	//KEY Copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 48, A->Key);

	//CTR Copy
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
		for (j = 0; j < 24; j++)
			fprintf(fp_rsp, "%02X", A->Key[j]);
		fprintf(fp_rsp, "\n");

		///IV
		fprintf(fp_rsp, "CTR = ");
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
			//모듈 코딩 값
			CTR(A);
			for (j = 0; j < 16; j++)
				A->Msg[j] = A->CT[j];
			CTR_ADD(A->IV);
			if (i == 998)
				for (int j = 0; j < 16; j++)
					temp[j] = A->CT[j];
		}

		//key 재설정
		for (int x = 0; x < 8; x++)
			A->Key[x] ^= temp[x + 8];
		for (int x = 8; x < 24; x++)
			A->Key[x] ^= A->CT[x - 8];


		fprintf(fp_rsp, "CT = ");

		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->CT[j]);
		fprintf(fp_rsp, "\n\n");
	}

}

void MCT_CTR256() {

	FILE* fp_req = NULL;
	FILE* fp_rsp = NULL;
	unsigned char* ptr = NULL;

	u8 buf[200] = { 0, };
	u8 temp[16] = { 0, };


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

	fp_req = fopen("ARIA256(CTR)MCT.req", "r");
	assert(fp_req != NULL);
	fp_rsp = fopen("ARIA256(CTR)MCT.rsp", "w");
	assert(fp_rsp != NULL);

	//KEY Copy
	fgets(buf, sizeof(buf), fp_req);
	ptr = strtok(buf, " =");// 공백과 띄어쓰기 무시
	ptr = strtok(NULL, " =");
	convertStr2Byte(ptr, 64, A->Key);

	//CTR Copy
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
		for (j = 0; j < 32; j++)
			fprintf(fp_rsp, "%02X", A->Key[j]);
		fprintf(fp_rsp, "\n");

		///IV
		fprintf(fp_rsp, "CTR = ");
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
			//모듈 코딩 값
			CTR(A);
			for (j = 0; j < 16; j++)
				A->Msg[j] = A->CT[j];
			CTR_ADD(A->IV);
			if (i == 998)
				for (int j = 0; j < 16; j++)
					temp[j] = A->CT[j];
		}

		//key 재설정
		for (int x = 0; x < 16; x++)
			A->Key[x] ^= temp[x];
		for (int x = 16; x < 32; x++)
			A->Key[x] ^= A->CT[x - 16];


		fprintf(fp_rsp, "CT = ");

		for (j = 0; j < 16; j++)
			fprintf(fp_rsp, "%02X", A->CT[j]);
		fprintf(fp_rsp, "\n\n");
	}

}

void MCT_TEST()
{
	MCT_CFB128();
	MCT_CFB192();
	MCT_CFB256();
	MCT_OFB128();
	MCT_OFB192();
	MCT_OFB256();
	MCT_CTR128();
	MCT_CTR192();
	MCT_CTR256();
}