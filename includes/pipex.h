/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:38:35 by hmoubal           #+#    #+#             */
/*   Updated: 2022/03/13 22:24:20 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

void	free_memory_pipex(char **s);
void	ft_file(int fd, char *path, char **cmd);
char	*ft_strjoin_pipex(char const *s1,	char const *s2);
char	**ft_split(char const *s,	char c);
size_t	ft_strlen(char const	*str);
int		ft_strncmp(const char *str, const char *tab, size_t a);
void	*ft_memcpy(void *dest,	const void *src,	size_t size);
void	ft_putstr_fd(char *s,	int fd);
void	ft_pid(pid_t pid, char *path, char **cmd);
void	ft_path_checker(char *paths);
void	ft_execve_error(char *path, char **cmd);
void	ft_path_null(char *path, char **cmd);
#endif
