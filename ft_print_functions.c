
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

int	ft_print_dec(int n, char plus, char space)
{
	int		count;
	char	c;

	count = 0;
	if (n < 0)
	{
		if (n == -2147483648)
			return (write(1, "-2147483648", 11));
		count += write(1, "-", 1);
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
		return (count += write(1, &c, 1));
	}
	count += ft_print_dec(n / 10, plus, space);
	return (count += write(1, &c, 1));
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
