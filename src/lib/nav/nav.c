#include "nav.h"
#include "task.h"
#include <math.h>

//Defines the lowest and highest accepted world-position on the internal drone map
#define LOWEST_Y_ORG (MAP_MIDDLE) - (MAP_HEIGHT * CENTIMETERS_PR_PIXEL / 2)
#define HIGHEST_Y_ORG (MAP_MIDDLE) + (MAP_HEIGHT * CENTIMETERS_PR_PIXEL / 2)
#define LOWEST_X_ORG (MAP_MIDDLE) - (MAP_HEIGHT * CENTIMETERS_PR_PIXEL / 2)
#define HIGHEST_X_ORG (MAP_MIDDLE) + (MAP_HEIGHT * CENTIMETERS_PR_PIXEL / 2)

/**
 * Convert from the angle representation of this project (100th subdivisions of each angle) to dix16 radians
 * @param degrees_100th the angle in 100th subdivisions of an angle
 * @return the degree in fix16 radians
 */
fix16_t fix_rad_angle(uint16_t degrees_100th) {
    if(degrees_100th >= (uint16_t) 360 * INV_ANGLE_RESOLUTION) {
        WARNING(SENDER_MAP, "fix_rad_angle: Angle > 360 degrees");
        return fix16_from_int(-1);
    }

    return fix16_deg_to_rad(fix16_from_int(ANGLE_RESOLUTION * degrees_100th));
}

/**
 * Calculates the distance on the y-axis given an angle and a distance
 * @param angle in 1/100 degrees
 * @param distance in cm
 * @return the distance on the y-axis
 */
fix16_t calculate_y_distance (uint16_t angle, fix16_t distance) {
    return fix16_mul(fix16_sin(fix_rad_angle(angle)), distance);
}

/**
 * Calculates the distance on the x-axis given an angle a distance
 * @param angle in 1/100 degrees
 * @param distance in cm
 * @return the distance on the x-axis
 */
fix16_t calculate_x_distance (uint16_t angle, fix16_t distance) {
    fix16_t cos_angle = fix16_cos(fix_rad_angle(angle));
    return fix16_mul(cos_angle, distance);
}

void update_angle(nav_t *nav, fix16_t degrees) {
    //Must use a 32-bit int here, because degrees may be between -36000 and 36000
    int32_t converted_degrees = fix16_to_int(degrees) * INV_ANGLE_RESOLUTION;
    int32_t res_angle = (int32_t) nav->angle + converted_degrees;
    if(res_angle >= (uint16_t) 360 * INV_ANGLE_RESOLUTION) {
        res_angle %= 360 * INV_ANGLE_RESOLUTION;
    }
    else if(res_angle < 0) {
        res_angle += 360 * INV_ANGLE_RESOLUTION;
    }
    nav->angle = (uint16_t) res_angle;
}

uint8_t check_wall_front(rep_t *rep, state_t state){
    if((rep->sonar->valid) == 1 && (rep->sonar->value <= MIN_RANGE || rep->laser->front_value <= MIN_RANGE) &&
            is_sonar_reliable(rep, state)){
        return 1;
    }
    return 0;
}

uint8_t check_wall_left(rep_t *rep) {
    //Check map
    if (rep->laser->left_value <= MIN_RANGE) {
        return 1;
    }
    return 0;
}

uint8_t check_wall_right(rep_t *rep) {
    //Check map
    if (rep->laser->right_value <= MIN_RANGE) {
        return 1;
    }
    return 0;
}

uint8_t check_ground(rep_t *rep) {
    if (rep->ir_bottom->value <= MIN_RANGE) {
        return 1;
    }
    return 0;
}

uint8_t check_ceiling(rep_t *rep) {
    if (rep->ir_top->value <= MIN_RANGE) {
        return 1;
    }
    return 0;
}

uint8_t check_win_front(rep_t *rep, state_t state) {
    if (rep->sonar->valid && rep->laser->left_value >= MIN_RANGE && rep->sonar->value <= MIN_RANGE &&
            is_sonar_reliable(rep, state)) {
        return 1;
    }
    return 0;
}

