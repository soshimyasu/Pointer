/***********************************************************/
// 1부. 고급 포인터 분석 및 설계
/***********************************************************/

/***********************************************************/
// [1-1-1] 버퍼의 요소수 계산
/***********************************************************/

#if 0

#include <stdio.h>

void main(void)
{
	int a[10];

	int *start = &a[0];
	int *end = &a[9] + 1;
	int *p = &a[3];

	printf(" start[%x], end[%x], p[%x]\n", start, end, p);
	printf(" end-start=%d\n", end - start);
	printf(" end-1=%x\n", end - 1);

	printf("%d\n", sizeof(a) / sizeof(a[0]));

	// 주소 - 주소 = 주소간 데이터 갯수
	printf("%d\n", (end - start) / sizeof(int));// 2
	printf("%d\n", (end - start));				// 10
	printf("%d\n", (p - start) / sizeof(int));	// 0
	printf("%d\n", (p - start));				// 3
	printf("%d\n", (end - p) / sizeof(int));	// 1
	printf("%d\n", (end - p));					// 7
}

#endif

/***********************************************************/
// [1-1-2] 주소의 연산과 타입 승계
/***********************************************************/

#if 0

#include <stdio.h>

void main(void)
{
	int *p, *q;

	p = (int *)0x1008;
	q = (int *)0x1000;

	// 주소와 주소 간은 '-'만 가능하다
	//printf("%d\n", p * q); // x 주소 연산에서 '*' 는 지원하지 않음, *연산시 왼쪽/오른쪽 피연산자로 주소 사용 불가
	//printf("%d\n", p / q); // x 주소 연산에서 '/' 는 지원하지 않음, /연산시 왼쪽/오른쪽 피연산자로 주소 사용 불가
	//printf("%d\n", p + q); // x 주소 연산에서 '+' 는 지원하지 않음
	printf("%d\n", p - q);
	printf("%d\n", q - p);	// 가능!!

	//printf("0x%p\n", p * 2); // p는 주소, *연산시 왼쪽 피연산자로 주소 사용 불가
	//printf("0x%p\n", p / 2); // p는 주소, /연산시 왼쪽 피연산자로 주소 사용 불가 
	printf("0x%p\n", p + 2); // 0x1010
	printf("0x%p\n", p - 2); // 0x1000
}

#endif


/***********************************************************/
// [1-3-3] : 단일 포인터
/***********************************************************/

#if 0

#include <stdio.h>

void func(int *p)
{
	*p = 100;
	p++;
	printf("0x%p\n", p);
}

void main(void)
{
	int a[] = { 1,2,3,4 };
	int *p = a;

	func(p);
	printf("%d\n", *p);
	printf("0x%p, 0x%p\n", a, p);
}

#endif

#if 0

#include <stdio.h>

void Swap(int* p, int* q)
{
	int t;

	t = *q;
	*q = *p;
	*p = t;
}

void Swap2(int** p, int** q)
{
	int *t;

	t = *q;
	printf("Before  t=[%08p], p=[%08p], q=[%08p]\n", t, p, q);
	*q = *p;
	*p = t;

	printf("After  t=[%08p], p=[%08p], q=[%08p]\n", t, p, q);
}

void main(void)
{
	int a = 10, b = 20;
	
	printf("Before : %d[%08p] %d[%08p]\n", a, &a, b, &b);
	//Swap(&a, &b);
	Swap2(&(&a), &(&b));	// OK
	printf("After : %d[%08p] %d[%08p\n", a, &a, b, &b);
}

#endif


/* frpg */


/***********************************************************/
// [1-3-4] : 다중 포인터의 활용
/***********************************************************/

#if 0

#include <stdio.h>

int func(const int **p)
{
	int i;
	int sum = 0;

	printf("=========%d\n", (*p)[0]);

	for (i = 0; i < (*p)[0]; i++) {
		sum += (*p)[i+1];
	}
	//*p += (*p)[0] + 1;
	*p += i + 1;

	return sum;
}

void main(void)
{
	int i;
	int a[] = { 1, 10, 2, -5, -20, 3, 100, 200, 300, 4, -10, -20, -30, -40 };
	const int *p = a;

	for (i = 0; i < 4; i++)
	{
		printf("SUM=%d\n", func(&p));
	}
}

#endif

/***********************************************************/
// [1-1-5] 배열 parameter
/***********************************************************/

#if 0

#include <stdio.h>

int sum(int b[4])	// 이는 int *로 casting 된다.첫 요소의 주소가 전달된다.
{
	int i, sum = 0;
	
	// sizeof(b) = 4 (32bit)
	// sizeof(b[0]) = 4
	for (i = 0; i < (sizeof(b) / sizeof(b[0])); i++)
	{
		sum += b[i];
	}
	return sum;
}

void main(void)
{
	int a[4] = { 1,2,3,4 };

	// sizeof(a) = 16
	// sizeof(a[0]) = 4
	printf("%d\n", sum(a));	// int *가 func로 넘어간다.
}

#endif

#if 0

#include <stdio.h>

void func(int b[5])
{
	printf("0x%p\n", b);
	printf("0x%p\n", &b[0]);
	printf("%d\n", sizeof(b));
}

void main(void)
{
	int a[5] = { 10,20,30,40, 50 };

	printf("0x%p\n", a);
	printf("0x%p\n", &a[0]);
	printf("%d\n", sizeof(a));
	func(a);
}

