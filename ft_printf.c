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

int     ft_choose(int i, const char *str)
{
    int test;
    
    test = ft_test_squeeze(i, str);
    if (test == 1)
        return 1;
    if(str[i] == '0')
        return 0;
    return 1;
}
int    ft_flag(int i, const char *str, va_list print_list)
{
    int test;
    int zero;

    if(str[i] == '-')
    {
        test = ft_test_squeeze(i + 1, str);
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
    else if (str[i] >= '0' && str[i] <= '9')
    {   
        zero = ft_choose(i, str);
        if(zero == 1)
        {
            test = ft_test_squeeze(i, str);
            if (test == 1)
            {
                i = ft_test_spec(i, str, print_list);
                return i;
            }
            i = ft_space(i, str, print_list);
            return i;
        }
        else if(zero != 1)
        {   
            while(str[i] == '0')
                i++;
            if (str[i] == '*')
                i = ft_zero_star(i, str, print_list);
           else
                i = ft_zero(i, str, print_list);
            return i;
        }
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
        test = ft_test_squeeze(i, str);
        if (test == 1)
        {
            i = ft_test_spec(i, str, print_list);
            return i;
        }
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

/*int main ()
{



    printf("\n\n----------NUMBERS----------\n\n");

    ft_printf("%.1s%*i%2dnZNzJigntfWNJ", NULL, -10, 2147483647, 2147483647);
    printf("%.1s%*i%2dnZNzJigntfWNJ", NULL, -10, 2147483647, 2147483647);





Diff for printf("%*sNLlX7u6p3fke5Ta", -10, "");
  printf: |          NLlX7u6p3fke5Ta-- 25 --|
ftprintf: |NLlX7u6p3fke5Ta-- 15 --|

Diff for printf("%-17.1s%-cvNxsOM9K4", NULL, '\0');
  printf: |(                vNxsOM9K4-- 27 --|
ftprintf: |(          vNxsOM9K4-- 21 --|

Diff for printf("%%26gQxNNA%*Xgg8PeyLtvSrb5DR%c", -9, 2147483647, 'D');
  printf: |%26gQxNNA7FFFFFFF gg8PeyLtvSrb5DRD-- 34 --|
ftprintf: |%26gQxNNA7FFFFFFFgg8PeyLtvSrb5DRD-- 33 --|

Diff for printf("nG6L%0.*u%-i%016.*dfzL2l", 4, 2147483647, 2147483647, -2, -2147483647);
  printf: |nG6L21474836472147483647-000002147483647fzL2l-- 45 --|
ftprintf: |nG6L21474836472147483647     -2147483647fzL2l-- 45 --|

Diff for printf("%-3XP%-13.*iupoaqvHyDI%%%18X%08u", -434915681, -6, 2147483647, -2147483647, 2147483647);
  printf: |E613B69FP2147483647   upoaqvHyDI%          800000012147483647-- 61 --|
ftprintf: |E613B69FP2147483647          upoaqvHyDI%          800000012147483647-- 68 --|

Diff for printf("%.3x%-12x%17.*sg27Lj%%aina", -10117281, -865060806, -4, NULL);
  printf: |ff659f5fcc70383a               (null)g27Lj%aina-- 47 --|
ftprintf: |ff659f5fcc70383a                         (null)g27Lj%aina-- 57 --|

Diff for printf("X%0*x", -10, 2147483647);
  printf: |X7fffffff  -- 11 --|
ftprintf: |X7fffffff-- 9 --|

Diff for printf("%-*.0xVzFfdgP60qJP%013.*iAlhxvf7%0.0u%0.1X", -1, 0, -9, 2147483647, 1480183496, -2147483647);
  printf: | VzFfdgP60qJP0002147483647Alhxvf7148018349680000001-- 51 --|
ftprintf: | VzFfdgP60qJP   2147483647Alhxvf7148018349680000001-- 51 --|

Diff for printf("A8yDj%019x%-.3s", 0, "");
  printf: |A8yDj0000000000000000000-- 24 --|
ftprintf: |A8yDj0000000000000000000 -- 25 --|

Diff for printf("3%-*.2dTC%xUm%*d", 3, 0, 2147483647, 9, 427710461);
  printf: |300 TC7fffffffUm427710461-- 25 --|
ftprintf: |300TC7fffffffUm427710461-- 24 --|

Diff for printf("%-6iZ9ipf%u%11.0u%0.3XAX r1ARS", 0, 2147483647, -2147483647, 0);
  printf: |0     Z9ipf2147483647 2147483649000AX r1ARS-- 43 --|
ftprintf: |0     Z9ipf21474836472147483649000AX r1ARS-- 42 --|

Diff for printf("8EUwX%3.0i%-12.1s%*iD%03.4i%03dW9pqR", -2147483647, NULL, 4, -2147483647, 0, -2147483647);
  printf: |8EUwX-2147483647(           -2147483647D0000-2147483647W9pqR-- 60 --|
ftprintf: |8EUwX-2147483647(     -2147483647D0000-2147483647W9pqR-- 54 --|

Diff for printf("%03.2i%01XVh Ge%d%-5.2d%16sf3N%xsN85", 0, 0, -1626352288, 0, "", -2147483647);
  printf: | 000Vh Ge-162635228800                   f3N80000001sN85-- 56 --|
ftprintf: | 000Vh Ge-162635228800                f3N80000001sN85-- 53 --|

Diff for printf("vONyasJ%i0Qx%16.*xBBup", 0, -6, 0);
  printf: |vONyasJ00Qx               0BBup-- 31 --|
ftprintf: |vONyasJ00Qx                BBup-- 31 --|

Diff for printf("%4cBwW8PRbe4o94rLq %*d%x", '\0', -9, 0, 0);
  printf: |   BwW8PRbe4o94rLq 0        0-- 30 --|
ftprintf: |   BwW8PRbe4o94rLq 00-- 22 --|

Diff for printf("%-15.0d%0*.3X%-14c%%izyJ%-7.4s", -980656664, -9, -2147483647, 'h', NULL);
  printf: |-980656664     80000001 h             %izyJ(nul   -- 50 --|
ftprintf: |-980656664 80000001h             %izyJ(nul-- 42 --|

Diff for printf("taq5%-2XKU2UB%9d%*s2qx", 0, 2147483647, -8, NULL);
  printf: |taq50 KU2UB2147483647(null)  2qx-- 32 --|
ftprintf: |taq50 KU2UB2147483647(null)2qx-- 30 --|

Diff for printf("X%18.*X3%3.*s%%%-cwaYm%.3u", 7, 390736792, -5, NULL, 'n', 0);
  printf: |X          174A2B983(null)%nwaYm000-- 35 --|
ftprintf: |X          174A2B983        (null)%nwaYm000-- 43 --|

Diff for printf(" HUBq5hWTD%-20.4saKqjjh%0.1d%-*i%-.4i", NULL, -2147483647, 10, 0, 0);
  printf: | HUBq5hWTD(nul                aKqjjh-21474836470         0000-- 61 --|
ftprintf: | HUBq5hWTD(nul          aKqjjh-21474836470         0000-- 55 --|

Diff for printf("%.2dbv0SF%c%*x%10c%-9sc Gz4uCOBY", 2147483647, '\0', -2, 0, 'n', NULL);
  printf: |2147483647bv0SF0          n(null)   c Gz4uCOBY-- 47 --|
ftprintf: |2147483647bv0SF0         n(null)   c Gz4uCOBY-- 46 --|

Diff for printf("%0i%-*cifXvXZH7VNc%%%*.*s qt", -2147483647, -4, '\0', 10, -2, "");
  printf: |-2147483647   ifXvXZH7VNc%           qt-- 40 --|
ftprintf: |-2147483647   ifXvXZH7VNc%             qt-- 42 --|

Diff for printf("9 gF4%sgd5%-.1u%-*.5d%-9.5XnpPuV%-.3i3rNFU", NULL, -2016250990, -10, 473865453, -895578000, 0);
  printf: |9 gF4(null)gd52278716306473865453 CA9E9070 npPuV0003rNFU-- 56 --|
ftprintf: |9 gF4(null)gd52278716306473865453CA9E9070 npPuV0003rNFU-- 55 --|

Diff for printf("mBnew%-3.3s4TVBA", "");
  printf: |mBnew   4TVBA-- 13 --|
ftprintf: |mBnew 4TVBA-- 11 --|

Diff for printf("eIlc%5.5saS", "");
  printf: |eIlc     aS-- 11 --|
ftprintf: |eIlc aS-- 7 --|

Diff for printf("u%-16.3iPnhKVo9%%%-.0s4", -2147483647, "");
  printf: |u-2147483647     PnhKVo9%4-- 26 --|
ftprintf: |u-2147483647         PnhKVo9% 4-- 31 --|

Diff for printf("%-19X%-d%-3.0sMUKKkaupwq971X4S", 948297471, 0, "");
  printf: |3885DEFF           0   MUKKkaupwq971X4S-- 39 --|
ftprintf: |3885DEFF           0 MUKKkaupwq971X4S-- 37 --|

Diff for printf("%-12.*iIaKVfEYihN4UR", 9, 0);
  printf: |000000000   IaKVfEYihN4UR-- 25 --|
ftprintf: |000000000IaKVfEYihN4UR-- 22 --|

Diff for printf("ze%-2.0sroQ", "vrf08lDVmGGQdivZStdD4Z");
  printf: |ze  roQ-- 7 --|
ftprintf: |zeroQ-- 5 --|

Diff for printf("%-*.5sI7GV8o%6c%c%.1du5fjA%X%-19.3x", -9, "", '\0', '\0', 103290513, 2147483647, 18372078);
  printf: |         I7GV8o     103290513u5fjA7FFFFFFF11855ee            -- 63 --|
ftprintf: | I7GV8o     103290513u5fjA7FFFFFFF11855ee            -- 55 --|

    return 0;
}*/