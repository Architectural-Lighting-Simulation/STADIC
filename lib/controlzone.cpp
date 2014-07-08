#include "controlzone.h"
#include <iostream>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

ControlZone::ControlZone(QObject *parent) :
    QObject(parent)
{
}

//Setters
bool ControlZone::setOptimumMethod(QString method){
    if (method=="on" || method=="off" || method=="dim_to_min" || method=="dim_to_off" || method=="switched"){
        m_OptimumMethod=method;
    }else{
        std::cerr<<"ERROR: The \"optimum_control\" is not an acceptable string."<<std::endl;
        std::cerr<<"\tThe following values are allowed: \"on\", \"off\", \"dim_to_min\", \"dim_to_off\", \"switched\"."<<std::endl;
        return false;
    }
    return true;
}

bool ControlZone::setCPMethod(QString method){
    if (method=="auto" || method=="user"){
        m_CPMethod=method;
    }else{
        std::cerr<<"ERROR: The \"cp_method\" is not an acceptable string."<<std::endl;
        std::cerr<<"\tThe following values are allowed: \"auto\" or \"user\""<<std::endl;
        return false;
    }
    return true;
}
void ControlZone::setNumCPs(int value){
    m_NumCPs=value;
}
void ControlZone::setTargetPercentage(double value){
    if (value>=0 && value<1){
        m_TargetPercentage=value;
    }else{
        std::cerr<<"WARNING: The \"target_percentage\" must be between 0 and 1.  A value of 0.10 will be assumed."<<std::endl;
        m_TargetPercentage=0.1;
    }
}
void ControlZone::setExcludedPoints(QString file){
    m_ExcludedPoints=file;
}
bool ControlZone::setCriticalPoints(int point){
    if (point>0){
        m_CriticalPoints.push_back(point);
    }else{
        std::cerr<<"ERROR: The \"points\" listing for critical points must be greater than 0."<<std::endl;
        return false;
    }
    return true;
}
void ControlZone::setMaximumBFSignal(double value){
    m_MaximumBFSignal=value;
}
void ControlZone::setMinimumBFSignal(double value){
    m_MinimumBFSignal=value;
}
void ControlZone::setOffSignal(double value){
    m_OffSignal=value;
}
void ControlZone::setOnSignal(double value){
    m_OnSignal=value;
}
void ControlZone::setSetpointSignal(double value){
    m_SetpointSignal=value;
}
void ControlZone::setSignal(double value){
    m_Signal=value;
}
void ControlZone::setDimmingLevel(double value){
    m_DimmingLevel=value;
}
void ControlZone::setSignalToBFFile(QString file){
    m_SignalToBFFile=file;
}
bool ControlZone::setSensorType(QString type){
    if (type=="sensitivity_file"){
        m_SensorType=type;
    }else{
        std::cerr<<"ERROR: The key \"sensor_type\" does not contain an acceptable type."<<std::endl;
        std::cerr<<"\tThe acceptable type is as follows: \"sensitivity_file\""<<std::endl;
        return false;
    }
    return true;
}
void ControlZone::setSensorFile(QString file){
    m_SensorFile=file;
}
bool ControlZone::setSensorLocation(double x, double y, double z, double xd, double yd, double zd, double spin){
    if (spin>-360 && spin<360){
        m_SensorLocation.clear();
        m_SensorLocation.push_back(x);
        m_SensorLocation.push_back(y);
        m_SensorLocation.push_back(z);
        m_SensorLocation.push_back(xd);
        m_SensorLocation.push_back(yd);
        m_SensorLocation.push_back(zd);
        m_SensorLocation.push_back(spin);
    }else{
        std::cerr<<"ERROR: The key \"spin_ccw\" must contain a value between -360 and 360."<<std::endl;
        return false;
    }
    return true;
}
bool ControlZone::setAlgorithm(QString algorithm){
    if (algorithm=="open_dimming" || algorithm=="closed_proportional" || algorithm=="constant_setpoint" || algorithm=="open_switching" || algorithm=="closed_switching" || algorithm=="user_defined_1"){
        m_Algorithm=algorithm;
    }else{
        std::cerr<<"ERROR: The algorithm is not an acceptable string."<<std::endl;
        std::cerr<<"\tThe following values are allowed:\n\t\t\"open_dimming\"\n\t\t\"closed_proportional\"\n\t\t\"constant_setpoint\"\n\t\t\"open_switching\"\n\t\t\"closed_switching\"\n\t\t\"user_defined_1\""<<std::endl;
        return false;
    }
    return true;
}
void ControlZone::setIESFile(QString file){
    m_IESFile=file;
}
bool ControlZone::setLLF(double value){
    if (value>0){
        m_LLF=value;
    }else{
        std::cerr<<"ERROR: The \"LLF\" must be greater than 0."<<std::endl;
        return false;
    }
    return true;
}
bool ControlZone::setLampLumens(int value){
    if (value>0){
        m_LampLumens=value;
    }else{
        std::cerr<<"ERROR: The \"lamp_lumens\" must be greater than 0."<<std::endl;
        return false;
    }
    return true;
}
bool ControlZone::setBallastType(QString type){
    if (type=="linear_dimming" || type=="non_dimming"){
        m_BallastType=type;
    }else{
        std::cerr<<"ERROR: The \"ballast_type\" is not an approved type."<<std::endl;
        std::cerr<<"\tThe approved types are as follows: \"linear_dimming\" and \"non_dimming\""<<std::endl;
        return false;
    }
    return true;
}
bool ControlZone::setBFMin(double value){
    if (value>=0 && value<3){
        m_BFMin=value;
    }else{
        std::cerr<<"WARNING: The \"bf_min\" must be greater than or equal to 0."<<std::endl;
        return false;
    }
    return true;
}
bool ControlZone::setBFMax(double value){
    if (value>=0 && value<3){
        m_BFMax=value;
    }else{
        std::cerr<<"WARNING: The \"bf_max\" must be between 0 and 3."<<std::endl;
        return false;
    }
    return true;
}
bool ControlZone::setWattsMax(double value){
    if (value>=0){
        m_WattsMax=value;
    }else{
        std::cerr<<"ERROR: The \"watts_max\" must be greater than 0."<<std::endl;
        return false;
    }
    return true;
}
bool ControlZone::setWattsMin(double value){
    if (value>=0){
        m_WattsMin=value;
    }else{
        std::cerr<<"ERROR: The \"watts_min\" must be greater than 0."<<std::endl;
        return false;
    }
    return true;
}
bool ControlZone::setBallastFactor(double value){
    if (value>=0 && value<3){
        m_BallastFactor=value;
    }else{
        std::cerr<<"WARNING: The \"ballast_factor\" must be between 0 and 3."<<std::endl;
        return false;
    }
    return true;
}
bool ControlZone::setWatts(double value){
    if (value<0){
        m_Watts=value;
    }else{
        std::cerr<<"ERROR: The \"watts\" must be greater than 0."<<std::endl;
        return false;
    }
    return true;
}
bool ControlZone::setLuminaireLayout(double x, double y, double z, double rotation, double tilt, double spin){
    std::vector<double> tempVector;
    tempVector.push_back(x);
    tempVector.push_back(y);
    tempVector.push_back(z);
    if (rotation>-360 && rotation<360){
        tempVector.push_back(rotation);
    }else{
        std::cerr<<"ERROR: The key \"rotation\" must be between -360 and 360."<<std::endl;
        return false;
    }
    if (tilt>-360 && tilt<360){
        tempVector.push_back(tilt);
    }else{
        std::cerr<<"ERROR: The key \"tilt\" must be between -360 and 360."<<std::endl;
        return false;
    }
    if (spin>-360 && spin<360){
        tempVector.push_back(spin);
    }else{
        std::cerr<<"ERROR: The key \"spin\" must be between -360 and 360."<<std::endl;
        return false;
    }
    m_LuminaireLayout.push_back(tempVector);
    return true;
}



