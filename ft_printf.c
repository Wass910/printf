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

int main ()
{



    printf("\n\n----------NUMBERS----------\n\n");

    ft_printf("%-.*sYp oM%-11.*u%0X", -6, "5tsHk0B6xgAxWcY9oP8aAueJfwdnBKobKAJZzWxqOre45HOpzZ5DjpfLKkhd6l59gjwjyf0BoKLQZVsCPDx4og3TJgjwzeFG", -6, 0, -1422028796);
    printf("%-.*sYp oM%-11.*u%0X", -6, "5tsHk0B6xgAxWcY9oP8aAueJfwdnBKobKAJZzWxqOre45HOpzZ5DjpfLKkhd6l59gjwjyf0BoKLQZVsCPDx4og3TJgjwzeFG", -6, 0, -1422028796);

/*


Diff for printf("%-.*sYp oM%-11.*u%0X", -6, "5tsHk0B6xgAxWcY9oP8aAueJfwdnBKobKAJZzWxqOre45HOpzZ5DjpfLKkhd6l59gjwjyf0BoKLQZVsCPDx4og3TJgjwzeFG", -6, 0, -1422028796);
  printf: |5tsHk0B6xgAxWcY9oP8aAueJfwdnBKobKAJZzWxqOre45HOpzZ5DjpfLKkhd6l59gjwjyf0BoKLQZVsCPDx4og3TJgjwzeFGYp oM0          AB3D9004-- 120 --|
ftprintf: |5tsHk0B6xgAxWcY9oP8aAueJfwdnBKobKAJZzWxqOre45HOpzZ5DjpfLKkhd6l59gjwjyf0BoKLQZVsCPDx4og3TJgjwzeFGYp oM0           AB3D9004-- 121 --|

Diff for printf("AKCLy%.*xf", 3, 0);
  printf: |AKCLy000f-- 9 --|
ftprintf: |AKCLy0f-- 7 --|

Diff for printf("%011.*xAAS4%3.4unL", -8, -2147483647, -2147483647);
  printf: |00080000001AAS42147483649nL-- 27 --|
ftprintf: |   80000001AAS42147483649nL-- 27 --|

Diff for printf("%15ulw6XggDO%06.2x%d%c%.4X95EvC0boif", 0, -2147483647, 1757674600, 'n', 0);
  printf: |              0lw6XggDO800000011757674600n000095EvC0boif-- 56 --|
ftprintf: |              0lw6XggDO800000011757674600n0095EvC0boif-- 54 --|

Diff for printf("azr u2WrZ c %0*.5i", -10, 1758494537);
  printf: |azr u2WrZ c 1758494537-- 22 --|
ftprintf: |azr u2WrZ c 1758494537     -- 27 --|

Diff for printf("%.5sa%18.*iZv5UKwYeifB%*X%*.1sINgg2pSw", "", -5, -2147483647, 4, 2147483647, 3, NULL);
  printf: |a       -2147483647Zv5UKwYeifB7FFFFFFF  (INgg2pSw-- 49 --|
ftprintf: |a-00000002147483647Zv5UKwYeifB7FFFFFFF  (INgg2pSw-- 49 --|

Diff for printf("%cK%020.*XAV%-.5d%*u", 'l', -3, 2147483647, 0, 2, -2147483647);
  printf: |lK0000000000007FFFFFFFAV000002147483649-- 39 --|
ftprintf: |lK            7FFFFFFFAV000002147483649-- 39 --|

Diff for printf("dNN%%WiJNAyTJC%.0d%.1xjz2", -2147483647, 0);
  printf: |dNN%WiJNAyTJC-21474836470jz2-- 28 --|
ftprintf: |dNN%WiJNAyTJC-2147483647jz2-- 27 --|

Diff for printf("E%%%-1.3X%-6.2d%.2x", 0, 2147483647, 0);
  printf: |E%000214748364700-- 17 --|
ftprintf: |E%0002147483647-- 15 --|

Diff for printf("%%%5.*iDpSr3", -8, 0);
  printf: |%    0DpSr3-- 11 --|
ftprintf: |%00000DpSr3-- 11 --|

Diff for printf("%.3XuKUK", 0);
  printf: |000uKUK-- 7 --|
ftprintf: |0uKUK-- 5 --|

Diff for printf("%%%-7.4iD47%%%09x", 0, 0);
  printf: |%0000   D47%000000000-- 21 --|
ftprintf: |%0000  D47%000000000-- 20 --|

Diff for printf("%*.2i%7.3xh%i", -7, -1008206265, -2147483647, 1506728880);
  printf: |-100820626580000001h1506728880-- 30 --|
ftprintf: |-1008206265    80000001h1506728880-- 34 --|

Diff for printf("po1a3%.2X%d04pdap%-.*dw5O", 0, 2147483647, 0, 2147483647);
  printf: |po1a300214748364704pdap2147483647w5O-- 36 --|
ftprintf: |po1a3214748364704pdap2147483647w5O-- 34 --|

Diff for printf("%%yA%0*iKFf6%*.5x8DVTNJ%-1d", -2, 0, 7, -2147483647, 0);
  printf: |%yA0 KFf6800000018DVTNJ0-- 24 --|
ftprintf: |%yA0KFf6800000018DVTNJ0-- 23 --|

Diff for printf(" 7B9m%%%-*cfP16cvpmv%0.1ij2Qox%c%.3xsT", 8, '\0', 0, 'N', 0);
  printf: | 7B9m%       fP16cvpmv0j2QoxN000sT-- 35 --|
ftprintf: | 7B9m%       fP16cvpmv0j2QoxN0sT-- 33 --|

Diff for printf("n%0*.1dLXreE0%%fM4iIl%019.3da9zI%.4X", -3, 1621426016, 0, 0);
  printf: |n1621426016LXreE0%fM4iIl                000a9zI0000-- 51 --|
ftprintf: |n1621426016  LXreE0%fM4iIl                000a9zI00-- 51 --|

Diff for printf("qgYaq2swKdGJOr%.3xn2m%-4x", 0, 0);
  printf: |qgYaq2swKdGJOr000n2m0   -- 24 --|
ftprintf: |qgYaq2swKdGJOr0n2m0   -- 22 --|

Diff for printf("%.1x%-s%.4u%7d%-8.0uCL%16u%s", 0, NULL, 1908788002, 0, 0, 2147483647, "SGQ23KCb  sveHRLkmbN1ZnUw8phtnMiRaB0I5qPA");
  printf: |0(null)1908788002      0        CL      2147483647SGQ23KCb  sveHRLkmbN1ZnUw8phtnMiRaB0I5qPA-- 91 --|
ftprintf: |(null)1908788002      0        CL      2147483647SGQ23KCb  sveHRLkmbN1ZnUw8phtnMiRaB0I5qPA-- 90 --|

Diff for printf("%-iT76YqvBn%.4u%012.*uH%-.4x", 0, -2147483647, -3, 0, -1713752144);
  printf: |0T76YqvBn2147483649000000000000H99da37b0-- 40 --|
ftprintf: |0T76YqvBn2147483649           0H99da37b0-- 40 --|

Diff for printf("EZMerOm %20.5i%.1X1%.*xTR%0X", -2147483647, 0, -8, 0, -2147483647);
  printf: |EZMerOm          -2147483647010TR80000001-- 41 --|
ftprintf: |EZMerOm          -214748364710TR80000001-- 40 --|

Diff for printf("J%-11.5X%*.1sGDBiv%12c%0.*x", -2147483647, -3, NULL, '\0', -5, -2147483647);
  printf: |J80000001   (  GDBiv           80000001-- 40 --|
ftprintf: |J80000001   (GDBiv           80000001-- 38 --|

Diff for printf("1Nd6Q%.4sD%.0semrChjA9%0*.4i%0x%020.0d", NULL, "", -8, -2147483647, 0, 633626802);
  printf: |1Nd6Q(nulDemrChjA9-21474836470           633626802-- 50 --|
ftprintf: |1Nd6Q(nulDemrChjA9-2147483647   0           633626802-- 53 --|

Diff for printf("25HavxNnrC4%-2xMvAmt4yq%-1x%.4xJST", 279578806, -2147483647, 0);
  printf: |25HavxNnrC410aa08b6MvAmt4yq800000010000JST-- 42 --|
ftprintf: |25HavxNnrC410aa08b6MvAmt4yq8000000100JST-- 40 --|

Diff for printf("%17s%-19.*uSRdHdAvUa3Xok%-*cYZKj7", "", -3, 0, 10, '0');
  printf: |                 0                  SRdHdAvUa3Xok0         YZKj7-- 64 --|
ftprintf: |                 0                   SRdHdAvUa3Xok0         YZKj7-- 65 --|

Diff for printf("bW%%aQ51THD%-8.0sPXI6%0*.1dKTwD%%", "I0yYEeTeFRdXwJV Y4lOYYPDJjarUKepgLMtc12qLwgt992r4W4WBp7f8Oq1xgt89PlfDb2mLVboHry", -2, 2147483647);
  printf: |bW%aQ51THD        PXI62147483647KTwD%-- 37 --|
ftprintf: |bW%aQ51THD        PXI62147483647 KTwD%-- 38 --|

Diff for printf("%-12cS%-.1in4Tt%20.4X%-7.5d%0X", '\0', -150860633, 2147483647, 0, 0);
  printf: |           S-150860633n4Tt            7FFFFFFF00000  0-- 55 --|
ftprintf: |           S-150860633n4Tt            7FFFFFFF00000 0-- 54 --|

Diff for printf("w4HSd5zEmH3PG70%8xq%-9.3i8gH4u0gGg", -2147483647, 0);
  printf: |w4HSd5zEmH3PG7080000001q000      8gH4u0gGg-- 42 --|
ftprintf: |w4HSd5zEmH3PG7080000001q000     8gH4u0gGg-- 41 --|

Diff for printf("%8.4u%-.2i%-.4uo12%-17.*d%%%-20u1XCm2L", 2147483647, 2147483647, -1257571157, 5, 0, 2147483647);
  printf: |214748364721474836473037396139o1200000            %2147483647          1XCm2L-- 77 --|
ftprintf: |214748364721474836473037396139o1200000           %2147483647          1XCm2L-- 76 --|

Diff for printf("%%cg%-caSub2%% 11Yk8TY%-*d%0*.3i5", 'V', 4, 2147483647, -4, 1227544590);
  printf: |%cgVaSub2% 11Yk8TY214748364712275445905-- 39 --|
ftprintf: |%cgVaSub2% 11Yk8TY21474836471227544590 5-- 40 --|

Diff for printf("%017.1x%%%.3x%-iq0H1", 2147483647, 0, 188458921);
  printf: |         7fffffff%000188458921q0H1-- 34 --|
ftprintf: |         7fffffff%0188458921q0H1-- 32 --|

Diff for printf("hu%-7.*s%-*dPo%.*i%011xY%10.*Xkq", -7, NULL, 0, -2147483647, 6, 1208283227, -2147483647, -8, 2147483647);
  printf: |hu(null) -2147483647Po120828322700080000001Y  7FFFFFFFkq-- 56 --|
ftprintf: |hu(null)       -2147483647Po120828322700080000001Y  7FFFFFFFkq-- 62 --|

Diff for printf("%-*.4x%0ubjA7a%%HQS%.4XaLk2", 10, -1770809819, 2147483647, 0);
  printf: |96739625  2147483647bjA7a%HQS0000aLk2-- 37 --|
ftprintf: |96739625  2147483647bjA7a%HQS00aLk2-- 35 --|

Diff for printf("%0*.4iatM23 xlDdypU%-iZ5vpz%016.2x", -6, -373554333, -2147483647, 2147483647);
  printf: |-373554333atM23 xlDdypU-2147483647Z5vpz        7fffffff-- 55 --|
ftprintf: |-373554333 atM23 xlDdypU-2147483647Z5vpz        7fffffff-- 56 --|
*/


    return 0;
} 