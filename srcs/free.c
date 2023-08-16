/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 00:25:08 by cdelicia          #+#    #+#             */
/*   Updated: 2019/09/22 01:50:04 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		correct_exit(t_all *all)
{
	free_array(all->map, all->size_map);
	if (all->leg->nt_img)
		mlx_destroy_image(all->win->mlx, all->leg->nt_img);
	if (all->leg->et_img)
		mlx_destroy_image(all->win->mlx, all->leg->et_img);
	if (all->leg->st_img)
		mlx_destroy_image(all->win->mlx, all->leg->st_img);
	if (all->leg->wt_img)
		mlx_destroy_image(all->win->mlx, all->leg->wt_img);
	if (all->leg->spr_img)
		mlx_destroy_image(all->win->mlx, all->leg->spr_img);
	if (all->win->img)
		mlx_destroy_image(all->win->mlx, all->win->img);
	if (all->esc)
		mlx_destroy_window(all->win->mlx, all->win->win);
	if (all->win->mlx)
		free(all->win->mlx);
	if (all->leg)
		free_all_struct(all);
	ft_putendl_fd("cub3D\nClosed\n", 1);
	exit(0);
}

void	free_all_struct(t_all *all)
{
	free(all->leg->nt);
	free(all->leg->et);
	free(all->leg->st);
	free(all->leg->wt);
	free(all->leg->spr);
	free(all->leg);
}

int		del_all(int i, char **cut_map, char **map, char **legend)
{
	if (i == 0)
		free(map);
	else
	{
		free_array(cut_map, i + 2);
		free(map);
	}
	free(legend);
	return (0);
}

void	free_array(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}

int		no_correct_exit(t_all *all, int n)
{
	free_array(all->map, all->size_map);
	if (all->leg->nt_img)
		mlx_destroy_image(all->win->mlx, all->leg->nt_img);
	if (all->leg->et_img)
		mlx_destroy_image(all->win->mlx, all->leg->et_img);
	if (all->leg->st_img)
		mlx_destroy_image(all->win->mlx, all->leg->st_img);
	if (all->leg->wt_img)
		mlx_destroy_image(all->win->mlx, all->leg->wt_img);
	if (all->leg->spr_img)
		mlx_destroy_image(all->win->mlx, all->leg->spr_img);
	if (all->win->img)
		mlx_destroy_image(all->win->mlx, all->win->img);
	if (all->esc)
		mlx_destroy_window(all->win->mlx, all->win->win);
	if (all->win->mlx)
		free(all->win->mlx);
	if (all->leg)
		free_all_struct(all);
	ft_error_checker(n);
	exit(0);
}
