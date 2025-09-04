/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoherfan <yoherfan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:33:45 by yoherfan          #+#    #+#             */
/*   Updated: 2025/09/03 12:00:58 by yoherfan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_dir_line(t_input *input, int *elements, int *indxs, char *dir)
{
	if (input->file[indxs[0]][indxs[1]] == dir[0] && \
		input->file[indxs[0]][indxs[1] + 1] == dir[1] && \
		input->file[indxs[0]][indxs[1] + 2] == ' ')
	{
		check_north(input, elements, indxs, dir);
		check_south(input, elements, indxs, dir);
		check_west(input, elements, indxs, dir);
		check_east(input, elements, indxs, dir);
		return (1);
	}
	return (0);
}

int	is_skyfloor_line(t_input *input, int *elements, int *indxs, char *dir)
{
	int	j;

	j = indxs[1] + 2;
	if (input->file[indxs[0]][indxs[1]] == dir[0] && \
		input->file[indxs[0]][indxs[1] + 1] == ' ')
	{
		if (dir[0] == 'F')
			is_floor_line_exe(input, elements, indxs, j);
		if (dir[0] == 'C')
			is_sky_line_exe(input, elements, indxs, j);
		return (1);
	}
	return (0);
}

void	is_floor_line_exe(t_input *input, int *elements, int *indxs, int j)
{
	if (elements[4] == 0)
	{
		elements[4] = 1;
		while (input->file[indxs[0]][j] == ' ')
			j++;
		input->floor.line = ft_strdup(&input->file[indxs[0]][j]);
	}
	else
		elements[4] = -1;
}

void	is_sky_line_exe(t_input *input, int *elements, int *indxs, int j)
{
	if (elements[5] == 0)
	{
		elements[5] = 1;
		while (input->file[indxs[0]][j] == ' ')
			j++;
		input->sky.line = ft_strdup(&input->file[indxs[0]][j]);
	}
	else
		elements[5] = -1;
}
