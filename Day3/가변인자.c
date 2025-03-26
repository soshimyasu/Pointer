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

#if 01

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
// [1-7-14] : my_add 함수의 재설계
/***********************************************************/

#if 01

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
