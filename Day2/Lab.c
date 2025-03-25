/**********************************************************/
// [1-3-3] : 포인터 배열
/**********************************************************/

#if 0

#include <stdio.h> 

int x[4] = { 1,2,3,4 };

void main(void)
{
	int *a[4] = { x + 3, x + 2, x + 1, x };

	printf("%d\n", x[2]);

	// 배열 a를 이용하여 x[2]를 30으로

	= 30;

	printf("%d\n", x[2]);
}

#endif

/**********************************************************/
// [1-3-4] : 대치법 활용
/**********************************************************/

#if 0

#include <stdio.h> 

int x[4] = { 1,2,3,4 };

int *f1(void)
{
	return x;
}

void f2(int *p)
{
	printf("%d == %d == %d == %d\n", x[2], *(x + 2), p[0], *p);
}

void main(void)
{
	int *p;
	int *a[4] = { x + 3, x + 2, x + 1, x };

	p = x;

	printf("%d == %d\n", x[2], p[2]);
	printf("%d == %d == %d == %d\n", x[2], *(x + 2), a[3][2], *a[1]);
	printf("%d == %d == %d == %d\n", x[2], *(x + 2), f1()[2], *(f1() + 2));
	f2(x + 2);
}

#endif

/**********************************************************/
// [1-3-5] : 포인터 배열 활용
/**********************************************************/

#if 0

#include <stdio.h> 

char err[3][25] = { "Speed Error!", "Position Error!", "Unknown Command Error!" };

void main(void)
{
	printf("%s\n", err[1]);
}

#endif

#if 0

#include <stdio.h> 

char *err[3] = { "Speed Error!", "Position Error!", "Unknown Command Error!" };

void main(void)
{
	printf("%s\n", err[1]);
}

#endif

/**********************************************************/
// [1-3-6] : 문자열의 이해
/**********************************************************/

#if 0

#include <stdio.h> 

void main(void)
{
	char a[4] = "LEW";

	printf("%p	%p \n", a, &a);
	printf("%p	%p \n", "LEW", &"LEW");
	printf("%c	%c\n", a[0], a[1]);
	printf("%c	%c\n", "LEW"[0], "LEW"[1]);
	printf("%c	%p \n", *a, a + 1);
	printf("%c	%p \n", *"LEW", "LEW" + 1);
	printf("%p	%p \n", &a, &a + 1);
	printf("%p	%p \n", &"LEW", &"LEW" + 1);
	a[0] = 'K';	// ok
	"LEW"[0] = 'M';	// error , RO-Data 변경 불가
	printf("sizeof = %d\n", sizeof("LEW"));
}

#endif

/**********************************************************/
// [1-3-7] : 문자열 바꾸기
/**********************************************************/

#if 0

#include <stdio.h> 

void Swap(char **p, char **q)
{
	char *tmp;
	tmp = *q;
	*q = *p;
	*p = tmp;
}

void main(void)
{
	char * a = "hello";
	char * b = "hi";

	printf("Before : %s, %s\n", a, b);
	Swap(&a, &b);
	printf("After : %s, %s\n", a, b);
}

#endif

/**********************************************************/
// [1-3-8] : 함수의 실행
/**********************************************************/

#if 0

#include <stdio.h> 

int add(int a, int b)
{
	return a + b;
}

void main(void)
{
	printf("%d\n", add(3, 4));
	printf("%d\n", (&add)(3, 4));
	printf("%d\n", (*add)(3, 4));
	printf("%d\n", (**add)(3, 4));
}

#endif

/**********************************************************/
// [1-3-9] : 배열을 가리키는 포인터
/**********************************************************/

#if 0

#include <stdio.h> 

void main(void)
{
	int a[4] = { 10,20,30,40 };
	int(*p)[4] = &a;

	printf("0x%p\n", p);
	printf("0x%p\n", p + 1);
	printf("0x%p\n", *p);
}

#endif
