#ifndef _cAssert_HG
#define _cAssert_HG

#define SnP_BREAK() __debugbreak()


#define Snp_ASSERT(condition, ...) \
	if(!(condition))				\
		SnP_BREAK();

#endif // !_cAssert_HG
