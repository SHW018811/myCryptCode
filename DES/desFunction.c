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
    Mixer function (leftBlock, rightBlock, roundKeys[round])
        copy(32, rightBlock, T1) -> T1 is extension 48bits
        function(T1, roundKey, T2) -> T2 is 32bits
        exclusiveOr(32, leftBlock, T2, T3) -> T3 is new rightBlock?
*/
void function(uint64_t T1, uint64_t roundKeys[], uint64_t *T2){
    
}

void copy(uint64_t rightBlock, uint64_t *T1){
    *T1=rightBlock;
}

void mixer(uint64_t leftBlock, uint64_t rightBlock, uint64_t roundKeys[]){
    uint64_t temper1=0;
    uint64_t temper2=0;
    copy(32, rightBlock, &temper1);
    function(&temper1, roundKeys, &temper2);
}

//i need to function and mixer