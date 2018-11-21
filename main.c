/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 13:25:05 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/21 13:25:06 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_hook(int key, void *param)
{
	param = 0;
	if (key == 53)
		exit(0);
	return (0);
}

void	 drawline(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1)
{
    int dx, dy, p, x, y;
 
    dx=x1-x0;
    dy=y1-y0;
 
    x=x0;
    y=y0;
 
    p=2*dy-dx;
 
    while(x<x1)
    {
        if(p>=0)
        {
            mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF);
            y=y+1;
            p=p+2*dy-2*dx;
        }
        else
        {
            mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF);
            p=p+2*dy;
        }
        x=x+1;
    }
}

void	draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		p;

	if (x0 > x1)
		ft_swap(&x0, &x1);
	if (y0 > y1)
		ft_swap(&y0, &y1);
	x = x0;
	y = y0;
	dx = x1 - x0;
	dy = y1 - y0;
	p = 2 * dy - dx;
	while (x < x1)
	{
		if (p >= 0)
		{
            mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF);
            y = y + 1;
            p = p + 2 * dy - 2 * dx;
		}
		else
        {
            mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF);
            p = p + 2 * dy;
        }
        x++;
	}
}

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 750, 750, "test");
	drawline(mlx_ptr, win_ptr, 0, 0, 250, 300);
	draw_line(mlx_ptr, win_ptr, 50, 0, 0, 300);
	mlx_key_hook(win_ptr, key_hook, (void *)0);
	mlx_loop(mlx_ptr);
	return (0);
}
