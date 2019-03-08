#include "fractol.h"

int				mandelbrot_calcu(t_complex p, t_context *pctx)
{
	t_complex	z;
	t_complex	c;
	int			iteration;
	double		temp;

	c.re = p.re;
	c.im = p.im;
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

int				julia_calcu(t_complex p, t_context *pctx)
{
	t_complex	z;
	t_complex	c;
	int			iteration;
	double		temp;


	z.re = p.re;
	z.im = p.im;
	iteration = 0;
	c.re = pctx->julia.re;
	c.im = pctx->julia.im;

	// c.re = 0.285;
	// c.im = 0.01;
	while ((iteration < pctx->max_iteration) && (z.re * z.re + z.im * z.im < 4))
	{
		temp = z.re;
		z.re = z.re * z.re - z.im * z.im + c.re;
		z.im = 2 * z.im * temp + c.im;
        iteration++;
   	}
	return (iteration);
}


int				burningship_calcu(t_complex p, t_context *pctx)
{
	t_complex	z;
	int			iteration;
	double		temp;

	z.re = p.re;
	z.im = p.im;
	iteration = 0;
	while ((iteration < pctx->max_iteration) && (z.re * z.re + z.im * z.im < 4))
	{
		temp = z.re;
		z.re = abs_double(z.re * z.re - z.im * z.im + z.re);
		z.im = abs_double(2 * z.im * temp) + z.im;
        iteration++;
   	}
	return (iteration);
}

double	abs_double(double a)
{
	return( a >= 0 ? a : -a);
}
