#if !defined(FIELD) || !defined(VAR_FIELD)
#error You need to define FIELD and VAR_FIELD macro
#else

VAR_FIELD(cl_ord_id, 18, 20)
FIELD(reason, 46, reason, RestatementReason)
FIELD(active_volume, 55, binary4, uint32_t)
FIELD(secondary_order_id, 59, base36, std::string)

#undef FIELD
#undef VAR_FIELD

#endif
