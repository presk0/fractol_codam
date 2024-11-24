/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/11/24 23:01:17 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int	julia_iter(t_data *data, t_complex c)
{
	int			iter_max;
	int			iter;
	double		tmp;
	t_complex	z;

	iter = 0;
	z = data->param->julia_coef;
	iter_max = data->param->iter_max;
	while (complex_square_module(z) < 4 && iter < iter_max)
	{
		tmp = z.r * z.r - z.i * z.i + c.r;
		z.i = 2 * z.r * z.i + c.i;
		z.r = tmp;
		iter++;
	}
	return (iter);
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
