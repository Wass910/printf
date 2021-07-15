/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:24:46 by idhiba            #+#    #+#             */
/*   Updated: 2021/07/13 18:24:48 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	*test;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_count_long(n) + 1));
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
	test = ft_strrev(str);
	free(str);
	return (test);
}

char	*ft_itoa_x(long int n, int type_charac)
{
	char	*alpha;
	char	*str;
	char	*test;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_count_long(n) + 1));
	if (str == NULL)
		return (0);
	if (type_charac == 1)
		alpha = "0123456789abcdef";
	else
		alpha = "0123456789ABCDEF";
	while (n > 0)
	{
		str[i] = alpha[n % 16];
		i++;
		n = n / 16;
	}
	str[i] = '\0';
	test = ft_strrev(str);
	free(str);
	return (test);
}
