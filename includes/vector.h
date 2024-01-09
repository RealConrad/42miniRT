
#ifndef VECTOR_H
# define VECTOR_H

# include "mini_rt.h"

# ifndef EPSILON
#  define EPSILON 1e-6
# endif /*EPSILON*/


t_vector	vec_add(t_vector v1, t_vector v2);
t_vector	vec_subtract(t_vector v1, t_vector v2);
t_vector	vec_divide(t_vector v1, t_vector v2);
t_vector	vec_multiply(t_vector v1, t_vector v2);
t_vector	normalize_vector(t_vector v);
double		dot_product(t_vector v1, t_vector v2);
t_vector	to_vec(double n);
t_vector	vec_scale(t_vector v, double scale);

#endif /*VECTOR_H*/