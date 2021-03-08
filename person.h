#ifndef PERSON_H
#define PERSON_H
#include <QPoint>
#include <map>
#include <QColor>
class Person
{
public:
    bool isHealthy = true;
    bool hasMask = false;
    QPoint position = {0,0};
    Person() = delete;
    int moveSpeed = 39;
    void move();
    explicit Person(const QPoint &point,bool hasAMask);
    void setIll(){this->isHealthy = false;}
    void setHelath(){this->isHealthy = true;}
    QColor getTargetColor();
    int getDistance();
    int illPosibility();
    void setHasAMask(bool has){this->hasMask = has;};
    void setPosition(const QPoint& pos){this->position = pos;}
};

#endif // PERSON_H
