#include "pipex.h"

void	pipex(t_var *var, char **av, char **env)
{
	while (var->i <= var->n)
	{
		forking(av, env, var, var->i);
		if (var->ret == 0)
			var->fork[var->i] = 1;
		else
			var->fork[var->i] = 0;
		var->i++;
	}
	var->i = 0;
	while (var->i <= var->n)
	{
		if (var->fork[var->i])
		{
			waitpid(var->pid[var->i], &var->status, 0);
			if (WIFEXITED(var->status))
				var->exit = WEXITSTATUS(var->status);
		}
		var->i++;
	}
	exit_pipex(var);
}

int	main(int ac, char **av, char **env)
{
	t_var	var;

	if (ac < 5)
		return (1);
	var.ret = init_pipex(&var, ac, env);
	if (var.ret == -1)
		exit_pipex(&var);
	pipex(&var, av, env);
	return (0);
}
