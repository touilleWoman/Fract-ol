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
		ft_putendl_fd("usage: ./fractol <fractal> (mandelbrot;julia)", 2);
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
	if (ft_strcmp(argv[1], "burningship") == 0)
	{
		ctx.choose = 3;
		window(&ctx);
	}
	else
		ft_putendl_fd("fractal name wrong", 2);
	return(0);
}
