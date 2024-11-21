/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:19:05 by supersko          #+#    #+#             */
/*   Updated: 2024/11/20 22:04:01 by nidionis         ###   ########.fr       */
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
# define DEFAULT_ITER_MAX 256
# define GREEN get_rgba(0, 255, 0, 255)
# define BLUE get_rgba(0, 0, 255, 255)
# define RED get_rgba(255, 0, 0, 255)
# define BPP sizeof(int32_t)

/*
typedef struct mlx
{
	void*		window;
	void*		context;
	int32_t		width;
	int32_t		height;
	double		delta_time;
}	mlx_t;
*/

typedef struct s_pix
{
	int	x;
	int	y;
}	t_pix;

typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

typedef mlx_t t_mlx;

typedef struct s_param 
{
	int			iter_max;
	t_complex	julia_coef;
	int			zoom;
	t_pix		offset;
}	t_param;

typedef struct s_data
{
	t_mlx		*mlx;
	mlx_image_t	*img;
	t_param		param;
}	t_data;

#endif
