/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:43:38 by vintran           #+#    #+#             */
/*   Updated: 2021/08/24 20:56:47 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	else if (!ft_strncmp(var->cmd, "..", ft_strlen(var->cmd)))
		perror("pipex");
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
		else
			perror("pipex");
	}
	else
		cmd_not_found(var->cmd);
	var->ret = -3;
	exit_pipex(var);
}
