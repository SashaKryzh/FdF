/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 13:25:36 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/21 13:25:37 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include "mlx.h"

# include "libft.h"

# define TRUE 1
# define FALSE 0

typedef struct		s_cell
{
	int				x;
	int				y;
	int				z;
}					t_cell;

typedef struct		s_map
{
	t_cell			**map;
	int				w;
	int				h;
}					t_map;

typedef struct		s_read
{
	t_cell			*l;
	struct s_read	*next;
}					t_read;

/*
** Tests
*/

#endif
