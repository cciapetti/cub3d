/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoherfan <yoherfan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:52:49 by cciapett          #+#    #+#             */
/*   Updated: 2025/09/17 16:33:42 by yoherfan         ###   ########.fr       */
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

void	ft_update_pos_ray(t_pc *pc)
{
	pc->mapx = (int)pc->posx;
	pc->mapy = (int)pc->posy;
}

void	ft_rays(t_pc *pc, t_input *input, t_win *win)
{
	int		x;
	float	distance;
	char	side;

	x = -1;
	while (++x < WIDTH)
	{
		side = '\0';
		distance = 0;
		ft_update_pos_ray(pc);
		ft_compute_delta_dist(pc, x);
		ft_increment_ray(pc);
		while (pc->hit == 0)
		{
			if (pc->sidedistx < pc->sidedisty)
				ft_increment_distance('X', pc, &pc->mapx, &side);
			else
				ft_increment_distance('Y', pc, &pc->mapy, &side);
			pc->hit = ft_check_map(pc->mapx, pc->mapy, input);
		}
		ft_evaluate_height(pc, distance, side);
		ft_display(pc, win, x, side);
	}
}
