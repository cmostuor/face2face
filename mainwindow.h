#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include "ModelViewer5.h"
#include "ModelManager.h"
#include "qrect.h"
#include "qlabel.h"

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();
	void setChilds(ModelViewer *modelViewer, QWidget *sideMenu);

signals:
	//SideMenu signal
	void modelChange(int modelNumber);
	//keyboard events
	void keyPressed(QKeyEvent* event);

private:
	ModelViewer *modelViewer;
	ModelManager *modelManager;
	QWidget *sideMenu;

protected:
	void resizeEvent ( QResizeEvent *event );
	void mouseReleaseEvent( QMouseEvent *event );
	void keyPressEvent(QKeyEvent* event);
	
};

#endif // MAINWINDOW_H
