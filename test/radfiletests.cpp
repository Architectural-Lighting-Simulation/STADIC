/******************************************************************************
 * Copyright (c) 2014-2015, The Pennsylvania State University
 * Copyright (c) 2015-2016, Jason W. DeGraw
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

#include "radfiledata.h"
#include "gtest/gtest.h"
#include <iostream>
#include "materialprimitives.h"
#include "geometryprimitives.h"
#include "functions.h"

TEST(RadFileTests, ParseRadFile)
{
  stadic::RadFileData radData;
  ASSERT_TRUE(radData.addRad("simple.rad"));
  ASSERT_EQ(36, radData.primitives().size());
  ASSERT_EQ(36, radData.geometry().size());
  ASSERT_EQ(0, radData.materials().size());
  ASSERT_TRUE(radData.addRad("material.rad"));
  //Testing to ensure all of the primitives are read in
  ASSERT_EQ(42, radData.primitives().size());
  ASSERT_EQ(36, radData.geometry().size());
  ASSERT_EQ(6, radData.materials().size());

  //Testing First Polygon for contents
  EXPECT_EQ("l_floor", radData.geometry().at(0)->modifierName());
  EXPECT_EQ(stadic::RadPrimitive::Polygon, radData.geometry().at(0)->type());
  EXPECT_EQ("l_floor.0.1", radData.geometry().at(0)->name());
  EXPECT_EQ(0, radData.geometry().at(0)->arg1().size());
  EXPECT_EQ(0, radData.geometry().at(0)->arg2().size());
  ASSERT_EQ(12, radData.geometry().at(0)->arg3().size());
  EXPECT_EQ(0, stadic::toDouble(radData.geometry().at(0)->arg3().at(0)));
  EXPECT_EQ(240, stadic::toDouble(radData.geometry().at(0)->arg3().at(3)));
  EXPECT_EQ(240, stadic::toDouble(radData.geometry().at(0)->arg3().at(6)));
  EXPECT_EQ(240, stadic::toDouble(radData.geometry().at(0)->arg3().at(10)));

  //Testing Last Polygon for contents
  EXPECT_EQ("l_ceiling", radData.geometry().at(radData.geometry().size()-1)->modifierName());
  EXPECT_EQ(stadic::RadPrimitive::Polygon, radData.geometry().at(radData.geometry().size()-1)->type());
  EXPECT_EQ("l_ceiling.39.1", radData.geometry().at(radData.geometry().size()-1)->name());
  EXPECT_EQ(0, radData.geometry().at(radData.geometry().size()-1)->arg1().size());
  EXPECT_EQ(0, radData.geometry().at(radData.geometry().size()-1)->arg2().size());
  ASSERT_EQ(12, radData.geometry().at(radData.geometry().size()-1)->arg3().size());
  EXPECT_EQ(0, stadic::toDouble(radData.geometry().at(radData.geometry().size()-1)->arg3().at(0)));
  EXPECT_EQ(0, stadic::toDouble(radData.geometry().at(radData.geometry().size()-1)->arg3().at(3)));
  EXPECT_EQ(240, stadic::toDouble(radData.geometry().at(radData.geometry().size()-1)->arg3().at(6)));
  EXPECT_EQ(0, stadic::toDouble(radData.geometry().at(radData.geometry().size()-1)->arg3().at(10)));

  //Testing first material for contents
  EXPECT_EQ("void", radData.materials().at(0)->modifierName());
  EXPECT_EQ(stadic::RadPrimitive::Plastic, radData.materials().at(0)->type());
  EXPECT_EQ("l_wall", radData.materials().at(0)->name());
  EXPECT_EQ(0, radData.materials().at(0)->arg1().size());
  EXPECT_EQ(0, radData.materials().at(0)->arg2().size());
  ASSERT_EQ(5, radData.materials().at(0)->arg3().size());
  EXPECT_EQ(.5, stadic::toDouble(radData.materials().at(0)->arg3().at(0)));
  EXPECT_EQ(.5, stadic::toDouble(radData.materials().at(0)->arg3().at(1)));
  EXPECT_EQ(.5, stadic::toDouble(radData.materials().at(0)->arg3().at(2)));
  EXPECT_EQ(0, stadic::toDouble(radData.materials().at(0)->arg3().at(3)));
  EXPECT_EQ(0, stadic::toDouble(radData.materials().at(0)->arg3().at(4)));

  //Testing second material for contents
  EXPECT_EQ("void", radData.materials().at(1)->modifierName());
  EXPECT_EQ(stadic::RadPrimitive::Glass, radData.materials().at(1)->type());
  EXPECT_EQ("l_window", radData.materials().at(1)->name());
  EXPECT_EQ(0, radData.materials().at(1)->arg1().size());
  EXPECT_EQ(0, radData.materials().at(1)->arg2().size());
  ASSERT_EQ(3, radData.materials().at(1)->arg3().size());
  EXPECT_EQ(.65, stadic::toDouble(radData.materials().at(1)->arg3().at(0)));
  EXPECT_EQ(.65, stadic::toDouble(radData.materials().at(1)->arg3().at(1)));
  EXPECT_EQ(.65, stadic::toDouble(radData.materials().at(1)->arg3().at(2)));

  //Testing last material for contents
  EXPECT_EQ("void", radData.materials().at(radData.materials().size()-1)->modifierName());
  EXPECT_EQ(stadic::RadPrimitive::Plastic, radData.materials().at(radData.materials().size()-1)->type());
  EXPECT_EQ("l_ceiling", radData.materials().at(radData.materials().size()-1)->name());
  EXPECT_EQ(0, radData.materials().at(radData.materials().size()-1)->arg1().size());
  EXPECT_EQ(0, radData.materials().at(radData.materials().size()-1)->arg2().size());
  ASSERT_EQ(5, radData.materials().at(radData.materials().size()-1)->arg3().size());
  EXPECT_EQ(.8, stadic::toDouble(radData.materials().at(radData.materials().size()-1)->arg3().at(0)));
  EXPECT_EQ(.8, stadic::toDouble(radData.materials().at(radData.materials().size()-1)->arg3().at(1)));
  EXPECT_EQ(.8, stadic::toDouble(radData.materials().at(radData.materials().size()-1)->arg3().at(2)));
  EXPECT_EQ(0, stadic::toDouble(radData.materials().at(radData.materials().size()-1)->arg3().at(3)));
  EXPECT_EQ(0, stadic::toDouble(radData.materials().at(radData.materials().size()-1)->arg3().at(4)));

  //Test getting primitives by type
  shared_vector<stadic::PlasticMaterial> plastic = radData.getPrimitives<stadic::PlasticMaterial>();
  ASSERT_EQ(5,plastic.size());

  //Testing second plastic for contents
  EXPECT_EQ("l_extwall",plastic[1]->name());
  EXPECT_EQ(.15,plastic[1]->red());
  EXPECT_EQ(.15,plastic[1]->green());
  EXPECT_EQ(.15,plastic[1]->blue());
  EXPECT_EQ(0,plastic[1]->specularity());
  EXPECT_EQ(0,plastic[1]->roughness());
}

TEST(RadfileTests, Empty)
{
    stadic::RadFileData radData;
    ASSERT_FALSE(radData.addRad("empty.rad"));
    ASSERT_EQ(0, radData.primitives().size());
}

TEST(RadfileTests, SingleLine)
{
    stadic::RadFileData radData;
    ASSERT_TRUE(radData.addRad("materialsingleline.rad"));
    ASSERT_EQ(6, radData.primitives().size());
}

TEST(RadfileTests, AddAndFind)
{
    stadic::RadFileData radData;
    ASSERT_TRUE(radData.addRad("materialsingleline.rad"));
    ASSERT_EQ(6, radData.primitives().size());
    stadic::RadPrimitive *black = new stadic::PlasticMaterial(0, 0, 0, 0, 0);
    black->setModifier(stadic::RadPrimitive::sharedVoid());
    black->setName("black");
    radData.addPrimitive(black);
    ASSERT_EQ(7, radData.primitives().size());
    std::shared_ptr<stadic::RadPrimitive> found = nullptr;
    for (auto poly : radData.geometry()) {
        if (poly->name() == "l_wall") {
            found = poly;
            break;
        }
    }
    ASSERT_EQ(nullptr, found);
    std::shared_ptr<stadic::RadPrimitive> foundf = radData.findGeometry([](std::shared_ptr<stadic::RadPrimitive> p){return p->name() == "l_wall"; });
    ASSERT_EQ(nullptr, foundf);
    for (auto matl : radData.materials()) {
        if (matl->name() == "l_wall") {
            found = matl;
            break;
        }
    }
    ASSERT_NE(nullptr, found);
    foundf = radData.findPrimitive([](std::shared_ptr<stadic::RadPrimitive> p){return p->name() == "l_wall"; });
    ASSERT_EQ(found, foundf);
    found = nullptr;
    for (auto matl : radData.materials()) {
        if (matl->name() == "black") {
            found = matl;
            break;
        }
    }
    ASSERT_NE(nullptr, found);
    foundf = radData.findMaterial([](std::shared_ptr<stadic::RadPrimitive> p){return p->name() == "black"; });
    ASSERT_EQ(found, foundf);
}

TEST(RadfileTests, Aliasing)
{
    // Set up the first set of data
    stadic::RadFileData radData;
    ASSERT_TRUE(radData.addRad("materialsingleline.rad"));
    ASSERT_EQ(6, radData.primitives().size());
    stadic::RadPrimitive *black = new stadic::PlasticMaterial(0, 0, 0, 0, 0);
    black->setModifier(stadic::RadPrimitive::sharedVoid());
    black->setName("black");
    std::shared_ptr<stadic::RadPrimitive> blackMaterial = radData.addPrimitive(black);
    ASSERT_NE(nullptr, blackMaterial);
    ASSERT_EQ(7, radData.primitives().size());
    ASSERT_TRUE(radData.addRad("simple.rad"));
    ASSERT_EQ(43, radData.primitives().size());
    std::shared_ptr<stadic::RadPrimitive> windowMaterial;
    windowMaterial = radData.findPrimitive([](std::shared_ptr<stadic::RadPrimitive> p){return p->name() == "l_window"; });
    ASSERT_NE(nullptr, windowMaterial);
    ASSERT_TRUE(radData.setAlias(blackMaterial, windowMaterial));
    ASSERT_EQ(1, radData.aliases().size());

    // Copy the first set, then make additional changes
    stadic::RadFileData otherRad = radData;
    ASSERT_EQ(43, otherRad.primitives().size());
    ASSERT_EQ(1, otherRad.aliases().size());
    stadic::RadPrimitive *white = new stadic::PlasticMaterial(1, 1, 1, 0, 0);
    white->setModifier(stadic::RadPrimitive::sharedVoid());
    white->setName("white");
    std::shared_ptr<stadic::RadPrimitive> whiteMaterial = otherRad.addPrimitive(white);
    ASSERT_NE(nullptr, whiteMaterial);
    std::shared_ptr<stadic::RadPrimitive> groundMaterial;
    groundMaterial = radData.findPrimitive([](std::shared_ptr<stadic::RadPrimitive> p){return p->name() == "l_ground"; });
    ASSERT_NE(nullptr, groundMaterial);
    ASSERT_TRUE(otherRad.setAlias(whiteMaterial, groundMaterial));
    ASSERT_EQ(2, otherRad.aliases().size());

    // Try to add an alias that isn't in the rad file
    std::shared_ptr<stadic::RadPrimitive> whiteMat = std::shared_ptr<stadic::RadPrimitive>(new stadic::PlasticMaterial(1, 1, 1, 0, 0));
    whiteMat->setModifier(stadic::RadPrimitive::sharedVoid());
    whiteMat->setName("white");
    ASSERT_FALSE(otherRad.setAlias(whiteMat, groundMaterial));

    // Final size checks
    EXPECT_EQ(43, radData.primitives().size());
    EXPECT_EQ(1, radData.aliases().size());
    EXPECT_EQ(44, otherRad.primitives().size());
    ASSERT_EQ(2, otherRad.aliases().size());
}

bool isGlass(stadic::RadPrimitive* primitive)
{
    return primitive->type() == stadic::RadPrimitive::Glass;
}
bool nameStartsWith(stadic::RadPrimitive* primitive, const std::string &name)
{
    if (primitive->name().compare(0,name.length(),name)==0){
        return true;
    }
    return false;
  //return primitive->name().startsWith(name);
}

TEST(RadFileTests, SplitRadFile)
{
    std::vector<std::string> names = { "l_window" };
    stadic::RadFileData radData;
    ASSERT_TRUE(radData.addRad("simple.rad"));
    EXPECT_EQ(36, radData.primitives().size());
    std::pair<shared_vector<stadic::RadPrimitive>, shared_vector<stadic::RadPrimitive> > split = radData.split(names);
    EXPECT_EQ(2, split.first.size());
    EXPECT_EQ(34, split.second.size());
}

TEST(RadFileTests, ParseComplicatedRadFile)
{
    stadic::RadFileData radData;
    ASSERT_TRUE(radData.addRad("complicated.rad"));
    EXPECT_EQ(112, radData.primitives().size());
    EXPECT_EQ(8, radData.materials().size());
    EXPECT_EQ(104, radData.geometry().size());
}

TEST(RadFileTests, WriteSimpleRadFile)
{
    stadic::RadFileData radData;
    ASSERT_TRUE(radData.addRad("simple.rad"));
    ASSERT_TRUE(radData.writeRadFile("simpletest.rad"));
    stadic::RadFileData reread;
    ASSERT_TRUE(reread.addRad("simpletest.rad"));
    EXPECT_EQ(radData.primitives().size(), reread.primitives().size());
}

TEST(RadFileTests, PlasticTest)
{
    stadic::RadFileData radData,badData;
    ASSERT_TRUE(radData.addRad("supportedprimitives.rad"));
    ASSERT_EQ(6, radData.primitives().size());
    auto primitive = std::dynamic_pointer_cast<stadic::PlasticMaterial>(radData.primitives()[0]);
    ASSERT_FALSE(!primitive);
    EXPECT_EQ("void", primitive->modifierName());
    EXPECT_EQ("l_wall", primitive->name());
    EXPECT_EQ(0.5, primitive->red());
    EXPECT_EQ(0.5, primitive->green());
    EXPECT_EQ(0.5, primitive->blue());
    EXPECT_EQ(0, primitive->roughness());
    EXPECT_EQ(0, primitive->specularity());

    EXPECT_FALSE(badData.addRad("badplasticmaterial.rad"));
    EXPECT_EQ(0, badData.primitives().size());
}

TEST(RadFileTests, MetalTest)
{
    stadic::RadFileData radData, badData;
    ASSERT_TRUE(radData.addRad("supportedprimitives.rad"));
    ASSERT_EQ(6, radData.primitives().size());
    auto primitive = std::dynamic_pointer_cast<stadic::MetalMaterial>(radData.primitives()[1]);
    ASSERT_FALSE(!primitive);
    EXPECT_EQ("void", primitive->modifierName());
    EXPECT_EQ("l_metal", primitive->name());
    EXPECT_EQ(0.75, primitive->red());
    EXPECT_EQ(0.75, primitive->green());
    EXPECT_EQ(0.75, primitive->blue());
    EXPECT_EQ(0.01, primitive->roughness());
    EXPECT_EQ(0.01, primitive->specularity());

    EXPECT_FALSE(badData.addRad("badmetalmaterial.rad"));
    EXPECT_EQ(0, badData.primitives().size());
}

TEST(RadFileTests, GlassTest)
{
    stadic::RadFileData radData, badData;
    ASSERT_TRUE(radData.addRad("supportedprimitives.rad"));
    ASSERT_EQ(6, radData.primitives().size());
    auto primitive = std::dynamic_pointer_cast<stadic::GlassMaterial>(radData.primitives()[2]);
    ASSERT_FALSE(!primitive);
    EXPECT_EQ("void", primitive->modifierName());
    EXPECT_EQ("l_window", primitive->name());
    EXPECT_EQ(0.65, primitive->redTrans());
    EXPECT_EQ(0.65, primitive->greenTrans());
    EXPECT_EQ(0.65, primitive->blueTrans());

    EXPECT_FALSE(badData.addRad("badglassmaterial.rad"));
    EXPECT_EQ(0, badData.primitives().size());
}

TEST(RadFileTests, TransTest)
{
    stadic::RadFileData radData, badData;
    ASSERT_TRUE(radData.addRad("supportedprimitives.rad"));
    ASSERT_EQ(6, radData.primitives().size());
    auto primitive = std::dynamic_pointer_cast<stadic::TransMaterial>(radData.primitives()[3]);
    ASSERT_FALSE(!primitive);
    EXPECT_EQ("void", primitive->modifierName());
    EXPECT_EQ("l_trans", primitive->name());
    EXPECT_EQ(0.75, primitive->red());
    EXPECT_EQ(0.75, primitive->green());
    EXPECT_EQ(0.75, primitive->blue());
    EXPECT_EQ(0.01, primitive->specularity());
    EXPECT_EQ(0.01, primitive->roughness());
    EXPECT_EQ(0.02, primitive->transmissivity());
    EXPECT_EQ(0.03, primitive->transSpecular());

    EXPECT_FALSE(badData.addRad("badtransmaterial.rad"));
    EXPECT_EQ(0, badData.primitives().size());
}

TEST(RadFileTests, PolygonTest)
{
    stadic::RadFileData radData,badData;
    ASSERT_TRUE(radData.addRad("supportedprimitives.rad"));
    ASSERT_EQ(6, radData.primitives().size());
    auto primitive = std::dynamic_pointer_cast<stadic::PolygonGeometry>(radData.primitives()[4]);
    ASSERT_FALSE(!primitive);
    ASSERT_EQ(12, primitive->arg3().size());
    EXPECT_EQ("l_wall", primitive->modifierName());
    EXPECT_EQ("l_wall.2.1", primitive->name());

    EXPECT_FALSE(badData.addRad("badpolygongeometry.rad"));
    EXPECT_EQ(0, badData.primitives().size());
}

TEST(RadFileTests, SingleLineTest){

    stadic::RadFileData radData;
    ASSERT_TRUE(radData.addRad("daylightcase1/rad/mat1.rad"));
}

TEST(RadFileTests, ParseConsistentRadFile)
{
    stadic::RadFileData radData;
    ASSERT_TRUE(radData.addRad("complicated.rad"));
    ASSERT_TRUE(radData.isConsistent());
    ASSERT_TRUE(radData.buildModifierTree());
    ASSERT_TRUE(radData.isConsistent());
}

TEST(RadFileTests, ParseInconsistentRadFile)
{
    stadic::RadFileData radData;
    ASSERT_TRUE(radData.addRad("simple.rad"));
    ASSERT_FALSE(radData.isConsistent());
}
