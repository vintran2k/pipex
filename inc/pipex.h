/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 21:00:18 by vintran           #+#    #+#             */
/*   Updated: 2021/08/24 21:00:20 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_var
{
	int		i;
	int		**fd;
	char	*cmd;
	char	*cmdpath;
	char	**path;
	char	**str;
	pid_t	*pid;
	int		file;
	int		n;
	int		status;
	int		exit;
	int		ret;
	int		*fork;
}			t_var;

int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strlen(char *s);
char		*ft_strndup(char *src, int n);
char		**ft_split(const char *s, char c);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strcat(char *dest, char *src);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_putstr_fd(char *s, int fd);
int			is_slash(char *cmd);
char		**get_env_path(char **env);
char		*get_cmd(char *av);
char		*get_option(char *av);
char		*get_cmdpath(char *cmd, char **path);
void		ft_bzero(void *s, size_t n);
int			init_pipex(t_var *var, int ac, char **env);
void		pipex(t_var *var, char **av, char **env);
int			init_forking(char **av, t_var *var, int i);
int			first_fork(char **env, t_var *var);
int			mid_fork(char **env, t_var *var, int i);
int			last_fork(char **env, t_var *var);
int			forking(char **av, char **env, t_var *var, int i);
void		close_first(t_var *var);
void		close_mid(t_var *var, int index);
void		close_last(t_var *var);
void		hub_close(t_var *var, int i);
void		ft_free_tab(char **tab);
void		execve_error(t_var *var);
void		exit_pipex(t_var *var);

#endif