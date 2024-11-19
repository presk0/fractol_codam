/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:19:05 by supersko          #+#    #+#             */
/*   Updated: 2024/11/19 15:20:16 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <time.h>
# include <stdint.h>
# include <libft.h>
# include <MLX42/MLX42.h>
# define WIDTH 256
# define HEIGHT 256
# define BPP sizeof(int32_t)

typedef struct s_pix
{
	int	x;
	int	y;
}	t_pix;

typedef struct s_pt
{
	double	x;
	double	y;
}	t_pt;

typedef struct s_mlx
{
	void*		window;
	void*		context;
	int32_t		width;
	int32_t		height;
	double		delta_time;
}	t_mlx;

typedef struct s_data
{
	t_mlx	mlx;
}	t_data;

#endif
