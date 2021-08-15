/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:53:08 by vintran           #+#    #+#             */
/*   Updated: 2021/08/14 17:01:23 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_first(t_var *var)
{
	int	i;
	int	j;

	i = 0;
	while (i < var->n)
	{
		j = 0;
		while (j < 2)
		{
			if (i != 0 || j != 1)
				close(var->fd[i][j]);
			j++;
		}
		i++;
	}
}

void	close_mid(t_var *var, int index)
{
	int	i;
	int	j;

	i = 0;
	while (i < var->n)
	{
		j = 0;
		while (j < 2)
		{
			if ((i != index || j != 0) && (i != index + 1 || j != 1))
				close(var->fd[i][j]);
			j++;
		}
		i++;
	}
}

void	close_last(t_var *var)
{
	int	i;
	int	j;

	i = 0;
	while (i < var->n)
	{
		j = 0;
		while (j < 2)
		{
			if (i != 1 || j != 0)
				close(var->fd[i][j]);
			j++;
		}
		i++;
	}
}

void	free_vars(t_var *var)
{
	int	i;

	i = 0;
	/*if (var->fd)
	{
		while (i < var->n)
		{
			if (var->fd[i])
				free(var->fd[i]);
				var->fd[i] = NULL;
			i++;
		}
		free(&var->fd);
		var->fd = NULL;
	}*/
	free(var->cmdpath);
		var->cmdpath = NULL;
	free(var->cmd);
		var->cmd = NULL;
	free(var->opt);
		var->opt = NULL;
	free(var->str);
		var->str = NULL;
	ft_free_tab(var->path);
		var->path = NULL;
	free(var->pid);
		var->pid = NULL;
}

void	exit_pipex(t_var *var)
{
	if (var->ret == -1)
		write(STDERR_FILENO, "error\n", 6);
	/*if (var->ret == -6)
	{
		write(STDERR_FILENO, "pipex: command not found: ", 26);
		write(STDERR_FILENO, var->cmd, ft_strlen(var->cmd));
		write(STDERR_FILENO, "\n", 1);
		var->status = 0;
	}*/
	free_vars(var);
	if (var->ret < 0)
	{
		var->exit = WEXITSTATUS(var->status);
		exit(var->exit);
	}
}
