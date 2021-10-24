#include <string>
#include <iostream>
#define EXPORT_C extern "C"

struct Bls
{
    void* obj; 
    const char* private_key;
    const char* public_key;
    const char* signed_key;
};
typedef struct Bls pMather;
EXPORT_C  pMather  *bls_create();
EXPORT_C uint8_t*  bls_generate(pMather *self, unsigned char *seedString);
EXPORT_C const char* get_private_key(pMather *self);
EXPORT_C const char*  get_public_key(pMather *self, const char*privateKeyVector);
// EXPORT_C const char* get_public_key(pMather *self);
EXPORT_C const char* get_signature(pMather *self);

