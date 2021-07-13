/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:25:26 by idhiba            #+#    #+#             */
/*   Updated: 2021/07/13 18:25:29 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_norme_u(unsigned int nb_u)
{
	if (nb_u != 0)
		ft_putstr(ft_itoa_u(nb_u, 10), 0);
	else
		ft_putchar('0', 0);
	return ;
}

void	ft_type(char type, va_list print_list)
{
	char	*dest;

	if (type == 'd' || type == 'i')
		ft_putstr(ft_itoa(va_arg(print_list, int), 10), 0);
	else if (type == 'c')
		ft_putchar(va_arg(print_list, int), 0);
	else if (type == 's')
	{
		dest = va_arg(print_list, char *);
		if (dest == NULL)
			ft_putstr("(null)", 0);
		else
			ft_putstr(dest, 0);
	}
	else if (type == 'u')
		ft_norme_u(va_arg(print_list, unsigned int));
	else if (type == 'x' || type == 'X')
		ft_verif_x(type, va_arg(print_list, unsigned int));
	else if (type == 'p')
		ft_adress(va_arg(print_list, void *));
	return ;
}

int	ft_flag(int i, const char *str, va_list print_list)
{
	if (str[i] == '-')
		i = ft_tiret(i, str, print_list);
	else if (str[i] >= '0' && str[i] <= '9')
	{
		if (str[i] == '0')
			i = ft_zero(i, str, print_list);
		else
			i = ft_space(i, str, print_list);
	}
	else if (str[i] == '.')
		i = ft_point(i, str, print_list);
	else
		ft_type(str[i], print_list);
	return (i);
}

int	ft_all(const char *str, va_list print_list)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] == '%')
			ft_putchar('%', 0);
		if (str[i] != '%')
			ft_putchar(str[i], 0);
		else
			i = ft_flag(i + 1, str, print_list);
		i++;
	}
	return (i);
}

int	ft_printf(const char *str, ...)
{
	int			count;
	int			ret;
	int			result;
	va_list		print_list;

	va_start(print_list, str);
	ft_all(str, print_list);
	count = ft_putchar('a', 1);
	ret = ft_putstr("a", 1);
	result = count + ret;
	va_end(print_list);
	printf("\n");
	return (result);
}
