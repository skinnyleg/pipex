/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 08:44:58 by hmoubal           #+#    #+#             */
/*   Updated: 2021/11/06 21:23:14 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest,	const void *src,	size_t size)
{
	char	*p1;
	char	*p2;
	char	*tab;
	char	*hub;

	p1 = dest;
	p2 = (char *)src;
	tab = NULL;
	hub = NULL;
	if (!p1 && !p2)
		return (NULL);
	if (p1 < p2)
	{
		while (size--)
			*p1++ = *p2++;
	}
	else
	{
		tab = p1 + (size - 1);
		hub = p2 + (size - 1);
		while (size--)
			*tab-- = *hub--;
	}
	return (dest);
}
