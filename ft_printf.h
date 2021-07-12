#ifndef FT_printF_H
# define FT_printF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

typedef struct	s_list
{
	int				tiret;
	int				precision;
	int				precision_len;
	int				width;
	int				precision_parcing;
	int				width_parcing;
	int				zero;
}				t_list;

char	*ft_itoa(int n, int base);
char	*ft_itoa_u(long int n, int base);
char	*ft_itoa_x(long int n, int type_charac);
int		ft_atoi(char *nptr);
int		ft_strlen(char *s);
int		ft_putchar(char c, int n);
int		ft_putstr(char *s, int n);
char	*ft_strdup(const char *s);
int     ft_no_zer(int n);
int     ft_type_tiret(char type, va_list print_list);
int     ft_tiret(int i, const char *str, va_list print_list);
int     ft_tiret_d(int no_zer);
char    *ft_adress(void *adress);
void    ft_verif_x(char c, unsigned int nb);
int     ft_zero(int i, const char *str, va_list print_list);
int     ft_zero_u(unsigned int nb, int speciation);
int     ft_zero_x(char type,long int nb, int speciation);
int     ft_point(int i, const char *str, va_list print_list);
char	*ft_itoa_space( int n, int base);
int     ft_space(int i, const char *str, va_list print_list);
char	*ft_itoa_squeeze( int n, int base);
char	*ft_itoa_u_space(long int n, int base);
int     ft_test_spec(int i, const char *str, va_list print_list);
void 	ft_verif_x_space(char c, unsigned int nb);
int     ft_space_x(char type,long int nb, int speciation);

#endif