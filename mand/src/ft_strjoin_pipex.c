/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitam <haitam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:01:34 by hmoubal           #+#    #+#             */
/*   Updated: 2022/02/25 23:14:57 by haitam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strjoin_pipex(char const *s1,	char const *s2)
{
	char	*tab;
	size_t	i;
	size_t	j;
	int		k;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	k = 0;
	tab = (char *)malloc(i + j + 1);
	if (tab == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		tab[k] = (char)*s1++;
		k++;
	}
	while (*s2 != '\0')
	{
		tab[k] = (char)*s2++;
		k++;
	}
	tab[k] = '\0';
	return (tab);
}
