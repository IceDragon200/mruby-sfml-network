#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <SFML/Network/Socket.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/network/socket.hxx"
#include "mrb/sfml/network/tcp_socket.hxx"
#include "mrb/sfml/network/udp_socket.hxx"

static sf::Socket*
mrb_sfml_socket_ptr(mrb_state* mrb, mrb_value self)
{
  cxx_mrb_ensure_type_data(mrb, self);
  void *dptr = DATA_PTR(self);
  const struct mrb_data_type *dt = DATA_TYPE(self);
  if (&mrb_sfml_udp_socket_type == dt || &mrb_sfml_tcp_socket_type == dt) {
    return (sf::Socket*)dptr;
  } else {
    mrb_raisef(mrb, E_TYPE_ERROR, "wrong argument type (expected a SFML::TcpSocket or SFML::UdpSocket)");
  }
  return NULL;
}

static mrb_value
socket_set_blocking(mrb_state* mrb, mrb_value self)
{
  mrb_bool opt;
  sf::Socket* socket;
  mrb_get_args(mrb, "b", &opt);
  socket = mrb_sfml_socket_ptr(mrb, self);
  socket->setBlocking(opt);
  return self;
}

static mrb_value
socket_get_blocking(mrb_state* mrb, mrb_value self)
{
  sf::Socket* socket = mrb_sfml_socket_ptr(mrb, self);
  return mrb_bool_value(socket->isBlocking());
}

extern "C" void
mrb_sfml_socket_init_bind(mrb_state* mrb, struct RClass* mod)
{
  struct RClass* socket_class = mrb_define_class_under(mrb, mod, "Socket", mrb->object_class);
  struct RClass* status_module = mrb_define_module_under(mrb, socket_class, "Status");
  MRB_SET_INSTANCE_TT(socket_class, MRB_TT_DATA);
  mrb_define_const(mrb, status_module, "Done", mrb_fixnum_value(sf::Socket::Status::Done));
  mrb_define_const(mrb, status_module, "NotReady", mrb_fixnum_value(sf::Socket::Status::NotReady));
  mrb_define_const(mrb, status_module, "Partial", mrb_fixnum_value(sf::Socket::Status::Partial));
  mrb_define_const(mrb, status_module, "Disconnected", mrb_fixnum_value(sf::Socket::Status::Disconnected));
  mrb_define_const(mrb, status_module, "Error", mrb_fixnum_value(sf::Socket::Status::Error));
  mrb_define_method(mrb, socket_class, "blocking=", socket_set_blocking, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, socket_class, "blocking", socket_get_blocking, MRB_ARGS_NONE());
}
