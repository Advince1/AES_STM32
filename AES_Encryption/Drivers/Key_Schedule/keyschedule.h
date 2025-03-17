/*
 * keyschedule.h
 *
 *  Created on: Mar 17, 2025
 *      Author: Adrien
 */

#ifndef KEY_SCHEDULE_KEYSCHEDULE_H_
#define KEY_SCHEDULE_KEYSCHEDULE_H_

#include "utils.h"

uint8_t getSubstitution(uint8_t s_box[256],uint8_t value);
void addRound(uint8_t previous_key[4][4], int round, uint8_t new_key[4][4]);
void getRoundKey(uint8_t roundkey[11][4][4]);

#endif /* KEY_SCHEDULE_KEYSCHEDULE_H_ */
