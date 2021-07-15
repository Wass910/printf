/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norme.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:25:26 by idhiba            #+#    #+#             */
/*   Updated: 2021/07/14 19:27:26 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_norme_u(unsigned int nb_u)
{
	char	*dest;

	dest = ft_itoa_u(nb_u, 10);
	if (nb_u != 0)
		ft_putstr(dest, 0);
	else
		ft_putchar('0', 0);
	free(dest);
	return ;
}

void	ft_norme_d(int nb)
{
	char	*dest;

	dest = ft_itoa(nb, 10);
	if (nb != INT_MIN)
		ft_putstr(dest, 0);
	else
		ft_putstr("2147483648", 0);
	free(dest);
	return ;
}

int	ft_norme_tiret(void *adress)
{
	char	*dest;
	int		lengh;

	dest = ft_adress(adress);
	if (adress == NULL)
	{
		free(dest);
		return (3);
	}
	lengh = ft_strlen(dest);
	free(dest);
	return (lengh + 2);
}

void	ft_tiret_norme(int tmp, int espaces)
{
	while (tmp - espaces > 0)
	{
		ft_putchar(' ', 0);
		tmp--;
	}
	return ;
}

int	ft_norme_itoa(int n)
{
	if (n < 0)
	{	
		n = -1 * (n);
		ft_putchar('-', 0);
	}
	if (n == 0)
		ft_putchar('0', 0);
	return (n);
}
