/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:57:25 by vintran           #+#    #+#             */
/*   Updated: 2021/08/19 01:59:32 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;

	i = -1;
	while (++i < n)
	{
		((unsigned char *)s)[i] = 0;
	}
}

int	init_malloc(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->n)
	{
		var->fd[i] = malloc(sizeof(int) * 2);
		if (!var->fd[i])
			return (-1);
		if (pipe(var->fd[i]) == -1)
			return (-1);
		i++;
	}
	var->str = malloc(sizeof(char *) * 3);
	if (!var->str)
		return (-1);
	var->str[0] = NULL;
	var->str[1] = NULL;
	var->str[2] = NULL;
	return (0);
}

int	init_pipex(t_var *var, int ac, char **env)
{
	ft_bzero(var, sizeof(t_var));
	var->n = ac - 4;
	var->fork = malloc(sizeof(int) * (var->n + 1));
	if (!var->fork)
		return (-1);
	var->path = get_env_path(env);
	if (!var->path)
		return (-1);
	var->fd = malloc(sizeof(int *) * var->n);
	if (!var->fd)
		return (-1);
	var->pid = malloc(sizeof(pid_t) * (var->n + 1));
	if (!var->pid)
		return (-1);
	if (init_malloc(var) == -1)
		return (-1);
	return (0);
}

int	init_forking(char **av, t_var *var, int i)
{
	if (i == 0)
	{
		var->file = open(av[1], O_RDONLY);
		if (var->file == -1)
			return (-2);
	}
	if (i == var->n)
	{
		if (var->file != -1)
			close(var->file);
		var->file = open(av[3 + var->n], O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (var->file == -1)
			return (-2);
	}
	var->cmd = get_cmd(av[2 + i]);
	if (!var->cmd)
		return (-2);
	var->cmdpath = get_cmdpath(var->cmd, var->path);
	var->str[0] = var->cmdpath;
	if (!var->str[0])
		var->str[0] = var->cmd;
	var->str[1] = get_option(av[2 + i]);
	return (0);
}
