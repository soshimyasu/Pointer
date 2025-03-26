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
	static int r = 0;	// 최초 한번만 초기화
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
// 함수를 받고 함수를 리턴
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

int(*fa[3])(int, int) = { add, sub, mul };

// 1.
// paramter type : int (*)(void)
// 
// 2. 
// return type : int (*)(int, int)
// int (*op( int (*fp)(void)))(int, int)

// op( fp )
int( *(op(int(*fp)(void))) )(int, int)
{
	return fa[fp()];
}

void main(void)
{
	printf("%d\n", op(get_key)(3, 4));
	printf("%d\n", op(get_key)(3, 4));
	printf("%d\n", op(get_key)(3, 4));
	printf("%d\n", op(get_key)(3, 4));
	printf("%d\n", op(get_key)(3, 4));
	printf("%d\n", op(get_key)(3, 4));
	printf("%d\n", op(get_key)(3, 4));
}



// ---------------------------------------------------------------------------
// #define, typedef 차이점
// ---------------------------------------------------------------------------
#include <stdio.h>

#define dp double *
typedef double *DP;

void main(void)
{

	DP a, b;
	printf("%d %d\n", sizeof(a), sizeof(b));	// 4,4

	dp c, d;
	printf("%d %d\n", sizeof(c), sizeof(d));	// 4(double *),8(double0=)
}


// ---------------------------------------------------------------------------
// typedef를 이용한 가독성 증대
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

// typedef
// FPTR type : int (*)()
typedef int(*FPTR)();

FPTR fa[3] = { add, sub, mul };

FPTR op(FPTR fp)
{
	return fa[fp()];
}

void main(void)
{
	printf("%d\n", op(get_key)(3, 4));
	printf("%d\n", op(get_key)(3, 4));
	printf("%d\n", op(get_key)(3, 4));
	printf("%d\n", op(get_key)(3, 4));
	printf("%d\n", op(get_key)(3, 4));
	printf("%d\n", op(get_key)(3, 4));
	printf("%d\n", op(get_key)(3, 4));
}


// ---------------------------------------------------------------------------
// 직관적 코드 설계 1
// ---------------------------------------------------------------------------

#include <stdio.h> 

// f2(void)
// f2 리턴 타입 : int (*)[4]
// int (*)[4] f2(void)
// int (*f2(void))[4]
int (*f2(void))[4]
{
	static int a[3][4] = { 1,2,3,4,5,6,7,8,9,10,11,12 };

	return a;
}

//f1(void)
// f1 리턴타입 : int (*(*)(void))[4]
// int (*(*)(void))[4] 
// int (*(*)(void))[4] f1(void)
int(*(*f1(void))(void))[4]
{
	return f2;
}

void main(void)
{
	//printf("%d\n", f1()); // a[1][2]
	printf("%d\n", f1()()[1][2]); // a[1][2]
	// f1() == f2
	// f2() == f1()() ==> f2 == f1()
	// f1()() == a
}


// ---------------------------------------------------------------------------
// 직관적 코드 설계 1 ( typedef )
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// 직관적 코드 설계 2
// ---------------------------------------------------------------------------
#include <stdio.h> 

// f2 type = int (*)[4]
// int(*)[4] => int (*f2)[4]
//f2(void)
int (*f2(void))[4]
{
	static int a[3][4] = { 1,2,3,4,5,6,7,8,9,10,11,12 };

	return a; // int (*)[4]
}

// f1 type = int * 
int *f1(void)
{
	return f2()[2]; // f2() == int (*)[4], &a[0] = int (*)[4] == a ==> f2() == a
	// f2()[2] == a[2]
}

void main(void)
{
	//printf("%d\n", f1()); // f1() type : int *
	printf("%d\n", f1()[-2]);
	
	// f1() == f2()[2] == a[2]
	// a[1][2] == a[2][-2]
	// f1()[-2]
}


// ---------------------------------------------------------------------------
// 직관적 코드 설계 2 ( typedef )
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// 직관적 코드 설계 3
// ---------------------------------------------------------------------------
#include <stdio.h> 

//f2(void)
int(*f2(void))[3][4]
{
	static int a[3][4] = { 1,2,3,4,5,6,7,8,9,10,11,12 };

	return &a;	// type : int (*)[3][4]
}


//f1(void)
int (*f1(void))[4]
{
	return f2()[0]; // int(*f2(void))[3][4]
	// f2()[0] == (&a)[0] == *&a == a
	// a type : int (*)[4]
}

void main(void)
{
	//printf("%d\n", f1());
	printf("%d\n", f1()[1][2]);

	// f1() == f2()[0] == a
	// a[1][2] == f1()[1][2]
}


// ---------------------------------------------------------------------------
// 직관적 코드 설계 4
// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
// 직관적 코드 설계 5
// ---------------------------------------------------------------------------
