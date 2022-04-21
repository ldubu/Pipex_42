/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:27:17 by ldubuche          #+#    #+#             */
/*   Updated: 2022/04/21 11:37:48 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	__close_pipes(t_data_b *pipex)
{
	int	i;

	i = 0;
	while (i < (2 * (pipex->cmd_nbr - 1)))
	{
		if (pipex->pipe[i] != -1)
		{
			close(pipex->pipe[i]);
			pipex->pipe[i] = -1;
		}
		i++;
	}
}

void	__free_close(t_data_b *pipex)
{
	if (pipex->fd1 != -1)
	{
		close(pipex->fd1);
		pipex->fd1 = -1;
	}
	if (pipex->fd2 != -1)
	{
		close(pipex->fd2);
		pipex->fd2 = -1;
	}
	if (pipex->pipe != NULL)
	{
		__close_pipes(pipex);
		free(pipex->pipe);
		pipex->pipe = NULL;
	}
	if (pipex->cmd_paths != NULL)
		__free_split(pipex->cmd_paths);
	if (pipex->cmd_arg != NULL)
		__free_split(pipex->cmd_arg);
}

void	__free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split[i]);
	free(split);
	split = NULL;
}

int	__error(char *str, t_data_b *pipex)
{
	__free_close(pipex);
	ft_printf("%s\n", str);
	exit(errno);
	return (errno);
}

void	__free_pip(int *pip)
{
	free(pip);
	__putstr_fd("\n", STDOUT_FILENO);
	exit(errno);
}
