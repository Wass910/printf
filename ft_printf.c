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
        ft_putchar('0');
        return;
    }
    if(c == 'x')
        ft_putstr(ft_itoa_x(nb, 1));
    else
        ft_putstr(ft_itoa_x(nb, 2)); 
    return ;
}

char     *ft_adress(void *adress)
{
    char *dest;
    
    dest = ft_itoa_u((intptr_t)adress, 16);
    write(1, "0x", 2);
    ft_putstr(dest);
    return dest;
}

void     ft_type(char type, va_list print_list)
{
    if(type == 'd' || type == 'i')
        ft_putstr(ft_itoa(va_arg(print_list, int), 10));
    else if(type == 'c')
        ft_putchar(va_arg(print_list, int));
    else if(type == 's')
        ft_putstr(va_arg(print_list, char*));
    else if(type == 'u')
        ft_putstr(ft_itoa_u(va_arg(print_list,unsigned int), 10));
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
    if(str[i] > '0' && str[i] <= '9')
    {
        i = ft_space(i, str, print_list);
        return i;
    }
    else if(str[i] == '0')
    {    
        i = ft_zero(i, str, print_list);
        return i;
    }
    else if(str[i] == '.')
    {
        i = ft_point(i, str, print_list);
        return i;
    }
    /*else if(str[i] == '*')
        ft_putstr(ft_itoa(va_arg(print_list, int), 10));
*/
    else
        ft_type(str[i], print_list);
    return i;
}

int     ft_analyse(int i, const char *str, va_list print_list)
{
    i = ft_flag(i, str, print_list);
    
    return i;
}

int ft_all(int count, const char *str, va_list print_list)
{
    int i;

    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] == '%' && str[i + 1] == '%')
            ft_putchar('%');
        if(str[i] != '%')
            ft_putchar(str[i]);
        else
            i = ft_analyse(i + 1, str, print_list);
        i++;
    }

    return 0;
}

int     ft_count_pourcent(const char *str)
{
    int i;
    int count;

    count = 0;
    i = 0;
    while(str[i] != '\0')
    {
        if (str[i] == '%' && str[i + 1] != '%')
            count++;
        i++;
    } 
    return count;
}

int     ft_printf(const char *str, ...)
{
	va_list		print_list;
    int         count;

	va_start(print_list, str);
    count = ft_count_pourcent(str);
    ft_all(count, str, print_list);
    printf("\n");
    va_end(print_list);
	return 0;
}

int main ()
{
    char s2[] = "Voici l'operation :";
	char c = 'a';
	int *ptr ;

    printf("\n\n----------NUMBERS----------\n\n");

	ft_printf("salut %2s  p\n",  s2);
	printf("salut %2s  p\n\n",  s2);

    /*ft_printf("%0015d|\n",50);
	printf("%0015d|\n\n",50);

	ft_printf("%.010d|\n",50);
	printf("%.010d|\n\n",50);

	ft_printf("%-45d|\n", 50);
	printf("%-45d|\n\n", 50);

	ft_printf("%0023d|\n", 50);
	printf("%0023d|\n\n", 50);

	ft_printf("%.23d|\n", 50);
	printf("%.23d|\n\n", 50);

	ft_printf("%d|\n", 50);
	printf("%d|\n\n", 50);

	ft_printf("%-100d  p\n",50);
	printf("%-100d  p\n\n",50);

	ft_printf("%.010d|\n",50);
	printf("%.010d|\n\n",50);

	ft_printf("%d|\n", 50);
	printf("%d|\n\n", 50);

	ft_printf("%021d|\n", 50);
	printf("%021d|\n\n",50);


	ft_printf("%.10s|\n", s2);
	printf("%.10s|\n\n", s2);

 	ft_printf("%-10s|\n", s2);
	printf("%-10s|\n\n", s2);

	ft_printf("%.010s|\n", s2);
	printf("%.010s|\n\n", s2);

	ft_printf("%.40s|\n", s2);
	printf("%.40s|\n\n", s2);

	ft_printf("%-40s|\n", s2);
	printf("%-40s|\n\n", s2);

	ft_printf("%.40s|\n", s2);
	printf("%.40s|\n\n", s2);

	ft_printf("%.040s|\n", s2);
	printf("%.040s|\n\n", s2);

	ft_printf("%s|\n",  s2);
	printf("%s|\n\n",  s2);

	ft_printf("%.50s|\n", s2);
	printf("%.50s|\n\n", s2);

 	ft_printf("%-50s|\n", s2);
	printf("%-50s|\n\n", s2);

	ft_printf("%.5s|\n", s2);
	printf("%.5s|\n\n", s2);

	ft_printf("%.050s|\n", s2);
	printf("%.050s|\n\n", s2);

    ft_printf("%-10c|\n", c);
	printf("%-10c|\n\n", c);

	ft_printf("%-50c|\n", c);
	printf("%-50c|\n\n", c);

	ft_printf("%-2c|\n", c);
	printf("%-2c|\n\n", c);
	
    ft_printf("salut ca va %x  p\n",  -1);
	printf("salut ca va %x  p\n\n",  -1);

    ft_printf("hey %x  p\n",  -1);
	printf("hey %x  p\n\n",  -1);

    ft_printf("hey %-1x  p\n",  -1);
	printf("hey %-1x  p\n\n",  -1);

    ft_printf("hey %-2x  p\n",  -1);
	printf("hey %-2x  p\n\n",  -1);

    ft_printf("azer %-3x  p\n",  -1);
	printf("azer %-3x  p\n\n",  -1);

    ft_printf("azer %-10x  p\n",  -1);
	printf("azer %-10x  p\n\n",  -1);

    ft_printf("ok toi %-15x  p\n",  -1);
	printf("ok toi %-15x  p\n\n",  -1);

    ft_printf("sisi bg%-9x  p\n",  -1);
	printf("sisi bg%-9x  p\n\n",  -1);

    ft_printf("popo %-19x  p\n",  -1);
	printf("popo %-19x  p\n\n",  -1);

    ft_printf("%d|\n",  -1);
	printf("%d|\n\n",  -1);

    ft_printf("%d|\n",  -1);
	printf("%d|\n\n",  -1);

    ft_printf("%d|\n",  -1);
	printf("%d|\n\n",  -1);


    ft_printf("%d|\n",  -1);
	printf("%d|\n\n",  -1);


    ft_printf("%d|\n",  -1);
	printf("%d|\n\n",  -1);

    ft_printf("%d|\n",  -1);
	printf("%d|\n\n",  -1);
*/
    return 0;
}