/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoherfan <yoherfan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:27:45 by yoherfan          #+#    #+#             */
/*   Updated: 2025/07/22 16:28:32 by yoherfan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	inspect_file(t_input *input)
{
	int	indxs[2];
	int	elements[6];

	indxs[0] = -1;
	set_elements(elements, 0);
	while (++indxs[0] < input->file_rows)
	{
		indxs[1] = -1;
		while (++indxs[1] < (int)ft_strlen(input->file[indxs[0]]))
		{
			if (input->file[indxs[0]][indxs[1]] == ' ')
				continue;
			if (check_direction(input, elements, indxs, "NO") == 1 || \
				check_direction(input, elements, indxs, "SO") == 1 || \
				check_direction(input, elements, indxs, "WE") == 1 || \
				check_direction(input, elements, indxs, "EA") == 1 || \
				check_field(input, elements, indxs, "F") == 1 || \
				check_field(input, elements, indxs, "C") == 1)
				return (1);
		}
	}
	return (set_elements(elements, 1));
}
