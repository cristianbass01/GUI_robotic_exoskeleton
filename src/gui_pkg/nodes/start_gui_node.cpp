#include <QApplication>
#include <qicon.h>
#include "main_form.h"
#include "global_variable.h"
#include "log.h"

#include <QDir>

const QString path = QDir::homePath() + "/Alice/Log/";
UserList userList;

void logTest()
{
  Log log(userList.getAt(0)->getDir());
  log.addWalkingEx(8,8,0, QTime(0,0,0,0));
}


int main(int argc, char *argv[])
{

  ros::init(argc, argv, "start_gui_node");
  QApplication a(argc, argv);

  //QString a2 = ;

  MainForm w;
  // set the window title as the node name
  w.setWindowTitle(QString::fromStdString(ros::this_node::getName()));

  // load the icon from our qrc file and set it as the application icon
  QIcon icon(":/icons/exoskeleton_icon.png");
  w.setWindowIcon(icon);
  userList.loadXml(path + "users.xml");
  w.show();


  //logTest(); // ------------------------------------


  return a.exec();
}
