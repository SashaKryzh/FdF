/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 15:09:16 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/31 15:09:16 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	check_keys(int key, t_map *fdf)
{
	if (key == 15)
	{
		fdf->zoom = 1;
		fdf->projection = fdf_none;
		fdf->ox = 0;
		fdf->oy = 0;
		fdf->oz = 0;
	}
	else if (key == 34)
		fdf->projection = fdf_iso;
	else if (key == 27 || key == 78 || key == 24 || key == 69)
	{
		if (fdf->zoom == -1 * fdf->segm / 2 && (key == 27 || key == 78))
			return ;
		fdf->zoom += key == 27 || key == 78 ? -1 : 1;
		if (!fdf->zoom)
			fdf->zoom = key == 27 || key == 78 ? -1 : 1;
	}
}

int			key_hook(int key, void *param)
{
	t_map *fdf;

	fdf = (t_map *)param;
	if (key == 53)
	{
		exit(0);
	}
	if (key == 13 || key == 126 || key == 1 || key == 125)
		fdf->ox += key == 1 || key == 125 ? 1 : -1;
	else if (key == 0 || key == 123 || key == 2 || key == 124)
		fdf->oy += key == 0 || key == 123 ? -1 : 1;
	else if (key == 33 || key == 30)
		fdf->oz += key == 33 ? -1 : 1;
	else if (key >= 82 && key <= 92)
		fdf->depth = key - 82;
	else
		check_keys(key, fdf);
	rotation(fdf);
	return (0);
}
