/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 00:11:52 by haitam            #+#    #+#             */
/*   Updated: 2022/05/18 17:53:08 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_split_check(char **cmd)
{
	if (*cmd == NULL)
	{
		perror("error");
		exit(0);
	}
}

void	ft_path_null(char *path, char **cmd)
{
	if (path == NULL)
	{
		free_memory_pipex(cmd);
		ft_putstr_fd("Command not found", 1);
		exit(1);
	}
}

void	ft_execve_error(char *path, char **cmd, int a)
{
	free(path);
	free_memory_pipex(cmd);
	perror("execve error");
	if (a == 2)
		write(1, "-1", 2);
	exit(1);
}
