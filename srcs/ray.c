/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:09:44 by cdelicia          #+#    #+#             */
/*   Updated: 2019/10/05 13:22:05 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	make_step_shorter(int *flag, double *step, double *dist)
{
	*dist -= 0.60;
	*step = 0.00045;
	*flag = 1;
}

void	ft_raycasting(t_all *all, t_plr *plr, double angle, t_intersect *intr)
{
	double		x;
	double		y;
	double		dist;
	int			f;
	double		step;

	dist = 1;
	f = 0;
	step = 0.5;
	while (TRUE)
	{
		x = plr->x + dist * cos(angle + plr->dir);
		y = plr->y - dist * sin(angle + plr->dir);
		if (all->map[(int)(y / SCALE)][(int)(x / SCALE)] == '1' && f == 0)
			make_step_shorter(&f, &step, &dist);
		else if (all->map[(int)(y / SCALE)][(int)(x / SCALE)] == '1' && f == 1)
		{
			intr->x = x;
			intr->y = y;
			intr->dist = dist;
			all->intr = intr;
			return ;
		}
		dist += step;
	}
}

double	calculate_angle(int res_x_2, int line_number)
{
	double	angle;
	double	y;
	int		x_offset;

	y = res_x_2 / tan(M_PI_2 / 3);
	x_offset = abs(line_number - res_x_2);
	if (x_offset == 0)
		return (0);
	if (x_offset == 1)
		return ((M_PI_2 - atan(y / 1)));
	angle = ((M_PI_2 - atan(y / x_offset)) - \
	(M_PI_2 - atan(y / (x_offset - 1))));
	return (angle);
}

int		error_checker(int n, char **map, int h)
{
	free_array(map, h);
	if (n == 20)
		ft_putendl_fd("Error\nBad fd\n", 1);
	if (n == 21)
		ft_putendl_fd("Error\nInvalid *.cub file\n", 1);
	if (n == 22)
		ft_putendl_fd("Error\nInvalid map\n", 1);
	if (n == 23)
		ft_putendl_fd("Error\nMalloc\n", 1);
	if (n == 24)
		ft_putendl_fd("Error\nBad *argv[]\n", 1);
	if (n == 25)
		ft_putendl_fd("Error\nBad map legend\n", 1);
	if (n == 26)
		ft_putendl_fd("Error\nMlx pointer\n", 1);
	exit(1);
}

void	check_tail(char *l)
{
	while (*l == ' ')
		l++;
	while (ft_isdigit(*l) && *l != '\0')
		l++;
	if (*l == '\0')
		return ;
	while (*l == ' ' && *l != '\0')
		l++;
	if (*l == '\0')
		return ;
	ft_error_checker(ERR_BAD_MAP_LEGEND);
}
