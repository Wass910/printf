#include "ft_printf.h"

int     ft_point_d(int nb, int speciation)
{
    char *dest;
    int lengh;

    dest = ft_itoa(nb, 10);
    lengh = ft_strlen(dest);
    if(nb == 0)
        speciation--;
    while(speciation - lengh > 0)
    {
        ft_putchar('0');
        speciation--;
    }
    ft_putstr(dest);
    return 1;
}

int     ft_point_s(char *dest, int speciation)
{
    int lengh;
    int i;

    i = 0;
    lengh = ft_strlen(dest);
    if(lengh <= speciation)
    {
        ft_putstr(dest);
        return 1;
    }
    while (speciation > 0)    
    {
        ft_putchar(dest[i]);
        speciation--;
        i++;
    }
    return 1;
}

int     ft_type_point(char type, va_list print_list, int speciation)
{

    if(type == 'd' || type == 'i')
        return(ft_point_d(va_arg(print_list, int), speciation));
    else if(type == 'u')
        return (ft_zero_u(va_arg(print_list, unsigned int), speciation));
    else if(type == 'x' || type == 'X')
        return (ft_zero_x(type, va_arg(print_list,unsigned int), speciation));
    else if(type == 's')
        return (ft_point_s(va_arg(print_list, char*), speciation));
    return 0;
}

int     ft_point(int i, const char *str, va_list print_list)
{
    char *speciation;
    int tmp;

    tmp = i;
    while(str[tmp + 1] >= '0' && str [tmp + 1] <= '9')
        tmp++;
    if (!(speciation = malloc(sizeof(*speciation) * (tmp + 1))))
		return (0);
    tmp = 0; 
    while(str[i + 1] == '0')
        i++;
    while(str[i + 1] >= '0' && str [i + 1] <= '9')
    {
        speciation[tmp] = str[i + 1];
        tmp++;
        i++;
    }
    i++;
    tmp = ft_atoi(speciation);
    ft_type_point(str[i], print_list, tmp);
    return (i);
}

int     ft_point_star(int i, const char *str, va_list print_list)
{

    int tmp;

    tmp = va_arg(print_list, int);
    i++;
    ft_type_point(str[i], print_list, tmp);
    return (i);
}