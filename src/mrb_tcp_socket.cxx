#include <mruby.h>
#include <mruby/class.h>
#include <SFML/Network/TcpSocket.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/network/tcp_socket.hxx"
#include "mrb/sfml/network/ip_address.hxx"

static mrb_data_free_func tcp_socket_free = cxx_mrb_data_free<sf::TcpSocket>;
extern "C" const struct mrb_data_type mrb_sfml_tcp_socket_type = { "sf::TcpSocket", tcp_socket_free };

static mrb_value
tcp_socket_initialize(mrb_state* mrb, mrb_value self)
{
  sf::TcpSocket* socket;
  cxx_mrb_data_free_value(mrb, self);
  socket = new sf::TcpSocket();
  mrb_data_init(self, socket, &mrb_sfml_tcp_socket_type);
  return self;
}

static mrb_value
tcp_socket_get_local_port(mrb_state* mrb, mrb_value self)
{
  sf::TcpSocket* socket = mrb_sfml_tcp_socket_ptr(mrb, self);
  return mrb_fixnum_value((int)socket->getLocalPort());
}

static mrb_value
tcp_socket_get_remote_address(mrb_state* mrb, mrb_value self)
{
  sf::TcpSocket* socket = mrb_sfml_tcp_socket_ptr(mrb, self);
  return mrb_sfml_ip_address_value(mrb, socket->getRemoteAddress());
}

static mrb_value
tcp_socket_get_remote_port(mrb_state* mrb, mrb_value self)
{
  sf::TcpSocket* socket = mrb_sfml_tcp_socket_ptr(mrb, self);
  return mrb_fixnum_value((int)socket->getRemotePort());
}

static mrb_value
tcp_socket_disconnect(mrb_state* mrb, mrb_value self)
{
  sf::TcpSocket* socket = mrb_sfml_tcp_socket_ptr(mrb, self);
  socket->disconnect();
  return self;
}

extern "C" void
mrb_sfml_tcp_socket_init_bind(mrb_state* mrb, struct RClass* mod)
{
  struct RClass* tcp_socket_class = mrb_define_class_under(mrb, mod, "TcpSocket", mrb_class_get_under(mrb, mod, "Socket"));
  MRB_SET_INSTANCE_TT(tcp_socket_class, MRB_TT_DATA);
  mrb_define_method(mrb, tcp_socket_class, "initialize", tcp_socket_initialize, MRB_ARGS_NONE());
  mrb_define_method(mrb, tcp_socket_class, "local_port", tcp_socket_get_local_port, MRB_ARGS_NONE());
  mrb_define_method(mrb, tcp_socket_class, "remote_port", tcp_socket_get_remote_port, MRB_ARGS_NONE());
  mrb_define_method(mrb, tcp_socket_class, "disconnect", tcp_socket_disconnect, MRB_ARGS_NONE());
}
