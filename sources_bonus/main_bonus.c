/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:57:36 by ldubuche          #+#    #+#             */
/*   Updated: 2022/04/19 11:00:34 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data_b	pipex;

	pipex = (t_data_b){0, 0, argv, argc, argc - 3, envp, NULL, NULL, NULL, \
	NULL, NULL, 0};
	if (argc < 5)
		return (__error("./pipex file1 cmd1 [...] cmdn file2", 2));
	if (__strncmp(argv[1], "here_doc", 9) == 0)
	{
		if (argc < 6)
			return (__error("./pipex here_doc LIMITER cmd cmd1 [...] cmdn file"\
			, 2));
		pipex.here_doc = argv[2];
		pipex.cmd_nbr--;
	}
	__time_to_pipe(&pipex);
	return (0);
}

int	__time_to_pipe(t_data_b *pipex)
{
	int			i;
	int			status;
	int			*pip;

	pip = NULL;
	i = 0;
	if (pipex->here_doc != NULL)
		pip = __get_instruction(pipex);
	pipex->pipe = (int **) malloc(sizeof(int *) * (pipex->cmd_nbr - 1));
	if (pipex->pipe == NULL)
		return (__error(strerror(errno), errno));
	pipex->id = (int *) malloc(sizeof(int) * (pipex->cmd_nbr));
	if (pipex->id == NULL)
	{
		free(pipex->pipe);
		return (__error(strerror(errno), errno));
	}
	while (i < pipex->cmd_nbr - 1)
	{
		pipex->pipe[i] = (int *) malloc(sizeof(int) * 2);
		if (pipex->pipe[i] == NULL)
			return (__error(strerror(errno), errno));
		pipe(pipex->pipe[i]);
		i++;
	}
	i = 0;
	while (i < pipex->cmd_nbr)
	{
		printf("i = %d, cmd_nbr = %d\n", i, pipex->cmd_nbr);
		pipex->id[i] = fork();
		if (pipex->id[i] == 0)
		{
			__child(pipex, i, pip);
			fprintf(stderr, "sort pas par la\n");
			i = pipex->argc;
		}
		i++;
	}
	i = 0;
	while (i < pipex->cmd_nbr)
	{
		fprintf(stderr, "enter wait n %d\n", i);
		waitpid(pipex->id[i], &status, 0);
		i++;
	}
	return (0);
}

int	*__get_instruction(t_data_b *pipex)
{
	char	*line;
	int		*pip;

	pip = (int *) malloc(sizeof(int) * 2);
	pipe(pip);
	line = __get_next_line(STDOUT_FILENO);
	while (__strncmp(line, pipex->here_doc, __strlen(pipex->here_doc)) != 0)
	{
		__putstr_fd(line, pip[1]);
		__putstr_fd("\n", pip[1]);
		free(line);
		line = __get_next_line(STDOUT_FILENO);
	}
	return (pip);
}

int	__child(t_data_b *pipex, int i, int *pip)
{
	int	j;

	j = 0;
	(void) pip;
	fprintf(stderr, "Child n %d\n", i);
	if (i == 0)
	{
		pipex->fd1 = open(pipex->argv[1], O_RDONLY);
		if (pipex->fd1 == -1)
			return (errno);
		dup2(pipex->fd1, STDIN_FILENO);
	}
	else
	{
		fprintf(stderr, "Child %d pipe %d in\n", i, i - 1);
		dup2(pipex->pipe[i - 1][0], STDIN_FILENO);
		close(pipex->pipe[i - 1][1]);
	}
	if (i == pipex->cmd_nbr -1)
	{
		pipex->fd2 = open(pipex->argv[pipex->cmd_nbr + 2], O_TRUNC \
		| O_CREAT | O_RDWR, S_IRWXU);
		if (pipex->fd2 == -1)
			return (errno);
		dup2(pipex->fd2, STDOUT_FILENO);
	}
	else
	{
		fprintf(stderr, "Child %d pipe %d out\n", i, i);
		dup2(pipex->pipe[i][1], STDOUT_FILENO);
		close(pipex->pipe[i][0]);
	}
	pipex->cmd_arg = __split(pipex->argv[i + 2], ' ');
	fprintf(stderr, "Child n %d cmd = %s\n", i, pipex->cmd_arg[0]);
	/*char **buff = NULL;
	read(0, &buff, 7);
	write(1, &buff, 7);*/
	if (pipex->cmd_arg == NULL)
		return (__bonus_free_error("Split fail", pipex));
	while (pipex->envp[j] != NULL)
	{
		if (__strnstr(pipex->envp[j], "PATH", 4) != NULL)
		{
			if (access(pipex->cmd_arg[0], X_OK) == 0)
				return (execve(pipex->cmd_path, pipex->cmd_arg, pipex->envp));
			return (__cmd_bonus(pipex, j));
		}
		j++;
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

	fprintf(stderr, "enter cmd\n");
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
		//fprintf(stderr, "enter while\n");
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
	fprintf(stderr, ".%s.\n", pipex->cmd_arg[0]);
	return (__error("Command not found", 127));
}
