/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:19:05 by supersko          #+#    #+#             */
/*   Updated: 2024/11/24 23:38:14 by nidionis         ###   ########.fr       */
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
# define KEY_R 82
# define KEY_F 70
# define KEY_ESC 256

# define ZOOM_STEP 0.1
# define QUALITY_STEP 1
# define JULIA_COEF_R_STEP 0.01
# define JULIA_COEF_I_STEP 0.01
# define COLOR_STEP 1
# define WIDTH 2048
# define HEIGHT 1024
# define DEFAULT_ITER_MAX 30

typedef mlx_t			t_mlx;

typedef struct s_param	t_param;

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
	t_mlx			*mlx;
	mlx_image_t		*img;
	t_param			*param;
}	t_data;

typedef struct s_param
{
	int			iter_max;
	t_complex	julia_coef;
	int			color_coef;
	double		zoom;
	t_pix		offset;
	void		(*f_fract)(t_data *d, t_pix pix);
}	t_param;

void			set_complex(t_complex *z, double r, double i);
t_complex		complex_scale(t_complex z1, double scale);
t_complex		complex_sum(t_complex z1, t_complex z2);
int				complex_module(t_complex z);
unsigned int	complex_square_module(t_complex p);
void			my_scrollhook(double xdelta, double ydelta, void *data);
void			resize_win(int width, int height, void *data);
void			other_keyhooks(mlx_key_data_t keydata, void *data);
void			my_keyhook(mlx_key_data_t keydata, void *data);
void			set_pix(t_pix *pix, int x, int y);
t_complex		pixel_to_complex(t_data *data, t_pix p);
void			draw_pixel(t_data *data, t_pix pix, int color);
int				julia_iter(t_data *data, t_complex c);
void			prepare_next_frame(t_data *data);
double			ft_random(int n, int a, int b);
void			init_data(t_data *data, char **argv);
int				loops(t_data *data);
int				fractol(t_data *data, char **argv);
int				colors(t_data *data, int iter);
void			render_julia(t_data *data, t_pix pix);

#endif
