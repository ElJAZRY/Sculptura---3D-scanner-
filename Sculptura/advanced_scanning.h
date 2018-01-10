#ifndef ADVANCED_SCANNING_H
#define ADVANCED_SCANNING_H

#include <QDialog>

namespace Ui {
class Advanced_scanning;
}

class Advanced_scanning : public QDialog
{
    Q_OBJECT

public:
    explicit Advanced_scanning(QWidget *parent = 0);
    ~Advanced_scanning();

private slots:
    void on_apply_pb_clicked();

private:
    Ui::Advanced_scanning *ui;
};

#endif // ADVANCED_SCANNING_H
