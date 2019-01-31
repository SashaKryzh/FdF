/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:15:01 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/30 18:15:01 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_image(t_map *fdf)
{
	int i;
	int j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH * (fdf->bpp / 8))
		{
			fdf->img_p[i * fdf->size_line + j] = 0;
			j++;
		}
		i++;
	}
}

void	draw_map(t_map *fdf, t_cell **img)
{
	int i;
	int	j;

	clear_image(fdf);
	i = 0;
	while (i < fdf->h)
	{
		j = 0;
		while (j < fdf->w)
		{
			if (j < fdf->w - 1)
				draw_line(fdf, img[i][j], img[i][j + 1], img[i][j]);
			if (i < fdf->h - 1)
				draw_line(fdf, img[i][j], img[i + 1][j], img[i][j]);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
}
