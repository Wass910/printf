#include "ft_printf.h"

int ft_test_squeeze(int i, const char *str)
{
    while (str[i] < 'a' || str[i] > 'z')
    {
        if (str[i] == '.')
        {
            return 1;
        }
        i++;
    }
    return 0;
}

int     ft_squeeze_spec(int i, const char *str)
{
    char *speciation;
    int tmp;

    tmp = i;
    while(str[tmp] >= '0' && str [tmp ] <= '9')
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
    //i++;
    tmp = ft_atoi(speciation);
    return (tmp);
}

int     ft_squeeze_point(int i, const char *str)
{
    char *speciation;
    int tmp;

    tmp = i;
    while(str[tmp] >= '0' && str [tmp ] <= '9')
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
    //i++;
    tmp = ft_atoi(speciation);
    return (tmp);
}

void    ft_write_space(int space)
{
     while (space > 0)
    {
        ft_putchar(' ');
        space--;
    }
    return ;
}

void    ft_condition_squeeze_d(int nb, int tmp)
{
    if (nb < 0)
        tmp--;
    while(tmp > 0)
    {
        ft_putchar(' ');
        tmp--;
    }
}

int    ft_condition_squeeze_u(int space, int zer, int lengh)
{
    int tmp;

    tmp = 0;
    if (space > zer && zer > lengh)
        tmp = space - zer;
    else if (lengh > zer)
        tmp = space - lengh;
    return tmp;
}

int     ft_point_d_squeeze(int nb, int space, int zer)
{
    char *dest;
    int lengh;
    int tmp;

    tmp = 0;
    if (nb == 0 && zer == 0)
    {
        ft_write_space(space);
        return 1;
    }
    if (space > zer)
        tmp = space - zer;
    dest = ft_itoa(nb, 10);
    lengh = ft_strlen(dest);
    if (zer == 0)
        tmp = tmp - lengh;
    if(nb == 0)
       zer--;
    while(zer - lengh > 0)
    {
        ft_putchar('0');
        zer--;
    }
    ft_putstr(dest);
    ft_condition_squeeze_d(nb, tmp);
    return 1;
}

int     ft_point_u_squeeze(unsigned int nb, int space, int zer)
{
    char *dest;
    int lengh;
    int tmp; 

    if (nb == 0 && zer == 0)
    {
        ft_write_space(space);
        return 1;
    }
    dest = ft_itoa_u(nb, 10);
    lengh = ft_strlen(dest);
    tmp = ft_condition_squeeze_u(space, zer, lengh);
    if(nb <= 0)
        zer--;
    while(zer - lengh > 0)
    {
        ft_putchar('0');
        zer--;
    }
    ft_putstr(dest);   
    while(tmp > 0)
    {
        ft_putchar(' ');
        tmp--;
    }
    return 1;
}

int     ft_point_x_squeeze( unsigned int nb, int space, int zer, char type)
{
    char *dest;
    int lengh;
    int tmp; 

    if (nb == 0 && zer == 0)
    {
        ft_write_space(space);
        return 1;
    }
    dest = ft_itoa_x(nb, 10);
    lengh = ft_strlen(dest);
    tmp = ft_condition_squeeze_u(space, zer, lengh);
    if(nb <= 0)
        zer--;
    while(zer - lengh > 0)
    {
        ft_putchar('0');
        zer--;
    }
    ft_verif_x(type, nb);    
    while(tmp > 0)
    {
        ft_putchar(' ');
        tmp--;
    }
    return 1;
}

int     ft_point_s_squeeze(char *dest, int space, int zer)
{
    int lengh;
    int i;
    int tmp;

    tmp = 0;
    if (space > zer)
        tmp = space - zer;
    i = 0;
    lengh = ft_strlen(dest);
    if(lengh <= zer)
    {
        ft_putstr(dest);
        return 1;
    }
    while (zer > 0)    
    {
        ft_putchar(dest[i]);
        zer--;
        i++;
    }
    while(tmp > 0)
    {
        ft_putchar(' ');
        tmp--;
    }
    return 1;
}

void     ft_type_squeeze(char type, va_list print_list, int space, int zer)
{
    if(type == 'd' || type == 'i')
        ft_point_d_squeeze(va_arg(print_list, int), space, zer);
    else if(type == 'u')
        ft_point_u_squeeze(va_arg(print_list, unsigned int), space, zer);
    else if(type == 'x' || type == 'X')
        ft_point_x_squeeze(va_arg(print_list,unsigned int), space, zer, type);
    else if(type == 's')
        ft_point_s_squeeze(va_arg(print_list, char*), space, zer);
    return ;
}

int     ft_squeeze(int i, const char *str, va_list print_list)
{
    int space;
    int zer;
    int tmp;

    tmp = i;
    if (str[tmp] == '*')
        space = va_arg(print_list, int);
    else 
        space = ft_squeeze_spec(i, str);
    while (str[tmp] != '.')
        tmp++;
    if (str[tmp + 1] == '*')
        zer = va_arg(print_list, int);
    else
        zer = ft_squeeze_point(tmp + 1, str);
    while (str[tmp] < 'a' || str[tmp] > 'z')
        tmp++;
    ft_type_squeeze(str[tmp], print_list, space, zer); 

    return (tmp);
}