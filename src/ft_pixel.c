/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/11/24 22:56:58 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	set_pix(t_pix *pix, int x, int y)
{
	pix->x = x;
	pix->y = y;
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

void	draw_pixel(t_data *data, t_pix pix, int color)
{
	if (!data || !data->img || !data->mlx)
		return ;
	if (pix.x >= 0 && pix.x < (int)data->mlx->width
		&& pix.y >= 0 && pix.y < (int)data->mlx->height)
		mlx_put_pixel(data->img, pix.x, pix.y, color);
}
