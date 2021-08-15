/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 18:03:19 by vintran           #+#    #+#             */
/*   Updated: 2021/08/13 19:01:17 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		is_slash(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '/')
			return (1);
		cmd++;
	}
	return (0);
}

int	cmd_error_msg(char *cmd)
{
	char	*msg;

	msg = ft_strndup("", 1);
	if (!msg)
		return (-1);
	//msg = ft_strjoin(msg, cmd);
	//if (!msg)
		//return (-1);
	msg = ft_strjoin(msg, "pipex: command not found ");
	if (!msg)
		return (-1);
	msg = ft_strjoin(msg, cmd);
	if (!msg)
		return (-1);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(msg);
	return (0);
}

int	cmd_error(t_var *var)
{
	int fd;

	//fprintf(stderr, "VINS VINS %s\n", var->cmd);
	if (!ft_strncmp(var->cmd, "..", ft_strlen(var->cmd)))
	{
		//ft_putstr_fd("passage1 pour cmd = ", STDERR_FILENO);
		//ft_putstr_fd(var->cmd, STDERR_FILENO);
		//ft_putstr_fd("\n", STDERR_FILENO);
		cmd_error_msg(var->cmd);
	}
	else if (is_slash(var->cmd))
	{
		fd = open(var->cmd, O_DIRECTORY);
		if (fd != -1)
		{
			close(fd);
			perror("pipex");
		}
	}
	else
	{
		//ft_putstr_fd("passage2 pour cmd = ", STDERR_FILENO);
		//ft_putstr_fd(var->cmd, STDERR_FILENO);
		//ft_putstr_fd("\n", STDERR_FILENO);
		if (!cmd_error_msg(var->cmd))
			return (-1);
	}
	return (0);
}
