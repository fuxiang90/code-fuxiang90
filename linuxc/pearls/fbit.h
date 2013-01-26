#ifndef FBIT_H_INCLUDED
#define FBIT_H_INCLUDED

#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#ifdef __cplusplus
extern          "C" {
#endif


typedef unsigned char bool;
struct fBit
{
    uint32_t  mlen;
    uint32_t *mdata;
};


/*typedef struct fBit * fBitPtr;*/

struct fBit * bitInit(uint32_t cap );

int bitInsert(uint32_t value, struct fBit * bit_ptr);
int bitFind(uint32_t value ,struct fBit * bit_ptr);
void bitPrint(struct fBit * bit_ptr);

void bitMain();
void bitCreat();
#ifdef __cplusplus
}
#endif
#endif // FBIT_H_INCLUDED
