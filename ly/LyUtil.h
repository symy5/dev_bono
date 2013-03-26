#ifndef __LYUTIL_H__
#define __LYUTIL_H__

#if defined(__cplusplus)
extern "C" {
#endif


char* LyUtil_allocConstCharP(const char* pBuf);
char* LyUtil_allocInt(int nSize);
void LyUtil_freeCharP(char* pBuf);


#if defined(__cplusplus)
}
#endif


#endif /* __LYUTIL_H__ */
