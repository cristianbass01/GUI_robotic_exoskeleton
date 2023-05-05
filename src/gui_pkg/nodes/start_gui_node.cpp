#include <QApplication>
#include "selection_form.h"

int main(int argc, char *argv[])
{

  ros::init(argc, argv, "start_gui_node");
  QApplication a(argc, argv);

  SelectionForm w;
  w.show();

  // set the window title as the node name
  //w.setWindowTitle(QString::fromStdString(ros::this_node::getName()));

  // load the icon from our qrc file and set it as the application icon
//    QIcon icon(":/icons/my_gui_icon.png");
//    w.setWindowIcon(icon);


  return a.exec();
}
