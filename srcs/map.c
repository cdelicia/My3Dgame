/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 02:23:29 by cdelicia          #+#    #+#             */
/*   Updated: 2019/10/05 01:43:48 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**split_legend(char **map, int *tmp)
{
	int		i;
	int		j;
	char	**legend;
	int		remember;

	i = 0;
	j = 0;
	*tmp = 0;
	remember = 0;
	legend = (char **)ft_calloc(9, sizeof(char *));
	while (map[i])
	{
		if (map[i][0] == ' ' || ft_isdigit(map[i][0]))
			*tmp += 1;
		if (ft_isdigit(map[i][0]) && remember == 0)
			remember = i;
		if (ft_isalpha(map[i][0]) && j < 8)
			legend[j++] = map[i];
		if (ft_isalpha(map[i][0]) && i > remember && remember != 0)
			ft_error_checker(ERR_BAD_MAP_LEGEND);
		i++;
	}
	return (legend);
}

int		map_size(char **map, int *len)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (map[i])
	{
		if (map[i][0] == ' ' || ft_isdigit(map[i][0]))
			count++;
		i++;
	}
	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) > *len)
			*len = (int)ft_strlen(map[i]);
		i++;
	}
	*len += 2;
	return (count);
}

char	**make_new_map(int l, char **cut_map, char **map)
{
	int		i;
	int		j;
	int		k;

	i = 1;
	j = 0;
	while (map[j])
	{
		if (map[j][0] == ' ' || ft_isdigit(map[j][0]))
		{
			k = 1;
			cut_map[i] = (char *)ft_calloc(l + 1, sizeof(char));
			cut_map[i][k - 1] = ' ';
			while (map[j][k - 1])
			{
				cut_map[i][k] = map[j][k - 1];
				k++;
			}
			while (k < l)
				cut_map[i][k++] = ' ';
			i++;
		}
		j++;
	}
	return (cut_map);
}

char	**ft_cut_map(char **map, int *size)
{
	int		i;
	int		height;
	int		len;
	char	*str;
	char	**cut_map;

	i = 0;
	len = 0;
	str = NULL;
	cut_map = NULL;
	height = map_size(map, &len) + 2;
	*size = len;
	if ((str = (char *)ft_calloc(len + 1, sizeof(char))) == NULL)
		error_checker(ERR_MALLOC, map, height - 2);
	while (len > i)
		str[i++] = ' ';
	if ((cut_map = (char **)ft_calloc(height + 1, sizeof(char *))) == NULL)
	{
		free(str);
		error_checker(ERR_MALLOC, map, height - 2);
	}
	cut_map[0] = ft_strdup(str);
	cut_map[height - 1] = ft_strdup(str);
	free(str);
	return (make_new_map(len, cut_map, map));
}

char	**make_map(t_list **head, int size, t_all *all, int i)
{
	t_list	*tmp;
	char	**map;
	char	**legend;
	char	**cut_map;

	tmp = *head;
	if ((map = ft_calloc(size + 1, sizeof(char *))) == NULL)
		ft_error_checker(ERR_MALLOC);
	while (tmp)
	{
		map[i++] = tmp->content;
		tmp = tmp->next;
	}
	legend = split_legend(map, &i);
	cut_map = ft_cut_map(map, &size);
	if (check_map(cut_map, i + 1, size - 1) == NULL)
	{
		del_all(i, cut_map, map, legend);
		ft_error_checker(ERR_INVALID_MAP);
	}
	legend = fix_legend(legend, all);
	del_all(0, cut_map, map, legend);
	all->size_map = i + 2;
	return (cut_map);
}
