/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 12:00:02 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/08 12:00:06 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				mandelbrot_calcu(t_complex n, t_context *pctx)
{
	t_complex	z;
	t_complex	c;
	int			iteration;
	double		temp;

	c.re = n.re;
	c.im = n.im;
	iteration = 0;
	z.re = 0;
	z.im = 0;
	while ((iteration < pctx->max_iteration) && (z.re * z.re + z.im * z.im < 4))
	{
		temp = z.re;
		z.re = z.re * z.re - z.im * z.im + c.re;
		z.im = 2 * z.im * temp + c.im;
		iteration++;
	}
	return (iteration);
}

int				julia_calcu(t_complex n, t_context *pctx)
{
	t_complex	z;
	t_complex	c;
	int			iteration;
	double		temp;

	z.re = n.re;
	z.im = n.im;
	iteration = 0;
	c.re = pctx->julia.re;
	c.im = pctx->julia.im;
	while ((iteration < pctx->max_iteration) && (z.re * z.re + z.im * z.im < 4))
	{
		temp = z.re;
		z.re = z.re * z.re - z.im * z.im + c.re;
		z.im = 2 * z.im * temp + c.im;
		iteration++;
	}
	return (iteration);
}


int				burningship_calcu(t_complex n, t_context *pctx)
{
		t_complex	z;
		t_complex	c;
		int			iteration;
		double		temp;

		c.re = n.re;
		c.im = n.im;
		iteration = 0;
		z.re = 0;
		z.im = 0;
		while ((iteration < pctx->max_iteration) && (z.re * z.re + z.im * z.im < 4))
		{
			temp = z.re;
			z.re = abs_double(z.re * z.re - z.im * z.im + c.re);
			z.im = abs_double(2 * z.im * temp + c.im);
			iteration++;
		}
		return(iteration);
}

double			abs_double(double a)
{
	return( a >= 0 ? a : -a);
}
