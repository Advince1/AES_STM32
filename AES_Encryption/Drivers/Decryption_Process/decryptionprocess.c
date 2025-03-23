/*
 * decryptionprocess.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Adrien
 */

#include "decryptionprocess.h"

void invShiftRows(uint8_t state[MATRIX_SIZE][MATRIX_SIZE]) {
    uint8_t temp[MATRIX_SIZE][MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            temp[i][j] = state[(i-j+4)%4][j];
        }
    }
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            state[i][j] = temp[i][j];
        }
    }
}

void invMixColumns(uint8_t state[MATRIX_SIZE][MATRIX_SIZE]) {
    uint8_t temp[4];
    for (int col = 0; col < MATRIX_SIZE; col++) {
        temp[0] = gmul(state[col][0], 0x0E) ^ gmul(state[col][1], 0x0B) ^ gmul(state[col][2], 0x0D) ^ gmul(state[col][3], 0x09);
        temp[1] = gmul(state[col][0], 0x09) ^ gmul(state[col][1], 0x0E) ^ gmul(state[col][2], 0x0B) ^ gmul(state[col][3], 0x0D);
        temp[2] = gmul(state[col][0], 0x0D) ^ gmul(state[col][1], 0x09) ^ gmul(state[col][2], 0x0E) ^ gmul(state[col][3], 0x0B);
        temp[3] = gmul(state[col][0], 0x0B) ^ gmul(state[col][1], 0x0D) ^ gmul(state[col][2], 0x09) ^ gmul(state[col][3], 0x0E);
        for (int row = 0; row < MATRIX_SIZE; row++) {
            state[col][row] = temp[row];
        }
    }
}

void AesDecryption(uint8_t cypherkey[16], uint8_t data[16]) {

	uint8_t matrix_cypherkey[4][4];
	uint8_t matrix_data[4][4];

	for(int i = 0; i < 4; i++){
		for(int j = 0; j<4; j++){
			matrix_cypherkey[i][j] = cypherkey[4*i+j];
			matrix_data[i][j] = data[4*i+j];
		}
	}

	uint8_t roundkey[11][4][4];
	getRoundKey(matrix_cypherkey, roundkey);
    addRoundKey(matrix_data, roundkey[10]);
    for (int a = 9; a >= 0; a--) {
        invShiftRows(matrix_data);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                matrix_data[i][j] = getSubstitution(inv_s_box, matrix_data[i][j]);
            }
        }
        addRoundKey(matrix_data, roundkey[a]);
        if (a != 0) {
            invMixColumns(matrix_data);
        }
    }

    for(int i = 0; i < 4; i++){
    	for(int j = 0; j<4; j++){
    		cypherkey[4*i+j] = matrix_cypherkey[i][j];
    		data[4*i+j] = matrix_data[i][j];
    	}
    }
}

