#ifndef RAND_SEARCH_H
#define RAND_SEARCH_H

#include <stdint.h>

#include "map/map.h"

typedef struct search_node_s search_node_t;
typedef struct nav_s nav_t;

#define ALLOWED_SEARCH_ITERATIONS 10

typedef enum set_e{
    OPEN,
    CLOSED
}set_t;

struct search_node_s{
    pixel_coord_t pos;
    search_node_t *parent;
    uint8_t gscore;
    uint8_t fscore;
    uint8_t valid;
};

typedef struct search_s{
    search_node_t *closed_set;
    search_node_t *open_set;
    uint16_t closedset_size;
    uint16_t openset_size;
    pixel_coord_t goal;
    uint8_t active;
}search_t;

void init_search(search_t *search);
search_node_t* findpath(nav_t *nav);
search_node_t* addnode(search_t *list, search_node_t node, set_t set);
search_node_t* close_node(search_t *list, search_node_t *node);
void add_neighbours(search_t *list, search_node_t *node);
uint8_t estimate(search_node_t *node, pixel_coord_t pos);
search_node_t lowestf(search_t *search);


#endif //RAND_SEARCH_H
