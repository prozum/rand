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
    map_coord_t pos;
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
    map_coord_t goal;
    uint8_t active;
}search_t;

/**
 * Initializes a heuristic search struct
 * @param search - A pointer to the search_t struct to initialize
 */
void init_search(search_t *search);
/**
 * Attempt to find a path between the drone's current position and the point specified in the nav->search_data->goal
 * @param nav - A pointer to the nav_t struct maintaining information about position, angle etc.
 * @return - A path to the specified point?
 */
search_node_t* find_path(nav_t *nav);
/**
 * Adds a node the the specified list
 * @param list - A pointer to the list to add to
 * @param node - The node to add
 * @param set - NEEDS DOCUMENTATION
 * @return - NEEDS DOCUMENTATION
 */
search_node_t* addnode(search_t *list, search_node_t node, set_t set);
/**
 * Close a specified node from the search list
 * @param list - The search list
 * @param node - The node to close
 * @return - NEEDS DOCUMENTATION
 */
search_node_t* close_node(search_t *list, search_node_t *node);
/**
 * Add neighbours to a specified node on the list
 * @param list - The search list
 * @param node - The node to add neighbours to
 */
void add_neighbours(search_t *list, search_node_t *node);
/**
 * Estimates a given node from the current position
 * @param node - A pointer to the node to estimate
 * @param pos - The drone's current position
 * @return - NEEDS DOCUMENTATION
 */
uint8_t estimate(search_node_t *node, map_coord_t pos);
/**
 * Finds the node with the lowest f-estimate on the search list
 * @param search The search list to search in
 * @return The node with the lowest f-estimate
 */
search_node_t lowestf(search_t *search);


#endif //RAND_SEARCH_H
