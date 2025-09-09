/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:29:20 by cciapett          #+#    #+#             */
/*   Updated: 2025/09/09 17:41:02 by cciapett         ###   ########.fr       */
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

	tex_y = (int)*tex_pos & (win->tex_height - 1);
	*tex_pos += step;
	color = win->data_pixel2[win->tex_width * tex_y + tex_x];
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

	y = -pc->lineHeight / 2 + HEIGHT / 2 - 1;
	if (pc->lineHeight < 0)
		return ;
	draw_start = -pc->lineHeight / 2 + HEIGHT / 2;
	if (side == 'v')
		wallx = pc->posY + (pc->sideDistX - pc->deltaDistX) * pc->rayDirY;
	else
		wallx = pc->posX + (pc->sideDistY - pc->deltaDistY) * pc->rayDirX;
	wallx -= floor((wallx));
	tex_x = (int)(wallx * (double)(win->tex_height));
	if (side == 'v' && pc->rayDirX > 0)
		tex_x = win->tex_width - tex_x - 1;
	if (side == 'o' && pc->rayDirY < 0)
		tex_x = win->tex_width - tex_x - 1;
	step = 1.0 * win->tex_width / pc->lineHeight;
	tex_pos = (draw_start - HEIGHT / 2 + pc->lineHeight / 2) * step;
	while (++y < pc->lineHeight / 2 + HEIGHT / 2)
		win->data_pixel[WIDTH * y + x] = ft_color(&tex_pos, tex_x, win, step);
	ft_color_sky(pc, win, x);
	ft_color_floor(pc, win, x);
}
