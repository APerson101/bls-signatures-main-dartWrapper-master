#include <iostream>
#include "bls.hpp"
class BlsSignature
{
	public:
        BlsSignature();
        void generate_private_key();
        std::string get_private();
        std::string get_public_key();
        std::string get_signature();
        std::string private_key;
        std::string public_key;
        std::string signed_key;
};