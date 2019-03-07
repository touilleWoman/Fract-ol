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
	val_cl = iteration * 360 / pctx->max_iteration + pctx->key.variation_cl;
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

	browse_pixel(pctx);
	mlx_hook(pctx->win_ptr, 2, 0, key_press, pctx);
	mlx_hook(pctx->win_ptr, 17, 0, closewindow, pctx);
	mlx_hook(pctx->win_ptr, 4, 0, mouse_press, pctx);
	mlx_loop(pctx->mlx_ptr);
	return (0);

}




typedef struct {
	t_context *pctx;
	int xmin;
	int xmax;
	int ymin;
	int ymax;
} t_params;

void			*start_routine(void *raw_params) 
{
	t_params *params = (t_params*)raw_params;
	sub_browse_pixel(params->pctx, params->xmin, params->xmax, params->ymin, params->ymax);
	return NULL;
}

void			browse_pixel(t_context *pctx)
{
	int nb_threads;
	int curr_thread;
	int slice_x;
	pthread_t threads[4];
	t_params params[4];

	nb_threads = 4;
	curr_thread = 0;
	slice_x = WIN_X / nb_threads;
	while (curr_thread < 4)
	{
		params[curr_thread].pctx=pctx;
		params[curr_thread].xmin=curr_thread * slice_x;
		params[curr_thread].xmax=(curr_thread + 1) * slice_x;
		params[curr_thread].ymin=0;
		params[curr_thread].ymax=WIN_Y;
		pthread_create(&threads[curr_thread], NULL, start_routine, &params[curr_thread]);
		curr_thread++;
	}

	curr_thread = 0;
	while (curr_thread < nb_threads)
	{
		pthread_join(threads[curr_thread], NULL);
		curr_thread++;
	}
	mlx_put_image_to_window(pctx->mlx_ptr,pctx->win_ptr, pctx->img_ptr, 0, 0);

}

void			sub_browse_pixel(t_context *pctx, int xmin, int xmax, int ymin, int ymax)
{
	int			iteration;


	iteration = 0;
	int		x = xmin;
	int		y = ymin;

	while (y < ymax)
	{
		while (x < xmax)
		{
			if (pctx->choose == 1)
			{
				iteration = mandelbrot_calcu(x, y, pctx);
			}
			if (pctx->choose == 2)
			{
				iteration = julia_calcu(x, y, pctx);
			}
			if (iteration != pctx->max_iteration)
			{
				put_pixel_with_cl(x, y, pctx, iteration);
			}
			x++;
		}
		x = 0;
		y++;
	}
}












