/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:24:34 by idhiba            #+#    #+#             */
/*   Updated: 2021/07/13 18:24:39 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_count(int n)
{
	int	i;

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

int	ft_count_long(long int n)
{
	long int	i;

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

char	*ft_strrev(char *str)
{
	int		i;
	int		y;
	char	*tmp;

	y = 0;
	i = 0;
	while (str[i] != '\0')
		i++;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (tmp == NULL)
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
	char	*test;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (ft_count(n) + 1));
	if (str == NULL)
		return (0);
	alpha = "0123456789abcdef";
	n = ft_norme_itoa(n);
	while (n > 0)
	{
		str[i] = alpha[n % base];
		i++;
		n = n / base;
	}
	str[i] = '\0';
	test = ft_strrev(str);
	free(str);
	return (test);
}

char	*ft_itoa_squeeze( int n, int base)
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
