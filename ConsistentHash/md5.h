#pragma once


/* typedef a 32 bit type */
typedef unsigned long int UINT4;

/* Data structure for MD5 (Message Digest) computation */
typedef struct {
	UINT4 i[2];                   /* number of _bits_ handled mod 2^64 */
	UINT4 buf[4];                                    /* scratch buffer */
	unsigned char in[64];                              /* input buffer */
	unsigned char digest[16];     /* actual digest after MD5Final call */
} MD5_CTX;

void MD5Init(MD5_CTX* mdContext);
void MD5Update(MD5_CTX* mdContext, unsigned char* inBuf, unsigned int inLen);
void MD5Final(MD5_CTX* mdContext);
static void Transform(UINT4* buf, UINT4* in);
// 指定一个文件的路径path，根据文件内容计算出一个md5加密串
char* MD5_file(const char* path, int md5_len=32);
// 从原始的字符串，得到加密后的md5串
char* MD5(const char* buf, int md5_len = 32);
// 把32位的md5串，处理成unsigned int返回
unsigned int getMD5(const char* buf);
