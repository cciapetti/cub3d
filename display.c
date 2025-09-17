/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoherfan <yoherfan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:29:20 by cciapett          #+#    #+#             */
/*   Updated: 2025/09/17 17:28:21 by yoherfan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_display_exe(t_win *win, char side, int x, double step)
{
	int	y;

	y = win->draw_start - 1;
	while (++y < win->draw_end)
	{
		if (side == 'v')
		{
			if (win->pc->raydirx > 0)
				win->data_pixel[y * WIDTH + x] = ft_color(win, step, 3);
			else
				win->data_pixel[y * WIDTH + x] = ft_color(win, step, 2);
		}
		else
		{
			if (win->pc->raydiry > 0)
				win->data_pixel[y * WIDTH + x] = ft_color(win, step, 1);
			else
				win->data_pixel[y * WIDTH + x] = ft_color(win, step, 0);
		}
	}
	win->data_pixel[y * WIDTH + x] = ft_color(win, step, 0);
}

void	ft_display(t_pc *pc, t_win *win, int x, char side)
{
	double	wallx;
	double	step;

	win->draw_start = -pc->lineheight / 2 + HEIGHT / 2;
	if (win->draw_start < 0)
		win->draw_start = 0;
	win->draw_end = pc->lineheight / 2 + HEIGHT / 2;
	if (win->draw_end >= HEIGHT)
		win->draw_end = HEIGHT - 1;
	if (side == 'v')
		wallx = pc->posy + (pc->sidedistx - pc->deltadistx) * pc->raydiry;
	else
		wallx = pc->posx + (pc->sidedisty - pc->deltadisty) * pc->raydirx;
	wallx -= floor(wallx);
	win->tex_x = (int)(wallx * (double)win->tex_width);
	if (side == 'v' && pc->raydirx > 0)
		win->tex_x = win->tex_width - win->tex_x - 1;
	if (side == 'o' && pc->raydiry < 0)
		win->tex_x = win->tex_width - win->tex_x - 1;
	step = (win->tex_height / pc->lineheight);
	win->tex_pos = (win->draw_start - HEIGHT / 2 + pc->lineheight / 2) * step;
	ft_display_exe(win, side, x, step);
	ft_color_sky(pc, win, x);
	ft_color_floor(pc, win, x);
}
