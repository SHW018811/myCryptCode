#ifndef TABLE_H
#define TABLE_H

extern uint64_t plaintext;
extern uint64_t ciphertext;
extern uint64_t key;
extern uint32_t leftBlock;
extern uint32_t rightBlock;

extern uint64_t roundKey[16];
extern const uint8_t IP[64];
extern const uint8_t FP[64];
extern const uint8_t parityTable[56];
extern const uint8_t keyCompressTable[48];
extern const uint8_t shiftCount[16];


#endif //TABLE_H