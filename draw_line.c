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
		ft_swap(&p1->color, &p2->color);
	}
}

void	draw_line(t_map *fdf, t_cell p1, t_cell p2)
{
	bool	steep;
	int		dx;
	int		dy;
	int		derror;
	int		error;
	t_cell	cur;

	steep = false;
	check_direction(&steep, &p1, &p2);
	cur = p1;
	dx = p2.x - cur.x;
	dy = p2.y - cur.y;
	derror = ft_abs(dy) * 2;
	error = 0;
	while (cur.x < p2.x)
	{
		get_color(&cur, &p1, &p2, dx > dy);
		if (!steep)
			mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, cur.x + WIN_WIDTH / 2, cur.y + WIN_HEIGHT / 2, cur.color);
		else
			mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, cur.y + WIN_WIDTH / 2, cur.x + WIN_HEIGHT / 2, cur.color);
		error += derror;
		if (error > dx)
		{
			cur.y += p2.y > cur.y ? 1 : -1;
			error -= dx * 2; 
		}
		cur.x++;
	}
}

double	get_percentage(int start, int end, int cur)
{
	double place;
	double dist;

	place = cur - start;
	dist = end - start;
	return (dist == 0 ? 1.0 : (place / dist));
}

int			get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}
void		get_color(t_cell *cur, t_cell *start, t_cell *end, int delta)
{
	double	per;
	int		r;
	int		g;
	int		b;

	if (cur->color == end->color)
		return ;
	if (delta)
		per = get_percentage(start->x, end->x, cur->x);
	else
		per = get_percentage(start->y, end->y, cur->y);
	r = get_light((start->color >> 16) & 0xFF, (end->color >> 16) & 0xFF, per);
    g = get_light((start->color >> 8) & 0xFF, (end->color >> 8) & 0xFF, per);
    b = get_light(start->color & 0xFF, end->color & 0xFF, per);
	cur->color = (r << 16) | (g << 8) | b;
	if (!cur->color)
	{
		printf("0x%X\n", cur->color);
		printf("0x%X 0x%X\n", start->color, end->color);
	}
}