uint8_t check_win_left(rep_t *rep) {
    if (rep->laser->left_value >= MIN_RANGE) {
        //Cross reference map and turn to check with sonar if necessary
    }
    return 0;
}

uint8_t check_win_right(rep_t *rep) {
    if (rep->laser->right_value >= MIN_RANGE) {
        //Cross reference map and turn to check with sonar if necessary
    }
    return 0;
}

uint8_t check_blocked_front(state_t *state){
    if(state->wall_front || state->win_front){
        return 1;
    }
    return 0;
}

uint8_t check_blocked_right(state_t *state){
    if(state->wall_right || state->win_right){
        return 1;
    }
    return 0;
}

uint8_t check_blocked_left(state_t *state){
    if(state->wall_left || state->win_left){
        return 1;
    }
    return 0;
}

void update_state(state_t *state, rep_t *rep){
    state->ceiling = check_ceiling(rep);
    state->ground = check_ground(rep);
    state->wall_front = check_wall_front(rep, *state);
    state->wall_left = check_wall_left(rep);
    state->wall_right = check_wall_right(rep);
    state->win_front = check_win_front(rep, *state);
    state->win_left = check_win_left(rep);
    state->win_right = check_win_right(rep);
    state->blocked_front = check_blocked_front(state);
    state->blocked_left = check_blocked_left(state);
    state->blocked_right = check_blocked_right(state);
}

void init_rep(fc_t *fc, laser_t *laser, sonar_t *sonar, ir_t *irTop, ir_t *irBottom, rep_t *rep){
    rep->fc = fc;
    rep->laser = laser;
    rep->sonar = sonar;
    rep->ir_top = irTop;
    rep->ir_bottom = irBottom;
}

void init_nav(nav_t *nav){
    nav->task = IDLE;
    nav->val = 0;
    nav->angle = 0;
    nav->prev_dist_wall = 0;

    //Assmumes drone to start in the middle of the room.
    nav->posx = MAP_MIDDLE;
    nav->posy = MAP_MIDDLE;

    *((uint16_t*) &nav->state) &= 0x0000; //hacky (albeit quick) way to set all states to zero

    nav->timer = 0;

    init_search(&nav->search_data);
}

/**
 * Main function of the navigation unit - entry-point for the scheduler
 * @param rep
 * @param nav
 */
void navigation(rep_t *rep, nav_t *nav){

    update_state(&nav->state, rep);
    task_t currenttask = nav->task;

    switch(currenttask){
        case IDLE:
            on_idle(rep, nav); break;
        case TURNING:
            on_turning(rep, nav); break;
        case MOVEFORWARD:
            on_move_forward(rep, nav); break;
        case MOVEUP:
            on_move_up(rep, nav); break;
        case MOVEDOWN:
            on_move_down(rep, nav); break;
        case SEARCHING:
            on_searching(rep, nav); break;
        default: printf("Invalid task!"); break;
    }

    if(nav->state.blocked_left)
        nav->prev_dist_wall = rep->laser->left_value;
    else if(nav->state.blocked_right){
        nav->prev_dist_wall = rep->laser->right_value;
    }
}

void update_nav_value(fix16_t *nav_val, fix16_t velocity) {
    fix16_t result = fix16_sub(*nav_val, fix16_div(velocity, fix16_from_int(PERIODS_PER_SEC)));
    if(fix16_to_int(result) < 0)
        *nav_val = fix16_from_int(0);
    else
        *nav_val = result;
}

//These functions run according to the current task being done.
void on_idle(rep_t *rep, nav_t *nav) {
    state_t state = nav->state;
    if (state.blocked_front) {
        if (state.blocked_right) {
            if (state.blocked_left)
                nav_turn_around(rep, nav);
            else
                nav_turn_left(rep, nav, FULL_TURN);
        }
        else
            nav_turn_right(rep, nav, FULL_TURN);
    }
    else
        nav_move_forward(rep, nav, fix16_from_int(25));
}

