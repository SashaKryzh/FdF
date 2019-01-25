/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 19:25:03 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/22 19:25:03 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_map(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			ft_printf("%d", map->map[i][j].z);
			if (map->map[i][j].color)
				ft_printf(",0x%X", map->map[i][j].color);
			write(1, " ", 1);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
