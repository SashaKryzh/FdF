/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:13:14 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/22 16:13:15 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_func(char *msg)
{
	perror(msg);
	exit(1);
}

void	rotation(t_map *fdf)
{
	int		i;

	if (fdf->projection == fdf_iso)
	{
		iso(fdf);
		return ;
	}
	print_rotation_info(fdf);
	i = 0;
	while (i < fdf->h)
	{
		ft_memcpy(fdf->img[i], fdf->map[i], sizeof(t_cell) * fdf->w);
		zoom(fdf, fdf->img[i]);
		rot_x(fdf, fdf->img[i]);
		rot_y(fdf, fdf->img[i]);
		rot_z(fdf, fdf->img[i]);
		i++;
	}
	draw_map(fdf, fdf->img);
}

void	magic(t_map *fdf)
{
	int		i;

	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
		fdf->filename);
	show_usage(fdf);
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	fdf->img_p = mlx_get_data_addr(fdf->img_ptr, &fdf->bpp,
		&fdf->size_line, &fdf->endian);
	fdf->zoom = 1;
	fdf->depth = 1;
	fdf->img = (t_cell **)ft_memalloc(sizeof(t_cell *) * fdf->h);
	i = 0;
	while (i < fdf->h)
	{
		fdf->img[i] = (t_cell *)ft_memalloc(sizeof(t_cell) * fdf->w);
		i++;
	}
	fdf->segm = (IMG_WIDTH / 2) / (fdf->w > fdf->h ? fdf->w : fdf->h);
	rotation(fdf);
	mlx_hook(fdf->win_ptr, 2, 5, key_hook, (void *)fdf);
	mlx_loop(fdf->mlx_ptr);
}

int		main(int ac, char *av[])
{
	t_map	fdf;

	ft_bzero(&fdf, sizeof(t_map));
	get_map(&fdf, ac, av);
	magic(&fdf);
	return (0);
}
