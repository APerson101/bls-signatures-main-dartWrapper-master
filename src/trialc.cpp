#include "testheaders.hpp"
#include <cstring>
#include <string>
using namespace std;


pMather  *bls_create()
{
    pMather *m;
    BlsSignature *obj;
   m= (typeof(m))malloc(sizeof(*m));
   obj=new BlsSignature();
   m->obj=obj;
   return m;
    // return new (std::nothrow)BlsSignature();
}
struct Bls bls_generate(pMather *self)
{

    BlsSignature *obj;
    obj=static_cast<BlsSignature*>(self->obj);
        obj->generate_private_key();
        struct Bls bls;
        bls.obj=self;
        bls.private_key=obj->private_key.c_str();
        bls.public_key=obj->public_key.c_str();
        bls.signed_key=obj->signed_key.c_str();
        return bls;
}
EXPORT_C const char* get_public_key(pMather *self)
{
      BlsSignature *obj;
    obj=static_cast<BlsSignature*>(self->obj);

    // BlsSignature * p=reinterpret_cast<BlsSignature*>(self);
        std::string val=obj->get_public_key();
        const char* sk=val.c_str();
        cout<<"public key is "<<sk<<endl;
        return sk;
}
EXPORT_C const char* get_signature(pMather* self)
{
    // BlsSignature * p=reinterpret_cast<BlsSignature*>(self);
    //     std::string val=p->get_signature(); 
    //     const char* sg=val.c_str();
    //     cout<<"Signature is "<<sg<<endl;
        return "sg";
}

EXPORT_C const char* get_private_key(pMather* self)
{
    // BlsSignature * p=reinterpret_cast<BlsSignature*>(self);
    //     std::string val=p->get_private();
    //     const char* pk=val.c_str();
    //     cout<<"private key is "<<pk<<endl;
        return "pk";
}
