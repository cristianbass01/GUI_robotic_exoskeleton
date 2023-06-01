;; Auto-generated. Do not edit!


(when (boundp 'fake_exo::serv)
  (if (not (find-package "FAKE_EXO"))
    (make-package "FAKE_EXO"))
  (shadow 'serv (find-package "FAKE_EXO")))
(unless (find-package "FAKE_EXO::SERV")
  (make-package "FAKE_EXO::SERV"))
(unless (find-package "FAKE_EXO::SERVREQUEST")
  (make-package "FAKE_EXO::SERVREQUEST"))
(unless (find-package "FAKE_EXO::SERVRESPONSE")
  (make-package "FAKE_EXO::SERVRESPONSE"))

(in-package "ROS")





(defclass fake_exo::servRequest
  :super ros::object
  :slots (_code ))

(defmethod fake_exo::servRequest
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

(defclass fake_exo::servResponse
  :super ros::object
  :slots (_error ))

(defmethod fake_exo::servResponse
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

(defclass fake_exo::serv
  :super ros::object
  :slots ())

(setf (get fake_exo::serv :md5sum-) "62d2895a600383a28702b76d8606b327")
(setf (get fake_exo::serv :datatype-) "fake_exo/serv")
(setf (get fake_exo::serv :request) fake_exo::servRequest)
(setf (get fake_exo::serv :response) fake_exo::servResponse)

(defmethod fake_exo::servRequest
  (:response () (instance fake_exo::servResponse :init)))

(setf (get fake_exo::servRequest :md5sum-) "62d2895a600383a28702b76d8606b327")
(setf (get fake_exo::servRequest :datatype-) "fake_exo/servRequest")
(setf (get fake_exo::servRequest :definition-)
      "string code
---
string error

")

(setf (get fake_exo::servResponse :md5sum-) "62d2895a600383a28702b76d8606b327")
(setf (get fake_exo::servResponse :datatype-) "fake_exo/servResponse")
(setf (get fake_exo::servResponse :definition-)
      "string code
---
string error

")



(provide :fake_exo/serv "62d2895a600383a28702b76d8606b327")


