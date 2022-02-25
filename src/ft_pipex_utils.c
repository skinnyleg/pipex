/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitam <haitam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:46:44 by haitam            #+#    #+#             */
/*   Updated: 2022/02/25 23:14:57 by haitam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_memory_pipex(char **s)
{
	int	block;

	block = 0;
	while (s[block])
	{
		free(s[block]);
		block++;
	}
}

void	ft_file(int fd)
{
	if (fd < 0)
	{
		ft_putstr_fd("unreadable file", 1);
		exit(1);
	}
}
