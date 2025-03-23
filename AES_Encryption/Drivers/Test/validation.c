/*
 * validation.c
 *
 *  Created on: Mar 20, 2025
 *      Author: Adrien
 */

#include "validation.h"

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
