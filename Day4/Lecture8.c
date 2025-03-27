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

