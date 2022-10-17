/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:08:52 by byoshimo          #+#    #+#             */
/*   Updated: 2022/10/16 03:21:28 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char *ft_get_flags(const char *str_flags, char c, char *flags)
{
	while (*str_flags != c)
	{
		if (*str_flags == '#')
			flags[0] = '#';
		else if (*str_flags == ' ')
			flags[1] = ' ';
		else if (*str_flags == '+')
			flags[2] = '+';
		str_flags++;
	}
	return(flags);
}

static int	ft_print_argument(const char *str_flags, char c, va_list ap)
{
	int	count;
	char *flags;

	count = 0;
	flags = ft_strdup("***");
	flags = ft_get_flags(str_flags, c, flags);
	if (c == 'c')
		count += ft_print_char(va_arg(ap, int));
	else if (c == 's')
		count += ft_print_str(va_arg(ap, char *));
	else if (c == 'p')
		count += ft_print_ptr(va_arg(ap, unsigned long), flags[2], flags[1]);
	else if (c == 'd' || c == 'i')
		count += ft_print_dec(va_arg(ap, int), flags[2], flags[1]);
	else if (c == 'u')
		count += ft_print_uns(va_arg(ap, unsigned int));
	else if (c == 'x' || c == 'X')
		count += ft_print_hex(va_arg(ap, unsigned int), c, flags[0]);
	else if (c == '%')
		count += ft_print_char('%');
	return (free(flags), count);
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

// #include <stdio.h>

// int	main(void)
// {
// 	// char	ptr[5] = "12";
// 	// char	c = 'c';
// 	// int	i = 4445645;
// 	// int	j = -1;
// 	// long	k = 5012312;

// 	// printf("%d\n", printf("%### + +#x *%# +u *%# +x*%# +s* *%# +c* *%# +p %+ #%\n", i, j, k, ptr, c, ptr));
// 	// ft_printf("%d\n", ft_printf("%### + +#x *%# +u *%# +x*%# +s* *%# +c* *%# +p %+ #%\n", i, j, k, ptr, c, ptr));

// 	ft_printf("%# d fdsafasdf %# +s\n", 214748364, "djsfiai");
// 	printf("%d fsdafasd\n", 214748364);
// 	return (0);
// }