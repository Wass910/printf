#include "ft_printf.h"

int	ft_space_s_null(char *dest, int speciation)
{
	int	lengh;

	lengh = ft_strlen(dest);
	while (speciation - lengh > 0)
	{
		ft_putchar(' ', 0);
		speciation--;
	}
	ft_putstr(dest, 0);
	return (1);
}

int	ft_space_s(char *dest, int speciation)
{
	int	lengh;

	if (dest == NULL)
	{
		ft_space_s_null("(null)", speciation);
		return (1);
	}
	if (speciation < 0)
		speciation = speciation * (-1);
	lengh = ft_strlen(dest);
	while (speciation - lengh > 0)
	{
		ft_putchar(' ', 0);
		speciation--;
	}
	ft_putstr(dest, 0);
	return (1);
}

int	ft_type_space(char type, va_list print_list, int speciation)
{
	if (type == 'd' || type == 'i')
		return (ft_space_d(va_arg(print_list, int), speciation));
	if (type == 'c')
		return (ft_space_c(va_arg(print_list, int), speciation));
	else if (type == 'u')
		return (ft_space_u(va_arg(print_list, unsigned int), speciation));
	else if (type == 'p')
		return (ft_space_p(va_arg(print_list, void *), speciation));
	else if (type == 'x' || type == 'X')
		return (ft_space_x(type, va_arg(print_list, unsigned int), speciation));
	else if (type == 's')
		return (ft_space_s(va_arg(print_list, char *), speciation));
	return (0);
}

int	ft_space(int i, const char *str, va_list print_list)
{
	char	*speciation;
	int		tmp;

	tmp = i;
	while (str[tmp] >= '0' && str [tmp] <= '9')
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
	ft_type_space(str[i], print_list, tmp);
	free(speciation);
	return (i);
}
