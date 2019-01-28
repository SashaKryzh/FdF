/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 10:07:20 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/28 10:07:20 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_direction(bool *steep, t_cell *p1, t_cell *p2)
{
	if (ft_abs(p1->x - p2->x) < ft_abs(p1->y - p2->y))
	{
		ft_swap(&p1->x, &p1->y);
		ft_swap(&p2->x, &p2->y);
		*steep = true;
	}
	if (p1->x > p2->x)
	{
		ft_swap(&p1->x, &p2->x);
		ft_swap(&p1->y, &p2->y);
	}
}

void	draw_line(t_map *fdf, t_cell p1, t_cell p2)
{
	bool	steep;
	int		dx;
	int		dy;
	int		derror;
	int		error;

	steep = false;
	check_direction(&steep, &p1, &p2);
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	derror = ft_abs(dy) * 2;
	error = 0;
	while (p1.x < p2.x)
	{
		if (!steep)
			mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, p1.x + WIN_WIDTH / 2, p1.y + WIN_HEIGHT / 2, 0xFFFFFF);
		else
			mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, p1.y + WIN_WIDTH / 2, p1.x + WIN_HEIGHT / 2, 0xFFFFFF);
		error += derror;
		if (error > dx)
		{
			p1.y += p2.y > p1.y ? 1 : -1;
			error -= dx * 2; 
		}
		p1.x++;
	}
}
