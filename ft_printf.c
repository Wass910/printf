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
    va_end(print_list);
	return result;
}

/*int main ()
{



    printf("\n\n----------NUMBERS----------\n\n");

    ft_printf("%0i%-*cifXvXZH7VNc%%%*.*s qt", -2147483647, -4, '\0', 10, -2, "");
    printf("%0i%-*cifXvXZH7VNc%%%*.*s qt", -2147483647, -4, '\0', 10, -2, "");



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

Diff for printf("nNO%XZv8bDGgPk%.4u%-d%-.0x%2.3s", -2147483647, 0, -2147483647, 2147483647, "");
  printf: |nNO80000001Zv8bDGgPk0000-21474836477fffffff  -- 45 --|
ftprintf: |nNO80000001Zv8bDGgPk0000-21474836477fffffff-- 43 --|

Diff for printf("WNWMFV%12ds4ff%12.5x0zP%-.5u", 2147483647, 0, -113083913);
  printf: |WNWMFV  2147483647s4ff       000000zP4181883383-- 47 --|
ftprintf: |WNWMFV  2147483647s4ff       00000000zP4181883383-- 49 --|

Diff for printf("%-c%-4.1sJt%*.1dw%.2i%.*u%-c%s%*c", '\0', "ZyZgmqK1I076kpzxGEAcQYAYVEKZJEMCuKE OYa7Vosl iHRIjvrH9LLeErJlBUKB9X5EJ0O3a", -4, 2147483647, -2147483647, 3, 2147483647, 'n', "", -10, '\0');
  printf: |Z   Jt2147483647w-21474836472147483647n         -- 50 --|
ftprintf: |Z   Jt2147483647w-21474836472147483647n         -- 50 --|

Diff for printf("jcY7m%%%15.*u%*.5s", -1, 0, 4, "RiOqeB S5MiAJIhWLlz5WBqDerKXCuVFwPzTxyCw5sephnWZL72GnQRU");
  printf: |jcY7m%              0RiOqe-- 26 --|
ftprintf: |jcY7m%               RiOqe-- 26 --|

Diff for printf("XjdnaeVWUOBOJf3u5BeWN%0.*d", -1, 0);
  printf: |XjdnaeVWUOBOJf3u5BeWN0-- 22 --|
ftprintf: |XjdnaeVWUOBOJf3u5BeWN-- 21 --|

Diff for printf("Rp6gnd%0X%-16.*d", 2147483647, 4, -2147483647);
  printf: |Rp6gnd7FFFFFFF-2147483647     -- 30 --|
ftprintf: |Rp6gnd7FFFFFFF-2147483647               -- 40 --|

Diff for printf("%*.3X6lwD%-.*dEmh1gG", -6, 0, 7, -2147483647);
  printf: |000   6lwD-2147483647Emh1gG-- 27 --|
ftprintf: |      6lwD-2147483647Emh1gG-- 27 --|

Diff for printf("%%%13.1X%dtHidy", 0, 1147949756);
  printf: |%            01147949756tHidy-- 29 --|
ftprintf: |%            0001147949756tHidy-- 31 --|

Diff for printf("%-12i%15c%.0d%*.*sR3 8%-8x%cA0Zt%014X%%", 2147483647, 'i', 0, -2, -4, "WQQiaZTAd9WWbjBkMMhZfOcO6UQo 9J3rO1sXYHB1IkTADCxuxljHhGr3gtU", 0, '\0', 2147483647);
  printf: |2147483647                iWQQiaZTAd9WWbjBkMMhZfOcO6UQo 9J3rO1sXYHB1IkTADCxuxljHhGr3gtUR3 80       A0Zt0000007FFFFFFF%-- 119 --|
ftprintf: |2147483647                i0WQQiaZTAd9WWbjBkMMhZfOcO6UQo 9J3rO1sXYHB1IkTADCxuxljHhGr3gtUR3 80       A0Zt0000007FFFFFFF%-- 120 --|

Diff for printf("QP%%%0.*x%-*c", 9, 0, -10, '\0');
  printf: |QP%000000000         -- 22 --|
ftprintf: |QP%00000000000         -- 24 --|

Diff for printf("brqhNt%.*X%s%-.*dWb4X%-13svsOZW%-.2dPhdCo", -8, 0, NULL, 3, 0, "", 0);
  printf: |brqhNt0(null)000Wb4X             vsOZW00PhdCo-- 45 --|
ftprintf: |brqhNt0       (null)000Wb4X             vsOZW00PhdCo-- 52 --|

Diff for printf("%0*ik1IZiSIl%-cBWf2e%12.*i", 1, 229624029, 'd', -9, -1287288180);
  printf: |229624029k1IZiSIldBWf2e -1287288180-- 35 --|
ftprintf: |229624029k1IZiSIldBWf2e-01287288180-- 35 --|

Diff for printf("%*c%-*.2i9Pj%0x", -9, '\0', -2, -2147483647, 0);
  printf: |        -21474836479Pj0-- 24 --|
ftprintf: |        -21474836479Pj0-- 24 --|

Diff for printf("YX%-.*u%-.*x%014.0X%-7u%-X", 4, 0, 4, -2147483647, 0, 0, 920900513);
  printf: |YX000080000001              0      36E3D3A1-- 43 --|
ftprintf: |YX000080000001              000      36E3D3A1-- 45 --|

Diff for printf("T%11.3iA TtMMbkrgzdpCM%%%*.4d%0.0X", -440211868, -7, 0, -2147483647);
  printf: |T -440211868A TtMMbkrgzdpCM%0000   80000001-- 43 --|
ftprintf: |T -440211868A TtMMbkrgzdpCM%   000080000001-- 43 --|

Diff for printf("%-4X%u9%*d%06x%cCPc2IjOcn%0*.0u", 2147483647, 1394836567, -9, -2147483647, 2147483647, 'o', 5, 0);
  printf: |7FFFFFFF13948365679-21474836477fffffffoCPc2IjOcn     -- 53 --|
ftprintf: |7FFFFFFF1394836567921474836477fffffffoCPc2IjOcn     -- 52 --|

Diff for printf("%X%11.*XgoXkCnMgIEOlQwQ3s3S%.5u1", 2147483647, 1, 0, 2147483647);
  printf: |7FFFFFFF          0goXkCnMgIEOlQwQ3s3S21474836471-- 49 --|
ftprintf: |7FFFFFFF          000goXkCnMgIEOlQwQ3s3S21474836471-- 51 --|

Diff for printf("%018.2XDviioL%0*.1x%%yUQhW7Z%s", 0, 0, 0, NULL);
  printf: |                00DviioL0%yUQhW7Z(null)-- 39 --|
ftprintf: |                0000DviioL000%yUQhW7Z(null)-- 43 --|

Diff for printf("%-xyR8xpd%-20.2isa41%9.*x", 197068997, 2147483647, -8, -2147483647);
  printf: |bbf08c5yR8xpd2147483647          sa41 80000001-- 46 --|
ftprintf: |bbf08c5yR8xpd2147483647                    sa41 80000001-- 56 --|

Diff for printf("%0.0X%-.4x%019.2i%.*x%.2x%02.4XcLi0", 547349387, -2028470603, -1670158724, 4, 2147483647, 1370230430, 0);
  printf: |209FE38B8717feb5        -16701587247fffffff51ac0e9e0000cLi0-- 59 --|
ftprintf: |209FE38B8717feb5        -16701587247fffffff51ac0e9e000000cLi0-- 61 --|

Diff for printf("%x%-3.*i%018.4x9%d", -1851123297, -5, -2147483647, 0, -1489058272);
  printf: |91aa199f-2147483647              00009-1489058272-- 49 --|
ftprintf: |91aa199f-2147483647              0000009-1489058272-- 51 --|

Diff for printf("%.0d7Obk8e%*cji%.1i%-1cM4e2n", 144875411, -8, '\0', -422741636, 'l');
  printf: |1448754117Obk8e       ji-422741636lM4e2n-- 41 --|
ftprintf: |1448754117Obk8e       ji-422741636lM4e2n-- 41 --|

Diff for printf("%019.*X8Phxw%%%07x3jfI%-4.5xQON9t", -7, 0, 0, 2147483647);
  printf: |00000000000000000008Phxw%00000003jfI7fffffffQON9t-- 49 --|
ftprintf: |                   08Phxw%00000003jfI7fffffffQON9t-- 50 --|

Diff for printf("J7FeWNXmp%c%-.2s%-14c%12s%c%.*x%5.0d", 'i', "uaqCTywM1y6P7Q0pd2m1EapdwDO", '\0', NULL, 'B', -10, -2147483647, 1460423583);
  printf: |J7FeWNXmpiua                   (null)B800000011460423583-- 57 --|
ftprintf: |J7FeWNXmpiua                   (null)B80000001  1460423583-- 59 --|

Diff for printf("G9YWE%-XmKxwU%%%0.3X%.0u%01.5u%19.0i", -2147483647, 0, 0, 2147483647, -2147483647);
  printf: |G9YWE80000001mKxwU%0002147483647        -2147483647-- 51 --|
ftprintf: |G9YWE80000001mKxwU%0000002147483647        -2147483647-- 54 --|

Diff for printf("QXU%c%.1X%.0s5ZIQC%19u%dQn%010.*X", 'k', -1555775974, "ICqd6RodQCbkkvJ5 eBwTIFAeNNXiC", 0, -918156865, -9, -2147483647);
  printf: |QXUkA344BE1A5ZIQC                  0-918156865Qn0080000001-- 58 --|
ftprintf: |QXUkA344BE1A5ZIQC                  0-918156865Qn  80000001-- 58 --|

Diff for printf("Sbe%020.*X%03.3u%-XVx", -8, 2147483647, -2147483647, -2147483647);
  printf: |Sbe0000000000007FFFFFFF214748364980000001Vx-- 43 --|
ftprintf: |Sbe            7FFFFFFF214748364980000001Vx-- 43 --|

Diff for printf("%%%10.0XuvDN%1cUpGt%%icrRgL", 0, '\0');
  printf: |%          uvDNUpGt%icrRgL-- 27 --|
ftprintf: |%          00uvDNUpGt%icrRgL-- 29 --|

Diff for printf("%.*x SL65RLK", -9, 2147483647);
  printf: |7fffffff SL65RLK-- 16 --|
ftprintf: |7fffffff  SL65RLK-- 17 --|

Diff for printf("%4.2X%%%-16uzHO%-15cDfneB8Ln7%cct9VA", 0, -2147483647, '\0', '\0');
  printf: |  00%2147483649      zHO              DfneB8Ln7ct9VA-- 54 --|
ftprintf: |  0000%2147483649      zHO              DfneB8Ln7ct9VA-- 56 --|

Diff for printf("SUW%i%0.0xkXO%-*soOLULqot%*.0s", 2147483647, 2147483647, -4, NULL, -6, "");
  printf: |SUW21474836477fffffffkXO(null)oOLULqot      -- 44 --|
ftprintf: |SUW21474836477fffffffkXO(null)oOLULqot-- 38 --|

Diff for printf("%XqOKs yZkpjLrk5j%*c4SA", 2147483647, -7, '\0');
  printf: |7FFFFFFFqOKs yZkpjLrk5j      4SA-- 33 --|
ftprintf: |7FFFFFFFqOKs yZkpjLrk5j      4SA-- 33 --|

Diff for printf("bJ%0*.2u%-c%-18.5ilv4btM%-ulvtS%.*d", -2, 0, 'L', 2147483647, 2147483647, -8, -2147483647);
  printf: |bJ00L2147483647        lv4btM2147483647lvtS-2147483647-- 54 --|
ftprintf: |bJ00L2147483647                  lv4btM2147483647lvtS-2147483647-- 64 --|

Diff for printf("nf21zJ7pIZk%sPGHT%4.0x", "jNijupOBd", 0);
  printf: |nf21zJ7pIZkjNijupOBdPGHT    -- 28 --|
ftprintf: |nf21zJ7pIZkjNijupOBdPGHT    00-- 30 --|

Diff for printf("%06.0x", 0);
  printf: |      -- 6 --|
ftprintf: |      00-- 8 --|

Diff for printf("%014.*u%-.*X", -5, 2147483647, 3, 0);
  printf: |00002147483647000-- 17 --|
ftprintf: |    2147483647000-- 17 --|

Diff for printf("%.0iAJ%.*u%%%-*.0u%01.2u%-*uBgj8I%-.2x", 0, 5, 0, -5, 2147483647, 1507377032, 7, 2147483647, -2147483647);
  printf: |AJ00000%214748364715073770322147483647Bgj8I80000001-- 51 --|
ftprintf: |0AJ00000%214748364715073770322147483647Bgj8I80000001-- 52 --|

Diff for printf(" KOVc%.3Xdi%013X%-10.*xnE8 hB%07.5d", 2147483647, 0, -6, 0, 2147483647);
  printf: | KOVc7FFFFFFFdi00000000000000         nE8 hB2147483647-- 54 --|
ftprintf: | KOVc7FFFFFFFdi00000000000000          nE8 hB2147483647-- 55 --|

Diff for printf("%3Xp%017.*xxjLApjfXQ%%", 302539795, -4, 0);
  printf: |12086413p00000000000000000xjLApjfXQ%-- 36 --|
ftprintf: |12086413p                 0xjLApjfXQ%-- 37 --|

Diff for printf("%*c6EKb1EOddmq0", -6, 'D');
  printf: |D     6EKb1EOddmq0-- 18 --|
ftprintf: |     D6EKb1EOddmq0-- 18 --|

Diff for printf("%2.0xKH%-cqgfDx175u%14sAG", 0, '2', "");
  printf: |  KH2qgfDx175u              AG-- 30 --|
ftprintf: |  00KH2qgfDx175u              AG-- 32 --|

Diff for printf("%-16.*xS", -2, 0);
  printf: |0               S-- 17 --|
ftprintf: |0                S-- 18 --|

Diff for printf("sSD7%-c%2.3saTcOthudd%02.5dm93", '\0', "", 0);
  printf: |sSD7  aTcOthudd00000m93-- 24 --|
ftprintf: |sSD7aTcOthudd00000m93-- 22 --|

Diff for printf("9%12.2XwAnon%0dtrPDig", 0, 2147483647);
  printf: |9          00wAnon2147483647trPDig-- 34 --|
ftprintf: |9          0000wAnon2147483647trPDig-- 36 --|

Diff for printf("%011.0X%0.1x2e izWiYI1f5oRuO08agfo%19.0xuURg4", 0, -2147483647, -2147483647);
  printf: |           800000012e izWiYI1f5oRuO08agfo           80000001uURg4-- 65 --|
ftprintf: |           00800000012e izWiYI1f5oRuO08agfo           80000001uURg4-- 67 --|

Diff for printf("%cdd5eL%-.2x8xrLVdRssHp%.1d%0.2x", '\0', -2147483647, -2147483647, 0);
  printf: |dd5eL800000018xrLVdRssHp-214748364700-- 38 --|
ftprintf: |dd5eL800000018xrLVdRssHp-21474836470000-- 40 --|

Diff for printf("sgk6%-7i%-17.3dE%-*xfK ", -2147483647, -185722976, -4, 2147483647);
  printf: |sgk6-2147483647-185722976       E7ffffffffK -- 44 --|
ftprintf: |sgk6-2147483647-185722976                E7ffffffffK -- 53 --|

Diff for printf("%3.1xy", 0);
  printf: |  0y-- 4 --|
ftprintf: |  000y-- 6 --|

Diff for printf("%-14.1dNpH%-12.5u", 485131452, 0);
  printf: |485131452     NpH00000       -- 29 --|
ftprintf: |485131452              NpH00000       -- 38 --|

Diff for printf("%0.1xfzqXyFwK%*i", 0, 1, 1760255985);
  printf: |0fzqXyFwK1760255985-- 19 --|
ftprintf: |000fzqXyFwK1760255985-- 21 --|

Diff for printf("%-11.*d%0*.*d", -10, 0, -7, -5, -2147483647);
  printf: |0          -2147483647-- 22 --|
ftprintf: |0           -2147483647-- 23 --|

Diff for printf("Be%-6c%05.2iFNwi%c3aTpzeDdLMbPWVcMm%7.4X", '4', 0, '\0', 0);
  printf: |Be4        00FNwi3aTpzeDdLMbPWVcMm   0000-- 42 --|
ftprintf: |Be4        00FNwi3aTpzeDdLMbPWVcMm   000000-- 44 --|

Diff for printf("%013.*XSHcs", -3, -555776862);
  printf: |00000DEDF84A2SHcs-- 17 --|
ftprintf: |     DEDF84A2SHcs-- 17 --|

Diff for printf("0oqvo%%Z%0*.5XbMraQAP2OH%.0s", -4, 0, "unQaPYOH8wH66a29Wn8");
  printf: |0oqvo%Z00000bMraQAP2OH-- 22 --|
ftprintf: |0oqvo%Z    bMraQAP2OH-- 21 --|

Diff for printf("AzR0R%*c", -5, '\0');
  printf: |AzR0R    -- 10 --|
ftprintf: |AzR0R    -- 10 --|

Diff for printf("IS%07.*u", -10, 0);
  printf: |IS0000000-- 9 --|
ftprintf: |IS       -- 9 --|

Diff for printf("%*ctksU%.*dSplAT%-s%0.*X", 4, 'Y', 10, -1216340406, "", 3, 0);
  printf: |   YtksU-1216340406SplAT000-- 27 --|
ftprintf: |   YtksU-1216340406SplAT00000-- 29 --|

Diff for printf("tL1sa8 qb%0*.4XAZGOb9lbuj%-s", -7, 0, NULL);
  printf: |tL1sa8 qb0000   AZGOb9lbuj(null)-- 32 --|
ftprintf: |tL1sa8 qb       AZGOb9lbuj(null)-- 32 --|

Diff for printf("vOLSPEVQn%*uBnbyvU8KIFbb%%", -7, 0);
  printf: |vOLSPEVQn0      BnbyvU8KIFbb%-- 29 --|
ftprintf: |vOLSPEVQn      0BnbyvU8KIFbb%-- 29 --|

Diff for printf("WdP3Sb%16.5d%*c%-x%-.4X%-.*uDANjU 7", -348136929, -3, '\0', 0, 0, -9, 0);
  printf: |WdP3Sb      -348136929  000000DANjU 7-- 38 --|
ftprintf: |WdP3Sb      -348136929  000000DANjU 7-- 38 --|

Diff for printf("05yhbx%*cX8RQJ4u%13cH jU%%eMGnfy", -5, '\0', '\0');
  printf: |05yhbx    X8RQJ4u            H jU%eMGnfy-- 42 --|
ftprintf: |05yhbx    X8RQJ4u            H jU%eMGnfy-- 42 --|
    return 0;
}*/