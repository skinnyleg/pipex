/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitam <haitam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 01:19:25 by haitam            #+#    #+#             */
/*   Updated: 2022/03/06 00:24:47 by haitam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
