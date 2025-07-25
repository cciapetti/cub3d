/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:08:40 by cciapett          #+#    #+#             */
/*   Updated: 2025/07/25 18:35:38 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_exit(int key, void *arg)
{
    t_win   *win;
    win = (t_win *)arg;

    if (key == XK_Escape)
    {
        mlx_destroy_window(win->mlx, win->window);
        mlx_destroy_display(win->mlx);
        exit(0);
	    return (0);
    }
	return (0);
}

int ft_clean(void *arg)
{
    t_win	*win;

	win = (t_win *)arg;
	mlx_destroy_window(win->mlx, win->window);
	mlx_destroy_display(win->mlx);
	exit(0);
	return (0);
}

int main(int argc, char **argv)
{
    t_input		input;
    t_win       win;
    t_pc        pc;
    
    parse_cub3d(argc, argv, &input);
    ft_read_map(&input, &pc);
    win.mlx = mlx_init();
    win.window = mlx_new_window(win.mlx, WIDTH, HEIGHT, "giochino");
    win.img = mlx_new_image(win.mlx, WIDTH, HEIGHT);
    win.data_pixel = (int *)mlx_get_data_addr(win.img, &win.bpp, &win.size_line, &win.endian);
    ft_rays(&pc, &input, &win);
    mlx_put_image_to_window(win.mlx, win.window, win.img, 0, 0);
    mlx_hook(win.window, KeyPress, KeyPressMask, ft_exit, &win);
	mlx_hook(win.window, 17, 0, ft_clean, &win);
    mlx_loop(win.mlx);
    
}
