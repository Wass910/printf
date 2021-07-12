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
	if (nb == 0)
	{
		ft_putchar('0', 0);
		return ;
	}
	if (c == 'x')
		ft_putstr(ft_itoa_x(nb, 1), 0);
	else
		ft_putstr(ft_itoa_x(nb, 2), 0);
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
	write(1, "0x", 2);
	ft_putstr(dest, 0);
	return (dest);
}
