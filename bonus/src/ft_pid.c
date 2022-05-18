/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 01:19:25 by haitam            #+#    #+#             */
/*   Updated: 2022/05/18 17:53:20 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_path_checker(char *paths)
{
	if (paths == NULL)
	{
		ft_putstr_fd("env error", 1);
		exit(1);
	}
}

void	ft_pid(pid_t pid, char *path, char **cmd)
{
	if (pid == -1)
	{
		free(path);
		free_memory_pipex(cmd);
		ft_putstr_fd("fork error", 1);
		exit(1);
	}
}
