/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/11/24 22:54:51 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	set_complex(t_complex *z, double r, double i)
{
	z->r = r;
	z->i = i;
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

int	complex_module(t_complex z)
{
	return (sqrt(z.r * z.r + z.i * z.i));
}

unsigned int	complex_square_module(t_complex p)
{
	return (p.r * p.r + p.i * p.i);
}
