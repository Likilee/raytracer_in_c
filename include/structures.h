/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:46:59 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/05 11:41:13 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

/*
** 0. Mlx structures
*/
typedef struct s_data		t_data;
typedef struct s_scene		t_scene;
typedef struct s_cntl		t_cntl;

/*
** 1. common structures
*/
typedef struct s_vec3		t_vec3;
typedef struct s_vec3		t_point3;
typedef struct s_vec3		t_color3;
typedef struct s_ray		t_ray;
typedef struct s_hit_record	t_hit_rec;
typedef struct s_matrix44	t_matrix44;
typedef struct s_pth_data	t_pth_data;

/*
** 2. scene structures
*/
typedef struct s_global		t_global;
typedef struct s_camera		t_camera;
typedef struct s_cam_set	t_cam_set;
typedef struct s_canvas		t_canvas;
typedef struct s_material	t_material;
typedef struct s_texture	t_texture;

/*
** 3. object structures
*/
typedef struct s_objects	t_objects;
typedef struct s_light		t_light;
typedef struct s_l_set		t_l_set;
typedef struct s_sphere		t_sphere;
typedef struct s_sp_set		t_sp_set;
typedef struct s_plane		t_plane;
typedef struct s_square		t_square;
typedef struct s_cylinder	t_cylinder;
typedef struct s_triangle	t_triangle;
typedef struct s_tr_set		t_tr_set;
typedef struct s_cube		t_cube;
typedef struct s_pyramid	t_pyramid;

/*
** 4. Identifier Macro
*/
typedef int					t_bool;

# define FALSE 0
# define TRUE 1

typedef int					t_obj_type;

# define SP 0
# define LIGHT 1
# define PL	2
# define SQ 3
# define CY 4
# define TR 5
# define CB 6
# define PM 7
# define CAM 11

typedef int					t_material_type;

# define DIFFUSE 0
# define METAL 1
# define DIELECTRIC 2
# define LAMBERTIAN 3

typedef int					t_tex_type;

# define SOLID 0
# define CHECKER 1
# define CHECKER_UV 2
# define RAINBOW 3
# define IMAGE 4
# define WAVE 5

typedef int					t_light_type;

# define POINT 0
# define PARALLEL 1

typedef int					t_filter;

# define FILT_D 0
# define FILT_S 1
# define FILT_R 2
# define FILT_G 3
# define FILT_B 4

/*
** Global macro
*/
# define COUNT 20
# define KSN 256

/*
** 1. Common  structures
*/
struct						s_vec3
{
	double	x;
	double	y;
	double	z;
};

struct						s_ray
{
	t_point3	orig;
	t_vec3		dir;
};

struct						s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	t_objects	*obj;
	t_material	*material;
	t_texture	*texture;
	double		tmin;
	double		tmax;
	double		t;
	double		u;
	double		v;
	t_bool		front_face;
};

struct						s_matrix44
{
	double	x[4][4];
	t_vec3	rotate_deg;
};

struct						s_pth_data
{
	int			lane;
	int			count;
	int			progress;
	t_cntl		*c;
};

/*
** 2. Scene structures
*/
struct						s_global
{
	t_color3	ambient;
	int			spp;
	int			depth;
	int			lux;
	t_filter	f_type;
};

/*
** camera member
** - orig = origin
** - dir = dir
** - horizontal = ???????????? ??????
** - vertical = ???????????? ??????
** - left_bottom = lower left corner;
*/
struct						s_camera
{
	t_point3	orig;
	t_point3	dir;
	double		hfov;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_point3	left_bottom;
};

struct						s_cam_set
{
	double		theta;
	double		half_width;
	double		viewport_height;
	double		viewport_width;
	t_vec3		w;
	t_vec3		u;
	t_vec3		v;
	t_vec3		vup;
	t_vec3		lookat;
};

/*
** canvas member
** - width = canvas width;
** - hegiht = canvas height;
*/
struct						s_canvas
{
	int		width;
	int		height;
	double	aspect_ratio;
};

struct						s_material
{
	t_material_type	type;
	double			option1;
};

struct						s_texture
{
	t_color3	albedo1;
	t_color3	albedo2;
	double		option1;
	t_data		*img;
	t_tex_type	type;
};

/*
** 0. Mlx structures
*/
struct						s_scene
{
	t_global	global;
	t_canvas	canv;
	t_camera	*cam_onair;
	t_objects	*cam_list;
	t_objects	*world;
	t_objects	*background;
	t_data		*img;
};

struct						s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
};

/*
**  mode
**  0:default 1:object transform 2:camera transform
*/
struct						s_cntl
{
	void		*mlx;
	void		*win;
	t_scene		*scene;
	t_objects	*selected;
	t_data		*img;
	int			mode;
	int			light_on;
	t_bool		rotate_on;
};

/*
** 3. Object structures
*/
struct						s_objects
{
	void		*element;
	t_matrix44	*rotate;
	t_matrix44	*rotate_normal;
	t_material	*material;
	t_texture	*texture;
	void		*next;
	t_obj_type	type;
};

struct						s_light
{
	t_point3		p;
	t_vec3			dir;
	t_color3		light_color;
	double			brightness;
	double			ka;
	t_light_type	type;
};

struct						s_l_set
{
	t_ray		light_ray;
	t_color3	ambient;
	t_color3	diffuse;
	t_color3	specular;
	t_vec3		light_dir;
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	t_color3	lightintensity;
	double		lightattenuation;
	double		distanceattenuation;
	double		lightradiusmask;
	double		attenuation_radius;
	double		light_len;
	double		kd;
	double		ks;
	double		ksn;
	double		spec;
};

struct						s_sphere
{
	t_point3	center;
	double		radius;
	double		radius2;
};

struct						s_sp_set
{
	t_vec3		oc;
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		sqrtd;
	double		root;
};

struct						s_plane
{
	t_point3	p;
	t_vec3		normal;
};

struct						s_square
{
	t_point3	center;
	t_vec3		normal;
	double		side_len;
	t_point3	min;
	t_point3	max;

};

struct						s_cylinder
{
	t_point3	center_bottom;
	t_point3	center_top;
	t_vec3		axis;
	double		radius;
	double		radius2;
	double		height;

};

struct						s_triangle
{
	t_point3	p0;
	t_point3	p1;
	t_point3	p2;
	t_vec3		p0p1;
	t_vec3		p1p2;
	t_vec3		p2p0;
	t_vec3		normal;
};

struct						s_tr_set
{
	t_vec3		p;
	t_vec3		c0;
	t_vec3		c1;
	t_vec3		c2;
	t_vec3		vp;
	t_vec3		r0_p0;
	double		t;
	double		denominator;
};

/*
** square[i] ordered: up,down,left,right,front,back
*/
struct						s_cube
{
	t_point3	center;
	double		side_len;
	t_square	*square[6];
};

struct						s_pyramid
{
	t_point3	top;
	t_point3	center;
	double		side_len;
	t_square	*bottom;
	t_triangle	*side[4];
};

#endif
