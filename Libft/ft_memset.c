/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:15:09 by hmoubal           #+#    #+#             */
/*   Updated: 2021/11/06 21:05:10 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *p1,	int v,	size_t count)
{
	int				i;
	unsigned char	*p;

	i = 0;
	p = p1;
	while (count != 0)
	{
		p[i] = v;
		i++;
		count--;
	}
	return (p1);
}