void on_turning(rep_t *rep, nav_t *nav){
    // Ugly workaround since rotation direction cannot be read from gyro
    if (rep->fc->yaw == rep->fc->duty->MIN_FC_DUTY)
        update_angle(nav, fix16_div(rep->fc->gyro, fix16_from_float(PERIODS_PER_SEC)));
    else
        update_angle(nav, - fix16_div(rep->fc->gyro, fix16_from_float(PERIODS_PER_SEC)));

    update_nav_value(&nav->val, rep->fc->gyro);
    if(fix16_to_int(nav->val) == 0){
        move_stop(rep->fc);
        nav->task = IDLE;
    }
}

void onTurnaround(rep_t *rep, nav_t *nav){

    update_nav_value(&nav->val, rep->fc->gyro);
    if(nav->val == 0){
        update_angle(nav, fix16_from_int(180));
        move_stop(rep->fc);
        nav->task = IDLE;
    }
}

void alignToWall(rep_t *rep, nav_t *nav){
    fix16_t diffWall = 0, directionDistance = fix16_div(rep->fc->vel->y, fix16_from_int(PERIODS_PER_SEC)), degreesToTurn = 0;

    if (nav->state.blocked_left){
        diffWall = fix16_from_int(rep->laser->left_value - nav->prev_dist_wall);
        nav->prev_dist_wall = rep->laser->left_value;
    }
    else if (nav->state.blocked_right){
        diffWall = fix16_from_int(rep->laser->right_value - nav->prev_dist_wall);
        nav->prev_dist_wall = rep->laser->right_value;
    }

    if(diffWall == fix16_from_int(1))
        diffWall = fix16_from_float(1);
    degreesToTurn = diffWall;  //fix16_rad_to_deg(fix16_asin(fix16_div(directionDistance, fix16_mul(fix16_sin(fix16_from_int(PERPENDICULAR)), diffWall)))); todo: Insert proper calculation

    if (diffWall < fix16_from_int(0) && rep->laser->left_value < MIN_RANGE){
        nav_turn_right(rep, nav, abs(fix16_to_int(degreesToTurn)));
    } else if (diffWall < fix16_from_int(0) && rep->laser->right_value < MIN_RANGE) {
        nav_turn_left(rep, nav, abs(fix16_to_int(degreesToTurn)));
    } else if (diffWall > fix16_from_int(0) && rep->laser->left_value < MIN_RANGE) {
        nav_turn_left(rep, nav, abs(fix16_to_int(degreesToTurn)));
    } else if (diffWall > fix16_from_int(0) && rep->laser->right_value < MIN_RANGE) {
        nav_turn_right(rep, nav, abs(fix16_to_int(degreesToTurn)));
    }
}

void on_move_forward(rep_t *rep, nav_t *nav){
    //calculate the current position from the current position and angle
    nav->posx = nav->posx + fix16_to_int(calculate_x_distance(nav->angle, fix16_div(rep->fc->vel->y,
                                                                                    fix16_from_int(PERIODS_PER_SEC))));
    nav->posy = nav->posy + fix16_to_int(calculate_y_distance(nav->angle, fix16_div(rep->fc->vel->y,
                                                                                    fix16_from_int(PERIODS_PER_SEC))));
    map_set_position(nav, VISITED);

    if(!check_alignment_wall(rep, nav))
        alignToWall(rep, nav);

    draw_map(rep, nav);
    if(fix16_to_int(nav->val) > 0 && nav->task == MOVEFORWARD)
        update_nav_value(&nav->val, rep->fc->gyro);
    if(nav->state.wall_front || fix16_to_int(nav->val) == 0){
        move_stop(rep->fc);
        nav->val = 0;
        nav->task = IDLE;
    }
}

void on_move_up(rep_t *rep, nav_t *nav){

    if (nav->state.ceiling){
        move_stop(rep->fc);
        nav->task = IDLE;
    }
}

