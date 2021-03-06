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

#include "geometryprimitives.h"
#include "logging.h"
#include "functions.h"

namespace stadic {
//Polygon
PolygonGeometry::PolygonGeometry() : RadPrimitive()
{
    RadPrimitive::setType("polygon");
}

PolygonGeometry::PolygonGeometry(std::vector<double> points) : RadPrimitive()
{
    RadPrimitive::setType("polygon");
    setPoints(points);
}

// Setters
bool PolygonGeometry::setPoints(std::vector<double> points)
{
    if(points.size()%3 != 0) {
        STADIC_LOG(Severity::Warning, "The setting of the polygon points has failed - argument size must be a multiple of 3.");
        return false;
    } else {
        std::vector<std::string> args;
        for(double value : points) {
            args.push_back(stadic::toString(value));
            initArg(3, args);
        }
    }
    return true;
}

// Getters
std::vector<double> PolygonGeometry::points() const
{
    std::vector<double> points;
    for (int i=0;i<arg3().size();i++){
        points.push_back(stadic::toDouble(arg3()[i]));
    }
    return points;
}

//Protected
bool PolygonGeometry::validateArg3(const std::string &value, int position) const 
{
    bool ok;
    stadic::toDouble(value, &ok);
    return ok;
}

bool PolygonGeometry::validateArg3(const std::vector<std::string> &arg) const
{
    if(arg.size()%3 != 0) {
        STADIC_LOG(Severity::Warning, "The setting of the polygon points has failed - argument size must be a multiple of 3.");
        return false;
    }
    for(std::string value : arg) {
        bool ok;
        stadic::toDouble(value, &ok);
        if(!ok) {
            return false;
        }
    }
    return true;
}

//Sphere
SphereGeometry::SphereGeometry() : RadPrimitive()
{
    RadPrimitive::setType("sphere");
    std::vector<std::string> arg3={"0","0","0","1"};
    initArg(3,arg3);
}

SphereGeometry::SphereGeometry(std::vector<double> centerPoint, double radius) : RadPrimitive()
{
    RadPrimitive::setType("sphere");
    std::vector<std::string> arg3={"0","0","0","1"};
    initArg(3,arg3);
    setCenterPoint(centerPoint);
    setRadius(radius);
}

bool SphereGeometry::setCenterPoint(std::vector<double> centerPoint)
{
    if(centerPoint.size()!= 3) {
        STADIC_ERROR("The setting of the sphere center has failed - center must contain 3 values (ex. x y z).");
        return false;
    } else {
        for(int i=0;i<3;i++) {
            if (!setArg3(stadic::toString(centerPoint[i]), i)){
                return false;
            }
        }
    }
    return true;
}

bool SphereGeometry::setRadius(double radius)
{
    if (radius<=0){
        STADIC_ERROR("The radius of a sphere cannot be negative.");
        return false;
    } else {
        if (setArg3(stadic::toString(radius), 3)){
            return true;
        }
    }
    return false;
}

// Getters
std::vector<double> SphereGeometry::centerPoint() const
{
    std::vector<double> cPoint;
    cPoint.push_back(toDouble(getArg3(0)));
    cPoint.push_back(toDouble(getArg3(1)));
    cPoint.push_back(toDouble(getArg3(2)));
    return cPoint;
}

double SphereGeometry::radius() const
{
    return toDouble(getArg3(3));
}

//Protected
bool SphereGeometry::validateArg3(const std::string &value, int position) const
{
    bool ok;
    stadic::toDouble(value, &ok);
    if(ok){
        if(position<3){
            return true;
        } else if(position==3 && toDouble(value)>0){
            return true;
        }
    }
    return false;
}

/*
bool SphereGeometry::validateArg(int number, std::string value, int position) const
{
    if(number==3) {
        bool ok;
        double dval = stadic::toDouble(value, &ok);
        if (ok){
            if (position<3){
                return true;
            }else if (position==3 && toDouble(value)>0){
                return true;
            }
        }
    }
    return false;
}

bool SphereGeometry::validateArg(int number, std::vector<std::string> arg) const
{
    if(number==3) {
        if(arg.size() != 4) {
            return false;
        }
        for(std::string value : arg) {
            bool ok;
            double dval = stadic::toDouble(value, &ok);
            if(ok) {
                return true;
            }
        }
    }
    return false;
}
*/

//Ring
RingGeometry::RingGeometry() : RadPrimitive()
{
    RadPrimitive::setType("ring");
    std::vector<std::string> arg3={"0","0","0","0", "0", "1", "0", "1"};
    initArg(3,arg3);
}

RingGeometry::RingGeometry(std::vector<double> centerPoint, std::vector<double> surfaceNormal, double innerRadius, double outerRadius) : RadPrimitive()
{
    RadPrimitive::setType("ring");
    std::vector<std::string> arg3={"0","0","0","0", "0", "1", "0", "1"};
    initArg(3,arg3);
    setCenterPoint(centerPoint);
    setSurfaceNormal(surfaceNormal);
    setInnerRadius(innerRadius);
    setOuterRadius(outerRadius);
}

bool RingGeometry::setCenterPoint(std::vector<double> centerPoint)
{
    if(centerPoint.size()!= 3) {
        STADIC_ERROR("The setting of the ring center has failed - center must contain 3 values (ex. x y z).");
        return false;
    } else {
        for(int i=0;i<3;i++) {
            if(!setArg3(stadic::toString(centerPoint[i]), i)){
                return false;
            }
        }
    }
    return true;
}

bool RingGeometry::setSurfaceNormal(std::vector<double> surfaceNormal)
{
    if(surfaceNormal.size()!= 3) {
        STADIC_ERROR("The setting of the ring surface normal has failed - the surface normal must contain 3 values (ex. x y z).");
        return false;
    } else {
        for(int i=0;i<3;i++) {
            if(!setArg3(stadic::toString(surfaceNormal[i]), i+3)){
                return false;
            }
        }
    }
    return true;
}

bool RingGeometry::setInnerRadius(double radius)
{
    if (radius<0){
        STADIC_ERROR("The radius of a ring cannot be negative.");
        return false;
    } else {
        if(setArg3(stadic::toString(radius), 6)){
            return true;
        }
    }
    return false;
}

bool RingGeometry::setOuterRadius(double radius){
    if (radius<=0&&innerRadius()==0){
        STADIC_ERROR("The radius of a ring cannot be negative.  At least one radii has to be greater than 0.");
        return false;
    } else {
        if(setArg3(stadic::toString(radius), 7)){
            return true;
        }
    }
    return false;
}

// Getters
std::vector<double> RingGeometry::centerPoint() const
{
    std::vector<double> cPoint;
    cPoint.push_back(toDouble(getArg3(0)));
    cPoint.push_back(toDouble(getArg3(1)));
    cPoint.push_back(toDouble(getArg3(2)));
    return cPoint;
}

std::vector<double> RingGeometry::surfaceNormal() const
{
    std::vector<double> surfaceNormal;
    surfaceNormal.push_back(toDouble(getArg3(3)));
    surfaceNormal.push_back(toDouble(getArg3(4)));
    surfaceNormal.push_back(toDouble(getArg3(5)));
    return surfaceNormal;
}

//Add getters and setters for R1 and R2, but only getters for inner and outer radius
double RingGeometry::innerRadius() const
{
    return toDouble(getArg3(6));
}

double RingGeometry::outerRadius() const
{
    return toDouble(getArg3(7));
}

//Protected
bool RingGeometry::validateArg3(const std::string &value, int position) const
{
    bool ok;
    stadic::toDouble(value, &ok);
    if(ok){
        if(position<8){
            return true;
        }
    }
    return false;
}
/*
bool RingGeometry::validateArg(int number, std::string value, int position) const
{
    if(number==3) {
        bool ok;
        double dval = stadic::toDouble(value, &ok);
        if (ok){
            if (position<8){
                return true;
            }
        }
    }
    return false;
}

bool RingGeometry::validateArg(int number, std::vector<std::string> arg) const
{
    if(number==3) {
        if(arg.size() != 8) {
            return false;
        }
        for(std::string value : arg) {
            bool ok;
            double dval = stadic::toDouble(value, &ok);
            if(ok) {
                return true;
            }
        }
    }
    return false;
}
*/

}
