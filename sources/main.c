/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:52:31 by ldubuche          #+#    #+#             */
/*   Updated: 2022/04/04 14:57:06 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	pipex;

	if (argc != 5)
		return (__error("./pipex file1 cmd1 cmd2 file2", 2));
	pipex = (t_data){0, 0, argv, argc, envp, NULL, NULL, NULL, 0};
	pipex.pipe = (int *) malloc(sizeof(int) * 2);
	if (pipex.pipe == NULL)
		return (__error(strerror(errno), 0));
	if (pipe(pipex.pipe) == -1)
		return (__error(strerror(errno), 0));
	return (__time_to_fork(&pipex));
}

int	__time_to_fork(t_data *pipex)
{
	int		id1;
	int		id2;

	id2 = -1;
	id1 = fork();
	if (id1 == -1)
		return (__free_error(strerror(errno), pipex));
	if (id1 == 0)
	{
		pipex->ret = __child1(pipex);
		return (__free_error(strerror(errno), pipex));
	}
	id2 = fork();
	if (id2 == -1)
		return (__free_error(strerror(errno), pipex));
	if (id2 == 0)
	{
		pipex->ret = __child2(pipex);
		return (__free_error(strerror(errno), pipex));
	}
	return (__free_parent(id1, id2, pipex));
}

int	__child1(t_data *pipex)
{
	int		i;

	i = 0;
	pipex->fd1 = open(pipex->argv[1], O_RDONLY);
	if (pipex->fd1 == -1)
		return (errno);
	dup2(pipex->pipe[1], STDOUT_FILENO);
	close(pipex->pipe[0]);
	dup2(pipex->fd1, STDIN_FILENO);
	pipex->cmd_arg = __split(pipex->argv[2], ' ');
	if (pipex->cmd_arg == NULL)
		return (__free_error("Split fail", pipex));
	while (pipex->envp[i] != NULL)
	{
		if (__strnstr(pipex->envp[i], "PATH", 4) != NULL)
		{
			if (access(pipex->cmd_arg[0], X_OK) == 0)
				return (execve(pipex->cmd_path, pipex->cmd_arg, pipex->envp));
			return (__cmd(pipex, i));
		}
		i++;
	}
	return (__free_error("PATH was not found", pipex));
}

int	__child2(t_data *pipex)
{
	int		i;

	i = 0;
	pipex->fd2 = open(pipex->argv[4], O_TRUNC | O_CREAT | O_RDWR, S_IRWXU);
	if (pipex->fd2 == -1)
		return (errno);
	dup2(pipex->pipe[0], STDIN_FILENO);
	close(pipex->pipe[1]);
	dup2(pipex->fd2, STDOUT_FILENO);
	pipex->cmd_arg = __split(pipex->argv[3], ' ');
	if (pipex->cmd_arg == NULL)
		return (__free_error("Split fail", pipex));
	while (pipex->envp[i] != NULL)
	{
		if (__strnstr(pipex->envp[i], "PATH", 4) != NULL)
		{
			if (access(pipex->cmd_arg[0], X_OK) == 0)
				return (execve(pipex->cmd_path, pipex->cmd_arg, pipex->envp));
			return (__cmd(pipex, i));
		}
		i++;
	}
	return (__free_error("PATH was not found", pipex));
}
/*int		j = read(0, buff, 12);
	fprintf(stderr, "j = %d\n", j);
	fprintf(stderr, "buff = %s\n", buff);
	fprintf(stderr, "errno = %s\n", strerror(errno));*/

int	__cmd(t_data *pipex, int i)
{
	int		j;
	char	*tmp;
	char	**split;

	tmp = __strdup(&(pipex->envp[i][5]));
	if (tmp == NULL)
		return (__free_error("Strdup fail", pipex));
	split = __split(tmp, ':');
	if (split == NULL)
		return (__free_error("Split fail", pipex));
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
