/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:26:28 by idhiba            #+#    #+#             */
/*   Updated: 2021/07/13 18:27:10 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
