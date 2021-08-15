#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_var
{
	int		**fd;
	char	*cmd;
	char	*cmdpath;
	char	*opt;
	char	**path;
	char	**str;
	pid_t	*pid;
	int		file;
	int		n;
	int		status;
	int		exit;
	int		ret;

}			t_var;

int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strlen(char *s);
char		*ft_strndup(char *src, int n);
char		**ft_split(const char *s, char c);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strcat(char *dest, char *src);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strjoin(char const *s1, char const *s2);
char		**get_env_path(char **env);
char		*get_cmd(char *av);
char		*get_option(char *av);
char		*get_cmdpath(char *cmd, char **env, t_var *var);
void		ft_bzero(void *s, size_t n);
int			init_pipex(t_var *var);
int			init_forking(char **av, char **env, t_var *var, int i);
void		close_first(t_var *var);
void		close_mid(t_var *var, int index);
void		close_last(t_var *var);
void		ft_free_tab(char **tab);
int			cmd_error(t_var *var);
void		exit_pipex(t_var *var);

#endif