#ifndef RAND_SEARCH_H
#define RAND_SEARCH_H

/** @file search.h
 * \brief Search algorithm functions and data
 *
 * \addtogroup Search
 * @{
 */

#include <stdint.h>
#include <stdbool.h>

#include "map/map.h"

//! Defines the lowest and highest accepted world-position on the internal drone map
#define LOWEST_Y_ORG 0
#define HIGHEST_Y_ORG (MAP_HEIGHT * CENTIMETERS_PR_FIELD)
#define LOWEST_X_ORG 0
#define HIGHEST_X_ORG (MAP_WIDTH * CENTIMETERS_PR_FIELD)

typedef struct nav_s nav_t; //!< Forward declare due to circular dependencies

/**
 * Defines the maximum number of iterations the search algorithm may take for each scheduled time-slice
 */
#define ALLOWED_SEARCH_ITERATIONS 10

/**
 * An enum for storing possible states for the sets of the heuristic search algorithm
 */
typedef enum set_e {
    OPEN,  //!< The set is open, meaning there's still a chance to find a path to the goal
    CLOSED //!< The set is closed, there's no chance to find a path to the goal
} set_t;

/**
 * Defines the data-structure used for heauristic search
 */
typedef struct search_node_s search_node_t;
struct search_node_s {
    map_coord_t pos;       //!< Position on the drone's internal map
    search_node_t *parent; //!< The parent of the node in the constructed search-tree
    uint8_t gscore;        //!< The estimated path from the search node to the goal
    uint8_t fscore;        //!< The traversed path from start to this node
    uint8_t valid;         //!< False if the node has been closed, or not opened yet.
};

/**
 * Defines the data-structure used to store all relevant data of a heuristic search
 */
typedef struct search_s {
    search_node_t *closed_set; //!< A pointer to the head of the closed-set list of the search
    search_node_t *open_set;   //!< A pointer to the head of the open-set list of the search
    uint16_t closedset_size;   //!< Stores the size of the closed set
    uint16_t openset_size;     //!< Stored the size of the open set
    map_coord_t goal; //!< Stores the goal position for the search, i.e. the point on the map in which the search ends
    uint8_t active;   //!< A flag for indicating if the search is active, i.e. needs to be scheduled again
} search_t;

/**
 * Initializes a heuristic search struct
 * @param search - A pointer to the search_t struct to initialize
 */
void init_search(search_t *search);

/**
 * Aligns the drones internal representation of the world to the drone's map
 * @param x_coord - Real world x-coordinate
 * @param y_coord - Real world y-coordinate
 * @return - A struct containing the map-coordinates
 */
map_coord_t align_to_map(uint16_t x_coord, uint16_t y_coord);

/**
 * Attempt to find a path between the drone's current position and the point specified in the nav->search_data->goal
 * @param nav - A pointer to the nav_t struct maintaining information about position, angle etc.
 * @return - The goal node from which the shortest path to it can be reconstructed
 */
search_node_t *find_path(nav_t *nav);
/**
 * Adds a node the the specified list
 * @param list - A pointer to the list to add to
 * @param node - The node to add
 * @param set - the set which a node is added to. This can be either the open or the closed set
 * @return - a reference to the node in the list it has been added to
 */
search_node_t *addnode(search_t *list, search_node_t node, set_t set);
/**
 * Close a specified node from the open search list and add it to the closed set
 * @param list - The search list
 * @param node - The node to close
 * @return - a reference to the node in the closed set.
 */
search_node_t *close_node(search_t *list, search_node_t *node);
/**
 * Add neighbours to a specified node on the list
 * @param list - The search list
 * @param node - The node to add neighbours to
 */
void add_neighbours(search_t *list, search_node_t *node);
/**
 * Estimates a given node from the current position
 * @param node - A pointer to the node to estimate
 * @param pos - The goal position
 * @return - the estimate of the path length from the node to the goal
 */
uint8_t estimate(search_node_t *node, map_coord_t pos);
/**
 * Finds the node with the lowest f-estimate on the search list
 * @param search The search list to search in
 * @return The node with the lowest traversed path from the start
 */
search_node_t lowestf(search_t *search);

#endif // RAND_SEARCH_H

//! @}
