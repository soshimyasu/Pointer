#include <stdio.h>

int add(int a, int b)
{
	return a + b;
}

void f1(void)
{
	printf("func\n");
}

int * f2(void)
{ // f2 == a 
	static int a[4] = { 1,2,3,4 };

	return a;
}

void main(void)
{
	// p, q, r 선언
	int (*p)(int a, int b);
	void (*q)(void);
	int *(*r)(void);

	// p, q, r에 대응 함수 대입
	p = add;
	q = f1;
	r = f2;

	printf("%d\n", add(3, 4));
	f1();
	printf("%d\n", f2()[2]);	// f2() type : int *

	// 위와 동일한 결과가 나오도록 p, q, r로 실행
	printf("%d\n", p(3, 4));
	q();
	printf("%d\n", r()[2]);	// f2() type : int *
}

// ---------------------------------------------------------------------------
// 함수를 함수에 전달
// ---------------------------------------------------------------------------
#include <stdio.h> 

int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

void func(int (*p)(int,int))
{
	printf("%d\n", p(3, 4));
}

void main(void)
{
	func(add);
	func(sub);
}


// ---------------------------------------------------------------------------
// 함수 포인터 파라메터 미 지정 ( 권장 안함 )
// ---------------------------------------------------------------------------
#include <stdio.h> 

int add(int a, int b)
{
	return a + b;
}

int sqr(int a)
{
	return a * a;
}

int func(void)
{
	return 100;
}

// add, sqr, func에 공통적인 함수 등가포인터 p 설계
int(*p)();

void main(void)
{
	p = add;
	printf("%d\n", p(3, 4));

	p = sqr;
	printf("%d\n", p(3));

	p = func;
	printf("%d\n", p());
}


// ---------------------------------------------------------------------------
// Lookup table를 활용한 함수 포인터
// ---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

int mul(int a, int b)
{
	return a * b;
}

int get_key(void)
{
	static int r = 0;
	int ret = r;

	r = (r + 1) % 3;
	return ret;
}

int(*fa[3])(int, int) = { add, sub, mul };	// int (*)(int, int)

int op(int a, int b)
{
	return fa[get_key()](a, b);
}

void main(void)
{
	printf("%d\n", op(3, 4));
	printf("%d\n", op(3, 4));
	printf("%d\n", op(3, 4));
	printf("%d\n", op(3, 4));
	printf("%d\n", op(3, 4));
	printf("%d\n", op(3, 4));
	printf("%d\n", op(3, 4));
}


// ---------------------------------------------------------------------------
// 
// ---------------------------------------------------------------------------
