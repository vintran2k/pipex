#include "pipex.h"

int	first_fork(char **env, t_var *var)
{
	//fprintf(stderr, "first fork BATARD !!\n");
	dup2(var->file, STDIN_FILENO);
	dup2(var->fd[0][1], STDOUT_FILENO);
	close_first(var);
	if (execve(var->str[0], var->str, env) == -1)
		execve_error(var);
	return (0);
}

int	mid_fork(char **env, t_var *var, int i)
{
	//fprintf(stderr, "mid fork BATARD !!\n");
	dup2(var->fd[i - 1][0], STDIN_FILENO);
	dup2(var->fd[i][1], STDOUT_FILENO);
	close_mid(var, i);
	if (execve(var->str[0], var->str, env) == -1)
		execve_error(var);
	return (0);
}

int	last_fork(char **env, t_var *var)
{
	//fprintf(stderr, "last fork BATARD !!\n");
	dup2(var->fd[var->n - 1][0], STDIN_FILENO);
	dup2(var->file, STDOUT_FILENO);
	close_last(var);
	if (execve(var->str[0], var->str, env) == -1)
		execve_error(var);
	return (0);
}

int	pipex(char **av, char **env, t_var *var, int i)
{
	var->ret = init_forking(av, var, i);
	if (var->ret < 0)
		perror("pipex");
	if (var->ret == 0)
	{
		var->pid[i] = fork();
		if (var->pid[i] == 0)
		{
			if (i == 0)
				var->ret = first_fork(env, var);
			else if (i == var->n)
				var->ret = last_fork(env, var);
			else
				var->ret = mid_fork(env, var, i);
		}
	}
	hub_close(var, i);
	free(var->cmd);
	var->cmd = NULL;
	free(var->cmdpath);
	var->cmdpath = NULL;
	free(var->str[1]);
	var->str[1] = NULL;
	return (var->ret);
}

int	main(int ac, char **av, char **env)
{
	t_var	var;

	if (ac < 5)
		return (1);
	ft_bzero(&var, sizeof(t_var));
	var.n = ac - 4;
	var.ret = init_pipex(&var, env);
	if (var.ret == -1)
		exit_pipex(&var);
	while (var.i <= var.n)
	{
		pipex(av, env, &var, var.i);
		if (var.ret == 0)
			var.fork[var.i] = 1;
		else
			var.fork[var.i] = 0;
		var.i++;
	}
	var.i = 0;
	while (var.i <= var.n)
	{
		if (var.fork[var.i])
		{
			waitpid(var.pid[var.i], &var.status, 0);
			if (WIFEXITED(var.status))
				var.exit = WEXITSTATUS(var.status);
		}
		var.i++;
	}
	exit_pipex(&var);
	return (var.exit);
}
