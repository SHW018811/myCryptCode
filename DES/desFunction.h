#ifndef PERMUTE_H
#define PERMUTE_H

void permute(uint8_t inBits, uint8_t outBits, uint64_t inputBlock, uint64_t *outputBlock, const uint8_t table[]);
void split(uint8_t inBits, uint8_t outBits, uint64_t inputBlock, uint32_t *leftBlock, uint32_t *rightBlock);
void keyGenerator(uint64_t baseKey, uint64_t roundKeys[], const uint8_t shiftTable[]);
//void copy(uint64_t rightBlock, uint64_t *T1);
void substitute(uint64_t inBlock, uint64_t *outBlock, const uint8_t substitutionTable[8][4][16]);
void function(uint64_t T1, uint64_t roundKeys, uint64_t *T2);
void mixer(uint32_t leftBlock, uint32_t *rightBlock, uint64_t roundKeys);

#endif //PERMUTE_H