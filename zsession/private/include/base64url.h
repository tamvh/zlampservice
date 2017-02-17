#ifndef B64_H
#define B64_H

#include <string>
#include <vector>

class base64url
{
public:
    typedef std::vector<uint8_t> ByteArray;
public:
    static std::string encode(uint8_t const* bytes_to_encode, unsigned int in_len);
    static ByteArray decode(const std::string& input);
};

#endif // B64_H
