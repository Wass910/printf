#include "ft_printf.h"

int     ft_zero_d(int nb, int speciation)
{
    char *dest;
    int lengh;

    dest = ft_itoa(nb, 10);
    lengh = ft_strlen(dest);
    if(nb <= 0)
        speciation--;
    while(speciation - lengh > 0)
    {
        ft_putchar('0');
        speciation--;
    }
    ft_putstr(dest);
    return 1;
}

int     ft_zero_u(unsigned int nb, int speciation)
{
    char *dest;
    int lengh;

    dest = ft_itoa_u(nb, 10);
    lengh = ft_strlen(dest);
    if(nb <= 0)
        speciation--;
    while(speciation - lengh > 0)
    {
        ft_putchar('0');
        speciation--;
    }
    ft_putstr(dest);
    return 1;
}

int     ft_zero_x(char type,long int nb, int speciation)
{
    char *dest;
    int lengh;

    dest = ft_itoa_x(nb, 10);
    lengh = ft_strlen(dest);
    if(nb <= 0)
        speciation--;
    while(speciation - lengh > 0)
    {
        ft_putchar('0');
        speciation--;
    }
    ft_verif_x(type, nb);
    return 1;
}

int     ft_type_zero(char type, va_list print_list, int speciation)
{
    if(type == 'd' || type == 'i')
        return(ft_zero_d(va_arg(print_list, int), speciation));
    else if(type == 'u')
        return (ft_zero_u(va_arg(print_list, unsigned int), speciation));
    else if(type == 'x' || type == 'X')
        return (ft_zero_x(type, va_arg(print_list,unsigned int), speciation));
    return 0;
}

int     ft_zero(int i, const char *str, va_list print_list)
{
    char *speciation;
    int tmp;

    tmp = i;
    while(str[tmp + 1] >= '0' && str [tmp + 1] <= '9')
        tmp++;
    if (!(speciation = malloc(sizeof(*speciation) * (tmp + 1))))
		return (0);
    tmp = 0; 
    while(str[i] >= '0' && str [i] <= '9')
    {
        speciation[tmp] = str[i];
        tmp++;
        i++;
    }
    tmp = ft_atoi(speciation);
    ft_type_zero(str[i], print_list, tmp);
    return (i);
}

int     ft_zero_star(int i, const char *str, va_list print_list)
{
    int tmp;

    tmp = va_arg(print_list, int);
    i++;
    ft_type_zero(str[i], print_list, tmp);
    return (i);
}