#include "base64url.h"
#include <string>
#include <vector>

#ifdef DEBUG
#include <Poco/Logger.h>
extern Poco::Logger& logger;
#define DEBUG(...) logger.debug(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

// Prototype
// std::string base64Encode(std::vector<uint8_t> inputBuffer);
// This line goes in header file

/* Define these if they aren't already in your environment
 * #define TEXT(x) Lx    //Unicode
 * #define TCHAR wchar_t //Unicode
 * #define TCHAR char    //Not unicode
 * #define TEXT(x) x     //Not unicode
 * #define uint64_t long
 * #define uint8_t unsigned char
 * They are defined by default in Windows.h
 */

//Lookup table for encoding
//If you want to use an alternate alphabet, change the characters here
const static uint8_t encodeLookup[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
const static uint8_t padCharacter = '=';
std::string base64url::encode(uint8_t const* bytes_to_encode, unsigned int in_len)
{
    std::vector<uint8_t> inputBuffer(bytes_to_encode, bytes_to_encode + in_len);
    std::string encodedString;
    encodedString.reserve(((inputBuffer.size()/3) + (inputBuffer.size() % 3 > 0)) * 4);
    uint64_t temp;
    std::vector<uint8_t>::iterator cursor = inputBuffer.begin();
    for(size_t idx = 0; idx < inputBuffer.size()/3; idx++) {
        temp  = (*cursor++) << 16; //Convert to big endian
        temp += (*cursor++) << 8;
        temp += (*cursor++);
        encodedString.append(1, encodeLookup[(temp & 0x00FC0000) >> 18]);
        encodedString.append(1, encodeLookup[(temp & 0x0003F000) >> 12]);
        encodedString.append(1, encodeLookup[(temp & 0x00000FC0) >> 6 ]);
        encodedString.append(1, encodeLookup[(temp & 0x0000003F)      ]);
    }

    switch(inputBuffer.size() % 3)
    {
    case 1:
        temp  = (*cursor++) << 16; //Convert to big endian
        encodedString.append(1, encodeLookup[(temp & 0x00FC0000) >> 18]);
        encodedString.append(1, encodeLookup[(temp & 0x0003F000) >> 12]);
        encodedString.append(2, padCharacter);
        break;
    case 2:
        temp  = (*cursor++) << 16; //Convert to big endian
        temp += (*cursor++) << 8;
        encodedString.append(1, encodeLookup[(temp & 0x00FC0000) >> 18]);
        encodedString.append(1, encodeLookup[(temp & 0x0003F000) >> 12]);
        encodedString.append(1, encodeLookup[(temp & 0x00000FC0) >> 6 ]);
        encodedString.append(1, padCharacter);
        break;
    }
    return encodedString;
}

base64url::ByteArray base64url::decode(const std::string& input)
{
    ByteArray empty_data;
    if (input.length() % 4) { //Sanity check
        //        throw std::runtime_error("Non-Valid base64!");
        DEBUG("Non-Valid base64!");
        return empty_data;
    }
    size_t padding = 0;
    if (input.length()) {
        if (input[input.length()-1] == padCharacter) {
            padding++;
        }
        if (input[input.length()-2] == padCharacter) {
            padding++;
        }
    }

    //Setup a vector to hold the result
    ByteArray decodeduint8_ts;
    decodeduint8_ts.reserve(((input.length()/4)*3) - padding);
    uint64_t temp=0; //Holds decoded quanta
    std::string::const_iterator cursor = input.begin();
    while (cursor < input.end()) {
        for (size_t quantumPosition = 0; quantumPosition < 4; quantumPosition++) {
            temp <<= 6;
            if       (*cursor >= 0x41 && *cursor <= 0x5A) { // This area will need tweaking if
                temp |= *cursor - 0x41;		                // you are using an alternate alphabet
            } else if  (*cursor >= 0x61 && *cursor <= 0x7A) {
                temp |= *cursor - 0x47;
            } else if  (*cursor >= 0x30 && *cursor <= 0x39) {
                temp |= *cursor + 0x04;
            } else if  (*cursor == 0x2D) {
                temp |= 0x3E; //change to 0x2D for URL alphabet
            } else if  (*cursor == 0x5F) {
                temp |= 0x3F; //change to 0x5F for URL alphabet
            } else if  (*cursor == padCharacter) { //pad
                switch( input.end() - cursor )
                {
                case 1: //One pad character
                    decodeduint8_ts.push_back((temp >> 16) & 0x000000FF);
                    decodeduint8_ts.push_back((temp >> 8 ) & 0x000000FF);
                    return decodeduint8_ts;
                case 2: //Two pad characters
                    decodeduint8_ts.push_back((temp >> 10) & 0x000000FF);
                    return decodeduint8_ts;
                default:
                    DEBUG("Invalid Padding in Base 64!");
                    return empty_data;
//                    throw std::runtime_error("Invalid Padding in Base 64!");
                }
            }  else {
                DEBUG("Non-Valid Character in Base 64!");
                return empty_data;
//                throw std::runtime_error("Non-Valid Character in Base 64!");
            }
            cursor++;
        }
        decodeduint8_ts.push_back((temp >> 16) & 0x000000FF);
        decodeduint8_ts.push_back((temp >> 8 ) & 0x000000FF);
        decodeduint8_ts.push_back((temp      ) & 0x000000FF);
    }
    return decodeduint8_ts;
}
