/***********************************************************/
// [1-8-1] : 구조체의 메모리 구성
/***********************************************************/

#if 0

#include <stdio.h>

struct _st
{
	short a;
	int b;
	char c;
	int d;
}st = { 0x1111, 0x22222222, 0x33, 0x44444444 };

void main(void)
{
	printf("%d\n", sizeof(st));
}

#endif

/***********************************************************/
// [1-8-2] : 구조체의 메모리 절감
/***********************************************************/

#if 0

#include <stdio.h>

struct _st
{
	short a;
	char b;
	int c;
	int d;
}st = { 0x1111, 0x33, 0x22222222, 0x44444444 };

void main(void)
{
	printf("%d\n", sizeof(st));
}

#endif

/***********************************************************/
// [1-8-3] : 구조체 데이터의 parsing
/***********************************************************/

#if 0

#include <stdio.h>

//#define  BUF	 ((unsigned char *)0x100)

unsigned char buf[] = { 0x4d,0x4d,0x55,0x5f,0x45,0x6e,0x61,0x62,0x6c,0x65,0x44,0x43,0x61,0x63,0x68,0x65 };

#define  BUF	 (buf)

struct st
{
	unsigned char x;
	unsigned char y;
	unsigned short length;
};

void main(void)
{
	struct st info;

	info.x = *BUF;
	info.y = *(BUF + 1);
	info.length = *(unsigned short *)(BUF + 2);

	printf("0x%x, 0x%x, 0x%x\n", info.x, info.y, info.length);
}

#endif

/***********************************************************/
// [1-8-4] : 구조체 포인터를 이용한 액세스
/***********************************************************/

#if 0

#include <stdio.h>

unsigned char buf[] = { 0x4d,0x4d,0x55,0x5f,0x45,0x6e,0x61,0x62,0x6c,0x65,0x44,0x43,0x61,0x63,0x68,0x65 };

#define  BUF	 (buf)

struct st
{
	unsigned char x;
	unsigned char y;
	unsigned short length;
};

void main(void)
{
	struct st *info;

	info = (struct st *)BUF;
	printf("0x%x, 0x%x, 0x%x\n", info->x, info->y, info->length);

	info++;
	printf("0x%x, 0x%x, 0x%x\n", info->x, info->y, info->length);
}
#endif

#if 0

#include <stdio.h>

//#define  info	 ((struct st *)0x100)

unsigned char buf[] = { 0x4d,0x4d,0x55,0x5f,0x45,0x6e,0x61,0x62,0x6c,0x65,0x44,0x43,0x61,0x63,0x68,0x65 };

#define  info	 ((struct st *)buf)

struct st
{
	unsigned char x;
	unsigned char y;
	unsigned short length;
};

void main(void)
{
	printf("0x%x, 0x%x, 0x%x\n", info->x, info->y, info->length);
	printf("0x%x, 0x%x, 0x%x\n", (info + 1)->x, (info + 1)->y, (info + 1)->length);
}

#endif

/***********************************************************/
// [1-8-5] : 연속한 구조체 데이터
// [1-8-6] : 연속한 구조체는 구조체 배열이다
/***********************************************************/

#if 0

#include <stdio.h>

//#define  info	 ((struct st *)0x100)

unsigned char buf[] = { 0x4d,0x4d,0x55,0x5f,0x45,0x6e,0x61,0x62,0x6c,0x65,0x44,0x43,0x61,0x63,0x68,0x65 };

#define  info	 ((struct st *)buf)

struct st
{
	unsigned char x;
	unsigned char y;
	unsigned short length;
};

void main(void)
{
	int i;

	for (i = 0; i < 4; i++)
	{
		// info : 구조체 주소 => 연산자 '->'로 접근
		// info[] : 구조체 => 연산자 '.'로 접근
		printf("0x%x, 0x%x, 0x%x\n", info[i].x, info[i].y, info[i].length); <= 권장!!
		printf("0x%x, 0x%x, 0x%x\n", (info+1)->x, (info + 1)->y, (info + 1)->length);
	}
}

#endif


/***********************************************************/
// [1-8-7] : 구조체 활용의 문제점
/***********************************************************/

#if 01

#include <stdio.h>

//#define  info	 ((struct st *)0x100)

unsigned char buf[] = { 0x4d,0x4d,0x55,0x5f,0x45,0x6e,0x61,0x62,0x6c,0x65,0x44,0x43,0x61,0x63,0x68,0x65 };

#define  info	 ((struct st *)buf)

struct st
{
	unsigned char x;
	unsigned char y;
	unsigned int length;
};

void main(void)
{
	printf("0x%x, 0x%x, 0x%x\n", info[0].x, info[0].y, info[0].length);
	printf("0x%x, 0x%x, 0x%x\n", info[1].x, info[1].y, info[1].length);
}

