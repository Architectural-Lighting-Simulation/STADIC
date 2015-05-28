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

#include "processshade.h"
#include "logging.h"
#include "dayill.h"
#include <vector>
#include <iostream>
#include <fstream>

namespace stadic {
ProcessShade::ProcessShade(BuildingControl *model) :
    m_Model(model)
{
}

bool ProcessShade::processShades()
{
    std::vector<std::shared_ptr<Control>> spaces=m_Model->spaces();
    for (int i=0;i<spaces.size();i++){
        if (!makeShadeSched(spaces[i].get())){
            STADIC_LOG(Severity::Error, "The creation of the shade schedule for "+spaces[i].get()->spaceName()+" has failed.");
            return false;
        }

        DaylightIlluminanceData finalIll;


        std::vector<double> finalTemporalIll;

    }

    return true;
}
bool ProcessShade::writeSched(){
    return writeSched(std::cout);
}

bool ProcessShade::writeSched(std::ostream& out){
    //This function does all of the writing.
}

bool ProcessShade::writeSched(std::string file){
    std::ofstream oFile;
    oFile.open(file);
    if (!oFile.is_open()){
        STADIC_LOG(Severity::Error, "The opening of the file "+ file + " has failed.");
        return false;
    }
    if (!writeSched(oFile)){
        oFile.close();
        return false;
    }
    oFile.close();
    return true;
}
bool ProcessShade::makeShadeSched(Control *model){
    std::vector<std::vector<int>> shadeSchedule;
    for (int j=0;j<model->windowGroups().size();j++){
        if (model->windowGroups()[j].shadeControl()->controlMethod()=="automated_signal"){
            shadeSchedule.push_back(automatedSignal(model, j));
        }else if (model->windowGroups()[j].shadeControl()->controlMethod()=="automated_profile_angle"){
            shadeSchedule.push_back(automatedProfileAngle(model, j));
        }else if (model->windowGroups()[j].shadeControl()->controlMethod()=="automated_profile_angle_signal"){
            shadeSchedule.push_back(automatedProfileAngleSignal(model, j));
        }

    }



    return true;
}
//Shade Control Algorithms
std::vector<int> ProcessShade::automatedSignal(Control *model, int windowGroup){
    std::vector<int> shadeSchedule;


    return shadeSchedule;
}

std::vector<int> ProcessShade::automatedProfileAngle(Control *model, int windowGroup){
    std::vector<int> shadeSchedule;


    return shadeSchedule;
}
std::vector<int> ProcessShade::automatedProfileAngleSignal(Control *model, int windowGroup){
    std::vector<int> shadeSchedule;


    return shadeSchedule;
}



}