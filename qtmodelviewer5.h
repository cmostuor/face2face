#ifndef QTMODELVIEWER5_H
#define QTMODELVIEWER5_H

#include <QtWidgets/QMainWindow>
#include "ui_qtmodelviewer5.h"

class QtModelViewer5 : public QMainWindow
{
	Q_OBJECT

public:
	QtModelViewer5(QWidget *parent = 0);
	~QtModelViewer5();

private:
	Ui::QtModelViewer5Class ui;
};

#endif // QTMODELVIEWER5_H
