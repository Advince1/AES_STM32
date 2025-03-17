/*
 * keyschedule.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Adrien
 */

#include "keyschedule.h"


#include <stdint.h>
#include <stdio.h>

uint8_t getSubstitution(uint8_t s_box[256], uint8_t value){
    return s_box[value];
}

void addRound(uint8_t previous_key[4][4], int round, uint8_t new_key[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            new_key[i][j] = previous_key[i][j];
        }
    }


    new_key[0][0] = previous_key[3][1];
    new_key[0][1] = previous_key[3][2];
    new_key[0][2] = previous_key[3][3];
    new_key[0][3] = previous_key[3][0];

    for (int i = 0; i < 4; i++) {
    	new_key[0][i] = getSubstitution(s_box,new_key[0][i]);
    }

    for (int i = 0; i < 4; i++) {
    	new_key[0][i] = new_key[0][i] ^ Rcon[round][i] ^ previous_key[0][i];
    }

    for (int i = 1; i < 4; i++) {
    	for(int j= 0; j< 4; j++){
    		new_key[i][j] = new_key[i-1][j] ^ previous_key[i][j];
    	}
    }
}

void getRoundKey(uint8_t roundkey[11][4][4]){
	for(int i = 0; i<4; i++){
	  	  for (int j = 0; j<4; j++){
	  		  roundkey[0][i][j] = cipher_key[i][j];
	  	  }
	    }

	    uint8_t prev_key[4][4];
	    uint8_t next_key[4][4];
	    for (int i = 0; i < 4; i++) {
	            for (int j = 0; j < 4; j++) {
	                prev_key[i][j] = cipher_key[i][j];
	            }
	        }

	    for(int i = 1; i<11;i++){
	  	  addRound(prev_key, i-1, next_key);
	  	  for (int j = 0; j < 4; j++) {
	  		  for (int k = 0; k < 4; k++) {
	  			  roundkey[i][j][k] = next_key[j][k];
	  		  }
	  	  }
	  	  for (int i = 0; i < 4; i++) {
	  		  for (int j = 0; j < 4; j++) {
	  			  prev_key[i][j] = next_key[i][j];
	  		  }
	  	  }
	    }
}
