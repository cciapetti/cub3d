/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:52:49 by cciapett          #+#    #+#             */
/*   Updated: 2025/09/05 18:51:17 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_check_map(int map_rayX, int map_rayY, t_input *input, t_pc *pc)
{
    int i;

    i = 0;
    (void)pc;
    if (input->map[map_rayY][map_rayX] == '1')
        return (1);
    return (0);
}


void    ft_update_pos_ray(t_pc *pc, int *map_rayX, int *map_rayY)
{
    pc->mapX = (int)pc->posX;
    pc->mapY = (int)pc->posY;
    *map_rayX = pc->mapX;
    *map_rayY = pc->mapY;
}

void    ft_rays(t_pc *pc, t_input *input, t_win *win)
{
    int     x;
    int     map_rayX;
    int     map_rayY;
    float   distance;
    char    side;

    x = -1;
    while (++x < WIDTH) //per ogni raggio
    {
        side = '\0';
        distance = 0;
        ft_update_pos_ray(pc, &map_rayX, &map_rayY);
        ft_compute_deltaDist(pc, x);
        ft_increment_ray(pc);
        while (pc->hit == 0) //finche il raggio non trova un muro
        {
            if (pc->sideDistX < pc->sideDistY)
                ft_increment_distance('X', pc, &map_rayX, &side);
            else
                ft_increment_distance('Y', pc, &map_rayY, &side);
            pc->hit = ft_check_map(map_rayX, map_rayY, input, pc);
        }
        ft_evaluate_height(pc, distance, side);
        ft_display(pc, win, x, side);
    }
}
