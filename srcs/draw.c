/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 00:32:39 by cdelicia          #+#    #+#             */
/*   Updated: 2019/09/30 01:56:37 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_line *line, t_all *all)
{
	int		i;
	char	*dst;

	i = 0;
	while (i < (int)(all->leg->res_y / 2 - line->size / 2))
	{
		dst = all->win->addr;
		dst += line->number * BYPP;
		dst += i * all->win->line_l;
		*(int *)dst = all->leg->ceiling;
		i++;
	}
}

void	draw_floor(t_line *line, t_all *all)
{
	int		i;
	char	*dst;

	i = (int)(all->leg->res_y / 2 + line->size / 2);
	while (i < all->leg->res_y)
	{
		dst = all->win->addr;
		dst += line->number * BYPP;
		dst += i * all->win->line_l;
		*(int *)dst = all->leg->floor;
		i++;
	}
}

void	draw_wall(t_line *line, t_all *all)
{
	int		i;
	char	*dst;
	char	*from;
	int		end;

	i = scale_texture(line, all, &end);
	if (all->tex->side == 'S' || all->tex->side == 'W')
		draw_wall_inverted(line, all, &i, &end);
	while (i < line->size - end)
	{
		from = all->tex->what_now + (int)(i * all->tex->res_y / \
		line->size) * all->tex->line_l;
		from += (int)(all->intr->offset * all->tex->res_x / SCALE) * BYPP;
		dst = all->win->addr;
		dst += line->number * BYPP;
		dst += (i + (int)(all->leg->res_y / 2 - line->size / 2)) *
		all->win->line_l;
		if (*(unsigned int*)from >= TRANSPARENT)
			*(int*)dst = all->leg->ceiling;
		else
			*(int*)dst = *(int*)from;
		i++;
	}
}

void	ft_draw_image(t_all *all, t_line line, t_intersect *intr)
{
	int	count;

	if ((all->items = malloc(sizeof(t_items) * num_of_spr(all->map))) == NULL)
		no_correct_exit(all, ERR_MALLOC);
	count = calc_all_sprite_values(all->map, all->items, all->plr);
	my_qsort(all->items, 0, count - 1);
	while (line.number < all->leg->res_x)
	{
		ft_raycasting(all, all->plr, line.angle, intr);
		if (fabs(all->intr->y / SCALE - lround(all->intr->y / SCALE)) < \
			fabs(all->intr->x / SCALE - lround(all->intr->x / SCALE)))
			choosing_texture_sn(all);
		else
			choosing_texture_ew(all);
		if ((line.size = (int)(SCALE / (2 * tan(M_PI_2 / 3)) * \
		all->leg->res_x / (all->intr->dist * cos(line.angle)))) < 0)
			line.size = 0;
		draw_ceiling(&line, all);
		draw_wall(&line, all);
		draw_floor(&line, all);
		draw_sprites(&line, all, count - 1);
		line.angle -= calculate_angle(all->leg->res_x / 2, line.number);
		line.number += 1;
	}
	free(all->items);
}

void	ft_draw_scene(t_all *all)
{
	t_line		line;
	t_intersect intr;

	line.angle = M_PI_2 / 3;
	line.number = 0;
	ft_draw_image(all, line, &intr);
	if (all->bmp == 1)
	{
		save_to_bmp(all->win->addr, all);
		correct_exit(all);
	}
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
}
