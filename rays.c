/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:52:49 by cciapett          #+#    #+#             */
/*   Updated: 2025/09/09 16:25:10 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_map(int map_rayx, int map_rayy, t_input *input)
{
	int	i;

	i = 0;
	if (input->map[map_rayy][map_rayx] == '1')
		return (1);
	return (0);
}

void	ft_update_pos_ray(t_pc *pc, int *map_rayx, int *map_rayy)
{
	pc->mapX = (int)pc->posX;
	pc->mapY = (int)pc->posY;
	*map_rayx = pc->mapX;
	*map_rayy = pc->mapY;
}

void	ft_rays(t_pc *pc, t_input *input, t_win *win)
{
	int		x;
	int		map_rayx;
	int		map_rayy;
	float	distance;
	char	side;

	x = -1;
	while (++x < WIDTH)
	{
		side = '\0';
		distance = 0;
		ft_update_pos_ray(pc, &map_rayx, &map_rayy);
		ft_compute_deltaDist(pc, x);
		ft_increment_ray(pc);
		while (pc->hit == 0)
		{
			if (pc->sideDistX < pc->sideDistY)
				ft_increment_distance('X', pc, &map_rayx, &side);
			else
				ft_increment_distance('Y', pc, &map_rayy, &side);
			pc->hit = ft_check_map(map_rayx, map_rayy, input);
		}
		ft_evaluate_height(pc, distance, side);
		ft_display(pc, win, x, side);
	}
}
