/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:29:20 by cciapett          #+#    #+#             */
/*   Updated: 2025/09/05 18:34:32 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	ft_color_sky(t_pc *pc, t_win *win, int x)
{
	int	i;
	int	red;
	int	blue;
	int	green;

	i = 0;
	red = win->input->sky.rgb_r;
	blue = win->input->sky.rgb_b;
	green = win->input->sky.rgb_g;
	while (i < (int)HEIGHT/2 - (int)pc->lineHeight/2)
    {
        win->data_pixel[i * WIDTH + x] = create_trgb(100,red, green, blue);
        i++;
    }
}

void	ft_color_floor(t_pc *pc, t_win *win, int x)
{
	int	i;
	int	red;
	int	blue;
	int	green;
	
	i =  (int)HEIGHT/2 + (int)pc->lineHeight/2;
	red = win->input->floor.rgb_r;
	blue = win->input->floor.rgb_b;
	green = win->input->floor.rgb_g;
    while (i < HEIGHT)
    {
        win->data_pixel[i * WIDTH + x] = create_trgb(100, red, green, blue);
        i++;
    }
}

void    ft_display(t_pc *pc, t_win *win, int x, char side)
{
    int i;
    int c;

    i = 0;
    c = WIDTH*HEIGHT/2;
    if (pc->lineHeight < 0)
        return ;
    while (i < (int)pc->lineHeight/2)
    {
		if (side == 'v')
		{
			if (win->pc->rayDirX > 0)
			    win->data_pixel[c - (WIDTH * i) + x] = win->data_pixel2[x];
			else
				win->data_pixel[c - (WIDTH * i) + x] = create_trgb(0, 26, 142, 49);
		}
		else
		{
			if (win->pc->rayDirY > 0)
				win->data_pixel[c - (WIDTH * i) + x] = create_trgb(0, 109, 52, 152);
			else
				win->data_pixel[c - (WIDTH * i) + x] = create_trgb(0, 233, 225, 109);
		}
        i++;
    }
    i = 0;
    while (i < (int)pc->lineHeight/2)
    {
		if (side == 'v')
		{
			if (win->pc->rayDirX > 0)
			    win->data_pixel[c + (WIDTH * i) + x] = win->data_pixel2[x];
			else
				win->data_pixel[c + (WIDTH * i) + x] = create_trgb(0, 26, 142, 49);
		}
		else
		{
			if (win->pc->rayDirY > 0)
				win->data_pixel[c + (WIDTH * i) + x] = create_trgb(0, 109, 52, 152);
			else
				win->data_pixel[c + (WIDTH * i) + x] = create_trgb(0, 233, 225, 109);
		}
        i++;
    }
	ft_color_sky(pc, win, x);
	ft_color_floor(pc, win, x);
}
