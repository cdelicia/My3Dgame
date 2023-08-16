/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 00:52:03 by cdelicia          #+#    #+#             */
/*   Updated: 2019/09/28 23:49:50 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_element_legend(char **l, t_all *all)
{
	int			i;
	int			j;
	int			k;
	t_legend	*legend;

	i = 0;
	j = 0;
	k = 0;
	if ((legend = (t_legend *)malloc(sizeof(t_legend))) == NULL)
		error_checker(ERR_MALLOC, l, 8);
	check_legend_flags(l, j, k);
	while (l[i])
	{
		cel_help(l, legend, i, all);
		i++;
	}
	all->leg = legend;
	check_legend_data(legend);
}

void	check_legend_flags(char **l, int i, int k)
{
	while (l[i])
	{
		if (l[i][0] == 'R' && l[i][1] == ' ')
			k += 1;
		else if (l[i][0] == 'N' && l[i][1] == 'O' && l[i][2] == ' ')
			k += 2;
		else if (l[i][0] == 'S' && l[i][1] == 'O' && l[i][2] == ' ')
			k += 3;
		else if (l[i][0] == 'W' && l[i][1] == 'E' && l[i][2] == ' ')
			k += 4;
		else if (l[i][0] == 'E' && l[i][1] == 'A' && l[i][2] == ' ')
			k += 5;
		else if (l[i][0] == 'S' && l[i][1] == ' ')
			k += 6;
		else if (l[i][0] == 'F' && l[i][1] == ' ')
			k += 7;
		else if (l[i][0] == 'C' && l[i][1] == ' ')
			k += 8;
		else
			k += 37;
		i++;
	}
	if (i != 8 || k != 36)
		error_checker(ERR_BAD_MAP_LEGEND, l, 8);
}

void	check_legend_data(t_legend *legend)
{
	if (check_path(legend->nt) == 0 || check_path(legend->et) == 0 || \
		check_path(legend->wt) == 0 || check_path(legend->st) == 0 || \
		check_path(legend->spr) == 0)
		ft_error_checker(ERR_BAD_MAP_LEGEND);
	if (legend->r1 > 255 || legend->r2 > 255 || legend->g1 > 255 || \
		legend->g2 > 255 || legend->b1 > 255 || legend->b2 > 255 || \
		legend->r1 < 0 || legend->r2 < 0 || legend->g1 < 0 || \
		legend->g2 < 0 || legend->b1 < 0 || legend->b2 < 0)
		ft_error_checker(ERR_BAD_MAP_LEGEND);
	legend->nt_img = NULL;
	legend->wt_img = NULL;
	legend->et_img = NULL;
	legend->st_img = NULL;
	legend->spr_img = NULL;
}

int		check_path(char *name)
{
	while (*name != '\0')
	{
		if (*name == '.')
			if (ft_strncmp(name, ".xpm", 4) == 0)
				if (name[4] == '\0')
					return (1);
		name++;
	}
	return (0);
}

int		check_filename(char *name)
{
	while (*name != '\0')
	{
		if (*name == '.')
			if (ft_strncmp(name, ".cub", 4) == 0)
				if (name[4] == '\0')
					return (1);
		name++;
	}
	return (0);
}
