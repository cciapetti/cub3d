/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_direction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoherfan <yoherfan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:43:49 by yoherfan          #+#    #+#             */
/*   Updated: 2025/07/22 16:53:08 by yoherfan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_direction(t_input *input, int *elements, int *indxs, char *dir)
{
	if (input->file[indxs[0]][indxs[1]] == dir[0] && \
		input->file[indxs[0]][indxs[1] + 1] == dir[1] && \
		input->file[indxs[0]][indxs[1] + 2] == ' ')
	{
		if (check_north(elements, dir) == 1)
			return (1);
		if (check_south(elements, dir) == 1)
			return (1);
		if (check_west(elements, dir) == 1)
			return (1);
		if (check_east(elements, dir) == 1)
			return (1);
	}
	return (0);
}

int check_north(int *elements, char *dir)
{
    if (dir[0] == 'N')
		{
			if (elements[0] == 0)
				elements[0] = 1;
			else
				return (1);			
		}
    return (0);
}

int check_south(int *elements, char *dir)
{
	if (dir[0] == 'S')
	{
		if (elements[1] == 0)
			elements[1] = 1;
		else
			return (1);			
	}
	return (0);
}

int check_west(int *elements, char *dir)
{
	if (dir[0] == 'W')
	{
		if (elements[2] == 0)
			elements[2] = 1;
		else
			return (1);			
	}
	return (0);
}

int check_east(int *elements, char *dir)
{
	if (dir[0] == 'E')
	{
		if (elements[3] == 0)
			elements[3] = 1;
		else
			return (1);			
	}
    return (0);
}
