#include <mruby.h>
#include <mruby/class.h>
#include <SFML/Network/IpAddress.hpp>
#include "mrb/sfml/network/ip_address.hxx"

static mrb_data_free_func ip_address_free = cxx_mrb_data_free<sf::IpAddress>;
extern "C" const struct mrb_data_type mrb_sfml_ip_address_type = { "sf::IpAddress", ip_address_free };

extern "C" mrb_value
mrb_sfml_ip_address_value(mrb_state* mrb, sf::IpAddress* address)
{

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
  cxx_mrb_data_free_value(mrb, self);
  switch (argc) {
    case 0: {
      ipAddress = new sf::IpAddress();
    } break;
    case 1: {
      ipAddress = new sf::IpAddress();
    } break;
    case 4: {
      ipAddress = new sf::IpAddress();
    } break;
    default: {
      mrb_raisef(mrb, E_ARGUMENT_ERROR, "expected 0, 1, or 4 arguments!");
    } break;
  }
  mrb_data_init(self, ipAddress, &mrb_sfml_ip_address_type);
  return self;
}

extern "C" void
mrb_sfml_ip_address_init_bind(mrb_state* mrb, struct RClass* mod)
{
  struct RClass* tcp_socket_class = mrb_define_class_under(mrb, mod, "IpAddress", mrb->object_class);
  MRB_SET_INSTANCE_TT(tcp_socket_class, MRB_TT_DATA);
  mrb_define_method(mrb, tcp_socket_class, "initialize", ip_address_initialize, MRB_ARGS_ARG(0,4));
}