//Getters
QString ControlZone::optimumMethod(){
    return m_OptimumMethod;
}
QString ControlZone::cpMethod(){
    return m_CPMethod;
}
int ControlZone::numCPs(){
    return m_NumCPs;
}
double ControlZone::targetPercentage(){
    return m_TargetPercentage;
}
QString ControlZone::excludedPoints(){
    return m_ExcludedPoints;
}
std::vector<int> ControlZone::criticalPoints(){
    return m_CriticalPoints;
}
double ControlZone::maximumBFSignal(){
    return m_MaximumBFSignal;
}
double ControlZone::minimumBFSignal(){
    return m_MinimumBFSignal;
}
double ControlZone::offSignal(){
    return m_OffSignal;
}
double ControlZone::setpointSignal(){
    return m_SetpointSignal;
}
double ControlZone::onSignal(){
    return m_OnSignal;
}
double ControlZone::signal(){
    return m_Signal;
}
double ControlZone::dimmingLevel(){
    return m_DimmingLevel;
}
QString ControlZone::signalToBFFile(){
    return m_SignalToBFFile;
}
QString ControlZone::sensorType(){
    return m_SensorType;
}
QString ControlZone::sensorFile(){
    return m_SensorFile;
}
std::vector<double> ControlZone::sensorLocation(){
    return m_SensorLocation;
}
QString ControlZone::algorithm(){
    if (m_Algorithm.isEmpty()){
        m_Algorithm="null";
    }
    return m_Algorithm;
}
QString ControlZone::iesFile(){
    return m_IESFile;
}
double ControlZone::llf(){
    return m_LLF;
}
int ControlZone::lampLumens(){
    return m_LampLumens;
}
QString ControlZone::ballastType(){
    return m_BallastType;
}
double ControlZone::bfMin(){
    return m_BFMin;
}
double ControlZone::bfMax(){
    return m_BFMax;
}
double ControlZone::wattsMax(){
    return m_WattsMax;
}
double ControlZone::wattsMin(){
    return m_WattsMin;
}
double ControlZone::ballastFactor(){
    return m_BallastFactor;
}
double ControlZone::watts(){
    return m_Watts;
}
std::vector<std::vector<double> > ControlZone::luminaireLayout(){
    return m_LuminaireLayout;
}




