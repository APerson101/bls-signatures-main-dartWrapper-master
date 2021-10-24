#include <iostream>
#include "bls.hpp"
class BlsSignature
{
	public:
        BlsSignature();
        vector<uint8_t> generate_private_key( vector<uint8_t> seedString);
        std::string get_public_key(std::string privateKeyVector);
        std::string get_private();
        std::string get_signature();
        std::string private_key;
        std::string public_key;
        std::string signed_key;
};