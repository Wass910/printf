#include "ft_printf.h"

int	ft_space_d(int nb, int speciation)
{
	char	*dest;
	int		lengh;

	dest = ft_itoa_space(nb, 10);
	lengh = ft_strlen(dest);
	if (nb <= 0)
		speciation--;
	while (speciation - lengh > 0)
	{
		ft_putchar(' ', 0);
		speciation--;
	}
	if (nb < 0)
		ft_putchar('-', 0);
	if (nb == 0)
		ft_putchar('0', 0);
	ft_putstr(dest, 0);
	free(dest);
	return (1);
}

int	ft_space_x(char type, long int nb, int speciation)
{
	char	*dest;
	int		lengh;

	dest = ft_itoa_x(nb, 10);
	lengh = ft_strlen(dest);
	if (nb <= 0)
		speciation--;
	while (speciation - lengh > 0)
	{
		ft_putchar(' ', 0);
		speciation--;
	}
	ft_verif_x(type, nb);
	free(dest);
	return (1);
}

int	ft_space_u(unsigned int nb, int speciation)
{
	char	*dest;
	int		lengh;

	dest = ft_itoa_u(nb, 10);
	lengh = ft_strlen(dest);
	if (nb <= 0)
		speciation--;
	while (speciation - lengh > 0)
	{
		ft_putchar(' ', 0);
		speciation--;
	}
	if (nb == 0)
		ft_putchar('0', 0);
	ft_putstr(dest, 0);
	free(dest);
	return (1);
}

int	ft_space_c(char charac, int speciation)
{
	while (speciation - 1 > 0)
	{
		ft_putchar(' ', 0);
		speciation--;
	}
	ft_putchar(charac, 0);
	return (1);
}

int	ft_space_p(void *adress, int speciation)
{
	char	*dest;
	int		lengh;

	dest = ft_itoa_u((intptr_t)adress, 16);
	lengh = ft_strlen(dest) + 2;
	while (speciation - lengh > 0)
	{
		ft_putchar(' ', 0);
		speciation--;
	}
	ft_adress(adress);
	free(dest);
	return (1);
}
