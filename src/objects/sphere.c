/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:45:11 by eweiberl          #+#    #+#             */
/*   Updated: 2024/01/30 16:45:13 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @brief Checks if a ray hits a specific sphere object
 * @param sphere the sphere object to check
 * @param ray the ray to check
 * @return sets the distance to -1 in case of no hit
 */
void	hit_sphere(t_sphere *sphere, t_ray *ray)
{
	t_vector	sphere_to_ray_origin;
	double		dir_len_sq;
	double		projection_len;
	double		radius_sq;
	double		discriminant;

	sphere_to_ray_origin = vec_subtract(ray->origin, sphere->cords);
	dir_len_sq = dot_product(ray->direction, ray->direction);
	projection_len = 2.0 * dot_product(sphere_to_ray_origin, ray->direction);
	radius_sq = dot_product(sphere_to_ray_origin, sphere_to_ray_origin)
		- (sphere->diameter / 2) * (sphere->diameter / 2);
	discriminant = projection_len * projection_len - 4 * dir_len_sq * radius_sq;
	if (discriminant < 0)
	{
		ray->distance = -1;
		return ;
	}
	ray->distance = (-projection_len - sqrt(discriminant)) / (2.0 * dir_len_sq);
	ray->ray_colour = normalize_colour(sphere->colour);
	ray->hit_point = ray_at(*ray, ray->distance);
	ray->surface_norm = normalize_vector(vec_subtract(ray->hit_point,
				sphere->cords));
}
