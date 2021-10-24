#include <iostream>
#include "bls.hpp"
class BlsSignature
{
	public:
        BlsSignature();
        void generate_private_key( vector<uint8_t> seedString);
        void get_public_key(vector<uint8_t> privateKeyVector);
        void sign(vector<uint8_t> privatekeyVector, vector<uint8_t> messageVector);
        vector<uint8_t> private_key;
        vector<uint8_t>  public_key;
        vector<uint8_t> signed_key;
};