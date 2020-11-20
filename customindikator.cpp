#include "customindikator.h"

CustomIndikator::CustomIndikator(QWidget *parent) : QWidget(parent)
{
    //Установка дефолтной размерности
    setGeometry(0,0,200,200);

    //Установка дефолтных значений
    setDefaultValues(false,true);

    //Запись центра компонента
    setCenterX(width()/2);
    setCenterY(height()/2);

}

void CustomIndikator::setDefaultValues(bool _Active, bool _CanActive, bool _TypeObject, QColor _OnColor, QColor _OffColor)
{
    //Запоминание типа объекта
    setType(static_cast<TYPE_OBJECT>(_TypeObject));
    //Если было принудительного изменения цвета покраски
    if(_OnColor != Qt::transparent  || _OffColor != Qt::transparent)
        setCustomStyle(_OnColor,_OffColor);

    //Установка стиля отрисовки
    setStyle(TYPE_STYLE::Dracula);

    //Устанавливаем текущую активность и возможность активности
    setActive(_Active);
    setCanActive(_CanActive);

    CustomIndikator::repaint();
}

void CustomIndikator::setStyle(const CustomIndikator::TYPE_STYLE &style){

    //Если тип объекта квадрат
    if(getType() == TYPE_OBJECT::Rect)
    {
        //Выбран светлый стиль отрисовки
        if(style == TYPE_STYLE::SnowWhite)
        {
            m_colors.BrushOff              = Styles::Light::LightGray;
            m_colors.BorderOff             = Styles::Light::Gray;
            m_colors.BrushOn               = Styles::Light::Orange;
            m_colors.BorderOn             = Styles::Light::Gray;
            m_colors.BackGroundColor = Styles::Light::White;
        }
        //Выбран тёмный стиль отрисовки
        else if (style ==TYPE_STYLE:: Dracula)
        {
            m_colors.BrushOff               = Styles::Dracula::DarkGray;
            m_colors.BorderOff             = Styles::Dracula::Black;
            m_colors.BrushOn               = Styles::Dracula::Green;
            m_colors.BorderOn             = Styles::Dracula::GrayWhite;
            m_colors.BackGroundColor = Styles::Dracula::Asphalt;
        }
       setStyleSheet("* {background-color: " + QString(m_colors.BackGroundColor.name()) + "}");
    }
    //Если тип объекта круг
    else
    {
        //Выбран светлый стиль отрисовки
        if(style ==  TYPE_STYLE::SnowWhite)
        {
            m_colors.BrushOff = Styles::Light::LightGray;
            m_colors.BorderOff = Styles::Light::Gray;
            m_colors.BrushOn =Styles:: Light::Cyan;
            m_colors.BorderOn = Styles::Light::Gray;
            m_colors.BackGroundColor =Styles::Light::White;
        }
        //Выбран тёмный стиль отрисовки
        else if (style ==  TYPE_STYLE::Dracula)
        {
            m_colors.BrushOff              = Styles::Dracula::DarkGray;
            m_colors.BorderOff            = Styles::Dracula::Black;
            m_colors.BrushOn                 = Styles::Dracula::LightCyan;
            m_colors.BorderOn             = Styles::Dracula::GrayWhite;
            m_colors.BackGroundColor =Styles::Dracula::Asphalt;
        }
       setStyleSheet("* {background-color: " + QString(m_colors.BackGroundColor.name()) + "}");
    }
}

void CustomIndikator::setCustomStyle(QColor _OnColor, QColor _OffColor)
{
    //Если цвет включение не был принудительно изменен
    if(_OnColor != Qt::transparent)
      m_colors.BrushOn = _OnColor;
    //Если цвет выключения не был принудительно изменен
    if(_OffColor != Qt::transparent)
      m_colors.BrushOff = _OffColor;
}

void CustomIndikator::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        //Если уже присутствует активность сбрасываем флаг в false
        if(getCanActive())
        {
            if(getActive())  setActive(false);
            //Иначе устанавливаем в true
            else setActive(true);
        }
        CustomIndikator::repaint();
    }
}

void CustomIndikator::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter paint(this);
    m_painter = &paint;

    // Сглаживание рисунка
    m_painter->setRenderHint(QPainter::Antialiasing, true);

    //Если позиция активна
    if(getActive())
    {
        m_painter->setPen(m_colors.BorderOn);
        m_painter->setBrush(m_colors.BrushOn);
    }
    else
    {
        m_painter->setPen(m_colors.BorderOff);
        m_painter->setBrush(m_colors.BrushOff);
    }

    //Отрисовка объекта
   if(getType() == TYPE_OBJECT::Circle)
      m_painter->drawEllipse(getCenter(),getRadius(),getRadius());
    else
    {
      m_painter->drawRect(getCenter().x()-getRadius(), getCenter().y()-getRadius(), getRadius()*2,getRadius()*2);
    }
}

void CustomIndikator::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    //Запись центра компонента
    m_Center.setX(width()/2);
    m_Center.setY(height()/2);
    //Минимальный радиус от ширины и высоты компонента
    setRadius(std::min(this->width()/2, this->height()/2));
    //Установка минимальной размерности компонента
    setMinimumSize(13,13);

    CustomIndikator::repaint();
}
