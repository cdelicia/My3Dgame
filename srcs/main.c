/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 14:23:22 by cdelicia          #+#    #+#             */
/*   Updated: 2019/09/30 01:03:40 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_read_map(char *argv, t_all *all)
{
	int		i;
	int		fd;
	char	*line;
	t_list	*head;
	char	**map;

	line = NULL;
	head = NULL;
	map = NULL;
	i = 0;
	if ((fd = open(argv, O_RDONLY)) < 0)
		ft_error_checker(ERR_FD);
	while (get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	map = make_map(&head, ft_lstsize(head), all, i);
	ft_lstclear(&head, free);
	close(fd);
	return (map);
}

void	initialization(t_all *all, t_plr *plr)
{
	plr->x = 0;
	plr->y = 0;
	plr->start = 0;
	plr->dir = 0;
	plr->end = 0;
	all->bmp = 0;
	all->esc = 0;
}

void	argv_check(int argc, char **argv, t_all *all, t_plr *plr)
{
	if (argc == 1)
		ft_error_checker(ERR_ARG);
	else if (argc == 2 && check_filename(argv[1]) == 1)
	{
		all->map = ft_read_map(argv[1], all);
		check_map_symbols(all->map);
	}
	else if (argc == 2 && check_filename(argv[1]) == 0)
		ft_error_checker(ERR_INVALID_CUB_FILE);
	else if (argc == 3 && (ft_strncmp(argv[2], "--save", 6) == 0))
	{
		if ((argv[2])[6] == '\0')
		{
			all->bmp = 1;
			all->map = ft_read_map(argv[1], all);
		}
		else
			ft_error_checker(ERR_ARG);
	}
	else
		ft_error_checker(ERR_ARG);
	ft_init_player(all->map, plr);
	all->plr = plr;
}

void	create_new_image(t_win *win, t_all *all, t_tex *tex)
{
	int rem;

	rem = all->leg->res_x % SCALE;
	if (all->bmp == 1 && (rem <= (SCALE / 2)) && rem > 0)
		all->leg->res_x -= rem;
	else if (all->bmp == 1 && (rem > (SCALE / 2)) && rem < SCALE)
		all->leg->res_x += (SCALE - rem);
	win->win = mlx_new_window(win->mlx, all->leg->res_x, all->leg->res_y, \
	"cub3D");
	if (win->win == NULL)
		no_correct_exit(all, ERR_MLX);
	win->img = mlx_new_image(win->mlx, all->leg->res_x, all->leg->res_y);
	if (win->img == NULL || win->win == NULL)
		no_correct_exit(all, ERR_MLX);
	win->addr = mlx_get_data_addr(win->img, &win->bpp, &win->line_l, &win->en);
	textures(all, tex);
}

int		main(int argc, char **argv)
{
	t_win win;
	t_plr plr;
	t_all all;
	t_tex tex;

	initialization(&all, &plr);
	win.mlx = mlx_init();
	all.win = &win;
	argv_check(argc, argv, &all, &plr);
	create_new_image(&win, &all, &tex);
	ft_draw_scene(&all);
	mlx_hook(win.win, 2, (1L << 0), &key_press, &all);
	mlx_hook(win.win, 17, (1L << 0), &correct_exit, &all);
	mlx_loop(win.mlx);
	return (0);
}
