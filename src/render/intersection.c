#include "mini_rt.h"

static double		hit_sphere(t_sphere *sphere, t_ray ray);
static double		hit_plane(t_plane *plane, t_ray ray);
static double		hit_cylinder(t_cylinder *cylinder, t_ray ray);

double	hit_object(t_object *object, t_ray ray)
{
	if (object->sphere != NULL)
		return (hit_sphere(object->sphere, ray));
	else if (object->cylinder != NULL)
		return (hit_cylinder(object->cylinder, ray));
	else if (object->plane != NULL)
		return (hit_plane(object->plane, ray));
	return (-1.0);
}

static double	hit_sphere(t_sphere *sphere, t_ray ray)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	oc = vec_subtract(ray.origin, sphere->cords);
	a = dot_product(ray.direction, ray.direction);
	b = 2.0 * dot_product(oc, ray.direction);
	c = dot_product(oc, oc) - (sphere->diameter / 2)
		* (sphere->diameter / 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	return ((-b - sqrt(discriminant)) / (2.0 * a));
}

static double	hit_plane(t_plane *plane, t_ray ray)
{
	double	d_pro;
	double	distance;

	d_pro = dot_product(plane->threed_vec, ray.direction);
	if (ft_dabs(d_pro) < EPSILON)
		return (-1.0);
	distance = dot_product(vec_subtract(plane->cords, ray.origin),
			plane->threed_vec) / d_pro;
	if (distance < 0)
		return (-1.0);
	return (distance);
}

static double hit_cylinder(t_cylinder *cylinder, t_ray ray) {
	t_vector oc = {ray.origin.x - cylinder->cords.x, ray.origin.y - cylinder->cords.y, ray.origin.z - cylinder->cords.z};
	double radius = cylinder->diameter / 2;

	t_vector vd = {ray.direction.x - dot_product(ray.direction, cylinder->axis) * cylinder->axis.x,
				   ray.direction.y - dot_product(ray.direction, cylinder->axis) * cylinder->axis.y,
				   ray.direction.z - dot_product(ray.direction, cylinder->axis) * cylinder->axis.z};

	t_vector vo = {oc.x - dot_product(oc, cylinder->axis) * cylinder->axis.x,
				   oc.y - dot_product(oc, cylinder->axis) * cylinder->axis.y,
				   oc.z - dot_product(oc, cylinder->axis) * cylinder->axis.z};

	double a = dot_product(vd, vd);
	double b = 2 * dot_product(vo, vd);
	double c = dot_product(vo, vo) - radius * radius;

	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0) return -1; // No intersection

	double t0 = (-b - sqrt(discriminant)) / (2 * a);
	double t1 = (-b + sqrt(discriminant)) / (2 * a);

	double t_closest = -1;
	double ts[2] = {t0, t1};

	for (int i = 0; i < 2; i++) {
		double t = ts[i];
		if (t <= 0) continue;

		t_vector p = {ray.origin.x + t * ray.direction.x,
					  ray.origin.y + t * ray.direction.y,
					  ray.origin.z + t * ray.direction.z};
		t_vector v = vec_subtract(p, cylinder->cords);
		double d = dot_product(v, cylinder->axis);

		// Adjusted to check if the point is within height/2 from the center
		double half_height = cylinder->height / 2;
		if (d >= -half_height && d <= half_height && (t_closest < 0 || t < t_closest)) {
			t_closest = t;
		}
	}

	return t_closest;
}
