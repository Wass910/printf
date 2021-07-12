#include "ft_printf.h"

int     ft_tiret_d(int no_zer)
{
    char *dest;

    dest = ft_itoa(no_zer, 10);
    ft_putstr(dest, 0);
    if(ft_no_zer(no_zer) == 1)
        return 1;
    if(no_zer == ft_strlen(dest))
        return ft_strlen(dest );
    if(no_zer < 0)
        return (ft_strlen(dest) + 1);
    return ft_strlen(dest);

}

int     ft_tiret_u(unsigned int no_zer_u)
{
    char *dest;
    unsigned int lengh;

    dest = ft_itoa_u(no_zer_u, 10);
    lengh = ft_strlen(dest);
    ft_putstr(dest, 0);
    free(dest);
    if(ft_no_zer(no_zer_u) == 1)
        return 1;
    if(no_zer_u == 1)
        return (lengh);
    if(no_zer_u == lengh)
        return lengh;
    return lengh;
}

int     ft_tiret_x(char type, long int tiret_x)
{
    char *dest;
    int lengh;

    ft_verif_x(type, tiret_x);
    dest = ft_itoa_x(tiret_x, 1);
    lengh = ft_strlen(dest);
    free(dest);
    if(tiret_x == 0)
        return (lengh + 1);
    return lengh;
}

int     ft_type_tiret(char type, va_list print_list)
{
    char *dest;

    if(type == 'd' || type == 'i')
        return(ft_tiret_d(va_arg(print_list, int)));
    else if(type == 'c')
        ft_putchar(va_arg(print_list, int), 0);
        return 1;
    else if(type == 's')
    {    
        dest = ft_strdup(va_arg(print_list, char*));
        if (dest == NULL)
            ft_putstr("(null)", 0);
        ft_putstr(dest, 0);
    }
    else if(type == 'u')
        return (ft_tiret_u(va_arg(print_list, unsigned int)));
    else if(type == 'x' || type == 'X')
        return (ft_tiret_x(type, va_arg(print_list,unsigned int)));
    else if(type == 'p')
        dest = ft_adress(va_arg(print_list,void *));
    return (1);
}

int     ft_tiret(int i, const char *str, va_list print_list)
{
    char *speciation;
    int tmp;
    int espaces;

    tmp = i;
    while(str[tmp + 1] >= '0' && str [tmp + 1] <= '9')
        tmp++;
    if (!(speciation = malloc(sizeof(*speciation) * (tmp + 1))))
		return (0);
    tmp = 0; 
    while(str[i + 1] >= '0' && str [i + 1] <= '9')
    {
        speciation[tmp] = str[i + 1];
        tmp++;
        i++;
    }
    i++;
    tmp = ft_atoi(speciation);
    espaces = ft_type_tiret(str[i], print_list);
    while(tmp - espaces > 0)
    {
        ft_putchar(' ', 0);
        tmp--;
    }
    free(speciation);
    return (i);
}