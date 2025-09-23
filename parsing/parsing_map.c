/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoherfan <yoherfan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:32:40 by yoherfan          #+#    #+#             */
/*   Updated: 2025/09/23 14:39:03 by yoherfan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	closed_updown(t_input *in)
{
	int	i;
	int	j;
	int	flag;

	j = -1;
	while (++j < in->map_len)
	{
		i = 0;
		if (closed_updown_exe(in, i, j) == 0)
			return (0);
		flag = 1;
		while (in->map[i + 1] != NULL && (int)ft_strlen(in->map[i + 1]) != 0)
		{
			i++;
			if (in->map[i][j] == '\0' && flag == 0)
				return (0);
			else if (in->map[i][j] == '1' || in->map[i][j] == '\0')
				flag = 1;
			else
				flag = 0;
		}
		if (flag == 0)
			return (0);
	}
	return (1);
}

int	closed_updown_exe(t_input *in, int i, int j)
{
	if (in->map[i][j] != '1' && \
		(in->map[i][j] == '\0' && in->map[i + 1][j] == '0'))
		return (0);
	return (1);
}

int	closed_leftright(t_input *in, int i)
{
	int	j;
	int	flag;

	if (in->map[i][0] != '1' && in->map[i][0] != '\0')
		return (0);
	flag = 1;
	j = -1;
	while (++j < (int)ft_strlen(in->map[i]))
	{
		if (in->map[i][j] == '\0' && flag == 0)
			return (0);
		else if (in->map[i][j] == '1')
			flag = 1;
		else
			flag = 0;
	}
	if (flag == 0)
		return (0);
	return (1);
}

int	is_closed(t_input *in)
{
	int	i;
	int	lim[3];

	i = -1;
	lim[2] = 0;
	if (find_char(in->map[++i], "1 \0", 1) == 0)
		return (0);
	while (in->map[++i] != NULL)
	{
		if ((int)ft_strlen(in->map[i]) == 0)
		{
			lim[2] = 1;
			continue ;
		}
		if ((int)ft_strlen(in->map[i]) != 0 && lim[2] == 1)
			return (0);
		is_closed_exe(in, i);
		if (closed_leftright(in, i) == 0)
			return (0);
	}
	if (closed_updown(in) == 0)
		return (0);
	fix_angles(in);
	return (1);
}

void	is_closed_exe(t_input *in, int i)
{
	int	j;

	j = -1;
	while (in->map[i][++j] != '\0')
		if (in->map[i][j] == ' ')
			in->map[i][j] = '1';
}
