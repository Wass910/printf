#include <stdio.h>
#include <stdlib.h>
#include "ft_printf.h"

#define TEST "\n\
|%c| est un char\n\
|%s| est une string\n\
|%p| est une addresse\n\
|%d| est un entier\n\
|%i| aussi\n\
|%u| est un entier non signe\n\
|%x| est un hexa\n\
|%X| est un HEXA\n\
|%%| est un simple pourcent",\
0,\
NULL,\
NULL,\
-42,\
-2048,\
42,\
42,\
127

int	main(void)
{
	int	ret;
	int	ft_ret;

	printf("\e[32m   printf[");
	ret = printf(TEST);
	printf("]: %d\n", ret);
	printf("\e[33mft_printf[");
	fflush(stdout);
	ft_ret = ft_printf(TEST);
	printf("]: %d\n\e[0m", ft_ret);
	fflush(stdout);
	system("leaks a.out | grep 'Process'");
	return (0);
}