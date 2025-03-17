/*
 * encryptionprocess.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Adrien
 */

#include "main.h"


// :small_blue_diamond: Affichage d'une matrice 4x4 en hexadécimal
void printMatrix(uint8_t matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%02X ", matrix[i][j]);  // Correction : affichage en hexadécimal
        }
        printf("\n");
    }
}


// Étape 2 : Décalage des lignes (ShiftRows)
void shiftRows(uint8_t state[MATRIX_SIZE][MATRIX_SIZE]) {
    uint8_t temp[MATRIX_SIZE][MATRIX_SIZE];

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            temp[i][j] = state[(i+j)%4][j];  // Correction du décalage
        }
    }

    // Copier la matrice temporaire dans la matrice originale
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            state[i][j] = temp[i][j];
        }
    }
}


// :small_blue_diamond: Étape 3 : Multiplication dans le corps de Galois GF(2^8)
uint8_t gmul(uint8_t a, uint8_t b) {
    uint8_t p = 0;
    uint8_t hi_bit_set;
    for (int i = 0; i < 8; i++) {
        if (b & 1) {
            p ^= a;  // XOR si le bit LSB de b est 1
        }
        hi_bit_set = (a & 0x80);  // Vérifie si le bit de poids fort est 1
        a <<= 1;  // Décale vers la gauche
        if (hi_bit_set) {
            a ^= 0x1B;  // XOR avec le polynôme irréductible x^8 + x^4 + x^3 + x + 1
        }
        b >>= 1;  // Décale b vers la droite
    }
    return p;
}

// :small_blue_diamond: Étape 3 : MixColumns (diffusion des octets)
void mixColumns(uint8_t state[MATRIX_SIZE][MATRIX_SIZE]) {
    uint8_t temp[4];

    for (int col = 0; col < MATRIX_SIZE; col++) {
        temp[0] = gmul(state[col][0], 2) ^ gmul(state[col][1], 3) ^ state[col][2] ^ state[col][3];
        temp[1] = state[col][0] ^ gmul(state[col][1], 2) ^ gmul(state[col][2], 3) ^ state[col][3];
        temp[2] = state[col][0] ^ state[col][1] ^ gmul(state[col][2], 2) ^ gmul(state[col][3], 3);
        temp[3] = gmul(state[col][0], 3) ^ state[col][1] ^ state[col][2] ^ gmul(state[col][3], 2);

        // Copie les nouvelles valeurs dans l'état
        for (int row = 0; row < MATRIX_SIZE; row++) {
            state[col][row] = temp[row];
        }
    }
}





// Étape 4 : AddRoundKey (XOR entre l'état et la clé)
void addRoundKey(uint8_t state[MATRIX_SIZE][MATRIX_SIZE], uint8_t key[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int col = 0; col < MATRIX_SIZE; col++) {
        for (int row = 0; row < MATRIX_SIZE; row++) {
            state[row][col] ^= key[row][col];
        }
    }
}

void getData(uint8_t data[4][4]){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			data[i][j] = matrix_test[i][j];
		}
	}
}

void readData(uint8_t data[4][4]){
	printf("Data :\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%02X ", data[i][j]);
		}
		printf("\n");
	}
}

void AesEncryption(uint8_t roundkey[11][4][4], uint8_t data[4][4]){
	addRoundKey(data, roundkey[0]);
	for (int a = 0; a < 10; a++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				data[i][j] = getSubstitution(s_box, data[i][j]);
			}
		}
		shiftRows(data);
		if(a != 9 ){
			mixColumns(data);
		}
		addRoundKey(data, roundkey[a+1]);
	}
}
