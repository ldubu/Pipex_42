/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:57:36 by ldubuche          #+#    #+#             */
/*   Updated: 2022/04/06 16:04:57 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data_b	pipex;
	int		i;
	int	 status;

	i = 2;
	if (argc < 5)
		return (__error("./pipex file1 cmd1 [cmd...] cmdn file2", 2));
	pipex = (t_data_b){0, 0, argv, argc, envp, NULL, NULL, NULL, NULL, 0};
	pipex.pipe = (int **) malloc(sizeof(int *) * (argc - 3));
	pipex.id = (int *) malloc(sizeof(int) * (argc - 2));
	if (pipex.pipe == NULL)
		return (__error(strerror(errno), errno));
	while (i < argc - 1)
	{
		pipex.pipe[i - 2] = (int *) malloc(sizeof(int) * 2);
		if (pipex.pipe[i - 2] == NULL)
			return (__error(strerror(errno), errno));
		pipex.id[i - 2] = fork();
		if (pipex.id[i - 2] == 0)
		{
			__child(&pipex, i - 2);
			i = argc;
		}
		i++;
	}
	i = 0;
	while (i < argc - 3)
	{
		waitpid(pipex.id[i], &status, 0);
		i++;
	}
	return (0);
}

int	__child(t_data_b *pipex, int i)
{
	if (i == 0)
	{
		pipex->fd1 = open(pipex->argv[1], O_RDONLY);
		if (pipex->fd1 == -1)
			return (errno);
		dup2(pipex->fd1, STDIN_FILENO);
	}
	else
	{
		dup2(pipex->pipe[i - 1][0], STDIN_FILENO);
		close(pipex->pipe[i - 1][1]);
	}
	if (i == pipex->argc -1)
	{
		pipex->fd2 = open(pipex->argv[4], O_TRUNC | O_CREAT | O_RDWR, S_IRWXU);
		if (pipex->fd2 == -1)
			return (errno);
		dup2(pipex->fd2, STDOUT_FILENO);
	}
	else
	{
		dup2(pipex->pipe[i][1], STDOUT_FILENO);
		close(pipex->pipe[i][0]);
	}
	pipex->cmd_arg = __split(pipex->argv[2], ' ');
	if (pipex->cmd_arg == NULL)
		return (__bonus_free_error("Split fail", pipex));
	while (pipex->envp[i] != NULL)
	{
		if (__strnstr(pipex->envp[i], "PATH", 4) != NULL)
		{
			if (access(pipex->cmd_arg[0], X_OK) == 0)
				return (execve(pipex->cmd_path, pipex->cmd_arg, pipex->envp));
			return (__cmd_bonus(pipex, i));
		}
		i++;
	}
	return (__bonus_free_error("PATH was not found", pipex));
}

/*
int		j = read(0, buff, 12);
	fprintf(stderr, "j = %d\n", j);
	fprintf(stderr, "buff = %s\n", buff);
	fprintf(stderr, "errno = %s\n", strerror(errno));*/

int	__cmd_bonus(t_data_b *pipex, int i)
{
	int		j;
	char	*tmp;
	char	**split;

	tmp = __strdup(&(pipex->envp[i][5]));
	if (tmp == NULL)
		return (__bonus_free_error("Strdup fail", pipex));
	split = __split(tmp, ':');
	if (split == NULL)
		return (__bonus_free_error("Split fail", pipex));
	free(tmp);
	j = 0;
	while (split[j] != NULL)
	{
		tmp = __strjoin(split[j], "/");
		pipex->cmd_path = __strjoin(tmp, pipex->cmd_arg[0]);
		if (access(pipex->cmd_path, X_OK) == 0)
			return (execve(pipex->cmd_path, pipex->cmd_arg, pipex->envp));
		free (split[j++]);
		free (pipex->cmd_path);
		free (tmp);
	}
	__free_split(pipex->cmd_arg, 0);
	__free_split(split, j);
	return (__error("Command not found", 127));
}
