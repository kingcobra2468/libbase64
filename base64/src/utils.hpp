#ifndef __UTILS__
#define __UTILS__

#include <string>
#include <fstream>
#include <iostream>

class utils
{
private:
    static const std::string base64_charset;

public:
    enum class Charsets
    {
        BASE_64,
        ASCII,
        BINARY
    };

    static void bin_to_base64(int chunk, int chunk_size, std::string &base64_string);
    static int chr_to_index(char character, Charsets charset);
    static int size_of_file(std::ifstream &file);
    static char *sub_chunk(char *buffer, int start_index, int len);

    template <class Type>
    static int to_bin(Type input, int len, int bit_rate, int chunk_size, Charsets charset)
    {

        int bin;
        int chrpos = 0;

        for (int i = 0; i < len; i++)
        {
            if (i == 0)
            {
                chrpos = chr_to_index((int)(unsigned char)input[i], charset);
                bin = chrpos << (bit_rate * ((chunk_size - i) - 1));
            }
            else
            {
                chrpos = chr_to_index((int)(unsigned char)input[i], charset);
                if (chrpos == -1)
                    break;
                bin |= (chrpos << (bit_rate * ((chunk_size - i) - 1)));
            }
        }
        return bin;
    }
};

#endif