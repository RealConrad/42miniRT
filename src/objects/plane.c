/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:45:04 by eweiberl          #+#    #+#             */
/*   Updated: 2024/01/30 16:45:07 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @brief Checks if a ray hits a specific plane object
 * @param plane the plane object to check
 * @param ray the ray to check
 * @return sets the distance to -1 in case of no hit
 */
void	hit_plane(t_plane *plane, t_ray *ray)
{
	double	d_pro;
	double	distance;

	d_pro = dot_product(normalize_vector(plane->threed_vec),
			normalize_vector(ray->direction));
	if (ft_dabs(d_pro) < EPSILON)
	{
		ray->distance = -1;
		return ;
	}
	distance = dot_product(vec_subtract(plane->cords, ray->origin),
			plane->threed_vec) / d_pro;
	if (distance < 0)
		ray->distance = -1;
	else
	{
		ray->distance = distance;
		ray->ray_colour = normalize_colour(plane->colour);
		ray->hit_point = ray_at(*ray, ray->distance);
		if (d_pro >= 0)
			ray->surface_norm = normalize_vector(
					vec_scalar_multiply(plane->threed_vec, -1.0));
		else
			ray->surface_norm = normalize_vector(plane->threed_vec);
	}
}
