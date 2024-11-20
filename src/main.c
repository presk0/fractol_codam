/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2024/11/20 15:10:37 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

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

static void ft_hook(void* param)
{
	const t_mlx* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	init_pix(t_pix *pix, int x, int y)
{
	pix->x = x;
	pix->y = y;
}

void	orthonormal(t_data *data, t_pix *i)
{
	int	black;
	int	white;

	white = get_rgba(255, 255, 255, 255);
	black = get_rgba(0, 100, 0, 0);
	if (i->x == HEIGHT / 2 || i->y == WIDTH / 2)
		mlx_put_pixel(data->img, i->y, i->x, white);
	else
		mlx_put_pixel(data->img, i->y, i->x, black);
}

void	prepare_next_frame(t_data *data, void (*f)(t_data *data, t_pix *i))
{
	t_pix	i;
	
	init_pix(&i, 0, 0);
	while (i.x < WIDTH)
	{
		i.y = 0;
		while (i.y < HEIGHT)
		{
			f(data, &i);
			(i.y)++;
		}
		(i.x)++;
	}
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
			ft_errmsg("mlx_init crashed\n");
			return (-1);
		}
		data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
		if (!data.img || (mlx_image_to_window(data.mlx, data.img, 0, 0) < 0))
		{
			ft_errmsg("mlx_new_image crashed\n");
			mlx_terminate(data.mlx);
			return (-1);
		}
		//mlx_put_pixel(data.img, 0, 0, 0xAF0000FF);
		prepare_next_frame(&data, orthonormal);
		    // Draw the image at coordinate (0, 0).
		mlx_image_to_window(data.mlx, data.img, 0, 0);
		mlx_loop_hook(data.mlx, ft_hook, data.mlx);
		mlx_loop(data.mlx);
		mlx_terminate(data.mlx);
	}
	return (0);
}
