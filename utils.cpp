#include <string>
#include <fstream>
#include <iostream>
#include "utils.hpp"

void utils::bin_to_base64(int chunk, int chunk_size, std::string& base64_string){

    std::string base64_charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    switch (chunk_size) {

        case 3:
            base64_string.push_back(base64_charset[(chunk >> 18) & 0x3f]);
            base64_string.push_back(base64_charset[(chunk >> 12) & 0x3f]);
            base64_string.push_back(base64_charset[(chunk >> 6) & 0x3f]);
            base64_string.push_back(base64_charset[chunk & 0x3f]);
            break;
        case 2:
            base64_string.push_back(base64_charset[(chunk >> 18) & 0x3f]);
            base64_string.push_back(base64_charset[(chunk >> 12) & 0x3f]);
            base64_string.push_back(base64_charset[(chunk >> 6) & 0x3f]);
            base64_string.push_back('=');
            break;
        case 1:
            base64_string.push_back(base64_charset[(chunk >> 18) & 0x3f]);
            base64_string.push_back(base64_charset[(chunk >> 12) & 0x3f]);
            base64_string.push_back('=');
            base64_string.push_back('=');
            break; 
    }
}

int utils::chr_to_index(char character, Charsets charset){

    std::string base64_charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int chrIndex;

    switch(charset){

        case Charsets::BASE_64:
            chrIndex = base64_charset.find(character);
            break;
        case Charsets::BINARY:
            chrIndex = (int)(unsigned char)character;
            break;
        case Charsets::ASCII:
            chrIndex = character; 
            break;
    }

    return chrIndex;
}

int utils::size_of_file(std::ifstream& file) {
    
    try {
        file.seekg(0, file.end);
        int size = file.tellg();
        file.seekg(0, file.beg);
        return size;
    }
    catch (std::ifstream::failure error){
        
        std::cerr << "\nError while getting file size" << std::endl;
        std::abort();
    }
    
}

char * utils::sub_chunk(char * buffer, int start_index, int len){
    
    char * sub_buf = new char[len];
    
    for (int i = 0; i < len; i++){
        sub_buf[i] = buffer[start_index + i];
    }

    return sub_buf;
}