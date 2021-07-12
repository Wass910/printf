#include "ft_printf.h"

unsigned int     ft_convers_u(unsigned int nb)
{
    unsigned int i;

    i = nb;
    i = i * (-1);
    i = 4294967296 - i;
    return i;
}

void ft_verif_x(char c, unsigned int nb)
{
    if (nb == 0)
    {
        ft_putchar('0', 0);
        return;
    }
    if(c == 'x')
        ft_putstr(ft_itoa_x(nb, 1), 0);
    else
        ft_putstr(ft_itoa_x(nb, 2), 0); 
    return ;
}

void ft_verif_x_space(char c, unsigned int nb)
{
    if(c == 'x')
        ft_putstr(ft_itoa_x(nb, 1), 0);
    else
        ft_putstr(ft_itoa_x(nb, 2), 0); 
    return ;
}


char     *ft_adress(void *adress)
{
    char *dest;
    
    dest = ft_itoa_u((intptr_t)adress, 16);
    write(1, "0x", 2);
    ft_putstr(dest, 0);
    return dest;
}

void     ft_type(char type, va_list print_list)
{
    char *dest;
    if(type == 'd' || type == 'i')
        ft_putstr(ft_itoa(va_arg(print_list, int), 10), 0);
    else if(type == 'c')
        ft_putchar(va_arg(print_list, int), 0);
    else if(type == 's')
    {
        dest = va_arg(print_list, char*);
        if ( dest == NULL)
            ft_putstr("(null)", 0);
        else
            ft_putstr(dest, 0);
    }
    else if(type == 'u')
        ft_putstr(ft_itoa_u(va_arg(print_list,unsigned int), 10), 0);
    else if(type == 'x' || type == 'X')
        ft_verif_x(type, va_arg(print_list, unsigned int));
    else if(type == 'p')
        ft_adress(va_arg(print_list,void *));
    return ;
}

int    ft_flag(int i, const char *str, va_list print_list)
{
    if(str[i] == '-')
    {
       i = ft_tiret(i, str, print_list);
      return i;
    }
    else if (str[i] >= '0' && str[i] <= '9')
    {   
        if(str[i] == '0')
        {
            i = ft_zero(i, str, print_list);
            return i;
        }  
        else
        {
            i = ft_space(i, str, print_list);
            return i;
        }
    }
    else if(str[i] == '.')
    {
        i = ft_point(i, str, print_list);
        return i;
    }
    else
        ft_type(str[i], print_list);
    return i;
}

int     ft_analyse(int i, const char *str, va_list print_list)
{
    i = ft_flag(i, str, print_list);
    
    return i;
}

int ft_all( const char *str, va_list print_list)
{
    int i;

    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] == '%' && str[i + 1] == '%')
            ft_putchar('%', 0);
        if(str[i] != '%')
            ft_putchar(str[i], 0);
        else
            i = ft_analyse(i + 1, str, print_list);
        
        
        i++;
    }

    return i;
}

int     ft_printf(const char *str, ...)
{
    int count;
    int ret;
    int result;
    result = 0;
	va_list		print_list;

	va_start(print_list, str);
    ft_all( str, print_list);
    count = ft_putchar('a', 1);
    ret = ft_putstr("a", 1);
    result = count + ret;
    printf("\n");
    va_end(print_list);
	return result;
}

int main ()
{



    printf("\n\n----------NUMBERS----------\n\n");

    ft_printf("AKCLy%012uf", -14);
    printf("AKCLy%012uf", -14);

    return 0;
} 