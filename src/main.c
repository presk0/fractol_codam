/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2024/11/18 22:17:25 by nidionis         ###   ########.fr       */
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

// Print the window width and height.
static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	t_data	data;
	(void)data;

	if (argc <= 1 || argc > 2)
		help_msg();
	else
	{
		// MLX allows you to define its core behaviour before startup.
		mlx_set_setting(MLX_MAXIMIZED, true);
		mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "fractol", true);
		if (!mlx)
		{
			ft_errmsg("mlx_init crashed\n");
			return (-1);
		}

		/* Do stuff */

		// Create and display the image.
		mlx_image_t* img = mlx_new_image(mlx, 256, 256);
		if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		{
			ft_errmsg("mlx_new_image crashed\n");
			return (-1);
		}

		// Even after the image is being displayed, we can still modify the buffer.
		mlx_put_pixel(img, 0, 0, 0xFF0000FF);

		// Register a hook and pass mlx as an optional param.
		// NOTE: Do this before calling mlx_loop!
		mlx_loop_hook(mlx, ft_hook, mlx);
		mlx_loop(mlx);
		mlx_terminate(mlx);
	}
	return (0);
}
