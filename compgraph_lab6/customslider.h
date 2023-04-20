#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <QSlider>
class Customslider : public QSlider
{
public:
    explicit Customslider(QWidget* parent = 0);
    void keyPressEvent(QKeyEvent * ev) override;
};

#endif // CUSTOMSLIDER_H
