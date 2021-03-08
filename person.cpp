#include "person.h"
Person::Person(const QPoint &point,bool hasAMask)
    :position(point),hasMask(hasAMask){}

QColor Person::getTargetColor()
{
    if(this->isHealthy){
        return this->hasMask? QColor(0,205,0):QColor(192,255,62);
    }else{
        return this->hasMask?QColor(255,165,0):QColor(238,64,0);
    }
}

int Person::getDistance()
{
    if(this->isHealthy)return 0;
    return this->hasMask ? 20:50;
}

int Person::illPosibility()
{
    if(!this->isHealthy)return 0;
    return this->hasMask ? 5:2;
}

void Person::move()
{
    auto halfSpeed = this->moveSpeed/2;
    auto newX = rand()%moveSpeed-halfSpeed + position.x();
    auto newY = rand()%moveSpeed-halfSpeed + position.y();
    if(newX <= 0)newX = 0;
    if(newY <= 0)newY = 0;
    if(newX >= 750) newX = 750;
    if(newY >= 750) newY = 750;
    this->position.setX(newX);
    this->position.setY(newY);
}
