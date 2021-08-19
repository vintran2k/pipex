/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 03:09:37 by vintran           #+#    #+#             */
/*   Updated: 2021/08/19 03:09:40 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_var	var;

	if (ac != 5)
	{
		ft_putstr_fd("usage: ./pipex [file1] [cmd1] [cmd2] file2\n", 1);
		return (1);
	}
	var.ret = init_pipex(&var, ac, env);
	if (var.ret == -1)
		exit_pipex(&var);
	pipex(&var, av, env);
	return (0);
}
