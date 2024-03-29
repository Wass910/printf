/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zero.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:28:19 by idhiba            #+#    #+#             */
/*   Updated: 2021/07/13 23:50:31 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_zero_d(int nb, int speciation)
{
	char	*dest;
	int		lengh;

	if (nb == INT_MIN)
		dest = ft_strdup("2147483648");
	else
		dest = ft_itoa(nb, 10);
	lengh = ft_strlen(dest);
	if (nb <= 0)
		speciation--;
	if (nb == INT_MIN)
		ft_putchar('-', 0);
	while (speciation - lengh > 0)
	{
		ft_putchar('0', 0);
		speciation--;
	}
	ft_putstr(dest, 0);
	free(dest);
	return (1);
}

int	ft_zero_u(unsigned int nb, int speciation)
{
	char	*dest;
	int		lengh;

	dest = ft_itoa_u(nb, 10);
	lengh = ft_strlen(dest);
	if (nb <= 0)
		speciation--;
	while (speciation - lengh > 0)
	{
		ft_putchar('0', 0);
		speciation--;
	}
	if (nb == 0)
		ft_putchar('0', 0);
	ft_putstr(dest, 0);
	free(dest);
	return (1);
}

int	ft_zero_x(char type, long int nb, int speciation)
{
	char	*dest;
	int		lengh;

	if (speciation < 0)
	{
		ft_space_x(type, nb, speciation);
		return (1);
	}
	dest = ft_itoa_x(nb, 10);
	lengh = ft_strlen(dest);
	if (nb <= 0)
		speciation--;
	while (speciation - lengh > 0)
	{
		ft_putchar('0', 0);
		speciation--;
	}
	ft_verif_x(type, nb);
	free(dest);
	return (1);
}

int	ft_type_zero(char type, va_list print_list, int speciation)
{
	if (type == 'd' || type == 'i')
		return (ft_zero_d(va_arg(print_list, int), speciation));
	else if (type == 'u')
		return (ft_zero_u(va_arg(print_list, unsigned int), speciation));
	else if (type == 'x' || type == 'X')
		return (ft_zero_x(type, va_arg(print_list, unsigned int), speciation));
	return (0);
}

int	ft_zero(int i, const char *str, va_list print_list)
{
	char	*speciation;
	int		tmp;

	tmp = i;
	while (str[tmp + 1] >= '0' && str [tmp + 1] <= '9')
		tmp++;
	speciation = malloc(sizeof(*speciation) * (tmp + 1));
	if (speciation == NULL)
		return (0);
	tmp = 0;
	while (str[i] >= '0' && str [i] <= '9')
	{
		speciation[tmp] = str[i];
		tmp++;
		i++;
	}
	tmp = ft_atoi(speciation);
	ft_type_zero(str[i], print_list, tmp);
	free(speciation);
	return (i);
}
