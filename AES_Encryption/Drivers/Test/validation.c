/*
 * validation.c
 *
 *  Created on: Mar 20, 2025
 *      Author: Adrien
 */

#include "validation.h"

static uint8_t nist_cypher_key[16] = {
	0x2b, 0x7e, 0x15, 0x16,
	0x28, 0xae, 0xd2, 0xa6,
	0xab, 0xf7, 0x15, 0x88,
	0x09, 0xcf, 0x4f, 0x3c
};

static uint8_t nist_decrypted[16] = {
	0x32, 0x43, 0xf6, 0xa8,
	0x88, 0x5a, 0x30, 0x8d,
	0x31, 0x31, 0x98, 0xa2,
	0xe0, 0x37, 0x07, 0x34
};

static uint8_t nist_encrypted[16] = {
    0x39, 0x25, 0x84, 0x1d,
    0x02, 0xdc, 0x09, 0xfb,
    0xdc, 0x11, 0x85, 0x97,
    0x19, 0x6a, 0x0b, 0x32
};

static uint8_t nist_round_keys[11][4][4] = {
				{
						{0x2B, 0x7E, 0x15, 0x16},
						{0x28, 0xAE, 0xD2, 0xA6},
						{0xAB, 0xF7, 0x15, 0x88},
						{0x09, 0xCF, 0x4F, 0x3C}
				},
				{
						{0xa0, 0xfa, 0xfe, 0x17},
						{0x88, 0x54, 0x2c, 0xb1},
						{0x23, 0xa3, 0x39, 0x39},
						{0x2a, 0x6c, 0x76, 0x05}
				},
				{
						{0xf2, 0xc2, 0x95, 0xf2},
						{0x7a, 0x96, 0xb9, 0x43},
						{0x59, 0x35, 0x80, 0x7a},
						{0x73, 0x59, 0xf6, 0x7f}
				},
				{
						{0x3d, 0x80, 0x47, 0x7d},
						{0x47, 0x16, 0xfe, 0x3e},
						{0x1e, 0x23, 0x7e, 0x44},
						{0x6d, 0x7a, 0x88, 0x3b}
				},
				{
						{0xef, 0x44, 0xa5, 0x41},
						{0xa8, 0x52, 0x5b, 0x7f},
						{0xb6, 0x71, 0x25, 0x3b},
						{0xdb, 0x0b, 0xad, 0x00}
				},
				{
						{0xd4, 0xd1, 0xc6, 0xf8},
						{0x7c, 0x83, 0x9d, 0x87},
						{0xca, 0xf2, 0xb8, 0xbc},
						{0x11, 0xf9, 0x15, 0xbc}
				},
				{
						{0x6d, 0x88, 0xa3, 0x7a},
						{0x11, 0x0b, 0x3e, 0xfd},
						{0xdb, 0xf9, 0x86, 0x41},
						{0xca, 0x00, 0x93, 0xfd}
				},
				{
						{0x4e, 0x54, 0xf7, 0x0e},
						{0x5f, 0x5f, 0xc9, 0xf3},
						{0x84, 0xa6, 0x4f, 0xb2},
						{0x4e, 0xa6, 0xdc, 0x4f}
				},
				{
						{0xea, 0xd2, 0x73, 0x21},
						{0xb5, 0x8d, 0xba, 0xd2},
						{0x31, 0x2b, 0xf5, 0x60},
						{0x7f, 0x8d, 0x29, 0x2f}
				},
				{
						{0xac, 0x77, 0x66, 0xf3},
						{0x19, 0xfa, 0xdc, 0x21},
						{0x28, 0xd1, 0x29, 0x41},
						{0x57, 0x5c, 0x00, 0x6e}
				},
				{
						{0xd0, 0x14, 0xf9, 0xa8},
						{0xc9, 0xee, 0x25, 0x89},
						{0xe1, 0x3f, 0x0c, 0xc8},
						{0xb6, 0x63, 0x0c, 0xa6}
				}
};

void TestRoundKey(void){
	uint8_t nistkey[4][4];
	for (int i = 0; i < 4; i++) {
		 for (int j = 0; j < 4; j++) {
			  nistkey[i][j] = nist_cypher_key[4*i+j];
		  }
	 }
	uint8_t nistroundkey[11][4][4];
	getRoundKey(nistkey, nistroundkey);

	int tot = 0;
	for(int i = 1; i<11; i++){
		int cpt = 0;
		for(int j=0; j<4; j++){
			for(int k = 0; k<4; k++){
				if(nistroundkey[i][j][k] == nist_round_keys[i][j][k]){
					cpt++;
				}
			}
		}
		if(cpt==16){
			tot++;
		}
	}
	if(tot == 10){
		printf("NIST ROUNDKEY VALIDATION TEST : OK\n");
	}else{
		printf("NIST ROUNDKEY VALIDATION TEST : NOT OK\n");
	}
}

void TestAesEncryption(void){
	uint8_t nistdata[16];
	for(int i = 0; i<16; i++){
		nistdata[i] = nist_decrypted[i];
	}
	uint8_t nistkey[16];
	for(int i = 0; i<16; i++){
		nistkey[i] = nist_cypher_key[i];
	}

	AesEncryption(nistkey, nistdata);

	int cpt = 0;

	for(int i = 0; i<16; i++){
		if(nistdata[i] == nist_encrypted[i]){
			cpt++;
		}
	}

	if(cpt==16){
		printf("NIST AES ENCRYPTION VALIDATION TEST : OK\n");
	}else{
		printf("NIST AES ENCRYPTION VALIDATION TEST : NOT OK\n");
	}
}

void TestAesDecryption(void){
	uint8_t nistdata[16];
	for(int i = 0; i<16; i++){
		nistdata[i] = nist_encrypted[i];
	}
	uint8_t nistkey[16];
	for(int i = 0; i<16; i++){
		nistkey[i] = nist_cypher_key[i];
	}

	AesDecryption(nistkey, nistdata);

	int cpt = 0;

	for(int i = 0; i<16; i++){

		if(nistdata[i] == nist_decrypted[i]){
			cpt++;
		}
	}

	if(cpt==16){
		printf("NIST AES DECRYPTION VALIDATION TEST : OK\n");
	}else{
		printf("NIST AES DECRYPTION VALIDATION TEST : NOT OK\n");
	}
}
