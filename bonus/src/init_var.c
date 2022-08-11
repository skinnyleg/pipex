/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:46:43 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/11 14:14:13 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_check_cmd(t_var *var)
{
	if (var->cmd == NULL)
	{
		ft_putstr_fd("Malloc Error\n", 2);
		free_2d(var->paths);
		close_all(var);
		free_int(var->p, var->pipe_num);
		exit(1);
	}
}

void	ft_check_path(t_var *var)
{
	if (var->cmd_path == NULL)
	{
		free_2d(var->cmd);
		free_2d(var->paths);
		close_all(var);
		free_int(var->p, var->pipe_num);
		ft_putstr_fd("Command Not Found\n", 2);
		exit(1);
	}
}

void	create_pipe(t_var *var)
{
	int	i;

	i = -1;
	var->p = (int **)malloc(sizeof(int *) * (var->pipe_num));
	if (var->p == NULL)
	{
		ft_putstr_fd("Malloc error\n", 2);
		exit(1);
	}
	while (++i < var->pipe_num)
	{
		var->p[i] = (int *)malloc(sizeof(int) * 2);
		if (var->p[i] == NULL)
		{
			ft_putstr_fd("Malloc error\n", 2);
			free_int(var->p, i);
			exit(1);
		}
		if (pipe(var->p[i]) == -1)
		{
			ft_putstr_fd("pipe error\n", 2);
			free_int(var->p, var->pipe_num);
			exit(1);
		}
	}
}

void	init(t_var *var, char **av, char **env, int ac)
{
	var->fork_num = ac - 3;
	var->pipe_num = var->fork_num - 1;
	create_pipe(var);
	var->fd[0] = open(av[1], O_RDWR);
	var->fd[1] = open(av[var->ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0645);
	ft_file(var);
	var->paths = ft_findpath(env);
	ft_check_env(var);
	var->i = 0;
	var->j += 2;
}

void	init_cmd(t_var *var, char *cmd)
{
	var->cmd = ft_split(cmd, ' ');
	ft_check_cmd(var);
	var->cmd_path = ft_path(var, var->cmd[0]);
	ft_check_path(var);
}
