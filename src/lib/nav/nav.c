#include "nav.h"

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

uint8_t CheckBlockedF(state_t state){
    if(state.AWallF || state.AWinF){
        return 1;
    }
    return 0;
}

uint8_t CheckBlockedR(state_t state){
    if(state.AWallR || state.AWinR){
        return 1;
    }
    return 0;
}

uint8_t CheckBlockedL(state_t state){
    if(state.AWallL || state.AWinL){
        return 1;
    }
    return 0;
}

void update_state(state_t state, rep_t *rep){
    state.ACeiling = CheckACeiling(rep);
    state.AGround =  CheckAGround(rep);
    state.AWallF = CheckAWallF(rep, state);
    state.AWallL = CheckAWallL(rep);
    state.AWallR = CheckAWallR(rep);
    state.AWinF = CheckAWinF(rep, state);
    state.AWinL = CheckAWinL(rep);
    state.AWinR = CheckAWinR(rep);
    state.BlockedF = CheckBlockedF(state);
    state.BlockedL = CheckBlockedL(state);
    state.BlockedR = CheckBlockedR(state);
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
    nav->posx = 0;
    nav->posy = 0;

    *((uint16_t*) &nav->state) &= 0x0000; //hacky (albeit quick) way to set all states to zero

    nav->timer = 0;
}

/**
 * Main function of the navigation unit - entry-point for the scheduler
 * @param rep
 * @param nav
 */
void navigation(rep_t *rep, nav_t *nav){ //:todo make rep and nav one unit

    update_state(nav->state, rep);

    //what were we doing?
    task_t currenttask = nav->task;
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
                Turnleft(rep,nav);
        }
        else
            Turnright(rep, nav);
    }
    else
        Moveforward(rep, nav);
}

void onTurnleft(rep_t *rep, nav_t *nav){
    /* Check if done turning through nav->val
     * if done then set task to IDLE or start new one.
     */
}

void onTurnright(rep_t *rep, nav_t *nav){
    /* Check if done turning through nav->val
     * if done then set task to IDLE or start new one.
     */
}

void onTurnaround(rep_t *rep, nav_t *nav){
    /* Check if done turning through nav->val
     * if done then set task to IDLE or start new one.
     */
}

void onMoveforward(rep_t *rep, nav_t *nav){
    /* Check AWallF and if no then using nav->val is possible to avoid moving too far without drawing on the map'
     * or simply draw on the map here
     * In either case set task to IDLE or start new one when done.
     */

    if ((nav->state.AWallF || nav->state.AWinF) && (rep->laser->front_value <= MIN_RANGE || rep->sonar->value <= MIN_RANGE) && isSonarReliable(rep, nav->state)) {
        fix16_t x_offset = fix16_mul(fix16_cos(nav->angle), fix16_from_int(rep->laser->front_value));
        fix16_t y_offset = fix16_mul(fix16_sin(nav->angle), fix16_from_int(rep->laser->front_value));
        
        if (rep->laser->front_value > (rep->sonar->value + MIN_DIFF_LASER_SONAR))
            map_write(nav->posx+fix16_to_int(x_offset), nav->posy+fix16_to_int(y_offset), TRANSPARENT);
        else
            map_write(nav->posx+fix16_to_int(x_offset), nav->posy+fix16_to_int(y_offset), WALL);
    }
}

void onMoveup(rep_t *rep, nav_t *nav){
    /* Check ACeiling if no then maybe nav->val
     *
     */
}

void onMovedown(rep_t *rep, nav_t *nav){
    /* Check AGround if no then maybe nav->val
     *
     */
}

void onSearching(rep_t *rep, nav_t *nav){
    /* Haven't the foggiest
     * Set to IDLE
     */
}

//These functions run whenever a new task is assigned
void Idle(rep_t *rep, nav_t *nav) {
    //move_stop(rep->fc); todo: uncomment when FC is initialized
    nav->task = IDLE;
}

void Turnleft(rep_t *rep, nav_t *nav){
    //rotate_left(rep->fc);
    nav->task = TURNLEFT;
}

void Turnright(rep_t *rep, nav_t *nav){
    //rotate_right(rep->fc);
    nav->task = TURNRIGHT;
}

void Turnaround(rep_t *rep, nav_t *nav){
    //rotate_right(rep->fc); //todo: Must happen two times
    nav->task = TURNRIGHT;
}

void Moveforward(rep_t *rep, nav_t *nav){
    //move_forward(rep->fc);
    nav->task = MOVEFORWARD;
}

void Moveup(rep_t *rep, nav_t *nav){
    //move_up(rep->fc);
    nav->task = MOVEUP;
}

void Movedown(rep_t *rep, nav_t *nav){
    //move_down(rep->fc);
    nav->task = MOVEDOWN;
}

void Searching(rep_t *rep, nav_t *nav){
    //todo: needs implementing
    nav->task = SEARCHING;
}

uint8_t isSonarReliable(rep_t *rep, state_t state){
    /* finds the distance to the wall the drone is following 
     * if blockedR returns 0, then the wall is to the left, otherwise the right
     * if the wall is on the left distToWall receives the distance to left, otherwise right */
    fix16_t distToWall = fix16_from_int(state.BlockedR ? rep->laser->left_value : rep->laser->right_value);
    
    /* find the distance to the wall with a 15 degree angle from front view */
    fix16_t calcSonarDistToWall = fix16_mul(distToWall/fix16_sin(fix16_from_float(fix16_rad_to_deg(SONAR_DEG))), fix16_sin(fix16_from_float(fix16_rad_to_deg(PERPENDICULAR))));

    /* if the measured value compared to the calculated value is less or equal to the allowed deviation of the sensor */
    if (fix16_abs(calcSonarDistToWall - rep->sonar->value <= SONAR_DEVIATION) && rep->sonar->valid)
    {
        return 1;
    } else {
        return 0;
    }
}


