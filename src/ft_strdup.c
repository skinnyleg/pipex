/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitam <haitam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:54:22 by hmoubal           #+#    #+#             */
/*   Updated: 2022/02/25 23:14:57 by haitam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strdup(const char *src)
{
	char	*hub;
	int		i;
	int		len;

	hub = NULL;
	i = 0;
	len = 0;
	while (src[len] != '\0')
		len++;
	hub = malloc(len + 1);
	if (hub == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		hub[i] = src[i];
		i++;
	}
	hub[i] = '\0';
	return (hub);
}
