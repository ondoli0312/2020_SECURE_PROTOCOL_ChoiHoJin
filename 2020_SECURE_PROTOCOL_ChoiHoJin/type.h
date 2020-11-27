#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

unsigned char getHex(unsigned char ch);
void convertStr2Byte(unsigned char* from, int size, unsigned char* to);

#define TRUE
#define FALSE
#define Block_size	16
#define KEY_LEN		16
#define KEY_BITLEN	128

typedef struct Data {
	u8* Msg;
	u8* CT;
	u8* Key;
	u8 IV[16];
	u8 final_Msg[16];
	u32 msgLen;
	u32 keyLen;
	u32 ctLen;
	u32 padding_Flag;
	u32 Enc_Flag;
	u32 operation_Flag;

	void (*Enc)(u8*, u8*, u8*, u32);
	void (*Pad)(u8*, int);
	void (*Operation)(u8*, u8*, u8*, u8*);
}DATA;

enum {
	oneZeroPad = 0,
	ansiPad,
	pkcs7Pad,
	isoPad
};

enum {
	useLEA = 0x11000,
	useARIA,
	useAES
};

enum {
	useECB  = 0x10000,
	useCBC,
	useCFB,
	useOFB,
	useCTR
};

void LEA(const u8* pt, const u8* mk, const u8* ct, u32 keyLen);
unsigned char getHex(unsigned char ch);
void convertStr2Byte(unsigned char* from, int size, unsigned char* to); 
void XOR(u8* A, u8* B, int Len);