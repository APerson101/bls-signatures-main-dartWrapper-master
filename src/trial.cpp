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

vector<uint8_t> BlsSignature::generate_private_key(vector<uint8_t> seedString)
{
    // uint8_t buffer[PrivateKey::PRIVATE_KEY_SIZE];
    // memcmp(buffer, getRandomSeed().data(), PrivateKey::PRIVATE_KEY_SIZE);

// vector<uint8_t> seed = {0,  50, 6,  244, 24,  199, 1,  25,  52,  88,  192,
//                         19, 18, 12, 89,  6,   220, 18, 102, 58,  209, 82,
//                         12, 62, 89, 110, 182, 9,   44, 20,  254, 22};
// string s2;
//     stringstream ss;
//     for (const auto &item : seedString) {
//         ss << hex << int(item);
//     }
//     s2 = ss.str();
PrivateKey sk = AugSchemeMPL().KeyGen(seedString);
vector<uint8_t> skBytes = sk.Serialize();

    cout<<skBytes.data()<<endl;

cout<<Util::HexStr(skBytes)<<endl;
return skBytes;
// PrivateKey sk = PrivateKey::FromByteVector(getRandomSeed(), true);
// PrivateKey sk = PrivateKey::FromByteVector(seed, true);
// cout<<seed<<endl;

G1Element pk = sk.GetG1Element();
vector<uint8_t> message = {1, 2, 3, 4, 5};  

G2Element signature = AugSchemeMPL().Sign(sk, message);

bool ok = AugSchemeMPL().Verify(pk, message, signature);
// vector<uint8_t> skBytes = sk.Serialize();
vector<uint8_t> pkBytes = pk.Serialize();
vector<uint8_t> signatureBytes = signature.Serialize();
cout<<Util::HexStr(skBytes)<<endl;
// private_key=Util::HexStr(skBytes);
private_key=Util::HexStr(skBytes);
public_key=Util::HexStr(pkBytes);
signed_key=Util::HexStr(signatureBytes);
}

std::string BlsSignature::get_public_key(std::string privateKeyVector)
{
    string s2;
    stringstream ss;
    for (const auto &item : privateKeyVector) {
        ss << hex << int(item);
    }
    s2 = ss.str();
PrivateKey sk = PrivateKey::FromByteVector(Util::HexToBytes(s2));
G1Element pk = sk.GetG1Element();
vector<uint8_t> pkBytes = pk.Serialize();
public_key=Util::HexStr(pkBytes);
cout<<public_key<<endl;
return public_key;


    // cout<<public_key<<endl;
// return public_key;
}
std::string BlsSignature::get_signature()
{
    // cout<<signed_key<<endl;

return signed_key;
}std::string BlsSignature::get_private()
{
    // cout<<private_key<<endl;

return "private_key";
}

int main()
{
}