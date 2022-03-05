/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitam <haitam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:46:44 by haitam            #+#    #+#             */
/*   Updated: 2022/03/06 00:28:14 by haitam           ###   ########.fr       */
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

void	ft_file(int fd, char *path, char **cmd)
{
	if (fd < 0)
	{
		free(path);
		free_memory_pipex(cmd);
		ft_putstr_fd("unreadable file", 1);
		exit(1);
	}
}
