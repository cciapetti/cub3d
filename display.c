/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:29:20 by cciapett          #+#    #+#             */
/*   Updated: 2025/07/25 18:35:32 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void    ft_display(t_pc *pc, t_win *win, int x) //x e' la colonna dello schermo
{
    int i;
    int j;
    int c; //meta' schermo

    i = 0;
    j = 0;
    (void)x;
    c = WIDTH*HEIGHT/2;

    while (i < (int)pc->lineHeight/2)
    {
        win->data_pixel[c - (WIDTH * i) + x] = create_trgb(0, 255, 0, 0);
        i++;
    }
    i = 0;
    while (i < (int)pc->lineHeight/2)
    {
        win->data_pixel[c + (WIDTH * i) + x] = create_trgb(0, 255, 0, 0);
        i++;
    }
    while (j < WIDTH)
    {
        i = 0;
        while (i < HEIGHT/2 - (int)pc->lineHeight/2)
        {
            win->data_pixel[i *WIDTH + j] = create_trgb(100, 80, 80, 230);
            i++;
        }
        j++;
    }
    j = 0;
    while (j < WIDTH)
    {
        i =  HEIGHT/2 + (int)pc->lineHeight/2;
        while (i < HEIGHT)
        {
            win->data_pixel[i *WIDTH + j] = create_trgb(100, 80, 230, 80);
            i++;
        }
        j++;
    }
}




