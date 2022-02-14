/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:13:56 by hmoubal           #+#    #+#             */
/*   Updated: 2021/11/08 10:09:39 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s,	unsigned int start,	size_t	len)
{
	int		i;
	char	*tab;

	i = 0;
	tab = NULL;
	if (!s)
		return (NULL);
	if (ft_strlen (s + start) < len)
		len = ft_strlen(s + start);
	if (*s == '\0')
		len = 0;
	tab = (char *)malloc(len + 1);
	if (tab == NULL)
		return (NULL);
	while (len != 0 && start < ft_strlen(s))
	{
		tab[i] = s[start];
		i++;
		start++;
		len--;
	}
	tab[i] = '\0';
	return (tab);
}
