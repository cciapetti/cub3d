/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoherfan <yoherfan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:08:40 by cciapett          #+#    #+#             */
/*   Updated: 2025/09/17 16:07:33 by yoherfan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rotation(int key, t_win *win)
{
	double	alpha;
	float	tempx;
	float	tempy;

	alpha = 0.0372665;
	tempx = win->pc->dirx;
	tempy = win->pc->diry;
	if (key == XK_Left)
	{
		win->pc->dirx = (cos(alpha) * tempx) - (sin(alpha) * tempy);
		win->pc->diry = (sin(alpha) * tempx) + (cos(alpha) * tempy);
	}
	if (key == XK_Right)
	{
		win->pc->dirx = (cos(-alpha) * tempx) - (sin(-alpha) * tempy);
		win->pc->diry = (sin(-alpha) * tempx) + (cos(-alpha) * tempy);
	}
	win->pc->planex = win->pc->diry * FOV_SCALE;
	win->pc->planey = -win->pc->dirx * FOV_SCALE;
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
		mlx_destroy_image(win->mlx, win->images[0]);
		mlx_destroy_image(win->mlx, win->images[1]);
		mlx_destroy_image(win->mlx, win->images[2]);
		mlx_destroy_image(win->mlx, win->images[3]);
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
	mlx_destroy_image(win->mlx, win->images[0]);
	mlx_destroy_image(win->mlx, win->images[1]);
	mlx_destroy_image(win->mlx, win->images[2]);
	mlx_destroy_image(win->mlx, win->images[3]);
	mlx_destroy_window(win->mlx, win->window);
	mlx_destroy_display(win->mlx);
	clean_parsing(win->input);
	free(win->mlx);
	exit(0);
	return (0);
}

int	load_images(t_win *win)
{
	win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	win->images[0] = mlx_xpm_file_to_image(win->mlx, \
		win->input->t[0].texture_path, &win->tex_width, &win->tex_height);
	win->images[1] = mlx_xpm_file_to_image(win->mlx, \
		win->input->t[1].texture_path, &win->tex_width, &win->tex_height);
	win->images[2] = mlx_xpm_file_to_image(win->mlx, \
		win->input->t[2].texture_path, &win->tex_width, &win->tex_height);
	win->images[3] = mlx_xpm_file_to_image(win->mlx, \
		win->input->t[3].texture_path, &win->tex_width, &win->tex_height);
	win->data_pixel = (int *)mlx_get_data_addr(win->img, &win->bpp, \
		&win->size_line, &win->endian);
	if (!win->images[0] || !win->images[1] || !win->images[2] \
		|| !win->images[3])
		return (0);
	win->data_pixel2[0] = (int *)mlx_get_data_addr(win->images[0], &win->bpp, \
		&win->size_line, &win->endian);
	win->data_pixel2[1] = (int *)mlx_get_data_addr(win->images[1], &win->bpp, \
		&win->size_line, &win->endian);
	win->data_pixel2[2] = (int *)mlx_get_data_addr(win->images[2], &win->bpp, \
		&win->size_line, &win->endian);
	win->data_pixel2[3] = (int *)mlx_get_data_addr(win->images[3], &win->bpp, \
		&win->size_line, &win->endian);
	return (1);
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
		win.window = mlx_new_window(win.mlx, WIDTH, HEIGHT, "cub3d");
		if (load_images(&win) == 0)
			invalid_texture_err(&win);
		else
		{
			ft_rays(&pc, &input, &win);
			mlx_put_image_to_window(win.mlx, win.window, win.img, 0, 0);
			mlx_hook(win.window, KeyPress, KeyPressMask, ft_press_key, &win);
			mlx_hook(win.window, 17, 0, ft_clean, &win);
			mlx_loop(win.mlx);
		}
	}
}
