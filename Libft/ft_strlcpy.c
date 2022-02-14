/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:19:44 by hmoubal           #+#    #+#             */
/*   Updated: 2021/11/06 21:44:48 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest,	const char *src,	size_t size)
{
	size_t	i;
	size_t	a;

	i = 0;
	a = 0;
	while (src[i] != '\0')
		i++;
	if (size != 0)
	{
		while (src[a] != '\0' && a < size - 1)
		{
			dest[a] = src[a];
			a++;
		}
		dest[a] = '\0';
	}
	return (i);
}
