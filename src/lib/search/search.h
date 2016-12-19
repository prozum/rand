#ifndef RAND_SEARCH_H
#define RAND_SEARCH_H

/** @file search.h
 * \brief Search algorithm functions and data
 *
 * \addtogroup Search
 * @{
 */

#include <stdint.h>

#include "map/map.h"

typedef struct nav_s nav_t; //!< Forward declare due to circular dependencies

/**
 * Defines the maximum number of iterations the search algorithm may take for each scheduled time-slice
 */
#define ALLOWED_SEARCH_ITERATIONS 10

/**
 * An enum for storing possible states for the sets of the heuristic search algorithm
 */
typedef enum set_e {
    OPEN, //!< The set is open, meaning there's still a chance to find a path to the goal
    CLOSED //!< The set is closed, there's no chance to find a path to the goal
} set_t;

/**
 * Defines the data-structure used for heauristic search
 */
typedef struct search_node_s search_node_t;
struct search_node_s {
    map_coord_t pos; //!< Position on the drone's internal map
    search_node_t *parent; //!< The parent of the node in the constructed search-tree
    uint8_t gscore; //!< ARNE MUST DOCUMENT
    uint8_t fscore; //!< ARNE MUST DOCUMENT
    uint8_t valid; //!< ARNE MUST DOCUMENT
};

/**
 * Defines the data-structure used to store all relevant data of a heuristic search
 */
typedef struct search_s {
    search_node_t *closed_set; //!< A pointer to the head of the closed-set list of the search
    search_node_t *open_set; //!< A pointer to the head of the open-set list of the search
    uint16_t closedset_size; //!< Stores the size of the closed set
    uint16_t openset_size; //!< Stored the size of the open set
    map_coord_t goal; //!< Stores the goal position for the search, i.e. the point on the map in which the search ends
    uint8_t active; //!< A flag for indicating if the search is active, i.e. needs to be scheduled again
} search_t;

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

//! @}
