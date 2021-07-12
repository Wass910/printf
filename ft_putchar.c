#include "ft_printf.h"

int	ft_putchar(char c, int n)
{
	static int	i;
	int			res;

	if (n == 1)
	{	
		res = i;
		i = 0;
		return (res);
	}
	write(1, &c, 1);
	i++;
	return (i);
}
