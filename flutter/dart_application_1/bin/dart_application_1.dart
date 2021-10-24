import 'dart:typed_data';
import 'dart:convert' as c;

import 'package:hex/hex.dart';
import 'package:path/path.dart' as path;
import 'dart:io' show Platform, Directory;
import 'package:ffi/ffi.dart';
import 'dart:ffi';
import 'package:bip39/bip39.dart' as bip39;

void main(List<String> arguments) async {
  var libaryPath = path.join(
      Directory.current.parent.parent.path, 'build/src/', 'libblstest.dylib');
  var dylib = DynamicLibrary.open(libaryPath);
  Pointer<Bls> Function() blsfunction = dylib
      .lookup<NativeFunction<Pointer<Bls> Function()>>('bls_create')
      .asFunction();
  Pointer<Bls> blsObject = blsfunction();
  var seed = bip39.mnemonicToSeed(bip39.generateMnemonic(strength: 256));
  // var seed = bip39.generateMnemonic();
  print(seed.lengthInBytes);
  // var outBuf = allocate<Uint8>(count: outSize);
  final startingPointer = calloc<Uint8>(
    seed.length,
  );
  for (var i = 0; i < seed.length; i++) {
    // print(seed[i]);
    startingPointer[i] = seed[i];
  }
  print(startingPointer.asTypedList(seed.length));
  // final pointerList = startingPointer.asTypedList(seed.length);
  // pointerList.setAll(0, seed);
  // print(pointerList);
  // pointerList.print({"seed original", seed});
  // Pointer<Uint8> things = calloc<Uint8>(seed.length);
  // final thing = arena.allocate(seed.length);
  // calloc<Uint8>()
  Pointer<Uint8> Function(Pointer<Bls>, Pointer<Uint8>) generateKeys = dylib
      .lookup<
          NativeFunction<
              Pointer<Uint8> Function(
                  Pointer<Bls>, Pointer<Uint8>)>>('bls_generate')
      .asFunction();
  final tt = generateKeys(blsObject, startingPointer.cast<Uint8>());
  print({'private key bytes', tt.asTypedList(32)});
  calloc.free(startingPointer);
  // print(HexCodec().encode(tt.asTypedList(32)));
  // print(pointerList);

  // print({
  //   "private key",
  //   tt.private_key.toDartString(),
  // });

  // Pointer<Utf8> Function(Pointer<Bls>, Pointer<Utf8>) get_public_key = dylib
  //     .lookup<
  //         NativeFunction<
  //             Pointer<Utf8> Function(
  //                 Pointer<Bls>, Pointer<Utf8>)>>('get_public_key')
  //     .asFunction();
  // final pk =
  //     get_public_key(blsObject, tt.private_key.toDartString().toNativeUtf8());

  // print({
  //   "public key",
  //   pk.toDartString(),
  // });
  //   "public key",
  //   tt.public_key.toDartString(),
  //   "signed key",
  //   tt.signed_key.toDartString()
  // });
}

class Bls extends Struct {
  external Pointer<Void> obj;
  external Pointer<Utf8> private_key;
  external Pointer<Utf8> public_key;
  external Pointer<Utf8> signed_key;
}
