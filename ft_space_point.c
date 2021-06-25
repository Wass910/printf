#include "ft_printf.h"

int     ft_point_d_space(int nb, int space, int zer)
{
    char *dest;
    int lengh;
    int tmp;

    tmp = 0;
    dest = ft_itoa_space(nb, 10);
    lengh = ft_strlen(dest);
    if (nb < 0)
        space--;
    if (lengh > zer)
        space = space - lengh ;
    else 
        space = space - zer;
    if (zer < 0)
    {
        if(nb < 0)
        {
            ft_putchar('-', 0);
        }
        while (space  > 0)
        {
            ft_putchar('0', 0);
            space--;
        }
        ft_putstr(dest, 0);
        return 1;
    }
    while(space > 0)
    {
        ft_putchar(' ', 0);
        space--;
    }
    if(nb < 0)
    {
        ft_putchar('-', 0);
    }
    while (zer - lengh > 0)
    {
        ft_putchar('0', 0);
        zer--;
    }
    ft_putstr(dest, 0);
    free(dest);
    return 1;
}

int     ft_point_u_space(unsigned int nb, int space, int zer)
{
    char *dest;
    int lengh;
    int tmp;

    tmp = 0;
    dest = ft_itoa_u_space(nb, 10);
    lengh = ft_strlen(dest);
    if (nb < 0)
        space--;
    if (zer < lengh)
        space = space - lengh;
    else
        space = space - zer;
    //if(zer == 0 && nb != 0)
    //    space = space - lengh;
    while(space > 0)
    {
        ft_putchar(' ', 0);
        space--;
    }
    if(nb < 0)
    {
        ft_putchar('-', 0);
    }
    while (zer - lengh > 0)
    {
        ft_putchar('0', 0);
        zer--;
    }
    ft_putstr(dest, 0);
    free(dest);
    return 1;
}

int     ft_point_x_space(unsigned int nb, int space, int zer, char type)
{
    char *dest;
    int lengh;
    int tmp;

    tmp = 0;
    dest = ft_itoa_x(nb, 10);
    lengh = ft_strlen(dest);
    if (space < 0)
    {
        ft_verif_x_space(type, nb);
        space = space * (-1);
        while(space - lengh > 0)
        {
            ft_putchar(' ', 0);
            space--;
        }
        return 1;
    }
    if (zer < lengh)
        space = space - lengh;
    else if (lengh > zer)
        space = space - lengh ;
    else 
        space = space - zer;
    while(space > 0)
    {
        ft_putchar(' ', 0);
        space--;
    }
    if(nb < 0)
    {
        ft_putchar('-', 0);
    }
    if (nb == 0)
    {
        ft_putchar('0', 0);
        lengh--;
    }
    while (zer - lengh > 0)
    {
        ft_putchar('0', 0);
        zer--;
    }
    ft_verif_x_space(type, nb);
    free(dest);
    return 1;
}

int     ft_point_s_space(char *dest, int space, int zer)
{
    int lengh;
    int i;
    int tmp;
    tmp = 0;
    i = 0;

    lengh = ft_strlen(dest);
    if (zer < lengh)
        tmp = space - zer;
    else if (space > zer)
        tmp = space - lengh;
    if (tmp < 0)
        tmp = space - zer;
    //if(lengh <= zer)
    //{
     //   ft_putstr(dest, 0);
     //   return 1;
    //}
    if (zer < 0)
    {
        while(space - lengh  > 0)
        {
            ft_putchar(' ', 0);
            space--;
        }
        if (dest[i] != '\0')
        {
            while (lengh > 0)    
            {
                ft_putchar(dest[i], 0);
                lengh--;
                i++;
            }
       }
       return 1;
    }
    while(tmp > 0)
    {
        ft_putchar(' ', 0);
        tmp--;
    }
    if (dest[i] != '\0')
    {
        while (zer > 0)    
        {
            ft_putchar(dest[i], 0);
            zer--;
            i++;
        }
    }
    return 1;
}

void     ft_type_squeeze_spec(char type, va_list print_list, int space, int zer)
{
    char *dest;

    if(type == 'd' || type == 'i')
        ft_point_d_space(va_arg(print_list, int), space, zer);
    else if(type == 'u')
        ft_point_u_space(va_arg(print_list, unsigned int), space, zer);
    else if(type == 'x' || type == 'X')
        ft_point_x_space(va_arg(print_list,unsigned int), space, zer, type);
    else if(type == 's')
    {   
        dest = va_arg(print_list, char*);
        if (dest == NULL)
        {    
            ft_point_s_space("(null)", space, zer); 
        }
        else
        {
            ft_point_s_space(dest, space, zer);
        }
    }
    return ;
}

int     ft_test_spec(int i, const char *str, va_list print_list)
{
    int space;
    int zer;
    int tmp;

    tmp = i;
    while(str[tmp] == '0')
        tmp++;
    if (str[tmp] == '*')
    {
        space = va_arg(print_list, int);
    }
    else 
        space = ft_squeeze_spec(i, str);
    while (str[tmp] != '.')
        tmp++;
    if (str[tmp + 1] == '*')
        zer = va_arg(print_list, int);
    else
        zer = ft_squeeze_point(tmp + 1, str);
    while (str[tmp] < 'A' || (str[tmp] > 'Z' && str[tmp] < 'a') || str[tmp] > 'z')
        tmp++;
    if (str[tmp] != 's' && str[tmp] != 'x' && str[tmp] != 'X' && space < 0)
            space = space * (-1);
    if (str[tmp] == 'x' || str[tmp == 'X'])
        ft_type_squeeze_spec(str[tmp], print_list, space, zer);
    else if(space <= zer)
    {
        ft_type_squeeze(str[tmp], print_list, space, zer); 
    }
    else 
    {
        ft_type_squeeze_spec(str[tmp], print_list, space, zer);
    }
    return (tmp);
}


