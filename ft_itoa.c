#include "ft_printf.h"

int			ft_count(int n)
{
	int i;

	i = 0;
	if (n < 0)
		i = 1;
	if (n == 0)
	{
		i = 1;
		return (i);
	}
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int			ft_count_long(long int n)
{
	long int i;

	i = 0;
	if (n < 0)
		i = 1;
	if (n == 0)
	{
		i = 1;
		return (i);
	}
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char		*ft_strrev(char *str)
{
	int		i;
	int		y;
	char	*tmp;

	y = 0;
	i = 0;
	while (str[i] != '\0')
		i++;
	if (!(tmp = (char*)malloc(sizeof(char) * (i + 1))))
		return (0);
	i--;
	while (i >= 0)
	{
		tmp[y] = str[i];
		i--;
		y++;
	}
	tmp[y] = '\0';
	return (tmp);
}

char	*ft_itoa(int n, int base)
{
	char	*alpha;
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * (ft_count(n) + 1))))
		return (0);
	alpha = "0123456789abcdef";
	if (n < 0)
	{
		n = 4294967296 - (1 * n);
        ft_putchar('-', 0);
	}
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

char	*ft_itoa_squeeze( int n, int base)
{
	char	*alpha;
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * (ft_count(n) + 1))))
		return (0);
	alpha = "0123456789abcdef";
	if (n < 0)
	{
		n = 4294967296 - (1 * n);
        ft_putchar('-', 0);
	}
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

char	*ft_itoa_space( int n, int base)
{
	char	*alpha;
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * (ft_count(n) + 1))))
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
	if (!(str = (char*)malloc(sizeof(char) * (ft_count_long(n) + 1))))
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

char	*ft_itoa_u_space(long int n, int base)
{
	char	*alpha;
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * (ft_count_long(n) + 1))))
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

char	*ft_itoa_x(long int n, int type_charac)
{
	char	*alpha;
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * (ft_count_long(n) + 1))))
		return (0);
    if (type_charac == 1)
	    alpha = "0123456789abcdef";
    else 
        alpha = "0123456789ABCDEF";
    if (n < 0)
	{
		n = 4294967296 - (1 * n);
        ft_putchar('-', 0);
	}
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