/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoherfan <yoherfan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:59:21 by yoherfan          #+#    #+#             */
/*   Updated: 2025/07/22 16:17:08 by yoherfan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	messages_error(int err)
{
	if (err == 0)
		return ;
	else if (err == 1)
    	printf("Invalid number of arguments\n");
	else if (err == 2)
		printf("Invalid map extension\n");
	else if (err == 3)
		printf("Invalid input file\n");
	else if (err == 4)
		printf("Map is empty\n");
	else if (err == 5)
		printf("Invalid fields\n");
}

void	print_matrix(t_input *input)
{
	int	i;
	
	i = -1;
	while (++i < input->file_rows)
		printf("%s", input->file[i]);
}
