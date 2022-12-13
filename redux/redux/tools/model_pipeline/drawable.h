/*
Copyright 2017-2022 Google Inc. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS-IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef REDUX_TOOLS_MODEL_PIPELINE_DRAWABLE_H_
#define REDUX_TOOLS_MODEL_PIPELINE_DRAWABLE_H_

#include <limits>
#include <vector>

#include "redux/modules/math/vector.h"
#include "redux/tools/model_pipeline/material.h"

namespace redux::tool {

// A material and the collection of vertices (as specified by indices in an
// externally managed vertex array) to which that material applies.
struct Drawable {
  Drawable()
      : min_position(std::numeric_limits<float>::max()),
        max_position(std::numeric_limits<float>::lowest()) {}

  Material material;
  std::vector<size_t> indices;
  vec3 min_position;
  vec3 max_position;
};

}  // namespace redux::tool

#endif  // REDUX_TOOLS_MODEL_PIPELINE_DRAWABLE_H_
