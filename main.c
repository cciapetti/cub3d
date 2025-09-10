/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:08:40 by cciapett          #+#    #+#             */
/*   Updated: 2025/09/10 16:23:36 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rotation(int key, t_win *win)
{
	double	alpha;
	float	tempx;
	float	tempy;

	alpha = 0.0872665;
	tempx = win->pc->dirX;
	tempy = win->pc->dirY;
	if (key == XK_Left)
	{
		win->pc->dirX = (cos(alpha) * tempx) - (sin(alpha) * tempy);
		win->pc->dirY = (sin(alpha) * tempx) + (cos(alpha) * tempy);
	}
	if (key == XK_Right)
	{
		win->pc->dirX = (cos(-alpha) * tempx) - (sin(-alpha) * tempy);
		win->pc->dirY = (sin(-alpha) * tempx) + (cos(-alpha) * tempy);
	}
	win->pc->planeX = win->pc->dirY * FOV_SCALE;
	win->pc->planeY = -win->pc->dirX * FOV_SCALE;
	ft_rays(win->pc, win->input, win);
	mlx_put_image_to_window(win->mlx, win->window, win->img, 0, 0);
}

int	ft_press_key(int key, void *arg)
{
	t_win	*win;

	win = (t_win *)arg;
	if (key == XK_Escape)
	{
		mlx_destroy_image(win->mlx, win->img);
		mlx_destroy_image(win->mlx, win->img2);
		mlx_destroy_window(win->mlx, win->window);
		mlx_destroy_display(win->mlx);
		clean_parsing(win->input);
		free(win->mlx);
		exit(0);
		return (0);
	}
	if (key == 119 || key == 115 || key == 97 || key == 100)
		ft_moves(key, win);
	if (key == XK_Left || key == XK_Right)
		ft_rotation(key, win);
	return (0);
}

int	ft_clean(void *arg)
{
	t_win	*win;

	win = (t_win *)arg;
	mlx_destroy_image(win->mlx, win->img);
	mlx_destroy_image(win->mlx, win->img2);
	mlx_destroy_window(win->mlx, win->window);
	mlx_destroy_display(win->mlx);
	clean_parsing(win->input);
	free(win->mlx);
	exit(0);
	return (0);
}

static void	load_images(t_win *win)
{
	win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	win->img2 = mlx_xpm_file_to_image(win->mlx, "./textures/face2.xpm", \
		&win->tex_width, &win->tex_height);
	win->data_pixel = (int *)mlx_get_data_addr(win->img, &win->bpp, \
		&win->size_line, &win->endian);
	win->data_pixel2 = (int *)mlx_get_data_addr(win->img2, &win->bpp, \
		&win->size_line, &win->endian);
}


int	main(int argc, char **argv)
{
	t_input	input;
	t_win	win;
	t_pc	pc;

	ft_set_structure(&input);
	if (parse_cub3d(argc, argv, &input) == 0)
		clean_parsing(&input);
	else
	{
		win.pc = &pc;
		win.input = &input;
		ft_read_map(&input, &pc);
		win.mlx = mlx_init();
		win.window = mlx_new_window(win.mlx, WIDTH, HEIGHT, "giochino");
		load_images(&win);
		ft_rays(&pc, &input, &win);
		mlx_put_image_to_window(win.mlx, win.window, win.img, 0, 0);
		mlx_hook(win.window, KeyPress, KeyPressMask, ft_press_key, &win);
		mlx_hook(win.window, 17, 0, ft_clean, &win);
		mlx_loop(win.mlx);
	}
}
