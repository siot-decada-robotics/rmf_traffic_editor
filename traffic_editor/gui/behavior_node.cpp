/*
 * Copyright (C) 2019-2020 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include "behavior_node.h"
#include "building.h"
using std::string;

BehaviorNode::BehaviorNode()
{
}

BehaviorNode::~BehaviorNode()
{
}

bool BehaviorNode::populate_model_state_from_vertex_name(
    ModelState& state,
    const std::string vertex_name,
    Building& building)
{
  // look up the destination in the building
  printf("  finding destination [%s]\n", vertex_name.c_str());
  bool found = false;
  for (const auto& level : building.levels)
    for (const auto& vertex : level->vertices)
    {
      const string full_name = level->name + "/" + vertex.name;
      if (full_name == vertex_name)
      {
        found = true;
        state.x = vertex.x;
        state.y = vertex.y;
        state.level_name = level->name;
        break;
      }
    }

  if (found)
  {
    printf(
        "  vertex [%s] = (%.2f, %.2f) on level [%s]\n",
        vertex_name.c_str(),
        state.x,
        state.y,
        state.level_name.c_str());
    return true;
  }
  else
  {
    printf("  ERROR: could not find [%s]\n", vertex_name.c_str());
    return false;
  }
}
