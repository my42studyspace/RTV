/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfreddie <gfreddie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 20:46:32 by gfreddie          #+#    #+#             */
/*   Updated: 2021/02/04 21:05:38 by gfreddie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "ft_printf.h"

# define SHADER_FILE "./src/shader/shader.frag"
# define HEIGHT 1080
# define WIDTH 1920
# define DIRECTION 0
# define AMBIENT 1
# define POINT 2
# define FULL_RENDER 1
# define MIN_RENDER 0
# define STOP_RENDER -1
# define FLOAT_MAX 3.402823466e+38
# define FLOAT_MIN 1.175494351e-38

typedef	struct		s_material
{
	float			color[3];
	float			specular;
}					t_material;

typedef	struct		s_transform
{
	float			position[3];
	float			rotation[3];
}					t_transform;

typedef	struct		s_camera
{
	t_transform		transform;
	float			direction[3];
}					t_camera;

typedef	struct		s_light
{
	int				type;
	t_transform		transform;
	float			direction[3];
	float			intensity;
	float			radius;
}					t_light;

typedef	struct		s_sphere
{
	t_transform		transform;
	float			radius;
	t_material		material;
	short			is_outline;
	short			is_toon;
}					t_sphere;

typedef	struct		s_plane
{
	t_transform		transform;
	float			normal[3];
	t_material		material;
}					t_plane;

typedef	struct		s_cone
{
	t_transform		transform;
	float			axis[3];
	float			angle;
	t_material		material;
}					t_cone;

typedef	struct		s_cylinder
{
	t_transform		transform;
	float			axis[3];
	float			radius;
	t_material		material;
}					t_cylinder;

typedef struct		s_rtv1
{
	char			*vertex_shader_source;
	char			*fragment_shader_source;
	GLFWwindow		*window;
	GLuint			fragment_shader;
	GLuint			vertex_shader;
	GLuint			shader_program;
	GLuint			vbo;
	GLuint			vao;
	GLuint			ebo;
	t_light			lights[16];
	int				number_of_lights;
	t_camera		camera;
	t_sphere		spheres[16];
	int				number_of_spheres;
	t_plane			planes[16];
	int				number_of_planes;
	t_cone			cones[16];
	int				number_of_cones;
	t_cylinder		cylinders[16];
	int				number_of_cylinders;
	int				argc;
	char			**argv;
	char			is_move;
	char			is_mouse_move;
	double			prev_mouse_pos_x;
	double			prev_mouse_pos_y;
	double			cur_mouse_pos_x;
	double			cur_mouse_pos_y;
	double			delta_x;
	double			delta_y;
	float			camera_rotation_speed;
	float			camera_move_speed;
	float			camera_forward[3];
	float			camera_right[3];
	float			camera_move_direction[2];
	char			render_type;
}					t_rtv1;

char				*load_shader(char *file);
int					main();
void				parse_line(t_rtv1 *rtv1, char **mass);
void				parser(t_rtv1 *rtv1);
int					parse_cam(t_rtv1 *rtv1, char **mass);
int					parse_light(t_rtv1 *rtv1, char **mass);
int					parse_sphere(t_rtv1 *rtv1, char **mass);
int					parse_plane(t_rtv1 *rtv1, char **mass);
int					parse_cone(t_rtv1 *rtv1, char **mass);
int					parse_cylinder(t_rtv1 *rtv1, char **mass);
char				*combine_str_int_str(char *str1, int number, char *str2);
void				set_main_settings(GLuint shader_program, t_rtv1 *rtv1);
void				set_objects_count(GLuint shader_program, t_rtv1 *rtv1);
void				set_cam_uniform(t_camera camera, GLuint shader_program);
void				set_sphere_uniform(t_sphere sphere, int index,
	GLuint shader_program);
void				set_cone_uniform(t_cone cone, int index,
	GLuint shader_program);
void				set_cylinder_uniform(t_cylinder cylinder, int index,
	GLuint shader_program);
void				set_plane_uniform(t_plane plane, int index,
	GLuint shader_program);
void				set_light_uniform(t_light light, int index,
	GLuint shader_program);
void				set_settings(t_rtv1 *rtv1, GLuint shader_program);
void				usage();
void				exit_with_error(char *message);
void				malloc_check(void *data);
float				clamp(float number, float min, float max);
int					validate_light(char *str1, char *str2);
int					validation_obj(char *line);
int					validation(char *line);
void				apply_rotation(float *v, float angle_x, float angle_y);
void				rotation_y(float *v, float angle);
void				rotation_x(float *v, float angle);
void				rotate_camera_direction(t_rtv1 *rtv1);
void				reset_camera_direction(t_rtv1 *rtv1);
void				move_camera(t_rtv1 *rtv1);
t_rtv1				*init(int argc, char **argv);
void				mouse_button_callback(GLFWwindow *window, int key,
	int action, int mode);
void				cursor_position_callback(GLFWwindow *window, double xpos,
	double ypos);
void				key_callback(GLFWwindow *window, int key, int scancode,
	int action);
void				init_gl(t_rtv1 *rtv1);
void				loop(t_rtv1 *rtv1);
void				set_event_callbacks(t_rtv1 *rtv1);
void				parse_vec3(float *vec3, char **str);
void				parse_float(float *f, char *str);
int					parse_light(t_rtv1 *rtv1, char **mass);
void				parse_light_help(t_rtv1 *rtv1, char **mass);
void				free_double_char_array(char **str);
#endif
