/***********************************************************/
// [1-9-1] : 비트필드 구조체의 특징
/***********************************************************/

#if 01

#include <stdio.h>

struct _st1
{
	unsigned char a : 2;
	unsigned char b : 3;
	unsigned char c : 2;
}x;

struct _st2
{
	unsigned int a : 2;
	unsigned int b : 3;
	unsigned int c : 2;
}y;

void main(void)
{
	y.a = x.a = 0x2;
	y.b = x.b = 0x5;
	y.c = x.c = 0x1;

	printf("%d %d\n", sizeof(x), sizeof(y));
	printf("0x%X 0x%X 0x%X 0x%X\n", x.a, x.b, y.a, y.b);
	printf("0x%.2X 0x%.8X\n", *(unsigned char *)&x, *(unsigned int *)&y);
}

#endif
// 결과
// 1 4
// 0x2 0x5 0x2 0x5
// 0x36 0x00000036

/***********************************************************/
// [1-9-2] : 파일시스템의 파일 생성 시간
/***********************************************************/

#if 0

#include <stdio.h>

unsigned char buf[] = { 0x52,0x7a };

void main(void)
{
	unsigned char hour, min, sec;
	unsigned short temp = *(unsigned short *)buf;

	// 코드 작성
	hour = (temp >> 11)&0x1f;
	min = (temp >> 5) & 0x3f;
	sec = (temp) & 0x1f;

	printf("Time=%d:%d:%d\n", hour, min, sec * 2);
}

#endif

/***********************************************************/
// [1-9-3] : 비트필드 구조체의 활용
/***********************************************************/

#if 01

#include <stdio.h>

unsigned char buf[] = { 0x52,0x7a };

// little endian
// -------------------------------------
// | 0             7|8               15|
// -------------------------------------
// | 0x52           | 0x7a             |
// -------------------------------------

// big endian
// -------------------------------------
// | 0             7|8               15|
// -------------------------------------
// | 0x7a           | 0x52             |
// -------------------------------------

// 순서 중요 ( LSB 부터 sec -> min -> hour )
struct fat_time
{
	unsigned short sec : 5;
	unsigned short min : 6;
	unsigned short hour : 5;
};

void main(void)
{
	struct fat_time * time = (struct fat_time *)buf;

	printf("Time=%d:%d:%d\n", time->hour, time->min, time->sec * 2);
	printf("Sizeof Time=%d\n", sizeof(struct fat_time));
}

#endif


/***********************************************************/
// [1-9-5] : 비트필드의 멤버의 데이터 타입
/***********************************************************/

#if 0

#include <stdio.h>

struct st
{
	int a1 : 3;
	int a2 : 2;
	int a3 : 1;
}x;

void main(void)
{
	x.a3 = -1;

	if (x.a3 == -1) printf("TRUE\n");
	else printf("FALSE\n");

	x.a3 = 1;

	if (x.a3 == 1) printf("TRUE\n");
	else printf("FALSE\n");
}

#endif

/***********************************************************/
// [1-9-6] : Unnamed 비트필드 멤버
/***********************************************************/

#if 0

#include <stdio.h>

volatile struct st
{
	unsigned short LSEON : 1;
	unsigned short LSERDY : 1;
	unsigned short LSEBYP : 1;
	unsigned short rsvd1 : 5;
	unsigned short RTCSEL : 2;
	unsigned short rsvd2 : 5;
	unsigned short RTCEN : 1;
}RTC_CR;

void main(void)
{
	printf("%d\n", sizeof(RTC_CR));
}

#endif

#if 0

#include <stdio.h>

volatile struct st
{
	unsigned short LSEON : 1;
	unsigned short LSERDY : 1;
	unsigned short LSEBYP : 1;
	unsigned short : 5;
	unsigned short RTCSEL : 2;
	unsigned short : 5;
	unsigned short RTCEN : 1;
}RTC_CR;

void main(void)
{
	printf("%d\n", sizeof(RTC_CR));
}

#endif

/***********************************************************/
// [1-9-7] : Zero Size Width 비트필드
/***********************************************************/

#if 0

#include <stdio.h>

