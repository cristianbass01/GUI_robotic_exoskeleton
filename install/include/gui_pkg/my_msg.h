// Generated by gencpp from file gui_pkg/my_msg.msg
// DO NOT EDIT!


#ifndef GUI_PKG_MESSAGE_MY_MSG_H
#define GUI_PKG_MESSAGE_MY_MSG_H


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
struct my_msg_
{
  typedef my_msg_<ContainerAllocator> Type;

  my_msg_()
    : n1(0)  {
    }
  my_msg_(const ContainerAllocator& _alloc)
    : n1(0)  {
  (void)_alloc;
    }



   typedef int32_t _n1_type;
  _n1_type n1;





  typedef boost::shared_ptr< ::gui_pkg::my_msg_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::gui_pkg::my_msg_<ContainerAllocator> const> ConstPtr;

}; // struct my_msg_

typedef ::gui_pkg::my_msg_<std::allocator<void> > my_msg;

typedef boost::shared_ptr< ::gui_pkg::my_msg > my_msgPtr;
typedef boost::shared_ptr< ::gui_pkg::my_msg const> my_msgConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::gui_pkg::my_msg_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::gui_pkg::my_msg_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::gui_pkg::my_msg_<ContainerAllocator1> & lhs, const ::gui_pkg::my_msg_<ContainerAllocator2> & rhs)
{
  return lhs.n1 == rhs.n1;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::gui_pkg::my_msg_<ContainerAllocator1> & lhs, const ::gui_pkg::my_msg_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace gui_pkg

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::gui_pkg::my_msg_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::gui_pkg::my_msg_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::gui_pkg::my_msg_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::gui_pkg::my_msg_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::gui_pkg::my_msg_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::gui_pkg::my_msg_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::gui_pkg::my_msg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "9af3d60cfc2ff33bd276c7f8d4a1f7d6";
  }

  static const char* value(const ::gui_pkg::my_msg_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x9af3d60cfc2ff33bULL;
  static const uint64_t static_value2 = 0xd276c7f8d4a1f7d6ULL;
};

template<class ContainerAllocator>
struct DataType< ::gui_pkg::my_msg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "gui_pkg/my_msg";
  }

  static const char* value(const ::gui_pkg::my_msg_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::gui_pkg::my_msg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int32 n1\n"
;
  }

  static const char* value(const ::gui_pkg::my_msg_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::gui_pkg::my_msg_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.n1);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct my_msg_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::gui_pkg::my_msg_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::gui_pkg::my_msg_<ContainerAllocator>& v)
  {
    s << indent << "n1: ";
    Printer<int32_t>::stream(s, indent + "  ", v.n1);
  }
};

} // namespace message_operations
} // namespace ros

#endif // GUI_PKG_MESSAGE_MY_MSG_H
