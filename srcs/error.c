/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:43:38 by vintran           #+#    #+#             */
/*   Updated: 2021/08/18 04:52:56 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = -1;
	dest = malloc(sizeof(char *)
			* (ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1));
	if (!dest)
		return (NULL);
	while (s1[++i])
		dest[i] = s1[i];
	while (s2[++j])
		dest[i + j] = s2[j];
	dest[i + j] = '\0';
	free((char *)s1);
	return (dest);
}

int	is_slash(char *cmd)
{
	int	i;

	i = 0;
	if (cmd)
	{
		while (cmd[i])
		{
			if (cmd[i] == '/')
				return (1);
			i++;
		}
	}
	return (0);
}

void	cmd_not_found(char *cmd)
{

	ft_putstr_fd("pipex: command not found: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	execve_error(t_var *var)
{
	int	fd;

	if (!var->path)
		perror("pipex");
	else if (!ft_strncmp(var->str[0], "..", ft_strlen(var->str[0])))
		cmd_not_found(var->cmd);
	else if (is_slash(var->str[0]))
	{
		fd = open(var->str[0], O_DIRECTORY);
		if (fd != -1)
		{
			close(fd);
			ft_putstr_fd("pipex: ", STDERR_FILENO);
			ft_putstr_fd(var->cmd, STDERR_FILENO);
			ft_putstr_fd(" is a directory\n", STDERR_FILENO);
		}
	}
	else
		cmd_not_found(var->cmd);
	var->ret = -3;
	exit_pipex(var);
}
