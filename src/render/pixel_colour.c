#include "mini_rt.h"

static t_colour	blend_colour(t_colour c1, t_colour c2, double t);
static t_colour	get_object_colour(t_ray ray, t_object *objects);
static t_colour	get_sphere_colour(t_object *closest, t_ray ray);
static t_colour	get_plane_colour(t_object *closest, t_ray ray);
static t_colour	get_cylinder_colour(t_object *closest, t_ray ray);

/**
 * @brief Checks the colour of the ray
 * @param ray the ray to check
 * @param objects the list of objects
 * @return the colour of what the ray hits or the background colour
 */
t_colour	get_ray_colour(t_ray ray, t_object *objects)
{
	t_vector	normalized_ray_direction;
	double		ratio;
	t_colour	ray_colour;
	t_colour	sky1;
	t_colour	sky2;

	ray_colour = get_object_colour(ray, objects);
	if (legal_colour(ray_colour))
		return (ray_colour);
	normalized_ray_direction = normalize_vector(ray.direction);
	ratio = 0.5 * (-normalized_ray_direction.y + 1.0);
	sky1 = (t_colour){128, 178, 255};
	sky2 = (t_colour){255, 255, 255};
	ray_colour = blend_colour(sky1, sky2, ratio);
	return (ray_colour);
}

/**
 * @brief Gets the colour of the first object the ray hits
 * @param ray the ray to check
 * @param objects the objects to check
 * @return the colour of the object or -1 if there's no hit
 */
static t_colour	get_object_colour(t_ray ray, t_object *objects)
{
	t_object	*temp;
	double		distance;
	t_object	*closest;
	double		old_hit;

	closest = NULL;
	temp = objects;
	old_hit = 0;
	while (temp)
	{
		distance = hit_object(temp, ray);
		if ((distance < old_hit || old_hit == 0) && distance > 0.0)
		{
			closest = temp;
			old_hit = distance;
		}
		temp = temp->next;
	}
	if (closest != NULL && closest->sphere != NULL)
		return (get_sphere_colour(closest, ray));
	else if (closest != NULL && closest->cylinder != NULL)
	{
		// printf("Returning cylinder colour!\n");
		return (get_cylinder_colour(closest, ray));
	}
	else if (closest != NULL && closest->plane != NULL)
		return (get_plane_colour(closest, ray));
	return ((t_colour){-1, -1, -1});
}

/**
 * @brief Calculates the colour of the plane
 * @param closest the plane it hits
 * @param ray the ray to check
 * @return the plane colour
 * @note Placeholder for now
 */
static t_colour	get_plane_colour(t_object *closest, t_ray ray)
{
	double		t;
	double		falloff;
	t_colour	plane_color;
	double		base_brightness;
	double		adjusted_brightness;

	t = hit_object(closest, ray);
	falloff = 1.0 / (1.0 + t * t * 0.01);
	plane_color = closest->plane->colour;
	base_brightness = 0.2;
	adjusted_brightness = base_brightness + (1.0 - base_brightness) * falloff;
	plane_color.r = (int)(plane_color.r * adjusted_brightness);
	plane_color.g = (int)(plane_color.g * adjusted_brightness);
	plane_color.b = (int)(plane_color.b * adjusted_brightness);
	return (plane_color);
}

/**
 * @brief Calculates the colour of the plane
 * @param closest the plane it hits
 * @param ray the ray to check
 * @return the plane colour
 * @note Placeholder for now
 */
static t_colour	get_cylinder_colour(t_object *closest, t_ray ray)
{
	t_colour	cylinder_colour;
	(void)closest;
	(void)ray;

	cylinder_colour = closest->cylinder->colour;
	return (cylinder_colour);
}

/**
 * @brief Calculates the colour of the circle
 * @param closest the plane it hits
 * @param ray the ray to check
 * @return the plane colour
 * @note Placeholder for now
 */
static t_colour	get_sphere_colour(t_object *closest, t_ray ray)
{
	t_vector	hit_point;
	t_vector	n;
	double		t;

	t = hit_object(closest, ray);
	hit_point = ray_at(ray, t);
	n = normalize_vector(vec_subtract(hit_point, closest->sphere->cords));
	return ((t_colour){0.5 * (n.x + 1) * 255, 0.5 * (n.y + 1)
		* 255, 0.5 * (n.z + 1) * 255});
}

/**
 * @brief Blends colour based on given ratio
 * @param c1 
 * @param c2 
 * @param t 
 * @return 
 */
static t_colour	blend_colour(t_colour c1, t_colour c2, double ratio)
{
	t_colour	result;

	result.r = (int)((1 - ratio) * c1.r + ratio * c2.r);
	result.g = (int)((1 - ratio) * c1.g + ratio * c2.g);
	result.b = (int)((1 - ratio) * c1.b + ratio * c2.b);
	return (result);
}
