#include "ft_printf.h"

void	ft_norme_u(unsigned int nb_u)
{
	if (nb_u != 0)
		ft_putstr(ft_itoa_u(nb_u, 10), 0);
	else
		ft_putchar('0', 0);
	return ;
}

void	ft_norme_d(int nb)
{
	if (nb != INT_MIN)
		ft_putstr(ft_itoa(nb, 10), 0);
	else
		ft_putstr("-2147483648", 0);
	return ;
}

int	ft_norme_tiret(void *adress)
{
	char *dest;

	dest = ft_adress(adress);
	if (adress == NULL)
		return (3);
	return (ft_strlen(dest) + 2);
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