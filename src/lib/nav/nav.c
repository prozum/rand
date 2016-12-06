#include "nav.h"


/**
 * This function is called by the scheduler every period
 */
void navigation(rep_t *rep, nav_t *nav){
    //what were we doing?
    task_t currenttask = nav->task;
    if (currenttask == idle) {
        /*check if anything is near
         * if nothing is near, check if area is discovered
         * if not, turn around to explore,
         * else start moving
         */
        onIdle();
    }else if(currenttask == turnleft){
         /*
          * Do something
          */
        onTurnleft();
    }else if(currenttask == turnright){
        /*
         * Do something
         */
        onTurnright();
    }else if(currenttask == turnaround){
        /*
         * Do something
         */
        onTurnaround();
    }else if(currenttask == movedown){
        /*
         * Do something
         */
        onMovedown();
    }else if(currenttask == moveup){
        /*
         * Do something
         */
        onMoveup();
    }else if(currenttask == moveforward){
        /*
         * Do something
         */
        onMoveforward();
    }else if(currenttask == searching){
        /*
         * Do something
         */
        onSearching();
    }
    /* this should stop the drone if there's less or equal to 120 cm forward */
    if ( (rep->sonar->valid) == 1 && (rep->sonar->value <= MIN_RANGE || rep->laser->front_value <= MIN_RANGE))
        move_stop(rep->fc);
    
    
}

void init_rep(fc_t *fc, laser_t *laser, sonar_t *sonar, ir_t *irTop, ir_t *irBottom, rep_t *rep){
    rep->fc = fc;
    rep->laser = laser;
    rep->sonar = sonar;
    rep->ir_top = irTop;
    rep->ir_bottom = irBottom;
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

uint8_t CheckAWallF(rep_t *rep){
    if((rep->sonar->valid) == 1 && (rep->sonar->value <= 40 || rep->laser->front_value <= 40)){
        return 1;
    }
    return 0;
}

uint8_t CheckAWallL(rep_t *rep) {
    //Check map
    if (rep->laser->left_value <= 40) {
        return 1;
    }
    return 0;
}

uint8_t CheckAWallR(rep_t *rep) {
    //Check map
    if (rep->laser->right_value <= 40) {
        return 1;
    }
    return 0;
}

uint8_t CheckAGround(rep_t *rep) {
    if (rep->ir_bottom->value <= 40) {
        return 1;
    }
    return 0;
}

uint8_t CheckACeiling(rep_t *rep) {
    if (rep->ir_top->value <= 40) {
        return 1;
    }
    return 0;
}

uint8_t CheckAWinF(rep_t *rep) {
    if (rep->sonar->valid && rep->laser->left_value >= 60 && rep->sonar->value <= 40) {
        return 1;
    }
    return 0;
}

uint8_t CheckAWinL(rep_t *rep) {
    if (rep->laser->left_value >= 40) {
        //Cross reference map and turn to check with sonar if necessary
    }
    return 0;
}

uint8_t CheckAWinR(rep_t *rep) {
    if (rep->laser->right_value >= 40) {
        //Cross reference map and turn to check with sonar if necessary
    }
    return 0;
}

void update_state(state_t *state, rep_t *rep){
    state->ACeiling = CheckACeiling(rep);
    state->AGround =  CheckAGround(rep);
    state->AWallF = CheckAWallF(rep);
    state->AWallL = CheckAWallL(rep);
    state->AWallR = CheckAWallR(rep);
    state->AWinF = CheckAWinF(rep);
    state->AWinL = CheckAWinL(rep);
    state->AWinR = CheckAWinR(rep);
}

void onIdle(){

}

void onTurnleft(){

}

void onTurnright(){

}

void onTurnaround(){

}

void onMoveforward(){

}

void onMoveup(){

}

void onMovedown(){

}

void onSearching(){

}



