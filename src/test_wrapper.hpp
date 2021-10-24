#include <string>
#include <iostream>
#define EXPORT_C extern "C"

struct Bls
{
    void* obj; 
    uint8_t* private_key;
    uint8_t* public_key;
    uint8_t* signed_key;
};
typedef struct Bls pMather;
EXPORT_C  pMather  *bls_create();
EXPORT_C void bls_generate(pMather *self, unsigned char *seedString);
EXPORT_C void  get_public_key(pMather *self, unsigned char*privateKeyVector);
EXPORT_C void sign(pMather *self,unsigned char*privateKeyVector, unsigned char*messageVector);

