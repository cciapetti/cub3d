/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:28:24 by cciapett          #+#    #+#             */
/*   Updated: 2025/09/12 11:54:01 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	while (i < (int)HEIGHT / 2 - (int)pc->lineheight / 2)
	{
		win->data_pixel[i * WIDTH + x] = red << 16 | green << 8 | blue;
		i++;
	}
}

void	ft_color_floor(t_pc *pc, t_win *win, int x)
{
	int	i;
	int	red;
	int	blue;
	int	green;

	i = (int)HEIGHT / 2 + (int)pc->lineheight / 2;
	red = win->input->floor.rgb_r;
	blue = win->input->floor.rgb_b;
	green = win->input->floor.rgb_g;
	while (i < HEIGHT)
	{
		win->data_pixel[i * WIDTH + x] = red << 16 | green << 8 | blue;
		i++;
	}
}

int	ft_color(t_win *win, double step, int index)
{
	int	tex_y;
	int	color;

	color = 0;
	win->index_color = index;
	tex_y = (int)win->tex_pos & (win->tex_height - 1);
	win->tex_pos += step;
	if (win->index_color == 0)
		color = win->data_pixel2[0][win->tex_width * tex_y + win->tex_x];
	else if (win->index_color == 1)
		color = win->data_pixel2[1][win->tex_width * tex_y + win->tex_x];
	else if (win->index_color == 2)
		color = win->data_pixel2[2][win->tex_width * tex_y + win->tex_x];
	else if (win->index_color == 3)
		color = win->data_pixel2[3][win->tex_width * tex_y + win->tex_x];
	return (color);
}
