/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 19:57:21 by vintran           #+#    #+#             */
/*   Updated: 2021/08/18 19:57:48 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_vars(t_var *var)
{
	int	i;

	i = 0;
	if (var->fd)
	{
		while (i < var->n)
		{
			if (var->fd[i])
				free(var->fd[i]);
			i++;
		}
		free(var->fd);
	}
	if (var->pid)
		free(var->pid);
	if (var->cmd)
		free(var->cmd);
	if (var->cmdpath)
		free(var->cmdpath);
	if (var->str)
		free(var->str);
	free(var->fork);
	ft_free_tab(var->path);
}

void	exit_pipex(t_var *var)
{
	free_vars(var);
	if (var->ret == -3 && (errno == 2 || errno == 13))
		exit (127);
	if (var->ret < 0)
		exit (1);
	else
		exit(var->exit);
}
