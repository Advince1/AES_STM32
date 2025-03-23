/*
 * validation.h
 *
 *  Created on: Mar 20, 2025
 *      Author: Adrien
 */

#ifndef TEST_VALIDATION_H_
#define TEST_VALIDATION_H_

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "keyschedule.h"
#include "encryptionprocess.h"
#include "decryptionprocess.h"

void TestRoundKey(void);
void TestAesEncryption(void);
void TestAesDecryption(void);

#endif /* TEST_VALIDATION_H_ */
