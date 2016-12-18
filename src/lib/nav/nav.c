#include "nav.h"
#include "task.h"
#include <math.h>
#include <stdbool.h>

//! Defines the lowest and highest accepted world-position on the internal drone map
#define LOWEST_Y_ORG 0
#define HIGHEST_Y_ORG MAP_HEIGHT * CENTIMETERS_PR_PIXEL
#define LOWEST_X_ORG 0
#define HIGHEST_X_ORG MAP_WIDTH * CENTIMETERS_PR_PIXEL

#define M_PI 3.14159265358979323846

fix16_t calc_y_dist(fix16_t angle, fix16_t distance) {
    fix16_t sin_angle = fix16_sin(angle);
    return fix16_mul(sin_angle, distance);
}

fix16_t calc_x_dist(fix16_t angle, fix16_t distance) {
    fix16_t cos_angle = fix16_cos(angle);
    return fix16_mul(cos_angle, distance);
}

void update_angle(nav_t *nav, fix16_t degrees) {
    nav->angle = fix16_add(nav->angle, degrees);
    if (nav->angle > fix16_from_dbl(M_PI * 2)) {
        nav->angle = fix16_mod(nav->angle, fix16_from_dbl(M_PI * 2));
    } else if (nav->angle < fix16_from_int(0)) {
        nav->angle = fix16_add(fix16_from_dbl(M_PI * 2), nav->angle);
    }
}

uint8_t check_wall_front(rep_t *rep, state_t state){
    if((rep->sonar->valid) == 1 && (rep->sonar->value <= MIN_RANGE || rep->laser->val_front <= MIN_RANGE)) {
        // &&   is_sonar_reliable(rep, state)){
        return 1;
    }
    return 0;
}

uint8_t check_wall_left(rep_t *rep) {
    //Check map
    if (rep->laser->val_left <= MIN_RANGE) {
        return 1;
    }
    return 0;
}

