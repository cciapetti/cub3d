/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:29:20 by cciapett          #+#    #+#             */
/*   Updated: 2025/09/11 11:45:34 by cciapett         ###   ########.fr       */
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
	while (i < (int)HEIGHT / 2 - (int)pc->lineHeight / 2)
	{
		win->data_pixel[i * WIDTH + x] = create_trgb(100, red, green, blue);
		i++;
	}
}

void	ft_color_floor(t_pc *pc, t_win *win, int x)
{
	int	i;
	int	red;
	int	blue;
	int	green;

	i = (int)HEIGHT / 2 + (int)pc->lineHeight / 2;
	red = win->input->floor.rgb_r;
	blue = win->input->floor.rgb_b;
	green = win->input->floor.rgb_g;
	while (i < HEIGHT)
	{
		win->data_pixel[i * WIDTH + x] = create_trgb(100, red, green, blue);
		i++;
	}
}

int	ft_color(double *tex_pos, int tex_x, t_win *win, double step)
{
	int	tex_y;
	int	color;

	color = 0;
	tex_y = (int)*tex_pos & (win->tex_height - 1);
	*tex_pos += step;
	if (win->index_color == 0)
		color = win->data_pixel2[0][win->tex_width * tex_y + tex_x];
	else if (win->index_color == 1)
		color = win->data_pixel2[1][win->tex_width * tex_y + tex_x];
	else if (win->index_color == 2)
		color = win->data_pixel2[2][win->tex_width * tex_y + tex_x];
	else if (win->index_color == 3)
		color = win->data_pixel2[3][win->tex_width * tex_y + tex_x];
	return (color);
}


void	ft_display(t_pc *pc, t_win *win, int x, char side)
{
	int		draw_start;
	double	wallx;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		y;

	if (pc->lineHeight <= 0)
		return ;
	draw_start = -pc->lineHeight / 2 + HEIGHT / 2;
	y = draw_start - 1;
	if (draw_start < 0)
		draw_start = 0;
	if (side == 'v')
		wallx = pc->posY + (pc->sideDistX - pc->deltaDistX) * pc->rayDirY;
	else
		wallx = pc->posX + (pc->sideDistY - pc->deltaDistY) * pc->rayDirX;
	wallx -= floor(wallx);
	tex_x = (int)(wallx * (double)win->tex_width);
	if (side == 'v' && pc->rayDirX < 0)
		tex_x = win->tex_width - tex_x - 1;
	if (side == 'o' && pc->rayDirY > 0)
		tex_x = win->tex_width - tex_x - 1;
	step = (win->tex_height / pc->lineHeight) * pc->tex_scale;
	tex_pos = (draw_start - HEIGHT / 2 + pc->lineHeight / 2) * step;
	while (++y < pc->lineHeight / 2 + HEIGHT / 2)
	{
		if (side == 'v')
		{
			if (win->pc->rayDirX > 0)
			{
				win->data_pixel[y * WIDTH + x] = ft_color(&tex_pos, tex_x, win, step);
				win->index_color = 0;
			}
			else
			{
				win->data_pixel[y * WIDTH + x] = ft_color(&tex_pos, tex_x, win, step);
				win->index_color = 1;
			}
		}
		else
		{
			if (win->pc->rayDirX > 0)
			{
				win->data_pixel[y * WIDTH + x] = ft_color(&tex_pos, tex_x, win, step);
				win->index_color = 2;
			}
			else
			{
				win->data_pixel[y * WIDTH + x] = ft_color(&tex_pos, tex_x, win, step);
				win->index_color = 3;
			}
		}
	}
	win->data_pixel[y * WIDTH + x] = ft_color(&tex_pos, tex_x, win, step);
	ft_color_sky(pc, win, x);
	ft_color_floor(pc, win, x);
}
