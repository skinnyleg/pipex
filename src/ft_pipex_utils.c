/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:46:44 by haitam            #+#    #+#             */
/*   Updated: 2022/03/25 14:58:30 by hmoubal          ###   ########.fr       */
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
	free(s);
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

void	ft_read(int *p, char *path, char **cmd)
{
	char	*str;

	str = malloc(2);
	read(p[0], str, 2);
	if (ft_strncmp(str, "-1", 2) == 0)
	{
		free(path);
		free_memory_pipex(cmd);
		close(p[1]);
		close(p[0]);
		free(str);
		exit(1);
	}
	free(str);
}
