; Auto-generated. Do not edit!


(cl:in-package fake_exo-srv)


;//! \htmlinclude serv-request.msg.html

(cl:defclass <serv-request> (roslisp-msg-protocol:ros-message)
  ((code
    :reader code
    :initarg :code
    :type cl:string
    :initform ""))
)

(cl:defclass serv-request (<serv-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <serv-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'serv-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name fake_exo-srv:<serv-request> is deprecated: use fake_exo-srv:serv-request instead.")))

(cl:ensure-generic-function 'code-val :lambda-list '(m))
(cl:defmethod code-val ((m <serv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fake_exo-srv:code-val is deprecated.  Use fake_exo-srv:code instead.")
  (code m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <serv-request>) ostream)
  "Serializes a message object of type '<serv-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'code))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'code))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <serv-request>) istream)
  "Deserializes a message object of type '<serv-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'code) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'code) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<serv-request>)))
  "Returns string type for a service object of type '<serv-request>"
  "fake_exo/servRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'serv-request)))
  "Returns string type for a service object of type 'serv-request"
  "fake_exo/servRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<serv-request>)))
  "Returns md5sum for a message object of type '<serv-request>"
  "62d2895a600383a28702b76d8606b327")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'serv-request)))
  "Returns md5sum for a message object of type 'serv-request"
  "62d2895a600383a28702b76d8606b327")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<serv-request>)))
  "Returns full string definition for message of type '<serv-request>"
  (cl:format cl:nil "string code~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'serv-request)))
  "Returns full string definition for message of type 'serv-request"
  (cl:format cl:nil "string code~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <serv-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'code))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <serv-request>))
  "Converts a ROS message object to a list"
  (cl:list 'serv-request
    (cl:cons ':code (code msg))
))
;//! \htmlinclude serv-response.msg.html

(cl:defclass <serv-response> (roslisp-msg-protocol:ros-message)
  ((error
    :reader error
    :initarg :error
    :type cl:string
    :initform ""))
)

(cl:defclass serv-response (<serv-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <serv-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'serv-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name fake_exo-srv:<serv-response> is deprecated: use fake_exo-srv:serv-response instead.")))

(cl:ensure-generic-function 'error-val :lambda-list '(m))
(cl:defmethod error-val ((m <serv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fake_exo-srv:error-val is deprecated.  Use fake_exo-srv:error instead.")
  (error m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <serv-response>) ostream)
  "Serializes a message object of type '<serv-response>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'error))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'error))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <serv-response>) istream)
  "Deserializes a message object of type '<serv-response>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'error) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'error) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<serv-response>)))
  "Returns string type for a service object of type '<serv-response>"
  "fake_exo/servResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'serv-response)))
  "Returns string type for a service object of type 'serv-response"
  "fake_exo/servResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<serv-response>)))
  "Returns md5sum for a message object of type '<serv-response>"
  "62d2895a600383a28702b76d8606b327")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'serv-response)))
  "Returns md5sum for a message object of type 'serv-response"
  "62d2895a600383a28702b76d8606b327")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<serv-response>)))
  "Returns full string definition for message of type '<serv-response>"
  (cl:format cl:nil "string error~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'serv-response)))
  "Returns full string definition for message of type 'serv-response"
  (cl:format cl:nil "string error~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <serv-response>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'error))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <serv-response>))
  "Converts a ROS message object to a list"
  (cl:list 'serv-response
    (cl:cons ':error (error msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'serv)))
  'serv-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'serv)))
  'serv-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'serv)))
  "Returns string type for a service object of type '<serv>"
  "fake_exo/serv")