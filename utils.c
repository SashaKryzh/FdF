/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 19:22:04 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/22 19:22:04 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		add_line(t_read **read, t_cell *line)
{
	t_read	*new;
	t_read	*tmp;

	new = (t_read *)ft_memalloc(sizeof(t_read));
	new->l = line;
	if (!*read)
		*read = new;
	else
	{
		tmp = *read;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int			line_width(char **token)
{
	int i;

	i = 0;
	if (!token)
		exit_func("Line error");
	while (token[i])
		i++;
	return (i);
}

int			ft_atoi_hex(char *s)
{
	int r;
	int i;

	r = 0;
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	while (s[i])
	{
		if (ft_isdigit(s[i]))
			r = r * 16 + s[i] - '0';
		else if (s[i] >= 'A' && s[i] <= 'F')
			r = r * 16 + s[i] - 'A' + 10;
		else if (s[i] >= 'a' && s[i] <= 'f')
			r = r * 16 + s[i] - 'a' + 10;
		else
			break ;
		i++;
	}
	return (r);
}

void		put_bytes(char *s, char *v, int endian)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (endian)
			s[i] = v[3 - i];
		else
			s[i] = v[i];
		i++;
	}
}

void		check_direction(bool *steep, t_cell *p1, t_cell *p2)
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
