#ifndef PERMUTE_H
#define PERMUTE_H

void permute(uint8_t inBits, uint8_t outBits, uint64_t inputBlock, uint64_t *outputBlock, const uint8_t table[]);
void split(uint8_t inBits, uint8_t outBits, uint64_t inputBlock, uint32_t *leftBlock, uint32_t *rightBlock);
void keyGenerator(uint64_t baseKey, uint64_t roundKeys[], const uint64_t shiftTable[]);

#endif //PERMUTE_H