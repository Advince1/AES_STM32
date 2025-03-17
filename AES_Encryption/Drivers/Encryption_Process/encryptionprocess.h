/*
 * encryptionprocess.h
 *
 *  Created on: Mar 17, 2025
 *      Author: Adrien
 */

#ifndef ENCRYPTION_PROCESS_ENCRYPTIONPROCESS_H_
#define ENCRYPTION_PROCESS_ENCRYPTIONPROCESS_H_

#include <stdint.h>

#define MATRIX_SIZE 4

void shiftRows(uint8_t matrix[MATRIX_SIZE][MATRIX_SIZE]);
int mod(int a, int b);
void printMatrix(uint8_t matrix[MATRIX_SIZE][MATRIX_SIZE]);
void saveMatrix(uint8_t matrix[MATRIX_SIZE][MATRIX_SIZE], uint8_t temp[MATRIX_SIZE][MATRIX_SIZE]);
uint8_t gmul(uint8_t a, uint8_t b);
void mixColumns(uint8_t state[MATRIX_SIZE][MATRIX_SIZE]);
void addRoundKey(uint8_t state[MATRIX_SIZE][MATRIX_SIZE], uint8_t key[MATRIX_SIZE][MATRIX_SIZE]);

#endif /* ENCRYPTION_PROCESS_ENCRYPTIONPROCESS_H_ */
