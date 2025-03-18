/*
 * decryptionprocess.h
 *
 *  Created on: Mar 17, 2025
 *      Author: Adrien
 */

#ifndef DECRYPTION_PROCESS_DECRYPTIONPROCESS_H_
#define DECRYPTION_PROCESS_DECRYPTIONPROCESS_H_

#include <stdint.h>
#include "encryptionprocess.h"

void invShiftRows(uint8_t state[MATRIX_SIZE][MATRIX_SIZE]);
void invMixColumns(uint8_t state[MATRIX_SIZE][MATRIX_SIZE]);
void AesDecryption(uint8_t roundkey[11][4][4], uint8_t data[4][4]);



#endif /* DECRYPTION_PROCESS_DECRYPTIONPROCESS_H_ */
