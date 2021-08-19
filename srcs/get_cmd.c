/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 03:10:08 by vintran           #+#    #+#             */
/*   Updated: 2021/08/19 03:10:11 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_env_path(char **env)
{
	char	**res;
	int		i;

	res = NULL;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			res = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (res);
}

char	*get_cmd(char *av)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = NULL;
	while (av[i] && av[i] != ' ')
		i++;
	if (i > 0)
		cmd = ft_strndup(av, i);
	return (cmd);
}

char	*get_option(char *av)
{
	char	*opt;

	opt = NULL;
	while (*av)
	{
		if (*av == ' ')
		{
			while (*av == ' ')
				av++;
			break ;
		}
		av++;
	}
	if (*av)
		opt = ft_strndup(av, ft_strlen(av));
	return (opt);
}

char	*get_cmdpath(char *cmd, char **path)
{
	char	*cmdpath;
	int		i;
	int		cmdlen;
	int		pathlen;

	cmdlen = ft_strlen(cmd);
	i = -1;
	while (path[++i])
	{
		pathlen = ft_strlen(path[i]);
		cmdpath = malloc(pathlen + cmdlen + 2);
		if (!cmdpath)
			return (NULL);
		ft_strcpy(cmdpath, path[i]);
		cmdpath[pathlen] = '/';
		cmdpath[pathlen + 1] = '\0';
		ft_strcat(cmdpath, cmd);
		if (!access(cmdpath, F_OK))
			return (cmdpath);
		free(cmdpath);
	}
	return (NULL);
}
