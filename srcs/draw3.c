/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 00:50:23 by cdelicia          #+#    #+#             */
/*   Updated: 2019/09/28 23:48:57 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		scale_sprite(t_line *line, t_items *item, t_all *all, int *end)
{
	int i;

	i = 0;
	*end = 0;
	line->size_sprite = (int)(SCALE / (2 * tan(M_PI_2 / 3)) *
	all->leg->res_x / item->plr_spr_dist);
	if (line->size_sprite > all->leg->res_y)
	{
		i = (line->size_sprite - all->leg->res_y) / 2;
		*end = i;
	}
	return (i);
}

int		scale_texture(t_line *line, t_all *all, int *end)
{
	int i;
	int diff;
	int	remainder;

	i = 0;
	diff = line->size - all->leg->res_y;
	remainder = diff % 2;
	*end = 0;
	if (line->size > all->leg->res_y && remainder == 0)
	{
		i = (line->size - all->leg->res_y) / 2;
		*end = i;
	}
	else if (line->size > all->leg->res_y && remainder == 1)
	{
		i = (line->size - all->leg->res_y) / 2;
		*end = i + 1;
	}
	return (i);
}

int		num_of_spr(char **map)
{
	t_point pos;
	int		count;

	pos.y = 0;
	count = 0;
	while (map[pos.y])
	{
		pos.x = 0;
		while (map[pos.y][pos.x])
		{
			if ((ft_strchr("2", map[pos.y][pos.x])))
			{
				player_direction_check(map, pos.y, pos.x);
				count += 1;
			}
			pos.x++;
		}
		pos.y++;
	}
	return (count);
}

void	my_swap(t_items *items, int i, int j)
{
	t_items temp;

	temp = items[i];
	items[i] = items[j];
	items[j] = temp;
}

void	my_qsort(t_items *items, int left, int right)
{
	int i;
	int last;

	if (left >= right)
		return ;
	my_swap(items, left, (left + right) / 2);
	last = left;
	i = left + 1;
	while (i <= right)
	{
		if (items[i].plr_spr_dist > items[left].plr_spr_dist)
			my_swap(items, ++last, i);
		i++;
	}
	my_swap(items, left, last);
	my_qsort(items, left, last - 1);
	my_qsort(items, last + 1, right);
}
