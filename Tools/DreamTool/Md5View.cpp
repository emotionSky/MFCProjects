// Md5View.cpp: 实现文件
//

#include "pch.h"
#include "DreamTool.h"
#include "Md5View.h"


// Md5View

IMPLEMENT_DYNCREATE(Md5View, CFormView)

Md5View::Md5View()
	: CFormView(IDD_DIALOG_MD5)
	, m_number(_T(""))
	, m_pwd(_T(""))
	, m_realme(_T(""))
	, m_nonce(_T(""))
	, m_uri(_T(""))
	, m_response(_T(""))
{

}

Md5View::~Md5View()
{
}

void Md5View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_number);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
	DDX_Text(pDX, IDC_EDIT3, m_realme);
	DDX_Text(pDX, IDC_EDIT5, m_nonce);
	DDX_Text(pDX, IDC_EDIT4, m_uri);
	DDX_Text(pDX, IDC_EDIT6, m_response);
}

BEGIN_MESSAGE_MAP(Md5View, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &Md5View::OnBnClickedButton1)
END_MESSAGE_MAP()


// Md5View 诊断

#ifdef _DEBUG
void Md5View::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void Md5View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// Md5View 消息处理程序

/* F, G, H and I are basic MD5 functions.
 */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

 /* ROTATE_LEFT rotates x left n bits.
  */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
Rotation is separate from addition to prevent recomputation.
 */