#endif
//결과 : 
//0x4d, 0x4d, 0x62616e45
//0x6c, 0x65, 0x65686361
//alignment 규정 때문에 8byte 단위로 읽힘
// sizeof(struct st *) = 8

/***********************************************************/
// [1-8-8] : 구조체 멤버 alignment 규정
/***********************************************************/

#if 0

#include <stdio.h>

struct _s1
{
	short a;
}s1 = { 0x1234 };

struct _s2
{
	short a;
	int b;
	char c;
	double d;
}s2 = { 0x1234, 0x56789abc, 0xfe, 3.14 };

struct _s3
{
	char a;
	short b;
	int c[2];
}s3 = { 0x12, 0x3456, {0xfedcba98, 0x13579bdf} };

void main(void)
{
	printf("%d, %p\n", sizeof(s1), &s1.a);	// 2, 003FA048 
	printf("%d, %p, %p, %p, %p\n", sizeof(s2), &s2.a, &s2.b, &s2.c, &s2.d);	// 24, 003FA050, 003FA054, 003FA058, 003FA060
	printf("%d, %p, %p, %p, %p\n", sizeof(s3), &s3.a, &s3.b, &s3.c[0], &s3.c[1]);	// 12, 003FA068, 003FA06A, 003FA06C, 003FA070
}

#endif

/***********************************************************/
// [1-8-9] : pack을 사용한 구조체 멤버 alignment 규정
/***********************************************************/

#if 01

#include <stdio.h>

#pragma pack(1)

struct _s1
{
	short a;
}s1 = { 0x1234 };

#pragma pack(4)

struct _s2
{
	short a;
	int b;
	char c;
	double d;
}s2 = { 0x1234, 0x56789abc, 0xfe, 3.14 };

#pragma pack(1)

struct _s3
{
	char a;
	short b;
	int c[2];
}s3 = { 0x12, 0x3456, {0xfedcba98, 0x13579bdf} };

#pragma pack(8)

void main(void)
{
	printf("%d, %p\n", sizeof(s1), &s1.a);
	printf("%d, %p, %p, %p, %p\n", sizeof(s2), &s2.a, &s2.b, &s2.c, &s2.d);
	printf("%d, %p, %p, %p, %p\n", sizeof(s3), &s3.a, &s3.b, &s3.c[0], &s3.c[1]);
}

#endif
// 결과
// 2, 0098A074
// 20, 0098A078, 0098A07C, 0098A080, 0098A084
// 11, 0098A08C, 0098A08D, 0098A08F, 0098A093

/***********************************************************/
// [1-8-10] : pack 옵션의 이전 상태 복원
/***********************************************************/

#if 01

#include <stdio.h>

#pragma pack(show)	// warning C4810: pragma pack(show)의 값 == 8
#pragma pack(1)

struct _s1
{
	short a;
}s1 = { 0x1234 };

#pragma pack(push, 4)	// 1 push

struct _s2
{
	short a;
	int b;
	char c;
	double d;
}s2 = { 0x1234, 0x56789abc, 0xfe, 3.14 };

#pragma pack(pop)	// 1 pop
#pragma pack(show)	// warning C4810: pragma pack(show)의 값 == 1

struct _s3
{
	char a;
	short b;
	int c[2];
}s3 = { 0x12, 0x3456, {0xfedcba98, 0x13579bdf} };

#pragma pack(8)

void main(void)
{
	printf("%d, %p\n", sizeof(s1), &s1.a);
	printf("%d, %p, %p, %p, %p\n", sizeof(s2), &s2.a, &s2.b, &s2.c, &s2.d);
	printf("%d, %p, %p, %p, %p\n", sizeof(s3), &s3.a, &s3.b, &s3.c[0], &s3.c[1]);
}

#endif


/***********************************************************/
// [1-8-11] : pack으로 원하는 구조체 만들기 ( 6B 만들기 )
/***********************************************************/

#if 01

#include <stdio.h>

//#define  info	 ((struct st *)0x100)

unsigned char buf[] = { 0x4d,0x4d,0x55,0x5f,0x45,0x6e,0x61,0x62,0x6c,0x65,0x44,0x43,0x61,0x63,0x68,0x65 };

#define  info	 ((struct st *)buf)

#pragma pack( push, 1)
// or #pragma pack( push, 2)

struct st
{
	unsigned char x;
	unsigned char y;
	unsigned int length;
};

#pragma pack(pop)

void main(void)
{
	printf("%d, %p\n", sizeof(struct st), info->x);
	printf("0x%x, 0x%x, 0x%x\n", info[0].x, info[0].y, info[0].length);
	printf("0x%x, 0x%x, 0x%x\n", info[1].x, info[1].y, info[1].length);
}

#endif
// 결과 : 
// 0x4d, 0x4d, 0x6e455f55
// 0x61, 0x62, 0x4344656c
