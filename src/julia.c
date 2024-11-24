/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/11/24 23:04:44 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

double	ft_random(int n, int a, int b)
{
	return ((double)((n * a + b) % 100) / 100.0);
}

/*
int colors(t_data *data, int iter)
{
    double	t;
	int		global;
	int		r;
	int		g;
	int		b;

	global = data->param->color_coef;
    if (iter == DEFAULT_ITER_MAX)
        return 0x000000;
    t = (double)iter / DEFAULT_ITER_MAX;
    r = (int)(ft_random(global, 1000, 4321) * t * 255);
    g = (int)(ft_random(global, 123, 987) * t * 255);
    b = (int)(ft_random(global, 3333, 2364) * t * 255);
    return (r << 24 | g << 16 | b << 8 | (r % 127 + 127));
}
*/

int	colors(t_data *data, int iter)
{
	double	t;
	int		global;
	int		r;
	int		g;
	int		b;

	global = data->param->color_coef;
	if (iter == DEFAULT_ITER_MAX)
		return (0);
	t = (double)iter / DEFAULT_ITER_MAX;
	r = (int)(ft_random(global, 1000, 4321) * (t - 1) * (t - 1) * 255);
	g = (int)(ft_random(global, 123, 987) * (1 - t) * t * 255);
	b = (int)(ft_random(global, 3333, 2364) * t * t * 255);
	return (r << 24 | g << 16 | b << 8 | (r % 127 + 127));
}

void	render_julia(t_data *data, t_pix pix)
{
	t_param		*p;
	int			iter;
	int			color;
	t_complex	c;

	p = data->param;
	c = pixel_to_complex(data, pix);
	iter = julia_iter(data, c);
	color = colors(data, iter);
	draw_pixel(data, pix, color);
}
