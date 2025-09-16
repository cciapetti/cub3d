/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:41:32 by cciapett          #+#    #+#             */
/*   Updated: 2025/09/12 11:52:19 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	ft_search_letter(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == c)
			return (str[i]);
	}
	return (0);
}

static void	ft_det_dir(t_pc *pc, char c)
{
	if (c == 'N')
	{
		pc->dirx = 0;
		pc->diry = 1;
	}
	if (c == 'S')
	{
		pc->dirx = 0;
		pc->diry = -1;
	}
	if (c == 'E')
	{
		pc->dirx = 1;
		pc->diry = 0;
	}
	if (c == 'W')
	{
		pc->dirx = -1;
		pc->diry = 0;
	}
}

void	ft_read_map(t_input *input, t_pc *pc)
{
	int		i;
	int		j;
	char	*str;

	str = "NSEW";
	i = -1;
	while (input->map[++i] != NULL)
	{
		j = -1;
		while (input->map[i][++j] != '\0')
		{
			if (ft_search_letter(input->map[i][j], str) != 0)
			{
				pc->posx = j + 0.5;
				pc->posy = i + 0.5;
				pc->mapx = (int)pc->posx;
				pc->mapy = (int)pc->posy;
				ft_det_dir(pc, ft_search_letter(input->map[i][j], str));
			}
		}
	}
	pc->planex = pc->diry * FOV_SCALE;
	pc->planey = -pc->dirx * FOV_SCALE;
}
