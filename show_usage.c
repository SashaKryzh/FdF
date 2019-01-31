/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_usage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 13:03:18 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/31 13:03:18 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define MLX_WIN fdf->mlx_ptr, fdf->win_ptr

static void		line(t_map *fdf)
{
	int i;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		mlx_pixel_put(MLX_WIN, IMG_WIDTH, i, 0xFF0000);
		mlx_pixel_put(MLX_WIN, IMG_WIDTH + 1, i, 0xFF0000);
		i++;
	}
}

void	show_usage(t_map *fdf)
{
	line(fdf);
	mlx_string_put(MLX_WIN, IMG_WIDTH + 15, 25, 0xFFFFFF, ESC);
	mlx_string_put(MLX_WIN, IMG_WIDTH + 15, 75, 0xFFFFFF, ROT_OX);
	mlx_string_put(MLX_WIN, IMG_WIDTH + 15, 100, 0xFFFFFF, ROT_OY);
	mlx_string_put(MLX_WIN, IMG_WIDTH + 15, 125, 0xFFFFFF, ROT_OZ);
	mlx_string_put(MLX_WIN, IMG_WIDTH + 15, 175, 0xFFFFFF, ZOOM);
	mlx_string_put(MLX_WIN, IMG_WIDTH + 15, 200, 0xFFFFFF, DEPTH);
	mlx_string_put(MLX_WIN, IMG_WIDTH + 15, 250, 0xFFFFFF, ISO);
	mlx_string_put(MLX_WIN, IMG_WIDTH + 15, 275, 0xFFFFFF, RESET);
}
