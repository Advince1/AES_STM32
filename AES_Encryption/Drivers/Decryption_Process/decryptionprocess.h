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
#include "utils.h"
#include "keyschedule.h"

void invShiftRows(uint8_t state[MATRIX_SIZE][MATRIX_SIZE]);
void invMixColumns(uint8_t state[MATRIX_SIZE][MATRIX_SIZE]);
void AesDecryption(uint8_t cypherkey[16], uint8_t data[16]);



#endif /* DECRYPTION_PROCESS_DECRYPTIONPROCESS_H_ */
