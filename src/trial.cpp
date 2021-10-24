#include "bls.hpp"
#include "testheaders.hpp"
#include "trialc.cpp"
#include <sstream>
#include <iterator>
using namespace bls;
using namespace std;
BlsSignature::BlsSignature()
{}
std::vector<uint8_t> getRandomSeed() {
    uint8_t buf[32];
    bn_t r;
    bn_new(r);
    bn_rand(r, RLC_POS, 256);
    bn_write_bin(buf, 32, r);
    std::vector<uint8_t> ret(buf, buf + 32);
    return ret;
}

void BlsSignature::generate_private_key(vector<uint8_t> seedString)
{
 
PrivateKey sk = AugSchemeMPL().KeyGen(seedString);
vector<uint8_t> skBytes = sk.Serialize();

private_key=skBytes;
}

void BlsSignature::get_public_key(vector<uint8_t> privateKeyVector)
{
PrivateKey sk = PrivateKey::FromByteVector(privateKeyVector);
G1Element pk = sk.GetG1Element();
vector<uint8_t> pkBytes = pk.Serialize();
public_key=pkBytes;
}
void BlsSignature::sign(vector<uint8_t> privatekeyVector, vector<uint8_t> messageVector)
{
    PrivateKey sk = PrivateKey::FromByteVector(privatekeyVector);
G1Element pk = sk.GetG1Element();
G2Element signature = AugSchemeMPL().Sign(sk, messageVector);
bool ok = AugSchemeMPL().Verify(pk, messageVector, signature);
vector<uint8_t> signatureBytes = signature.Serialize();
signed_key=signatureBytes;
}
