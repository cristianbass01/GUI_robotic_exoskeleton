#include <QApplication>
#include <qicon.h>
#include "main_form.h"
#include "global_variable.h"
#include "log.h"
#include "connected_component.h"
#include "frame_window.h"

#include <QDir>

// inizializzazione variabili globale
const QString path = QDir::homePath() + "/Alice/Log/";
UserList userList;
User *currentUser;

int main(int argc, char *argv[])
{

  ConnectedComponent::getInstance().initialize(argc, argv);

  //ros::init(argc, argv, "start_gui_node");
  QApplication a(argc, argv);

  //QString a2 = ;

  std::shared_ptr<FrameWindow> frame;
  frame.reset(new FrameWindow());
  frame->customizeWindow(new MainForm(frame.get()));

  // set the window title as the node name
  //w.setWindowTitle(QString::fromStdString(ros::this_node::getName()));

  // load the icon from our qrc file and set it as the application icon
  QIcon icon(":/icons/Icons/exoskeleton_icon.png");
  frame->setWindowIcon(icon);
  frame->showMaximized();
  userList.loadXml(path + "users.xml");
  currentUser = nullptr;
  frame->show();

  return a.exec();
}
