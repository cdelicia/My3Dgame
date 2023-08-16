/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 02:10:37 by cdelicia          #+#    #+#             */
/*   Updated: 2019/10/05 00:19:51 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	choosing_texture_sn(t_all *all)
{
	all->intr->offset = all->intr->x - floor(all->intr->x / SCALE) * SCALE;
	if (all->intr->y > all->plr->y)
	{
		all->tex->what_now = all->tex->s;
		all->tex->side = 'S';
		all->tex->res_x = all->tex->s_resx;
		all->tex->res_y = all->tex->s_resy;
		all->tex->line_l = all->tex->s_linel;
	}
	else
	{
		all->tex->what_now = all->tex->n;
		all->tex->side = 'N';
		all->tex->res_x = all->tex->n_resx;
		all->tex->res_y = all->tex->n_resy;
		all->tex->line_l = all->tex->n_linel;
	}
}

void	choosing_texture_ew(t_all *all)
{
	all->intr->offset = all->intr->y - floor(all->intr->y / SCALE) * SCALE;
	if (all->intr->x > all->plr->x)
	{
		all->tex->what_now = all->tex->e;
		all->tex->side = 'E';
		all->tex->res_x = all->tex->e_resx;
		all->tex->res_y = all->tex->e_resy;
		all->tex->line_l = all->tex->e_linel;
	}
	else
	{
		all->tex->what_now = all->tex->w;
		all->tex->side = 'W';
		all->tex->res_x = all->tex->w_resx;
		all->tex->res_y = all->tex->w_resy;
		all->tex->line_l = all->tex->w_linel;
	}
}

void	draw_wall_inverted(t_line *line, t_all *all, int *i, int *end)
{
	char	*dst;
	char	*from;

	dst = NULL;
	from = NULL;
	while (*i < line->size - *end)
	{
		from = all->tex->what_now + (int)(*i * all->tex->res_y / \
		line->size) * all->tex->line_l;
		from += (int)((SCALE - all->intr->offset) * all->tex->res_x / SCALE)
		* BYPP;
		dst = all->win->addr;
		dst += line->number * BYPP;
		dst += (*i + (int)(all->leg->res_y / 2 - line->size / 2)) *
		all->win->line_l;
		if (*(unsigned int*)from >= TRANSPARENT)
			*(int*)dst = all->leg->ceiling;
		else
			*(int*)dst = *(int*)from;
		*i += 1;
	}
	*i = line->size - *end;
}

void	choosing_side(t_all *all)
{
	if (fabs(all->intr->y / SCALE - lround(all->intr->y / SCALE)) < \
		fabs(all->intr->x / SCALE - lround(all->intr->x / SCALE)))
		all->intr->offset = all->intr->x - floor(all->intr->x / SCALE) * SCALE;
	else
		all->intr->offset = all->intr->y - floor(all->intr->y / SCALE) * SCALE;
}
