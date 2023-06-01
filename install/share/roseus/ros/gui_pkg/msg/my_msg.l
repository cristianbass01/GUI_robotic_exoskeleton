;; Auto-generated. Do not edit!


(when (boundp 'gui_pkg::my_msg)
  (if (not (find-package "GUI_PKG"))
    (make-package "GUI_PKG"))
  (shadow 'my_msg (find-package "GUI_PKG")))
(unless (find-package "GUI_PKG::MY_MSG")
  (make-package "GUI_PKG::MY_MSG"))

(in-package "ROS")
;;//! \htmlinclude my_msg.msg.html


(defclass gui_pkg::my_msg
  :super ros::object
  :slots (_n1 ))

(defmethod gui_pkg::my_msg
  (:init
   (&key
    ((:n1 __n1) 0)
    )
   (send-super :init)
   (setq _n1 (round __n1))
   self)
  (:n1
   (&optional __n1)
   (if __n1 (setq _n1 __n1)) _n1)
  (:serialization-length
   ()
   (+
    ;; int32 _n1
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _n1
       (write-long _n1 s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _n1
     (setq _n1 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get gui_pkg::my_msg :md5sum-) "9af3d60cfc2ff33bd276c7f8d4a1f7d6")
(setf (get gui_pkg::my_msg :datatype-) "gui_pkg/my_msg")
(setf (get gui_pkg::my_msg :definition-)
      "int32 n1

")



(provide :gui_pkg/my_msg "9af3d60cfc2ff33bd276c7f8d4a1f7d6")


