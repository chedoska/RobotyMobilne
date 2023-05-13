#include "path_planning.h"

uint8_t findNodePath(uint8_t start_id, uint8_t goal_id, Node_data *map_data, uint8_t *path){
  uint16_t nodes_g_values[NODE_COUNT];// = {UINT16_MAX,UINT16_MAX,UINT16_MAX,UINT16_MAX,UINT16_MAX,UINT16_MAX,UINT16_MAX,UINT16_MAX};
  for(int i = 0; i < NODE_COUNT; i++)
    nodes_g_values[i] = UINT16_MAX;
  
  BITARRAY nodes_checked = 0;
  uint8_t parent_nodes_ids[NODE_COUNT];

  nodes_g_values[start_id] = 0;

  while(1){
    uint8_t node_with_min_g_value_id;
    uint16_t current_min_g_value_found = UINT16_MAX;
    for(int i = 0; i < NODE_COUNT; i++){
      if(!(nodes_checked & (1 << i)) && nodes_g_values[i] < current_min_g_value_found){
        current_min_g_value_found = nodes_g_values[i];
        node_with_min_g_value_id = i;
      }
    }
    nodes_checked |= (1 << node_with_min_g_value_id);
    if(node_with_min_g_value_id == goal_id) break;

    for(int i = 0; i < 4; i++){
      int8_t child_node_id = map_data[node_with_min_g_value_id].neighbours[i];
      if(child_node_id == -1) continue;
      if(!(nodes_checked & (1 << child_node_id)) &&
         nodes_g_values[child_node_id] > nodes_g_values[node_with_min_g_value_id] + map_data[node_with_min_g_value_id].travel_costs[i]){
          nodes_g_values[child_node_id] = nodes_g_values[node_with_min_g_value_id] + map_data[node_with_min_g_value_id].travel_costs[i];
          parent_nodes_ids[child_node_id] = node_with_min_g_value_id;
         }
    }
  }

  uint8_t path_temp[NODE_COUNT];
  uint8_t path_size = 0;
  
  uint8_t curren_node_id = goal_id;
  while(curren_node_id != start_id){
    path_temp[path_size++] = curren_node_id;
    curren_node_id = parent_nodes_ids[curren_node_id];
  }
  path_temp[path_size++] = curren_node_id;

  uint8_t index = 0;
  for(int i = path_size - 1; i >= 0; i--){
    path[index++] = path_temp[i];
  }

  return path_size;
}

void determine_direction(uint8_t from_node_id, uint8_t to_node_id, uint8_t *exit_direction, uint8_t *enter_direction, Node_data *map_data){
  for(int i = 0; i < 4; i++){
    if(map_data[from_node_id].neighbours[i] == to_node_id) *exit_direction = i;
    if(map_data[to_node_id].neighbours[i] == from_node_id) *enter_direction = i;
  }
}

void generateManeuverList(uint8_t *path, uint8_t path_size, Node_data *map_data, Maneuver *maneuver_list, uint8_t start_direction, uint8_t *end_direction){
  uint8_t node_enter_directions[NODE_COUNT];
  uint8_t node_exit_directions[NODE_COUNT];

  for(int i = 0; i < path_size - 1; i++){
    determine_direction(path[i], path[i + 1], &node_exit_directions[i], &node_enter_directions[i + 1], map_data);
  }
  node_enter_directions[0] = start_direction;
  node_exit_directions[path_size - 1] = ( node_enter_directions[path_size - 1] + 2 ) % 4;

  for(int i = 0; i < path_size; i++){
    int8_t direction_diff = node_enter_directions[i] - node_exit_directions[i];
    if(direction_diff == 1 || direction_diff == -3) maneuver_list[i] = TURN_RIGHT;
    else if(direction_diff == -1 || direction_diff == 3) maneuver_list[i] = TURN_LEFT;
    else if(direction_diff == 2 || direction_diff == -2) maneuver_list[i] = GO_STRAIGHT;
    else if(direction_diff == 0) maneuver_list[i] = REVERSE;
    else maneuver_list[i] == -1;
  }

  *end_direction = node_enter_directions[path_size - 1];
}
