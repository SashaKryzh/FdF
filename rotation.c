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

void	zoom(t_map *fdf, t_cell *img)
{
	int		segm;
	int		i;

	segm = fdf->segm;
	if (fdf->zoom > 0)
		segm = segm * fdf->zoom;
	else
		segm = segm / (fdf->zoom * -1);
	i = 0;
	while (i < fdf->w)
	{
		img[i].x = img[i].x * segm - (fdf->w - 1) * segm / 2;
		img[i].y = img[i].y * segm - (fdf->h - 1) * segm / 2;
		if (fdf->z_max)
			img[i].z = img[i].z * segm *
				((double)fdf->depth / (double)fdf->z_max);
		i++;
	}
}

void	rot_x(t_map *fdf, t_cell *img)
{
	double	angl;
	int		i;
	int		tmp;

	i = 0;
	angl = (double)fdf->ox / (double)10;
	while (i < fdf->w)
	{
		tmp = img[i].y;
		img[i].y = img[i].y * cos(angl) + img[i].z * sin(angl);
		img[i].z = -1 * tmp * sin(angl) + img[i].z * cos(angl);
		i++;
	}
}

void	rot_y(t_map *fdf, t_cell *img)
{
	double	angl;
	int		i;
	int		tmp;

	i = 0;
	angl = (double)fdf->oy / (double)10;
	while (i < fdf->w)
	{
		tmp = img[i].x;
		img[i].x = img[i].x * cos(angl) + img[i].z * sin(angl);
		img[i].z = -1 * tmp * sin(angl) + img[i].z * cos(angl);
		i++;
	}
}

void	rot_z(t_map *fdf, t_cell *img)
{
	double	angl;
	int		i;
	int		tmp;

	i = 0;
	angl = (double)fdf->oz / (double)10;
	while (i < fdf->w)
	{
		tmp = img[i].x;
		img[i].x = img[i].x * cos(angl) - img[i].y * sin(angl);
		img[i].y = tmp * sin(angl) + img[i].y * cos(angl);
		i++;
	}
}

void	iso(t_map *fdf)
{
	int		i;
	int		j;
	int		prev_x;
	int		prev_y;

	i = 0;
	while (i < fdf->h)
	{
		ft_memcpy(fdf->img[i], fdf->map[i], sizeof(t_cell) * fdf->w);
		zoom(fdf, fdf->img[i]);
		j = 0;
		while (j < fdf->w)
		{
			prev_x = fdf->img[i][j].x;
			prev_y = fdf->img[i][j].y;
			fdf->img[i][j].x = (prev_x - prev_y) * cos(0.523599);
			fdf->img[i][j].y = -1 * fdf->img[i][j].z +
				(prev_x + prev_y) * sin(0.523599);
			j++;
		}
		i++;
	}
	draw_map(fdf, fdf->img);
}
