#ifndef RADPRIMITIVE_H
#define RADPRIMITIVE_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include<array>

namespace stadic {

class RadPrimitive : public QObject
{
    Q_OBJECT
public:
    enum Type {Source, Sphere, Bubble, Polygon, Cone, Cup, Cylinder, Tube, Ring, Instance,
               Mesh, Light, Illum, Glow, Spotlight, Mirror, Prism1, Prism2, Plastic, Metal,
               Trans, Plastic2, Metal2, Trans2, Mist, Dielectric, Interface, Glass, Plasfunc,
               Metfunc, Transfunc, BRTDfunc, Plasdata, Metdata, Transdata, BSDF, Antimatter,
               Texfunc, Texdata, Colorfunc, Brightfunc, Colordata, Brightdata, Colorpict, Colortext,
               Brighttext, Mixfunc, Mixdata, Mixpict, Mixtext, Unknown};
    explicit RadPrimitive(QObject *parent = 0);

    bool isGeometry() const;
    bool isMaterial() const;

    //Setters
    void setModifier(QString modifier);
    virtual bool setType(QString type);
    void setName(QString name);
    bool setArg1(std::vector<QString> vals);
    bool setArg1(QString arg, int position);
    bool setArg2(std::vector<QString> vals);
    bool setArg2(QString arg, int position);
    bool setArg3(std::vector<QString> vals);
    bool setArg3(QString arg, int position);

    virtual bool setArg(int number, QString value, int position);

    //Getters
    QString modifier() const;
    Type type() const;
    QString typeString() const;
    QString name() const;
    std::vector<QString> arg1() const;
    std::vector<QString> arg2() const;
    std::vector<QString> arg3() const;

    virtual QString getArg1(int position) const;
    virtual QString getArg2(int position) const;
    virtual QString getArg3(int position) const;
    virtual QString getArg(int number, int position) const;

    static RadPrimitive *fromRad(QTextStream &data, QObject *parent = 0);

protected:
    void initArg(int number, std::vector<QString> arg);

private:
    virtual bool validateArg(int number, QString value, int position) const {return true;}
    virtual bool validateArg(int number, std::vector<QString> value) const {return true;}
    static std::array<QString,51> s_typeStrings;
    static Type typeFromString(QString string);

    QString m_Modifier;
    QString m_TypeString;
    QString m_Name;
    std::vector<QString> m_Arg1;
    std::vector<QString> m_Arg2;
    std::vector<QString> m_Arg3;

signals:

public slots:

};



}

#endif // RADPRIMITIVE_H