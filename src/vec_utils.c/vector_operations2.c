
#include "mini_rt.h"

/**
 * @brief Takes 2 vectors and returns a single scalar value. This works
 * by multiplying the 2 vectors elements.
 * @param v1 
 * @param v2 
 * @return 
 */
double	dot_product(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

/**
 * @brief Converts the given number to a vector.
 *
 * The X,Y,Z elements of the vector will all be set to `n`.
 * @param n The number to be converted to a vector.
 * @return A newly created vector from `n`.
 */
t_vector	to_vec(double n)
{
	return ((t_vector){n, n, n});
}

t_vector	vec_scale(t_vector v, double scale)
{
	t_vector	result;

	result.x = v.x  * scale;
	result.y = v.y  * scale;
	result.z = v.z  * scale;
	return (result);
}
