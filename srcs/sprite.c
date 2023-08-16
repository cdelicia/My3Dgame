/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 00:45:30 by cdelicia          #+#    #+#             */
/*   Updated: 2019/09/28 14:45:51 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	trigonometric_calc(t_items *all, t_plr *plr)
{
	all->x_offset = all->x_center - plr->x;
	all->y_offset = all->y_center - plr->y;
	all->plr_spr_dist = hypot(all->x_offset, all->y_offset);
	if (all->y_offset <= 0)
		all->cub_direct_angle = acos(all->x_offset / all->plr_spr_dist);
	else
		all->cub_direct_angle = 2 * M_PI -
		acos(all->x_offset / all->plr_spr_dist);
	if (all->cub_direct_angle > M_PI)
		all->cub_direct_angle -= M_PI * 2;
	else if (all->cub_direct_angle < -M_PI)
		all->cub_direct_angle += M_PI * 2;
}

int		calc_all_sprite_values(char **map, t_items *items, t_plr *plr)
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
				items->x_center = pos.x * SCALE + SCALE / 2;
				items->y_center = pos.y * SCALE + SCALE / 2;
				trigonometric_calc(items, plr);
				items++;
				count++;
			}
			pos.x++;
		}
		pos.y++;
	}
	return (count);
}

void	draw_one_sprite(t_items *item, t_line *line, t_all *all)
{
	int		i;
	int		end;
	char	*dst;
	char	*from;

	item->beta = item->cub_direct_angle - all->plr->dir;
	item->spr_offset = SCALE / 2 - ((item->plr_spr_dist * cos(item->beta) *
	tan(line->angle)) - (item->plr_spr_dist * sin(item->beta)));
	if (item->spr_offset < 0 || item->spr_offset > SCALE)
		return ;
	i = scale_sprite(line, item, all, &end);
	while (i < line->size_sprite - end)
	{
		from = all->spr.addr + (int)(i * all->spr.height /
		line->size_sprite) * all->spr.line_l;
		from += (int)(item->spr_offset * all->spr.width / SCALE) * BYPP;
		dst = all->win->addr;
		dst += line->number * BYPP;
		dst += (i + all->leg->res_y / 2 - line->size_sprite / 2) *
		all->win->line_l;
		if (*(unsigned int*)from < TRANSPARENT)
			*(int*)dst = *(int*)from;
		i++;
	}
}

void	draw_sprites(t_line *line, t_all *all, int count)
{
	int		i;

	i = 0;
	if (all->plr->dir > M_PI)
		all->plr->dir -= M_PI * 2;
	else if (all->plr->dir < -M_PI)
		all->plr->dir += M_PI * 2;
	while (i <= count)
	{
		if (all->items[i].plr_spr_dist < all->intr->dist &&
			all->items[i].cub_direct_angle < all->plr->dir + M_PI_2 &&
			all->items[i].cub_direct_angle > all->plr->dir - M_PI_2)
			draw_one_sprite(&all->items[i], line, all);
		else if (all->items[i].plr_spr_dist < all->intr->dist &&
			(all->items[i].cub_direct_angle - all->plr->dir > (M_PI * 2 -
			M_PI_2 / 2) || all->items[i].cub_direct_angle -
			all->plr->dir < (-M_PI * 2 + M_PI_2 / 2)))
			draw_one_sprite(&all->items[i], line, all);
		i++;
	}
}