#endif

/***********************************************************/
// [1-1-6] 배열 활용식을 이용한 배열 요소 액세스
/***********************************************************/

#if 0

#include <stdio.h>

int a[4] = { 1,2,3,4 };

void main(void)
{
	printf("%d\n", a[0]);
	printf("%d\n", a[3]);
	printf("%d\n", a[4]);
	printf("%d\n", a[-1]);

	printf("%d\n", (a + 1)[2]);
	printf("%d\n", a[3]);

	printf("%d\n", a[2]);
	printf("%d\n", *(a + 2));
	printf("%d\n", *(2 + a));
	printf("%d\n", 2[a]); // 에러 안뜬다. []은 사용자가 쉽게 인식하기 위한 기호일 뿐이다.
						// 컴파일러는 단순히 *주소 연산이다. 2[a] = *(2+a) = *(a+2)
}

#endif

/**********************************************************/
// [1-2-1] : 배열의 요소 타입
/**********************************************************/

#if 0

#include <stdio.h>

void main(void)
{
	int *a;  

	int *b1[4];
	int **b2[4];
	int b3[4];

	b1[0] = a;
	b2[0] = &a;
	b3[0] = *a;
}

#endif

#if 0

#include <stdio.h>

void main(void)
{
	int(*p)[4];

	// 변수 선언

	//	b1[4]
	//	b2[4]
	//	b3[4]
	int (*b1[4])[4];
	int(**b2[4])[4];	// int(**)[4] b2[4] => int(**b2[4])[4]
	int	b3[4];

	b1[0] = p;	// p type : int (*)[4]
	b2[0] = &p; // &p type : int(**)[4]
	b3[0] = (*p)[1]; // p type : int
}

#endif

#if 0

#include <stdio.h>

void main(void)
{
	int a[3];

	// 변수 선언

	//	b1[4]
	//	b2[4]
	//	b3[4]
	int *b1[3];
	int(*b2[4])[3];
	int	b3[4];

	b1[0] = a;	// type  배열: int[3], 주소:int *
	b2[0] = &a;	// type : int(*)[3]
	b3[0] = a[1];// type int
}

#endif

#if 0

#include <stdio.h>

void main(void)
{
	int *a[3];

	// 변수 선언

	int	**b1[4];
	int *(*b2[4])[3];
	int *b3[4];

	b1[0] = a;	// type 배열: int *[3], 주소 : int**
	b2[0] = &a; // type : int *(*)[3]
	b3[0] = a[1]; // type : int *
}

#endif

/**********************************************************/
// [1-2-2] : 함수의 리턴 타입
/**********************************************************/

#if 0

#include <stdio.h>

int *a;

int *f1(void)
{
	return a; // type : int *
}

int **f2(void)
{
	return &a; // type : int *(*) => int **
}

int f3(void)
{
	return *a;	// int *a => *a삭제 ==> int
}

void main(void)
{
	f1();
	f2();
	f3();
}

#endif

#if 0

#include <stdio.h>

int(*p)[4];

int (*f1(void))[4]
{
	return p;	// int (*)[4]
}

int (**f2(void))[4]
{
	return &p;	// int (*p)[4] => p 없애고 (*) ==> int (*(*))[4] = int (**)[4]
}

int f3(void)
{
	return (*p)[1];	// int (p)[4] =>  int
}

void main(void)
{
	f1();
	f2();
	f3();
}

#endif

#if 0

#include <stdio.h>

int(*p)(int);

int (*f1(void))(int)
{
	return p;// int (*)(int)
}

int (**f2(void))(int)
{
	return &p;// int (*p)(int) => p없애고 (*) ==> int (*(*))(int) = int (**)(int)
}

int f3(void)
{
	return (*p)(3);// int (*)(int)
}

void main(void)
{
	f1();	
	f2();	
	f3();
}

#endif

/***********************************************************/
// [1-3-1] : 문자열과 %s 옵션 이해
/***********************************************************/

#if 0

#include <stdio.h> 

void main(void)
{
	char a[] = "LEW";
	char *p = "%s\n";

	printf("%s\n", "LEW");
	printf("%s\n", a);
	printf("%s\n", *a);	// *a 값을 문자열의 시작 주소로 인식하고, 오류가 발생함!! , 안할수도 있음( 머신에 따라 다름 )
	printf(p, a);
}

#endif

/**********************************************************/
// [1-3-2] : 무엇이 인쇄될까요?
/**********************************************************/

#if 0

#include <stdio.h>

void main(void)
{
	char a[4] = "LEW";
	char *p = a;

	printf("%p:%p \n", p, &p);
	printf("%p:%p \n", a, &a);			// 상수화된 주소, 변경 불가
	printf("%p:%p \n", main, &main);	// 상수화된 주소, 변경 불가
	printf("%p:%p \n", "LEW", &"LEW");	// 상수화된 주소, 변경 불가
}

#endif

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

/**********************************************************/
// [1-3-10] : 배열 포인터 연습
/**********************************************************/

#if 0

#include <stdio.h> 

void func(int (*p)[4])
{
	// main의 a[2]를 50으로

	(*p)[2] = 50;
}

void main(void)
{
	int a[4] = { 10,20,30,40 };

	printf("%d\n", a[2]);
	func(&a);
	printf("%d\n", a[2]);
}

