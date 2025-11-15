#include "allHeader.h"

/*==============================================================================
    Data Encryption Standard Code
    DATE : 2025 - 11 - 08
    WRITER : Hi_Hee1
    VERSION : 1.0v

    todoList {
        [O] : Write to encryption steps DES.
        [X] : Look at each steps and typing to code.
            [O] : Make a permute function code.
            [O] : Make a split function code.
            [X] : Generate round keys
            [X] : Make a mixer function code.
            [X] : Make about round and mixer.
            [X] : Insert to swapper in round loop.
            [X] : combine and permute. (Write)
    }
    => Result : Notes file can be crypt.
==============================================================================*/

int main(void){
    uint16_t round=1;
    //First permutation & split
    permute(64, 64, plaintext, &ciphertext, IP);
    split(64, 32, ciphertext, &leftBlock, &rightBlock);
    
    keyGenerator(key, &roundKey[0], shiftCount[0]);
    printf("%llX", roundKey[0]);
    //Start round
    while(round <= 16){

        //if(round != 16) swapper(&leftBlock, &rightBlock)
    }

    //Encryption end after all parameter reset 

    return 0;
}