#include "nav.h"
#include "../task.h"

uint8_t CheckAWallF(rep_t *rep, state_t state){
    if((rep->sonar->valid) == 1 && (rep->sonar->value <= MIN_RANGE || rep->laser->front_value <= MIN_RANGE) && isSonarReliable(rep, state)){
        return 1;
    }
    return 0;
}

uint8_t CheckAWallL(rep_t *rep) {
    //Check map
    if (rep->laser->left_value <= MIN_RANGE) {
        return 1;
    }
    return 0;
}

uint8_t CheckAWallR(rep_t *rep) {
    //Check map
    if (rep->laser->right_value <= MIN_RANGE) {
        return 1;
    }
    return 0;
}

uint8_t CheckAGround(rep_t *rep) {
    if (rep->ir_bottom->value <= MIN_RANGE) {
        return 1;
    }
    return 0;
}

uint8_t CheckACeiling(rep_t *rep) {
    if (rep->ir_top->value <= MIN_RANGE) {
        return 1;
    }
    return 0;
}

uint8_t CheckAWinF(rep_t *rep, state_t state) {
    if (rep->sonar->valid && rep->laser->left_value >= MIN_RANGE && rep->sonar->value <= MIN_RANGE && isSonarReliable(rep, state)) {
        return 1;
    }
    return 0;
}

uint8_t CheckAWinL(rep_t *rep) {
    if (rep->laser->left_value >= MIN_RANGE) {
        //Cross reference map and turn to check with sonar if necessary
    }
    return 0;
}

uint8_t CheckAWinR(rep_t *rep) {
    if (rep->laser->right_value >= MIN_RANGE) {
        //Cross reference map and turn to check with sonar if necessary
    }
    return 0;
}

uint8_t CheckBlockedF(state_t *state){
    if(state->AWallF || state->AWinF){
        return 1;
    }
    return 0;
}

uint8_t CheckBlockedR(state_t *state){
    if(state->AWallR || state->AWinR){
        return 1;
    }
    return 0;
}

uint8_t CheckBlockedL(state_t *state){
    if(state->AWallL || state->AWinL){
        return 1;
    }
    return 0;
}

void update_state(state_t *state, rep_t *rep){
    state->ACeiling = CheckACeiling(rep);
    state->AGround =  CheckAGround(rep);
    state->AWallF = CheckAWallF(rep, *state);
    state->AWallL = CheckAWallL(rep);
    state->AWallR = CheckAWallR(rep);
    state->AWinF = CheckAWinF(rep, *state);
    state->AWinL = CheckAWinL(rep);
    state->AWinR = CheckAWinR(rep);
    state->BlockedF = CheckBlockedF(state);
    state->BlockedL = CheckBlockedL(state);
    state->BlockedR = CheckBlockedR(state);
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

    //Start in the middle of the map
    nav->posx = MAP_WIDTH/2;
    nav->posy = MAP_HEIGHT/2;

    *((uint16_t*) &nav->state) &= 0x0000; //hacky (albeit quick) way to set all states to zero

    nav->timer = 0;
}

/**
 * Main function of the navigation unit - entry-point for the scheduler
 * @param rep
 * @param nav
 */
void navigation(rep_t *rep, nav_t *nav){ //:todo make rep and nav one unit

    update_state(&nav->state, rep);
    //what were we doing?
    task_t currenttask = nav->task;
    //printf("Task: %d\n", currenttask);
    switch(currenttask){
        case IDLE: onIdle(rep, nav); break;
        case TURNLEFT: onTurnleft(rep, nav); break;
        case TURNRIGHT: onTurnright(rep, nav); break;
        case TURNAROUND: onTurnaround(rep, nav); break;
        case MOVEFORWARD: onMoveforward(rep, nav); break;
        case MOVEUP: onMoveup(rep, nav); break;
        case MOVEDOWN: onMovedown(rep, nav); break;
        case SEARCHING: onSearching(rep, nav); break;
        default: printf("Invalid task!"); break;
    }
    //printf("THE STATE IS: %d\n", nav->state);
}

