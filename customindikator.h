#ifndef CUSTOMINDIKATOR_H
#define CUSTOMINDIKATOR_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "stylescolors.h"

//Компонент статус индикатор, оповещающий пользователя о положении в true или false
class CustomIndikator : public QWidget
{
    Q_OBJECT
public:
    //Конструктор
    explicit CustomIndikator(QWidget *parent = nullptr);

    Q_PROPERTY(bool CanActive READ getCanActive WRITE setCanActive NOTIFY CanActiveChanged)   //Возможность включения активности нажатием
    Q_PROPERTY(bool Active READ getActive WRITE setActive NOTIFY ActiveChanged)                         //Текущее состояние

    //Getters
    bool getCanActive() const
    {
        return m_CanActive;
    }
    bool getActive() const
    {
        return m_Active;
    }

    //---------------------------------ENUMS------------------------------------
     //Перечисление с типом созданного объекта
     enum TYPE_OBJECT {Circle,Rect};   //0 - Окружность
                                       //1 - Квадрат
     //Перечисление типов стилей
     enum TYPE_STYLE
     {
       Dracula = 1,
       SnowWhite   = 2
     };
    //------------------------------------------------------------------------------

    //------------------------------PUBLIC_FUNCTIONS--------------------------
    //Функция устанавливающая дефолтные параметры у компонента
    void setDefaultValues(bool _Active, bool _CanActive, bool _TypeObject = false, QColor _OnColor = Qt::transparent, QColor _OffColor = Qt::transparent);
    //Функция выбора дефолтного стиля отрисовки
    void setStyle(const TYPE_STYLE &style);
    //-------------------------------------------------------------------------------

signals:

  //Signals
  void ActiveChange (bool Active);
  void CanActiveChanged(bool CanActive);
  void ActiveChanged(bool Active);

public slots:

  //Setters
  void setCanActive(bool CanActive)
{
    if (m_CanActive == CanActive)
        return;

    m_CanActive = CanActive;
    emit CanActiveChanged(m_CanActive);
}
  void setActive(bool Active)
{
    if (m_Active == Active)
        return;

    m_Active = Active;
    emit ActiveChanged(m_Active);
}

private:

  //---------------------------STRUCTS----------------------------
  //Структура отвечающая за цветовую палитру
    typedef struct{

      QColor BorderOn;                 //Цвет оконтовки когда ON
      QColor BorderOff;                //Цвет оконтовки когда OFF
      QColor BrushOn;                  //Цвет заливки когда ON
      QColor BrushOff;                 //Цвет заливки когда OFF
      QColor BackGroundColor;   //Цвет задника
  }Colors;
   //------------------------------------------------------------------

    //-------------------PRIVATE_FUNCTIONS--------------------
    //Функция кастомного стиля отрисовки
    void setCustomStyle(QColor _OnColor, QColor _OffColor);
    //----------------------------------------------------------------

    //Инструмент для отрисовки
    QPainter *m_painter;
    //Цветовая гамма объекта
    Colors m_colors;
    //Возможность активности нажатием
    bool    m_CanActive;
    //Текущее состояние
    bool    m_Active;

    //Тип объекта
    TYPE_OBJECT m_Type;
    TYPE_OBJECT getType(){return m_Type;}
    void        setType(TYPE_OBJECT _Value){m_Type = _Value;}

    //Радиус окружности
    qreal m_Radius;
    qreal getRadius(){return m_Radius;}
    void  setRadius(qreal _Value){m_Radius = _Value;}

    //Центр компонента
    QPointF m_Center;
    QPointF getCenter(){return m_Center;}
    qreal     getCenterX(){return m_Center.x();}
    qreal     getCenterY(){return m_Center.y();}
    void      setCenter(QPointF _Point){m_Center = _Point;}
    void      setCenterX(qreal _Value){m_Center.setX(_Value);}
    void      setCenterY(qreal _Value){m_Center.setY(_Value);}

    //Тип объекта
    bool  m_TypeObject;
    bool  getTypeObject(){return m_TypeObject;}
    void  setTypeObject(bool _Value){m_TypeObject = _Value;}

protected:

    //Events
    void mousePressEvent (QMouseEvent *event)    override; //Срабатывание на нажатие мыши на компоненте
    void paintEvent            (QPaintEvent   *event)     override; //Срабатывание на отрисовку формы
    void resizeEvent          (QResizeEvent *event)     override; //Срабатывание на изменения размера формы компонента
};

#endif // CUSTOMINDIKATOR_H
