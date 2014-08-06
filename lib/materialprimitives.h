#ifndef MATERIALPRIMITIVES_H
#define MATERIALPRIMITIVES_H
#include "radprimitive.h"

#include "stadicapi.h"

namespace stadic{
//PLASTIC
class STADIC_API PlasticMaterial : public RadPrimitive
{
public:
    explicit PlasticMaterial(QObject *parent=0);
    PlasticMaterial(double red, double green, double blue, double spec, double rough, QObject *parent=0);

    // Setters
    bool setType(QString){return false;}
    bool setRed(double value);
    bool setGreen(double value);
    bool setBlue(double value);
    bool setSpecularity(double value);
    bool setRoughness(double value);
    // Getters
    double red() const;
    double green() const;
    double blue() const;
    double specularity() const;
    double roughness() const;
private:
   virtual bool validateArg(int number, QString value, int position) const;
   virtual bool validateArg(int number, std::vector<QString> value) const;
};
//METAL
class STADIC_API MetalMaterial : public RadPrimitive
{
public:
    explicit MetalMaterial(QObject *parent=0);
    MetalMaterial(double red, double green, double blue, double spec, double rough, QObject *parent=0);

    // Setters
    bool setType(QString){return false;}
    bool setRed(double value);
    bool setGreen(double value);
    bool setBlue(double value);
    bool setSpecularity(double value);
    bool setRoughness(double value);
    // Getters
    double red() const;
    double green() const;
    double blue() const;
    double specularity() const;
    double roughness() const;
private:
   virtual bool validateArg(int number, QString value, int position) const;
   virtual bool validateArg(int number, std::vector<QString> value) const;
};
//TRANS
class STADIC_API TransMaterial : public RadPrimitive
{
public:
    explicit TransMaterial(QObject *parent=0);
    TransMaterial(double red, double green, double blue, double spec, double rough, double trans, double transpec, QObject *parent=0);

    // Setters
    bool setType(QString){return false;}
    bool setRed(double value);
    bool setGreen(double value);
    bool setBlue(double value);
    bool setSpecularity(double value);
    bool setRoughness(double value);
    bool setTransmission(double value);
    bool setTransmissivity(double value);
    bool setTransSpecular(double value);

    // Getters
    double red() const;
    double green() const;
    double blue() const;
    double specularity() const;
    double roughness() const;
    double transmissivity() const;
    double transSpecular() const;

private:
   virtual bool validateArg(int number, QString value, int position) const;
   virtual bool validateArg(int number, std::vector<QString> value) const;
};
//GLASS
class STADIC_API GlassMaterial : public RadPrimitive
{
public:
    explicit GlassMaterial(QObject *parent=0);
    GlassMaterial(double redTrans, double greenTrans, double blueTrans, QObject *parent);
    GlassMaterial(double redTrans, double greenTrans, double blueTrans, double refrac, QObject *parent);
    // Setters
    bool setType(QString){return false;}
    bool setRedTrans(double value);
    bool setGreenTrans(double value);
    bool setBlueTrans(double value);
    bool setRefraction(double value);

    // Getters
    double redTrans() const;
    double greenTrans() const;
    double blueTrans() const;
    double refraction() const;

private:
   virtual bool validateArg(int number, QString value, int position) const;
   virtual bool validateArg(int number, std::vector<QString> value) const;
};
//BSDF
class STADIC_API BSDFMaterial : public RadPrimitive
{
public:
    explicit BSDFMaterial(QObject *parent=0);
    BSDFMaterial(double thickness, QString BSDFfile, double ux, double uy, double uz, QObject *parent);

    // Setters
    bool setType(QString){return false;}
    bool setThickness(double value);
    bool setBSDFfile(QString name);
    bool setUX(double value);
    bool setUY(double value);
    bool setUZ(double value);
    // Getters
    double thickness() const;
    QString bsdfFile() const;
    double ux() const;
    double uy() const;
    double uz() const;
private:
   virtual bool validateArg(int number, QString value, int position) const;
   virtual bool validateArg(int number, std::vector<QString> value) const;
};
}
#endif // MATERIALPRIMITIVES_H
