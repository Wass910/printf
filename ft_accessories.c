/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_accessories.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:23:12 by idhiba            #+#    #+#             */
/*   Updated: 2021/07/14 19:24:57 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_convers_u(unsigned int nb)
{
	unsigned int	i;

	i = nb;
	i = i * (-1);
	i = 4294967296 - i;
	return (i);
}

void	ft_verif_x(char c, unsigned int nb)
{
	char	*dest;

	if (c == 'x')
		dest = ft_itoa_x(nb, 1);
	else
		dest = ft_itoa_x(nb, 2);
	if (nb == 0)
	{
		free(dest);
		ft_putchar('0', 0);
		return ;
	}
	ft_putstr(dest, 0);
	free(dest);
	return ;
}

void	ft_verif_x_space(char c, unsigned int nb)
{
	if (c == 'x')
		ft_putstr(ft_itoa_x(nb, 1), 0);
	else
		ft_putstr(ft_itoa_x(nb, 2), 0);
	return ;
}

char	*ft_adress(void *adress)
{
	char	*dest;

	dest = ft_itoa_u((intptr_t)adress, 16);
	ft_putstr("0x", 0);
	if (adress == NULL)
		ft_putchar('0', 0);
	else
		ft_putstr(dest, 0);
	free(dest);
	return (dest);
}
