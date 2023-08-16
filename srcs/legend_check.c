/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legend_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 03:32:00 by cdelicia          #+#    #+#             */
/*   Updated: 2019/10/05 14:21:44 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**fix_legend(char **l, t_all *all)
{
	int i;
	int j;

	i = 0;
	while (l[i])
	{
		j = 0;
		while (l[i][j])
		{
			if (l[i][j] == ' ' && l[i][j + 1] == ' ')
			{
				while (l[i][j + 1])
				{
					l[i][j + 1] = l[i][j + 2];
					j++;
				}
				j = 0;
			}
			j++;
		}
		l[i][j] = '\0';
		i++;
	}
	check_element_legend(l, all);
	return (l);
}

void	check_ceiling(char *l, t_legend *legend)
{
	++l;
	while (*l == ' ')
		l++;
	if (ft_isdigit(*l))
		legend->r1 = ft_atoi(l);
	else
		ft_error_checker(ERR_BAD_MAP_LEGEND);
	while (*l != ',' && *l != '\0')
		l++;
	if (*l == ',' && (*(l + 1) == ' ' || ft_isdigit(*(l + 1))))
		legend->g1 = ft_atoi(++l);
	else
		ft_error_checker(ERR_BAD_MAP_LEGEND);
	while (*l != ',' && *l != '\0')
		l++;
	if (*l == ',' && (*(l + 1) == ' ' || ft_isdigit(*(l + 1))))
		legend->b1 = ft_atoi(++l);
	else
		ft_error_checker(ERR_BAD_MAP_LEGEND);
	check_tail(l);
	legend->ceiling = legend->r1 * 256 * 256 + legend->g1 * 256 + legend->b1;
}

void	check_floor(char *l, t_legend *legend)
{
	++l;
	while (*l == ' ')
		l++;
	if (ft_isdigit(*l))
		legend->r2 = ft_atoi(l);
	else
		ft_error_checker(ERR_BAD_MAP_LEGEND);
	while (*l != ',' && *l != '\0')
		l++;
	if (*l == ',' && (*(l + 1) == ' ' || ft_isdigit(*(l + 1))))
		legend->g2 = ft_atoi(++l);
	else
		ft_error_checker(ERR_BAD_MAP_LEGEND);
	while (*l != ',' && *l != '\0')
		l++;
	if (*l == ',' && (*(l + 1) == ' ' || ft_isdigit(*(l + 1))))
		legend->b2 = ft_atoi(++l);
	else
		ft_error_checker(ERR_BAD_MAP_LEGEND);
	check_tail(l);
	legend->floor = legend->r2 * 256 * 256 + legend->g2 * 256 + legend->b2;
}

void	check_resolution(char *l, t_legend *legend, t_all *all)
{
	int	max_res_x;
	int	max_res_y;

	max_res_x = 0;
	max_res_y = 0;
	legend->res_x = 1;
	legend->res_y = 1;
	mlx_get_screen_size(all->win->mlx, &max_res_x, &max_res_y);
	legend->res_x = ft_atoi(++l);
	if (legend->res_x < 1)
		ft_error_checker(ERR_BAD_MAP_LEGEND);
	if (legend->res_x > max_res_x)
		legend->res_x = max_res_x;
	while (*l == ' ')
		l++;
	while (ft_isdigit(*l))
		l++;
	legend->res_y = ft_atoi(l);
	if (legend->res_y < 1)
		ft_error_checker(ERR_BAD_MAP_LEGEND);
	if (legend->res_y > max_res_y)
		legend->res_y = max_res_y;
	check_tail(l);
}

void	cel_help(char **l, t_legend *legend, int i, t_all *all)
{
	if (l[i][0] == 'R' && l[i][1] == ' ')
		check_resolution(l[i], legend, all);
	if (l[i][0] == 'N' && l[i][1] == 'O' && l[i][2] == ' ')
		legend->nt = ft_strdup(l[i] + 3);
	if (l[i][0] == 'S' && l[i][1] == 'O' && l[i][2] == ' ')
		legend->st = ft_strdup(l[i] + 3);
	if (l[i][0] == 'W' && l[i][1] == 'E' && l[i][2] == ' ')
		legend->wt = ft_strdup(l[i] + 3);
	if (l[i][0] == 'E' && l[i][1] == 'A' && l[i][2] == ' ')
		legend->et = ft_strdup(l[i] + 3);
	if (l[i][0] == 'S' && l[i][1] == ' ')
		legend->spr = ft_strdup(l[i] + 2);
	if (l[i][0] == 'F' && l[i][1] == ' ')
		check_floor(l[i], legend);
	if (l[i][0] == 'C' && l[i][1] == ' ')
		check_ceiling(l[i], legend);
}
