/******************************************************************************
 * Copyright (c) 2014-2015, The Pennsylvania State University
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission of the
 *    respective copyright holder or contributor.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * AND NONINFRINGEMENT OF INTELLECTUAL PROPERTY ARE EXPRESSLY DISCLAIMED. IN
 * NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *****************************************************************************/

#include "functions.h"
#include "gtest/gtest.h"
#include <string>
#include <vector>
#include <queue>

TEST(FunctionTests, Split)
{
  std::string testString = "This,is,only,a,test";
  std::vector<std::string> testList;
  testList.clear();
  testList=stadic::split(testString, ',');
  ASSERT_EQ(5,testList.size());
  EXPECT_EQ("This",testList[0]);
  EXPECT_EQ("is",testList[1]);
  EXPECT_EQ("only",testList[2]);
  EXPECT_EQ("a",testList[3]);
  EXPECT_EQ("test",testList[4]);

  testList = stadic::split("", ',');
  EXPECT_EQ(0, testList.size());

  testList = stadic::split(",", ',');
  EXPECT_EQ(0, testList.size());

  testList = stadic::split(",begins,with,delimiter", ',');
  ASSERT_EQ(3, testList.size());
  EXPECT_EQ("begins", testList[0]);
  EXPECT_EQ("with", testList[1]);
  EXPECT_EQ("delimiter", testList[2]);

  testList = stadic::split("ends,with,delimiter,", ',');
  ASSERT_EQ(3, testList.size());
  EXPECT_EQ("ends", testList[0]);
  EXPECT_EQ("with", testList[1]);
  EXPECT_EQ("delimiter", testList[2]);
}

TEST(FunctionTests, SplitTrim)
{
  std::string testString = "This, is , only,a ,     test";
  std::vector<std::string> testList;
  testList.clear();
  testList=stadic::trimmedSplit(testString, ',');
  ASSERT_EQ(5,testList.size());
  EXPECT_EQ("This",testList[0]);
  EXPECT_EQ("is",testList[1]);
  EXPECT_EQ("only",testList[2]);
  EXPECT_EQ("a",testList[3]);
  EXPECT_EQ("test",testList[4]);
}


TEST(FunctionTests, Trim)
{
    std::string testString = " word   ";
    EXPECT_EQ("word",stadic::trim(testString));
    std::string nothing = " ";
    EXPECT_TRUE(stadic::trim(nothing).empty());
}

TEST(FunctionTests, ToDouble)
{
    std::string string = "20.5";
    bool ok;
    double value = stadic::toDouble(string, &ok);
    EXPECT_EQ(20.5,value);
    EXPECT_TRUE(ok);
    string = "not a number";
    value = stadic::toDouble(string, &ok);
    EXPECT_EQ(0.0, value);
    EXPECT_FALSE(ok);
}

TEST(FunctionTests, ToString)
{
  std::string string = "20.5";
  double value = 20.5;
  EXPECT_EQ(string, stadic::toString(value));
}

TEST(FunctionTests, Partition)
{
    std::string string = "abcdefghijklm";
    auto parts = stadic::stringPartition(string, 'j');
    EXPECT_EQ("abcdefghi", parts.first);
    EXPECT_EQ("klm", parts.second);
    parts = stadic::stringPartition(string, 'n');
    EXPECT_EQ("abcdefghijklm", parts.first);
    EXPECT_TRUE(parts.second.empty());
    parts = stadic::stringPartition(string, 'm');
    EXPECT_EQ("abcdefghijkl", parts.first);
    EXPECT_TRUE(parts.second.empty());
    parts = stadic::stringPartition(string, 'a');
    EXPECT_EQ("bcdefghijklm", parts.second);
    EXPECT_TRUE(parts.first.empty());
}

TEST(FunctionTests, Tokenize)
{
    std::queue<std::string> queue;
    stadic::tokenize(queue, "This is a string to tokenize");
    ASSERT_EQ(6, queue.size());
    EXPECT_EQ("This", queue.front());
    queue.pop();
    EXPECT_EQ("is", queue.front());
    queue.pop();
    EXPECT_EQ("a", queue.front());
    queue.pop();
    EXPECT_EQ("string", queue.front());
    queue.pop();
    EXPECT_EQ("to", queue.front());
    queue.pop();
    EXPECT_EQ("tokenize", queue.front());
}
