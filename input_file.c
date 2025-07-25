/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoherfan <yoherfan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:18:22 by yoherfan          #+#    #+#             */
/*   Updated: 2025/07/21 16:19:14 by yoherfan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_get_file_rows(int fd)
{
	char	*map;
	int		i;

	i = 0;
	map = get_next_line(fd);
	free(map);
	while (map)
	{
		map = get_next_line(fd);
		i++;
		free (map);
	}
	return (i);
}

char	**ft_get_file(int fd, int dim)
{
	char	*line;
	char	**map;
	int		i;

	map = (char **)ft_calloc(sizeof(char *), dim);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		map[i] = ft_strdup(line);
		free (line);
		line = get_next_line(fd);
		i++;
	}
	return (map);
}