#endif

/***********************************************************/
// [1-3-11] : 구조체는 기본형이다
/***********************************************************/

#if 0

#include <stdio.h>

void main(void)
{
	int a, b = 10;

	a = b;
	printf("a=%d, b=%d\n", a, b);
}

#endif

#if 0

#include <stdio.h>

void main(void)
{
	struct st
	{
		int a;
		char b;
	} y = { 100, 'A' };

	struct st x = y;

	printf("x.a=%d, x.b=%c\n", x.a, x.b);
	printf("y.a=%d, y.b=%c\n", y.a, y.b);
}

#endif

/**********************************************************/
// [1-3-12] : 구조체의 함수 전달
/**********************************************************/

#if 0 

#include <stdio.h> 

struct math
{
	int id;
	char name[20];
	int score;
}mid, final = { 1, "Kim", 50 };

void main(void)
{
	mid = final;

	printf("%d\n", mid.id);
	printf("%s\n", mid.name);
	printf("%d\n", mid.score);
}

#endif

#if 0

#include <stdio.h>

struct math
{
	int id;
	char name[20];
	int score;
};

void cheat(struct math test);

void main(void)
{
	struct math final = { 1, "Kim", 50 };
	cheat(final);
	printf("%d\n", final.score);
}

void cheat(struct math test)
{
	test.score = 100;
}

#endif

/**********************************************************/
// [1-3-13] : 구조체 주소의 함수 전달
/**********************************************************/

#if 0

#include <stdio.h> 

struct math
{
	int id;
	char name[20];
	int score;
};

void cheat(struct math * test);

void main(void)
{
	struct math final = { 1, "Kim", 50 };
	cheat(&final);
	printf("%d\n", final.score);
}

void cheat(struct math * test)
{
	test->score = 100;
}

#endif

/***********************************************************/
// [1-4-1] : 2차원 배열의 활용식
/***********************************************************/

#if 0

#include <stdio.h>

int a[3][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12} };

void main(void)
{
	printf("%d\n", a[2][3]);
	printf("%d\n", *(*(a + 2) + 3));
	printf("%d\n", (a + 1)[1][3]);
	printf("%d\n", ((a + 1)[1] + 2)[1]);
	printf("%d\n", 3[a[2]]);
	printf("%d\n", 3[2[a]]);
}

#endif

/**********************************************************/
// [1-4-2] : 2차원 배열의 이해 연습
/**********************************************************/

#if 0

#include <stdio.h>

char a[3][4] = { "kim","lew","seo" };

void main(void)
{
	printf("%s\n", a);
	printf("%s\n", *a);
	printf("%s\n", a[0]);
	printf("%c\n", *a[0]);
	printf("%s\n", a[1]);
	printf("%c\n", *a[1]);
	printf("%s\n", a[2]);
	printf("%c\n", *a[2]);
}

#endif

/**********************************************************/
// [1-4-3] : 2차원배열의 전달
/**********************************************************/

#if 0

#include <stdio.h>

void draw_pixel(int y, int x, int value, int (*p)[3])
{
	p[y][x] = value;
}

void main(void)
{
	int a[2][3] = { 1,2,3,4,5,6 };

	printf("%d\n", a[1][2]);
	draw_pixel(1, 2, 10, a);
	printf("%d\n", a[1][2]);
}

#endif

/**********************************************************/
// [1-4-4] : 2차원배열의 리턴
/**********************************************************/

#if 0

#include <stdio.h>

int(*func(void))[4]
{
	static int a[3][4] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	return a;	// a = &a[0] => int (*)[4]
}

void main(void)
{
	printf("%d\n", func()[1][2] );
}

#endif

/**********************************************************/
// [1-4-5] : 배열 등가포인터 연습
/**********************************************************/

#if 0

#include <stdio.h>

void main(void)
{
	int a[2][3][4];
	int(*b[3])[4];
	int *(*c[2])(int *);
	int *d[3][4];
	int(*(*e[5])(void))[4];

	// pa ~ pe 포인터 변수 선언
	// 아래에 pa ~ pe 까지 포인터를 선언한다
	// 컴파일시 단 하나의 경고도 발생하지 않아야 한다

	int(*pa)[3][4];
	int(**pb)[4];
	int *(**pc)(int *);
	int *(*pd)[4];
	int(*(**pe)(void))[4];

	pa = a;
	pb = b;
	pc = c;
	pd = d;
	pe = e;
}

#endif

/**********************************************************/
// [1-4-6] : 등가포인터의 활용
/**********************************************************/

#if 0

#include <stdio.h>

void main(void)
{
	char arr[5][10] = { "Kim", "Lew", "Kang", "Song", "Park" };
	char(*p)[10];

	p = arr;

	printf("%s\n", *p);
	printf("%s\n", *(p + 1));
	printf("%c\n", *(*(p + 2) + 1));

	printf("%s\n", p[0]);
	printf("%s\n", p[1]);
	printf("%c\n", p[2][1]);
}

#endif

/**********************************************************/
// [1-4-7] : 등가 포인터로 바라보는 메모리
/**********************************************************/

#if 0

#include <stdio.h>

