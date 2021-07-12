#include "ft_printf.h"

int     ft_space_d(int nb, int speciation)
{
    char *dest;
    int lengh;

    dest = ft_itoa_space(nb, 10);
    lengh = ft_strlen(dest);
    if (speciation <  0)
    {

        if (nb == 0)
        {
            ft_putchar('0', 0);
            lengh++;
        }
        else if (nb < 0)
        {
            ft_putchar('-', 0);
            lengh++;
            ft_putstr(dest, 0);
        }
        else
            ft_putstr(dest, 0);
        while(speciation * (-1) - lengh > 0)
        {
            ft_putchar(' ', 0);
            speciation++;
        }
        return 1;
    }
    if(nb <= 0)
        speciation--;
    while(speciation - lengh > 0)
    {
        ft_putchar(' ', 0);
        speciation--;
    }
    if(nb < 0)
        ft_putchar('-', 0);
    if (nb == 0)
        ft_putchar('0', 0);
    ft_putstr(dest, 0);
    free(dest);
    return 1;
}

int     ft_space_x(char type,long int nb, int speciation)
{
    char *dest;
    int lengh;

    dest = ft_itoa_x(nb, 10);
    lengh = ft_strlen(dest);
    if (speciation < 0)
    {
        ft_verif_x(type, nb);
        speciation = speciation * (-1);
        if (nb == 0)
            lengh++;
        while(speciation - lengh > 0)
        {
            ft_putchar(' ', 0);
            speciation--;
        }
        return 1;
    }
    if(nb <= 0)
        speciation--;
    while(speciation - lengh > 0)
    {
        ft_putchar(' ', 0);
        speciation--;
    }
    ft_verif_x(type, nb);
    free(dest);
    return 1;
}

int     ft_space_u(unsigned int nb, int speciation)
{
    char *dest;
    int lengh;

    if (nb == 0 && speciation >= 0)
    {
        while(speciation - 1 > 0)
        {
            ft_putchar(' ', 0);
            speciation--;
        }
        ft_putchar('0', 0);
        return 1;
    }
    dest = ft_itoa_u(nb, 10);
    lengh = ft_strlen(dest);
    if (speciation < 0)
    {
        if (lengh == 0)
            lengh++;
        ft_putstr(dest, 0);
        speciation = speciation * (-1);
        while(speciation - lengh > 0)
        {
            ft_putchar(' ', 0);
            speciation--;
        }
        return 1;
    }
    if(nb <= 0)
        speciation--;
    
    while(speciation - lengh > 0)
    {
        ft_putchar(' ', 0);
        speciation--;
    }
    ft_putstr(dest, 0);
    free(dest);
    return 1;
}

int     ft_space_c(char charac, int speciation)
{
    if (speciation > 0)
    {
        while(speciation - 1 > 0)
        {
            ft_putchar(' ', 0);
            speciation--;
        }
        ft_putchar(charac, 0);
    }
    else
    {
        ft_putchar(charac, 0);
        speciation = speciation * (-1);
        while(speciation - 1 > 0)
        {
            ft_putchar(' ', 0);
            speciation--;
        }
    }
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
        ft_putchar(' ', 0);
        speciation--;
    }
    ft_adress(adress);
    free(dest);
    return 1;
}

int     ft_space_s_null(char *dest, int speciation)
{
    int lengh;

    lengh = ft_strlen(dest);
    if (speciation <  0)
    {
        ft_putstr(dest, 0);
        speciation = speciation * (-1);
        while(speciation - lengh > 0)
        {
            ft_putchar(' ', 0);
            speciation--;
        }
        return 1;
    }
    while(speciation - lengh > 0)
    {
        ft_putchar(' ', 0);
        speciation--;
    }
    ft_putstr(dest, 0);
    return 1;
}

int     ft_space_s(char *dest, int speciation)
{
    int lengh;

    if (dest == NULL)
    {
        ft_space_s_null("(null)", speciation);
        return 1;
    }
    if ( speciation < 0)
        speciation = speciation * (-1);
    lengh = ft_strlen(dest);
    while(speciation - lengh > 0)
    {
        ft_putchar(' ', 0);
        speciation--;
    }
    ft_putstr(dest, 0);
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
    free(speciation);
    return (i);
}