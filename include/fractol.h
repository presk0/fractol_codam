/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:19:05 by supersko          #+#    #+#             */
/*   Updated: 2024/11/21 17:02:35 by nidionis         ###   ########.fr       */
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

# define ARROW_RIGHT 262
# define ARROW_LEFT 263
# define ARROW_DOWN 264
# define ARROW_UP 265
# define KEY_Q 81
# define KEY_A 65
# define KEY_W 87
# define KEY_S 83
# define KEY_E 69
# define KEY_D 68

# define ZOOM_STEP 0.1
# define WIDTH 1024
# define HEIGHT 512
# define DEFAULT_ITER_MAX 42
# define GREEN get_rgba(0, 255, 0, 255)
# define BLUE get_rgba(0, 0, 255, 255)
# define RED get_rgba(255, 0, 0, 255)
# define BPP sizeof(int32_t)

typedef mlx_t t_mlx;

typedef struct s_parami s_param;

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


typedef struct s_data
{
	t_mlx				*mlx;
	mlx_image_t			*img;
	struct s_param		*param;
}	t_data;

typedef struct s_param 
{
	int			iter_max;
	t_complex	julia_coef;
	double		zoom;
	t_pix		offset;
	void		(*f)(t_data *d, t_pix pix);
}	t_param;

#endif
