/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 01:00:04 by cdelicia          #+#    #+#             */
/*   Updated: 2019/10/05 00:17:09 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	player_direction(char player)
{
	if (player == 'W')
		return (M_PI);
	if (player == 'N')
		return (M_PI_2);
	if (player == 'S')
		return (3 * M_PI_2);
	return (0);
}

void	player_direction_check(char **map, int i, int j)
{
	if (ft_strchr("NEWS", map[i][j]))
	{
		if (map[i][j - 1] == ' ' || map[i - 1][j - 1] == ' ')
			ft_error_checker(ERR_INVALID_MAP);
		if (map[i - 1][j] == ' ' || map[i - 1][j + 1] == ' ')
			ft_error_checker(ERR_INVALID_MAP);
		if (map[i][j + 1] == ' ' || map[i + 1][j + 1] == ' ')
			ft_error_checker(ERR_INVALID_MAP);
		if (map[i + 1][j] == ' ' || map[i + 1][j - 1] == ' ')
			ft_error_checker(ERR_INVALID_MAP);
	}
	else if (ft_strchr("2", map[i][j]))
	{
		if (map[i][j - 1] == ' ' || map[i - 1][j - 1] == ' ')
			ft_error_checker(ERR_INVALID_MAP);
		if (map[i - 1][j] == ' ' || map[i - 1][j + 1] == ' ')
			ft_error_checker(ERR_INVALID_MAP);
		if (map[i][j + 1] == ' ' || map[i + 1][j + 1] == ' ')
			ft_error_checker(ERR_INVALID_MAP);
		if (map[i + 1][j] == ' ' || map[i + 1][j - 1] == ' ')
			ft_error_checker(ERR_INVALID_MAP);
	}
}

void	ft_init_player(char **map, t_plr *plr)
{
	t_point pos;
	char	*plr_dir;
	int		player;

	pos.y = 0;
	player = 0;
	while (map[pos.y])
	{
		pos.x = 0;
		while (map[pos.y][pos.x])
		{
			if ((plr_dir = ft_strchr("NEWS", map[pos.y][pos.x])))
			{
				plr->x = pos.x * SCALE + SCALE / 2;
				plr->y = pos.y * SCALE + SCALE / 2;
				plr->dir = player_direction(*plr_dir);
				player_direction_check(map, pos.y, pos.x);
				player++;
			}
			pos.x++;
		}
		pos.y++;
	}
	if (player != 1)
		ft_error_checker(ERR_INVALID_MAP);
}

void	textures(t_all *all, t_tex *tex)
{
	int en;
	int bpp;

	if ((all->leg->nt_img = mlx_xpm_file_to_image(all->win->mlx, all->leg->nt, \
	&tex->n_resx, &tex->n_resy)) == NULL)
		no_correct_exit(all, ERR_BAD_MAP_LEGEND);
	tex->n = mlx_get_data_addr(all->leg->nt_img, &bpp, &tex->n_linel, &en);
	if ((all->leg->st_img = mlx_xpm_file_to_image(all->win->mlx, all->leg->st, \
	&tex->s_resx, &tex->s_resy)) == NULL)
		no_correct_exit(all, ERR_BAD_MAP_LEGEND);
	tex->s = mlx_get_data_addr(all->leg->st_img, &bpp, &tex->s_linel, &en);
	if ((all->leg->et_img = mlx_xpm_file_to_image(all->win->mlx, all->leg->et, \
	&tex->e_resx, &tex->e_resy)) == NULL)
		no_correct_exit(all, ERR_BAD_MAP_LEGEND);
	tex->e = mlx_get_data_addr(all->leg->et_img, &bpp, &tex->e_linel, &en);
	if ((all->leg->wt_img = mlx_xpm_file_to_image(all->win->mlx, all->leg->wt, \
	&tex->w_resx, &tex->w_resy)) == NULL)
		no_correct_exit(all, ERR_BAD_MAP_LEGEND);
	tex->w = mlx_get_data_addr(all->leg->wt_img, &bpp, &tex->w_linel, &en);
	if ((all->leg->spr_img = mlx_xpm_file_to_image(all->win->mlx, \
	all->leg->spr, &all->spr.width, &all->spr.height)) == NULL)
		no_correct_exit(all, ERR_BAD_MAP_LEGEND);
	all->spr.addr = mlx_get_data_addr(all->leg->spr_img, &bpp, \
	&all->spr.line_l, &en);
	all->tex = tex;
}
