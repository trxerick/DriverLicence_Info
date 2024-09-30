#include "conrecord.h"

conRecord::conRecord()
{
    recordNumber = 0;
    firstName = "";
    middleName = "";
    lastName = "";
    driverLicense = "";
    commandNumber = "";
    departureTime = "";
    kindOfMil = "";
    spec = "";
    armyUnit = "";
}

void conRecord::printConRecord()
{
    qDebug() << "recordNumber = " << recordNumber << " firstName = " << firstName << " middleName = " << middleName <<
                "lastName = " << lastName << " driverLicense = " << driverLicense << " commandNumber = " << commandNumber <<
                " departureTime = " << departureTime << " kindOfMil = " << kindOfMil << " spec = " << spec << " armyUnit = " << armyUnit;
}

int conRecord::getrecordNumber() {return recordNumber;}
void conRecord::setRecordNumber(int newRecordNumber) {recordNumber = newRecordNumber;}
QString conRecord::getFirstName() {return firstName;};
void conRecord::setFirstName(QString newFirstName) {firstName = newFirstName;}
QString conRecord::getMiddleName() {return middleName;}
void conRecord::setMiddleName(QString newMiddleName) {middleName = newMiddleName;}
QString conRecord::getLastName() {return lastName;};
void conRecord::setLastName(QString newLastName) {lastName = newLastName;}
QString conRecord::getDriverLicense() {return driverLicense;}
void conRecord::setDriverLicense(QString newDriverLicense) {driverLicense = newDriverLicense;}
QString conRecord::getCommandNumber() {return commandNumber;}
void conRecord::setCommandNumber(QString newCommandNumber) {commandNumber = newCommandNumber;}
QString conRecord::getDepartureTime() {return departureTime;}
void conRecord::setDepartureTime(QString newDepartureTime) {departureTime = newDepartureTime;}
QString conRecord::getKindOfMil() {return kindOfMil;}
void conRecord::setKindOfMil(QString newKindOfMil) {kindOfMil = newKindOfMil;}
QString conRecord::getSpec() {return spec;}
void conRecord::setSpec(QString newSpec) {spec = newSpec;}
QString conRecord::getArmyUnit() {return armyUnit;}
void conRecord::setArmyUnit(QString newArmyUnit) {armyUnit = newArmyUnit;}

conRecord::~conRecord(){}
