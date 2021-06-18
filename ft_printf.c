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

int ft_test(int i, const char *str)
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

void    ft_write_space(int nb)
{
    while(nb > 0)
    {
        ft_putchar(' ');
        nb--;
    }
    return ;
}

int     ft_point_d_squeeze(int nb, int space, int zer)
{
    char *dest;
    int lengh;
    int tmp;

    tmp = 0;
    if (nb == 0 && zer == 0)
    {
        while (space > 0)
        {
            ft_putchar(' ');
            space--;
        }
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
    if (nb < 0)
        tmp--;
    while(tmp > 0)
    {
        ft_putchar(' ');
        tmp--;
    }
    return 1;
}

int     ft_point_u_squeeze(unsigned int nb, int space, int zer)
{
    char *dest;
    int lengh;
    int tmp; 

    tmp = 0;
    if (nb == 0 && zer == 0)
    {
        while (space > 0)
        {
            ft_putchar(' ');
            space--;
        }
        return 1;
    }
    dest = ft_itoa_u(nb, 10);
    lengh = ft_strlen(dest);
    if (space > zer && zer > lengh)
        tmp = space - zer;
    else if (lengh > zer)
        tmp = space - lengh;
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

    tmp = 0;
    if (nb == 0 && zer == 0)
    {
        while (space > 0)
        {
            ft_putchar(' ');
            space--;
        }
        return 1;
    }
    dest = ft_itoa_x(nb, 10);
    lengh = ft_strlen(dest);
    if (space > zer && zer > lengh)
        tmp = space - zer;
    else if (lengh > zer)
        tmp = space - lengh;
    //printf("    %d     ", tmp);
    //if (zer == 0)
     //   tmp = tmp - lengh ;
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

int    ft_flag(int i, const char *str, va_list print_list)
{
    int test;

    if(str[i] == '-')
    {
        test = ft_test(i + 1, str);
        if (test == 1)
        {
            i = ft_squeeze(i + 1, str, print_list);
            return i;
        }
        if (str[i + 1] == '*')
            i = ft_tiret_star(i + 1, str, print_list);
        else
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
        while(str[i] == '0')
            i++;
        if (str[i] == '*')
            i = ft_zero_star(i, str, print_list);
        else
            i = ft_zero(i, str, print_list);
        return i;
    }
    else if(str[i] == '.')
    {
        if (str[i + 1] == '*')
            i = ft_point_star(i + 1, str, print_list);
        else
            i = ft_point(i, str, print_list);
        return i;
    }
    else if(str[i] == '*')
    {
        i = ft_space_star(i, str, print_list);
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

    ft_printf("salut %-*.14x  p\n",10,5);
    printf("salut %-*.14x  p\n\n", 10,5);

    /*ft_printf("salut %-*.*x  p\n",5, 0,   -50);
    printf("salut %-*.*x  p\n\n",5, 0,   -50);

    ft_printf("salut %-*.*x  p\n",20, 10,   0);
    printf("salut %-*.*x  p\n\n",20, 10,   0);

    ft_printf("salut %-*.*x  p\n",15, 0,   0);
    printf("salut %-*.*x  p\n\n",15, 0,   0);

    ft_printf("salut %-*.*x  p\n",11, 7,   -10);
	printf("salut %-*.*x  p\n\n", 11, 7, -10);

    ft_printf("salut %-*.*u  p\n",20, 20,   20);
    printf("salut %-*.*u  p\n\n",20, 20,   20);

    ft_printf("salut %-*.*u  p\n",0, 0,   20);
    printf("salut %-*.*u  p\n\n",0, 0,   20);

    ft_printf("salut %-*.*u  p\n",10, 20,   50);
    printf("salut %-*.*u  p\n\n",10, 20,   50);

    ft_printf("salut %-*.*d  p\n",5, 4,   3);
    printf("salut %-*.*d  p\n\n",5, 4,   3);

    ft_printf("salut %-*.*d  p\n",010, 0,   10);
    printf("salut %-*.*d  p\n\n",010, 0,   10);

    ft_printf("salut %-*.*d  p\n",5, 10,   5);
    printf("salut %-*.*d  p\n\n",5, 10,   5);

    ft_printf("salut %-*.*x  p\n",5, 3,   0);
    printf("salut %-*.*x  p\n\n",5, 3,   0);

    ft_printf("salut %-*.*x  p\n",0, 02,   0);
    printf("salut %-*.*x  p\n\n",0, 02,   0);

    ft_printf("salut %-*.*x  p\n",15, 0,   -5);
    printf("salut %-*.*x  p\n\n",15, 0,   -5);

    ft_printf("%0015d|\n",50);
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
	printf("popo %-19x  p\n\n",  -1);*/

    return 0;
}