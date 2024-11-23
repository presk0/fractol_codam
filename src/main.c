/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2024/11/23 17:58:42 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int	loops(t_data *data);

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
	coef = data->param->julia_coef;
	iter_max = data->param->iter_max;
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

	numerator = (double)p.x - (double)data->img->width / 2.0;
	denominator = data->param->zoom * (double)data->img->width / 2.0;
	if (denominator)
		z.r = numerator / denominator + data->param->offset.x;
	numerator = (double)p.y - (double)data->img->height / 2.0;
	denominator = data->param->zoom * (double)data->img->height / 2.0;
	if (denominator)
		z.i = numerator / denominator + data->param->offset.y;
	return (z);
}

void draw_pixel(t_data *data, t_pix pix, int color) {
    if (!data || !data->img || !data->mlx) {
        fprintf(stderr, "Error: Invalid data or uninitialized structures\n");
        return;
    }

    if (pix.x >= 0 && pix.x < (int)data->mlx->width &&
        pix.y >= 0 && pix.y < (int)data->mlx->height) {
        mlx_put_pixel(data->img, pix.x, pix.y, color);
    } else {
        fprintf(stderr, "Warning: Out-of-bounds pixel (%d, %d)\n", pix.x, pix.y);
    }
}

/*
void draw_pixel(t_data *data, t_pix pix, int color) {
	if (pix.y < (int)data->mlx->height && pix.x < (int)data->mlx->width)
		mlx_put_pixel(data->img, pix.x, pix.y, color);
}
*/

int julia_multicolor1(int iter) {
    if (iter == DEFAULT_ITER_MAX)
        return 0x000000;
    double t = (double)iter / DEFAULT_ITER_MAX;
    int r = (int)(9 * (1 - t) * t * t * t * 255);
    int g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
    int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
    return (r << 16) | (g << 8) | b;
}

int julia_multicolor2(int iter) {
    if (iter == DEFAULT_ITER_MAX)
        return 0x000000;
    double t = (double)iter / DEFAULT_ITER_MAX;
    int r = (int)(15 * (1 - t) * t * t * t * 255);
    int g = (int)(1 * (1 - t) * (1 - t) * t * t * 255);
    int b = (int)(5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
    return (r << 16) | (g << 8) | b;
}

int julia_multicolor3(int iter) {
    if (iter == DEFAULT_ITER_MAX)
        return 0x000000;
    double t = (double)iter / DEFAULT_ITER_MAX;
    int r = (int)(t);
    int g = (int)(0 * (1 - t) * (1 - t) * t * t * 255);
    int b = (int)(0 * (1 - t) * (1 - t) * (1 - t) * t * 255);
    return (r << 16) | (g << 8) | b;
}

void render_julia(t_data *data, t_pix pix) {
	t_param *p;

	p = data->param;
	t_complex c = pixel_to_complex(data, pix);
	int iter = julia_iter(data, c);
	int color = p->f_color(iter);
	draw_pixel(data, pix, color);
}

int	bonus_iter(t_data *data, t_complex c)
{
	(void)data;
	(void)c;
return 0;	
}

void render_bonus(t_data *data, t_pix pix) {
	t_param *p;

	p = data->param;
	t_complex c = pixel_to_complex(data, pix);
	int iter = bonus_iter(data, c);
	int color = p->f_color(iter);
	draw_pixel(data, pix, color);
}

void	prepare_next_frame(t_data *data)
{
	t_pix	i;
	void	(*f)(t_data *, t_pix i);
	
	f = data->param->f_fract;
	set_pix(&i, 0, 0);
	while (i.x < (int)data->mlx->width)
	{
		i.y = 0;
		while (i.y < (int)data->mlx->height)
		{
			f(data, i);
			(i.y)++;
		}
		(i.x)++;
	}
}

void	init_data(t_data *data)
{
	data->param = malloc(sizeof(t_param));
	set_complex(&data->param->julia_coef, 0, 0);
	data->param->iter_max = DEFAULT_ITER_MAX;
	data->param->zoom = 1;
	data->param->offset.x = 0;
	data->param->offset.y = 0;
	data->param->f_color = julia_multicolor3;
	mlx_set_window_limit(data->mlx, 1, 1, WIDTH, HEIGHT);
}

void my_scrollhook(double xdelta, double ydelta, void *data)
{
	t_param	*p;
	t_data	*d;

	d = data;
	(void)xdelta;
	p = ((t_data *)data)->param;
	if (ydelta > 0)
	{
		if ((p->zoom + ZOOM_STEP) * p->zoom > 0)
			p->zoom += ZOOM_STEP;
	}
	else if (ydelta < 0)
	{
		if ((p->zoom - ZOOM_STEP) * p->zoom > 0)
			p->zoom -= ZOOM_STEP;
	}
	loops(data);
}

void resize_win(int width, int height, void *data)
{
	(void)width;
	(void)height;
	t_data	*d;

	d = (t_data *)data;
	printf("mlx->width= %i\n", d->mlx->width);
	printf("mlx->height= %i\n", d->img->height);
	printf("img->width= %i\n", d->mlx->width);
	printf("img->height= %i\n", d->mlx->height);
	//d->img->width = width;
	//d->img->height = height;
	loops(data);
}

void	my_keyhook(mlx_key_data_t keydata, void *data)
{
	t_data	*d;

	d = (t_data *)data;
	if (keydata.key == KEY_ESC)
		mlx_terminate(((t_data *)data)->mlx);
	if (keydata.key == KEY_Q && d->param->iter_max + QUALITY_STEP > 0)
		d->param->iter_max += QUALITY_STEP;
	if (keydata.key == KEY_A && d->param->iter_max + QUALITY_STEP > 0)
		d->param->iter_max -= QUALITY_STEP;
	if (keydata.key == KEY_E)
	{
		d->param->julia_coef.r += JULIA_COEF_R_STEP;
		if (complex_module(d->param->julia_coef) > 2)
			d->param->julia_coef.r -= JULIA_COEF_R_STEP;
	}
	if (keydata.key == KEY_D)
	{
		d->param->julia_coef.r -= JULIA_COEF_R_STEP;
		if (complex_module(d->param->julia_coef) > 2)
			d->param->julia_coef.r += JULIA_COEF_R_STEP;
	}
	if (keydata.key == KEY_D)
	{
		d->param->julia_coef.r -= JULIA_COEF_R_STEP;
		if (complex_module(d->param->julia_coef) > 2)
			d->param->julia_coef.r += JULIA_COEF_R_STEP;
	}
	loops(data);
}

int	loops(t_data *data)
{
	prepare_next_frame(data);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	mlx_scroll_hook(data->mlx, &my_scrollhook, data);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_resize_hook(data->mlx, &resize_win, data);
	mlx_loop(data->mlx);
	return (0);
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
		//mlx_set_setting(MLX_MAXIMIZED, true);
		data.mlx = mlx_init(WIDTH, HEIGHT, "fractol", true);
		if (!data.mlx)
		{
			ft_errmsg((char *)mlx_strerror(mlx_errno));
			return (EXIT_FAILURE);
		}
		init_data(&data);
		data.param->f_fract = &render_julia;
		data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
		if (!data.img || (mlx_image_to_window(data.mlx, data.img, 0, 0) < 0))
		{
			mlx_close_window(data.mlx);
			ft_errmsg((char *)mlx_strerror(mlx_errno));
			return(EXIT_FAILURE);
		}
		if (loops(&data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	mlx_terminate(data.mlx);
	free(data.param);
	return (0);
}
