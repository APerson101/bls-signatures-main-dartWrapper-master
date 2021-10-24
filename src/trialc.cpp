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
uint8_t*  bls_generate(pMather *self, unsigned char *seedString)
{

// vector<uint8_t> vuc(static_cast<uint8_t*>(seedString), static_cast<uint8_t*>(seedString) + 32);
    // cout<<"element in seedString"<<vuc.at(0)<<endl;
    // cout<<"element in seedString"<<vuc[1]<<endl;
    // cout<<"element in seedString"<<vuc[2]<<endl;
// cout<<"vector c"<<unsigned(&seedString)<<endl;
// std::vector<uint8_t> wav_vector(seedString, sizeof(seedString));
// std::vector<unsigned char> buf=reinterpret_cast<char*>(seedString);
uint8_t* myuint8array = (uint8_t*)seedString;
vector<uint8_t> values(64) ;
// (myuint8array, myuint8array +64);
for( size_t i = 0 ; i < 64 ; i++ )
{
    values[i] = unsigned(myuint8array[i]) ;
}

// for( size_t i = 0 ; i < 64 ; i++ )
// {
//     cout<<unsigned(values[i]);
// }
// cout<<endl;
// vector<uint8_t*>& v = *reinterpret_cast<vector<uint8_t*> *>(myuint8array);
    BlsSignature *obj;
    obj=static_cast<BlsSignature*>(self->obj);
    // cout<<std::string(seedString) <<endl;
    std::vector<uint8_t> my_vector(8);
        vector<uint8_t> skBytes=obj->generate_private_key(values);
        cout<<"this is the bytes for c code"<<endl;

        for(int i=0; i<skBytes.size();i++)
{
    cout<<unsigned(skBytes[i]);
}
cout<<endl;
        uint8_t* sk= skBytes.data();
        for (int i = 0; i < 32; i++)
        {
            cout<<unsigned(sk[i]);
        }
        cout<<endl;
        
        return sk;

        // return sk;
        // struct Bls bls;
        // bls.obj=self;
        // bls.private_key=obj->private_key.c_str();
        // bls.public_key=obj->public_key.c_str();
        // bls.signed_key=obj->signed_key.c_str();
        // return bls;
}
EXPORT_C const char* get_public_key(pMather *self, const char* privateKeyVector)
{
      BlsSignature *obj;
    obj=static_cast<BlsSignature*>(self->obj);

    // BlsSignature * p=reinterpret_cast<BlsSignature*>(self);
        std::string val=obj->get_public_key(std::string(privateKeyVector));
        const char* sk=val.c_str();
        // cout<<"public key is "<<sk<<endl;
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
