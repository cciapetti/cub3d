/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:50:40 by cciapett          #+#    #+#             */
/*   Updated: 2025/09/11 12:19:21 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_compute_delta_dist(t_pc *pc, int x)
{
	pc->cameraX = 2 * x / (float)WIDTH - 1;
	pc->rayDirX = pc->dirX + pc->planeX * pc->cameraX;
	pc->rayDirY = -pc->dirY - pc->planeY * pc->cameraX;
	pc->hit = 0;
	pc->lineHeight = 0.0;
	if (pc->rayDirX == 0)
		pc->deltaDistX = 1e30;
	else
		pc->deltaDistX = fabsf(1 / pc->rayDirX);
	if (pc->rayDirY == 0)
		pc->deltaDistY = 1e30;
	else
		pc->deltaDistY = fabsf(1 / pc->rayDirY);
}

void	ft_increment_ray(t_pc *pc)
{
	if (pc->rayDirX >= 0)
	{
		pc->sideDistX = (pc->mapX + 1.0 - pc->posX) * pc->deltaDistX;
		pc->stepX = 1;
	}
	else
	{
		pc->sideDistX = (pc->posX - pc->mapX) * pc->deltaDistX;
		pc->stepX = -1;
	}
	if (pc->rayDirY >= 0)
	{
		pc->sideDistY = (pc->mapY + 1.0 - pc->posY) * pc->deltaDistY;
		pc->stepY = 1;
	}
	else
	{
		pc->sideDistY = (pc->posY - pc->mapY) * pc->deltaDistY;
		pc->stepY = -1;
	}
}

void	ft_evaluate_height(t_pc *pc, float distance, char side)
{
	if (side == 'v')
		distance = pc->sideDistX - pc->deltaDistX;
	else if (side == 'o')
		distance = pc->sideDistY - pc->deltaDistY;
	pc->lineHeight = HEIGHT / distance;
	pc->tex_scale = 1.0;
	if (pc->lineHeight > HEIGHT)
	{
		pc->lineHeight = HEIGHT;
		pc->tex_scale = (double)HEIGHT / (double) pc->lineHeight;
	}
}

void	ft_increment_distance(char dir, t_pc *pc, int *map_ray, char *side)
{
	if (dir == 'X')
	{
		pc->sideDistX += pc->deltaDistX;
		*map_ray += pc->stepX;
		*side = 'v';
	}
	else if (dir == 'Y')
	{
		pc->sideDistY += pc->deltaDistY;
		*map_ray += pc->stepY;
		*side = 'o';
	}
}
