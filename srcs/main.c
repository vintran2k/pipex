#include "pipex.h"

int	first_fork(char **env, t_var *var)
{
	dup2(var->file, STDIN_FILENO);
	dup2(var->fd[0][1], STDOUT_FILENO);
	close_first(var);
	if (execve(var->str[0], var->str, env) == -1)
		return (-1);
	return (0);
}

int	mid_fork(char **env, t_var *var, int i)
{
	dup2(var->fd[i - 1][0], STDIN_FILENO);
	dup2(var->fd[i][1], STDOUT_FILENO);
	close_mid(var, i);
	if (execve(var->str[0], var->str, env) == -1)
		return (-1);
	return (0);
}

int	last_fork(char **env, t_var *var)
{
	//fprintf(stderr, "last fork BATARD !!\n");
	dup2(var->fd[var->n - 1][0], STDIN_FILENO);
	dup2(var->file, STDOUT_FILENO);
	close_last(var);
	if (execve(var->str[0], var->str, env) == -1)
		return (-1);
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
	//fprintf(stderr, "ret = %d pour i = %d\n", var->ret , i);
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
	int		i;
	t_var	var;

	if (ac < 5)
		return (1);
	ft_bzero(&var, sizeof(t_var));
	var.n = ac - 4;
	if (init_pipex(&var, env) == -1)
		exit_pipex(&var);
	i = 0;
	while (i <= var.n)
	{
		pipex(av, env, &var, i);
		if (var.ret == 0)
			waitpid(var.pid[i], &var.status, 0);
		i++;
	}
	i = 0;
	/*while (i <= var.n)
	{
		waitpid(var.pid[i], &var.status, 0);
		i++;
	}*/
	//waitpid(0, &var.status, 0);
	exit_pipex(&var);
	return (var.ret);
}

// The next test will use the following command:
//./pipex "/dev/urandom" "cat" "head -1" "outs/test-xx.txt"
