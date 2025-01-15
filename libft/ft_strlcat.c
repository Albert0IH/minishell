/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:55:19 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/05/18 12:59:30 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	d;
	size_t	s;

	d = ft_strlen(dst);
	s = ft_strlen((char *)src);
	i = 0;
	if (size <= d)
	{
		return (size + s);
	}
	while (src[i] != '\0' && d + i + 1 < size)
	{
		dst[d + i] = src[i];
		i++;
	}
	dst[d + i] = '\0';
	return (d + s);
}
