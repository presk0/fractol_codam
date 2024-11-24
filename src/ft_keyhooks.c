/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/11/24 23:34:39 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	my_scrollhook(double xdelta, double ydelta, void *data)
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

void	resize_win(int width, int height, void *data)
{
	(void)width;
	(void)height;
	loops(data);
}

void	other_keyhooks(mlx_key_data_t keydata, void *data)
{
	t_data	*d;

	d = (t_data *)data;
	if (keydata.key == KEY_D)
	{
		d->param->julia_coef.r -= JULIA_COEF_R_STEP;
		if (complex_module(d->param->julia_coef) < 2)
			d->param->julia_coef.r -= JULIA_COEF_R_STEP;
	}
	if (keydata.key == KEY_R)
	{
		d->param->julia_coef.i += JULIA_COEF_I_STEP;
		if (complex_module(d->param->julia_coef) < 2)
			d->param->julia_coef.i += JULIA_COEF_I_STEP;
	}
	if (keydata.key == KEY_F)
	{
		d->param->julia_coef.i -= JULIA_COEF_I_STEP;
		if (complex_module(d->param->julia_coef) < 2)
			d->param->julia_coef.i -= JULIA_COEF_I_STEP;
	}
	if (keydata.key == KEY_W)
		d->param->color_coef += COLOR_STEP;
}

int	my_exit(t_data *data)
{
	mlx_terminate(data->mlx);
	free(data->param);
	exit(0);
	return (1);
}

void	my_keyhook(mlx_key_data_t keydata, void *data)
{
	t_data	*d;

	if (keydata.action != MLX_PRESS)
		return ;
	d = (t_data *)data;
	if (keydata.key == KEY_ESC && my_exit(data))
		return ;
	if (keydata.key == KEY_Q && d->param->iter_max + QUALITY_STEP > 0)
		d->param->iter_max += QUALITY_STEP;
	if (keydata.key == KEY_A && d->param->iter_max - QUALITY_STEP > 0)
		d->param->iter_max -= QUALITY_STEP;
	if (keydata.key == KEY_E)
	{
		d->param->julia_coef.r += JULIA_COEF_R_STEP;
		if (complex_module(d->param->julia_coef) < 2)
			d->param->julia_coef.r += JULIA_COEF_R_STEP;
	}
	if (keydata.key == KEY_S)
		d->param->color_coef -= COLOR_STEP;
	other_keyhooks(keydata, data);
	loops(data);
}
