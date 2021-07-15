/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:25:37 by idhiba            #+#    #+#             */
/*   Updated: 2021/07/15 16:15:00 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

int				ft_printf(const char *str, ...);
char			*ft_itoa(int n, int base);
char			*ft_itoa_u(long int n, int base);
char			*ft_itoa_x(long int n, int type_charac);
int				ft_atoi(char *str);
int				ft_strlen(char *s);
int				ft_putchar(char c, int n);
int				ft_putstr(char *s, int n);
char			*ft_strdup(const char *s);
int				ft_no_zer(int n);
int				ft_type_tiret(char type, va_list print_list);
int				ft_tiret(int i, const char *str, va_list print_list);
int				ft_tiret_d(int no_zer);
char			*ft_adress(void *adress);
void			ft_verif_x(char c, unsigned int nb);
int				ft_zero(int i, const char *str, va_list print_list);
int				ft_zero_u(unsigned int nb, int speciation);
int				ft_zero_x(char type, long int nb, int speciation);
int				ft_point(int i, const char *str, va_list print_list);
char			*ft_itoa_space( int n, int base);
int				ft_space(int i, const char *str, va_list print_list);
char			*ft_itoa_squeeze( int n, int base);
char			*ft_itoa_u_space(long int n, int base);
void			ft_verif_x_space(char c, unsigned int nb);
int				ft_count(int n);
int				ft_count_long(long int n);
char			*ft_strrev(char *str);
unsigned int	ft_convers_u(unsigned int nb);
void			ft_verif_x_space(char c, unsigned int nb);
char			*ft_adress(void *adress);
int				ft_space_d(int nb, int speciation);
int				ft_space_x(char type, long int nb, int speciation);
int				ft_space_u(unsigned int nb, int speciation);
int				ft_space_c(char charac, int speciation);
int				ft_space_p(void *adress, int speciation);
int				ft_space_s_null(char *dest, int speciation);
int				ft_space_s(char *dest, int speciation);
int				ft_type_space(char type, va_list print_list, int speciation);
void			ft_tiret_norme(int tmp, int espaces);
void			ft_norme_u(unsigned int nb_u);
void			ft_norme_d(int nb);
int				ft_norme_tiret(void *adress);
int				ft_norme_itoa(int n);

#endif
