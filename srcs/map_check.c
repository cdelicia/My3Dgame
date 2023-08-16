/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 03:26:18 by cdelicia          #+#    #+#             */
/*   Updated: 2019/09/22 02:35:30 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_oneside(char **map, int f, int maxh, int maxl)
{
	int j;

	j = 0;
	if (f == 1)
	{
		while (j <= maxl)
		{
			if (map[1][j] == '0')
				return (error_checker(ERR_INVALID_MAP, map, maxh));
			else
				j++;
		}
	}
	else if (f == 2)
	{
		while (j <= maxl)
		{
			if (map[maxh - 1][j] == '0')
				return (error_checker(ERR_INVALID_MAP, map, maxh));
			else
				j++;
		}
	}
	return (0);
}

int		check_backside(char **map, int f, int maxh, int maxl)
{
	int i;

	i = 0;
	if (f == 1)
	{
		while (i <= maxh)
		{
			if (map[i][1] == '0')
				return (error_checker(ERR_INVALID_MAP, map, maxh));
			else
				i++;
		}
	}
	else if (f == 2)
	{
		while (i <= maxh)
		{
			if (map[i][maxl - 1] == '0')
				return (error_checker(ERR_INVALID_MAP, map, maxh));
			else
				i++;
		}
	}
	return (0);
}

int		check_allside(char **map, int j, int maxh, int maxl)
{
	int i;

	i = 1;
	while (i < maxh)
	{
		while (j < maxl)
		{
			if (map[i][j] == ' ')
			{
				if (map[i][j - 1] == '0' || map[i - 1][j - 1] == '0')
					return (error_checker(ERR_INVALID_MAP, map, maxh));
				if (map[i - 1][j] == '0' || map[i - 1][j + 1] == '0')
					return (error_checker(ERR_INVALID_MAP, map, maxh));
				if (map[i][j + 1] == '0' || map[i + 1][j + 1] == '0')
					return (error_checker(ERR_INVALID_MAP, map, maxh));
				if (map[i + 1][j] == '0' || map[i + 1][j - 1] == '0')
					return (error_checker(ERR_INVALID_MAP, map, maxh));
			}
			j++;
		}
		i++;
		j = 1;
	}
	return (0);
}

char	**check_map(char **map, int maxh, int maxl)
{
	int i;
	int j;
	int error;

	i = 0;
	j = 0;
	while (map[i])
	{
		if (i == 0)
		{
			error = check_oneside(map, 1, maxh, maxl);
			error = check_oneside(map, 2, maxh, maxl);
			error = check_backside(map, 2, maxh, maxl);
			error = check_backside(map, 1, maxh, maxl);
		}
		else
			error = check_allside(map, 1, maxh, maxl);
		if (error == -1)
			return (NULL);
		i++;
	}
	return (map);
}

int		check_map_symbols(char **map)
{
	int i;
	int j;

	j = 1;
	while (map[j])
	{
		i = 1;
		while (map[j][i])
		{
			if (map[j][i] != ' ' && map[j][i] != '1' && \
			map[j][i] != '2' && map[j][i] != '0' && \
			map[j][i] != 'S' && map[j][i] != 'N' && \
			map[j][i] != 'E' && map[j][i] != 'W')
				return (ft_error_checker(ERR_INVALID_MAP));
			i++;
		}
		j++;
	}
	return (0);
}
