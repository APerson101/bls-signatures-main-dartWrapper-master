#include "testheaders.hpp"
#include <cstring>
#include <string>
#include <stdlib.h>
using namespace std;


pMather  *bls_create()
{
    pMather *m;
    BlsSignature *obj;
   m= (typeof(m))malloc(sizeof(*m));
   obj=new BlsSignature();
   m->obj=obj;
   return m;
}
void bls_generate(pMather *self, unsigned char *seedString)
{

uint8_t* myuint8array = (uint8_t*)seedString;
vector<uint8_t> values(64) ;
for( size_t i = 0 ; i < 64 ; i++ )
{
    values[i] = unsigned(myuint8array[i]) ;
}

    BlsSignature *obj;
    obj=static_cast<BlsSignature*>(self->obj);
    std::vector<uint8_t> my_vector(8);
     obj->generate_private_key(values);
  
        
        self->private_key=obj->private_key.data();
        free(myuint8array);
}
EXPORT_C void get_public_key(pMather *self, unsigned char* privateKeyVector)
{
      BlsSignature *obj;
    obj=static_cast<BlsSignature*>(self->obj);

    uint8_t* myuint8array = (uint8_t*)privateKeyVector;
vector<uint8_t> values(32) ;
for( size_t i = 0 ; i < 32 ; i++ )
{
    values[i] = unsigned(myuint8array[i]) ;
}
        obj->get_public_key(values);
        self->public_key=obj->public_key.data();
              free(myuint8array);

}
EXPORT_C void sign(pMather *self,unsigned char*privateKeyVector, unsigned char*messageVector)
{
       BlsSignature *obj;
    obj=static_cast<BlsSignature*>(self->obj);
    uint8_t* myuint8array = (uint8_t*)privateKeyVector;
    vector<uint8_t> pkv(32) ;
for( size_t i = 0 ; i < 32 ; i++ )
{
    pkv[i] = unsigned(myuint8array[i]) ;
}

   uint8_t* msgArray = (uint8_t*)messageVector;
    vector<uint8_t> msgv(8) ;
for( size_t i = 0 ; i < 8 ; i++ )
{
    msgv[i] = unsigned(msgArray[i]) ;
}


       obj->sign(pkv, msgv);
       self->signed_key=obj->signed_key.data();
}