void on_move_down(rep_t *rep, nav_t *nav){

    if(nav->state.ground){
        move_stop(rep->fc);
    }
}

void on_searching(rep_t *rep, nav_t *nav){
}

//These functions run whenever a new task is assigned
void nav_idle(rep_t *rep, nav_t *nav) {
    move_stop(rep->fc);
    nav->task = IDLE;
}

void nav_turn_left(rep_t *rep, nav_t *nav, uint8_t degrees){
    rotate_left(rep->fc);
    nav->val = fix16_from_int(degrees);
    nav->task = TURNING;
}

void nav_turn_right(rep_t *rep, nav_t *nav, uint8_t degrees){
    rotate_right(rep->fc);
    nav->val = fix16_from_int(degrees);
    nav->task = TURNING;
}

void nav_turn_around(rep_t *rep, nav_t *nav){
    rotate_right(rep->fc);
    nav->val = fix16_from_int(180); //Complete turnaround
    nav->task = TURNING;
}

void nav_move_forward(rep_t *rep, nav_t *nav, fix16_t distance){
    move_forward(rep->fc);
    nav->val = distance;
    nav->task = MOVEFORWARD;
}

void nav_move_up(rep_t *rep, nav_t *nav){
    move_up(rep->fc);
    nav->task = MOVEUP;
}

void nav_move_down(rep_t *rep, nav_t *nav){
    move_down(rep->fc);
    nav->task = MOVEDOWN;
}

void map_set_point(uint8_t x, uint8_t y,fieldstate_t field){
    map_write(x, y, field);
}

void map_set_position(nav_t *nav, fieldstate_t field) {
    pixel_coord_t pixel = align_to_pixel(nav->posx, nav->posy);

    map_write(pixel.x, pixel.y, field);
}

fieldstate_t map_check_point(uint8_t x, uint8_t y){
    return map_read(x, y);
}

fieldstate_t map_check_position(nav_t *nav) {
    pixel_coord_t pixel = align_to_pixel(nav->posx, nav->posy);

    return map_read(pixel.x, pixel.y);
}

uint8_t is_sonar_reliable(rep_t *rep, state_t state){
    /* finds the distance to the wall the drone is following
     * if blockedR returns 0, then the wall is to the left, otherwise the right
     * if the wall is on the left distToWall receives the distance to left, otherwise right */
    fix16_t distToWall = fix16_from_int(state.blocked_right ? rep->laser->left_value : rep->laser->right_value);

    /* find the distance to the wall with a 15 degree angle from front view */
    fix16_t calcSonarDistToWall = fix16_mul(distToWall/fix16_sin(fix16_from_float(fix16_rad_to_deg(SONAR_DEG))), fix16_sin(fix16_from_float(fix16_rad_to_deg(PERPENDICULAR))));

    /* if the measured value compared to the calculated value is less or equal to the allowed deviation of the sensor */
    if (fix16_abs(calcSonarDistToWall - fix16_from_int(rep->sonar->value) <= fix16_from_int(SENSOR_DEVIATION)) && rep->sonar->valid)
    {
        return 1;
    } else {
        return 0;
    }
}


#define MIN_TAKEACITON_RANGE 20
uint8_t check_alignment_wall(rep_t *rep, nav_t *nav){

    if (nav->state.blocked_right){

        if(nav->prev_dist_wall == 0){
            nav->prev_dist_wall = rep->laser->right_value;
            return 0;
        }
        
        if (nav->prev_dist_wall != rep->laser->right_value && rep->laser->right_value != LASER_MAX_RANGE){
            return 0;
        }
    } else if (rep->laser->left_value < MIN_RANGE){

        if(nav->prev_dist_wall == 0 && rep->laser->left_value != LASER_MAX_RANGE){
            nav->prev_dist_wall = rep->laser->left_value;
            return 0;
        }
        
        if (nav->prev_dist_wall != rep->laser->left_value && rep->laser->left_value != LASER_MAX_RANGE){
            return 0;
        }
    }

    return 1;
}

