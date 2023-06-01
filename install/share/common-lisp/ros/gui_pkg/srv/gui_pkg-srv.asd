
(cl:in-package :asdf)

(defsystem "gui_pkg-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "serv" :depends-on ("_package_serv"))
    (:file "_package_serv" :depends-on ("_package"))
  ))