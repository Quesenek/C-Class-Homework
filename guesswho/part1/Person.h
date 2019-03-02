/* 
 * This is .h file for the Person class
 * This class is used to get and set attributes about the people in the game guess who to form a person object.
 * 
 * Date:   November 11, 2018 
 */ 

#pragma once

#include <string>

using namespace std;

class Person
{
    private:
        string name;
        string hairColor;
        string hairType;
        string gender;
        bool glasses;
        string eyeColor;
        bool hat;

    public:
        Person();
        ~Person();

        string getName() const;
        void setName(string nam);
        string getHairColor() const;
        void setHairColor(string hc);
        string getHairType() const;
        void setHairType(string ht);
        string getGender() const;
        void setGender(string gen);
        bool getGlasses() const;
        void setGlasses(string gla);
        string getEyeColor() const;
        void setEyeColor(string ec);
        bool getHat() const;
        void setHat(string headware);
};
