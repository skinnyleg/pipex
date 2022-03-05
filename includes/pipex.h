/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitam <haitam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:38:35 by hmoubal           #+#    #+#             */
/*   Updated: 2022/03/06 00:14:44 by haitam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define BUFFER_SIZE 1
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

void	free_memory_pipex(char **s);
void	ft_file(int fd);
char	*ft_strjoin_pipex(char const *s1,	char const *s2);
char	**ft_split(char const *s,	char c);
size_t	ft_strlen(char const	*str);
int		ft_strncmp(const char *str, const char *tab, size_t a);
void	*ft_memcpy(void *dest,	const void *src,	size_t size);
void	ft_putstr_fd(char *s,	int fd);
void	ft_pid(pid_t pid);
void	ft_path_checker(char *paths);
void	ft_execve_error(char *path, char **cmd);
#endif
