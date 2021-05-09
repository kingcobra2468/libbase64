# Base64
Simple implementation of an encoder/decoder for the Base64 standard. Works on both on strings and files.

## **What's Included?**
- String to Base64 Conversion</li>
- File to Base64 Conversion</li>
- Base64 to String Conversion</li>
- Base64 to File(data dump) Conversion</li>


## **Examples**
import the library as <base64.hpp>.

### Convert String to Base64 String
```cpp
std::string base64_encoded_string = base64::base64_encode("testString");
```

### Convert a File's contents to Base64 String
```cpp
std::string base64_encoded_string = base64::base64_encode_f("/path/to/file.*");
```

### Decode Base64 String
```cpp
std::string a_string = base64::base64_decode("dGVzdFN0cmluZw==");
```

### Decode Base64 and Dump into File
```cpp
std::string file_path = base64::base64_decode_f("dGVzdFN0cmluZw==", "/path/to/file.*");
```

## **Compiling the Library**
1) Build the library with the included Makefile by running  `make`. 
2) Inside bin/ there will be options for both shared library .so file and a static archive .a file named `libbase64.so` and `libbase64.a` respectively.

## **Running the Unit Tests**
Inside tests/ there exists a few unit tests. To run them:
1) Install the catch2 header and place it inside of libs/. This could be done manually or via script `setup.sh`.
2) Compile the unit tests by running `make test`.
3) Run the tests binary, `libbase64_tests`, which could be found inside of bin/.