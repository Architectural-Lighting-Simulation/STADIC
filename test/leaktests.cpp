/****************************************************************
 * Copyright (c) 2014, The Pennsylvania State University
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms,
 * with or without modification, are permitted for
 * personal and commercial purposes provided that the
 * following conditions are met:
 *
 * 1. Redistribution of source code must retain the
 *    above copyright notice, this list of conditions
 *    and the following disclaimer.
 *
 * 2. Redistribution in binary form must reproduce the
 *    above copyright notice, this list of conditions
 *    and the following disclaimer.
 *
 * 3. Neither the name of The Pennsylvania State University
 *    nor the names of its contributors may be used to
 *    endorse or promote products derived from this software
 *    without the specific prior written permission of The
 *    Pennsylvania State University.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PENNSYLVANIA STATE UNIVERSITY
 * "AS IS" AND ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT OF
 * INTELLECTUAL PROPERTY ARE EXPRESSLY DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 ****************************************************************/

#include "leakcheck.h"
#include "gtest/gtest.h"
#include <iostream>
#include <vector>

TEST(LeakTests, EnclosedModel)
{
  //This model should be fully enclosed
  stadic::LeakCheck leakChecker;
  std::vector<std::string> radFiles = { "Simple.rad", "material.rad" };
  ASSERT_TRUE(leakChecker.setRadFile(radFiles));
  std::vector<std::string> layerNames = { "l_floor" };
  leakChecker.setFloorLayers(layerNames);
  ASSERT_TRUE(leakChecker.setUnits(0));
  ASSERT_TRUE(leakChecker.setReflectance(1));
  ASSERT_TRUE(leakChecker.isEnclosed());

}

TEST(LeakTests, LeakModel)
{
  //This model should contain a 10" x 10" square hole along the east side of the ceiling
  stadic::LeakCheck leakChecker;
  std::vector<std::string> radFiles={"SimpleHole.rad","material.rad"};
  ASSERT_TRUE(leakChecker.setRadFile(radFiles));
  std::vector<std::string> layerNames;
  layerNames.clear();
  layerNames.push_back("l_floor");
  leakChecker.setFloorLayers(layerNames);
  ASSERT_TRUE(leakChecker.setUnits(0));
  ASSERT_TRUE(leakChecker.setReflectance(1));
  ASSERT_FALSE(leakChecker.isEnclosed());

}
