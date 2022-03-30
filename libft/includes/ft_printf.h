/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:02:41 by ldubuche          #+#    #+#             */
/*   Updated: 2022/01/04 11:02:41 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <string.h>
# include "ft_struct.h"

# ifndef OS_NULL
#  ifdef __unix__
#   define OS_NULL "(nil)"
#  endif
#  ifdef __Apple__
#   define OS_NULL "0x0"
#  endif
# endif

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_flags(va_list ptr, const char **str, int len);
int		ft_space_nbr(t_struct *f1, char *str);
int		ft_spc_nbr2(t_struct *f1, int n);
int		ft_sign(t_struct *f1, char *str);
int		ft_printf(const char *str, ...);

void	ft_width_precision(t_struct *f1, const char **str);
void	ft_check_sign_diese(t_struct *f1, char *str);
void	ft_gagner_3_lignes(t_struct *f1, char *str);
void	ft_symbols(t_struct *f1, const char **str);
void	ft_args_to_str(t_struct *f1, va_list ptr);
void	ft_write_arg2(t_struct *f1, char *str);
void	ft_write_arg(t_struct *f1, char *str);
void	ft_putargs(t_struct *f1, char *str);
void	ft_chara(t_struct *f1, char *str);
void	ft_putspace(t_struct *f1, int n);
void	ft_putzero(t_struct *f1, int n);
void	ft_ini_struct(t_struct *f1);
void	ft_putchar(char c);
void	ft_putstr(char *s);

char	*ft_str_ptr(int type, char *str, t_struct *f1);
char	*ft_strcpy(const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const*s2);
char	*ft_freestr(char *temp, char *temp2);
char	*ft_pre(char *str, t_struct *f1);
char	*ft_strrchr(const char *s, int c);
char	*ft_ini_strjoin(char *s, char c);
char	*ft_unsi_itoa(unsigned int n);
char	*ft_address(unsigned long n);
char	*ft_hexa(unsigned int n);
char	*ft_c_to_str(char c);
char	*ft_toupper(char *s);
char	*ft_itoa(int n);
char	*ft_null(void);

size_t	ft_strlen(const char *s);

#endif