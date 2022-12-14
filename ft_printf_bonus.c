/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:08:52 by byoshimo          #+#    #+#             */
/*   Updated: 2022/10/19 05:01:10 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static t_flag_types	ft_get_flags(t_flag_types flag, char c, const char *str)
{
	while (*str != c)
	{
		if (*str == '#')
			flag.hash = '#';
		else if (*str == ' ')
			flag.space = ' ';
		else if (*str == '+')
			flag.plus = '+';
		str++;
	}
	return (flag);
}

static int	ft_print_argument(const char *str, char c, va_list ap)
{
	int				count;
	t_flag_types	flag;

	count = 0;
	flag.hash = '*';
	flag.space = '*';
	flag.plus = '*';
	flag = ft_get_flags(flag, c, str);
	if (c == 'c')
		count += ft_print_char(va_arg(ap, int));
	else if (c == 's')
		count += ft_print_str(va_arg(ap, char *));
	else if (c == 'p')
		count += ft_print_ptr(va_arg(ap, unsigned long), flag.plus, flag.space);
	else if (c == 'd' || c == 'i')
		count += ft_print_dec(va_arg(ap, int), flag.plus, flag.space);
	else if (c == 'u')
		count += ft_print_uns(va_arg(ap, unsigned int));
	else if (c == 'x' || c == 'X')
		count += ft_print_hex(va_arg(ap, unsigned int), c, flag.hash);
	else if (c == '%')
		count += ft_print_char('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		j;
	int		length;
	char	*conversions;

	conversions = ft_strdup("cspdiuxX");
	va_start(ap, str);
	i = 0;
	length = 0;
	while (str[i])
	{
		if (str[i] != '%')
			length += write(1, &str[i++], 1);
		else
		{
			i++;
			j = i;
			while (ft_strchr(conversions, str[j]) == NULL && str[j] != '%')
				j++;
			length += ft_print_argument(&str[i], str[j], ap);
			i = j + 1;
		}
	}
	return (free(conversions), length);
}
