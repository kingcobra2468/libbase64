#ifndef __BASE64__
#define __BASE64__

class base64 {

    public:

        static std::string base64_encode(std::string stringIn);
        static std::string base64_encode_f(std::string file, int buf_len);
        static std::string base64_decode(std::string stringIn);
        static std::string base64_decode_f(std::string stringIn, std::string out_file_name);

};

#endif