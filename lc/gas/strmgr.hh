#ifndef LORD_LC_GAS_STRMGR_HH
#define LORD_LC_GAS_STRMGR_HH

class StrMgr : public std::vector<std::string> {
public:
	size_t make(std::string s);
};

#endif
