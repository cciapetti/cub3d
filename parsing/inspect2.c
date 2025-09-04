/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspect2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoherfan <yoherfan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:40:25 by yoherfan          #+#    #+#             */
/*   Updated: 2025/09/04 11:21:02 by yoherfan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	inspect_file_exe(t_input *input, int *indxs, int *elements)
{
	while (++indxs[0] < input->file_rows)
	{
		indxs[1] = 0;
		while (input->file[indxs[0]][indxs[1]] == ' ' && \
			!(set_elements(elements, 1) == 0))
			indxs[1]++;
		if (input->file[indxs[0]][indxs[1]] == '\0' || \
			ft_strlen(input->file[indxs[0]]) == 0)
			continue ;
		else if (inspect_line(input, elements, indxs) == 1)
			if (set_elements(elements, 1) == 0)
				break ;
	}
}

int	inspect_bgcolors_exe(char **rgbmat, t_skyfloor *skfl)
{
	int	i;
	int	j;

	i = -1;
	while (rgbmat[++i] != NULL)
	{
		j = -1;
		while (rgbmat[i][++j] != '\0')
			if (ft_isdigit(rgbmat[i][j]) == 0)
				return (1);
		if (ft_atoi(rgbmat[i]) < 0 || ft_atoi(rgbmat[i]) > 255)
			return (1);
	}
	if (i != 3)
		return (1);
	skfl->rgb_r = (int)ft_atoi(rgbmat[0]);
	skfl->rgb_g = (int)ft_atoi(rgbmat[1]);
	skfl->rgb_b = (int)ft_atoi(rgbmat[2]);
	return (0);
}
