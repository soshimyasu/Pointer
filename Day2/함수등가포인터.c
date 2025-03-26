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


