// Auto-generated. Do not edit!

// (in-package gui_pkg.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class my_msg {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.n1 = null;
    }
    else {
      if (initObj.hasOwnProperty('n1')) {
        this.n1 = initObj.n1
      }
      else {
        this.n1 = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type my_msg
    // Serialize message field [n1]
    bufferOffset = _serializer.int32(obj.n1, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type my_msg
    let len;
    let data = new my_msg(null);
    // Deserialize message field [n1]
    data.n1 = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'gui_pkg/my_msg';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9af3d60cfc2ff33bd276c7f8d4a1f7d6';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 n1
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new my_msg(null);
    if (msg.n1 !== undefined) {
      resolved.n1 = msg.n1;
    }
    else {
      resolved.n1 = 0
    }

    return resolved;
    }
};

module.exports = my_msg;
