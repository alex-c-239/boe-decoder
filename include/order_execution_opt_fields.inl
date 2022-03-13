#ifndef VAR_FIELD
#error You need to define VAR_FIELD macro
#else

VAR_FIELD(symbol, 2, 1)
VAR_FIELD(last_mkt, 7, 128)
VAR_FIELD(fee_code, 8, 1)

#undef VAR_FIELD

#endif