void main(void)
{
	int a[12] = { 10, 20, 30, 40, 50, 60, 70, 80, 11, 22, 33, 44 };

	int *p = a;
	char *q = (char *)a;
	int(*r)[4] = (int(*)[4])a;
	int(*s)[3] = (int(*)[3])a;
	int(*t)[2][3] = (int(*)[2][3])a;

	printf("%d, %d\n", p[0], p[1]);
	printf("%d, %d\n", q[0], q[1]);
	printf("%p, %p\n", r[0], r[1]);
	printf("%p, %p\n", s[0], s[1]);
	printf("%p, %p\n", t[0], t[1]);
}

#endif

/**********************************************************/
// [1-4-8] : 배열의 액세스
/**********************************************************/

#if 0

#include <stdio.h>

int a[3][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12} };
int *b[3] = { a[2], a[1], a[0] };

void main(void)
{
	printf("%d\n", a[2][3]);

	//b를 이용하여 배열내의 숫자 12을 인쇄하시오
	printf("%d\n", b[0][3]);
}

#endif

/**********************************************************/
// [1-4-9] : 환산법의 적용
/**********************************************************/

#if 0

#include <stdio.h>

int a[3][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12} };
int *p = a[0];

void main(void)
{
	printf("%d\n", a[2][3]);

	//p 변수만 이용하여 배열내의 숫자 12을 인쇄하시오
	printf("%d\n", p[11]); // a[2][3] == a[0][11] = p[11]
}

#endif

/***********************************************************/
// [1-4-10] : 함수 parameter의 직관적 설계
/***********************************************************/

#if 0

#include <stdio.h>

int a[2][3][4] = { {{1,2,3,4},{5,6,7,8},{9,10,11,12}},{{10,20,30,40},{50,60,70,80},{90,100,110,120}} };	// int [2][3][4]

void f1(int *p)
{
	// p == a[0][1]
	printf("%d\n", p[17]);	// a[1][2][1] == a[0][1][1+12+4] == a[0][1][17]
}
void main(void)
{
	f1(*(a[0] + 1));	// *(a[0] + 1) = a[0][1]         type : int *
}

#endif

#if 0

#include <stdio.h>

int a[2][3][4] = { {{1,2,3,4},{5,6,7,8},{9,10,11,12}},{{10,20,30,40},{50,60,70,80},{90,100,110,120}} };	// int [2][3][4]

void f2(int(*p)[4])
{
	// p = a[2]
	printf("%d\n", p[-1]);	// a[1][2][1] == a[2][2][-11] == p[2][-11]
							// a[1][2][1] == a[2][-1][1] == p[-1][1]
}

void main(void)
{
	f2(*(a + 2));	// *(a+2) == a[2],       type : int (*)[4]
}

#endif


#if 0
void f2()
{
	printf("%d\n", );
}

void f3()
{
	printf("%d\n", );
}

void f4()
{
	printf("%d\n", );
}

void f5()
{
	printf("%d\n", );
}

void f6()
{
	printf("%d\n", );
}

#include <stdio.h>

int a[2][3][4] = { {{1,2,3,4},{5,6,7,8},{9,10,11,12}},{{10,20,30,40},{50,60,70,80},{90,100,110,120}} };	// int [2][3][4]

void f1(int *p)
{
	// p == a[0][1]
	printf("%d\n", p[17]);	// a[1][2][1] == a[0][1][1+12+4] == a[0][1][17]
}

void main(void)
{
	f1(*(a[0] + 1));	// *(a[0] + 1) = a[0][1]         type : int *
	f2(*(a + 2));		// 
	f3(a);
	f4(a + 3);
	f5(&a);
	f6(&a - 1);
}

#endif

/***********************************************************/
// [1-4-11] : 함수 리턴의 직관적 설계
/***********************************************************/

#if 0

#include <stdio.h>

int a[2][3] = { {1,2,3},{4,5,6} };
int b[2][3] = { {10,20,30},{40,50,60} };
int(*c[2])[3] = { b, a };
int(**p)[3] = c;

f1(void)
{
	return c[1];
}

f2(void)
{
	return c + 1;
}

f3(void)
{
	return a[0] - 1;
}

f4(void)
{
	return p;
}

f5(void)
{
	return &c;
}

void main(void)
{
	printf("6=%d\n", f1());
	printf("6=%d\n", f2());
	printf("6=%d\n", f3());
	printf("6=%d\n", f4());
	printf("6=%d\n", f5());
}

#endif

/**********************************************************/
// [1-4-12] : 코드의 직관적 해석
/**********************************************************/

#if 0 

#include <stdio.h>

char *c[] = { "ENTER", "NEW", "POINT", "FIRST" };
char **cp[] = { c + 3, c + 2, c + 1, c };
char ***cpp = cp;

void main(void)
{
	printf("%s", **++cpp);
	printf("%s ", *--*++cpp + 3);
	printf("%s", *cpp[-2] + 3);
	printf("%s\n", cpp[-1][-1] + 1);
}

#endif

/***********************************************************/
// [1-5-1] : 함수 등가포인터의 실행
/***********************************************************/

#if 0

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

#endif

/***********************************************************/
// [1-5-2] : 함수를 함수에 전달하자
/***********************************************************/

#if 0

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

#endif

/***********************************************************/
// [1-5-3] : Parameter 미지정형
/***********************************************************/

#if 0

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

#endif

/***********************************************************/
// [1-5-4] : 조건에 따른 함수 호출 엔진
/***********************************************************/

#if 0

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
	return rand() % 3;
}

