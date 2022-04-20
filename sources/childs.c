/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:24:26 by ldubuche          #+#    #+#             */
/*   Updated: 2022/04/20 16:39:57 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*__cmd(char **paths, char *cmd, t_data_b *pipex)
{
	char	*tmp;
	char	*command;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = __strjoin(paths[i], "/");
		if (tmp == NULL)
			__error("Strjoin fail", pipex);
		command = __strjoin(tmp, cmd);
		if (tmp == NULL)
		{
			free(tmp);
			__error("Strjoin fail", pipex);
		}
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

static void	__redirection(int fd_0, int fd_1)
{
	dup2(fd_0, 0);
	dup2(fd_1, 1);
}

void	__child_bonus(t_data_b pipex)
{
	pipex.id = fork();
	if (pipex.id == 0)
	{
		if (pipex.i == 0)
			__redirection(pipex.fd1, pipex.pipe[1]);
		else if (pipex.i == pipex.cmd_nbr - 1)
			__redirection(pipex.pipe[2 * pipex.i - 2], pipex.fd2);
		else
			__redirection(pipex.pipe[2 * pipex.i - 2], \
			pipex.pipe[2 * pipex.i + 1]);
		__close_pipes(&pipex);
		pipex.cmd_arg = __split(pipex.argv[2 + pipex.here_doc + pipex.i], ' ');
		if (pipex.cmd_arg == NULL)
			__error("Split fail", &pipex);
		if (access(pipex.cmd_arg[0], X_OK) == 0)
			execve(pipex.cmd_path, pipex.cmd_arg, pipex.envp);
		pipex.cmd = __cmd(pipex.cmd_paths, pipex.cmd_arg[0], &pipex);
		if (!pipex.cmd)
		{
			__error(strerror(errno), &pipex);
			exit(1);
		}
		execve(pipex.cmd, pipex.cmd_arg, pipex.envp);
	}
}
