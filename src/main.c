/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2024/11/24 23:24:53 by nidionis         ###   ########.fr       */
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
		");
}

void	init_data(t_data *data, char **argv)
{
	data->param = malloc(sizeof(t_param));
	set_complex(&data->param->julia_coef, -0.8, 0.156);
	if (argv[1][0] == 'm' || argv[1][0] == 'M' )
		set_complex(&data->param->julia_coef, 0, 0);
	data->param->iter_max = DEFAULT_ITER_MAX;
	data->param->zoom = 1;
	data->param->color_coef = 40;
	data->param->offset.x = 0;
	data->param->offset.y = 0;
	data->param->f_fract = &render_julia;
	mlx_set_window_limit(data->mlx, 1, 1, WIDTH, HEIGHT);
}

int	loops(t_data *data)
{
	prepare_next_frame(data);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_scroll_hook(data->mlx, &my_scrollhook, data);
	mlx_resize_hook(data->mlx, &resize_win, data);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	if (data->mlx)
		mlx_loop(data->mlx);
	return (0);
}

int	fractol(t_data *data, char **argv)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "fractol", true);
	if (!data->mlx)
	{
		ft_errmsg((char *)mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	init_data(data, argv);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
	{
		mlx_close_window(data->mlx);
		ft_errmsg((char *)mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (loops(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	mlx_terminate(data->mlx);
	free(data->param);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc <= 1 || argc > 2)
		help_msg();
	else if (fractol(&data, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (0);
}
