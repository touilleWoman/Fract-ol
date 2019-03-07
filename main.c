/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:14:31 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/01 10:18:21 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		main(int argc, char **argv)
{
	t_context	ctx;


	if (argc != 2)
	{
		ft_putendl_fd("usage: ./fractol <fractal> (mandelbrot)", 2);
		return (0);
	}
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
	{
		ctx.choose = 1;
		window(&ctx);
	}

	if (ft_strcmp(argv[1], "julia") == 0)
	{
		ctx.choose = 2;
		window(&ctx);
	}
	return(0);
}



int				julia_calcu(int x, int y, t_context *pctx)
{
	t_complex	z;
	t_complex	c;
	int			iteration;
	double		temp;

	z.re = ((double)x * (pctx->limit.xmax - pctx->limit.xmin) / IMG_X + pctx->limit.xmin  + pctx->key.var_x);
	z.im = ((double)y * (pctx->limit.ymax - pctx->limit.ymin) / IMG_Y + pctx->limit.ymin + pctx->key.var_y);
	iteration = 0;
	c.re = 0.285;
	c.im = 0.01;
	while ((iteration < pctx->max_iteration) && (z.re * z.re + z.im * z.im < 4))
	{
		temp = z.re;
		z.re = z.re * z.re - z.im * z.im + c.re;
		z.im = 2 * z.im * temp + c.im;
        iteration++;
   	}
	return (iteration);
}