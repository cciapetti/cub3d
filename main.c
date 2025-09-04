/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoherfan <yoherfan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:08:40 by cciapett          #+#    #+#             */
/*   Updated: 2025/09/04 15:53:27 by yoherfan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rotation(int key, t_win *win)
{
	double alpha = 0.0872665;
	float	tempx;
	float	tempy;

	tempx = win->pc->dirX;
	tempy = win->pc->dirY;
	if (key == XK_Left)
	{
		win->pc->dirX = (cos(alpha)*tempx) - (sin(alpha)*tempy);
		win->pc->dirY = (sin(alpha)*tempx) + (cos(alpha)*tempy);
	}
	if (key == XK_Right)
	{
		win->pc->dirX = (cos(-alpha)*tempx) - (sin(-alpha)*tempy);
		win->pc->dirY = (sin(-alpha)*tempx) + (cos(-alpha)*tempy);
	}
    win->pc->planeX = win->pc->dirY * FOV_SCALE;
    win->pc->planeY = -win->pc->dirX * FOV_SCALE;
	ft_rays(win->pc, win->input, win);
    mlx_put_image_to_window(win->mlx, win->window, win->img, 0, 0);
}

void    ft_moves(int key, t_win *win)
{
    float   temp_x;
    float   temp_y;
    int     toggle;

    temp_x = 0;
    temp_y = 0;
    toggle = 0;

    if (key == 119)
    {
        temp_x = win->pc->posX + (win->pc->dirX * 0.5);
        temp_y = win->pc->posY - (win->pc->dirY * 0.5);
        if (ft_check_map((int)temp_x, (int)temp_y, win->input, win->pc) == 1)
        {
            // printf("Posizione %f %f\n", win->pc->posX, win->pc->posY);
            toggle = 1;
        }
        if (toggle == 0)
        {
            win->pc->posX += (win->pc->dirX * 0.5);
            win->pc->posY -= (win->pc->dirY * 0.5);
        }
    }
    else if (key == 115)
    {
        temp_x = win->pc->posX - (win->pc->dirX * 0.5);
        temp_y= win->pc->posY + (win->pc->dirY * 0.5);
        if (ft_check_map((int)temp_x, (int)temp_y, win->input, win->pc) == 1)
        {
            printf("Posizione %f %f\n", win->pc->posX, win->pc->posY);
            toggle = 1;
        }
        if (toggle == 0)
        {
            win->pc->posX -= (win->pc->dirX * 0.5);
            win->pc->posY += (win->pc->dirY * 0.5);
        }
    }
    else if (key == 97)
    {
        temp_x = win->pc->posX - (win->pc->planeX * 0.5);
        temp_y = win->pc->posY + (win->pc->planeY * 0.5);
        if (ft_check_map((int)temp_x, (int)temp_y, win->input, win->pc) == 1 /* || temp_x == 1.0 */)
        {
            // printf("Posizione %f %f\n", win->pc->posX, win->pc->posY);
            toggle = 1;
        }
        if (toggle == 0)
        {
            win->pc->posX -= (win->pc->planeX * 0.5);
            win->pc->posY += (win->pc->planeY * 0.5);
        }
    }
    else if (key == 100)
    {
        temp_x = win->pc->posX + (win->pc->planeX * 0.5);
        temp_y = win->pc->posY - (win->pc->planeY * 0.5);
        if (ft_check_map((int)temp_x, (int)temp_y, win->input, win->pc) == 1)
        {
            // printf("Posizione %f %f\n", win->pc->posX, win->pc->posY);
            toggle = 1;
        }
        if (toggle == 0)
        {
            win->pc->posX += (win->pc->planeX * 0.5);
            win->pc->posY -= (win->pc->planeY * 0.5);
        }
    }
    ft_rays(win->pc, win->input, win);
    mlx_put_image_to_window(win->mlx, win->window, win->img, 0, 0);
}

int ft_press_key(int key, void *arg)
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
    // printf("key: %d\n", key);
    if (key == 119 || key == 115 || key == 97 || key == 100)
    {
        // printf("Movimento\n");
        ft_moves(key, win);
    }
    if (key == XK_Left || key == XK_Right)
	{
        ft_rotation(key, win);
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
    	win.img = mlx_new_image(win.mlx, WIDTH, HEIGHT);
    	win.data_pixel = (int *)mlx_get_data_addr(win.img, &win.bpp, &win.size_line, &win.endian);
    	ft_rays(&pc, &input, &win);
    	mlx_put_image_to_window(win.mlx, win.window, win.img, 0, 0);
    	mlx_hook(win.window, KeyPress, KeyPressMask, ft_press_key, &win);
		mlx_hook(win.window, 17, 0, ft_clean, &win);
    	mlx_loop(win.mlx);
	}
}
