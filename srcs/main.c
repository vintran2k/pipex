#include "pipex.h"

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

int	first_fork(char **env, t_var *var)
{
	//printf("0 = %s\n1 = %s\n2 = %s\n", var->str[0], var->str[1], var->str[2]);
	fprintf(stderr, "FIRST FORK BATARD!!!!!\n");
	if (var->file == -1)
		return (-1);
	dup2(var->file, STDIN_FILENO);
	dup2(var->fd[0][1], STDOUT_FILENO);
	close_first(var);
	if (execve(var->str[0], var->str, env) == -1)
	{
		printf("errno = %d\n", errno);
		if (errno == 2 || errno == 13) // a modif
			cmd_error(var);
		else
			perror("pipex");
	}
	return (0);
}

int	mid_fork(char **env, t_var *var, int i)
{
	fprintf(stderr, "MID FORK BATARD!!!!!\n");
	dup2(var->fd[i - 1][0], STDIN_FILENO);
	dup2(var->fd[i][1], STDOUT_FILENO);
	close_mid(var, i);
	if (execve(var->str[0], var->str, env) == -1)
	{
		fprintf(stderr, "excve failed in midfork\n");
		if (errno == 2 || errno == 13)
			cmd_error(var);
		else
			perror("pipex");
	}
	return (0);
}

int	last_fork(char **env, t_var *var)
{
	if (var->file == -1)
		return (-1);
	fprintf(stderr, "LAST FORK BATARD!!!!!\n");
	dup2(var->fd[var->n - 1][0], STDIN_FILENO);
	dup2(var->file, STDOUT_FILENO);
	close_last(var);
	if (execve(var->str[0], var->str, env) == -1)
	{
		fprintf(stderr, "excve failed in lastfork\n");
		if (errno == 2 || errno == 13)
			cmd_error(var);
		else
			perror("pipex");
	}
	return (0);
}

int	pipex(char **av, char **env, t_var *var, int i)
{
	var->ret = init_forking(av, env, var, i);
	printf("str[0] = %s\ni vaut %d\n", var->str[0], i);
	if (var->ret < 0)
		return (var->ret);
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
	hub_close(var, i);
	//ft_free_tab(var->path);
	//var->path = NULL;
	free(var->cmdpath);
	var->cmdpath = NULL;
	free(var->cmd);
	var->cmd = NULL;
	free(var->opt);
	var->opt = NULL;
	if (var->pid[i] == 0)
	{
		fprintf(stderr, "passage pour pid = %d\n", var->pid[i]);
		exit_pipex(var);
		exit(0);
	}
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
	if (init_pipex(&var) == -1)
		exit_pipex(&var);
	i = 0;
	var.path = get_env_path(env);
	while (i <= var.n)
	{
		var.ret = pipex(av, env, &var, i);
		if (var.ret < 0 && var.ret != -6)
			break ;
		i++;
	}
	i = var.n + 1;
	while (i > 0)
	{
		waitpid(var.pid[i - 1], &var.status, 0);
		i--;
	}
	exit_pipex(&var);
	return (var.ret);
}
