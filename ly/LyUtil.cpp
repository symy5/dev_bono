#include "LyUtil.h"
#include "LyClib.h"


char* LyUtil_allocConstCharP(const char* pBuf)
{
	if (! pBuf) {
		return NULL;
	}

	int nNum = STRLEN(pBuf);
	int nSize = (nNum + 1) * sizeof(char);
	char* pRet =(char*) MALLOC(nSize);
	MEMSET(pRet, 0x00, nSize);

	return pRet;
}


void LyUtil_freeCharP(char* pBuf)
{
	if (pBuf) {
		FREE(pBuf);
	}
}


char* LyUtil_allocInt(int nSize)
{
	char* pRet =(char*) MALLOC(nSize);
	MEMSET(pRet, 0x00, nSize);

	return pRet;
}