int op(int a, int b)
{
	switch (get_key())
	{
	case 0: return add(a, b);
	case 1: return sub(a, b);
	case 2: return mul(a, b);
	}
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

#endif

/***********************************************************/
// [1-5-5] : 함수 Lookup table
/***********************************************************/

#if 0

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


#endif

/***********************************************************/
// [1-5-6] : 함수를 받고 함수를 리턴하는 함수
/***********************************************************/

#if 0

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

int(*(op(int(*fp)(void))))(int, int)
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

#endif

/***********************************************************/
// [1-5-7] : qsort 함수를 이용한 배열 정렬
/***********************************************************/

#if 0

#include <stdio.h> 
#include <stdlib.h>

struct _st
{
	int num;
	char *name;
};

struct _st book[10] = { {7, "Kim"},	 {2, "Lew"}, 	 {10, "Kang"},
						{3, "Lee"},	 {6, "Seo"},	 {1, "Song"},
						{5, "Ki"},	 {8, "Moon"}, 	 {9, "Park"},
						{4, "Jung"} };

int compare_num_up(const void * a1, const void * a2)
{
	register const struct _st * p = a1, *q = a2;

	if (p->num > q->num) return 1;
	if (p->num < q->num) return -1;
	return 0;
}

void main(void)
{
	int i; struct _st tmp; struct _st *p;

	for (i = 0; i < 10; i++) printf("%d:%s\n", book[i].num, book[i].name);
	printf("\n");
	qsort(book, sizeof(book) / sizeof(book[0]), sizeof(struct _st), compare_num_up);
	for (i = 0; i < 10; i++) printf("%d:%s\n", book[i].num, book[i].name);

	tmp.num = 8;
	p = bsearch(&tmp, book, 10, sizeof(struct _st), compare_num_up);
	if (p)	printf("\nSearch Result => %d : %s\n", p->num, p->name);
	else	printf("\nSearch Failed\n");
}

#endif

#if 0

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

#endif

/***********************************************************/
// [1-5-8] : typedef을 이용한 가독성의 증대
/***********************************************************/

#if 0

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

#endif

/***********************************************************/
// [1-5-9] : 직관적 코드 설계 예제 1
/***********************************************************/

// 직접 선언

#if 0

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

#endif

// typedef 사용

#if 0

#include <stdio.h> 

//typedef FP2
// F2 타입 : int (*)[4]
typedef int (*FP2)[4];

//typedef FP1
// FP1 타입 : int (*(*))[4]
// typedef int (*FP2)[4] FP1;
typedef FP2(*FP1)(void);

FP2 f2(void)
{
	static int a[3][4] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	return a;//int (*)[4]
}

FP1 f1(void)
{
	return f2;//FP2 (*)(void)
}

void main(void)
{
	printf("%d\n", f1());
}

#endif

/***********************************************************/
// [1-5-10] : 직관적 코드 설계 예제 2
/***********************************************************/

#if 0

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

#endif

/***********************************************************/
// [1-5-11] : 직관적 코드 설계 예제 3
/***********************************************************/

#if 0 

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

#endif

/***********************************************************/
// [1-5-12] : 직관적 코드 설계 예제 4
/***********************************************************/

#if 0

#include <stdio.h> 

struct _st
{
	int num;
	char * name;
};

// f2(void)                     // [1]
struct _st(*f2(void))[3]
{
	static struct _st a[2][3] = { {{1,"KIM"}, {2,"SONG"}, {3, "KI"}}, {{4, "KANG"}, {5, "PARK"}, {6, "LEW"}} };
	return a;	// struct _st (*)[4]
}

//f1(int num)                   // [2]
struct _st *f1(int num)
{
	return f2()[num];
	// f2() == a[num]
	// a[num] type : struct _st *
}

void main(void)
{
	//printf("%s\n", f1(0));   // [3]
	printf("%s\n", f1(0)[4].name +1);
	
	// ARK ==> a[0][1].name[1]
	// f1(num) == a[num]
	// a[0][1].name[1] == f1(0)[1].name[1]
}

#endif

/***********************************************************/
// [1-5-13] : 직관적 코드 설계 예제 5
/***********************************************************/

#if 0

#include <stdio.h>

int *f1(void)
{
	static int a[4] = { 1,2,3,4 };
	return a;	// int *
}

int *f2(void)
{
	static int a[4] = { 10,20,30,40 };
	return a;	// int *
}

int *(*fa[2])() = { f1, f2 };

int f4(void)
{
	return 1;
}

//func1(void)     // [1]
int(*func1(void))(void)
{
	return fa;	// int (*)(void)
}

func2(p)   // [2]
{
	return func1()[p()];	
}

void main(void)
{
	printf("%d\n", func2(f4));   // [3]
}

#endif

/***********************************************************/
// [1-6-1] : 동적 배열
/***********************************************************/

#if 0

#include <stdio.h>
#include <stdlib.h>

void main(void)
{
	int i, j, x;
	int **p;

	x = 3;

	p = malloc(x * sizeof(int *));

	for (i = 0; i < x; i++)
	{
		p[i] = malloc(4 * sizeof(int));
	}

	for (i = 0; i < x; i++)
	{
		for (j = 0; j < 4; j++)
		{
			p[i][j] = i * 4 + j;
		}
	}

	for (i = 0; i < x; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf("%d\n", p[i][j]);
		}
	}

	for (i = 0; i < x; i++)
	{
		free(p[i]);
	}

	free(p);
}

