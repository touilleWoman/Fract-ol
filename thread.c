/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 16:39:33 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/08 16:39:35 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				*start_routine(void *raw_params)
{
	t_params *params;

	params = (t_params*)raw_params;
	sub_browse_pixel(params->pctx, params->xmin, params->xmax);
	return (NULL);
}

void				thread(t_context *pctx)
{
	int				i;
	int				slice_x;
	pthread_t		threads[4];
	t_params		params[4];

	i = 0;
	slice_x = WIN_X / 4;
	while (i < 4)
	{
		params[i].pctx = pctx;
		params[i].xmin = i * slice_x;
		params[i].xmax = (i + 1) * slice_x;
		pthread_create(&threads[i], NULL, start_routine, &params[i]);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	mlx_put_image_to_window(pctx->mlx_ptr, pctx->win_ptr, pctx->img_ptr, 0, 0);
}

void				sub_browse_pixel(t_context *pctx, int xmin, int xmax)
{
	int			i;
	int			y;
	int			x;
	t_complex	n;

	y = 0;
	i = 0;
	x = xmin;
	while (y < WIN_Y)
	{
		while (x < xmax)
		{
			n = normalize_pixel(x, y, pctx);
			i = switch_fractal(n, pctx);
			if (i != pctx->max_iteration)
				put_pixel_with_cl(x, y, pctx, i);
			x++;
		}
		x = xmin;
		y++;
	}
}

int					switch_fractal(t_complex n, t_context *pctx)
{
	int		i;

	pctx->choose == 1 ? i = mandelbrot_calcu(n, pctx) : pctx->choose;
	pctx->choose == 2 ? i = julia_calcu(n, pctx) : pctx->choose;
	pctx->choose == 3 ? i = burningship_calcu(n, pctx) : pctx->choose;
	pctx->choose == 5 ? i = julia2(n, pctx) : pctx->choose;
	pctx->choose == 4 ? i = tricorn(n, pctx) : pctx->choose;
	pctx->choose == 6 ? i = others(n, pctx) : pctx->choose;
	pctx->choose == 7 ? i = others2(n, pctx) : pctx->choose;
	pctx->choose == 8 ? i = others3(n, pctx) : pctx->choose;
	pctx->choose == 9 ? i = others4(n, pctx) : pctx->choose;
	return (i);
}
