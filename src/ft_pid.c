/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitam <haitam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 01:19:25 by haitam            #+#    #+#             */
/*   Updated: 2022/02/26 16:19:41 by haitam           ###   ########.fr       */
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

void	ft_pid(pid_t pid)
{
	if (pid == -1)
	{
		ft_putstr_fd("fork error", 1);
		exit(1);
	}
}
