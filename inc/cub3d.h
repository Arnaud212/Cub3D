/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:35:07 by agiraud           #+#    #+#             */
/*   Updated: 2023/10/30 17:54:22 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <float.h>
# include <X11/X.h>
# include <X11/keysym.h>

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

// Vecteur camera, champs de vision
# define FOV 0.5
# define COS_A 0.99875026039
# define SIN_A 0.04997916927

// Taille fenetre
# define WIN_WIDTH 1500
# define WIN_HEIGHT 750

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		mv_forth;
	int		mv_back;
	int		mv_left;
	int		mv_right;
	int		turn_left;
	int		turn_right;
}	t_player;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_text
{
	t_img	img;
	int		width;
	int		height;
	char	*name;
}	t_text;

typedef struct s_map
{
	int				col;
	int				lin;
	char			*map;
	unsigned int	ceiling;
	unsigned int	floor;
	t_text			n_text;
	t_text			s_text;
	t_text			e_text;
	t_text			w_text;
}	t_map;

typedef struct s_ray
{
	double	r_dir_x;
	double	r_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	camera_x;	
}	t_ray;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_mlx;

enum e_orientation
{
	north,
	south,
	east,
	west,
};

typedef struct s_line
{
	double				ray_length;
	enum e_orientation	wall_orientation;
	double				wall_inter;
}	t_line;

typedef struct s_all
{
	t_map		map;
	t_player	player;
	t_mlx		mlx;
}	t_all;

int		error_msg(char *error);
int		parse(int argc, char **argv, t_map *map, t_player *player);
int		valid_map(t_map *map);
int		parse_file_map(int fd, t_map *map, int *line_count);
int		valid_map_line(char *line);
char	*add_line_to_tmp_map(char *tmp_map, char *line);
char	*read_map(int fd, int *line_count);
void	get_map_size(t_map *map, char *tmp_map);
int		convert_tmp_map(t_map *map, char *tmp_map);
int		check_filename(char *name);
int		id_is_texture(char *line);
int		id_is_color(char *line);
int		get_tex_file(t_map *map, char *line, char *tex_file);
int		touches_zero(t_map *map, int x, int y);
int		parse_line_tex(t_map *map, char *line);
int		read_colors(char *line, unsigned int *color);
int		parse_line_color(t_map *map, char *line);
int		parse_line_id(t_map *map, char *line);
int		parse_file_id(int fd, t_map *map, int *line_count);
void	init_map(t_map *map);
void	free_map(t_map *map);
void	init_player(t_player *player);
void	player_start(t_player *player, int x, int y, char dir);
int		find_player(t_player *player, t_map *map);
int		launch_mlx(t_mlx *mlx);
int		get_textures(t_mlx *mlx, t_map *map);
int		get_textures_2(t_text *text, t_mlx *mlx);
void	start_loop(t_all *pack);
int		frame(t_mlx *mlx, t_player *player, t_map *map);
void	close_mlx(t_mlx *mlx, t_map *map);
void	project_ray(t_player *player, t_map *map, int nb, t_line *line);
void	init_ray(t_player *player, int nb, t_ray *ray);
void	init_step(t_player *player, t_ray *ray);
void	render_ray(t_mlx *mlx, t_map *map, int nb, t_line *line);
void	wall_type(t_ray *ray, t_line *line);
void	dda(t_map *map, t_line *line, t_ray *ray);
void	get_x(t_player *player, t_line *line, t_ray *ray);
void	get_y(t_player *player, t_line *line, t_ray *ray);
void	pixel_ceiling_floor(t_mlx *mlx, t_map *map, int nb, t_line *line);
t_text	*wall_text(t_map *map, t_line *line);
void	put_pixel(t_img *img, int nb, int x, unsigned int color);
int		key_press(int key, t_all *pack);
int		exit_prog(t_all *pack);
int		key_release(int key, t_all *pack);
int		refresh(t_all *pack);
void	mv_up(t_player *player, t_map *map);
void	mv_down(t_player *player, t_map *map);
void	mv_left(t_player *player, t_map *map);
void	mv_right(t_player *player, t_map *map);
void	turn_right(t_player *player);
void	turn_left(t_player *player);
int		verif_file(t_map *map);

#endif
