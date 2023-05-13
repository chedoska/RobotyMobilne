#ifndef PATH_PLANNING_H
#define PATH_PLANNING_H

#include "definitions.h"
#include "Arduino.h"

#define NODE_COUNT 9

#define DATA_BITARRAY_SIZE 16

#if DATA_BITARRAY_SIZE == 8
  #define BITARRAY uint8_t
#elif DATA_BITARRAY_SIZE == 16
  #define BITARRAY uint16_t
#elif DATA_BITARRAY_SIZE == 32
  #define BITARRAY uint32_t
#endif

typedef struct Node_data{
    uint8_t id;
    int8_t neighbours[4];          // 0 -north, 1- right, 2- bottom, 3- left
    uint8_t travel_costs[4];        // 0 -north, 1- right, 2- bottom, 3- left
} Node_data;

uint8_t findNodePath(uint8_t start_id, uint8_t goal_id, Node_data *map_data, uint8_t *path);

void determine_direction(uint8_t from_node_id, uint8_t to_node_id, uint8_t *exit_direction, uint8_t *enter_direction, Node_data *map_data);
void generateManeuverList(uint8_t *path, uint8_t path_size, Node_data *map_data, Maneuver *maneuver_list, uint8_t start_direction, uint8_t *end_direction);

#endif
