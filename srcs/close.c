/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:53:08 by vintran           #+#    #+#             */
/*   Updated: 2021/08/18 04:50:18 by vintran          ###   ########.fr       */
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

void	hub_close(t_var *var, int i)
{
	if (i == 0)
		close(var->fd[0][1]);
	else if (i == var->n)
		close(var->fd[var->n - 1][0]);
	else
	{
		close(var->fd[i - 1][0]);
		close(var->fd[i][1]);
	}
}

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
