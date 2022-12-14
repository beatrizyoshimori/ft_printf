/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 02:37:02 by byoshimo          #+#    #+#             */
/*   Updated: 2022/10/19 03:15:28 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int	ft_print_dec(int n)
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
	}
	c = (n % 10) + '0';
	if (n <= 9)
	{
		count += write(1, &c, 1);
		return (count);
	}
	count += ft_print_dec(n / 10);
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

int	ft_print_hex(unsigned long n, char c)
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
		count += write(1, &hex[n % 16], 1);
		free(hex);
		return (count);
	}
	count += ft_print_hex(n / 16, c);
	count += write(1, &hex[n % 16], 1);
	free(hex);
	return (count);
}

int	ft_print_ptr(unsigned long ptr)
{
	int	count;

	count = 0;
	if (!ptr)
	{
		count += write(1, "(nil)", 5);
		return (count);
	}
	count += write(1, "0x", 2);
	count += ft_print_hex(ptr, 'x');
	return (count);
}
