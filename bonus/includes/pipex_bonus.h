/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:38:35 by hmoubal           #+#    #+#             */
/*   Updated: 2022/05/20 18:00:13 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_all{
	char	*paths;
	int		i;
	int		j;
	int		fd[2];
	int		**p;
	int		*arr;
	int		*pid;
	int		fork_num;
	int		pipe_num;

}	t_all;

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
void	ft_execve_error(char *path, char **cmd, int a);
void	ft_split_check(char **cmd);
void	ft_path_null(char *path, char **cmd);
char	*ft_strdup(const char *src);
void	ft_read(int *p, char *path, char **cmd);
int		ft_child_rep(char *paths, char **av, int *p, char **env);
char	*ft_path(char *env, char *av);
char	*ft_findpath(char **env);
void	ft_malloc(void *tab);
void	ft_init(t_all *var, char **env, int ac, char **av);
void	ft_init2(t_all *var);
void	ft_routine(t_all *var, char **av, char **env);
void	ft_first(t_all *var, char **av, char **env, int index);
void	ft_middle(t_all *var, char **av, char **env, int index);
void	ft_last(t_all *var, char **av, char **env, int index);
#endif
