#include "allHeader.h"
/*==============================================================================
    permutation{
        1. permute(64, 64, plainText, inBlock, initialPermutationTable)
        2. permute(64, 64, outBlock, cipherBlock, finalPermutationTable)

        [mixer]
        permute(32, 48, inBlock, T1, expansionPermutationTable)
        permute(32, 32, T3, outBlock, straightPermutationTable)
    }
==============================================================================*/
void permute(uint8_t inBits, uint8_t outBits, uint64_t inputBlock, uint64_t *outputBlock, const uint8_t table[]){
    int i;
    *outputBlock = 0;
    for(i=0; i<outBits; i++){
        *outputBlock |= (inputBlock >> (inBits - table[i])) & 1;
        if(i != (outBits) - 1) *outputBlock <<= 1;
    }
}

//Split function (64, 32, inBlock, leftBlock, rightBlock)
void split(uint8_t inBits, uint8_t outBits, uint64_t inputBlock, uint32_t *leftBlock, uint32_t *rightBlock){
    uint32_t masking=0;
    int i=0;
    for(; i<outBits; i++){
        masking |= 0xf;
        if(i != outBits-1) masking <<= 4;
    }
    *rightBlock = masking & inputBlock;
    *leftBlock  = (inputBlock >> outBits) & masking;
}

/*
    Make a first key generator.
        1. parity drop
        2. split the key
        3. 56bit compress to 48bit
*/

void keyGenerator(uint64_t baseKey, uint64_t roundKeys[], const uint8_t shiftTable[]){
    uint32_t leftKey=0;
    uint32_t rightKey=0;
    uint64_t combKey=0;
    uint8_t temp[2]={0,0}; //temp[0] is left && temp[1] is right.

    permute(64, 56, baseKey, roundKeys, parityTable);
    split(56, 28, *roundKeys, &leftKey, &rightKey);
    
    for(int i=0; i<16; i++){
        if(shiftTable[i] == 1){
            temp[0]=((leftKey >> 27) & 1);
            temp[1]=((rightKey >> 27) & 1);
        }
        else if(shiftTable[i] == 2){
            temp[0]=((leftKey >> 26) & 3);
            temp[1]=((rightKey >> 26) & 3);
        }
        leftKey <<= shiftTable[i];
        rightKey <<= shiftTable[i];
        leftKey |= temp[0];
        rightKey |= temp[1];
        //masking
        leftKey &= 0xFFFFFFF;
        rightKey &= 0xFFFFFFF;
        //Creative combine
        combKey = leftKey;
        combKey <<= 28;
        combKey |= rightKey;
    
        permute(56, 48, combKey, &roundKeys[i], keyCompressTable);
    }
}


/*
    Mixer function (leftBlock, rightBlock, roundKeys[round])
        copy(32, rightBlock, T1) -> T1 is extension 48bits
        function(T1, roundKey, T2) -> T2 is 32bits
        exclusiveOr(32, leftBlock, T2, T3) -> T3 is new rightBlock?
*/
void substitute(uint64_t inBlock, uint64_t *outBlock, const uint8_t substitutionTable[8][4][16]){
    uint8_t row=0, col=0, temp=0, cnt = 0;
    for(int i=42; i>=0; i-=6){
        temp=(inBlock >> i) & 0x3F;
        row=((temp & 0x20) >> 4) | (temp & 1);
        col=(temp >> 1) & 0xF;
        *outBlock |= substitutionTable[cnt][row][col];
        cnt += 1;
        if(i != 0) *outBlock <<= 4;
    }
}

void function(uint64_t T1, uint64_t roundKeys, uint64_t *T2){
    uint64_t result = 0;
    permute(32, 48, T1, T2, expansionTable);
    *T2 = *T2 ^ roundKeys;
    //Operation sBox
    substitute(*T2, &result, sBox);
    permute(32, 32, result, T2, straightPBox);
}

void mixer(uint32_t leftBlock, uint32_t *rightBlock, uint64_t roundKeys){
    uint64_t oldRightBlock=0;
    uint64_t temper2=0;
    //copy
    oldRightBlock = *rightBlock;
    function(oldRightBlock, roundKeys, &temper2);
    *rightBlock = temper2;
}

//Swap left right block.
void swapper(uint32_t *leftBlock, uint32_t *rightBlock){

}