import 'package:hex/hex.dart';
import 'package:path/path.dart' as path;
import 'dart:io' show Platform, Directory;
import 'package:ffi/ffi.dart';
import 'dart:ffi';
import 'package:bip39/bip39.dart' as bip;

///FUNCTION TO GENERATE PRIVATE KEY
generatePrivateKey(
    DynamicLibrary dylib, Pointer<Bls> blsObject, String mnemonic) {
  var seed = bip.mnemonicToSeed(mnemonic);
  print({"seed mnemonic", mnemonic});
  final startingPointer = calloc<Uint8>(
    seed.length,
  );
  for (var i = 0; i < seed.length; i++) {
    startingPointer[i] = seed[i];
  }
  print({"seed bytes", startingPointer.asTypedList(seed.length)});
  Pointer<Uint8> Function(Pointer<Bls>, Pointer<Uint8>) generatePrivateKey =
      dylib
          .lookup<
              NativeFunction<
                  Pointer<Uint8> Function(
                      Pointer<Bls>, Pointer<Uint8>)>>('bls_generate')
          .asFunction();
  generatePrivateKey(blsObject, startingPointer.cast<Uint8>());
  print({"Private key bytes: ", blsObject.ref.private_key.asTypedList(32)});
  print({
    "Private key encoded: ",
    HexCodec().encode(blsObject.ref.private_key.asTypedList(32))
  });
}

initializeLibrary(DynamicLibrary dylib) {
  Pointer<Bls> Function() blsfunction = dylib
      .lookup<NativeFunction<Pointer<Bls> Function()>>('bls_create')
      .asFunction();
  Pointer<Bls> blsObject = blsfunction();
  print('');
  print('*' * 30);
  print("initialization successful");
  print('*' * 30);
  print('');
  return blsObject;
}

///FUNCTION GETS PUBLIC KEY USING PRIVATE KEY
getPublicKey(DynamicLibrary dylib, Pointer<Bls> blsObject) {
  void Function(Pointer<Bls>, Pointer<Uint8>) get_public_key = dylib
      .lookup<NativeFunction<Void Function(Pointer<Bls>, Pointer<Uint8>)>>(
          'get_public_key')
      .asFunction();
  get_public_key(blsObject, blsObject.ref.private_key);
  print({"public key bytes", blsObject.ref.public_key.asTypedList(48)});
  print({
    "public key encoded",
    HexCodec().encode(blsObject.ref.public_key.asTypedList(48))
  });
}

//SIGNATURE
void sign(DynamicLibrary dylib, Pointer<Bls> blsObject) {
  void Function(Pointer<Bls>, Pointer<Uint8>, Pointer<Uint8>) sign = dylib
      .lookup<
          NativeFunction<
              Void Function(
                  Pointer<Bls>, Pointer<Uint8>, Pointer<Uint8>)>>('sign')
      .asFunction();
  var testMessage = [4, 4, 4, 4, 4];

  final messagePointer = calloc<Uint8>(
    testMessage.length,
  );
  for (var i = 0; i < testMessage.length; i++) {
    messagePointer[i] = testMessage[i];
  }
  print({"message bytes", messagePointer.asTypedList(testMessage.length)});

  sign(blsObject, blsObject.ref.private_key, messagePointer);

  print({"Signed bytes", blsObject.ref.signed_key.asTypedList(96)});

  print({
    "Signed encoded",
    HexCodec().encode(blsObject.ref.signed_key.asTypedList(96))
  });
}

void main(List<String> arguments) async {
  //load library
  var libaryPath = path.join(
      Directory.current.parent.parent.path, 'build/src/', 'libblstest.dylib');
  var dylib = DynamicLibrary.open(libaryPath);

  //initialize
  Pointer<Bls> blsObject = initializeLibrary(dylib);

  //generate get 12-words
  var seedMnemonic = bip.generateMnemonic();

  //generate private key
  generatePrivateKey(dylib, blsObject, seedMnemonic);

  print('');
  print('*' * 30);
  print('');

  //get public key from public key
  getPublicKey(dylib, blsObject);

  print('');
  print('*' * 30);
  print('');

  //sigature
  sign(dylib, blsObject);

  print('');
  print('*' * 30);
  print('');
}

class Bls extends Struct {
  external Pointer<Void> obj;
  external Pointer<Uint8> private_key;
  external Pointer<Uint8> public_key;
  external Pointer<Uint8> signed_key;
}
