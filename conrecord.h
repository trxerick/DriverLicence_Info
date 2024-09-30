#ifndef CONRECORD_H
#define CONRECORD_H

#include <QString>
#include <QDebug>

class conRecord
{
    public:
        conRecord();
        ~conRecord();
        int getrecordNumber();
        void setRecordNumber(int newRecordNumber);
        QString getFirstName();
        void setFirstName(QString newFirstName);
        QString getMiddleName();
        void setMiddleName(QString newMiddleName);
        QString getLastName();
        void setLastName(QString newLastName);
        QString getDriverLicense();
        void setDriverLicense(QString newDriverLicense);
        QString getCommandNumber();
        void setCommandNumber(QString newCommandNumber);
        QString getDepartureTime();
        void setDepartureTime(QString newDepartureTime);
        QString getKindOfMil();
        void setKindOfMil(QString newKindOfMil);
        QString getSpec();
        void setSpec(QString newSpec);
        void printConRecord();
        QString getArmyUnit();
        void setArmyUnit(QString newArmyUnit);

    private:
        int recordNumber;
        QString firstName;
        QString middleName;
        QString lastName;
        QString driverLicense;
        QString commandNumber;
        QString departureTime;
        QString kindOfMil;
        QString spec;
        QString armyUnit;
};

#endif // CONRECORD_H
