#include <mruby.h>
#include <mruby/class.h>
#include <SFML/Network/IpAddress.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/network/ip_address.hxx"
#include "mrb/sfml/system/time.hxx"
#include "mrb/sfml/helpers.hxx"

static mrb_data_free_func ip_address_free = cxx_mrb_data_free<sf::IpAddress>;
MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_ip_address_type = { "sf::IpAddress", ip_address_free };

MRB_SFML_EXTERN mrb_value
mrb_sfml_ip_address_value(mrb_state* mrb, sf::IpAddress newAddress)
{
  mrb_value result = mrb_obj_new(mrb, mrb_class_get_under(mrb, mrb_module_get(mrb, "SFML"), "IpAddress"), 0, NULL);
  sf::IpAddress* address = mrb_sfml_ip_address_ptr(mrb, result);
  *address = newAddress;
  return result;
}

MRB_SFML_EXTERN sf::IpAddress
mrb_sfml_mruby_to_ip_address(mrb_state* mrb, mrb_value self)
{
  if (mrb_type(self) == MRB_TT_STRING) {
    return sf::IpAddress(mrb_string_value_ptr(mrb, self));
  }
  return *mrb_sfml_ip_address_ptr(mrb, self);
}

static mrb_value
ip_address_initialize(mrb_state* mrb, mrb_value self)
{
  sf::IpAddress* ipAddress;
  mrb_value obj;
  mrb_int b1;
  mrb_int b2;
  mrb_int b3;
  mrb_int argc = mrb_get_args(mrb, "|oiii", &obj, &b1, &b2, &b3);
  cxx_mrb_data_free_value<sf::IpAddress*>(mrb, self);
  switch (argc) {
    case 0: {
      ipAddress = new sf::IpAddress();
    } break;
    case 1: {
      if (mrb_type(obj) == MRB_TT_FIXNUM) {
        ipAddress = new sf::IpAddress((sf::Uint32)mrb_int(mrb, obj));
      } else if (mrb_type(obj) == MRB_TT_STRING) {
        ipAddress = new sf::IpAddress(mrb_string_value_ptr(mrb, obj));
      } else {
        mrb_raisef(mrb, E_ARGUMENT_ERROR, "expected String or Integer");
      }
    } break;
    case 4: {
      ipAddress = new sf::IpAddress((sf::Uint8)mrb_int(mrb, obj), (sf::Uint8)b1, (sf::Uint8)b2, (sf::Uint8)b3);
    } break;
    default: {
      mrb_raisef(mrb, E_ARGUMENT_ERROR, "expected 0, 1, or 4 arguments!");
    } break;
  }
  mrb_data_init(self, ipAddress, &mrb_sfml_ip_address_type);
  return self;
}

static mrb_value
ip_address_to_string(mrb_state* mrb, mrb_value self)
{
  sf::IpAddress* address = mrb_sfml_ip_address_ptr(mrb, self);
  return mrb_str_new_cstr(mrb, address->toString().c_str());
}

static mrb_value
ip_address_to_integer(mrb_state* mrb, mrb_value self)
{
  sf::IpAddress* address = mrb_sfml_ip_address_ptr(mrb, self);
  return mrb_fixnum_value(address->toInteger());
}

static mrb_value
ip_address_m_get_local_address(mrb_state* mrb, mrb_value self)
{
  return mrb_sfml_ip_address_value(mrb, sf::IpAddress::getLocalAddress());
}

static mrb_value
ip_address_m_get_public_address(mrb_state* mrb, mrb_value self)
{
  sf::Time* time = &sf::Time::Zero;
  mrb_get_args(mrb, "|d", &time, &mrb_sfml_time_type);
  return mrb_sfml_ip_address_value(mrb, sf::IpAddress::getPublicAddress(*time));
}

#define MRB_IP_BOOL_OPERATOR(operatorName, _operator_) \
static mrb_value \
ip_address_ ## operatorName(mrb_state* mrb, mrb_value self) \
{ \
  sf::IpAddress* address; \
  sf::IpAddress* other; \
  mrb_get_args(mrb, "d", &other, &mrb_sfml_ip_address_type); \
  address = mrb_sfml_ip_address_ptr(mrb, self); \
  return mrb_bool_value(address _operator_ other); \
}

MRB_IP_BOOL_OPERATOR(equal_to, ==);
MRB_IP_BOOL_OPERATOR(not_equal_to, !=);
MRB_IP_BOOL_OPERATOR(less_than, <);
MRB_IP_BOOL_OPERATOR(less_than_or_equal_to, <=);
MRB_IP_BOOL_OPERATOR(greater_than, >);
MRB_IP_BOOL_OPERATOR(greater_than_or_equal_to, >=);

MRB_SFML_EXTERN void
mrb_sfml_ip_address_init_bind(mrb_state* mrb, struct RClass* mod)
{
  struct RClass* tcp_socket_class = mrb_define_class_under(mrb, mod, "IpAddress", mrb->object_class);
  MRB_SET_INSTANCE_TT(tcp_socket_class, MRB_TT_DATA);

  mrb_define_method(mrb, tcp_socket_class, "initialize", ip_address_initialize,               MRB_ARGS_ARG(0,4));
  mrb_define_method(mrb, tcp_socket_class, "to_s",       ip_address_to_string,                MRB_ARGS_NONE());
  mrb_define_method(mrb, tcp_socket_class, "to_i",       ip_address_to_integer,               MRB_ARGS_NONE());
  mrb_define_method(mrb, tcp_socket_class, "==",         ip_address_equal_to,                 MRB_ARGS_REQ(1));
  mrb_define_method(mrb, tcp_socket_class, "!=",         ip_address_not_equal_to,             MRB_ARGS_REQ(1));
  mrb_define_method(mrb, tcp_socket_class, "<",          ip_address_less_than,                MRB_ARGS_REQ(1));
  mrb_define_method(mrb, tcp_socket_class, "<=",         ip_address_less_than_or_equal_to,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, tcp_socket_class, ">",          ip_address_greater_than,             MRB_ARGS_REQ(1));
  mrb_define_method(mrb, tcp_socket_class, ">=",         ip_address_greater_than_or_equal_to, MRB_ARGS_REQ(1));

  mrb_define_class_method(mrb, tcp_socket_class, "local_address",  ip_address_m_get_local_address,  MRB_ARGS_NONE());
  mrb_define_class_method(mrb, tcp_socket_class, "public_address", ip_address_m_get_public_address, MRB_ARGS_ARG(0,1));

  mrb_define_const(mrb, tcp_socket_class, "None",      mrb_sfml_ip_address_value(mrb, sf::IpAddress::None));
  mrb_define_const(mrb, tcp_socket_class, "Any",       mrb_sfml_ip_address_value(mrb, sf::IpAddress::Any));
  mrb_define_const(mrb, tcp_socket_class, "LocalHost", mrb_sfml_ip_address_value(mrb, sf::IpAddress::LocalHost));
  mrb_define_const(mrb, tcp_socket_class, "Broadcast", mrb_sfml_ip_address_value(mrb, sf::IpAddress::Broadcast));
}