#endif

/***********************************************************/
// [1-6-2] : 선형 메모리로 할당한 동적 배열
/***********************************************************/

#if 0

#include <stdio.h>
#include <stdlib.h>

void main(void)
{
	int i, j, x;
	int **p;

	x = 3;

	p = malloc(x * sizeof(int *));
	p[0] = malloc(x * 4 * sizeof(int));

	for (i = 1; i < x; i++)
	{
		p[i] = p[0] + i * 4;
	}

	for (i = 0; i < x; i++)
	{
		for (j = 0; j < 4; j++)
		{
			p[i][j] = i * 4 + j;
		}
	}

	for (i = 0; i < x; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf("%d\n", p[i][j]);
		}
	}

	free(p[0]);
	free(p);
}

#endif

/***********************************************************/
// [1-6-3] : 등가포인터를 이용한 동적 배열
/***********************************************************/

#if 0

#include <stdio.h>
#include <stdlib.h>

void main(void)
{
	int i, j, x;
	int(*p)[4];

	x = 3;

	p = malloc(x * sizeof(int[4]));

	for (i = 0; i < x; i++)
	{
		for (j = 0; j < 4; j++)
		{
			p[i][j] = i * 4 + j;
		}
	}

	for (i = 0; i < x; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf("%d\n", p[i][j]);
		}
	}

	free(p);
}

#endif

/***********************************************************/
// [1-6-4] : 모든 요소수가 가변인 배열
/***********************************************************/

#if 0

#include <stdio.h>
#include <stdlib.h>

void main(void)
{
	int i, j, m, n;
	int **p;

	m = 3, n = 4;

	p = malloc(m * sizeof(int *));
	p[0] = malloc(m * n * sizeof(int));

	for (i = 1; i < m; i++)
	{
		p[i] = p[0] + i * n;
	}

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			p[i][j] = i * n + j;
		}
	}

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%d\n", p[i][j]);
		}
	}

	free(p[0]);
	free(p);
}

#endif

/***********************************************************/
// [1-6-5] : 1차원 배열로 에뮬레이션
/***********************************************************/

#if 0

#include <stdio.h>
#include <stdlib.h>

void main(void)
{
	int i, j;
	int m = 3, n = 4;
	int *p;

	p = malloc(m * n * sizeof(int));

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			p[i*n + j] = i * n + j;
		}
	}

	for (i = 0; i < (m*n); i++)
	{
		printf("%d\n", p[i]);
	}

	free(p);
}

#endif

/***********************************************************/
// [1-7-1] : Type casting 연습 1
/***********************************************************/

#if 0

#include <stdio.h>

void func(int x)
{
	printf("%f\n", ((double *)x)[0]);
	printf("%f\n", ((double *)x)[1]);
	printf("%f\n", ((double *)x)[2]);
}

void main(void)
{
	double d[3] = { 3.14, 5.125, -7.42 };

	func((int)d);
}

#endif

#if 0

#include <stdio.h>

void func(int x)
{
	int i;

	for (i = 0; i < 3; i++)
	{
		printf("%f\n", ((double *)x)[i]);
	}
}

void main(void)
{
	double d[3] = { 3.14, 5.125, -7.42 };

	func((int)d);
}

#endif

/***********************************************************/
// [1-7-2] : Type casting 연습 2
/***********************************************************/

#if 0

#include <stdio.h>

void func(void * p)
{
	int i;

	for (i = 0; i < 3; i++)
	{
		printf("%f\n", (*(double **)p)[i]); // d == (*(double **)p)
	}
}

void main(void)
{
	double d[3] = { 3.14, 5.125, -7.42 };
	void *p = d;

	func(&p);	// double *
}

#endif

/***********************************************************/
// [1-7-3] :  Type casting 연습 3
/***********************************************************/

#if 0

#include <stdio.h>

void func(void *p)
{
	printf("%s\n", *((char **)p));
}

void main(void)
{
	char * p = "Willtek";
	func(&p);
}

#endif

/***********************************************************/
// [1-7-4] : Type casting 연습 4
/***********************************************************/

#if 0

#include <stdio.h>

struct st
{
	int i;
	char c;
};

void func(long long int a)
{
	printf("%d\n", ((struct st *)&a)->i);
	printf("%c\n", ((struct st *)&a)->c);
}

void main(void)
{
	struct st x = { 100, 'A' };

	func(*(long long int *)&x);
}

#endif

/***********************************************************/
// [1-7-5] : int 변수로 함수 실행하기
/***********************************************************/

#if 0

#include <stdio.h>

int func(int a, int b)
{
	return a + b;
}

void main(void)
{
	int a = (int)func;

	printf("%d\n", func(3, 4));
	printf("%d\n", ((int (*)(int,int))a)(3,4));
}

#endif

/***********************************************************/
// [1-7-6] : Type casting 연습 5
/***********************************************************/

#if 0

#include <stdio.h>

// typedef int (**FP)(int,int)
void func(void * p)
{
	printf("%d\n", (*(int (**)(int,int))p)(3,4) );
	//printf("%d\n", (*(FP)p)(3,4));
}

int add(int a, int b)
{
	return a + b;
}

void main(void)
{
	void *p = (void *)add;

	func(&p);
}

#endif

