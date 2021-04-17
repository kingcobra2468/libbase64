#include "base64.hpp"

/** 
 * @brief  encodes string to base64
 * @param  input String to encode
 * @retval base64 encoded string 
 **/
std::string base64::base64_encode(std::string input)
{

    int size = input.size();
    std::string base64_string;
    std::string plain_chunk;

    for (int i = 0; i < size; i += 3)
    {

        if (!plain_chunk.empty())
            plain_chunk.erase();

        int chunk = 0;
        plain_chunk = input.substr(i, 3);
        int chunk_len = plain_chunk.size();
        chunk = utils::to_bin<std::string>(plain_chunk, chunk_len, 8, 3, utils::Charsets::ASCII);
        utils::bin_to_base64(chunk, chunk_len, base64_string);
    }

    return base64_string;
}

/** 
 * @brief  encodes file's contents to base64
 * @param  in_file path to file: 
 * @param  buf_len (optional) buffer size when reading file 
 * @retval base64 encoded string 
 **/
std::string base64::base64_encode_f(std::string in_file, int buf_len = -1)
{

    std::ifstream input_file;
    input_file.open(in_file, std::ifstream::binary);

    if (input_file.fail())
    {
        std::cerr << "\nFile not found" << std::endl;
        std::abort();
    }

    std::string base64_string;
    char *buffer;
    int file_size = utils::size_of_file(input_file);

    if (buf_len == -1)
    {

        buffer = new char[file_size];
        input_file.read(buffer, file_size);

        for (int chunk_pos = 0; chunk_pos < file_size; chunk_pos += 3)
        {

            int chunk_len = (chunk_pos + 3 < file_size ? 3 : file_size - chunk_pos);
            unsigned char *sub_buf = (unsigned char *)utils::sub_chunk(buffer, chunk_pos, chunk_len);
            int bin = utils::to_bin(sub_buf, chunk_len, 8, 3, utils::Charsets::BINARY);
            utils::bin_to_base64(bin, chunk_len, base64_string);
        }
    }

    else
    {

        buffer = new char[buf_len];

        if (buf_len % 3 != 0)
            buf_len = (buf_len / 3) * 3;

        for (int chunk_pos = 0; chunk_pos < file_size; chunk_pos += buf_len)
        {

            int cur_buf_len = (chunk_pos + buf_len < file_size ? buf_len : file_size - chunk_pos);
            input_file.read(buffer, cur_buf_len);

            for (int sub_chunk_pos = 0; sub_chunk_pos < cur_buf_len; sub_chunk_pos += 3)
            {

                int chunk_len = (sub_chunk_pos + 3 < cur_buf_len ? 3 : cur_buf_len - sub_chunk_pos);
                unsigned char *sub_buf = (unsigned char *)utils::sub_chunk(buffer, sub_chunk_pos, chunk_len);
                int bin = utils::to_bin(sub_buf, chunk_len, 8, 3, utils::Charsets::BINARY);
                utils::bin_to_base64(bin, chunk_len, base64_string);
            }
        }
    }

    input_file.close();
    return base64_string;
}

/** 
 * @brief  decodes base64 string
 * @param  input base64 encoded string 
 * @retval decoded base64 string 
 **/
std::string base64::base64_decode(std::string input)
{

    std::string ascii_string;

    for (unsigned i = 0; i < input.size(); i += 4)
    {

        std::string sub_string = input.substr(i, 4);
        int padCount = std::count_if(sub_string.begin(), sub_string.end(), [](char x) { return (x == '=') ? true : false; });
        int chunk = utils::to_bin<std::string>(sub_string, sub_string.size(), 6, 4, utils::Charsets::BASE_64);

        switch (padCount)
        {

        case 0:
            ascii_string.push_back((chunk >> 16) & 0xFF);
            ascii_string.push_back((chunk >> 8) & 0xFF);
            ascii_string.push_back(chunk & 0xFF);
            break;
        case 1:
            ascii_string.push_back((chunk >> 16) & 0xFF);
            ascii_string.push_back((chunk >> 8) & 0xFF);
            break;
        case 2:
            ascii_string.push_back((chunk >> 16) & 0xFF);
            break;
        }
    }

    return ascii_string;
};

/** 
 * @brief  decodes base64 string into a file.
 * @param  input base64 encoded string.
 * @param  out_file_name path to file where base64 string will be decoded to.
 * @retval path to file 
 **/
std::string base64::base64_decode_f(std::string input, std::string out_file_name)
{

    std::ofstream output_file;
    output_file.open(out_file_name, std::ofstream::binary | std::ofstream::trunc);

    if (output_file.fail())
    {
        std::cerr << "\nError creating file when decoding base64\nCheck Permissions of directory" << std::endl;
        std::abort();
    }

    for (unsigned i = 0; i < input.size(); i += 4)
    {

        std::string sub_string = input.substr(i, 4);
        int padCount = std::count_if(sub_string.begin(), sub_string.end(), [](char x) { return (x == '=') ? true : false; });

        int chunk = utils::to_bin<std::string>(sub_string, sub_string.size(), 6, 4, utils::Charsets::BASE_64);

        switch (padCount)
        {

        case 0:
            output_file.put((chunk >> 16) & 0xFF);
            output_file.put((chunk >> 8) & 0xFF);
            output_file.put(chunk & 0xFF);
            break;
        case 1:
            output_file.put((chunk >> 16) & 0xFF);
            output_file.put((chunk >> 8) & 0xFF);
            break;
        case 2:
            output_file.put((chunk >> 16) & 0xFF);
            break;
        }
    }

    output_file.flush();
    output_file.close();

    return out_file_name;
};