#if !defined(FIELD) || !defined(VAR_FIELD)
#error You need to define FIELD and VAR_FIELD macro
#else

VAR_FIELD(cl_ord_id, 18, 20)
FIELD(exec_id, 38, base36, std::string)
FIELD(filled_volume, 46, binary4, uint32_t)
FIELD(price, 50, price, double)
FIELD(active_volume, 58, binary4, uint32_t)
FIELD(liquidity_indicator, 62, liquidity_indicator, LiquidityIndicator)
VAR_FIELD(symbol, 78, 8)
VAR_FIELD(last_mkt, 86, 4)
VAR_FIELD(fee_code, 90, 2)

#undef FIELD
#undef VAR_FIELD

#endif
