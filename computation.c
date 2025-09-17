/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoherfan <yoherfan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:50:40 by cciapett          #+#    #+#             */
/*   Updated: 2025/09/17 17:28:29 by yoherfan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_compute_delta_dist(t_pc *pc, int x)
{
	pc->camerax = 2 * x / (float)WIDTH - 1;
	pc->raydirx = pc->dirx + pc->planex * pc->camerax;
	pc->raydiry = -pc->diry - pc->planey * pc->camerax;
	pc->hit = 0;
	pc->lineheight = 0.0;
	if (pc->raydirx == 0)
		pc->deltadistx = 1e30;
	else
		pc->deltadistx = fabsf(1 / pc->raydirx);
	if (pc->raydiry == 0)
		pc->deltadisty = 1e30;
	else
		pc->deltadisty = fabsf(1 / pc->raydiry);
}

void	ft_increment_ray(t_pc *pc)
{
	if (pc->raydirx >= 0)
	{
		pc->sidedistx = (pc->mapx + 1.0 - pc->posx) * pc->deltadistx;
		pc->stepx = 1;
	}
	else
	{
		pc->sidedistx = (pc->posx - pc->mapx) * pc->deltadistx;
		pc->stepx = -1;
	}
	if (pc->raydiry >= 0)
	{
		pc->sidedisty = (pc->mapy + 1.0 - pc->posy) * pc->deltadisty;
		pc->stepy = 1;
	}
	else
	{
		pc->sidedisty = (pc->posy - pc->mapy) * pc->deltadisty;
		pc->stepy = -1;
	}
}

void	ft_evaluate_height(t_pc *pc, float distance, char side)
{
	if (side == 'v')
		distance = pc->sidedistx - pc->deltadistx;
	else if (side == 'o')
		distance = pc->sidedisty - pc->deltadisty;
	pc->lineheight = HEIGHT / distance;
}

void	ft_increment_distance(char dir, t_pc *pc, int *map_ray, char *side)
{
	if (dir == 'X')
	{
		pc->sidedistx += pc->deltadistx;
		*map_ray += pc->stepx;
		*side = 'v';
	}
	else if (dir == 'Y')
	{
		pc->sidedisty += pc->deltadisty;
		*map_ray += pc->stepy;
		*side = 'o';
	}
}
