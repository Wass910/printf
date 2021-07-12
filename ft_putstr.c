#include "ft_printf.h"

int	ft_putstr(char *s, int n)
{
	int			i;
	static int	ret;
	int			res;

	i = 0;
	if (n == 1)
	{
		res = ret;
		ret = 0;
		return (res);
	}
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
		ret++;
	}
	return (ret);
}
