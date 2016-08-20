#include <mruby.h>
#include <mruby/class.h>
#include <SFML/Network/UdpSocket.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/network/udp_socket.hxx"

static mrb_data_free_func udp_socket_free = cxx_mrb_data_free<sf::UdpSocket>;
extern "C" const struct mrb_data_type mrb_sfml_udp_socket_type = { "sf::UdpSocket", udp_socket_free };

static mrb_value
udp_socket_initialize(mrb_state* mrb, mrb_value self)
{
  cxx_mrb_data_free_value(mrb, self);
  sf::UdpSocket* socket = new sf::UdpSocket();
  mrb_data_init(self, socket, &mrb_sfml_udp_socket_type);
  return self;
}

extern "C" void
mrb_sfml_udp_socket_init_bind(mrb_state* mrb, struct RClass* mod)
{
  struct RClass* udp_socket_class = mrb_define_class_under(mrb, mod, "UdpSocket", mrb_class_get_under(mrb, mod, "Socket"));
  MRB_SET_INSTANCE_TT(udp_socket_class, MRB_TT_DATA);
  mrb_define_method(mrb, udp_socket_class, "initialize", udp_socket_initialize, MRB_ARGS_NONE());
}
