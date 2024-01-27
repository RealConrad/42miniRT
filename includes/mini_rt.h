
#ifndef MINI_RT_H
# define MINI_RT_H

/* -------------------------------------------------------------------------- */
/*                                  Libraries                                 */
/* -------------------------------------------------------------------------- */

# include "../libraries/libft/libft.h"
# include "../libraries/mlx/include/MLX42/MLX42.h"

/* -------------------------------------------------------------------------- */
/*                                  Includes                                  */
/* -------------------------------------------------------------------------- */

# include "parser.h"
# include "structs.h"
# include "renderer.h"
# include "testing.h"
# include "vector.h"
# include "lighting.h"

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include <pthread.h>
# include <float.h>

/* -------------------------------------------------------------------------- */
/*                                   Defines                                  */
/* -------------------------------------------------------------------------- */

# ifndef WIDTH
#  define WIDTH 1920
# endif

# ifndef HEIGHT
#  define HEIGHT 1080
# endif

# ifndef RPP
#  define RPP 1
# endif


/* -------------------------------------------------------------------------- */
/*                                  Functions                                 */
/* -------------------------------------------------------------------------- */

/* ---------------------------------- Utils --------------------------------- */

void		escape(keys_t keycode, void *param);
void		display_render_progress(int percent);
double		random_double(void);

t_colour	colour_multiply(t_colour c1, t_colour c2);
t_colour	colour_scalar_multiply(t_colour c, double scalar);
t_colour	get_sky_background(t_ray *ray);
t_colour	normalize_colour(t_colour colour);
void		clamp_normalized_colour(t_colour *colour);
uint32_t	get_rgb(t_colour colour);

void		free_objects(t_object *objects);

double		ft_dabs(double nb);

#endif /*MINI_RT_H*/
