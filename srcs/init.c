/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:57:25 by vintran           #+#    #+#             */
/*   Updated: 2021/08/17 02:39:50 by vintran          ###   ########.fr       */
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

int	init_pipex(t_var *var, char **env)
{
	int	i;

	var->fd = malloc(sizeof(int *) * var->n);
	if (!var->fd)
		return (-1);
	var->pid = malloc(sizeof(pid_t) * (var->n + 2));
	if (!var->pid)
		return (-1);
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
	var->path = get_env_path(env);
	return (0);
}

int	init_forking(char **av, t_var *var, int i)
{
	if (i == 0)
	{
		var->file = open(av[1], O_RDONLY);
		if (var->file == -1)
		{
			perror("pipex");
			return (-1);
		}
	}
	if (i == var->n)
	{
		close(var->file);
		var->file = open(av[3 + var->n], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (var->file == -1)
			return (-4);
	}
	var->cmd = get_cmd(av[2 + i]);
	if (var->cmd == NULL)
		return (-2);
	var->str[0] = get_cmdpath(var->cmd, var->path);
	if (var->str[0] == NULL)
		return (-6);
	var->str[1] = get_option(av[2 + i]);
	return (0);
}
