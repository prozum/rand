#ifndef RAND_NAV_H
#define RAND_NAV_H

/** @file nav.h
 * \brief Navigation functions and constants
 *
 * \addtogroup Navigation
 * @{
 */

#include <stdint.h>

#include "core/log.h"
#include "fc/fc.h"
#include "kalman/kalman-datafusion.h"
#include "kalman/kalman.h"
#include "libfixmath/fix16.h"
#include "map/map.h"
#include "nav-struct.h"
#include "search/search.h"

//! This defines that we belive that there is a window, if the laser reads more than a 0.5m longer than the sonar.
#define WINDOW_RECON_THRESHOLD 20 //!< The difference in readings that triggers the drone to believe there's a window
#define MIN_SENSOR_RANGE 60       //!< The distance at which the drone should follow the wall
#define MIN_DRAW_RANGE 100        //!< The range at which the drone should begin to draw obstacles

#define DRONE_RIGHT_SIDE 0x4b65f //!< 270 degrees
#define DRONE_LEFT_SIDE 0x19220  //!< 90 degrees

#define SENSOR_DEVIATION                                                                                               \
    5 //!< When following a wall indicates at how large a change of distance the drone should take action

#define PERIOD_MILLIS 100                      //!< The time between calls of the navigator in milliseconds.
#define PERIOD_SECONDS PERIOD_MILLIS / 1000.0f //!< The time between calls of the navigator in seconds

#define MAP_MIDDLE (MAP_HEIGHT + MAP_WIDTH) / 4 //!< Defines the middle of the drone's internal map

//! Constant used to find the distance to the wall with a 15 degree angle from front view
static const fix16_t sonar_reliable_constant = 0x5290; //!< sin(15) / sin(75)
static const fix16_t drone_right_side = 0x4b65f;       //!< 270 degrees
static const fix16_t drone_left_side = 0x19220;        //!< 90 degrees
static const fix16_t full_turn = 0x19220;              //!< 90 degrees

/**
 * Updates the state of the drone by checking its' world representation
 * @param state - A pointer to the state to update
 * @param rep - A pointer to the drone's world representation
 */
void update_state(state_t *state, rep_t *rep);

/**
 * Initializes the navigation-component
 * @param nav - A pointer to a nav_t struct that should be initialized
 */
void init_nav(nav_t *nav);

/**
 * Initializes the world representation for the navigation system
 * @param rep - A pointer to the rep_t struct to initialize
 * @param fc - A pointer to the flight-controller that controls the drone
 * @param laser - A pointer to the laser-component
 * @param sonar - A pointer to the sonar-component
 * @param ir_top - A pointer to the ir-sensor on top of the drone
 * @param ir_bottom - A pointer to the ir-sensor on the bottom of the drone
 */
void init_rep(rep_t *rep, fc_t *fc, laser_t *laser, sonar_t *sonar, ir_t *ir_top, ir_t *ir_bottom);

/**
 * The main entry point for the navigation struct
 * Reads all sensors, checks if any action must be taken and act accordingly
 * Also updates the map with found obstacles and visited positions
 * @param rep - A pointer to the drone's world representation
 * @param nav - A pointer to the navigation struct, which maintains position, angle etc.
 */
void navigation(rep_t *rep, nav_t *nav);

/**
 * Checks if there's a wall in front of the drone from the world representation
 * @param rep - The drone's world representation
 * @param state - The current state of the drone
 * @return - A boolean flag that is TRUE if there is a wall, and FALSE if not
 */
uint8_t check_wall_front(rep_t *rep, state_t state);

/**
 * Checks if there's a wall to the left of the drone
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @return - A boolean flag that is TRUE if there is a wall, and FALSE if not.
 */
uint8_t check_wall_left(rep_t *rep);

/**
 * Checks if there's a wall to the right of the drone
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @return - A boolean flag that is TRUE if there is a wall, and FALSE if not.
 */
uint8_t check_wall_right(rep_t *rep);

/**
 * Checks if there's a window in front of the drone
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param state - The current state of the drone
 * @return - A boolean flag that is TRUE if there is a window and FALSE if not
 */
uint8_t check_win_front(rep_t *rep, state_t state);

/**
 * Checks if there's a window to the left of the drone
 * @param state - A pointer to the struct maintaining the drone's world representation
 * @return - A boolean flag that is TRUE if there is a window and FALSE if not
 */
uint8_t check_win_left(state_t *state);

/**
 * Checks if there's a window to the right of the drone
 * @param state - A pointer to the struct maintaining the drone's world representation
 * @return - A boolean flag that is TRUE if there is a window and FALSE if not
 */
uint8_t check_win_right(state_t *state);

/**
 * Checks if there's ground closely below the drone
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @return - A boolean flag that is TRUE if the ground is close by and FALSE if not
 */
uint8_t check_ground(rep_t *rep);

/**
 * Checks if the ceiling is closely above the drone
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @return - A boolean flag that is TRUE if the ceiling is close by and FALSE if not
 */
uint8_t check_ceiling(rep_t *rep);

/**
 * Check if something blocks the drone in front of it
 * @param state - The current state
 * @return - A boolean flag that is TRUE if there's something in front of the drone and FALSE if not
 */
uint8_t check_blocked_front(state_t *state);

/**
 * Check if something blocks the drone to the right of it
 * @param state - The current state
 * @return - A boolean flag that is TRUE if there's something to the right of the drone and FALSE if not
 */
uint8_t check_blocked_right(state_t *state);

/**
 * Check if something blocks the drone to the left of it
 * @param state - The current state
 * @return - A boolean flag that is TRUE if there's something in the left of the drone and FALSE if not
 */
