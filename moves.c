/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:34:57 by cciapett          #+#    #+#             */
/*   Updated: 2025/09/12 11:52:19 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_up(float *temp_x, float *temp_y, t_win *win)
{
	int	toggle;

	toggle = 0;
	*temp_x = win->pc->posx + (win->pc->dirx * STEP);
	*temp_y = win->pc->posy - (win->pc->diry * STEP);
	if (ft_check_map((int)*temp_x, (int)*temp_y, win->input) == 1)
		toggle = 1;
	if (toggle == 0)
	{
		win->pc->posx += (win->pc->dirx * STEP);
		win->pc->posy -= (win->pc->diry * STEP);
	}
}

static void	ft_down(float *temp_x, float *temp_y, t_win *win)
{
	int	toggle;

	toggle = 0;
	*temp_x = win->pc->posx - (win->pc->dirx * STEP);
	*temp_y = win->pc->posy + (win->pc->diry * STEP);
	if (ft_check_map((int)*temp_x, (int)*temp_y, win->input) == 1)
		toggle = 1;
	if (toggle == 0)
	{
		win->pc->posx -= (win->pc->dirx * STEP);
		win->pc->posy += (win->pc->diry * STEP);
	}
}

static void	ft_left(float *temp_x, float *temp_y, t_win *win)
{
	int	toggle;

	toggle = 0;
	*temp_x = win->pc->posx - (win->pc->planex * STEP);
	*temp_y = win->pc->posy + (win->pc->planey * STEP);
	if (ft_check_map((int)*temp_x, (int)*temp_y, win->input) == 1)
		toggle = 1;
	if (toggle == 0)
	{
		win->pc->posx -= (win->pc->planex * STEP);
		win->pc->posy += (win->pc->planey * STEP);
	}
}

static void	ft_right(float *temp_x, float *temp_y, t_win *win)
{
	int	toggle;

	toggle = 0;
	*temp_x = win->pc->posx + (win->pc->planex * STEP);
	*temp_y = win->pc->posy - (win->pc->planey * STEP);
	if (ft_check_map((int)*temp_x, (int)*temp_y, win->input) == 1)
		toggle = 1;
	if (toggle == 0)
	{
		win->pc->posx += (win->pc->planex * STEP);
		win->pc->posy -= (win->pc->planey * STEP);
	}
}

void	ft_moves(int key, t_win *win)
{
	float	temp_x;
	float	temp_y;
	int		toggle;

	temp_x = 0;
	temp_y = 0;
	toggle = 0;
	if (key == 119)
		ft_up(&temp_x, &temp_y, win);
	else if (key == 115)
		ft_down(&temp_x, &temp_y, win);
	else if (key == 97)
		ft_left(&temp_x, &temp_y, win);
	else if (key == 100)
		ft_right(&temp_x, &temp_y, win);
	ft_rays(win->pc, win->input, win);
	mlx_put_image_to_window(win->mlx, win->window, win->img, 0, 0);
}
