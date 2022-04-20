/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:09:15 by ldubuche          #+#    #+#             */
/*   Updated: 2022/04/19 14:09:15 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data_b pipex;	

	if (argc < 5)
		return (__error("./pipex file1 cmd1 cmd2 file2", 2));
	pipex = (t_data_b){-1, -1, argc, argc - 3, 2 * (argc - 4), 0, 0, -1, 0, \
	NULL, argv, envp, NULL, NULL, NULL, NULL, NULL, NULL};
	__get_file(&pipex);
	pipex.pipe = (int *)malloc(sizeof(int) * pipex.pipe_nbr);
	if (!pipex.pipe)
		return(__error("allocation error\n", 2));
	pipex.env_path = __path(&pipex);
	if (pipex.env_path == NULL)
		printf("error in env_path\n");
	pipex.cmd_paths = __split(pipex.env_path, ':');
	//gestion d'erreur de split
	__pipe_time(&pipex);
	while (++(pipex.i) < pipex.cmd_nbr)
		__child_bonus(pipex);
	__close_pipes(&pipex);
	waitpid(-1, NULL, 0);
	//free pipex
	return (0);
}

int	__get_file(t_data_b *pipex)
{
	if (__strncmp(pipex->argv[1], "here_doc", 9) == 0)
	{
		__here_doc(pipex);
		pipex->fd2 = open(pipex->argv[pipex->argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0000644);	
		if (pipex->fd2 == -1)
			return (errno);
	}
	else
	{
		pipex->fd1 = open(pipex->argv[1], O_RDONLY);
		if (pipex->fd1 == -1)
			return (errno);
		pipex->fd2 = open(pipex->argv[pipex->argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
		if (pipex->fd2 == -1)
			return (errno);
	}
	return (0);
}

void	__here_doc(t_data_b *pipex)
{
	if (pipex->argc < 6)
		__error("./pipex here_doc LIMITER cmd cmd1 [...] cmdn file"\
		, 2);
	pipex->here_doc = 1;
	pipex->limiter = pipex->argv[2];
	pipex->cmd_nbr--;
	pipex->pipe_nbr -=2;
	__get_instruction(pipex);
}

void    __get_instruction(t_data_b *pipex)
{
	char    *line;
	int		*pip;

	pip = (int *) malloc(sizeof(int) * 2);
	pipe(pip);
	//verfier le renvoi de cette fonction
	line = NULL;
	pipex->fd1 = pip[0];
	__putstr_fd("heredoc>", 0);
	line = __get_next_line(0);
	while (__strncmp(line, pipex->limiter, __strlen(pipex->limiter)) != 0)
	{
		__putstr_fd(line, pip[1]);
		free(line);
		__putstr_fd("heredoc>", 0);
		line = __get_next_line(STDOUT_FILENO);
	}
	pipex->fd1 = pip[0];
	close(pip[1]);
}

char	*__path(t_data_b *pipex)
{
	int	i;

	i = 0;
	while (pipex->envp[i] != NULL)
	{
		if (__strnstr(pipex->envp[i], "PATH", 4) != NULL)
			return (pipex->envp[i]);
		i++;
	}
	return(NULL);
}

void	__pipe_time(t_data_b *pipex)
{
	int i;

	i = 0;
	while (i < pipex->cmd_nbr - 1)
	{
		if (pipe(pipex->pipe + (2 * i)) < 0)
			write(2, "pipe\n", 5);
		i++;
	}
}

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

static void	sub_dup2(int fd_0, int fd_1)
{
	dup2(fd_0, 0);
	dup2(fd_1, 1);
}

void	__child_bonus(t_data_b pipex)
{
	pipex.id = fork();
	if (!pipex.id)
	{
		if (pipex.i == 0)
		{	
			sub_dup2(pipex.fd1, pipex.pipe[1]);
		}
		else if (pipex.i == pipex.cmd_nbr - 1)
			sub_dup2(pipex.pipe[2 * pipex.i - 2], pipex.fd2);
		else
			sub_dup2(pipex.pipe[2 * pipex.i - 2], pipex.pipe[2 * pipex.i + 1]);
		__close_pipes(&pipex);
		pipex.cmd_arg = __split(pipex.argv[2 + pipex.here_doc + pipex.i], ' ');
		pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_arg[0]);
		if (!pipex.cmd)
		{
			__error(strerror(errno), errno);
			exit(1);
		}
		execve(pipex.cmd, pipex.cmd_arg, pipex.envp);
	}
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
