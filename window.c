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

int					create_window(t_context *pctx)
{
	pctx->mlx_ptr = mlx_init();
	if (pctx->mlx_ptr == NULL)
	{
		ft_putendl_fd("mlx_init error", 2);
		return (-1);
	}
	pctx->win_ptr = mlx_new_window(pctx->mlx_ptr, WIN_X, WIN_Y, WIN_NAME);
	if (pctx->win_ptr == NULL)
	{
		ft_putendl_fd("mlx_new_window error", 2);
		return (-1);
	}
	pctx->img_ptr = mlx_new_image(pctx->mlx_ptr, WIN_X, WIN_Y);
	if (pctx->img_ptr == NULL)
	{
		ft_putendl_fd("mlx_new_image error", 2);
		return (-1);
	}
	return (0);
}

int					window(t_context *pctx)
{
	int		bpp;
	int		e;

	reset(pctx);
	if (create_window(pctx) == -1)
		return (-1);
	pctx->data_a = mlx_get_data_addr(pctx->img_ptr, &bpp, &pctx->size_l, &e);
	thread(pctx);
	mlx_hook(pctx->win_ptr, 2, 0, key_press, pctx);
	mlx_hook(pctx->win_ptr, 17, 0, closewindow, pctx);
	mlx_hook(pctx->win_ptr, 4, 0, mouse_press, pctx);
	mlx_hook(pctx->win_ptr, 6, 0, mouse_move, pctx);
	mlx_loop(pctx->mlx_ptr);
	return (0);
}

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
			pctx->choose == 1 ? i = mandelbrot_calcu(n, pctx) : pctx->choose;
			pctx->choose == 2 ? i = julia_calcu(n, pctx) : pctx->choose;
			pctx->choose == 3 ? i = burningship_calcu(n, pctx) : pctx->choose;
			pctx->choose == 4 ? i = julia2(n, pctx) : pctx->choose;
			pctx->choose == 5 ? i = tricorn(n, pctx) : pctx->choose;
			if (i != pctx->max_iteration)
				put_pixel_with_cl(x, y, pctx, i);
			x++;
		}
		x = xmin;
		y++;
	}
}