/**
 * Takes in the newest measured data.
 * @return the updated representation struct
 *
rep_t update(rep_t *rep){
    rep_t rep;
    rep.fc = rep->fc;
    rep.laser = rep->laser;
    rep.sonar = sonar;
    rep.ir_top = ir_top;
    rep.ir_bottom = ir_bottom;

    return rep;
}*/

//These functions run according to the current task being done.
void onIdle(rep_t *rep, nav_t *nav) {
    state_t state = nav->state;
    if (state.BlockedF) {
        if (state.BlockedR) {
            if (state.BlockedL)
                Turnaround(rep, nav);
            else
                Turnleft(rep,nav, FULL_TURN);
        }
        else
            Turnright(rep, nav, FULL_TURN);
    }
    else
        Moveforward(rep, nav);
}

void onTurnleft(rep_t *rep, nav_t *nav){
    /* Check if done turning through nav->val
     * if done then set task to IDLE or start new one.
     * Set angle aswell, on finished turning maybe?
     */
    //todo:Udkommenter dette når gyro er implementeret.
    // nav->val = nav->val - (rep->fc->gyro / 10) //Gyro giver angles/s så vi /10 for at få det i angles/period
    if(nav->val == 0){
        move_stop(rep->fc);
        nav->task = IDLE;
    }
}

void onTurnright(rep_t *rep, nav_t *nav){
    /* Check if done turning through nav->val
     * if done then set task to IDLE or start new one.
     * Set angle aswell, on finished turning maybe?
     */
    //todo:Udkommenter dette når gyro er implementeret.
    // nav->val = nav->val - (rep->fc->gyro / 10) //Gyro giver angles/s så vi /10 for at få det i angles/period

    if(nav->val == 0){
        move_stop(rep->fc);
        nav->task = IDLE;
    }
}

void onTurnaround(rep_t *rep, nav_t *nav){
    /* Check if done turning through nav->val
     * if done then set task to IDLE or start new one.
     * Set angle aswell, on finished turning maybe?
     * nav-val er her mængden af grader der skal drejes.
     */

    //todo:Udkommenter dette når gyro er implementeret.
    // nav->val = nav->val - (rep->fc->gyro / 10) //Gyro giver angles/s så vi /10 for at få det i angles/period
    if(nav->val == 0){
        move_stop(rep->fc);
        nav->task = IDLE;
    }
}

void onMoveforward(rep_t *rep, nav_t *nav){
    /* Check AWallF and if no then using nav->val is possible to avoid moving too far without drawing on the map
     * or simply draw on the map here
     * In either case set task to IDLE or start new one when done.
     */

    if ((nav->state.AWallF || nav->state.AWinF) && (rep->laser->front_value <= MIN_RANGE || rep->sonar->value <= MIN_RANGE) && isSonarReliable(rep, nav->state)) {
        fix16_t x_offset = fix16_mul(fix16_cos(fix16_from_int(nav->angle)), fix16_from_int(rep->laser->front_value));
        fix16_t y_offset = fix16_mul(fix16_sin(fix16_from_int(nav->angle)), fix16_from_int(rep->laser->front_value));

        if (rep->laser->front_value > (rep->sonar->value + MIN_DIFF_LASER_SONAR))
            map_write(nav->posx+fix16_to_int(x_offset), nav->posy+fix16_to_int(y_offset), WINDOW);
        else
            map_write(nav->posx+fix16_to_int(x_offset), nav->posy+fix16_to_int(y_offset), WALL);
    }

    if (nav->state.AWallR && rep->laser->right_value <= MIN_RANGE)
    {
        fix16_t x_offset = fix16_mul(fix16_cos(fix16_from_int(nav->angle + DRONE_RIGHT_SIDE)), fix16_from_int(rep->laser->right_value));
        fix16_t y_offset = fix16_mul(fix16_sin(fix16_from_int(nav->angle + DRONE_RIGHT_SIDE)), fix16_from_int(rep->laser->right_value));

        map_write(nav->posx+fix16_to_int(x_offset), nav->posy+fix16_to_int(y_offset), WALL);
    }

    if (nav->state.AWallL && rep->laser->left_value <= MIN_RANGE)
    {
        fix16_t x_offset = fix16_mul(fix16_cos(fix16_from_int(nav->angle + DRONE_LEFT_SIDE)), fix16_from_int(rep->laser->left_value));
        fix16_t y_offset = fix16_mul(fix16_sin(fix16_from_int(nav->angle + DRONE_LEFT_SIDE)), fix16_from_int(rep->laser->left_value));

        map_write(nav->posx+fix16_to_int(x_offset), nav->posy+fix16_to_int(y_offset), WALL);
    }

    if(nav->val > 0)
        nav->val = nav->val - (uint16_t )(rep->fc->vel->y/10); //todo: Change this please. The idea is that nav->val is as the remaining amount of cm needed to be moved. And rep->fc->vel-y / 10 is the amount of cm moved since last period
    if(nav->state.AWallF){
        move_stop(rep->fc);
        nav->val = 0;
        nav->task = IDLE;
    }
}

