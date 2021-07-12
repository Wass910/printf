#include "ft_printf.h"

char	*ft_itoa_space( int n, int base)
{
	char	*alpha;
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_count(n) + 1));
	if (str == NULL)
		return (0);
	alpha = "0123456789abcdef";
	if (n < 0)
		n = 4294967296 - (1 * n);
	while (n > 0)
	{
		str[i] = alpha[n % base];
		i++;
		n = n / base;
	}
	str[i] = '\0';
	str = ft_strrev(str);
	return (str);
}

char	*ft_itoa_u(long int n, int base)
{
	char	*alpha;
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_count_long(n) + 1));
	if (str == NULL)
		return (0);
	alpha = "0123456789abcdef";
	if (n < 0)
		n = 4294967296 - (1 * n);
	if (n == 0)
		ft_putchar('0', 0);
	while (n > 0)
	{
		str[i] = alpha[n % base];
		i++;
		n = n / base;
	}
	str[i] = '\0';
	str = ft_strrev(str);
	return (str);
}

void	ft_n_neg(int n)
{
	if (n < 0)
	{
		n = 4294967296 - (1 * n);
		ft_putchar('-', 0);
	}
	return ;
}

char	*ft_itoa_x(long int n, int type_charac)
{
	char	*alpha;
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_count_long(n) + 1));
	if (str == NULL)
		return (0);
	if (type_charac == 1)
		alpha = "0123456789abcdef";
	else
		alpha = "0123456789ABCDEF";
	ft_n_neg(n);
	while (n > 0)
	{
		str[i] = alpha[n % 16];
		i++;
		n = n / 16;
	}
	str[i] = '\0';
	str = ft_strrev(str);
	return (str);
}
