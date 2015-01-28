/******************************************************************************
 * Copyright (c) 2014, The Pennsylvania State University
 * Copyright (c) 2015, Jason W. DeGraw
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

#ifndef RADPRIMITIVE_H
#define RADPRIMITIVE_H

#include <array>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include "stadicapi.h"
#include "functions.h"
#include "logging.h"
#include "sharedvector.h"
#include <boost/optional.hpp>

namespace stadic {

class STADIC_API RadPrimitive
{
public:
    enum Type {Source, Sphere, Bubble, Polygon, Cone, Cup, Cylinder, Tube, Ring, Instance,
               Mesh, Light, Illum, Glow, Spotlight, Mirror, Prism1, Prism2, Plastic, Metal,
               Trans, Plastic2, Metal2, Trans2, Mist, Dielectric, Interface, Glass, Plasfunc,
               Metfunc, Transfunc, BRTDfunc, Plasdata, Metdata, Transdata, BSDF, Antimatter,
               Texfunc, Texdata, Colorfunc, Brightfunc, Colordata, Brightdata, Colorpict, Colortext,
               Brighttext, Mixfunc, Mixdata, Mixpict, Mixtext, Unknown};
    RadPrimitive();
    virtual ~RadPrimitive()
    {}

    bool isGeometry() const;                                            //Boolean that determines whether the primitive is of a geometry type
    bool isMaterial() const;                                            //Boolean that determines whether the primitive is of a material type
	virtual bool isVoid() const
	{
		return false;
	}

    //Setters
    void setModifier(const std::string &modifier);                             //Function to set the modifier
    bool setModifierOverride(const std::string &name);  //!< Set the name of the modifier to use, overriding the modifier pointer
    virtual bool setType(const std::string &type);                             //Function to set the type
    void setName(const std::string &name);                                     //Function to set the name
    virtual bool setArg1(std::vector<std::string> vals);                //Function to set the argumens on line one from a vector of strings
    virtual bool setArg1(const std::string &arg, int position);                //Function to set an argument on line one given the position of the argument
    virtual bool setArg2(std::vector<std::string> vals);                //Function to set the arguments on line two from a vector of strings
    virtual bool setArg2(const std::string &arg, int position);                //Function to set an argument on line two given the position of the argument
    virtual bool setArg3(std::vector<std::string> vals);                //Function to set the arguments on line three from a vector of strings
    virtual bool setArg3(const std::string &arg, int position);                //Function to set an argument on line three given the position of the argument

    //Getters
    std::string modifierName() const;  //!< Returns the modifier name associated with the primitive
    boost::optional<std::string>  modifierOverride() const; //!< Returns the modifier name that will be used, if empty then the modifier pointer is used
    Type type() const;                                                  //Function that returns the type as a type
    std::string typeString() const;                                     //Function that returns the type as a string
    virtual std::string name() const;  //!< Returns the identifier of the primitive
    std::vector<std::string> arg1() const;                              //Function that returns the first line of arguments as a vector
    std::vector<std::string> arg2() const;                              //Function that returns the second line of arguments as a vector
    std::vector<std::string> arg3() const;                              //Function that returns the third line of arguments as a vector

    virtual std::string getArg1(int position) const; //!< Returns a given argument from the first line as a string, throws for out of range values
    virtual std::string getArg2(int position) const; //!< Returns a given argument from the second line as a string, throws for out of range values
    virtual std::string getArg3(int position) const; //!< Returns a given argument from the third line as a string, throws for out of range values
    virtual std::string getArg1(int position, const std::string &defaultValue) const; //!< Returns a given argument from the first line as a string or a default if the position is out of range
    virtual std::string getArg2(int position, const std::string &defaultValue) const; //!< Returns a given argument from the second line as a string or a default if the position is out of range
    virtual std::string getArg3(int position, const std::string &defaultValue) const; //!< Returns a given argument from the third line as a string or a default if the position is out of range

    std::string toRad() const;
    static RadPrimitive *fromRad(std::stringstream &data);
    static std::shared_ptr<RadPrimitive> fromRad(std::stringstream &data, const shared_vector<RadPrimitive> &knownPrimitives);
	static bool buildModifierTree(shared_vector<RadPrimitive> &primitives);
    static bool checkModifierTree(shared_vector<RadPrimitive> &primitives);
    static std::shared_ptr<RadPrimitive> sharedVoid();

protected:
    void initArg(int number, std::vector<std::string> arg);
    bool checkDoubleValue(const std::string &value, double min, double max, const std::string &variable, 
        double current) const;
    bool checkDoubleValue(const std::string &value, double min, double max, double recMin, double recMax,
        const std::string &variable, double current) const;
    bool checkDoubleValueMin(const std::string &value, double min, const std::string &variable,
        double current, bool inclusive) const;
    bool checkDoubleValue(const std::string &value, const std::string &variable, double current) const;
    double argToDouble(int number, int position, const std::string &variable) const;
    double argToDouble(int number, int position, const std::string &variable, double defaultValue) const;
    virtual bool setModifierName(const std::string &name);  //!< Set the modifier name if possible
    virtual bool validateArg1(const std::string &value, int position) const 
    {
        STADIC_LOG(Severity::Warning, "A " + typeString() + " primitive has no first argument in position "
            + stadic::toString(position));
        return false;
    }
    virtual bool validateArg1(const std::vector<std::string> &arg) const;
    virtual bool validateArg2(const std::string &value, int position) const
    {
        STADIC_LOG(Severity::Warning, "A " + typeString() + " primitive has no second argument in position "
            + stadic::toString(position));
        return false;
    }
    virtual bool validateArg2(const std::vector<std::string> &arg) const;
    virtual bool validateArg3(const std::string &value, int position) const
    {
        STADIC_LOG(Severity::Warning, "A " + typeString() + " primitive has no third argument in position "
            + stadic::toString(position));
        return false;
    }
    virtual bool validateArg3(const std::vector<std::string> &arg) const;
    virtual bool extendArg3() const { return false; }
    
private:
    static std::shared_ptr<RadPrimitive> s_void;
    static std::array<std::string,51> s_typeStrings;

    static Type typeFromString(const std::string &string);
    std::shared_ptr<RadPrimitive> findModifier(const std::string &name, const shared_vector<RadPrimitive> &knownPrimitives);

    std::string m_Modifier;                                             //Variable holding the modifier
    boost::optional<std::string> m_modifierName;
	std::shared_ptr<RadPrimitive> m_modifier;
    std::string m_TypeString;                                           //Variable holding the type
    std::string m_Name;                                                 //Variable holding the name
    std::vector<std::string> m_Arg1;                                    //Vector holding arguments on line 1
    std::vector<std::string> m_Arg2;                                    //Vector holding arguments on line 2
    std::vector<std::string> m_Arg3;                                    //Vector holding arguments on line 3

};

class STADIC_API UnknownPrimitive : public RadPrimitive
{
public:
    UnknownPrimitive()
    {}

protected:
    virtual bool validateArg1(const std::string &, int) const
    {
        return true;
    }
    virtual bool validateArg2(const std::string &, int) const
    {
        return true;
    }
    virtual bool validateArg3(const std::string &, int) const
    {
        return true;
    }
};

class STADIC_API VoidPrimitive : public RadPrimitive
{
public:
    VoidPrimitive()
    {}

	bool isVoid() const
	{
		return true;
	}

protected:
	virtual bool validateArg1(const std::string &, int) const
	{
		return false;
	}
	virtual bool validateArg2(const std::string &, int) const
	{
		return false;
	}
	virtual bool validateArg3(const std::string &, int) const
	{
		return false;
	}

};

}

#endif // RADPRIMITIVE_H
