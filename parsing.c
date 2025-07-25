/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoherfan <yoherfan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:41:02 by yoherfan          #+#    #+#             */
/*   Updated: 2025/07/22 16:44:25 by yoherfan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_input(int argc, char **argv)
{
	int lenght;

	lenght = ft_strlen(argv[1]);
	if (argc != 2)
		return (messages_error(1), 1);
	if (argv[1][lenght - 4] != '.')
		return (messages_error(2), 2);
	if (argv[1][lenght - 3] != 'c')
		return (messages_error(2), 2);
	if (argv[1][lenght - 2] != 'u')
		return (messages_error(2), 2);
	if (argv[1][lenght - 1] != 'b')
		return (messages_error(2), 2);
	return (0);
}

int	check_field(t_input *input, int *elements, int *indxs, char *dir)
{
	if (input->file[indxs[0]][indxs[1]] == dir[0] && \
		input->file[indxs[0]][indxs[1] + 1] == ' ')
	{			
		if (dir[0] == 'F')
		{
			if (elements[4] == 0)
				elements[4] = 1;
			else
				return (1);
		}
		if (dir[0] == 'C')
		{
			if (elements[5] == 0)
				elements[5] = 1;
			else
				return (1);
		}
	}
	return (0);
}

int	set_elements(int *elements, int toggle)
{
	if (toggle == 0)
	{
		elements[0] = 0;
		elements[1] = 0;
		elements[2] = 0;
		elements[3] = 0;
		elements[4] = 0;
		elements[5] = 0;
		return (0);
	}
	else
	{
		if (elements[0] == 0)
			return (1);
		if (elements[1] == 0)
			return (1);
		if (elements[2] == 0)
			return (1);
		if (elements[3] == 0)
			return (1);
		if (elements[4] == 0)
			return (1);
		return (0);
	}
}



int parse_cub3d(int argc, char **argv, t_input *input)
{
    int fd;

    if (check_input(argc, argv) != 0)
        return (0);
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
	{
        return (messages_error(3), 0);		
	}		
	input->file_rows = ft_get_file_rows(fd);
	close(fd);
    fd = open(argv[1], O_RDONLY);
	if (input->file_rows == 0)
		return (messages_error(4), 0);
	input->file = ft_get_file(fd, input->file_rows);
	if (inspect_file(input) == 1)
		return (messages_error(5), 0);
    close(fd);
	
	return (0);
}
