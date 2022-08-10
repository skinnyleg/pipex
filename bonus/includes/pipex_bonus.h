/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:38:35 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/10 15:09:56 by hmoubal          ###   ########.fr       */
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

typedef struct s_var
{
	char	*cmd_path;
	char	**cmd;
	int		p[2];
	char	**paths;
	int		i;
	int		fork_num;
	int		pipe_num;
	int		fd[2];
}	t_var;

void	free_2d(char **s);
void	ft_file(t_var *var);
char	*ft_strjoin(char const *s1,	char const *s2);
char	**ft_split(char const *s,	char c);
size_t	ft_strlen(char const	*str);
int		ft_strncmp(const char *str, const char *tab, size_t a);
void	*ft_memcpy(void *dest,	const void *src,	size_t size);
void	ft_putstr_fd(char *s,	int fd);
void	ft_pid(pid_t pid, t_var *var);
void	close_all(t_var *var);
void	ft_check_env(t_var *var);
void	ft_check_cmd(t_var *var);
void	init_cmd(t_var *var, char *cmd);
void	init(t_var *var, char **av, char **env);
void	ft_check_path(t_var *var);
char	**ft_findpath(char **env);
char	*ft_path(t_var *var, char *av);
#endif