pixel_coord_t align_to_pixel(uint16_t x_coord, uint16_t y_coord) {
    uint8_t x_pixel, y_pixel;

    uint16_t y_low = (uint16_t) LOWEST_Y_ORG;
    uint16_t x_low = (uint16_t) LOWEST_X_ORG;

    if(x_coord < LOWEST_X_ORG)
    {
        WARNING(SENDER_MAP, "align_to_pixel: x-coord out of bounds");
        x_pixel = 0;
    }
    else if (x_coord > HIGHEST_X_ORG) {
        WARNING(SENDER_MAP, "align_to_pixel: x-coord out of bounds");
        x_pixel = MAP_HEIGHT;
    }
    else
        x_pixel = (x_coord - y_low) / CENTIMETERS_PR_PIXEL;

    if(y_coord < LOWEST_Y_ORG) {
        WARNING(SENDER_MAP, "align_to_pixel: y-coord out of bounds");
        y_pixel = 0;
    }
    else if(y_coord > HIGHEST_Y_ORG) {
        WARNING(SENDER_MAP, "align_to_pixel: y-coord out of bounds");
        y_pixel = MAP_WIDTH;
    }
    else
        y_pixel = (y_coord - x_low) / CENTIMETERS_PR_PIXEL;

    pixel_coord_t coord = { .x = x_pixel, .y = y_pixel};
    return coord;
}

void draw_front(rep_t *rep, nav_t *nav, fieldstate_t state) {
    //Calculate the x-offset with cos(angle) * laser
    fix16_t x_offset = calculate_x_distance(nav->angle, fix16_from_int(rep->laser->front_value));
    //Calculate the y-offset with sin(angle) * laser
    fix16_t y_offset = calculate_y_distance(nav->angle, fix16_from_int(rep->laser->front_value));

    //And convert to pixel-coord
    pixel_coord_t pix_win = align_to_pixel(nav->posx + fix16_to_int(x_offset), nav->posy + fix16_to_int(y_offset));

    map_write(pix_win.x, pix_win.y, state);
}

void draw_side(rep_t *rep, nav_t *nav, const int16_t side_offset, fieldstate_t state) {
    fix16_t x_offset = calculate_x_distance(nav->angle+side_offset, fix16_from_int(rep->laser->right_value));
    fix16_t y_offset = calculate_y_distance(nav->angle+side_offset, fix16_from_int(rep->laser->right_value));

    //And convert to pixel-coord
    pixel_coord_t pix_obst = align_to_pixel(nav->posx + fix16_to_int(x_offset), nav->posy + fix16_to_int(y_offset));

    map_write(pix_obst.x, pix_obst.y, state);
}

void draw_map(rep_t *rep, nav_t *nav){
    uint16_t mes_diff = rep->laser->front_value - rep->sonar->value;

    //Draw map in direct front of the drone
    if(mes_diff > WINDOW_RECON_THRESHOLD) {
        draw_front(rep, nav, WINDOW);
    }
    else if (rep->laser->front_value == rep->sonar->value) {
        draw_front(rep, nav, WALL);
    }

    if((rep->sonar->value < MIN_RANGE || rep->laser->front_value <= MIN_RANGE)
       && rep->laser->front_value != LASER_MAX_DISTANCE_CM && rep->sonar->value != 0) {
        uint16_t mes_diff = abs(rep->laser->front_value - rep->sonar->value);
        //Draw map in direct front of the drone
        if (mes_diff > WINDOW_RECON_THRESHOLD) {
            draw_front(rep, nav, WINDOW);
        } else {
            draw_front(rep, nav, WALL);
        }
    }

    if (nav->state.wall_right && rep->laser->right_value <= MIN_RANGE) {
        draw_side(rep, nav, DRONE_RIGHT_SIDE, WALL);
    }

    if (nav->state.wall_left && rep->laser->left_value <= MIN_RANGE) {
        draw_side(rep, nav, DRONE_LEFT_SIDE, WALL);
    }
}
