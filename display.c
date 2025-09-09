/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:29:20 by cciapett          #+#    #+#             */
/*   Updated: 2025/09/09 15:11:50 by cciapett         ###   ########.fr       */
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
	(void)side;
	int	i_tex;
	int	x_tex;
    double wallX; //where exactly the wall was hit

    i = 0;
	i_tex = 0;
	x_tex = 0;
	c = WIDTH*HEIGHT/2 - (WIDTH *(int)(pc->lineHeight/2));
    if (pc->lineHeight < 0)
	{
        return ;
	}
	int drawStart = -pc->lineHeight / 2 + HEIGHT / 2;
	if(drawStart < 0) drawStart = 0;
	int drawEnd = pc->lineHeight / 2 + HEIGHT / 2;
	if(drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;
	if (side == 'v') 
		wallX = pc->posY + (pc->sideDistX - pc->deltaDistX) * pc->rayDirY;
    else
		wallX = pc->posX + (pc->sideDistY - pc->deltaDistY) * pc->rayDirX;
    wallX -= floor((wallX));
    int texX = (int)(wallX * (double)(win->tex_height));
	
    if(side == 'v' && pc->rayDirX > 0) 
		texX = win->tex_width - texX - 1;
    if(side == 'o' && pc->rayDirY < 0) 
		texX = win->tex_width - texX - 1;
    double step = 1.0 * win->tex_width / pc->lineHeight;
    double texPos = (drawStart - HEIGHT / 2 + pc->lineHeight / 2) * step;
	int	y = drawStart;
	while (y < drawEnd)
	{
		int texY = (int)texPos & (win->tex_height - 1);
		texPos += step;
		int color = win->data_pixel2[win->tex_width * texY + texX];
		win->data_pixel[(WIDTH * y) + x] = color;
		y++;
	}

	ft_color_sky(pc, win, x);
	ft_color_floor(pc, win, x);
}
