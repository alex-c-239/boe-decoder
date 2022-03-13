#pragma once

inline LiquidityIndicator decode_liquidity_indicator(const std::vector<unsigned char> & bytes, size_t & start)
{
    switch (bytes[start++]) {
    case 'A':
        return LiquidityIndicator::Added;
    case 'R':
        return LiquidityIndicator::Removed;
    default:
        return LiquidityIndicator::Unknown;
    }
}

#define FIELD(name, offset, protocol_type, ctype)                                                              \
    inline ctype decode_order_execution_field_##name(const std::vector<unsigned char> & bytes, size_t & start) \
    {                                                                                                          \
        return decode_##protocol_type(bytes, start = offset);                                                  \
    }

#define VAR_FIELD(name, offset, size)                                                                                \
    inline std::string decode_order_execution_field_##name(const std::vector<unsigned char> & bytes, size_t & start) \
    {                                                                                                                \
        return decode_text(bytes, start = offset, size);                                                             \
    }

#include "order_execution_fields.inl"
