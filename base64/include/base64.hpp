#ifndef __BASE64__
#define __BASE64__

#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <fstream>
#include "utils.hpp"

namespace base64
{
    std::string base64_encode(std::string stringIn);
    std::string base64_encode_f(std::string file, int buf_len);
    std::string base64_decode(std::string stringIn);
    std::string base64_decode_f(std::string stringIn, std::string out_file_name);
};

#endif