/***********************************************************/
// [1-7-7] : printf의 argument 전달 
/***********************************************************/

#if 0

#include <stdio.h>

int add(int a, int b)
{
	return a + b;
}

void main(void)
{
	printf("%d\n", add(3));
	printf("%d\n", add(3, 4, 5));
}

#endif

#if 0

#include <stdio.h>

void main(void)
{
	int a = 1, b = 2, c = 3;

	printf("남는 Argument : %d %d \n", a, b, c);
	printf("적은 Argument : %d %d %d\n", a, b);
}

#endif

/***********************************************************/
// [1-7-8] : 가변의 인수전달
/***********************************************************/

#if 0

#include <stdio.h>

int my_add(int cnt, ...)
{
	int i, sum = 0;

	for (i = 1; i <= cnt; i++)
	{
		sum += *(&cnt + i);

	}
	return sum;
}

void main(void)
{
	printf("%d\n", my_add(3, 7, 5, 4));
	printf("%d\n", my_add(5, 1, 2, 6, 9, 10));
}

#endif

/***********************************************************/
// [1-7-9] : 가변인자의 access
/***********************************************************/

#if 0

#include <stdio.h>

void my_ellipsis(int a, ...)
{
	printf("%d\n", a);
	printf("%u\n", );
	printf("%c\n", );
	printf("%f\n", );
	printf("%f\n", );
}

void main(void)
{
	int a = 10;
	unsigned char b = 100;
	unsigned char c = 'A';
	float d = 3.14f;
	double e = 5.125;

	my_ellipsis(a, b, c, d, e);
}

#endif

/***********************************************************/
// [1-7-10] : 재도전 - 실수의 인쇄
/***********************************************************/

#if 0 

#include <stdio.h>

void main(void)
{
	float f = 3.5f;

	printf("%#x\n", f);
}

#endif

#if 0 

#include <stdio.h>

void main(void)
{
	float f = 3.1f;

	printf("%#x\n", f);
}

#endif

/***********************************************************/
// [1-7-11] : 실수의 메모리 내용 dump
/***********************************************************/

#if 0

#include <stdio.h>

void main(void)
{
	float a = 3.5f;
	double b = 3.5;

	printf("float : %#.8x\n", *(int *)&a);

	printf("double: %#.8x : %.8x\n\n", *(((int *)&b) + 1), *(int *)&b );
}

#endif


/***********************************************************/
// [1-7-12] : 간이 format 지시자의 이용
/***********************************************************/

#if 0

#include <stdio.h>

void my_printf(char * fmt, ...)
{
	int *ap = (int *)&fmt + 1;

	while (*fmt)
	{
		switch (*fmt++)
		{
		case 'u': printf("%u\n", ); break;
		case 'd': printf("%d\n", ); break;
		case 'c': printf("%c\n", ); break;
		case 'f': printf("%f\n", ); break;
		case 's': printf("%s\n", ); break;
		}
	}
}

void main(void)
{
	int a = 10;
	unsigned char b = 100;
	unsigned char b2 = 'A';
	float c = 3.14f;
	double d = 5.125;

	my_printf("ducffsd", a, b, b2, c, d, "Keyseek", 100);
	my_printf("fdsc", -10.75, 100, "Willtek", 'B');
}

#endif

/***********************************************************/
// [1-7-13] : 가변인자 전달용 macro의 활용
/***********************************************************/

#if 0

#include <stdio.h>
#include <stdarg.h>

void my_printf(char * fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	while (*fmt)
	{
		switch (*fmt++)
		{
		case 'u': printf("%X\n", va_arg(ap, unsigned int)); break;
		case 'd': printf("%d\n", va_arg(ap, int)); break;
		case 'c': printf("%c\n", va_arg(ap, char)); break;
		case 'f': printf("%f\n", va_arg(ap, double)); break;
		case 's': printf("%s\n", va_arg(ap, char *)); break;
		}
	}

	va_end(ap);
}

void main(void)
{
	int a = 10; unsigned char b = 100; unsigned char b2 = 'A';
	float c = 3.14f; double d = 5.125;

	my_printf("ducffsd", a, b, b2, c, d, "Keyseek", 100);
	my_printf("fdsc", -10.75, 100, "Willtek", 'B');
}

#endif

/***********************************************************/
// [1-7-14] : my_add 함수의 재설계
/***********************************************************/

#if 0

#include <stdio.h>
#include <stdarg.h>

int my_add(int cnt, ...)
{
	int i, sum = 0;

	va_list ap;
	va_start(ap, cnt);

	for (i = 1; i <= cnt; i++)
	{
		sum += va_arg(ap, int);
	}

	va_end(ap);
	return sum;
}

void main(void)
{
	printf("%d\n", my_add(3, 7, 5, 4));
	printf("%d\n", my_add(5, 1, 2, 6, 9, 10));
}

#endif

/***********************************************************/
// [1-7-15] : 진짜 printf 처럼 동작하는 함수
/***********************************************************/

#if 0

#include <stdio.h>
#include <stdarg.h>

int my_printf(char * fmt, ...)
{
	int n;
	va_list ap;
	char string[256];

	va_start(ap, fmt);
	n = vsprintf(string, fmt, ap);
	printf(string);
	va_end(ap);
	return n;
}

