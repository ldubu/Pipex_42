/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:48:32 by ldubuche          #+#    #+#             */
/*   Updated: 2022/04/20 16:43:24 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_data
{
	int		fd1;
	int		fd2;
	char	**argv;
	int		argc;
	char	**envp;
	int		*pipe;
	char	**cmd_arg;
	char	*cmd_path;
	int		ret;
}	t_data;

typedef struct s_data_b
{
	int		fd1;
	int		fd2;
	int		argc;
	int		cmd_nbr;
	int		pipe_nbr;
	int		here_doc;
	int		ret;
	int		i;
	int		id;
	int		*pipe;
	char	**argv;
	char	**envp;
	char	**cmd_arg;
	char	*cmd_path;
	char	*limiter;
	char	*env_path;
	char	**cmd_paths;
	char	*cmd;
}	t_data_b;

#endif