/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 00:11:52 by haitam            #+#    #+#             */
/*   Updated: 2022/03/13 22:24:46 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_path_null(char *path, char **cmd)
{
	if (path == NULL)
	{
		free_memory_pipex(cmd);
		ft_putstr_fd("Command not found", 1);
		exit(1);
	}
}

void	ft_execve_error(char *path, char **cmd)
{
	free(path);
	free_memory_pipex(cmd);
	ft_putstr_fd("execve error", 1);
	exit(1);
}
