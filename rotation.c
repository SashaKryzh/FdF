/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:03:50 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/25 14:03:51 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom(t_map *fdf, t_cell *img, int row, double zoom)
{
	float	mult;
	int		i;

	mult = 35 * zoom;
	i = 0;
	while (i < fdf->w)
	{
		img[i].z = img[i].z * fdf->depth;
		img[i].y = img[i].y * mult - fdf->h / 2 * mult;
		img[i].x = img[i].x * mult - fdf->w / 2 * mult;
		i++;
	}
}

void	rot_x(t_map *fdf, t_cell *img, double angl)
{
	int		i;

	i = 0;
	while (i < fdf->w)
	{
		img[i].y = img[i].y * cos(angl) + img[i].z * sin(angl);
		img[i].z = -1 * img[i].y * sin(angl) + img[i].z * cos(angl);
		i++;
	}
}

void	rot_y(t_map *fdf, t_cell *img, double angl)
{
	int		i;

	i = 0;
	while (i < fdf->w)
	{
		img[i].x = img[i].x * cos(angl) + img[i].z * sin(angl);
		img[i].z = -1 * img[i].x * sin(angl) + img[i].z * cos(angl);
		i++;
	}
}

void	rot_z(t_map *fdf, t_cell *img, double angl)
{
	int		i;
	int		j;

	i = 0;
	while (i < fdf->w)
	{
		img[i].x = img[i].x * cos(angl) - img[i].y * sin(angl);
		img[i].y = img[i].x * sin(angl) + img[i].y * cos(angl);
		i++;
	}
}

void	iso(t_map *fdf)
{
	t_cell	**img;
	int		i;
	int		j;
	int		prev_x;
	int		prev_y;

	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	img = (t_cell **)ft_memalloc(sizeof(t_cell *) * fdf->h);
	i = 0;
	while (i < fdf->h)
	{
		img[i] = (t_cell *)ft_memalloc(sizeof(t_cell) * fdf->w);
		ft_memcpy(img[i], fdf->map[i], sizeof(t_cell) * fdf->w);
		zoom(fdf, img[i], i, fdf->zoom);
		j = 0;
		while (j < fdf->w)
		{
			prev_x = img[i][j].x;
			prev_y = img[i][j].y;
			img[i][j].x = (prev_x - prev_y) * cos(0.523599);
			img[i][j].y = -1 * img[i][j].z + (prev_x + prev_y) * sin(0.523599);
			j++;
		}
		i++;
	}
	draw_grid(fdf, img);
}
