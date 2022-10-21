/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:27:44 by byoshimo          #+#    #+#             */
/*   Updated: 2022/10/19 02:38:37 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

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
