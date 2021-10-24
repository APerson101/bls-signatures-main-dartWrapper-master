import 'package:path/path.dart' as path;
import 'dart:io' show Platform, Directory;
import 'package:ffi/ffi.dart';
import 'dart:ffi';

void main(List<String> arguments) async {
  var libaryPath = path.join(
      Directory.current.parent.parent.path, 'build/src/', 'libblstest.dylib');
  var dylib = DynamicLibrary.open(libaryPath);
  Pointer<Bls> Function() blsfunction = dylib
      .lookup<NativeFunction<Pointer<Bls> Function()>>('bls_create')
      .asFunction();
  Pointer<Bls> blsObject = blsfunction();

  Bls Function(Pointer<Bls>) generateKeys = dylib
      .lookup<NativeFunction<Bls Function(Pointer<Bls>)>>('bls_generate')
      .asFunction();
  final tt = generateKeys(blsObject);
  print({
    "private key",
    tt.private_key.toDartString(),
    "public key",
    tt.public_key.toDartString(),
    "signed key",
    tt.signed_key.toDartString()
  });
}

class Bls extends Struct {
  external Pointer<Void> obj;
  external Pointer<Utf8> private_key;
  external Pointer<Utf8> public_key;
  external Pointer<Utf8> signed_key;
}