void onMoveup(rep_t *rep, nav_t *nav){
    /*
     * Bare flyt indtil vi har nået loftet?
     */
    if (nav->state.ACeiling){
        move_stop(rep->fc);
        nav->task = IDLE;
    }
}

void onMovedown(rep_t *rep, nav_t *nav){
    /* Check AGround if no then maybe nav->val
     * Bare flyt indtil vi har nået jorden?
     */
    if(nav->state.AGround){
        move_stop(rep->fc);
    }
}

void onSearching(rep_t *rep, nav_t *nav){
    /*
     * Kode til at align med væg??
     * Set to IDLE
     */
}

//These functions run whenever a new task is assigned
void Idle(rep_t *rep, nav_t *nav) {
    move_stop(rep->fc);
    nav->task = IDLE;
}

void Turnleft(rep_t *rep, nav_t *nav, uint8_t degrees){
    rotate_left(rep->fc);
    nav->val = degrees;
    nav->task = TURNLEFT;
}

void Turnright(rep_t *rep, nav_t *nav, uint8_t degrees){
    rotate_right(rep->fc);
    nav->val = degrees;
    nav->task = TURNRIGHT;
}

void Turnaround(rep_t *rep, nav_t *nav){
    rotate_right(rep->fc); //todo: Must happen two times
    nav->val = 180; //Complete turnaround
    nav->task = TURNRIGHT;
}

void Moveforward(rep_t *rep, nav_t *nav){
    move_forward(rep->fc);
    nav->task = MOVEFORWARD;
}

void Moveup(rep_t *rep, nav_t *nav){
    move_up(rep->fc);
    nav->task = MOVEUP;
}

void Movedown(rep_t *rep, nav_t *nav){
    move_down(rep->fc);
    nav->task = MOVEDOWN;
}

void Searching(rep_t *rep, nav_t *nav){
    //todo: needs implementing
    nav->task = SEARCHING;
}

void Map_set_point(nav_t *nav, uint8_t x, uint8_t y,fieldstate_t field){
}

fieldstate_t Map_Check_point(nav_t nav, uint8_t x, uint8_t y){
    return UNVISITED;
}

uint8_t isSonarReliable(rep_t *rep, state_t state){
    /* finds the distance to the wall the drone is following
     * if blockedR returns 0, then the wall is to the left, otherwise the right
     * if the wall is on the left distToWall receives the distance to left, otherwise right */
    fix16_t distToWall = fix16_from_int(state.BlockedR ? rep->laser->left_value : rep->laser->right_value);

    /* find the distance to the wall with a 15 degree angle from front view */
    fix16_t calcSonarDistToWall = fix16_mul(distToWall/fix16_sin(fix16_from_float(fix16_rad_to_deg(SONAR_DEG))), fix16_sin(fix16_from_float(fix16_rad_to_deg(PERPENDICULAR))));

    /* if the measured value compared to the calculated value is less or equal to the allowed deviation of the sensor */
    if (fix16_abs(calcSonarDistToWall - fix16_from_int(rep->sonar->value) <= fix16_from_int(SONAR_DEVIATION)) && rep->sonar->valid)
    {
        return 1;
    } else {
        return 0;
    }
}


