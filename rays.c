/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:52:49 by cciapett          #+#    #+#             */
/*   Updated: 2025/07/25 18:13:04 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int ft_check_map(int map_rayX, int map_rayY, t_input *input)
{
    int i;

    i = 0;
    if (input->file[map_rayY][map_rayX] == '1')
        return (printf("trovato muro in [%d, %d]\n", map_rayY, map_rayX), 1);
    else
    {
        // printf("Avanzo...");
    }
    return (0);
}

void    ft_compute_deltaDist(t_pc *pc, int x)
{
    pc->cameraX = 2*x/(float)WIDTH - 1;
    pc->rayDirX = pc->dirX + pc->planeX * pc->cameraX;
    pc->rayDirY = -pc->dirY + pc->planeY * pc->cameraX;
    pc->hit = 0;
    pc->lineHeight = 0.0;
    if (pc->rayDirX == 0)
        pc->deltaDistX = 1e30;
    else
        pc->deltaDistX = fabsf(1/pc->rayDirX);
    if (pc->rayDirY == 0)
        pc->deltaDistY = 1e30;
    else
        pc->deltaDistY = fabsf(1/pc->rayDirY);
}

void    ft_increment_ray(t_pc *pc)
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

void    ft_evaluate_distance(t_pc *pc, float distance, char side)
{
    if (side == 'v')
        distance = pc->sideDistX - pc->deltaDistX;
    else if (side == 'o')
        distance = pc->sideDistY - pc->deltaDistY;
    printf("Distanza: %f  ", distance);
    pc->lineHeight = HEIGHT / distance;
    printf("lineHeight: %f\n", pc->lineHeight);
}

void    ft_rays(t_pc *pc, t_input *input, t_win *win)
{
    int     x;
    int     map_rayX;
    int     map_rayY;
    float   distance;
    char    side;

    x = 0;
    while (x < WIDTH) //per ogni raggio
    {
        side = '\0';
        distance = 0;
        map_rayX = pc->mapX;
        map_rayY = pc->mapY;

        ft_compute_deltaDist(pc, x);
        ft_increment_ray(pc);
        while (pc->hit == 0) //finche il raggio non trova un muro
        {
            if (pc->sideDistX < pc->sideDistY)
            {
                pc->sideDistX += pc->deltaDistX;
                map_rayX += pc->stepX;
                side = 'v'; //colpito lato schermo verticale
                // printf("DISTNZA minore su X\n");
            }
            else
            {
                pc->sideDistY += pc->deltaDistY;
                map_rayY += pc->stepY;
                side = 'o'; //colpito lato schermo orizzontale
                // printf("DISTNZA minore su Y\n");
            }
            pc->hit = ft_check_map(map_rayX, map_rayY, input);
        }
        ft_evaluate_distance(pc, distance, side);
        if (pc->lineHeight > HEIGHT)
            pc->lineHeight = HEIGHT;
        ft_display(pc, win, x);
        x++;
    }
}
