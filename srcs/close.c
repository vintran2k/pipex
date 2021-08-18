/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:53:08 by vintran           #+#    #+#             */
/*   Updated: 2021/08/18 19:57:42 by vintran          ###   ########.fr       */
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
