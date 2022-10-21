/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 02:29:48 by byoshimo          #+#    #+#             */
/*   Updated: 2022/10/19 04:51:40 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		length;
	char	*dst;

	length = 0;
	while (src != NULL && src[length])
		length++;
	dst = malloc(length + 1);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_print_char(int c)
{
	write(1, &c, 1);
	return (1);
}

static int	ft_print_argument(char c, va_list ap)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_print_char(va_arg(ap, int));
	if (c == 's')
		count += ft_print_str(va_arg(ap, char *));
	if (c == 'p')
		count += ft_print_ptr(va_arg(ap, unsigned long));
	if (c == 'd' || c == 'i')
		count += ft_print_dec(va_arg(ap, int));
	if (c == 'u')
		count += ft_print_uns(va_arg(ap, unsigned int));
	if (c == 'x' || c == 'X')
		count += ft_print_hex(va_arg(ap, unsigned int), c);
	if (c == '%')
		count += ft_print_char('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		length;

	va_start(ap, str);
	i = 0;
	length = 0;
	while (str[i])
	{
		if (str[i] != '%')
			length += write(1, &str[i], 1);
		else
		{
			i++;
			length += ft_print_argument(str[i], ap);
		}
		i++;
	}
	return (length);
}
