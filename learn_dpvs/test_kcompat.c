#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/types.h>

#define swap(a, b) \
	    do { typeof(a) __tmp = (a); (a) = (b); (b) = __tmp; } while (0)


// taken from definition in include/asm-generic/bitops/builtin-__ffs.h
inline unsigned long __ffs(unsigned long word)
{
    return __builtin_ctzl(word);
}

// taken from definition in include/asm-generic/bitops/builtin-fls.h
int fls(unsigned int x)
{
    return x ? sizeof(x) * 8 - __builtin_clz(x) : 0;
}

/**
 * taken from definition in lib/math/gcd.c
 *
 * gcd - calculate and return the greatest common divisor of 2 unsigned longs
 * @a: first value
 * @b: second value
 */
unsigned long gcd(unsigned long a, unsigned long b)
{
    unsigned long r = a | b;

    if (!a || !b)
        return r;

    b >>= __ffs(b);
    if (b == 1)
        return r & -r;

    for (;;) {
        a >>= __ffs(a);
        if (a == 1)
            return r & -r;
        if (a == b)
            return a << __ffs(r);

        if (a < b)
            swap(a, b);
        a -= b;
    }
}

int main(int argc, char *argv[])
{
	long x=0,y=0;
	
	if (argc > 1)
	x = atol(argv[1]);

	if (argc > 2)
	y = atol(argv[2]);

	printf("__ffs=%#lx\n", __ffs(x));
	printf("fls=%#x\n", fls(x));
	if (argc > 2)
		printf("gcd(%lu, %lu)=%lu\n", x, y, gcd(x,y));
	return 0;
}
