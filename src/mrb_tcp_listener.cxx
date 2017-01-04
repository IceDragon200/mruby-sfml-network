#include <mruby.h>
#include <mruby/class.h>
#include <SFML/Network/TcpListener.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/network/tcp_listener.hxx"
#include "mrb/sfml/network/tcp_socket.hxx"
#include "mrb/sfml/network/ip_address.hxx"
#include "mrb/sfml/helpers.hxx"

static mrb_data_free_func tcp_listener_free = cxx_mrb_data_free<sf::TcpListener>;
MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_tcp_listener_type = { "sf::TcpListener", tcp_listener_free };

static mrb_value
tcp_listener_initialize(mrb_state* mrb, mrb_value self)
{
  sf::TcpListener* socket;
  cxx_mrb_data_free_value<sf::TcpListener*>(mrb, self);
  socket = new sf::TcpListener();
  mrb_data_init(self, socket, &mrb_sfml_tcp_listener_type);
  return self;
}

static mrb_value
tcp_listener_get_local_port(mrb_state* mrb, mrb_value self)
{
  sf::TcpListener* socket = mrb_sfml_tcp_listener_ptr(mrb, self);
  return mrb_fixnum_value(socket->getLocalPort());
}

static mrb_value
tcp_listener_listen(mrb_state* mrb, mrb_value self)
{
  sf::TcpListener* socket;
  sf::IpAddress address = sf::IpAddress::Any;
  mrb_value addressObj;
  mrb_int port;
  mrb_get_args(mrb, "i|o", &port, &addressObj);
  if (!mrb_nil_p(addressObj)) {
    address = mrb_sfml_mruby_to_ip_address(mrb, addressObj);
  }
  socket = mrb_sfml_tcp_listener_ptr(mrb, self);
  return mrb_fixnum_value(socket->listen(port, address));
}

static mrb_value
tcp_listener_close(mrb_state* mrb, mrb_value self)
{
  sf::TcpListener* socket = mrb_sfml_tcp_listener_ptr(mrb, self);
  socket->close();
  return self;
}

static mrb_value
tcp_listener_accept(mrb_state* mrb, mrb_value self)
{
  sf::TcpListener* listener;
  sf::TcpSocket* socket;
  mrb_get_args(mrb, "d", &socket, &mrb_sfml_tcp_socket_type);
  listener = mrb_sfml_tcp_listener_ptr(mrb, self);
  return mrb_fixnum_value(listener->accept(*socket));
}

MRB_SFML_EXTERN void
mrb_sfml_tcp_listener_init_bind(mrb_state* mrb, struct RClass* mod)
{
  struct RClass* tcp_listener_class = mrb_define_class_under(mrb, mod, "TcpListener", mrb_class_get_under(mrb, mod, "Socket"));
  MRB_SET_INSTANCE_TT(tcp_listener_class, MRB_TT_DATA);
  mrb_define_method(mrb, tcp_listener_class, "initialize",     tcp_listener_initialize,     MRB_ARGS_NONE());
  mrb_define_method(mrb, tcp_listener_class, "local_port",     tcp_listener_get_local_port, MRB_ARGS_NONE());
  mrb_define_method(mrb, tcp_listener_class, "listen",         tcp_listener_listen,         MRB_ARGS_ARG(1,1));
  mrb_define_method(mrb, tcp_listener_class, "close",          tcp_listener_close,          MRB_ARGS_NONE());
  mrb_define_method(mrb, tcp_listener_class, "accept",         tcp_listener_accept,         MRB_ARGS_REQ(1));
}
