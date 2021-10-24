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
EXPORT_C struct Bls bls_generate(pMather *self);
EXPORT_C const char* get_private_key(pMather *self);
EXPORT_C const char* get_public_key(pMather *self);
EXPORT_C const char* get_signature(pMather *self);

