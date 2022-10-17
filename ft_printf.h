/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 23:48:57 by byoshimo          #+#    #+#             */
/*   Updated: 2022/10/17 23:36:40 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_flags_types
{
	char	hash;
	char	space;
	char	plus;
}	t_flags_types;

char	*ft_strdup(const char *src);
char	*ft_strchr(char *s, int c);
int		ft_printf(const char *str, ...);
int		ft_print_char(int c);
int		ft_print_str(char *str);
int		ft_print_dec(int i, char plus, char space);
int		ft_print_uns(unsigned int n);
int		ft_print_hex(unsigned long n, char c, char hash);
int		ft_print_ptr(unsigned long ptr, char plus, char space);

#endif