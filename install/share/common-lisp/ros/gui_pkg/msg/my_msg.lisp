; Auto-generated. Do not edit!


(cl:in-package gui_pkg-msg)


;//! \htmlinclude my_msg.msg.html

(cl:defclass <my_msg> (roslisp-msg-protocol:ros-message)
  ((n1
    :reader n1
    :initarg :n1
    :type cl:integer
    :initform 0))
)

(cl:defclass my_msg (<my_msg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <my_msg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'my_msg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name gui_pkg-msg:<my_msg> is deprecated: use gui_pkg-msg:my_msg instead.")))

(cl:ensure-generic-function 'n1-val :lambda-list '(m))
(cl:defmethod n1-val ((m <my_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gui_pkg-msg:n1-val is deprecated.  Use gui_pkg-msg:n1 instead.")
  (n1 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <my_msg>) ostream)
  "Serializes a message object of type '<my_msg>"
  (cl:let* ((signed (cl:slot-value msg 'n1)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <my_msg>) istream)
  "Deserializes a message object of type '<my_msg>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'n1) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<my_msg>)))
  "Returns string type for a message object of type '<my_msg>"
  "gui_pkg/my_msg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'my_msg)))
  "Returns string type for a message object of type 'my_msg"
  "gui_pkg/my_msg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<my_msg>)))
  "Returns md5sum for a message object of type '<my_msg>"
  "9af3d60cfc2ff33bd276c7f8d4a1f7d6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'my_msg)))
  "Returns md5sum for a message object of type 'my_msg"
  "9af3d60cfc2ff33bd276c7f8d4a1f7d6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<my_msg>)))
  "Returns full string definition for message of type '<my_msg>"
  (cl:format cl:nil "int32 n1~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'my_msg)))
  "Returns full string definition for message of type 'my_msg"
  (cl:format cl:nil "int32 n1~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <my_msg>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <my_msg>))
  "Converts a ROS message object to a list"
  (cl:list 'my_msg
    (cl:cons ':n1 (n1 msg))
))
