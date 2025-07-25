/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:09:05 by cciapett          #+#    #+#             */
/*   Updated: 2025/07/25 18:11:05 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minilibx-linux_cub3d/mlx.h"
#include "minilibx-linux_cub3d/mlx_int.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include <stdbool.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"

#define WIDTH 500
#define HEIGHT 400
#define FOV_SCALE 0.577

typedef struct s_win
{
    void    *mlx;
    void    *window;
    void    *img;
    int     *data_pixel;
    int     bpp;
    int     size_line;
    int     endian;
}   t_win;

typedef struct s_texture
{
    char    *direction;
    char    *texture_path;
}   t_texture;

typedef struct s_skyfloor
{
    char    id;
    int		rgb_r;
    int		rgb_g;
    int		rgb_b;
}   t_skyfloor;

typedef struct s_input
{
    char		**map;
	char		**file;
	t_texture	t[4];
	t_skyfloor	sky;
	t_skyfloor	floor;
	int			file_rows;
}   t_input;

typedef struct s_pc
{
    float   posX;
    float   posY;
    int     mapX;
    int     mapY;
    float   dirX;
    float   dirY;
    float   planeX;
    float   planeY;
    float   cameraX;
    float   rayDirX;
    float   rayDirY;
    float   deltaDistX;
    float   deltaDistY;
    float   sideDistX;
    float   sideDistY;
    int     hit;
    int     stepX;
    int     stepY;
    float   lineHeight;
}   t_pc;


//MANAGER.C

//CHECK_DIRECTION.C
int     check_direction(t_input *input, int *elements, int *indxs, char *dir);
int     check_north(int *elements, char *dir);
int     check_south(int *elements, char *dir);
int     check_west(int *elements, char *dir);
int     check_east(int *elements, char *dir);
//INPUT_FILE.C
int		ft_get_file_rows(int fd);
char	**ft_get_file(int fd, int dim);
//INSPECT.C
int     inspect_file(t_input *input);
//MESSAGES.C
void	messages_error(int err);
void	print_matrix(t_input *input);
//PARSING.C
int		check_input(int argc, char **argv);
int	    check_field(t_input *input, int *elements, int *indxs, char *dir);
int     set_elements(int *elements, int toggle);
int		parse_cub3d(int argc, char **argv, t_input *input);

//READ_MAP.C
void    ft_read_map(t_input *input, t_pc *pc);
//RAYS.C
void    ft_rays(t_pc *pc, t_input *input, t_win *win);
//DISPLAY.C
void    ft_display(t_pc *pc, t_win *win, int x);

