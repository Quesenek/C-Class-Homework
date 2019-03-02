/* 
 * This is .cpp file for the Person class
 * This class is used to get and set attributes about the people in the game guess who to form a person object.
 * 
 * Date:   November 11, 2018 
 */ 

#include "Person.h"

/*
 * The Person constructor is used to initialize the Person object and its member variables.
 * 
 * Return:  Nothing
 */
Person::Person()
{
    name = "";
    hairColor = "";
    hairType = "";
    gender = "";
    glasses = false;
    eyeColor = "";
    hat = false;
}

/*
 * The Person deconstructor is not used.
 * 
 * Return:  Nothing
 */
Person::~Person()
{
}

/*
 * The getName function is a const function that returns the name member variable of the Person object.
 * 
 * Return:  name
 */
string Person::getName() const
{
    return name;
}

/*
 * The setName function sets the name member variable of the Person object to what is contained in nam.
 * 
 * Parameter:    nam     a string that contains the new value for the name member variable
 * 
 * Return:  void
 */
void Person::setName(string nam)
{
    name = nam;
}

/*
 * The getHairColor function is a const function that returns the hairColor member variable of the Person object.
 * 
 * Return:  hairColor
 */
string Person::getHairColor() const
{
    return hairColor;
}

/*
 * The setHairColor function sets the hairColor member variable of the Person object to what is contained in hc.
 * 
 * Parameter:    hc     a string that contains the new value for the hairColor member variable
 * 
 * Return:  void
 */
void Person::setHairColor(string hc)
{
    hairColor = hc;
}

/*
 * The getHairType function is a const function that returns the hairType member variable of the Person object.
 * 
 * Return:  hairType
 */
string Person::getHairType() const
{
    return hairType;
}

/*
 * The setHairType function sets the hairType member variable of the Person object to what is contained in ht.
 * 
 * Parameter:    ht     a string that contains the new value for the hairType member variable
 * 
 * Return:  void
 */
void Person::setHairType(string ht)
{
    hairType = ht;
}

/*
 * The getGender function is a const function that returns the gender member variable of the Person object.
 * 
 * Return:  gender
 */
string Person::getGender() const
{
    return gender;
}

/*
 * The setGender function sets the name member variable of the Person object to what is contained in gen.
 * 
 * Parameter:    gen     a string that contains the new value for the gender member variable
 * 
 * Return:  void
 */
void Person::setGender(string gen)
{
    gender = gen;
}

/*
 * The getGlasses function is a const function that returns the glasses member variable of the Person object.
 * 
 * Return:  glasses
 */
bool Person::getGlasses() const
{
    return glasses;
}

/*
 * The setGlasses function sets the glasses member variable of the Person object to what is contained in gla.
 * 
 * Parameter:    gla     a string that contains the new value for the glasses member variable
 * 
 * Return:  void
 */
void Person::setGlasses(string gla)
{
    glasses = (gla == "yes");
}

/*
 * The getEyeColor function is a const function that returns the eyeColor member variable of the Person object.
 * 
 * Return:  eyeColor
 */
string Person::getEyeColor() const
{
    return eyeColor;
}

/*
 * The setEyeColor function sets the eyeColor member variable of the Person object to what is contained in ec.
 * 
 * Parameter:    ec     a string that contains the new value for the eyeColor member variable
 * 
 * Return:  void
 */
void Person::setEyeColor(string ec)
{
    eyeColor = ec;
}

/*
 * The getHat function is a const function that returns the hat member variable of the Person object.
 * 
 * Return:  hat
 */
bool Person::getHat() const
{
    return hat;
}

/*
 * The setHat function sets the hat member variable of the Person object to what is contained in headware.
 * 
 * Parameter:    headware     a string that contains the new value for the hat member variable
 * 
 * Return:  void
 */
void Person::setHat(string headware)
{
    hat = (headware == "yes");
}