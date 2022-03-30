/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:02:51 by ldubuche          #+#    #+#             */
/*   Updated: 2022/01/04 11:02:51 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCT_H
# define FT_STRUCT_H

typedef struct flags
{
	int		minus_fla;
	int		plus_fla;
	int		space_fla;
	int		diese_fla;
	int		zero_fla;

	int		width;
	int		pre;

	char	types;

	int		size;

	int		len;
	int		i;
	int		null;
	int		is_zero;
}	t_struct;

#endif