uint8_t check_wall_right(rep_t *rep) {
    //Check map
    if (rep->laser->val_right <= MIN_RANGE) {
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
    if (rep->sonar->valid && rep->laser->val_left >= MIN_RANGE && rep->sonar->value <= MIN_RANGE &&
            is_sonar_reliable(rep, state)) {
        return 1;
    }
    return 0;
}

uint8_t check_win_left(rep_t *rep) {
    if (rep->laser->val_left >= MIN_RANGE) {
        //Cross reference map and turn to check with sonar if necessary
    }
    return 0;
}

uint8_t check_win_right(rep_t *rep) {
    if (rep->laser->val_right >= MIN_RANGE) {
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

void init_rep(fc_t *fc, laser_t *laser, sonar_t *sonar, ir_t *ir_top, ir_t *ir_bottom, rep_t *rep){
    if(!rep)
        rep = malloc(sizeof(rep));

    rep->fc = fc;
    rep->laser = laser;
    rep->sonar = sonar;
    rep->ir_top = ir_top;
    rep->ir_bottom = ir_bottom;
}

void init_nav(nav_t *nav){
    if(!nav)
        nav = malloc(sizeof(nav_t));

    nav->task = IDLE;
    nav->val = fix16_from_int(0);
    nav->angle = fix16_from_int(0);
    nav->prev_dist_wall = 0;

    // Assume es drone to start in the middle of the room.
    nav->posx = MAP_MIDDLE * CENTIMETERS_PR_PIXEL;
    nav->posy = MAP_MIDDLE * CENTIMETERS_PR_PIXEL;

    *((uint16_t*) &nav->state) &= 0x0000; // Hacky (albeit quick) way to set all states to zero

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
        nav->prev_dist_wall = rep->laser->val_left;
    else if(nav->state.blocked_right){
        nav->prev_dist_wall = rep->laser->val_right;
    }
}

void update_nav_value(fix16_t *nav_val, fix16_t velocity) {
    fix16_t result;
    if (velocity > fix16_from_int(0)) {
        result = fix16_sub(*nav_val, fix16_mul(velocity, fix16_from_float(PERIOD_SECONDS)));
    } else {
        result = fix16_add(*nav_val, fix16_mul(velocity, fix16_from_float(PERIOD_SECONDS)));
    }

    if(result <= 0)
        *nav_val = fix16_from_int(0);
    else
        *nav_val = result;
}

// These functions run according to the current task being done.
void on_idle(rep_t *rep, nav_t *nav) {
    state_t state = nav->state;
    if (state.blocked_front) {
        if (state.blocked_right) {
            if (state.blocked_left)
                nav_turn_around(rep, nav);
            else
                nav_turn_left(rep, nav, full_turn);
        }
        else
            nav_turn_right(rep, nav, full_turn);
    }
    else
        nav_move_forward(rep, nav, fix16_from_int(25));
}

void on_turning(rep_t *rep, nav_t *nav){
    fix16_t moved_degrees = fix16_mul(rep->fc->gyro, fix16_from_float(PERIOD_SECONDS));

    update_angle(nav, moved_degrees);

    draw_map(rep, nav);
    update_nav_value(&nav->val, rep->fc->gyro);

    if(nav->val == 0){
        move_stop(rep->fc);
        nav->task = IDLE;
    }
}

void on_turnaround(rep_t *rep, nav_t *nav){

    update_nav_value(&nav->val, rep->fc->gyro);

    if(nav->val == 0){
        update_angle(nav, fix16_from_float(M_PI));
        move_stop(rep->fc);
        nav->task = IDLE;
    }
}

void align_to_wall(rep_t *rep, nav_t *nav){
    fix16_t diff_wall = 0, degrees_to_turn = 0;
    //fix16_t drift = fix16_mul(rep->fc->vel->y, fix16_from_float(PERIOD_SECONDS));

    if (nav->state.blocked_left){
        diff_wall = fix16_from_int(rep->laser->val_left - nav->prev_dist_wall);
        nav->prev_dist_wall = rep->laser->val_left;
    }
    else if (nav->state.blocked_right){
        diff_wall = fix16_from_int(rep->laser->val_right - nav->prev_dist_wall);
        nav->prev_dist_wall = rep->laser->val_right;
    }

    degrees_to_turn = diff_wall;  //fix16_rad_to_deg(fix16_asin(fix16_div(drift, fix16_mul(fix16_sin(fix16_from_int(PERPENDICULAR_RAD)), diffWall)))); todo: Insert proper calculation

    if (diff_wall < 0 && rep->laser->val_left < MIN_RANGE){
        nav_turn_right(rep, nav, abs(fix16_to_int(degrees_to_turn)));
    } else if (diff_wall < 0 && rep->laser->val_right < MIN_RANGE) {
        nav_turn_left(rep, nav, abs(fix16_to_int(degrees_to_turn)));
    } else if (diff_wall > 0 && rep->laser->val_left < MIN_RANGE) {
        nav_turn_left(rep, nav, abs(fix16_to_int(degrees_to_turn)));
    } else if (diff_wall > 0 && rep->laser->val_right < MIN_RANGE) {
        nav_turn_right(rep, nav, abs(fix16_to_int(degrees_to_turn)));
    }
}

void on_move_forward(rep_t *rep, nav_t *nav){
    fix16_t dist = fix16_mul(rep->fc->vel->y, fix16_from_float(PERIOD_SECONDS));

    // Calculate the current position from the current position and angle
    nav->posx = (uint16_t) (nav->posx + fix16_to_int(calc_x_dist(nav->angle, dist)));
    nav->posy = (uint16_t) (nav->posy + fix16_to_int(calc_y_dist(nav->angle, dist)));
    map_set_position(nav, VISITED);

    //if(!check_alignment_wall(rep, nav))
    //    align_to_wall(rep, nav);

    draw_map(rep, nav);
    if(fix16_to_int(nav->val) > 0)
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

void nav_turn_left(rep_t *rep, nav_t *nav, fix16_t angle){
    rotate_left(rep->fc);
    nav->val = angle;
    nav->task = TURNING;
}

void nav_turn_right(rep_t *rep, nav_t *nav, fix16_t angle){
    rotate_right(rep->fc);
    nav->val = angle;
    nav->task = TURNING;
}

void nav_turn_around(rep_t *rep, nav_t *nav){
    rotate_right(rep->fc);
    nav->val = fix16_pi; //Complete turnaround
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
    map_coord_t pixel = align_to_map(nav->posx, nav->posy);

    if (pixel.valid)
        map_write(pixel.x, pixel.y, field);
}

fieldstate_t map_check_point(uint8_t x, uint8_t y){
    return map_read(x, y);
}

fieldstate_t map_check_position(nav_t *nav) {
    map_coord_t pixel = align_to_map(nav->posx, nav->posy);

    return map_read(pixel.x, pixel.y);
}

uint8_t is_sonar_reliable(rep_t *rep, state_t state){
    /* Finds the distance to the wall the drone is following
     * If blockedR returns 0, then the wall is to the left, otherwise the right
     * If the wall is on the left dist_to_wall receives the distance to left, otherwise right */
    fix16_t dist_to_wall = fix16_from_int(state.blocked_right ? rep->laser->val_left : rep->laser->val_right);

    /* Find the distance to the wall with a 15 degree angle from front view
     * by using b = a (sin(B) / sin(A)) */
    fix16_t calc_sonar_dist_to_wall = fix16_mul(dist_to_wall, sonar_reliable_constant);

    /* If the measured value compared to the calculated value is less or equal to the allowed deviation of the sensor */
    if (fix16_abs(fix16_sub(calc_sonar_dist_to_wall, fix16_from_int(rep->sonar->value)) <= fix16_from_int(SENSOR_DEVIATION)) && rep->sonar->valid)
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
            nav->prev_dist_wall = rep->laser->val_right;
            return 0;
        }
        
        if (nav->prev_dist_wall != rep->laser->val_right && rep->laser->val_right != LASER_MAX_RANGE){
            return 0;
        }
    } else if (rep->laser->val_left < MIN_RANGE){

        if(nav->prev_dist_wall == 0 && rep->laser->val_left != LASER_MAX_RANGE){
            nav->prev_dist_wall = rep->laser->val_left;
            return 0;
        }
        
        if (nav->prev_dist_wall != rep->laser->val_left && rep->laser->val_left != LASER_MAX_RANGE){
            return 0;
        }
    }

    return 1;
}

map_coord_t align_to_map(uint16_t x_coord, uint16_t y_coord) {

    uint16_t y_low = (uint16_t) LOWEST_Y_ORG;
    uint16_t x_low = (uint16_t) LOWEST_X_ORG;

    map_coord_t res;
    res.valid = true;

    uint8_t x_mod = (x_coord - x_low) % CENTIMETERS_PR_PIXEL;
    if (x_mod >= CENTIMETERS_PR_PIXEL / 2) {
        res.x = (x_coord - x_low) / CENTIMETERS_PR_PIXEL + 1;
    } else {
        res.x = (x_coord - x_low) / CENTIMETERS_PR_PIXEL;
    }

    if(res.x < 0)
    {
        WARNING(SENDER_MAP, "align_to_map: x-coord out of bounds");
        res.valid = false;
        res.x = 0;
    }
    else if (res.x >= MAP_WIDTH) {
        WARNING(SENDER_MAP, "align_to_map: x-coord out of bounds");
        res.valid = false;
        res.x = MAP_WIDTH;
    }

    uint8_t y_mod = (y_coord - y_low) % CENTIMETERS_PR_PIXEL;
    if (y_mod >= CENTIMETERS_PR_PIXEL / 2) {
        res.y = (y_coord - y_low) / CENTIMETERS_PR_PIXEL + 1;
    } else {
        res.y = (y_coord - y_low) / CENTIMETERS_PR_PIXEL;
    }

    if(res.y < 0) {
        WARNING(SENDER_MAP, "align_to_map: y-coord out of bounds");
        res.valid = false;
        res.y = 0;
    }
    else if(res.y >= MAP_HEIGHT) {
        WARNING(SENDER_MAP, "align_to_map: y-coord out of bounds");
        res.valid = false;
        res.y = MAP_HEIGHT;
    }

    return res;
}

void draw_obstacle(uint16_t val, nav_t *nav, const fix16_t side_offset, fieldstate_t state) {
    fix16_t fixed_val = fix16_from_int(val);

    fix16_t x_offset = calc_x_dist(fix16_add(nav->angle, side_offset), fixed_val);
    fix16_t y_offset = calc_y_dist(fix16_add(nav->angle, side_offset), fixed_val);

    // And convert to pixel-coord
    map_coord_t pix_obst  = align_to_map(nav->posx + fix16_to_int(x_offset), nav->posy + fix16_to_int(y_offset));
    map_coord_t pix_drone  = align_to_map(nav->posx, nav->posy);

    // Draw obstacle
    if (pix_obst.valid)
        map_write(pix_obst.x, pix_obst.y, state);
    //map_write_line(pix_drone, pix_obst, VISITED);

    /*
    fix16_t D = fix16_sub(
            fix16_mul(fix16_from_int(2), y_offset),
            x_offset);

    fix16_t y = fix16_from_int(fix16_from_int(0));

    fix16_t x_start;
    fix16_t x_end;
    fix16_t x_inc;

    if (x_offset >= 0) {
        x_start = fix16_from_int(0);
        x_end = fix16_sub(x_offset, fix16_from_int(CENTIMETERS_PR_PIXEL));
        x_inc = fix16_from_int(CENTIMETERS_PR_PIXEL);
    } else if (x_offset < 0) {
        x_start = fix16_sub(x_offset, fix16_from_int(CENTIMETERS_PR_PIXEL));
        x_end = fix16_from_int(0);
        x_inc = fix16_from_int(- CENTIMETERS_PR_PIXEL);
        return;
    } else {
        return;
    }

    for (fix16_t x = x_start; x > x_end; x = fix16_add(x, x_inc)) {
        map_coord_t pix_visited  = align_to_map(nav->posx + fix16_to_int(x), nav->posy + fix16_to_int(y));
        map_write(pix_visited.x, pix_visited.y, VISITED);

        if (D >= fix16_from_int(0)) {
            y = fix16_add(y, fix16_one);
            D = fix16_sub(D, fix16_one);
        }
        D = fix16_add(D, y_offset);
    }
    */
}

void draw_map(rep_t *rep, nav_t *nav){

    if((rep->sonar->value < MIN_DRAW_RANGE || rep->laser->val_front <= MIN_DRAW_RANGE)
       && rep->laser->val_front != LASER_MAX_DISTANCE_CM && rep->sonar->value != 0) {
        uint16_t mes_diff = abs(rep->laser->val_front - rep->sonar->value);
        // Draw map in direct front of the drone
        if (mes_diff > WINDOW_RECON_THRESHOLD) {
            //draw_obstacle(rep->sonar->value, nav, 0, WINDOW);
        } else {
            //draw_obstacle(rep->laser->val_front, nav, 0, WALL);
        }
    }

    if (rep->laser->val_right <= MIN_DRAW_RANGE) {
        draw_obstacle(rep->laser->val_right, nav, drone_right_side, WALL);
    }

    if (rep->laser->val_left <= MIN_DRAW_RANGE) {
        //draw_obstacle(rep->laser->val_left, nav, drone_left_side, WALL);
    }
}