uint8_t check_blocked_left(state_t *state);

/**
 * Check if drone is following wall
 * @param state - The current state
 * @return - A boolean flag that is TRUE if the drone is following a wall and FALSE if not
 */
uint8_t check_follow_wall(state_t *state);

/**
 * Implements the IDLE-state of the drone
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 */
void on_idle(rep_t *rep, nav_t *nav);

/**
 * Implements the MOVE_FORWARD-state of the drone
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 */
void on_move_forward(rep_t *rep, nav_t *nav);

/**
 * Implements the MOVE_UP-state of the drone
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 */
void on_move_up(rep_t *rep, nav_t *nav);

/**
 * Implements the MOVE_DOWN-state of the drone
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 */
void on_move_down(rep_t *rep, nav_t *nav);

/**
 * Implements the FOLLOW_FORWARD-state of the drone
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 */
void on_follow_forward(rep_t *rep, nav_t *nav);

/**
 * Implements the FOLLOW_FURTHER-state of the drone
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 */
void on_follow_further(rep_t *rep, nav_t *nav);

/**
 * Implements the FOLLOW_CHECK-state of the drone
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 */
void on_follow_check(rep_t *rep, nav_t *nav);

/**
 * Implements the FOLLOW_TURN-state of the drone
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 */
void on_follow_turn(rep_t *rep, nav_t *nav);

/**
 * Implements the SEARCHING-state of the drone
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 */
void on_searching(rep_t *rep, nav_t *nav);

/**
 * Implements the TURNING-state of the drone
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 */
void on_turning(rep_t *rep, nav_t *nav);

/**
 * Checks if the sonar is reliable
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param state - The current state of the drone
 * @return - A boolean flag that is TRUE if the sonar is reliable and FALSE if not
 */
uint8_t is_sonar_reliable(rep_t *rep, state_t state);

/**
 * Aligns the drone to a wall either to the left or right of it, depending on the current state
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 */
uint8_t check_alignment_wall(rep_t *rep, nav_t *nav);

/**
 * Enters the IDLE state
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 */
void nav_idle(rep_t *rep, nav_t *nav);

/**
 * Enters the TURNING-state and turns the drone left
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 * @param angle - The angle to turn the drone
 */
void nav_turn_left(rep_t *rep, nav_t *nav, fix16_t angle);

/**
 * Enters the TURNING-state and turns the drone right
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 * @param angle - The angle to turn the drone
 */
void nav_turn_right(rep_t *rep, nav_t *nav, fix16_t angle);

/**
 * Enter the TURNING-state and turns the drone 180 degrees
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 */
void nav_turn_around(rep_t *rep, nav_t *nav);

/**
 * Enters the MOVING-state and move the drone forward
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 * @param distance - The distance to move the drone specified in centimeters
 */
void nav_move_forward(rep_t *rep, nav_t *nav, fix16_t distance);

/**
 * Enters the MOVEUP-state and move the drone upwards
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 */
void nav_move_up(rep_t *rep, nav_t *nav);

/**
 * Enters the MOVEDOWN-state and move the drone downwards
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 */
void nav_move_down(rep_t *rep, nav_t *nav);

/**
 * Enters the FOLLOW_FORWARD state
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 */
void nav_follow_forward(rep_t *rep, nav_t *nav);

/**
 * Enters the FOLLOW_FURTHER state
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 * @param distance - How much further to travel.
 */
void nav_follow_further(rep_t *rep, nav_t *nav, fix16_t distance);

/**
 * Enters the FOLLOW_CHECK state
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 */
void nav_follow_check(rep_t *rep, nav_t *nav);

/**
 * Enters the FOLLOW_TURN state
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 */
void nav_follow_turn(rep_t *rep, nav_t *nav);

/**
 * Enters the SEARCHING state to search for unexplored areas of the map
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to the navigation struct maintaining position, angle etc.
 */
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
 * Calculate offset on the y-axis from an angle and a distance
 * @param angle - The angle specified in radians
 * @param distance - The distance to the object
 * @return - The offset on the y-axis
 */
fix16_t calc_y_dist(fix16_t angle, fix16_t distance);

/**
 * Calculates offset on the x-axis from an angle and a distance
 * @param angle - The angle specified in radians
 * @param distance - The distance to the object
 * @return - The offset on the x-axis
 */
fix16_t calc_x_dist(fix16_t angle, fix16_t distance);

/**
 * Updates the current angle of the drone
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to a nav_t, i.e. the current position and angle of the drone
 */
void update_angle(rep_t *rep, nav_t *nav);

/**
 * Updates the current position of the drone
 * @param rep - A pointer to the struct maintaining the drone's world representation
 * @param nav - A pointer to a nav_t, i.e. the current position and angle of the drone
 */
void update_pos(rep_t *rep, nav_t *nav);

/** Draws an obstacle at a specified angle and distance from the drone's current position
 * @param val - The measured distance to the obstacle
 *   @param nav - A pointer to the navigation struct, i.e. the drone's position
 *   @param side_offset - The angle measured to the obstacle in 100th degrees
 *   @param state - The determined obstacle type (WINDOW, WALL, VISITED or UNVISITED)
 */
void draw_obstacle(uint16_t val, nav_t *nav, const fix16_t side_offset, fieldstate_t state);

/** Draws the map from the drone current position and world representation
 * @param rep - A pointer to a rep_t, i.e. the drone's world representation
 * @param nav - A pointer to a nav_t, i.e. the drone's current position
 */
void update_map(rep_t *rep, nav_t *nav);

#endif // RAND_NAV_H

//! @}
