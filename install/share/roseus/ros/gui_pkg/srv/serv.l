;; Auto-generated. Do not edit!


(when (boundp 'gui_pkg::serv)
  (if (not (find-package "GUI_PKG"))
    (make-package "GUI_PKG"))
  (shadow 'serv (find-package "GUI_PKG")))
(unless (find-package "GUI_PKG::SERV")
  (make-package "GUI_PKG::SERV"))
(unless (find-package "GUI_PKG::SERVREQUEST")
  (make-package "GUI_PKG::SERVREQUEST"))
(unless (find-package "GUI_PKG::SERVRESPONSE")
  (make-package "GUI_PKG::SERVRESPONSE"))

(in-package "ROS")





(defclass gui_pkg::servRequest
  :super ros::object
  :slots (_code ))

(defmethod gui_pkg::servRequest
  (:init
   (&key
    ((:code __code) "")
    )
   (send-super :init)
   (setq _code (string __code))
   self)
  (:code
   (&optional __code)
   (if __code (setq _code __code)) _code)
  (:serialization-length
   ()
   (+
    ;; string _code
    4 (length _code)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _code
       (write-long (length _code) s) (princ _code s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _code
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _code (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass gui_pkg::servResponse
  :super ros::object
  :slots (_error ))

(defmethod gui_pkg::servResponse
  (:init
   (&key
    ((:error __error) "")
    )
   (send-super :init)
   (setq _error (string __error))
   self)
  (:error
   (&optional __error)
   (if __error (setq _error __error)) _error)
  (:serialization-length
   ()
   (+
    ;; string _error
    4 (length _error)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _error
       (write-long (length _error) s) (princ _error s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _error
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _error (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass gui_pkg::serv
  :super ros::object
  :slots ())

(setf (get gui_pkg::serv :md5sum-) "62d2895a600383a28702b76d8606b327")
(setf (get gui_pkg::serv :datatype-) "gui_pkg/serv")
(setf (get gui_pkg::serv :request) gui_pkg::servRequest)
(setf (get gui_pkg::serv :response) gui_pkg::servResponse)

(defmethod gui_pkg::servRequest
  (:response () (instance gui_pkg::servResponse :init)))

(setf (get gui_pkg::servRequest :md5sum-) "62d2895a600383a28702b76d8606b327")
(setf (get gui_pkg::servRequest :datatype-) "gui_pkg/servRequest")
(setf (get gui_pkg::servRequest :definition-)
      "string code
---
string error

")

(setf (get gui_pkg::servResponse :md5sum-) "62d2895a600383a28702b76d8606b327")
(setf (get gui_pkg::servResponse :datatype-) "gui_pkg/servResponse")
(setf (get gui_pkg::servResponse :definition-)
      "string code
---
string error

")



(provide :gui_pkg/serv "62d2895a600383a28702b76d8606b327")


