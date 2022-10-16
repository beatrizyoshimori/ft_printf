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

char	*ft_strchr(char *s, int c)
{
	int	i;
	int	length;

	length = 0;
	while (s != NULL && s[length])
		length++;
	if ((unsigned char)c == '\0')
		return (&((char *)s)[length]);
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (&((char *)s)[i]);
		i++;
	}
	return (NULL);
}

int	ft_print_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_str(char *str)
{
	int	count;

	count = 0;
	if (!str)
	{
		count += write(1, "(null)", 6);
		return (count);
	}
	while (*str)
		count += write(1, &(*str++), 1);
	return (count);
}

int	ft_print_dec(int n, char plus, char space)
{
	int		count;
	char	c;

	count = 0;
	if (n < 0)
	{
		count += write(1, "-", 1);
		if (n == -2147483648)
		{
			count += write(1, "2147483648", 10);
			return (count);
		}
		n = -n;
		plus = '*';
		space = '*';
	}
	c = (n % 10) + '0';
	if (n <= 9)
	{
		if (plus == '+')
			count += write(1, "+", 1);
		else if (space == ' ')
			count += write(1, " ", 1);
		count += write(1, &c, 1);
		return (count);
	}
	count += ft_print_dec(n / 10, plus, space);
	count += write(1, &c, 1);
	return (count);
}

int	ft_print_uns(unsigned int n)
{
	int		count;
	char	c;

	count = 0;
	c = (n % 10) + '0';
	if (n <= 9)
	{
		count += write(1, &c, 1);
		return (count);
	}
	count += ft_print_uns(n / 10);
	count += write(1, &c, 1);
	return (count);
}

int	ft_print_hex(unsigned long n, char c, char hash)
{
	char	*hex;
	int		count;

	count = 0;
	if (c == 'x')
		hex = ft_strdup("0123456789abcdef");
	else
		hex = ft_strdup("0123456789ABCDEF");
	if (n < 16)
	{
		if (hash == '#' && c == 'x' && n != 0)
			count += write(1, "0x", 2);
		else if (hash == '#' && c == 'X' && n != 0)
			count += write(1, "0X", 2);
		count += write(1, &hex[n % 16], 1);
		return (free(hex), count);
	}
	count += ft_print_hex(n / 16, c, hash);
	count += write(1, &hex[n % 16], 1);
	return (free(hex), count);
}

int	ft_print_ptr(unsigned long ptr, char plus, char space)
{
	int	count;
	char	*hex;

	hex = ft_strdup("0123456789abcdef");
	count = 0;
	if (!ptr)
	{
		count += write(1, "(nil)", 5);
		free(hex);
		return (count);
	}
	if (ptr < 16)
	{
		if (plus == '+')
			count += write(1, "+", 1);
		else if (space == ' ')
			count += write(1, " ", 1);
		count += write(1, "0x", 2);
		count += write(1, &hex[ptr % 16], 1);
		return (free(hex), count);
	}
	count += ft_print_ptr(ptr/ 16, plus, space);
	count += write(1, &hex[ptr % 16], 1);
	return (free(hex), count);
}

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
	// char hash;
	// char space;
	// char plus;

	// hash = '*';
	// space = '*';
	// plus = '*';
	count = 0;
	flags = ft_strdup("***");
	flags = ft_get_flags(str_flags, c, flags);
	// while (*str_flags != c)
	// {
	// 	if (*str_flags == '#')
	// 		hash = '#';
	// 	else if (*str_flags == ' ')
	// 		space = ' ';
	// 	else if (*str_flags == '+')
	// 		plus = '+';
	// 	str_flags++;
	// }
	if (c == 'c')
		count += ft_print_char(va_arg(ap, int));
	if (c == 's')
		count += ft_print_str(va_arg(ap, char *));
	if (c == 'p')
		count += ft_print_ptr(va_arg(ap, unsigned long), flags[2], flags[1]);
	if (c == 'd' || c == 'i')
		count += ft_print_dec(va_arg(ap, int), flags[2], flags[1]);
	if (c == 'u')
		count += ft_print_uns(va_arg(ap, unsigned int));
	if (c == 'x' || c == 'X')
		count += ft_print_hex(va_arg(ap, unsigned int), c, flags[0]);
	if (c == '%')
		count += ft_print_char('%');
	return (free(flags), count);
}

#include <stdio.h>

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
			length += write(1, &str[i], 1);
		else
		{
			i++;
			j = i;
			while (ft_strchr(conversions, str[j]) == NULL && str[j] != '%')
				j++;
			length += ft_print_argument(&str[i], str[j], ap);
			i = j;
		}
		i++;
	}
	return (free(conversions), length);
}

// int	main(void)
// {
// 	// char	ptr[5] = "12";
// 	// char	c = 'c';
// 	// int	i = 4445645;
// 	// int	j = -1;
// 	// long	k = 5012312;

// 	// printf("%d\n", printf("%### + +#x *%# +u *%# +x*%# +s* *%# +c* *%# +p %+ #%\n", i, j, k, ptr, c, ptr));
// 	// ft_printf("%d\n", ft_printf("%### + +#x *%# +u *%# +x*%# +s* *%# +c* *%# +p %+ #%\n", i, j, k, ptr, c, ptr));

// 	ft_printf("%#c\n", 'x');
// 	printf("%#c\n", 'x');
// 	return (0);
// }