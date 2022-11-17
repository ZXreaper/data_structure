#ifndef _MD5_
#define _MD5_

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
// ָ��һ���ļ���·��path�������ļ����ݼ����һ��md5���ܴ�
char* MD5_file(const char* path, int md5_len=32);
// ��ԭʼ���ַ������õ����ܺ��md5��
char* MD5(const char* buf, int md5_len = 32);
// ��32λ��md5���������unsigned int����
unsigned int getMD5(const char* buf);
#endif