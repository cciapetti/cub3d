/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoherfan <yoherfan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:27:45 by yoherfan          #+#    #+#             */
/*   Updated: 2025/09/16 11:20:54 by yoherfan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	inspect_line(t_input *input, int *elements, int *indxs)
{
	if (is_dir_line(input, elements, indxs, "NO") == 1 || \
		is_dir_line(input, elements, indxs, "SO") == 1 || \
		is_dir_line(input, elements, indxs, "WE") == 1 || \
		is_dir_line(input, elements, indxs, "EA") == 1 || \
		is_skyfloor_line(input, elements, indxs, "F") == 1 || \
		is_skyfloor_line(input, elements, indxs, "C") == 1)
		return (1);
	else
		return (0);
}

int	inspect_file(t_input *input)
{
	int	indxs[3];
	int	elements[6];

	indxs[0] = -1;
	indxs[2] = -1;
	set_elements(elements, 0);
	inspect_file_exe(input, indxs, elements);
	if (set_elements(elements, 1) == 1)
		return (1);
	if (indxs[0] == input->file_rows -1)
		return (1);
	indxs[0]++;
	while (input->file[indxs[0]][0] == '\0' && indxs[0] < input->file_rows - 1)
		indxs[0]++;
	indxs[2] = indxs[0];
	if (indxs[0] == input->file_rows)
		return (1);
	ft_get_map(input, indxs);
	return (0);
}

int	inspect_map(t_input *input)
{
	int	checks[2];
	int	indxs[2];

	checks[0] = 0;
	indxs[0] = -1;
	while (input->map[++indxs[0]] != NULL)
	{
		if (find_char(input->map[indxs[0]], "NSWE01 ", 1) == 0 && \
		input->map[indxs[0]][0] != '\0')
			return (1);
		if (find_char(input->map[indxs[0]], "NSWE", 0) == 1)
		{
			if (checks[0] == 0)
				checks[0] = 1;
			else
				return (1);
		}
	}
	if (checks[0] == 0 || is_closed(input) == 0)
		return (1);
	return (0);
}

int	inspect_textures(t_input *input)
{
	int	fd[4];
	int	toggle;

	toggle = 0;
	fd[0] = open(input->t[0].texture_path, O_RDONLY);
	fd[1] = open(input->t[1].texture_path, O_RDONLY);
	fd[2] = open(input->t[2].texture_path, O_RDONLY);
	fd[3] = open(input->t[3].texture_path, O_RDONLY);
	if (fd[0] == -1 || fd[1] == -1 || fd[2] == -1 || fd[3] == -1)
		toggle = 1;
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
	return (toggle);
}

int	inspect_bgcolors(t_input *input)
{
	char	**rgbsky;
	char	**rgbfloor;

	rgbsky = ft_split2(input->sky.line, ',');
	rgbfloor = ft_split2(input->floor.line, ',');
	if ((inspect_bgcolors_exe(rgbsky, &input->sky) == 1) || \
	inspect_bgcolors_exe(rgbfloor, &input->floor) == 1)
		return (ft_free_matrix(rgbsky, 0), \
		ft_free_matrix(rgbfloor, 0), 1);
	ft_free_matrix(rgbsky, 0);
	ft_free_matrix(rgbfloor, 0);
	return (0);
}
