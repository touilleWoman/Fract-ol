/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 11:00:33 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/02 11:00:41 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


void				put_pixel_with_cl(double x, double y, t_context *pctx, int iteration)
{
	t_color		cl;
	int			val_cl;
	int			i;

	i = y * WIN_X + x;
	val_cl = iteration * 360 / pctx->max_iteration + pctx->variation_cl;
	cl = ft_color_val_calculate(val_cl);
	pctx->data_a[i * 4 + 2] = cl.r;
	pctx->data_a[i * 4 + 1] = cl.g;
	pctx->data_a[i * 4] = cl.b;
}

int					window(t_context *pctx)
{
	int		bpp;
	int		endian;

	reset(pctx);
	pctx->mlx_ptr = mlx_init();
	if (pctx->mlx_ptr == NULL)
		return (-1);
	pctx->win_ptr = mlx_new_window(pctx->mlx_ptr, WIN_X, WIN_Y, WIN_NAME);
	if (pctx->win_ptr == NULL)
		return (-1);
	pctx->img_ptr = mlx_new_image(pctx->mlx_ptr, WIN_X, WIN_Y);
	pctx->data_a = mlx_get_data_addr(pctx->img_ptr, &bpp,
		 &pctx->size_l, &endian);

	thread(pctx);
	mlx_hook(pctx->win_ptr, 2, 0, key_press, pctx);
	mlx_hook(pctx->win_ptr, 17, 0, closewindow, pctx);
	mlx_hook(pctx->win_ptr, 4, 0, mouse_press, pctx);
	mlx_loop(pctx->mlx_ptr);
	return (0);

}

void			*start_routine(void *raw_params) 
{
	t_params *params = (t_params*)raw_params;
	sub_browse_pixel(params->pctx, params->xmin, params->xmax);
	return (NULL);
}


void			thread(t_context *pctx)
{
	int				curr_thread;
	int				slice_x;
	pthread_t		threads[4];
	t_params		params[4];

	curr_thread = 0;
	slice_x = WIN_X / 4;
	while (curr_thread < 4)
	{
		params[curr_thread].pctx = pctx;
		params[curr_thread].xmin = curr_thread * slice_x;
		params[curr_thread].xmax = (curr_thread + 1) * slice_x;
		pthread_create(&threads[curr_thread], NULL, start_routine, &params[curr_thread]);
		curr_thread++;
	}
	curr_thread = 0;
	while (curr_thread < 4)
	{
		pthread_join(threads[curr_thread], NULL);
		curr_thread++;
	}
	mlx_put_image_to_window(pctx->mlx_ptr,pctx->win_ptr, pctx->img_ptr, 0, 0);

}

void			sub_browse_pixel(t_context *pctx, int xmin, int xmax)
{
	int			iteration;
	int			y;
	int			x;
	t_complex	p;

	y = 0;
	iteration = 0;
	x = xmin;

	while (y < WIN_Y)
	{
		while (x < xmax)
		{
			p = normalize_pixel(x, y, pctx);	
			if (pctx->choose == 1)
			{
				iteration = mandelbrot_calcu(p, pctx);
			}
			if (pctx->choose == 2)
			{
				iteration = julia_calcu(p, pctx);
			}
			if (iteration != pctx->max_iteration)
			{
				put_pixel_with_cl(x, y, pctx, iteration);
			}
			x++;
		}
		x = xmin;
		y++;
	}
}

t_complex		normalize_pixel(int x, int y, t_context *pctx)
{
	t_complex	p;

	p.re = (x * (pctx->limit.x2 - pctx->limit.x1) / WIN_X + pctx->limit.x1);
	p.im = (y * (pctx->limit.y2 - pctx->limit.y1) / WIN_Y + pctx->limit.y1);
	return (p);
}



