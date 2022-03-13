#pragma once

#include "codec.h"

#include <cmath>

/*
 * Fields
 *  Account : Text(16)
 *  Capacity : Alpha(1)
 *  ClOrdID : Text(20)
 *  MaxFloor : Binary(4)
 *  OrderQty : Binary(4)
 *  OrdType : Alphanum(1)
 *  Price : BinaryPrice(8)
 *  Side : Alphanum(1)
 *  Symbol : Alphanum(8)
 *  TimeInForce : Alphanum(1)
 */
inline unsigned char * encode_text(unsigned char * start, const std::string & str, const size_t field_size)
{
    return encode(start, str, field_size);
}

inline unsigned char * encode_char(unsigned char * start, const char ch)
{
    return encode(start, static_cast<uint8_t>(ch));
}

inline unsigned char * encode_binary4(unsigned char * start, const uint32_t value)
{
    return encode(start, value);
}

inline unsigned char * encode_price(unsigned char * start, const double value)
{
    const double order = 10000;
    const double epsilon = 1e-5;
    // beware: no precision loss check
    return encode(start, static_cast<int64_t>(value * order + std::copysign(epsilon, value)));
}

inline uint8_t decode_binary1(const std::vector<unsigned char> & bytes, size_t & start)
{
    return decode_binary(bytes, start, 1);
}

inline uint16_t decode_binary2(const std::vector<unsigned char> & bytes, size_t & start)
{
    return decode_binary(bytes, start, 2);
}

inline uint32_t decode_binary4(const std::vector<unsigned char> & bytes, size_t & start)
{
    return decode_binary(bytes, start, 4);
}

inline uint64_t decode_binary8(const std::vector<unsigned char> & bytes, size_t & start)
{
    return decode_binary(bytes, start, 8);
}

inline std::string decode_base36(const std::vector<unsigned char> & bytes, size_t & start)
{
    return convert_to_base(decode_binary8(bytes, start), 36);
}

inline double decode_price(const std::vector<unsigned char> & bytes, size_t & n)
{
    return to_signed(decode_binary8(bytes, n)) * (1e-4);
}

inline constexpr size_t char_size = 1;
inline constexpr size_t binary1_size = 1;
inline constexpr size_t binary2_size = 2;
inline constexpr size_t binary4_size = 4;
inline constexpr size_t binary8_size = 8;
inline constexpr size_t price_size = 8;

#define FIELD(name, protocol_type, ctype)                                                \
    inline unsigned char * encode_field_##name(unsigned char * start, const ctype value) \
    {                                                                                    \
        return encode_##protocol_type(start, value);                                     \
    }

#define VAR_FIELD(name, size)                                                                  \
    inline unsigned char * encode_field_##name(unsigned char * start, const std::string & str) \
    {                                                                                          \
        return encode_text(start, str, size);                                                  \
    }

#include "fields.inl"

#define FIELD(name, protocol_type, _) inline constexpr size_t name##_field_size = protocol_type##_size;
#define VAR_FIELD(name, size) inline constexpr size_t name##_field_size = size;

#include "fields.inl"

inline void set_opt_field_bit(unsigned char * bitfield_start, unsigned bitfield_num, unsigned bit)
{
    *(bitfield_start + bitfield_num - 1) |= bit;
}
