/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitam <haitam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:29:35 by hmoubal           #+#    #+#             */
/*   Updated: 2022/02/24 23:24:23 by haitam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_memcpy(void *dest,	const void *src,	size_t size)
{
	char	*p1;
	char	*p2;
	int		i;

	p1 = dest;
	p2 = (char *)src;
	if (!p1 && !p2)
		return (NULL);
	i = 0;
	while (size != 0)
	{
		p1[i] = p2[i];
		i++;
		size--;
	}
	return (dest);
}
