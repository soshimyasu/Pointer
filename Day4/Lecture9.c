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
