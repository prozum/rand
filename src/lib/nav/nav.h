#ifndef RAND_NAV_H
#define RAND_NAV_H

#define FULL_TURN 90
//This defines that we belive that there is a window, if the laser reads more than a 0.5m longer than the sonar.
#define WINDOW_RECON_THRESHOLD 50
#define MIN_RANGE 60
#define LASER_MAX_DISTANCE_CM 2200

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
#include "search/search.h"

#define FULL_TURN 90
//This defines that we belive that there is a window, if the laser reads more than a 0.5m longer than the sonar.
#define WINDOW_RECON_THRESHOLD 50
#define MIN_RANGE 60


#define DRONE_RIGHT_SIDE 27000
#define LASER_MAX_RANGE 2200
#define DRONE_LEFT_SIDE 9000

#define SENSOR_DEVIATION 5

#define PERIOD_MILLIS 100 //The time between calls of the navigator.
#define PERIODS_PER_SEC 1000 / PERIOD_MILLIS
#define PERIOD_SECONDS PERIOD_MILLIS / 1000.0f

#define MAP_MIDDLE (MAP_HEIGHT + MAP_WIDTH) / 4 * CENTIMETERS_PR_PIXEL

#define ANGLE_RESOLUTION 0.01    // Means that each degree is split in 100
#define INV_ANGLE_RESOLUTION 100 // One degree is 100 steps on the scale
#define FULL_TURN_SCALED (uint16_t) 360 * INV_ANGLE_RESOLUTION

/* Constant used to find the distance to the wall with a 15 degree angle from front view */
static const fix16_t sonar_reliable_constant = 0x5290; // sin(15) / sin(75)

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

void nav_idle(rep_t *rep, nav_t *nav);
void nav_turn_left(rep_t *rep, nav_t *nav, uint8_t degrees);
void nav_turn_right(rep_t *rep, nav_t *nav, uint8_t degrees);
void nav_turn_around(rep_t *rep, nav_t *nav);
void nav_move_forward(rep_t *rep, nav_t *nav, fix16_t distance);
void nav_move_up(rep_t *rep, nav_t *nav);
void nav_move_down(rep_t *rep, nav_t *nav);
void nav_searching(rep_t *rep, nav_t *nav);

/**
 * Sets the state of a specified point on the map
 * @param x - The x-coordinate to set
 * @param y - The y-coordinate to set
 * @param field - The state to set the point to
 */
void map_set_point(uint8_t x, uint8_t y, fieldstate_t field);
/**
 * Sets the position of the drone's current position on the map
 * @param nav - A pointer to a nav_t, i.e. the current position and angle of the drone
 * @param field - The state to set on the map
 */
void map_set_position(nav_t *nav, fieldstate_t field);
/**
 * Checks the state of a specified point on the map
 * @param x - The x-coordinate to check
 * @param y - The y-coordinate to check
 * @return - The state of the specified position
 */
fieldstate_t map_check_point(uint8_t x, uint8_t y);
/**
 * Checks what state the drones current position has on the internal map
 * @param nav - A pointer to a nav_t, i.e. the current position and angle of the drone
 * @return - The map-state of the current position
 */
fieldstate_t map_check_position(nav_t *nav);

/**
 * Aligns the drones internal representation of the world to the drone's map
 * @param x_coord - Real world x-coordinate
 * @param y_coord - Real world y-coordinate
 * @return - A struct containing the map-coordinates
 */
map_coord_t align_to_map(uint16_t x_coord, uint16_t y_coord);

fix16_t fix_rad_angle(uint16_t degrees_100th);
/**
 * Calculate offset on the y-axis from an angle and a distance
 * @param degrees_100th The angle specified in 100th degrees
 * @param distance - The distance to the object
 * @return - The offset on the y-axis
 */
fix16_t calculate_y_distance(uint16_t degrees_100th, fix16_t distance);
/**
 * Calculates offset on the x-axis from an angle and a distance
 * @param degrees_100th - The angle specified in 100th degrees
 * @param distance - The distance to the object
 * @return - The offset on the x-axis
 */
fix16_t calculate_x_distance(uint16_t degrees_100th, fix16_t distance);
/**
 * Updates the current angle of the drone
 * @param nav - A pointer to a nav_t, i.e. the current position and angle of the drone
 * @param degrees - The angle to increment with, specified in ordinary degrees
 */
void update_angle(nav_t *nav, fix16_t degrees);

/// Draws an obstacle at a specified angle and distance from the drone's current position
/// @param val - The measured distance to the obstacle
/// @param nav - A pointer to the navigation struct, i.e. the drone's position
/// @param side_offset - The angle measured to the obstacle in 100th degrees
/// @param state - The determined obstacle type (WINDOW, WALL, VISITED or UNVISITED)
void draw_obstacle(uint16_t val, nav_t *nav, const int16_t side_offset, fieldstate_t state);
/// Draws the map from the drone current position and world representation
/// @param rep - A pointer to a rep_t, i.e. the drone's world representation
/// @param nav - A pointer to a nav_t, i.e. the drone's current position
void draw_map(rep_t *rep, nav_t *nav);

#endif //RAND_NAV_H


