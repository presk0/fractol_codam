/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2024/11/21 13:50:38 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	set_complex(t_complex *z, double r, double i)
{
	z->r = r;
	z->i = i;
}

void	set_pix(t_pix *pix, int x, int y)
{
	pix->x = x;
	pix->y = y;
}

static void	help_msg(void)
{
	ft_errmsg("\n\
	Mandelbrot or Julia ? [M/j]\n\n\
	command help :\n\
		q - a : quality\n\
		w - s : color selection\n\
		e - d : modify real part of Julia's fractale\n\
		r - f : modify imaginary part of \"   \"\n\
		z     : Is it an available bonus ?\n");
}

int	complex_module(t_complex z)
{
	return (sqrt(z.r * z.r + z.i * z.i));
}

t_complex	complex_scale(t_complex z1, double scale)
{
	t_complex	scaled;

	set_complex(&scaled, 0, 0);
	if (scale)
	{
		scaled.r = z1.r / scale;
		scaled.i = z1.i / scale;
	}
	else
		ft_errmsg("[complex_scale] cannot divide by 0\n");
	return (scaled);
}

t_complex	complex_sum(t_complex z1, t_complex z2)
{
	t_complex	sum;

	sum.r = z1.r + z2.r;
	sum.i = z1.i + z2.i;
	return (sum);
}

static void ft_hook(void* param)
{
	const t_mlx* mlx = param;
	(void)mlx;

	//printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}
/*
void	orthonormal(t_data *data, t_pix *i, int color)
{
	int	black;

	black = get_rgba(0, 0, 0, 0);
	if (i->x == HEIGHT / 2 || i->y == WIDTH / 2)
		mlx_put_pixel(data->img, i->y, i->x, color);
	else
		mlx_put_pixel(data->img, i->y, i->x, black);
}
*/
unsigned	complex_square_module(t_complex p)
{
	return (p.r * p.r + p.i * p.i);
}

int	julia_iter(t_data *data, t_complex p)
{
	int			iter_max;
    int 		iter;
	double		tmp;
	t_complex	coef;

	iter = 0;
	coef = data->param.julia_coef;
	iter_max = data->param.iter_max;
    while (complex_square_module(p) <= 4 && iter < iter_max)
	{
        tmp = p.r * p.r - p.i * p.i + coef.r;
        p.i = 2 * p.r * p.i + coef.i;
        p.r = tmp;
        iter++;
    }
    return (iter);
}

t_complex	pixel_to_complex(t_data *data, t_pix p)
{
	t_complex	z;
	double		numerator;
	double		denominator;

	numerator = p.x - (double)WIDTH / 2.0;
	denominator = data->param.zoom * (double)WIDTH / 2.0;
    z.r = numerator / denominator + data->param.offset.x;
	numerator = p.y - (double)HEIGHT / 2.0;
	denominator = data->param.zoom * (double)HEIGHT / 2.0;
    z.i = numerator / denominator + data->param.offset.y;
	return (z);
}

int get_color(int iter) {
    if (iter == DEFAULT_ITER_MAX)
        return 0x000000;
    double t = (double)iter / DEFAULT_ITER_MAX;
    int r = (int)(9 * (1 - t) * t * t * t * 255);
    int g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
    int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
    return (r << 16) | (g << 8) | b;
}

void draw_pixel(t_data *data, t_pix pix, int color) {
    mlx_put_pixel(data->img, pix.y, pix.x, color);
}

void render_julia(t_data *data, t_pix pix) {
	t_complex c = pixel_to_complex(data, pix);
	int iter = julia_iter(data, c);
	int color = get_color(iter);
	draw_pixel(data, pix, color);
}

void	julia(t_data *data, t_pix *i, int color)
{
	int			count;
	int			iter_max;
	int			module;
	t_complex	i_nb;
	(void)color;

	iter_max = data->param.iter_max;
	count = 0;
	i_nb = pixel_to_complex(data, *i);
	module = julia_iter(data, i_nb);
	mlx_put_pixel(data->img, i->y, i->x, module);
}

void	prepare_next_frame(t_data *data, void (*f)(t_data *data, t_pix i))
{
	t_pix	i;
	
	set_pix(&i, 0, 0);
	while (i.x < WIDTH)
	{
		i.y = 0;
		while (i.y < HEIGHT)
		{
			f(data, i);
			(i.y)++;
		}
		(i.x)++;
	}
}

void	init_data(t_data *data)
{
	set_complex(&data->param.julia_coef, -0.7, 0.27015);
	data->param.iter_max = DEFAULT_ITER_MAX;
	data->param.zoom = 1;
	data->param.offset.x = 0;
	data->param.offset.y = 0;
}

void my_scrollhook(double xdelta, double ydelta, void *data)
{
	t_param	*p;
	t_data	*d;

	d = data;
	(void)xdelta;
	p = &(((t_data *)data)->param);
	if (ydelta > 0)
		p->zoom += ZOOM_STEP;
	else if (ydelta < 0)
		p->zoom -= ZOOM_STEP;
	prepare_next_frame(data, render_julia);
	mlx_image_to_window(d->mlx, d->img, 0, 0);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		i;
	(void)argc;
	(void)i;
	(void)argv;
	(void)data;

	if (argc <= 1 || argc > 2)
		help_msg();
	else
	{
		data.mlx = mlx_init(WIDTH, HEIGHT, "fractol", true);
		if (!data.mlx)
		{
			ft_errmsg("mlx_init crashed\n");
			return (-1);
		}
		init_data(&data);
		data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
		if (!data.img || (mlx_image_to_window(data.mlx, data.img, 0, 0) < 0))
		{
			ft_errmsg("mlx_new_image crashed\n");
			mlx_terminate(data.mlx);
			return (-1);
		}
		prepare_next_frame(&data, render_julia);
		mlx_image_to_window(data.mlx, data.img, 0, 0);
		mlx_loop_hook(data.mlx, ft_hook, data.mlx);
		mlx_scroll_hook(data.mlx, &my_scrollhook, &data);
		mlx_loop(data.mlx);
		mlx_terminate(data.mlx);
	}
	return (0);
}