volatile struct st
{
	unsigned int a1 : 5;
	unsigned int a2 : 25;
	unsigned int a3 : 3;
	unsigned int a4 : 4;
}x = { 0x1f, 0x0, 0x7, 0x0 };

void main(void)
{
	printf("%d\n", sizeof(x));
	printf("0x%.8x\n", ((unsigned int *)&x)[0]);
	printf("0x%.8x\n", ((unsigned int *)&x)[1]);
}

#endif

#if 0

#include <stdio.h>

volatile struct st
{
	unsigned int a1 : 5;
	unsigned int : 0;
	unsigned int a2 : 25;
	unsigned int : 0;
	unsigned int a3 : 3;
	unsigned int : 2;
	unsigned int a4 : 4;
}x = { 0x1f, 0x1fffff, 0x7, 0xf };

void main(void)
{
	printf("%d\n", sizeof(x));
	printf("0x%.8x\n", ((unsigned int *)&x)[0]);
	printf("0x%.8x\n", ((unsigned int *)&x)[1]);
	printf("0x%.8x\n", ((unsigned int *)&x)[2]);
}

#endif
// 결과
// 12
// 0x0000001f
// 0x001fffff
// 0x000001e7


/***********************************************************/
// [1-9-8] : 공용체와 구조체
/***********************************************************/

#if 0

#include <stdio.h>

union float_data
{
	float f;

	struct
	{
		unsigned int mant : 23;
		unsigned int exp : 8;
		unsigned int sign : 1;
	}bit;
}fdata;

void main(void)
{
	fdata.f = 13.625;

	printf("%f\n", fdata.f);
	printf("sign(1bit):%x\n", fdata.bit.sign);
	printf("exponent(8bit):%x\n", fdata.bit.exp);
	printf("mantissa(23bit):%x\n", fdata.bit.mant);

	fdata.bit.sign = 1;
	printf("%f\n", fdata.f);
}

#endif
// 결과
// 13.625000
// sign(1bit):0
// exponent(8bit):82
// mantissa(23bit):5a0000
// -13.625000


/***********************************************************/
// [1-9-9] : 파일시스템의 파일 종류 인식
/***********************************************************/

#if 0

#include <stdio.h>

unsigned char buf[] = { 0x25, 0x0f };

struct fat_file
{
	unsigned char r : 1;
	unsigned char h : 1;
	unsigned char s : 1;
	unsigned char v : 1;
	unsigned char d : 1;
	unsigned char a : 1;
};

#define fn	((struct fat_file *)buf)

void main(void)
{
	int i;

	for (i = 0; i < 2; i++)
	{
		if ((fn[i].r && fn[i].h && fn[i].s && fn[i].v)
			|| (fn[i].r && fn[i].h && fn[i].s && fn[i].v && fn[i].d && fn[i].a)) printf("Long File Name\n");
		else printf("A[%d]D[%d]V[%d]S[%d]H[%d]R[%d]\n", fn[i].a, fn[i].d, fn[i].v, fn[i].s, fn[i].h, fn[i].r);
	}
}

#endif

/***********************************************************/
// [1-9-10] : 효율적인 long file name의 판단
/***********************************************************/

#if 01

#include <stdio.h>

unsigned char buf[] = { 0x25, 0x0f, 0x3f };

struct fat_file
{
	unsigned char r : 1;
	unsigned char h : 1;
	unsigned char s : 1;
	unsigned char v : 1;
	unsigned char d : 1;
	unsigned char a : 1;
	unsigned char : 0;
};

struct long_file
{
	unsigned char ln : 4;
	unsigned char : 0;
};

union file
{
	struct fat_file n;
	struct long_file l;
};

#define fn	((union file *)buf)

void main(void)
{
	int i;

	for (i = 0; i < 3; i++)
	{
		if (fn[i].l.ln == 0xf ) printf("Long File Name\n");
		else printf("A[%d]D[%d]V[%d]S[%d]H[%d]R[%d]\n", fn[i].n.a, fn[i].n.d, fn[i].n.v, fn[i].n.s, fn[i].n.h, fn[i].n.r);
	}
}

#endif
