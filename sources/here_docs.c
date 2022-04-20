/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:25:47 by ldubuche          #+#    #+#             */
/*   Updated: 2022/04/20 16:42:38 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	__here_doc(t_data_b *pipex)
{
	if (pipex->argc < 6)
		__error("./pipex here_doc LIMITER cmd [...] cmdn file", pipex);
	pipex->here_doc = 1;
	pipex->limiter = pipex->argv[2];
	pipex->cmd_nbr--;
	pipex->pipe_nbr -= 2;
	__get_instruction(pipex);
}

void	__get_instruction(t_data_b *pipex)
{
	char	*line;
	int		*pip;

	pip = (int *) malloc(sizeof(int) * 2);
	if (pipe(pip) < 0)
		__error("Pipe process fail", pipex);
	pipex->fd1 = pip[0];
	line = NULL;
	__putstr_fd("heredoc>", STDOUT_FILENO);
	line = __get_next_line(STDOUT_FILENO);
	if (line == NULL)
		__free_pip(pip);
	while (__strncmp(line, pipex->limiter, __strlen(pipex->limiter)) != 0)
	{
		__putstr_fd(line, pip[1]);
		free(line);
		__putstr_fd("heredoc>", STDOUT_FILENO);
		line = __get_next_line(STDOUT_FILENO);
		if (line == NULL)
			__free_pip(pip);
	}
	close(pip[1]);
	free(pip);
}
