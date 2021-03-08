#ifndef SCHOOLMAPWIDGET_H
#define SCHOOLMAPWIDGET_H

#include <QWidget>
#include <set>
#include <person.h>
#include <QPoint>
#include <QMap>
#include <QRect>
#include <vector>
struct QRectComp{
    bool operator()(const QRect& a,const QRect&b)const{
        if(a.x() != b.x())
            return a.x() < b.x();
        if(a.y() != b.y())
            return a.y()< b.y();
        return a.x() * a.y() < b.x() * b.y();
    }
};

class MapData{
private:
    std::map<QRect,int,QRectComp> areas;
    QPoint size;
    QPoint getNewRandowPosition(const QPoint&point,int moveSpeed);
public:
    int getRectIndex(const QPoint & point);
    std::map<QRect,int,QRectComp>& getAreas(){return this->areas;}
    void addArea(const QRect &qRect);
    void setSize(const QPoint& s){this->size = s;}
    QPoint getNextPosition(const QPoint & point ,int moveSpeed,int depen =0);

};

class SchoolMapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SchoolMapWidget(QWidget *parent = nullptr);
    void addPersion(const QPoint &point);
    void setSimStatus(bool able){this->hasStart = able;}
protected:
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *e);
private:
    void initMap();
    void updateData();
    QTimer *renderTimer;
    std::set<Person*> personSet;
    void tryInfect();
    MapData mapData;
    bool hasStart = false;
    bool isIll = false;
    bool hasMask = false;
    int moveSpeed = 19;
    int areaDepenValue = 4;
    int comDistance  = 0;
    std::vector<std::pair<int,int>> statVal;
public:
    bool personNearBy(const QPoint&p, Person *person);
    void seMoveSpeed(int speed){this->moveSpeed = speed;}
    void setAreaDepenValue(int val){this->areaDepenValue = val;}
    void setCommDistance(int val){this->comDistance = val;}
    std::vector<std::pair<int,int>> getStatVal(){return this->statVal;}
signals:
public slots:
    void tick();
    void setIsIll(bool ill){this->isIll = ill;}
    void setHasMask(bool hasMask){this->hasMask = hasMask;}
};

#endif // SCHOOLMAPWIDGET_H
