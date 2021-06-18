#include "ft_printf.h"

int     ft_space_d(int nb, int speciation)
{
    char *dest;
    int lengh;

    dest = ft_itoa_space(nb, 10);
    lengh = ft_strlen(dest);
    if(nb <= 0)
        speciation--;
    while(speciation - lengh > 0)
    {
        ft_putchar(' ');
        speciation--;
    }
    if(nb < 0)
        ft_putchar('-');
    if (nb == 0)
        ft_putchar('0');
    ft_putstr(dest);
    return 1;
}

int     ft_space_u(unsigned int nb, int speciation)
{
    char *dest;
    int lengh;

    dest = ft_itoa_u(nb, 10);
    lengh = ft_strlen(dest);
    if(nb <= 0)
        speciation--;
    while(speciation - lengh > 0)
    {
        ft_putchar(' ');
        speciation--;
    }
    ft_putstr(dest);
    return 1;
}

int     ft_space_c(char charac, int speciation)
{
    while(speciation - 1 > 0)
    {
        ft_putchar(' ');
        speciation--;
    }
    ft_putchar(charac);
    return 1;
}

int     ft_space_x(char type,long int nb, int speciation)
{
    char *dest;
    int lengh;

    dest = ft_itoa_x(nb, 10);
    lengh = ft_strlen(dest);
    if(nb <= 0)
        speciation--;
    while(speciation - lengh > 0)
    {
        ft_putchar(' ');
        speciation--;
    }
    ft_verif_x(type, nb);
    return 1;
}

int     ft_space_p(void *adress, int speciation)
{
    char *dest;
    int lengh;

    dest = ft_itoa_u((intptr_t)adress, 16);    
    lengh = ft_strlen(dest) + 2;
    while(speciation - lengh > 0)
    {
        ft_putchar(' ');
        speciation--;
    }
    ft_adress(adress);
    return 1;
}

int     ft_space_s(char *dest, int speciation)
{
    int lengh;

    lengh = ft_strlen(dest);
    while(speciation - lengh > 0)
    {
        ft_putchar(' ');
        speciation--;
    }
    ft_putstr(dest);
    return 1;
}

int     ft_type_space(char type, va_list print_list, int speciation)
{
    if(type == 'd' || type == 'i')
        return(ft_space_d(va_arg(print_list, int), speciation));
    if(type == 'c')
        return(ft_space_c(va_arg(print_list, int), speciation));
    else if(type == 'u')
        return (ft_space_u(va_arg(print_list, unsigned int), speciation));
    else if(type == 'p')
        return (ft_space_p(va_arg(print_list, void*), speciation));
    else if(type == 'x' || type == 'X')
        return (ft_space_x(type, va_arg(print_list,unsigned int), speciation));
    else if(type == 's')
        return (ft_space_s(va_arg(print_list, char*), speciation));
    return 0;
}

int     ft_space(int i, const char *str, va_list print_list)
{
    char *speciation;
    int tmp;

    tmp = i;
    while(str[tmp] >= '0' && str [tmp] <= '9')
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
    ft_type_space(str[i], print_list, tmp);
    return (i);
}