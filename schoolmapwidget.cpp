#include "schoolmapwidget.h"
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
SchoolMapWidget::SchoolMapWidget(QWidget *parent) : QWidget(parent)
{
    this->renderTimer = new QTimer(this);
    connect(renderTimer, SIGNAL(timeout()), this, SLOT(tick()));
    renderTimer->start(40);
    this->initMap();
}

void SchoolMapWidget::addPersion(const QPoint &point)
{
   auto *person = new Person(point,this->hasMask);
   if(this->isIll)
   person->setIll();
   person->moveSpeed = moveSpeed;
   this->personSet.insert(person);
}


void SchoolMapWidget::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRect(rect());
      QPen pen1(QColor(0,191,255));
      pen1.setWidth(5);
      painter.setPen(pen1);
   auto areas = this->mapData.getAreas();
   for(auto &a:areas){
        painter.drawRect(a.first);
   }
  for(auto person:this->personSet){
     auto color = person->getTargetColor();
       QPen pen(color); //画笔
       QBrush brush(color); //画刷
       painter.setPen(pen);
       painter.setBrush(brush);
       auto dis = person->getDistance();
       painter.drawEllipse(person->position,8,8);
       painter.setBrush(Qt::NoBrush);
       painter.drawEllipse(person->position,dis,dis);
  }
}

void SchoolMapWidget::mouseReleaseEvent(QMouseEvent *e)
{
    this->addPersion(e->pos());
    this->update();
}

void SchoolMapWidget::initMap()
{
    this->mapData.setSize({750,750});
    this->mapData.addArea({200,0,400,150});
    this->mapData.addArea({50,250,250,100});
    this->mapData.addArea({100,500,100,100});
    this->mapData.addArea({500,300,200,200});
    srand(time(nullptr));
    QPalette pal(this->palette());
    pal.setBrush(QPalette::Window,
                QBrush(QPixmap(":/img/bg.png")));
    setAutoFillBackground(true);
    setPalette(pal);
 }

void SchoolMapWidget::updateData()
{
    int heathyPerson = 0;
    int illPersion = 0;
    for(auto i:this->personSet){
        if(i->isHealthy){
            heathyPerson++;
        }else {
            illPersion++;
        }
        auto newPosition = this->mapData.getNextPosition(i->position,this->moveSpeed,this->areaDepenValue);
        if(!personNearBy(newPosition,i)){
            i->setPosition(newPosition);
        }
    }
    this->statVal.emplace_back(heathyPerson,illPersion);
}

void SchoolMapWidget::tryInfect()
{
    for(auto patient :this->personSet){
        if(!patient->isHealthy){
            for(auto target:this->personSet){
                if(target->isHealthy){
                    auto p1 = target->position;
                    auto p2 = patient->position;
                    auto dis2 = (p1.x() - p2.x())*(p1.x() - p2.x())
                            +(p1.y() - p2.y())*(p1.y() - p2.y());
                    auto infectDistance = patient->getDistance();
                    auto rectID1 = this->mapData.getRectIndex(patient->position);
                    auto rectID2 = this->mapData.getRectIndex(target->position);
                    if(rectID1==rectID2 && dis2 <= infectDistance * infectDistance && rand()% target->illPosibility() == 0
                            ){
                        target->setIll();
                    }
                }
            }
        }

    }
}

bool SchoolMapWidget::personNearBy(const QPoint&p1,Person *person)
{
    auto minDis2 = this->comDistance * this->comDistance;
    for(auto p:this->personSet){
        auto p2 = p->position;
        if(p !=person){
            auto dis2 = (p1.x() - p2.x())*(p1.x() - p2.x())
                    +(p1.y() - p2.y())*(p1.y() - p2.y());
            if(dis2 <= minDis2){
                return true;
            }
        }
    }
    return false;
}
void SchoolMapWidget::tick()
{   if(!this->hasStart) return;
    this->updateData();
    this->tryInfect();
    this->update();
}

int MapData::getRectIndex(const QPoint &point){
    for(auto &rect:areas){
        if(rect.first.contains(point)) return rect.second;
    }
    return -1;
}

void MapData::addArea(const QRect &area)
{
    int index = this->areas.size();
    this->areas[area] = index;
}

QPoint MapData::getNewRandowPosition(const QPoint &position, int moveSpeed)
{
    auto halfSpeed = moveSpeed/2;
    auto newX = rand()%moveSpeed-halfSpeed + position.x();
    auto newY = rand()%moveSpeed-halfSpeed + position.y();
    if(newX <= 0)newX = 0;
    if(newY <= 0)newY = 0;
    if(newX >=this->size.x()) newX = this->size.x();
    if(newY >= this->size.y()) newY =this->size.y();
    return {newX,newY};
}

QPoint MapData::getNextPosition(const QPoint &position, int moveSpeed,int depen){
    auto rectID = getRectIndex(position); //获取当前的区域
    auto newPosition = getNewRandowPosition(position,moveSpeed); //随机生成一个新的位置
    auto newRectID = getRectIndex(newPosition); //获取新的位置的新区域
    if(newRectID == rectID) return newPosition; //如果前后区域一样就直接返回
    for(int i = 0;i <depen;i++){
        //尝试 depen次后都是新区域就进到新区域，否则不动
        if(getRectIndex(getNewRandowPosition(position,moveSpeed)) != newRectID){
            return position;
        }
    }
    return newPosition;
}