void main(void)
{
	int a = 10;
	unsigned char b = 100;

	unsigned char b2 = 'A';
	float c = 3.14f;
	double d = 5.125;

	my_printf("ANSWER = %d %u %c %1.2f %1.3f %s %d\n", a, b, b2, c, d, "Keyseek", 100);
}

#endif

/***********************************************************/
// [1-7-16] : Data Parsing 연습 1
/***********************************************************/

#if 0

#include <stdio.h>

struct _st
{
	int i;
	char c;
};

void my_test(char c, ...)
{
	printf("%c\n", c);
	printf("%d\n", );
	printf("%c\n", );
	printf("%s\n", );
	printf("%f\n", );
	printf("%f\n", );
	printf("%f\n", );
	printf("%d\n", );
}

int add(int a, int b)
{
	return a + b;
}

void main(void)
{
	char a = 'A';
	struct _st x = { 100, 'B' };
	double d[3] = { 3.14, 5.19, -7.42 };

	my_test(a, x, "Song", d, add);
}

#endif

/***********************************************************/
// [1-7-17] : Data Parsing 연습 2
/***********************************************************/

#if 0

#include <stdio.h>

void my_test(int a, ...)
{
	// [1] 넘어온 3.14 인쇄
	printf("f => %.2f\n", );
	// [2] 넘어온 배열을 이용하여 f1 함수를 간접호출하여 문자열 BIN 출력
	printf("%s", );
	// [3] 넘어온 배열을 이용하여 f2 함수를 간접호출하여 문자열 GO 출력
	printf("%s\n", );
}

char * f1(void)
{
	return "CABIN";
}

char * f2(void)
{
	return "LOGO";
}

void main(void)
{
	double d = 3.14;
	char * (*fa[2])() = { f1, f2 };

	my_test(1, &d, fa);
}

#endif

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
		printf("0x%x, 0x%x, 0x%x\n", (info+1)->x, (info + 1)->y, (info + 1)->length);
	}
}

#endif

/***********************************************************/
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
		printf("0x%x, 0x%x, 0x%x\n", info[i].x, info[i].y, info[i].length);
	}
}

#endif

/***********************************************************/
// [1-8-7] : 구조체 활용의 문제점
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
	unsigned int length;
};

void main(void)
{
	printf("0x%x, 0x%x, 0x%x\n", info[0].x, info[0].y, info[0].length);
	printf("0x%x, 0x%x, 0x%x\n", info[1].x, info[1].y, info[1].length);
}

#endif

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
	printf("%d, %p\n", sizeof(s1), &s1.a);
	printf("%d, %p, %p, %p, %p\n", sizeof(s2), &s2.a, &s2.b, &s2.c, &s2.d);
	printf("%d, %p, %p, %p, %p\n", sizeof(s3), &s3.a, &s3.b, &s3.c[0], &s3.c[1]);
}

#endif

/***********************************************************/
// [1-8-9] : pack을 사용한 구조체 멤버 alignment 규정
/***********************************************************/

#if 0

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

/***********************************************************/
// [1-8-10] : pack 옵션의 이전 상태 복원
/***********************************************************/

#if 0

#include <stdio.h>

#pragma pack(show)
#pragma pack(1)

struct _s1
{
	short a;
}s1 = { 0x1234 };

#pragma pack(push, 4)

struct _s2
{
	short a;
	int b;
	char c;
	double d;
}s2 = { 0x1234, 0x56789abc, 0xfe, 3.14 };

#pragma pack(pop)
#pragma pack(show)

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
// [1-8-11] : pack으로 원하는 구조체 만들기
/***********************************************************/

#if 0

#include <stdio.h>

//#define  info	 ((struct st *)0x100)

unsigned char buf[] = { 0x4d,0x4d,0x55,0x5f,0x45,0x6e,0x61,0x62,0x6c,0x65,0x44,0x43,0x61,0x63,0x68,0x65 };

#define  info	 ((struct st *)buf)

#pragma pack( push, 1)

struct st
{
	unsigned char x;
	unsigned char y;
	unsigned int length;
};

#pragma pack(pop)

void main(void)
{
	printf("0x%x, 0x%x, 0x%x\n", info[0].x, info[0].y, info[0].length);
	printf("0x%x, 0x%x, 0x%x\n", info[1].x, info[1].y, info[1].length);
}

#endif

/***********************************************************/
// [1-9-1] : 비트필드 구조체의 특징
/***********************************************************/

#if 0

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

#if 0

#include <stdio.h>

unsigned char buf[] = { 0x52,0x7a };

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
// [1-9-4] : 비트필드 구조체의 컨테이너
/***********************************************************/

#if 0

#include <stdio.h>

unsigned char buf[] = { 0x52,0x7a };

struct fat_time1
{
	unsigned int sec : 5;
	unsigned int min : 6;
	unsigned int hour : 5;
};

struct fat_time2
{
	unsigned char sec : 5;
	unsigned char min : 6;
	unsigned char hour : 5;
};

void main(void)
{
	struct fat_time1 * time1 = (struct fat_time *)buf;
	struct fat_time2 * time2 = (struct fat_time *)buf;

	printf("Time=%d:%d:%d\n", time1->hour, time1->min, time1->sec * 2);
	printf("Sizeof Time=%d\n", sizeof(struct fat_time1));
	printf("Time=%d:%d:%d\n", time2->hour, time2->min, time2->sec * 2);
	printf("Sizeof Time=%d\n", sizeof(struct fat_time2));
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
