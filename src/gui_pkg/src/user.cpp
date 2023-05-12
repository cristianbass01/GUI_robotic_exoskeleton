#include <user.h>

User::User() :
    dir_{""}, id_{""}, name_{""}, surname_{""}, birthday_{QDate(2000, 1, 1)}, sex_{""}, height_{0}, weight_{0}, femur_{0}, tibia_{0}
{}

User::User(QString dir, QString id, QString name, QString surname, QDate birthday, QString sex, int height, double weight, int femur, int tibia) :
    dir_{dir}, id_{id}, name_{name}, surname_{surname}, birthday_{birthday}, sex_{sex}, height_{height}, weight_{weight}, femur_{femur}, tibia_{tibia}
{}

//Getter
QString User::getId() const { return id_; }
QString User::getDir() const { return dir_; }
QString User::getName() const { return name_; }
QString User::getSurname() const { return surname_; }
QDate User::getBirthday() const { return birthday_; }
QString User::getSex() const { return sex_; }
int User::getHeight() const { return height_; }
double User::getWeight() const { return weight_; }
int User::getFemur() const { return femur_; }
int User::getTibia() const { return tibia_; }

//Setter
void User::setId(QString id) { id_ = id; }
void User::setDir(QString dir) { dir_ = dir; }
void User::setName(QString name) { name_ = name; }
void User::setSurname(QString surname) { surname_ = surname; }
void User::setBirthday(QDate birthday) { birthday_ = birthday; }
void User::setSex(QString sex) { sex_ = sex; }
void User::setHeight(int height) { height_ = height; }
double User::setWeight(double weight) { weight_ = weight; }
void User::setFemur(int femur) { femur_ = femur; }
void User::setTibia(int tibia) { tibia_ = tibia; }

