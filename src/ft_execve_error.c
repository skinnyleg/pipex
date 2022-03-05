/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitam <haitam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 00:11:52 by haitam            #+#    #+#             */
/*   Updated: 2022/03/06 00:15:13 by haitam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_execve_error(char *path, char **cmd)
{
	free(path);
	free_memory_pipex(cmd);
	ft_putstr_fd("execve error", 1);
	exit(1);
}
