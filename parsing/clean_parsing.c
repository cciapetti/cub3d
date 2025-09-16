/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoherfan <yoherfan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:58:59 by yoherfan          #+#    #+#             */
/*   Updated: 2025/09/16 11:19:39 by yoherfan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clean_parsing(t_input *in)
{
	if (in->t[0].texture_path != NULL)
		free(in->t[0].texture_path);
	if ((in->t[0].direction) != NULL)
		free(in->t[0].direction);
	if (in->t[1].texture_path != NULL)
		free(in->t[1].texture_path);
	if ((in->t[1].direction) != NULL)
		free(in->t[1].direction);
	if (in->t[2].texture_path != NULL)
		free(in->t[2].texture_path);
	if ((in->t[2].direction) != NULL)
		free(in->t[2].direction);
	if (in->t[3].texture_path != NULL)
		free(in->t[3].texture_path);
	if ((in->t[3].direction) != NULL)
		free(in->t[3].direction);
	if (in->file != NULL)
		ft_free_matrix(in->file, 0);
	if (in->map != NULL)
		ft_free_matrix(in->map, 0);
	if (in->floor.line != NULL)
		free(in->floor.line);
	if (in->sky.line != NULL)
		free(in->sky.line);
}

void	ft_free_matrix(char **matrix, int i)
{
	if (!matrix)
		return ;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free (matrix);
}

void	invalid_texture_err(t_win *win)
{
	message_error(7);
	mlx_destroy_image(win->mlx, win->img);
	if (win->images[0])
		mlx_destroy_image(win->mlx, win->images[0]);
	if (win->images[1])
		mlx_destroy_image(win->mlx, win->images[1]);
	if (win->images[2])
		mlx_destroy_image(win->mlx, win->images[2]);
	if (win->images[3])
		mlx_destroy_image(win->mlx, win->images[3]);
	mlx_destroy_window(win->mlx, win->window);
	mlx_destroy_display(win->mlx);
	clean_parsing(win->input);
	free(win->mlx);
}