#define FF(a, b, c, d, x, s, ac) { \
 (a) += F ((b), (c), (d)) + (x) + (unsigned int)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define GG(a, b, c, d, x, s, ac) { \
 (a) += G ((b), (c), (d)) + (x) + (unsigned int)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define HH(a, b, c, d, x, s, ac) { \
 (a) += H ((b), (c), (d)) + (x) + (unsigned int)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define II(a, b, c, d, x, s, ac) { \
 (a) += I ((b), (c), (d)) + (x) + (unsigned int)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

static unsigned char PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/**
 * Structure for holding MD5 context.
 * @var MD5_CTX
 */
typedef struct 
{
	unsigned int state[4];             /* state (ABCD) */
	unsigned int count[2];             /* number of bits, modulo 2^64 (lsb first) */
	unsigned char buffer[64];   /* input buffer */
} osip_MD5_CTX;

/* Decodes input (unsigned char) into output (UINT4). Assumes len is
  a multiple of 4.
 */
static void osip_Decode(unsigned int* output, unsigned char* input, unsigned int len)
{
	unsigned int i, j;

	for (i = 0, j = 0; j < len; i++, j += 4)
		output[i] = ((unsigned int)input[j]) | (((unsigned int)input[j + 1]) << 8) | (((unsigned int)input[j + 2]) << 16) | (((unsigned int)input[j + 3]) << 24);
}

/* Encodes input (UINT4) into output (unsigned char). Assumes len is
  a multiple of 4.
 */
static void osip_Encode(unsigned char* output, unsigned int* input, unsigned int len)
{
	unsigned int i, j;

	for (i = 0, j = 0; j < len; i++, j += 4) {
		output[j] = (unsigned char)(input[i] & 0xff);
		output[j + 1] = (unsigned char)((input[i] >> 8) & 0xff);
		output[j + 2] = (unsigned char)((input[i] >> 16) & 0xff);
		output[j + 3] = (unsigned char)((input[i] >> 24) & 0xff);
	}
}

static void osip_MD5_memcpy(unsigned char* output, unsigned char* input, unsigned int len)
{
	unsigned int i;

	for (i = 0; i < len; i++)
		output[i] = input[i];
}

/* Note: Replace "for loop" with standard memset if possible.
 */
static void osip_MD5_memset(unsigned char* output, int value, unsigned int len)
{
	unsigned int i;

	for (i = 0; i < len; i++)
		((char*)output)[i] = (char)value;
}

/* MD5 basic transformation. Transforms state based on block.
 */
static void osip_MD5Transform(unsigned int state[4], unsigned char block[64])
{
	unsigned int a = state[0], b = state[1], c = state[2], d = state[3], x[16];

	osip_Decode(x, block, 64);

	/* Round 1 */
	FF(a, b, c, d, x[0], S11, 0xd76aa478);       /* 1 */
	FF(d, a, b, c, x[1], S12, 0xe8c7b756);       /* 2 */
	FF(c, d, a, b, x[2], S13, 0x242070db);       /* 3 */
	FF(b, c, d, a, x[3], S14, 0xc1bdceee);       /* 4 */
	FF(a, b, c, d, x[4], S11, 0xf57c0faf);       /* 5 */
	FF(d, a, b, c, x[5], S12, 0x4787c62a);       /* 6 */
	FF(c, d, a, b, x[6], S13, 0xa8304613);       /* 7 */
	FF(b, c, d, a, x[7], S14, 0xfd469501);       /* 8 */
	FF(a, b, c, d, x[8], S11, 0x698098d8);       /* 9 */
	FF(d, a, b, c, x[9], S12, 0x8b44f7af);       /* 10 */
	FF(c, d, a, b, x[10], S13, 0xffff5bb1);      /* 11 */
	FF(b, c, d, a, x[11], S14, 0x895cd7be);      /* 12 */
	FF(a, b, c, d, x[12], S11, 0x6b901122);      /* 13 */
	FF(d, a, b, c, x[13], S12, 0xfd987193);      /* 14 */
	FF(c, d, a, b, x[14], S13, 0xa679438e);      /* 15 */
	FF(b, c, d, a, x[15], S14, 0x49b40821);      /* 16 */

	/* Round 2 */
	GG(a, b, c, d, x[1], S21, 0xf61e2562);       /* 17 */
	GG(d, a, b, c, x[6], S22, 0xc040b340);       /* 18 */
	GG(c, d, a, b, x[11], S23, 0x265e5a51);      /* 19 */
	GG(b, c, d, a, x[0], S24, 0xe9b6c7aa);       /* 20 */
	GG(a, b, c, d, x[5], S21, 0xd62f105d);       /* 21 */
	GG(d, a, b, c, x[10], S22, 0x2441453);       /* 22 */
	GG(c, d, a, b, x[15], S23, 0xd8a1e681);      /* 23 */
	GG(b, c, d, a, x[4], S24, 0xe7d3fbc8);       /* 24 */
	GG(a, b, c, d, x[9], S21, 0x21e1cde6);       /* 25 */
	GG(d, a, b, c, x[14], S22, 0xc33707d6);      /* 26 */
	GG(c, d, a, b, x[3], S23, 0xf4d50d87);       /* 27 */
	GG(b, c, d, a, x[8], S24, 0x455a14ed);       /* 28 */
	GG(a, b, c, d, x[13], S21, 0xa9e3e905);      /* 29 */
	GG(d, a, b, c, x[2], S22, 0xfcefa3f8);       /* 30 */
	GG(c, d, a, b, x[7], S23, 0x676f02d9);       /* 31 */
	GG(b, c, d, a, x[12], S24, 0x8d2a4c8a);      /* 32 */

	/* Round 3 */
	HH(a, b, c, d, x[5], S31, 0xfffa3942);       /* 33 */
	HH(d, a, b, c, x[8], S32, 0x8771f681);       /* 34 */
	HH(c, d, a, b, x[11], S33, 0x6d9d6122);      /* 35 */
	HH(b, c, d, a, x[14], S34, 0xfde5380c);      /* 36 */
	HH(a, b, c, d, x[1], S31, 0xa4beea44);       /* 37 */
	HH(d, a, b, c, x[4], S32, 0x4bdecfa9);       /* 38 */
	HH(c, d, a, b, x[7], S33, 0xf6bb4b60);       /* 39 */
	HH(b, c, d, a, x[10], S34, 0xbebfbc70);      /* 40 */
	HH(a, b, c, d, x[13], S31, 0x289b7ec6);      /* 41 */
	HH(d, a, b, c, x[0], S32, 0xeaa127fa);       /* 42 */
	HH(c, d, a, b, x[3], S33, 0xd4ef3085);       /* 43 */
	HH(b, c, d, a, x[6], S34, 0x4881d05);        /* 44 */
	HH(a, b, c, d, x[9], S31, 0xd9d4d039);       /* 45 */
	HH(d, a, b, c, x[12], S32, 0xe6db99e5);      /* 46 */
	HH(c, d, a, b, x[15], S33, 0x1fa27cf8);      /* 47 */
	HH(b, c, d, a, x[2], S34, 0xc4ac5665);       /* 48 */

	/* Round 4 */
	II(a, b, c, d, x[0], S41, 0xf4292244);       /* 49 */
	II(d, a, b, c, x[7], S42, 0x432aff97);       /* 50 */
	II(c, d, a, b, x[14], S43, 0xab9423a7);      /* 51 */
	II(b, c, d, a, x[5], S44, 0xfc93a039);       /* 52 */
	II(a, b, c, d, x[12], S41, 0x655b59c3);      /* 53 */
	II(d, a, b, c, x[3], S42, 0x8f0ccc92);       /* 54 */
	II(c, d, a, b, x[10], S43, 0xffeff47d);      /* 55 */
	II(b, c, d, a, x[1], S44, 0x85845dd1);       /* 56 */
	II(a, b, c, d, x[8], S41, 0x6fa87e4f);       /* 57 */
	II(d, a, b, c, x[15], S42, 0xfe2ce6e0);      /* 58 */
	II(c, d, a, b, x[6], S43, 0xa3014314);       /* 59 */
	II(b, c, d, a, x[13], S44, 0x4e0811a1);      /* 60 */
	II(a, b, c, d, x[4], S41, 0xf7537e82);       /* 61 */
	II(d, a, b, c, x[11], S42, 0xbd3af235);      /* 62 */
	II(c, d, a, b, x[2], S43, 0x2ad7d2bb);       /* 63 */
	II(b, c, d, a, x[9], S44, 0xeb86d391);       /* 64 */

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;

	/* Zeroize sensitive information.
	 */
	osip_MD5_memset((unsigned char*)x, 0, sizeof(x));
}

void osip_MD5Init(osip_MD5_CTX* context)
{
	context->count[0] = context->count[1] = 0;
	context->state[0] = 0x67452301;
	context->state[1] = 0xefcdab89;
	context->state[2] = 0x98badcfe;
	context->state[3] = 0x10325476;
}

void osip_MD5Update(
	osip_MD5_CTX* context, /* context */
	unsigned char* input,   /* input block */
	unsigned int inputLen   /* length of input block */
)
{
	unsigned int i, index, partLen;

	/* Compute number of bytes mod 64 */
	index = (unsigned int)((context->count[0] >> 3) & 0x3F);

	/* Update number of bits */
	if ((context->count[0] += ((unsigned int)inputLen << 3)) < ((unsigned int)inputLen << 3))
		context->count[1]++;
	context->count[1] += ((unsigned int)inputLen >> 29);

	partLen = 64 - index;

	/* Transform as many times as possible.
	 */
	if (inputLen >= partLen) {
		osip_MD5_memcpy((unsigned char*)&context->buffer[index], (unsigned char*)input, partLen);
		osip_MD5Transform(context->state, context->buffer);

		for (i = partLen; i + 63 < inputLen; i += 64)
			osip_MD5Transform(context->state, &input[i]);

		index = 0;
	}
	else
		i = 0;

	/* Buffer remaining input */
	osip_MD5_memcpy((unsigned char*)&context->buffer[index], (unsigned char*)&input[i], inputLen - i);
}

void osip_MD5Final(
	unsigned char digest[16],        /* message digest */
	osip_MD5_CTX* context   /* context */
)
{
	unsigned char bits[8];
	unsigned int index, padLen;

	/* Save number of bits */
	osip_Encode(bits, context->count, 8);

	/* Pad out to 56 mod 64.
	 */
	index = (unsigned int)((context->count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	osip_MD5Update(context, PADDING, padLen);

	/* Append length (before padding) */
	osip_MD5Update(context, bits, 8);

	/* Store state in digest */
	osip_Encode(digest, context->state, 16);

	/* Zeroize sensitive information.
	 */
	osip_MD5_memset((unsigned char*)context, 0, sizeof(*context));
}

#define HASHLEN 16
typedef char HASH[HASHLEN];

#define HASHHEXLEN 32
typedef char HASHHEX[HASHHEXLEN + 1];

static inline void CvtHex(HASH Bin, HASHHEX Hex)
{
	unsigned short i;
	unsigned char j;

	for (i = 0; i < HASHLEN; i++)
	{
		j = (Bin[i] >> 4) & 0xf;
		if (j <= 9)
			Hex[i * 2] = (j + '0');
		else
			Hex[i * 2] = (j + 'a' - 10);
		j = Bin[i] & 0xf;
		if (j <= 9)
			Hex[i * 2 + 1] = (j + '0');
		else
			Hex[i * 2 + 1] = (j + 'a' - 10);
	};
	Hex[HASHHEXLEN] = '\0';
}

static inline void DigestCalcHA1(
	const char* pszAlg,
	const char* pszUserName,
	const char* pszRealm,
	const char* pszPassword,
	const char* pszNonce,
	const char* pszCNonce,
	HASHHEX SessionKey)
{
	osip_MD5_CTX Md5Ctx;
	HASH HA1;

	osip_MD5Init(&Md5Ctx);
	osip_MD5Update(&Md5Ctx, (unsigned char*)pszUserName, (unsigned int)strlen(pszUserName));
	osip_MD5Update(&Md5Ctx, (unsigned char*)":", 1);
	osip_MD5Update(&Md5Ctx, (unsigned char*)pszRealm, (unsigned int)strlen(pszRealm));
	osip_MD5Update(&Md5Ctx, (unsigned char*)":", 1);
	osip_MD5Update(&Md5Ctx, (unsigned char*)pszPassword, (unsigned int)strlen(pszPassword));
	osip_MD5Final((unsigned char*)HA1, &Md5Ctx);
	if ((pszAlg != NULL) && _stricmp(pszAlg, "md5-sess") == 0)
	{
		osip_MD5Init(&Md5Ctx);
		osip_MD5Update(&Md5Ctx, (unsigned char*)HA1, HASHLEN);
		osip_MD5Update(&Md5Ctx, (unsigned char*)":", 1);
		osip_MD5Update(&Md5Ctx, (unsigned char*)pszNonce, (unsigned int)strlen(pszNonce));
		osip_MD5Update(&Md5Ctx, (unsigned char*)":", 1);
		osip_MD5Update(&Md5Ctx, (unsigned char*)pszCNonce, (unsigned int)strlen(pszCNonce));
		osip_MD5Final((unsigned char*)HA1, &Md5Ctx);
	}
	CvtHex(HA1, SessionKey);
}

/* calculate request-digest/response-digest as per HTTP Digest spec */
static inline void DigestCalcResponse(
	HASHHEX HA1,	            /* H(A1) */
	const char* pszNonce,	    /* nonce from server */
	const char* pszNonceCount,	/* 8 hex digits */
	const char* pszCNonce,	    /* client nonce */
	const char* pszQop,	        /* qop-value: "", "auth", "auth-int" */
	int Aka,	                /* Calculating AKAv1-MD5 response */
	const char* pszMethod,	    /* method from the request */
	const char* pszDigestUri,	/* requested URL */
	HASHHEX HEntity,	        /* H(entity body) if qop="auth-int" */
	HASHHEX Response            /* request-digest or response-digest */
)
{
	osip_MD5_CTX Md5Ctx;
	HASH HA2;
	HASH RespHash;
	HASHHEX HA2Hex;

	/* calculate H(A2) */
	osip_MD5Init(&Md5Ctx);
	osip_MD5Update(&Md5Ctx, (unsigned char*)pszMethod, (unsigned int)strlen(pszMethod));
	osip_MD5Update(&Md5Ctx, (unsigned char*)":", 1);
	osip_MD5Update(&Md5Ctx, (unsigned char*)pszDigestUri, (unsigned int)strlen(pszDigestUri));

	if (pszQop == NULL)
		goto auth_withoutqop;
	else if (0 == _stricmp(pszQop, "auth-int"))
		goto auth_withauth_int;
	else if (0 == _stricmp(pszQop, "auth"))
		goto auth_withauth;

auth_withoutqop:
	osip_MD5Final((unsigned char*)HA2, &Md5Ctx);
	CvtHex(HA2, HA2Hex);

	/* calculate response */
	osip_MD5Init(&Md5Ctx);
	osip_MD5Update(&Md5Ctx, (unsigned char*)HA1, HASHHEXLEN);
	osip_MD5Update(&Md5Ctx, (unsigned char*)":", 1);
	osip_MD5Update(&Md5Ctx, (unsigned char*)pszNonce, (unsigned int)strlen(pszNonce));
	osip_MD5Update(&Md5Ctx, (unsigned char*)":", 1);

	goto end;

auth_withauth_int:

	osip_MD5Update(&Md5Ctx, (unsigned char*)":", 1);
	osip_MD5Update(&Md5Ctx, (unsigned char*)HEntity, HASHHEXLEN);

auth_withauth:
	osip_MD5Final((unsigned char*)HA2, &Md5Ctx);
	CvtHex(HA2, HA2Hex);

	/* calculate response */
	osip_MD5Init(&Md5Ctx);
	osip_MD5Update(&Md5Ctx, (unsigned char*)HA1, HASHHEXLEN);
	osip_MD5Update(&Md5Ctx, (unsigned char*)":", 1);
	osip_MD5Update(&Md5Ctx, (unsigned char*)pszNonce, (unsigned int)strlen(pszNonce));
	osip_MD5Update(&Md5Ctx, (unsigned char*)":", 1);
	if (Aka == 0)
	{
		osip_MD5Update(&Md5Ctx, (unsigned char*)pszNonceCount, (unsigned int)strlen(pszNonceCount));
		osip_MD5Update(&Md5Ctx, (unsigned char*)":", 1);
		osip_MD5Update(&Md5Ctx, (unsigned char*)pszCNonce, (unsigned int)strlen(pszCNonce));
		osip_MD5Update(&Md5Ctx, (unsigned char*)":", 1);
		osip_MD5Update(&Md5Ctx, (unsigned char*)pszQop, (unsigned int)strlen(pszQop));
		osip_MD5Update(&Md5Ctx, (unsigned char*)":", 1);
	}
end:
	osip_MD5Update(&Md5Ctx, (unsigned char*)HA2Hex, HASHHEXLEN);
	osip_MD5Final((unsigned char*)RespHash, &Md5Ctx);
	CvtHex(RespHash, Response);
}

void Md5View::OnBnClickedButton1()
{
	UpdateData(TRUE);
	if (m_number.IsEmpty() || m_pwd.IsEmpty() || m_realme.IsEmpty() || m_nonce.IsEmpty() || m_uri.IsEmpty())
	{
		m_response = _T("输入数据有误，请重新输入");
		UpdateData(FALSE);
		return;
	}

	HASHHEX HA1;
	HASHHEX Response;
	LPTSTR num = m_number.GetBuffer();
	DigestCalcHA1("MD5",
		m_number.GetBuffer(),
		m_realme.GetBuffer(),
		m_pwd.GetBuffer(),
		m_nonce.GetBuffer(), NULL, HA1);
	DigestCalcResponse(HA1, m_nonce.GetBuffer(),
		NULL, NULL, NULL, 0, "REGISTER",
		m_uri.GetBuffer(), NULL, Response);

	m_response.Format("%s", Response);
	UpdateData(FALSE);
}
