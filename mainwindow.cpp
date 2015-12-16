#include "MainWindow.h"

MainWindow::MainWindow()
{
	//set black background color:
	this->setStyleSheet("background-color:black;");
}

MainWindow::~MainWindow()
{

}

void MainWindow::setChilds(ModelViewer *modelViewerReceived, QWidget *sideMenuReceived)
{
	modelViewer = modelViewerReceived;
	sideMenu = sideMenuReceived;
}

void MainWindow::resizeEvent( QResizeEvent * event )
{
	if(modelViewer && sideMenu)
	{
		modelViewer->setGeometry((QRect(0,0,this->width()-1,this->height()-1)));
		sideMenu->setGeometry(QRect((this->width()-50),0,50,sideMenu->height()));
		this->update();
	}
}

void MainWindow::mouseReleaseEvent( QMouseEvent *event )
{
	//get String of Lable
	QString text = ((QLabel*)childAt(event->pos()))->text();
	//convert it to Number
	int modelNumber = text.toInt()-1;
	emit modelChange(modelNumber);
}

//keyboard events
void MainWindow::keyPressEvent(QKeyEvent* event)
{
	emit keyPressed(event);
}