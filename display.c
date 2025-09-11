/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:29:20 by cciapett          #+#    #+#             */
/*   Updated: 2025/09/11 14:39:39 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_display_exe(t_win *win, char side, int x, double step)
{
	int	y;

	y = win->draw_start - 1;
	while (++y < win->pc->lineHeight / 2 + HEIGHT / 2)
	{
		if (side == 'v')
		{
			if (win->pc->rayDirX > 0)
				win->data_pixel[y * WIDTH + x] = ft_color(win, step, 0);
			else
				win->data_pixel[y * WIDTH + x] = ft_color(win, step, 1);
		}
		else
		{
			if (win->pc->rayDirY > 0)
				win->data_pixel[y * WIDTH + x] = ft_color(win, step, 2);
			else
				win->data_pixel[y * WIDTH + x] = ft_color(win, step, 3);
		}
	}
	win->data_pixel[y * WIDTH + x] = ft_color(win, step, 0);
}

void	ft_display(t_pc *pc, t_win *win, int x, char side)
{
	double	wallx;
	double	step;

	if (pc->lineHeight <= 0)
		return ;
	win->draw_start = -pc->lineHeight / 2 + HEIGHT / 2;
	if (win->draw_start < 0)
		win->draw_start = 0;
	if (side == 'v')
		wallx = pc->posY + (pc->sideDistX - pc->deltaDistX) * pc->rayDirY;
	else
		wallx = pc->posX + (pc->sideDistY - pc->deltaDistY) * pc->rayDirX;
	wallx -= floor(wallx);
	win->tex_x = (int)(wallx * (double)win->tex_width);
	if (side == 'v' && pc->rayDirX < 0)
		win->tex_x = win->tex_width - win->tex_x - 1;
	if (side == 'o' && pc->rayDirY > 0)
		win->tex_x = win->tex_width - win->tex_x - 1;
	step = (win->tex_height / pc->lineHeight) * pc->tex_scale;
	win->tex_pos = (win->draw_start - HEIGHT / 2 + pc->lineHeight / 2) * step;
	ft_display_exe(win, side, x, step);
	ft_color_sky(pc, win, x);
	ft_color_floor(pc, win, x);
}
