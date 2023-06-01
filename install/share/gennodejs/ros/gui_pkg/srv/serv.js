// Auto-generated. Do not edit!

// (in-package gui_pkg.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class servRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.code = null;
    }
    else {
      if (initObj.hasOwnProperty('code')) {
        this.code = initObj.code
      }
      else {
        this.code = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type servRequest
    // Serialize message field [code]
    bufferOffset = _serializer.string(obj.code, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type servRequest
    let len;
    let data = new servRequest(null);
    // Deserialize message field [code]
    data.code = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.code);
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'gui_pkg/servRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9d589d39a46fa5aba4838a23b9cc4e62';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string code
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new servRequest(null);
    if (msg.code !== undefined) {
      resolved.code = msg.code;
    }
    else {
      resolved.code = ''
    }

    return resolved;
    }
};

class servResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.error = null;
    }
    else {
      if (initObj.hasOwnProperty('error')) {
        this.error = initObj.error
      }
      else {
        this.error = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type servResponse
    // Serialize message field [error]
    bufferOffset = _serializer.string(obj.error, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type servResponse
    let len;
    let data = new servResponse(null);
    // Deserialize message field [error]
    data.error = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.error);
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'gui_pkg/servResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'eca8b96616c32aacf1be8bbf14c70eba';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string error
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new servResponse(null);
    if (msg.error !== undefined) {
      resolved.error = msg.error;
    }
    else {
      resolved.error = ''
    }

    return resolved;
    }
};

module.exports = {
  Request: servRequest,
  Response: servResponse,
  md5sum() { return '62d2895a600383a28702b76d8606b327'; },
  datatype() { return 'gui_pkg/serv'; }
};
