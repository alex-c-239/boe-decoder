#pragma once

inline RestatementReason decode_reason(const std::vector<unsigned char> & bytes, size_t & n)
{
    switch (bytes[n++]) {
    case 'R':
        return RestatementReason::Reroute;
    case 'X':
        return RestatementReason::LockedInCross;
    case 'W':
        return RestatementReason::Wash;
    case 'L':
        return RestatementReason::Reload;
    case 'Q':
        return RestatementReason::LiquidityUpdated;
    default:
        return RestatementReason::Unknown;
    }
}

#define FIELD(name, offset, protocol_type, ctype)                                                                \
    inline ctype decode_order_restatement_field_##name(const std::vector<unsigned char> & bytes, size_t & start) \
    {                                                                                                            \
        return decode_##protocol_type(bytes, start = offset);                                                    \
    }

#define VAR_FIELD(name, offset, size)                                                                                  \
    inline std::string decode_order_restatement_field_##name(const std::vector<unsigned char> & bytes, size_t & start) \
    {                                                                                                                  \
        return decode_text(bytes, start = offset, size);                                                               \
    }

#include "order_restatement_fields.inl"
