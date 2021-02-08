#include "lc.hh"

size_t TypeI64::byte_size()
{
	return 8;
}

std::string TypeI64::as_str()
{
	return "i64";
}
