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

void	print_map(t_map *fdf, t_cell **map)
{
	int i;
	int j;

	i = 0;
	while (i < fdf->h)
	{
		j = 0;
		while (j < fdf->w)
		{
			// ft_printf("%d(%d %d)", map->map[i][j].z, map->map[i][j].x, map->map[i][j].y);
			ft_printf("%3d(%2d %2d)", map[i][j].z, map[i][j].x, map[i][j].y);
			if (map[i][j].color)
				ft_printf(",0x%X", map[i][j].color);
			write(1, " ", 1);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	print_rotation_info(t_map *fdf)
{
	printf("zoom: %f\n", fdf->zoom);
	printf("depth: %f\n", fdf->depth);
	printf("ox: %f (%d)\n", fdf->ox, fdf->ox == (float)0.0);
	printf("oy: %f\n", fdf->oy);
	printf("oz: %f\n", fdf->oz);
	printf("\n");
}