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

static void				fill_pixel(t_map *fdf, t_cell *cur, bool steep)
{
	int res;
	int	x;
	int	y;

	x = cur->x + IMG_WIDTH / 2;
	y = cur->y + IMG_WIDTH / 2;
	if (x < 0 || y < 0 || x >= IMG_WIDTH || y >= IMG_WIDTH)
		return ;
	if (steep)
		ft_swap(&x, &y);
	res = y * fdf->size_line + x * fdf->bpp / 8;
	put_bytes((char *)&fdf->img_p[res], (char *)&cur->color, fdf->endian);
}

void					draw_line(t_map *fdf, t_cell p1, t_cell p2, t_cell cur)
{
	bool	steep;
	int		dx;
	int		dy;
	int		derror;
	int		error;

	steep = false;
	check_direction(&steep, &p1, &p2);
	cur = p1;
	dx = p2.x - cur.x;
	dy = p2.y - cur.y;
	derror = ft_abs(dy) * 2;
	error = 0;
	while (cur.x <= p2.x)
	{
		get_color(&cur, &p1, &p2, dx > dy);
		fill_pixel(fdf, &cur, steep);
		error += derror;
		if (error > dx)
		{
			cur.y += p2.y > cur.y ? 1 : -1;
			error -= dx * 2;
		}
		cur.x++;
	}
}

inline static double	get_percentage(int start, int end, int cur)
{
	double place;
	double dist;

	place = cur - start;
	dist = end - start;
	return (dist == 0 ? 1.0 : (place / dist));
}

inline static int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

void					get_color(t_cell *cur, t_cell *start,
	t_cell *end, int delta)
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
}
