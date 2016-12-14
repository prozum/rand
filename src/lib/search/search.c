#include "search.h"
#include "nav/nav.h"
#include "task.h"

/// This function finds the shortest path to a location.
/// \param nav
/// \param x
/// \param y
search_node_t* findpath(nav_t *nav){
    search_t *search = &nav->search_data;
    if(!search->active){
        search_node_t start;
        addnode(search, start, OPEN);

        map_coord_t startpos = align_to_map(nav->posx, nav->posy);
        start.pos = startpos;

        start.parent = NULL;
        start.gscore = 0;
        start.fscore = estimate(&start, search->goal);
    }
    uint8_t i;
    for(i = 0; i < ALLOWED_SEARCH_ITERATIONS; i++){
        search_node_t *current;
        *current = lowestf(search);
        if(current == NULL){
            search->active = 0;
            return NULL; //open set is empty (failure)
        }
        if ((current->pos.x == search->goal.x) && (current->pos.y == search->goal.y)){
            return current; //success
        }
        current = close_node(search, current); //current will now point to a node in the closed set
        add_neighbours(search, current);//estimate and add all relevant neighbours to the open set
    }
    return NULL; //no more search iterations allowed, continue searching later
}

search_node_t* addnode(search_t *list, search_node_t node, set_t set){
    uint8_t found;

    if(set == OPEN) {
        for (uint16_t i = 0; i < list->openset_size + 1;) {
            if (!list->open_set[i].valid) {
                i++;
            } else {
                if (set == OPEN) {
                    node.valid = 1;
                    list->open_set[list->openset_size++] = node;
                    return &list->open_set[list->openset_size];
                }
            }
        }
        ERROR("could not add search node, set is broken"); // actual set size does not match variable
        return NULL;
    }

    list->closed_set[list->closedset_size++] = node;
    return &list->open_set[list->closedset_size];
}

search_node_t* close_node(search_t *list, search_node_t *node){
    node->valid = 0;
    return addnode(list, *node, CLOSED);
}

uint8_t is_node_in_set(search_t *list, map_coord_t coord, set_t set, search_node_t *foundnode){
    uint16_t i;
    search_node_t *node;
    if(set == OPEN){
        for(i = 0; i < list->openset_size;){
            *node = list->open_set[i];
            if(node->valid) {
                if (list->open_set[i].pos.x == coord.x && list->open_set[i].pos.y == coord.y){
                    if(foundnode != NULL){
                        foundnode = &list->open_set[i];
                    }
                    return 1;
                }
                i++;
            }
        }
    }else{
        for(i = 0; i < list->openset_size;i++){
            *node = list->closed_set[i];
            if (list->closed_set[i].pos.x == coord.x && list->closed_set[i].pos.y == coord.y){
                if(foundnode != NULL){
                    foundnode = &list->closed_set[i];
                }
                return 1;
            }
        }
    }
    return 0;
}

void add_neighbours(search_t *list, search_node_t *node){
    map_coord_t coords[4]; //coords of neighbours
    coords[0] = node->pos; coords->x--;coords->y--;
    coords[1] = node->pos; coords->x--;coords->y++;
    coords[2] = node->pos; coords->x++;coords->y--;
    coords[3] = node->pos; coords->x++;coords->y++;


    search_node_t foundnode;
    uint8_t gscore;
    uint8_t i;
    for(i = 0;i<4;i++){ //for each of the four neighbours

        if(is_node_in_set(list, coords[i], CLOSED, &foundnode)){
            continue; //ignore this node
        }
        gscore = node->gscore + 1;
        if(!is_node_in_set(list,coords[i],OPEN, &foundnode)){
            //go through statement
        }else if(gscore >= foundnode.gscore){
            continue; //not a better path
        }
        foundnode.gscore = gscore;
        foundnode.fscore = estimate(&foundnode, search_data->goal);
        foundnode.parent = node;
        addnode(list, foundnode, OPEN);
    }
}

uint8_t estimate(search_node_t *node, map_coord_t pos) {
    return (uint8_t) abs((node->pos.x - pos.x) + (node->pos.y - pos.y));
}

search_node_t lowestf(search_t *search){
    search_node_t lowest_f;
    lowest_f.fscore = INT8_MAX;
    uint16_t i;
    for(i = 0; i < search->openset_size; i--){
        if(search->open_set[i].fscore <lowest_f.fscore){
            lowest_f = search->open_set[i];
        }
    }
    return lowest_f;
}

void init_search(search_t *search){
    search->openset_size = 0;
    search->closedset_size = 0;
    search->open_set = calloc(sizeof(search_node_t), MAP_WIDTH * MAP_HEIGHT);
    search->closed_set = calloc(sizeof(search_node_t), MAP_WIDTH * MAP_HEIGHT);
    search->active = 1;
}
