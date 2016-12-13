#ifndef RAND_NAV_H
#define RAND_NAV_H

#define FULL_TURN 90
#define MAX_NEGATIVE_ACCELERATION 0
#define NO_ACCELERATION 1
#define MAX_POSITIVE_ACCELERATION 2
//This defines that we belive that there is a window, if the laser reads more than a 0.5m longer than the sonar.
#define WINDOW_RECON_THRESHOLD 50
#define MIN_RANGE 60
#define LASER_MAX_DISTANCE_CM 2200

#define SONAR_DEG 15
#define PERPENDICULAR 90
#define DRONE_RIGHT_SIDE 27000
#define LASER_MAX_RANGE 2200
#define DRONE_LEFT_SIDE 9000

#define SENSOR_DEVIATION 5
#define MIN_DIFF_LASER_SONAR 30

#include <stdint.h>

#include "nav-struct.h"
#include "fc/fc.h"
#include "kalman/kalman_datafusion.h"
#include "kalman/kalman.h"
#include "core/log.h"
#include "map/map.h"
#include "libfixmath/fix16.h"

#define PERIOD_MILLIS 100 //The time between calls of the navigator.
#define PERIODS_PER_SEC 1000 / PERIOD_MILLIS

#define MAP_MIDDLE 800

#define ANGLE_RESOLUTION 0.01    // Means that each degree is split in 100
#define INV_ANGLE_RESOLUTION 100 // One degree is 100 steps on the scale

//todo: Skal udregnes ud fra WCET af løkken i findpath funktionen



typedef enum side_e{
    RIGHT = 0,
    LEFT = 1
}side_t;

void update_state(state_t *state, rep_t *rep);

void init_nav(nav_t *nav);
void init_rep(fc_t *fc, laser_t *laser, sonar_t *sonar, ir_t *irTop, ir_t *irBottom, rep_t *rep);

void navigation(rep_t *rep, nav_t *nav);

uint8_t check_wall_front(rep_t *rep, state_t state);
uint8_t check_wall_left(rep_t *rep);
uint8_t check_wall_right(rep_t *rep);
uint8_t check_win_front(rep_t *rep, state_t state);
uint8_t check_win_left(rep_t *rep);
uint8_t check_win_right(rep_t *rep);
uint8_t check_ground(rep_t *rep);
uint8_t check_ceiling(rep_t *rep);
uint8_t check_blocked_front(state_t *state);
uint8_t check_blocked_right(state_t *state);
uint8_t check_blocked_left(state_t *state);

void on_idle(rep_t *rep, nav_t *nav);
void on_move_forward(rep_t *rep, nav_t *nav);
void on_move_up(rep_t *rep, nav_t *nav);
void on_move_down(rep_t *rep, nav_t *nav);
void on_searching(rep_t *rep, nav_t *nav);
void on_turning(rep_t *rep, nav_t *nav);

uint8_t is_sonar_reliable(rep_t *rep, state_t state);
uint8_t check_alignment_wall(rep_t *rep, nav_t *nav);
void draw_map(rep_t *rep, nav_t *nav);

void nav_idle(rep_t *rep, nav_t *nav);
void nav_turn_left(rep_t *rep, nav_t *nav, uint8_t degrees);
void nav_turn_right(rep_t *rep, nav_t *nav, uint8_t degrees);
void nav_turn_around(rep_t *rep, nav_t *nav);
void nav_move_forward(rep_t *rep, nav_t *nav, fix16_t distance);
void nav_move_up(rep_t *rep, nav_t *nav);
void nav_move_down(rep_t *rep, nav_t *nav);
void nav_searching(rep_t *rep, nav_t *nav);

void map_set_point(uint8_t x, uint8_t y, fieldstate_t field);
void map_set_position(nav_t *nav, fieldstate_t field);
fieldstate_t map_check_point(uint8_t x, uint8_t y);
fieldstate_t map_check_position(nav_t *nav);

pixel_coord_t align_to_pixel(uint16_t x_coord, uint16_t y_coord);

fix16_t fix_rad_angle(uint16_t degrees_100th);
fix16_t calculate_y_distance(uint16_t degrees_100th, fix16_t distance);
fix16_t calculate_x_distance(uint16_t degrees_100th, fix16_t distance);
void update_angle(nav_t *nav, fix16_t degrees);

#endif //RAND_NAV_H


