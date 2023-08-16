/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:04:59 by cdelicia          #+#    #+#             */
/*   Updated: 2019/10/01 02:47:29 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	write_header_to_file(int fd, t_all *all)
{
	int				total;
	unsigned char	header[HEADER];
	int				sum;

	total = 0;
	sum = HEADER + INFO_HEADER + COLOR_TABLE;
	while (total < HEADER)
		header[total++] = 0;
	total = sum + all->leg->res_x * all->leg->res_y * BYPP;
	header[0] = OX42;
	header[1] = OX4D;
	header[2] = (unsigned char)(total % 256);
	header[3] = (unsigned char)(total / 256 % 256);
	header[4] = (unsigned char)(total / 256 / 256 % 256);
	header[5] = (unsigned char)(total / 256 / 256 / 256 % 256);
	header[10] = (unsigned char)sum;
	write(fd, header, HEADER);
}

void	write_info_to_file(int fd, t_all *all)
{
	int				res;
	unsigned char	info[INFO_HEADER];

	res = 0;
	while (res < INFO_HEADER)
		info[res++] = 0;
	info[0] = (unsigned char)INFO_HEADER;
	res = all->leg->res_x;
	info[4] = (unsigned char)(res % 256);
	info[5] = (unsigned char)(res / 256 % 256);
	info[6] = (unsigned char)(res / 256 / 256 % 256);
	info[7] = (unsigned char)(res / 256 / 256 / 256 % 256);
	res = all->leg->res_y;
	info[8] = (unsigned char)(res % 256);
	info[9] = (unsigned char)(res / 256 % 256);
	info[10] = (unsigned char)(res / 256 / 256 % 256);
	info[11] = (unsigned char)(res / 256 / 256 / 256 % 256);
	info[12] = (unsigned char)OX0001;
	info[14] = (unsigned char)OX20;
	write(fd, info, INFO_HEADER);
}

void	write_data_to_file(int fd, char *dst, t_all *all)
{
	int				i;
	unsigned char	pixel[4];
	int				j;
	int				clr;

	i = all->leg->res_x * (all->leg->res_y - 1);
	while (i >= 0)
	{
		j = 0;
		while (j < all->leg->res_x)
		{
			clr = ((int *)dst)[i];
			pixel[0] = (unsigned char)(clr % 256);
			pixel[1] = (unsigned char)(clr / 256 % 256);
			pixel[2] = (unsigned char)(clr / 256 / 256 % 256);
			pixel[3] = (unsigned char)(0);
			write(fd, &pixel, 4);
			j++;
			i++;
		}
		i -= 2 * all->leg->res_x;
	}
}

void	save_to_bmp(char *dst, t_all *all)
{
	int fd;

	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
		no_correct_exit(all, ERR_FD);
	write_header_to_file(fd, all);
	write_info_to_file(fd, all);
	write_data_to_file(fd, dst, all);
	close(fd);
	ft_putstr_fd("screenshot.bmp created\n", 1);
}

int		ft_error_checker(int n)
{
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
