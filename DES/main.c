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
    uint16_t round=0;
    //First permutation & split
    permute(64, 64, plaintext, &ciphertext, IP);
    split(64, 32, ciphertext, &leftBlock, &rightBlock);

    keyGenerator(key, roundKey, shiftCount);
    //Start round
    while(round < 16){
        uint32_t oldBlock=0;
        oldBlock = rightBlock;
        mixer(leftBlock, &rightBlock, roundKey[round]);
        leftBlock = rightBlock ^ leftBlock;
        if(round < 15){
            //swapper(&leftBlock, &rightBlock);
            rightBlock = leftBlock;
            leftBlock = oldBlock;
        }
        else if(round == 15) rightBlock = oldBlock;
        printf("[Round : %d] Round key : %llX, leftBlock : %X, rightBlock : %X\n", round, roundKey[round], leftBlock, rightBlock);
        round += 1;
    }
    //Final permutation
    ciphertext = leftBlock;
    ciphertext = (ciphertext << 32) | rightBlock;
    permute(64,64,ciphertext, &ciphertext, FP);
    printf("\nCiphertext : %llX",ciphertext);

    //Encryption end after all parameter reset

    return 0;
}