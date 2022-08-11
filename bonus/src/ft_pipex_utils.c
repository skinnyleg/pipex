/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:46:44 by haitam            #+#    #+#             */
/*   Updated: 2022/08/11 14:11:39 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	free_2d(char **s)
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

void	free_int(int **s,	int block)
{
	while (block--)
		free(s[block]);
	free(s);
}

void	ft_file(t_var *var)
{
	if (var->fd[0] < 0 || var->fd[1] < 0)
	{
		close_all(var);
		free_int(var->p, var->pipe_num);
		if (var->fd[0] < 0)
			ft_putstr_fd("unreadable file\n", 2);
		else
			ft_putstr_fd("Can't create output file\n", 2);
		exit(1);
	}
}

void	ft_check_env(t_var *var)
{
	if (var->paths == NULL)
	{
		ft_putstr_fd("env error\n", 2);
		close_all(var);
		free_int(var->p, var->pipe_num);
		exit(1);
	}
}

void	ft_pid(pid_t pid, t_var *var)
{
	if (pid == -1)
	{
		free(var->cmd_path);
		free_2d(var->cmd);
		free_2d(var->paths);
		close_all(var);
		ft_putstr_fd("fork error", 2);
		exit(1);
	}
}
