/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 14:23:24 by cdelicia          #+#    #+#             */
/*   Updated: 2019/10/05 13:17:29 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "./mlx_mms/mlx.h"
# include "./libft/libft.h"
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define SCALE 64
# define STEP 10
# define LIM 16

# define HEADER 14
# define INFO_HEADER 40
# define COLOR_TABLE 0
# define OX42 66
# define OX4D 77
# define BYPP 4
# define OX0001 1
# define OX20 32

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124

# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define PURPLE 0x990099
# define TRUE 1
# define TRANSPARENT 0xFF000000
# define RAD 57.29577951308

# define ERR_FD 20
# define ERR_INVALID_CUB_FILE 21
# define ERR_INVALID_MAP 22
# define ERR_MALLOC 23
# define ERR_ARG 24
# define ERR_BAD_MAP_LEGEND 25
# define ERR_MLX 26

typedef struct	s_struct
{
	int			res_x;
	int			res_y;
	char		*nt;
	char		*et;
	char		*wt;
	char		*st;
	char		*spr;
	void		*nt_img;
	void		*et_img;
	void		*wt_img;
	void		*st_img;
	void		*spr_img;
	int			r1;
	int			g1;
	int			b1;
	int			r2;
	int			g2;
	int			b2;
	int			ceiling;
	int			floor;
}				t_legend;

typedef struct	s_win
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			line_l;
	int			bpp;
	int			en;
}				t_win;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_plr
{
	double		x;
	double		y;
	double		dir;
	double		start;
	double		end;
}				t_plr;

typedef struct	s_texture
{
	char		*n;
	char		*e;
	char		*w;
	char		*s;
	int			w_resx;
	int			w_resy;
	int			w_linel;
	int			n_resx;
	int			n_resy;
	int			n_linel;
	int			e_resx;
	int			e_resy;
	int			e_linel;
	int			s_resx;
	int			s_resy;
	int			s_linel;
	int			res_x;
	int			res_y;
	int			line_l;
	char		*what_now;
	char		side;
}				t_tex;

typedef struct	s_intersect
{
	double		x;
	double		y;
	double		dist;
	double		offset;
	char		text;
}				t_intersect;

typedef struct	s_line
{
	int			size;
	int			number;
	double		angle;
	int			size_sprite;
}				t_line;

typedef struct	s_spr
{
	double		x_start;
	double		y_start;
	int			height;
	int			width;
	char		*addr;
	double		angle;
	int			line_l;
}				t_spr;

typedef struct	s_items
{
	double		plr_spr_dist;
	double		x_center;
	double		y_center;
	double		cub_direct_angle;
	double		beta;
	double		spr_offset;
	double		x_offset;
	double		y_offset;
}				t_items;

typedef struct	s_all
{
	t_win		*win;
	t_plr		*plr;
	t_legend	*leg;
	t_tex		*tex;
	t_intersect	*intr;
	t_line		*line;
	t_spr		spr;
	t_items		*items;
	char		**map;
	int			bmp;
	int			size_map;
	int			esc;
}				t_all;

char			**ft_read_map(char *av, t_all *all);
char			**split_legend(char **map, int *tmp);
int				map_size(char **map, int *len);
char			**make_new_map(int l, char **cut_map, char **map);
char			**ft_cut_map(char **map, int *i);
char			**make_map(t_list **head, int size, t_all *all, int i);
char			**fix_legend(char **l, t_all *all);
void			check_element_legend(char **l, t_all *all);
char			**check_map(char **map, int h, int l);
void			check_legend_data(t_legend *legend);
void			check_legend_flags(char **l, int j, int k);
int				check_path(char *name);
void			cel_help(char **l, t_legend *legend, int i, t_all *all);
int				check_filename(char *name);
int				check_map_symbols(char **map);
int				ft_error_checker(int n);
int				error_checker(int n, char **map, int h);
void			check_tail(char *l);

int				del_all(int i, char **c_m, char **m, char **l);
void			free_array(char **arr, int i);
void			free_all_struct(t_all *all);
int				correct_exit(t_all *all);
int				no_correct_exit(t_all *all, int n);
void			player_direction_check(char **map, int i, int j);

void			draw_sprites(t_line *line, t_all *all, int count);
void			ft_draw_scene(t_all *all);
void			draw_wall(t_line *line, t_all *all);
void			draw_wall_inverted(t_line *line, t_all *all, int *i, int *end);
void			ft_raycasting(t_all *all, t_plr *plr, double a, t_intersect *i);
void			create_new_image(t_win *win, t_all *all, t_tex *tex);
int				key_press(int key, t_all *all);
void			ft_init_player(char **map, t_plr *plr);
void			textures(t_all *all, t_tex *tex);
int				num_of_spr(char **map);
int				scale_texture(t_line *line, t_all *all, int *end);
int				scale_sprite(t_line *line, t_items *item, t_all *all, int *end);
double			calculate_angle(int res_x, int line_number);
void			save_to_bmp(char *dst, t_all *all);
void			choosing_side(t_all *all);
int				calc_all_sprite_values(char **map, t_items *items, t_plr *plr);
void			choosing_texture_ew(t_all *all);
void			choosing_texture_sn(t_all *all);
void			my_qsort(t_items *items, int left, int right);

#endif
