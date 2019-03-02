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
	char	*s1;

	if (argc != 2)
	{
		ft_putendl_fd("usage: ./fractol <fractal> (mandelbrot)", 2);
		return (0);
	}
	s1= "mandelbrot";
	if (ft_strcmp(argv[1], s1) == 0)
	{
		mandelbrot();
	}
	return(0);
}


