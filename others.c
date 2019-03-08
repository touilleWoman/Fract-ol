/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 16:21:13 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/08 16:21:19 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				others2(t_complex n, t_context *pctx)
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
		z.re = (z.re * z.re - z.im * z.im + c.re) / 2;
		z.im = 2 * z.im * temp + c.im;
		iteration++;
	}
	return (iteration);
}

int				others3(t_complex n, t_context *pctx)
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
		z.im = (2 * z.im * temp + c.im) * (1 / z.re);
		iteration++;
	}
	return (iteration);
}

int				others(t_complex n, t_context *pctx)
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
		z.im = (2 * z.im * temp + c.im) * (z.re);
		iteration++;
	}
	return (iteration);
}

int				others4(t_complex n, t_context *pctx)
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
		z.re = 0.5 / (z.re * z.re - z.im * z.im + c.re);
		z.im = 2 * z.im * temp + c.im;
		iteration++;
	}
	return (iteration);
}
