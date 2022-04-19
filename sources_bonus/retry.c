/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:01:40 by ldubuche          #+#    #+#             */
/*   Updated: 2022/04/19 11:01:40 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data_b	pipex;

	pipex = (t_data_b){0, 0, argv, argc, argc - 3, envp, NULL, NULL, NULL, \
	0, NULL, 0};
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

	i = 0;
	pipex->pipe = (int *) malloc(sizeof(int ) * 2 * (pipex->cmd_nbr - 1));
	if (pipex->pipe == NULL)
		return (__error(strerror(errno), errno));
	while (i < pipex->cmd_nbr - 1)
	{
		if(pipe(pipex->pipe + (2 * i)) < 0)
			return (__error("fail pipe", errno));
		i++;
	}
	i = 0;
	while (i < pipex->cmd_nbr)
	{
		__child_bonus(*pipex, i);
		i++;
	}
	return (0);
}

int	__child_bonus(t_data_b pipex, int i)
{
	int			status;
	int			j;

	j = 0;
	pipex.id = fork();
	if (!pipex.id)
	{
		if (i == 0)
		{
			pipex.fd1 = open(pipex.argv[1], O_RDONLY);
			if (pipex.fd1 == -1)
				return (errno);
			__redirection(pipex.fd1, pipex.pipe[1]);
		}
		else if (i == pipex.cmd_nbr - 1)
		{
			pipex.fd2 = open(pipex.argv[pipex.cmd_nbr + 2], O_TRUNC \
			| O_CREAT | O_RDWR, S_IRWXU);
			if (pipex.fd2 == -1)
				return (errno);
			__redirection(pipex.pipe[2 * i - 2], pipex.fd2);
		}
		else
			__redirection(pipex.pipe[2 * i - 2], pipex.pipe[2 * i + 1]);
		__close_pipes(&pipex);
		pipex.cmd_arg = __split(pipex.argv[i + 2], ' ');
	fprintf(stderr, "Child_b__child_bonus n %d cmd = %s\n", i, pipex.cmd_arg[0]);
	if (pipex.cmd_arg == NULL)
		return (__bonus_free_error("Split fail", &pipex));
	while (pipex.envp[j] != NULL)
	{
		if (__strnstr(pipex.envp[j], "PATH", 4) != NULL)
		{
			if (access(pipex.cmd_arg[0], X_OK) == 0)
				return (execve(pipex.cmd_path, pipex.cmd_arg, pipex.envp));
			return (__cmd_bonus(&pipex, j));
		}
		j++;
	}
	}
	else
		waitpid(pipex.id, &status, 0);
	return (__bonus_free_error("PATH was not found", &pipex));
}

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

void	__redirection(int fd_0, int fd_1)
{
	dup2(fd_0, 0);
	dup2(fd_1, 1);
}

void	__close_pipes(t_data_b *pipex)
{
	int	i;

	i = 0;
	while (i < (2 * (pipex->cmd_nbr - 1)))
	{
		close(pipex->pipe[i]);
		i++;
	}
}