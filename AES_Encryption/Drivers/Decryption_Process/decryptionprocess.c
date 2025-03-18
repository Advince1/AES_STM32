/*
 * decryptionprocess.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Adrien
 */

#include "decryptionprocess.h"
#include "utils.h"

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

void AesDecryption(uint8_t roundkey[11][4][4], uint8_t data[4][4]) {
    addRoundKey(data, roundkey[10]);
    for (int a = 9; a >= 0; a--) {
        invShiftRows(data);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                data[i][j] = getSubstitution(inv_s_box, data[i][j]);
            }
        }
        addRoundKey(data, roundkey[a]);
        if (a != 0) {
            invMixColumns(data);
        }
    }
}

