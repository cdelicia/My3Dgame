/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:28:20 by cdelicia          #+#    #+#             */
/*   Updated: 2019/10/05 01:16:06 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	diagonal_movement(t_all *all, t_plr *plr, double *x, double *y)
{
	if ((*x > 0 && all->map[(int)(plr->y + *y + LIM) /
	SCALE][(int)((plr->x + *x + LIM)) / SCALE] == '2')
	|| (*x < 0 && all->map[(int)(plr->y + *y - LIM) /
	SCALE][(int)((plr->x + *x - LIM)) / SCALE] == '2')
	|| (*y > 0 && all->map[(int)(plr->y + *y + LIM) /
	SCALE][(int)(plr->x + *x + LIM) / SCALE] == '2')
	|| (*y < 0 && all->map[(int)(plr->y + *y - LIM) /
	SCALE][(int)(plr->x + *x - LIM) / SCALE] == '2'))
	{
		*x = 0;
		*y = 0;
	}
}

void	toleft_toright(int key, t_all *all, t_plr *plr)
{
	double	x;
	double	y;

	x = STEP * sin(all->plr->dir);
	x *= key == 0 ? -1 : 1;
	if ((x > 0 && all->map[(int)(plr->y) / SCALE][(int)((plr->x + x + LIM))
	/ SCALE] == '1') || (x < 0 && all->map[(int)(plr->y) / SCALE][(int)((plr->x
	+ x - LIM)) / SCALE] == '1') || (x > 0 && all->map[(int)(plr->y) /
	SCALE][(int)((plr->x + x + LIM)) / SCALE] == '2') || (x < 0 &&
	all->map[(int)(plr->y) / SCALE][(int)((plr->x + x - LIM)) / SCALE] == '2'))
		x = 0;
	y = STEP * cos(all->plr->dir);
	y *= key == 0 ? -1 : 1;
	if ((y > 0 && all->map[(int)(plr->y + y + LIM) / SCALE][(int)(plr->x) /
	SCALE] == '1') || (y < 0 && all->map[(int)(plr->y + y - LIM) / SCALE][(int)
	(plr->x) / SCALE] == '1') || (y > 0 && all->map[(int)(plr->y + y + LIM) /
	SCALE][(int)(plr->x) / SCALE] == '2') || (y < 0 && all->map[(int)(plr->y + y
	- LIM) / SCALE][(int)(plr->x) / SCALE] == '2'))
		y = 0;
	diagonal_movement(all, plr, &x, &y);
	all->plr->x += x;
	all->plr->y += y;
}

void	tofront_toback(int key, t_all *all, t_plr *plr)
{
	double	x;
	double	y;

	x = STEP * cos(all->plr->dir);
	x *= key == 1 ? -1 : 1;
	if ((x > 0 && all->map[(int)(plr->y) / SCALE][(int)((plr->x + x + LIM)) /
	SCALE] == '1') || (x < 0 && all->map[(int)(plr->y) / SCALE][(int)((plr->x +
	x - LIM)) / SCALE] == '1') || (x > 0 && all->map[(int)(plr->y) /
	SCALE][(int)((plr->x + x + LIM)) / SCALE] == '2') || (x < 0 &&
	all->map[(int)(plr->y) / SCALE][(int)((plr->x + x - LIM)) / SCALE] == '2'))
		x = 0;
	y = STEP * sin(all->plr->dir);
	y *= key == 1 ? 1 : -1;
	if ((y > 0 && all->map[(int)(plr->y + y + LIM) / SCALE][(int)(plr->x) /
	SCALE] == '1') || (y < 0 && all->map[(int)(plr->y + y - LIM) /
	SCALE][(int)(plr->x) / SCALE] == '1') || (y > 0 && all->map[(int)(plr->y +
	y + LIM) / SCALE][(int)(plr->x) / SCALE] == '2') || (y < 0 &&
	all->map[(int)(plr->y + y - LIM) / SCALE][(int)(plr->x) / SCALE] == '2'))
		y = 0;
	diagonal_movement(all, plr, &x, &y);
	all->plr->x += x;
	all->plr->y += y;
}

int		key_press(int key, t_all *all)
{
	if (key == ESC)
	{
		all->esc = 1;
		correct_exit(all);
	}
	if (key == W || key == S)
		tofront_toback(key, all, all->plr);
	if (key == LEFT)
		all->plr->dir += M_PI_4 / 4;
	if (key == RIGHT)
		all->plr->dir -= M_PI_4 / 4;
	if (key == A || key == D)
		toleft_toright(key, all, all->plr);
	if (all->plr->dir > M_PI * 2)
		all->plr->dir -= M_PI * 2;
	else if (all->plr->dir < -M_PI * 2)
		all->plr->dir += M_PI * 2;
	ft_draw_scene(all);
	return (0);
}
