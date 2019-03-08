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
		ft_putendl_fd("usage: ./fractol <fractal>", 2);
		ft_putendl_fd("available fractals: mandelbrot julia burningship julia2 tricorn", 2);
		return (0);
	}
	if (choose_fractal(argv[1], &ctx) == 1)
		ft_putendl_fd("fractal name wrong", 2);
	return (0);
}

int		choose_fractal(char *str, t_context *pctx)
{
	if (ft_strcmp(str, "mandelbrot") == 0)
	{
		pctx->choose = 1;
		window(pctx);
		return (0);
	}
	if (ft_strcmp(str, "julia") == 0)
	{
		pctx->choose = 2;
		window(pctx);
		return (0);
	}
	if (ft_strcmp(str, "burningship") == 0)
	{
		pctx->choose = 3;
		window(pctx);
		return (0);
	}
	if (ft_strcmp(str, "julia2") == 0)
	{
		pctx->choose = 4;
		window(pctx);
		return (0);
	}
	if (ft_strcmp(str, "tricorn") == 0)
	{
		pctx->choose = 5;
		window(pctx);
		return (0);
	}
	return (1);
}
