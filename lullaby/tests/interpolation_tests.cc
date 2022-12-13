/*
Copyright 2017-2019 Google Inc. All Rights Reserved.

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

#include "lullaby/util/interpolation.h"
#include "lullaby/util/math.h"
#include "lullaby/tests/mathfu_matchers.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace lull {
namespace {

using testing::EqualsMathfu;

const float kEpsilon = 2e-5f;

TEST(EasingTest, EaseInPow) {
  EXPECT_THAT(EaseInPow(mathfu::kZeros3f, mathfu::kOnes3f, 0.5f, 2.0f),
              EqualsMathfu(mathfu::vec3(0.25f, 0.25f, 0.25f)));
}

TEST(InterpolationTest, Quadratic) {
  EXPECT_THAT(QuadraticEaseInOut(0.0f, 1.0f, 0.5f), 0.5f);

  EXPECT_THAT(QuadraticEaseIn(mathfu::kZeros3f, mathfu::kOnes3f, 0.5f),
              EqualsMathfu(mathfu::vec3(0.25f, 0.25f, 0.25f)));

  EXPECT_THAT(QuadraticEaseOut(mathfu::kZeros3f, mathfu::kOnes3f, 0.5f),
              EqualsMathfu(mathfu::vec3(0.75f, 0.75f, 0.75f)));

  EXPECT_THAT(QuadraticEaseInOut(mathfu::kZeros3f, mathfu::kOnes3f, 0.5f),
              EqualsMathfu(mathfu::vec3(0.5f, 0.5f, 0.5f)));

  EXPECT_THAT(QuadraticEaseInOut(mathfu::kZeros3f, mathfu::kOnes3f, 0.25f),
              EqualsMathfu(mathfu::vec3(0.125f, 0.125f, 0.125f)));

  EXPECT_THAT(QuadraticEaseInOut(mathfu::kZeros3f, mathfu::kOnes3f, 0.75f),
              EqualsMathfu(mathfu::vec3(0.875f, 0.875f, 0.875f)));
}

TEST(InterpolationTest, Cubic) {
  EXPECT_THAT(CubicEaseIn(0.0f, 1.0f, 0.0f), 0.0f);
  EXPECT_THAT(CubicEaseIn(0.0f, 1.0f, 0.5f), 0.125f);
  EXPECT_THAT(CubicEaseIn(0.0f, 1.0f, 1.0f), 1.0f);

  EXPECT_THAT(CubicEaseOut(0.0f, 1.0f, 0.0f), 0.0f);
  EXPECT_THAT(CubicEaseOut(0.0f, 1.0f, 0.5f), 0.875f);
  EXPECT_THAT(CubicEaseOut(0.0f, 1.0f, 1.0f), 1.0f);

  EXPECT_THAT(CubicEaseInOut(0.0f, 1.0f, 0.0f), 0.0f);
  EXPECT_THAT(CubicEaseInOut(0.0f, 1.0f, 0.5f), 0.5f);
  EXPECT_THAT(CubicEaseInOut(0.0f, 1.0f, 1.0f), 1.0f);

  EXPECT_THAT(CubicEaseIn(mathfu::kZeros3f, mathfu::kOnes3f, 0.5f),
              EqualsMathfu(mathfu::vec3(0.125f, 0.125f, 0.125f)));

  EXPECT_THAT(CubicEaseOut(mathfu::kZeros3f, mathfu::kOnes3f, 0.5f),
              EqualsMathfu(mathfu::vec3(0.875f, 0.875f, 0.875f)));

  EXPECT_THAT(CubicEaseInOut(mathfu::kZeros3f, mathfu::kOnes3f, 0.5f),
              EqualsMathfu(mathfu::vec3(0.5f, 0.5f, 0.5f)));

  EXPECT_THAT(CubicEaseInOut(mathfu::kZeros3f, mathfu::kOnes3f, 0.25f),
              EqualsMathfu(mathfu::vec3(0.0625f, 0.0625f, 0.0625f)));

  EXPECT_THAT(CubicEaseInOut(mathfu::kZeros3f, mathfu::kOnes3f, 0.75f),
              EqualsMathfu(mathfu::vec3(0.9375f, 0.9375f, 0.9375f)));
}

TEST(InterpolationTest, Quartic) {
  EXPECT_THAT(QuarticEaseIn(0.0f, 1.0f, 0.0f), 0.0f);
  EXPECT_THAT(QuarticEaseIn(0.0f, 1.0f, 0.5f), 0.0625f);
  EXPECT_THAT(QuarticEaseIn(0.0f, 1.0f, 1.0f), 1.0f);

  EXPECT_THAT(QuarticEaseOut(0.0f, 1.0f, 0.0f), 0.0f);
  EXPECT_THAT(QuarticEaseOut(0.0f, 1.0f, 0.5f), 0.9375f);
  EXPECT_THAT(QuarticEaseOut(0.0f, 1.0f, 1.0f), 1.0f);

  EXPECT_THAT(QuarticEaseInOut(0.0f, 1.0f, 0.0f), 0.0f);
  EXPECT_THAT(QuarticEaseInOut(0.0f, 1.0f, 0.5f), 0.5f);
  EXPECT_THAT(QuarticEaseInOut(0.0f, 1.0f, 1.0f), 1.0f);

  EXPECT_THAT(QuarticEaseIn(mathfu::kZeros3f, mathfu::kOnes3f, 0.5f),
              EqualsMathfu(mathfu::vec3(0.0625f, 0.0625f, 0.0625f)));

  EXPECT_THAT(QuarticEaseOut(mathfu::kZeros3f, mathfu::kOnes3f, 0.5f),
              EqualsMathfu(mathfu::vec3(0.9375f, 0.9375f, 0.9375f)));

  EXPECT_THAT(QuarticEaseInOut(mathfu::kZeros3f, mathfu::kOnes3f, 0.5f),
              EqualsMathfu(mathfu::vec3(0.5f, 0.5f, 0.5f)));

  EXPECT_THAT(QuarticEaseInOut(mathfu::kZeros3f, mathfu::kOnes3f, 0.25f),
              EqualsMathfu(mathfu::vec3(0.03125f, 0.03125f, 0.03125f)));

  EXPECT_THAT(QuarticEaseInOut(mathfu::kZeros3f, mathfu::kOnes3f, 0.75f),
              EqualsMathfu(mathfu::vec3(0.96875f, 0.96875f, 0.96875f)));
}

TEST(InterpolationTest, Quintic) {
  EXPECT_THAT(QuinticEaseIn(0.0f, 1.0f, 0.0f), 0.0f);
  EXPECT_THAT(QuinticEaseIn(0.0f, 1.0f, 0.5f), 0.03125f);
  EXPECT_THAT(QuinticEaseIn(0.0f, 1.0f, 1.0f), 1.0f);

  EXPECT_THAT(QuinticEaseOut(0.0f, 1.0f, 0.0f), 0.0f);
  EXPECT_THAT(QuinticEaseOut(0.0f, 1.0f, 0.5f), 0.96875f);
  EXPECT_THAT(QuinticEaseOut(0.0f, 1.0f, 1.0f), 1.0f);

  EXPECT_THAT(CubicEaseInOut(0.0f, 1.0f, 0.0f), 0.0f);
  EXPECT_THAT(CubicEaseInOut(0.0f, 1.0f, 0.5f), 0.5f);
  EXPECT_THAT(CubicEaseInOut(0.0f, 1.0f, 1.0f), 1.0f);

  EXPECT_THAT(QuinticEaseIn(mathfu::kZeros3f, mathfu::kOnes3f, 0.5f),
              EqualsMathfu(mathfu::vec3(0.03125f, 0.03125f, 0.03125f)));

  EXPECT_THAT(QuinticEaseOut(mathfu::kZeros3f, mathfu::kOnes3f, 0.5f),
              EqualsMathfu(mathfu::vec3(0.96875f, 0.96875f, 0.96875f)));

  EXPECT_THAT(QuinticEaseInOut(mathfu::kZeros3f, mathfu::kOnes3f, 0.5f),
              EqualsMathfu(mathfu::vec3(0.5f, 0.5f, 0.5f)));

  EXPECT_THAT(QuinticEaseInOut(mathfu::kZeros3f, mathfu::kOnes3f, 0.25f),
              EqualsMathfu(mathfu::vec3(0.015625f, 0.015625f, 0.015625f)));

  EXPECT_THAT(QuinticEaseInOut(mathfu::kZeros3f, mathfu::kOnes3f, 0.75f),
              EqualsMathfu(mathfu::vec3(0.984375f, 0.984375f, 0.984375f)));
}

TEST(InterpolationTest, FastOutSlowIn) {
  EXPECT_THAT(FastOutSlowIn(0.0f), 0.0f);
  EXPECT_THAT(FastOutSlowIn(1.0f), 1.0f);
  EXPECT_THAT(FastOutSlowIn(0.525252525f), 0.8f);

  // EXPECT_THAT(QuinticEaseInOut(mathfu::kZeros3f, mathfu::kOnes3f, 0.75f),
  //          EqualsMathfu(mathfu::vec3(0.984375f, 0.984375f, 0.984375f)));
}

}  // namespace
}  // namespace lull
