/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:34:57 by cciapett          #+#    #+#             */
/*   Updated: 2025/09/10 16:02:06 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_up(float *temp_x, float *temp_y, t_win *win)
{
	int	toggle;

	toggle = 0;
	*temp_x = win->pc->posX + (win->pc->dirX * STEP);
	*temp_y = win->pc->posY - (win->pc->dirY * STEP);
	if (ft_check_map((int)*temp_x, (int)*temp_y, win->input) == 1)
		toggle = 1;
	if (toggle == 0)
	{
		win->pc->posX += (win->pc->dirX * STEP);
		win->pc->posY -= (win->pc->dirY * STEP);
	}
}

static void	ft_down(float *temp_x, float *temp_y, t_win *win)
{
	int	toggle;

	toggle = 0;
	*temp_x = win->pc->posX - (win->pc->dirX * STEP);
	*temp_y = win->pc->posY + (win->pc->dirY * STEP);
	if (ft_check_map((int)*temp_x, (int)*temp_y, win->input) == 1)
		toggle = 1;
	if (toggle == 0)
	{
		win->pc->posX -= (win->pc->dirX * STEP);
		win->pc->posY += (win->pc->dirY * STEP);
	}
}

static void	ft_left(float *temp_x, float *temp_y, t_win *win)
{
	int	toggle;

	toggle = 0;
	*temp_x = win->pc->posX - (win->pc->planeX * STEP);
	*temp_y = win->pc->posY + (win->pc->planeY * STEP);
	if (ft_check_map((int)*temp_x, (int)*temp_y, win->input) == 1)
		toggle = 1;
	if (toggle == 0)
	{
		win->pc->posX -= (win->pc->planeX * STEP);
		win->pc->posY += (win->pc->planeY * STEP);
	}
}

static void	ft_right(float *temp_x, float *temp_y, t_win *win)
{
	int	toggle;

	toggle = 0;
	*temp_x = win->pc->posX + (win->pc->planeX * STEP);
	*temp_y = win->pc->posY - (win->pc->planeY * STEP);
	if (ft_check_map((int)*temp_x, (int)*temp_y, win->input) == 1)
		toggle = 1;
	if (toggle == 0)
	{
		win->pc->posX += (win->pc->planeX * STEP);
		win->pc->posY -= (win->pc->planeY * STEP);
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
	printf("posizione: %f %f\n", win->pc->posX, win->pc->posY);
	ft_rays(win->pc, win->input, win);
	mlx_put_image_to_window(win->mlx, win->window, win->img, 0, 0);
}
