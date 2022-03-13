#pragma once

#include <algorithm>
#include <cstdint>
#include <limits>
#include <string>
#include <vector>

inline unsigned char * encode(unsigned char * start, const uint8_t value)
{
    *start = value;
    return start + 1;
}

inline unsigned char * encode(unsigned char * start, const uint16_t value)
{
    *start++ = static_cast<unsigned char>(value & 0xFF);
    *start++ = static_cast<unsigned char>((value >> 8) & 0xFF);
    return start;
}

inline unsigned char * encode(unsigned char * start, const uint32_t value)
{
    *start++ = static_cast<unsigned char>(value & 0xFF);
    *start++ = static_cast<unsigned char>((value >> 8) & 0xFF);
    *start++ = static_cast<unsigned char>((value >> 16) & 0xFF);
    *start++ = static_cast<unsigned char>((value >> 24) & 0xFF);
    return start;
}

inline unsigned char * encode(unsigned char * start, uint64_t value)
{
    for (int i = 0; i < 8; ++i) {
        *start++ = static_cast<unsigned char>(value & 0xFF);
        value >>= 8;
    }
    return start;
}

inline unsigned char * encode(unsigned char * start, int64_t value)
{
    for (int i = 0; i < 8; ++i) {
        *start++ = static_cast<unsigned char>(value & 0xFF);
        value >>= 8;
    }
    return start;
}

inline unsigned char * encode(unsigned char * start, const std::string & str, const size_t field_size)
{
    size_t i = 0;
    while (i < str.size() && i < field_size) {
        *start++ = str[i];
        ++i;
    }
    while (i < field_size) {
        *start++ = '\0';
        ++i;
    }
    return start;
}

inline uint64_t decode_binary(const std::vector<unsigned char> & bytes, size_t & from, size_t length)
{
    uint64_t result = 0;
    for (size_t i = 0; i < length; ++i) {
        result *= 256;
        result += bytes[from + length - 1 - i];
    }
    from += length;
    return result;
}

inline int64_t to_signed(uint64_t n)
{
    if (n <= std::numeric_limits<int64_t>::max()) {
        return static_cast<int64_t>(n);
    }
    if (n >= static_cast<uint64_t>(std::numeric_limits<int64_t>::min())) {
        return static_cast<int64_t>(n - std::numeric_limits<int64_t>::min()) + std::numeric_limits<int64_t>::min();
    }
    throw n;
}

inline std::string decode_text(const std::vector<unsigned char> & bytes, size_t & from, size_t length)
{
    std::string result = std::string{
            reinterpret_cast<const char *>(&bytes[from]),
            std::min(
                    length,
                    (std::lower_bound(
                             bytes.begin() + from,
                             bytes.begin() + from + length,
                             '\0',
                             std::greater<>()) -
                     bytes.begin()) -
                            from)};
    from += length;
    return result;
}

inline std::string convert_to_base(uint64_t n, uint8_t base)
{
    if (n == 0) {
        return "0";
    }
    std::string str = "";
    while (n > 0) {
        uint8_t digit = n % base;
        str += static_cast<char>((digit < 10) ? ('0' + digit) : ('A' + digit - 10));
        n /= base;
    }
    std::reverse(str.begin(), str.end());
    return str;
}
