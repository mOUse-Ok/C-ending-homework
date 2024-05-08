#ifndef MW_H
#define MW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MW;
}
QT_END_NAMESPACE

class MW : public QMainWindow
{
    Q_OBJECT

public:
    MW(QWidget *parent = nullptr);
    ~MW();

private:
    Ui::MW *ui;
};
#endif // MW_H
