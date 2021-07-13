/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:25:15 by idhiba            #+#    #+#             */
/*   Updated: 2021/07/13 23:48:31 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_point_d(int nb, int speciation)
{
	char	*dest;
	int		lengh;

	if (nb == INT_MIN)
		dest = ft_strdup("-2147483648");
	else
		dest = ft_itoa_squeeze(nb, 10);
	lengh = ft_strlen(dest);
	if (lengh == 0)
		lengh++;
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

int	ft_point_s(char *dest, int speciation)
{
	int	i;

	i = 0;
	if (dest == NULL)
	{
		ft_point_s("(null)", speciation);
	}
	if (speciation < 0)
		speciation = ft_strlen(dest);
	if (ft_strlen(dest) <= speciation)
	{
		ft_putstr(dest, 0);
		return (1);
	}
	while (speciation > 0)
	{
		ft_putchar(dest[i], 0);
		speciation--;
		i++;
	}
	return (1);
}

int	ft_point_x(char type, long int nb, int speciation)
{
	char	*dest;
	int		lengh;

	dest = ft_itoa_x(nb, 10);
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
	ft_verif_x_space(type, nb);
	free(dest);
	return (1);
}

int	ft_type_point(char type, va_list print_list, int speciation)
{
	char	*dest;

	if (type == 'd' || type == 'i')
		return (ft_point_d(va_arg(print_list, int), speciation));
	else if (type == 'u')
		return (ft_zero_u(va_arg(print_list, unsigned int), speciation));
	else if (type == 'x' || type == 'X')
		return (ft_point_x(type, va_arg(print_list, unsigned int), speciation));
	else if (type == 's')
	{
		dest = va_arg(print_list, char *);
		if (dest == NULL)
			ft_point_s("(null)", speciation);
		else
			ft_point_s(dest, speciation);
	}
	return (1);
}

int	ft_point(int i, const char *str, va_list print_list)
{
	char	*speciation;
	int		tmp;

	tmp = i;
	while (str[tmp + 1] >= '0' && str [tmp + 1] <= '9')
		tmp++;
	speciation = malloc(sizeof(char) * (tmp + 1));
	if (speciation == NULL)
		return (0);
	tmp = 0;
	while (str[i + 1] == '0')
		i++;
	while (str[i + 1] >= '0' && str [i + 1] <= '9')
	{
		speciation[tmp] = str[i + 1];
		tmp++;
		i++;
	}
	i++;
	tmp = ft_atoi(speciation);
	ft_type_point(str[i], print_list, tmp);
	free(speciation);
	return (i);
}
