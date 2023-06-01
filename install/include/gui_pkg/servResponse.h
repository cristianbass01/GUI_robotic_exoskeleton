// Generated by gencpp from file gui_pkg/servResponse.msg
// DO NOT EDIT!


#ifndef GUI_PKG_MESSAGE_SERVRESPONSE_H
#define GUI_PKG_MESSAGE_SERVRESPONSE_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace gui_pkg
{
template <class ContainerAllocator>
struct servResponse_
{
  typedef servResponse_<ContainerAllocator> Type;

  servResponse_()
    : error()  {
    }
  servResponse_(const ContainerAllocator& _alloc)
    : error(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _error_type;
  _error_type error;





  typedef boost::shared_ptr< ::gui_pkg::servResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::gui_pkg::servResponse_<ContainerAllocator> const> ConstPtr;

}; // struct servResponse_

typedef ::gui_pkg::servResponse_<std::allocator<void> > servResponse;

typedef boost::shared_ptr< ::gui_pkg::servResponse > servResponsePtr;
typedef boost::shared_ptr< ::gui_pkg::servResponse const> servResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::gui_pkg::servResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::gui_pkg::servResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::gui_pkg::servResponse_<ContainerAllocator1> & lhs, const ::gui_pkg::servResponse_<ContainerAllocator2> & rhs)
{
  return lhs.error == rhs.error;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::gui_pkg::servResponse_<ContainerAllocator1> & lhs, const ::gui_pkg::servResponse_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace gui_pkg

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::gui_pkg::servResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::gui_pkg::servResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::gui_pkg::servResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::gui_pkg::servResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::gui_pkg::servResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::gui_pkg::servResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::gui_pkg::servResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "eca8b96616c32aacf1be8bbf14c70eba";
  }

  static const char* value(const ::gui_pkg::servResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xeca8b96616c32aacULL;
  static const uint64_t static_value2 = 0xf1be8bbf14c70ebaULL;
};

template<class ContainerAllocator>
struct DataType< ::gui_pkg::servResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "gui_pkg/servResponse";
  }

  static const char* value(const ::gui_pkg::servResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::gui_pkg::servResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string error\n"
"\n"
;
  }

  static const char* value(const ::gui_pkg::servResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::gui_pkg::servResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.error);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct servResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::gui_pkg::servResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::gui_pkg::servResponse_<ContainerAllocator>& v)
  {
    s << indent << "error: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.error);
  }
};

} // namespace message_operations
} // namespace ros

#endif // GUI_PKG_MESSAGE_SERVRESPONSE_H