bool ControlZone::parseJson(const QJsonObject &object){
    QJsonValue val=object.value("name");
    if (val.isUndefined()){
        std::cerr<<"ERROR: The key \"name\" is not found within \"control_zones\"."<<std::endl;
        return false;
    }else{
        if (val.isString()){
            setObjectName(val.toString());
        }else{
            std::cerr<<"ERROR: The key\"name\" does not contain a string."<<std::endl;
            return false;
        }
    }

    val=object.value("optimum_control");
    if (val.isUndefined()){
        std::cerr<<"ERROR: The key\"optimum_control\" is not found within \"control_zones\"."<<std::endl;
        return false;
    }else{
        if (val.isString()){
            if (!setOptimumMethod(val.toString())){
                return false;
            }
        }else{
            std::cerr<<"ERROR: The key \"optimum_control\" does not contain a string."<<std::endl;
            return false;
        }
    }

    val=object.value("sensor");
    if (val.isUndefined()){
        std::cerr<<"WARNING: The zone named \""<<objectName().toStdString()<<"\" does not have a photosensor."<<std::endl;
    }else{
        if (val.isObject()){
            QJsonObject tempObject=val.toObject();
            val=tempObject.value("sensor_type");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key \"sensor_type\" is not found within \"sensor\" in the zone named \""<<objectName().toStdString()<<"\"."<<std::endl;
                return false;
            }else{
                if (val.isString()){
                    setSensorType(val.toString());
                }else{
                    std::cerr<<"The key \"sensor_type\" does not contain a string in the zone named \""<<objectName().toStdString()<<"\"."<<std::endl;
                    return false;
                }
            }

            val=tempObject.value("sensor_file");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key \"sensor_file\" is not found within \"sensor\" in the zone named \""<<objectName().toStdString()<<"\"."<<std::endl;
                return false;
            }else{
                if (val.isString()){
                    setSensorFile(val.toString());
                }else{
                    std::cerr<<"The key \"sensor_file\" does not contain a string in the zone named \""<<objectName().toStdString()<<"\"."<<std::endl;
                    return false;
                }
            }
            val=tempObject.value("location");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key \"location\" is not found for the sensor in the zone named \""<<objectName().toStdString()<<"\"."<<std::endl;
                return false;
            }else{
                if (val.isObject()){
                    QJsonObject tempObject2=val.toObject();
                    double x, y, z, xd, yd, zd, spin;
                    val=tempObject2.value("x");
                    if (val.isUndefined()){
                        std::cerr<<"ERROR: The key \"x\" was not found for the sensor location in the zone named \""<<objectName().toStdString()<<"\"."<<std::endl;
                        return false;
                    }else{
                        if (val.isDouble()){
                            x=val.toDouble();
                        }else{
                            std::cerr<<"ERROR: The key \"x\" for the sensor location in the zone named \""<<objectName().toStdString()<<"\" does not contain a number."<<std::endl;
                            return false;
                        }
                    }

                    val=tempObject2.value("y");
                    if (val.isUndefined()){
                        std::cerr<<"ERROR: The key \"y\" was not found for the sensor location in the zone named \""<<objectName().toStdString()<<"\"."<<std::endl;
                        return false;
                    }else{
                        if (val.isDouble()){
                            y=val.toDouble();
                        }else{
                            std::cerr<<"ERROR: The key \"y\" for the sensor location in the zone named \""<<objectName().toStdString()<<"\" does not contain a number."<<std::endl;
                            return false;
                        }
                    }

                    val=tempObject2.value("z");
                    if (val.isUndefined()){
                        std::cerr<<"ERROR: The key \"z\" was not found for the sensor location in the zone named \""<<objectName().toStdString()<<"\"."<<std::endl;
                        return false;
                    }else{
                        if (val.isDouble()){
                            z=val.toDouble();
                        }else{
                            std::cerr<<"ERROR: The key \"z\" for the sensor location in the zone named \""<<objectName().toStdString()<<"\" does not contain a number."<<std::endl;
                            return false;
                        }
                    }

                    val=tempObject2.value("xd");
                    if (val.isUndefined()){
                        std::cerr<<"ERROR: The key \"xd\" was not found for the sensor location in the zone named \""<<objectName().toStdString()<<"\"."<<std::endl;
                        return false;
                    }else{
                        if (val.isDouble()){
                            xd=val.toDouble();
                        }else{
                            std::cerr<<"ERROR: The key \"xd\" for the sensor location in the zone named \""<<objectName().toStdString()<<"\" does not contain a number."<<std::endl;
                            return false;
                        }
                    }

                    val=tempObject2.value("yd");
                    if (val.isUndefined()){
                        std::cerr<<"ERROR: The key \"yd\" was not found for the sensor location in the zone named \""<<objectName().toStdString()<<"\"."<<std::endl;
                        return false;
                    }else{
                        if (val.isDouble()){
                            yd=val.toDouble();
                        }else{
                            std::cerr<<"ERROR: The key \"yd\" for the sensor location in the zone named \""<<objectName().toStdString()<<"\" does not contain a number."<<std::endl;
                            return false;
                        }
                    }

                    val=tempObject2.value("zd");
                    if (val.isUndefined()){
                        std::cerr<<"ERROR: The key \"zd\" was not found for the sensor location in the zone named \""<<objectName().toStdString()<<"\"."<<std::endl;
                        return false;
                    }else{
                        if (val.isDouble()){
                            zd=val.toDouble();
                        }else{
                            std::cerr<<"ERROR: The key \"zd\" for the sensor location in the zone named \""<<objectName().toStdString()<<"\" does not contain a number."<<std::endl;
                            return false;
                        }
                    }

                    val=tempObject2.value("spin_ccw");
                    if (val.isUndefined()){
                        std::cerr<<"ERROR: The key \"spin_ccw\" was not found for the sensor location in the zone named \""<<objectName().toStdString()<<"\"."<<std::endl;
                        return false;
                    }else{
                        if (val.isDouble()){
                            spin=val.toDouble();
                        }else{
                            std::cerr<<"ERROR: The key \"spin_ccw\" for the sensor location in the zone named \""<<objectName().toStdString()<<"\" does not contain a number."<<std::endl;
                            return false;
                        }
                    }
                    if (!setSensorLocation(x, y, z, xd, yd, zd, spin)){
                        return false;
                    }
                }else{
                    std::cerr<<"ERROR: The key \"location\" for the sensor in the zone named \""<<objectName().toStdString()<<"\" is not an object."<<std::endl;
                    return false;
                }
            }


        }else{
            std::cerr<<"ERROR: The key \"sensor\" in the zone named \""<<objectName().toStdString()<<"\" does not contain an object."<<std::endl;
            return false;
        }
    }

    val=object.value("cp_method");
    if (val.isUndefined()){
        std::cerr<<"WARNING: The key \"cp_method\" does not appear in the zone named \""<<objectName().toStdString()<<"\"."<<std::endl;
    }else{
        if (val.isString()){
            if (!setCPMethod(val.toString())){
                return false;
            }else{
                if (cpMethod()=="auto"){
                    val=object.value("quantity");
                    if (val.isUndefined()){
                        std::cerr<<"ERROR: The key \"quantity\" is needed with \"cp_method\" when auto is specified."<<std::endl;
                        return false;
                    }else{
                        if (val.isDouble()){
                            setNumCPs(int(val.toDouble()));
                        }else{
                            std::cerr<<"ERROR: The key \"quantity\" does not contain a number."<<std::endl;
                            return false;
                        }
                    }
                    val=object.value("target_percentage");
                    if (val.isUndefined()){
                        std::cerr<<"WARNING: The key \"target_percentage\" is needed with \"cp_method\" when auto is specified.  A value of 0.10 will be assumed."<<std::endl;
                        setTargetPercentage(0.1);
                    }else{
                        if (val.isDouble()){
                            setTargetPercentage(val.toDouble());
                        }else{
                            std::cerr<<"WARNING: The key \"target_percentage\" does not contain a number.  A value of 0.10 will be assumed."<<std::endl;
                            setTargetPercentage(0.1);
                        }
                    }
                    val=object.value("excluded_points");
                    if (val.isUndefined()){
                        std::cerr<<"WARNING: No excluded points file is being used for the critical point analysis for control zone named \""<<objectName().toStdString()<<"\"."<<std::endl;
                    }else{
                        if (val.isString()){
                            setExcludedPoints(val.toString());
                        }else{
                            std::cerr<<"ERROR: The key \"excluded_points\" does not contain a string."<<std::endl;
                            return false;
                        }
                    }
                }else if(cpMethod()=="user"){
                    val=object.value("points");
                    if (val.isUndefined()){
                        std::cerr<<"ERROR: The key \"points\" is needed with \"cp_method\" when user is specified."<<std::endl;
                        return false;
                    }else{
                        if (val.isArray()){
                            QJsonArray array=val.toArray();
                            for (int j=0;j<array.size();j++){
                                if (array.at(j).isDouble()){
                                    if (!setCriticalPoints(int(array.at(j).toDouble()))){
                                        return false;
                                    }
                                }else{
                                    std::cerr<<"ERROR: The key \"points\" has an entry that is not a number."<<std::endl;
                                    return false;
                                }
                            }
                        }else{
                            std::cerr<<"ERROR: The key \"points\" is not an array."<<std::endl;
                            return false;
                        }
                    }
                }
            }
        }else{
            std::cerr<<"ERROR: The key \"cp_method\" in the zone named \""<<objectName().toStdString()<<"\" does not contain a string."<<std::endl;
            return false;
        }
    }

    val=object.value("open_dimming");
    if (!val.isUndefined()){
        if (val.isObject()){
            QJsonObject tempObject=val.toObject();
            val=tempObject.value("maximum_bf_signal");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key\"maximum_bf_signal\" is needed with the \"open_dimming\" algorithm."<<std::endl;
                return false;
            }else{
                if (val.isDouble()){
                    setMaximumBFSignal(val.toDouble());
                }else{
                    std::cerr<<"ERROR: The key \"maximum_bf_signal\" does not contain a number."<<std::endl;
                    return false;
                }
            }
            val=tempObject.value("minimum_bf_signal");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key\"minimum_bf_signal\" is needed with the \"open_dimming\" algorithm."<<std::endl;
                return false;
            }else{
                if (val.isDouble()){
                    setMinimumBFSignal(val.toDouble());
                }else{
                    std::cerr<<"ERROR: The key \"minimum_bf_signal\" does not contain a number."<<std::endl;
                    return false;
                }
            }
            val=tempObject.value("off_signal");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key\"off_signal\" is needed with the \"open_dimming\" algorithm."<<std::endl;
                return false;
            }else{
                if (val.isDouble()){
                    setOffSignal(val.toDouble());
                }else{
                    std::cerr<<"ERROR: The key \"off_signal\" does not contain a number."<<std::endl;
                    return false;
                }
            }
        }else{
            std::cerr<<"ERROR: The key \"open_dimming\" does not contain an object."<<std::endl;
            return false;
        }
    }
    val=object.value("closed_proportional");
    if (!val.isUndefined()){
        if (val.isObject()){
            QJsonObject tempObject=val.toObject();
            val=tempObject.value("maximum_bf_signal");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key\"maximum_bf_signal\" is needed with the \"closed_proportional\" algorithm."<<std::endl;
                return false;
            }else{
                if (val.isDouble()){
                    setMaximumBFSignal(val.toDouble());
                }else{
                    std::cerr<<"ERROR: The key \"maximum_bf_signal\" does not contain a number."<<std::endl;
                    return false;
                }
            }
            val=tempObject.value("minimum_bf_signal");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key\"minimum_bf_signal\" is needed with the \"closed_proportional\" algorithm."<<std::endl;
                return false;
            }else{
                if (val.isDouble()){
                    setMinimumBFSignal(val.toDouble());
                }else{
                    std::cerr<<"ERROR: The key \"minimum_bf_signal\" does not contain a number."<<std::endl;
                    return false;
                }
            }
            val=tempObject.value("off_signal");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key\"off_signal\" is needed with the \"closed_proportional\" algorithm."<<std::endl;
                return false;
            }else{
                if (val.isDouble()){
                    setOffSignal(val.toDouble());
                }else{
                    std::cerr<<"ERROR: The key \"off_signal\" does not contain a number."<<std::endl;
                    return false;
                }
            }
        }else{
            std::cerr<<"ERROR: The key \"closed_proportional\" does not contain an object."<<std::endl;
            return false;
        }
    }

    val=object.value("constant_setpoint");
    if (!val.isUndefined()){
        if (val.isObject()){
            QJsonObject tempObject=val.toObject();
            val=tempObject.value("setpoint_signal");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key \"setpoint_signal\" is needed with the \"constant_setpoint\" algorithm."<<std::endl;
                return false;
            }else{
                if (val.isDouble()){
                    setSetpointSignal(val.toDouble());
                }else{
                    std::cerr<<"ERROR: The key \"setpoint_signal\" does not contain a number."<<std::endl;
                    return false;
                }
            }
            val=tempObject.value("off_signal");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key \"off_signal\" is needed with the \"constant_setpoint\" algorithm."<<std::endl;
                return false;
            }else{
                if (val.isDouble()){
                    setOffSignal(val.toDouble());
                }else{
                    std::cerr<<"ERROR: The key \"off_signal\" does not contain a number."<<std::endl;
                    return false;
                }
            }
        }else{
            std::cerr<<"ERROR: The key \"constant_setpoint\" does not contain an object."<<std::endl;
            return false;
        }
    }

    val=object.value("open_switching");
    if (!val.isUndefined()){
        if (val.isObject()){
            QJsonObject tempObject=val.toObject();
            val=tempObject.value("off_signal");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key \"off_signal\" is needed with the \"open_switching\" algorithm."<<std::endl;
                return false;
            }else{
                if (val.isDouble()){
                    setOffSignal(val.toDouble());
                }else{
                    std::cerr<<"ERROR: The key \"off_signal\" does not contain a number."<<std::endl;
                    return false;
                }
            }
            val=tempObject.value("on_signal");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key \"on_signal\" is needed with the \"open_switching\" algorithm."<<std::endl;
                return false;
            }else{
                if (val.isDouble()){
                    setOnSignal(val.toDouble());
                }else{
                    std::cerr<<"ERROR: The key \"on_signal\" does not contain a number."<<std::endl;
                    return false;
                }
            }
        }else{
            std::cerr<<"ERROR: The key \"open_switching\" does not contain an object."<<std::endl;
            return false;
        }
    }

    val=object.value("closed_switching");
    if (!val.isUndefined()){
        if (val.isObject()){
            QJsonObject tempObject=val.toObject();
            val=tempObject.value("off_signal");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key \"off_signal\" is needed with the \"closed_switching\" algorithm."<<std::endl;
                return false;
            }else{
                if (val.isDouble()){
                    setOffSignal(val.toDouble());
                }else{
                    std::cerr<<"ERROR: The key \"off_signal\" does not contain a number."<<std::endl;
                    return false;
                }
            }
            val=tempObject.value("on_signal");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key \"on_signal\" is needed with the \"closed_switching\" algorithm."<<std::endl;
                return false;
            }else{
                if (val.isDouble()){
                    setOnSignal(val.toDouble());
                }else{
                    std::cerr<<"ERROR: The key \"on_signal\" does not contain a number."<<std::endl;
                    return false;
                }
            }
        }else{
            std::cerr<<"ERROR: The key \"closed_switching\" does not contain an object."<<std::endl;
            return false;
        }
    }

    val=object.value("user_defined_1");
    if (val.isUndefined()){
        if (val.isObject()){
            QJsonObject tempObject=val.toObject();
            val=tempObject.value("signal");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key \"signal\" is needed with the \"user_defined_1\" algorithm."<<std::endl;
                return false;
            }else{
                if (val.isDouble()){
                    setSignal(val.toDouble());
                }else{
                    std::cerr<<"ERROR: The key \"signal\" does not contain a number."<<std::endl;
                    return false;
                }
            }
            val=tempObject.value("dimming_level");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key \"dimming_level\" is needed with the \"user_defined_1\" algorithm."<<std::endl;
                return false;
            }else{
                if (val.isDouble()){
                    setDimmingLevel(val.toDouble());
                }else{
                    std::cerr<<"ERROR: The key \"dimming_level\" does not contain a number."<<std::endl;
                    return false;
                }
            }
            val=tempObject.value("signal_to_bf_file");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key \"signal_to_bf_file\" is needed with the \"user_defined_1\" algorithm."<<std::endl;
                return false;
            }else{
                if (val.isString()){
                    setSignalToBFFile(val.toString());
                }else{
                    std::cerr<<"ERROR: The key \"signal_to_bf_file\" does not contain a string."<<std::endl;
                    return false;
                }
            }
        }else{
            std::cerr<<"ERROR: The key \"user_defined_1\" does not contain an object."<<std::endl;
            return false;
        }
    }
    //After parsing for the algorithm test to see if the algorithm has been set.  Alert user if it hasn't been set
    if (algorithm()=="null"){
        std::cerr<<"WARNING: There is no algorithm specified for the control zone named \""<<objectName().toStdString()<<"\"."<<std::endl;
        return false;
    }

    val=object.value("luminaire_information");
    if (val.isUndefined()){
        std::cerr<<"ERROR: The key \"luminaire_information\" is needed for a control zone."<<std::endl;
        return false;
    }else{
        if (val.isObject()){
            QJsonObject tempObject=val.toObject();
            val=tempObject.value("ies_file");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key \"ies_file\" is needed within \"luminaire_information\"."<<std::endl;
                return false;
            }else{
                if (val.isString()){
                    setIESFile(val.toString());
                }else{
                    std::cerr<<"ERROR: The key \"ies_file\" is not a string."<<std::endl;
                    return false;
                }
            }
            val=tempObject.value("LLF");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key \"LLF\" is needed within \"luminaire_information\"."<<std::endl;
                return false;
            }else{
                if (val.isDouble()){
                    if (!setLLF(val.toDouble())){
                        return false;
                    }
                }else{
                    std::cerr<<"ERROR: The key \"LLF\" is not a number."<<std::endl;
                    return false;
                }
            }
            val=tempObject.value("lamp_lumens");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key \"lamp_lumens\" is needed within \"luminaire_information\"."<<std::endl;
                return false;
            }else{
                if (val.isDouble()){
                    if(!setLampLumens(val.toDouble())){
                        return false;
                    }
                }else{
                    std::cerr<<"ERROR: The key \"lamp_lumens\" is not a number."<<std::endl;
                    return false;
                }
            }

        }else{
            std::cerr<<"ERROR: The key \"luminaire_information\" is not an object."<<std::endl;
            return false;
        }
    }

    val=object.value("ballast_driver_information");
    if (val.isUndefined()){
        std::cerr<<"ERROR: The key \"ballast_driver_information\" is needed within for a control zone."<<std::endl;
        return false;
    }else{
        if (val.isObject()){
            QJsonObject tempObject=val.toObject();
            val=tempObject.value("ballast_type");
            if (val.isUndefined()){
                std::cerr<<"ERROR: The key \"ballast_type\" is needed within \"ballast_driver_information\"."<<std::endl;
                return false;
            }else{
                if (val.isString()){
                    if (!setBallastType(val.toString())){
                        return false;
                    }else{
                        if (ballastType()=="linear_dimming"){
                            val=tempObject.value("bf_min");
                            if (val.isUndefined()){
                                std::cerr<<"ERROR: The key \"bf_min\" is needed for ballast type \"linear_dimming\"."<<std::endl;
                                return false;
                            }else{
                                if (val.isDouble()){
                                    if(!setBFMin(val.toDouble())){
                                        return false;
                                    }
                                }else{
                                    std::cerr<<"ERROR: The key \"bf_min\" is not a number."<<std::endl;
                                    return false;
                                }
                            }
                            val=tempObject.value("bf_max");
                            if (val.isUndefined()){
                                std::cerr<<"ERROR: The key \"bf_max\" is needed for ballast type \"linear_dimming\"."<<std::endl;
                                return false;
                            }else{
                                if (val.isDouble()){
                                    if (!setBFMin(val.toDouble())){
                                        return false;
                                    }
                                }else{
                                    std::cerr<<"ERROR: The key \"bf_max\" is not a number."<<std::endl;
                                    return false;
                                }
                            }
                            val=tempObject.value("watts_max");
                            if (val.isUndefined()){
                                std::cerr<<"ERROR: The key \"watts_max\" is needed for ballast type \"linear_dimming\"."<<std::endl;
                                return false;
                            }else{
                                if (val.isDouble()){
                                    if (!setWattsMax(val.toDouble())){
                                        return false;
                                    }
                                }else{
                                    std::cerr<<"ERROR: The key \"watts_max\" is not a number"<<std::endl;
                                    return false;
                                }
                            }
                            val=tempObject.value("watts_min");
                            if (val.isUndefined()){
                                std::cerr<<"ERROR: The key \"watts_min\" is needed for ballast type \"linear_dimming\"."<<std::endl;
                                return false;
                            }else{
                                if (val.isDouble()){
                                    if (!setWattsMin(val.toDouble())){
                                        return false;
                                    }
                                }else{
                                    std::cerr<<"ERROR: The key \"watts_min\" is not a number."<<std::endl;
                                    return false;
                                }
                            }
                        }else if (ballastType()=="non_dimming"){
                            val=tempObject.value("ballast_factor");
                            if (val.isUndefined()){
                               std::cerr<<"ERROR: The key \"ballast_factor\" is needed for ballast type \"non_dimming\"."<<std::endl;
                               return false;
                            }else{
                                if (val.isDouble()){
                                    if (!setBallastFactor(val.toDouble())){
                                        return false;
                                    }
                                }else{
                                    std::cerr<<"ERROR: The key \"ballast_factor\" is not a number."<<std::endl;
                                    return false;
                                }
                            }
                            val=tempObject.value("watts");
                            if (val.isUndefined()){
                                std::cerr<<"ERROR: The key \"watts\" is needed for ballast type \"non_dimming\"."<<std::endl;
                                return false;
                            }else{
                                if (val.isDouble()){
                                    if (!setWatts(val.toDouble())){
                                        return false;
                                    }
                                }else{
                                    std::cerr<<"ERROR: The key \"watts\" is not a number."<<std::endl;
                                    return false;
                                }
                            }
                        }
                    }
                }else{
                    std::cerr<<"ERROR: The key \"ballast_type\" is not a string."<<std::endl;
                    return false;
                }
            }

        }else{
            std::cerr<<"ERROR: The key \"ballast_driver_information\" is not an object."<<std::endl;
            return false;
        }
    }

    val=object.value("luminaire_layout");
    if (val.isUndefined()){
        std::cerr<<"ERROR: The key \"luminaire_layout\" is needed for a control zone."<<std::endl;
        return false;
    }else{
        if (val.isArray()){
            QJsonArray array=val.toArray();
            for (int i=0;i<array.size();i++){
                if (array.at(i).isObject()){
                    QJsonObject tempObject=array.at(i).toObject();
                    double x, y, z, rot, tilt, spin;
                    val=tempObject.value("x");
                    if (val.isUndefined()){
                        std::cerr<<"ERROR: The key \"x\" must be found within the \"luminaire_layout\" entries."<<std::endl;
                        return false;
                    }else{
                        if (val.isDouble()){
                            x=val.toDouble();
                        }else{
                            std::cerr<<"ERROR: The key \"x\" does not contain a number."<<std::endl;
                            return false;
                        }
                    }
                    val=tempObject.value("y");
                    if (val.isUndefined()){
                        std::cerr<<"ERROR: The key \"y\" must be found within the \"luminaire_layout\" entries."<<std::endl;
                        return false;
                    }else{
                        if (val.isDouble()){
                            y=val.toDouble();
                        }else{
                            std::cerr<<"ERROR: The key \"y\" does not contain a number."<<std::endl;
                            return false;
                        }
                    }
                    val=tempObject.value("z");
                    if (val.isUndefined()){
                        std::cerr<<"ERROR: The key \"z\" must be found within the \"luminaire_layout\" entries."<<std::endl;
                        return false;
                    }else{
                        if (val.isDouble()){
                            z=val.toDouble();
                        }else{
                            std::cerr<<"ERROR: The key \"z\" does not contain a number."<<std::endl;
                            return false;
                        }
                    }
                    val=tempObject.value("rotation");
                    if (val.isUndefined()){
                        std::cerr<<"ERROR: The key \"rotation\" must be found within the \"luminaire_layout\" entries."<<std::endl;
                        return false;
                    }else{
                        if (val.isDouble()){
                            rot=val.toDouble();
                        }else{
                            std::cerr<<"ERROR: The key \"rotation\" does not contain a number."<<std::endl;
                            return false;
                        }
                    }
                    val=tempObject.value("tilt");
                    if (val.isUndefined()){
                        std::cerr<<"ERROR: The key \"tilt\" must be found within the \"luminaire_layout\" entries."<<std::endl;
                        return false;
                    }else{
                        if (val.isDouble()){
                            tilt=val.toDouble();
                        }else{
                            std::cerr<<"ERROR: The key \"tilt\" does not contain a number."<<std::endl;
                            return false;
                        }
                    }
                    val=tempObject.value("spin_ccw");
                    if (val.isUndefined()){
                        std::cerr<<"ERROR: The key \"spin_ccw\" must be found within the \"luminaire_layout\" entries."<<std::endl;
                        return false;
                    }else{
                        if (val.isDouble()){
                            spin=val.toDouble();
                        }else{
                            std::cerr<<"ERROR: The key \"spin_ccw\" does not contain a number."<<std::endl;
                            return false;
                        }
                    }
                    if(!setLuminaireLayout(x, y, z, rot, tilt, spin)){
                        return false;
                    }
                }else{
                    std::cerr<<"ERROR: The key \"luminaire_layout\" contains a position that is not an object."<<std::endl;
                    return false;
                }
            }
        }else{
            std::cerr<<"ERROR: The key \"luminaire_layout\" is not an array."<<std::endl;
            return false;
        }
    }

    return true;
}
