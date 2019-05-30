# Base64
Base64 Encoder/Decoder that works both on strings and files.



<h4><b>What's Included?</b></h4>

<ul>
  <li>String to Base64 Conversion</li>
  <li>File to Base64 Conversion</li>
  <li>Base64 to String Conversion</li>
  <li>Base64 to File(data dump) Conversion</li>
</ul>

<h5><b>Include Library</b></h5>

```cpp
#include "base64.hpp"
```

<h5><b>Convert String to Base64 String</b></h5>

```cpp
std::string base64_encoded_string = base64::base64_encode("testString");
```
<h5><b>Convert a File's contents to Base64 String</b></h5>

```cpp
std::string base64_encoded_string = base64::base64_encode_f("/path/to/file.*");
```
<h5><b>Decode Base64 String</b></h5>

```cpp
std::string a_string = base64::base64_decode("dGVzdFN0cmluZw==");
```
<h5><b>Decode Base64 and Dump into File </b></h5>

```cpp
std::string file_path = base64::base64_decode_f("dGVzdFN0cmluZw==", "/path/to/file.*");
```
<h6>Note: Additional info on a function / its params / return value can be found above the function in base64.cpp or seen when using an IDE supporting intellig
