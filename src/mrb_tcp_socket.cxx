#include <mruby.h>
#include <mruby/array.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <SFML/Network/TcpSocket.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/network/ip_address.hxx"
#include "mrb/sfml/network/packet.hxx"
#include "mrb/sfml/network/tcp_socket.hxx"
#include "mrb/sfml/system/time.hxx"
#include "mrb/sfml/helpers.hxx"

static mrb_data_free_func tcp_socket_free = cxx_mrb_data_free<sf::TcpSocket>;
MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_tcp_socket_type = { "sf::TcpSocket", tcp_socket_free };

static mrb_value
tcp_socket_initialize(mrb_state* mrb, mrb_value self)
{
  sf::TcpSocket* socket;
  cxx_mrb_data_free_value<sf::TcpSocket*>(mrb, self);
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
tcp_socket_connect(mrb_state* mrb, mrb_value self)
{
  sf::IpAddress address;
  mrb_value remoteAddressObj;
  mrb_int remotePort;
  sf::Time* time = &sf::Time::Zero;
  sf::TcpSocket* socket;
  mrb_get_args(mrb, "oi|d",
    &remoteAddressObj,
    &remotePort,
    &time, &mrb_sfml_time_type);
  address = mrb_sfml_mruby_to_ip_address(mrb, remoteAddressObj);
  socket = mrb_sfml_tcp_socket_ptr(mrb, self);
  return mrb_fixnum_value(socket->connect(address, (unsigned short)remotePort, *time));
}

static mrb_value
tcp_socket_disconnect(mrb_state* mrb, mrb_value self)
{
  sf::TcpSocket* socket = mrb_sfml_tcp_socket_ptr(mrb, self);
  socket->disconnect();
  return self;
}

static mrb_value
tcp_socket_send_data(mrb_state* mrb, mrb_value self)
{
  sf::TcpSocket* socket;
  char* bytes;
  mrb_int len;
  std::size_t sent = 0;
  mrb_value result;
  sf::Socket::Status status;
  mrb_get_args(mrb, "s", &bytes, &len);
  socket = mrb_sfml_tcp_socket_ptr(mrb, self);
  status = socket->send(bytes, len * sizeof(char), sent);
  result = mrb_ary_new_capa(mrb, 2);
  mrb_ary_set(mrb, result, 0, mrb_fixnum_value(status));
  mrb_ary_set(mrb, result, 1, mrb_fixnum_value(sent));
  return result;
}

static mrb_value
tcp_socket_receive_data(mrb_state* mrb, mrb_value self)
{
  sf::TcpSocket* socket;
  char* bytes;
  mrb_int len;
  std::size_t received = 0;
  mrb_value result;
  sf::Socket::Status status;
  mrb_get_args(mrb, "s", &bytes, &len);
  socket = mrb_sfml_tcp_socket_ptr(mrb, self);
  status = socket->receive(bytes, len * sizeof(char), received);
  result = mrb_ary_new_capa(mrb, 2);
  mrb_ary_set(mrb, result, 0, mrb_fixnum_value(status));
  mrb_ary_set(mrb, result, 1, mrb_fixnum_value(received));
  return result;
}

static mrb_value
tcp_socket_send_packet(mrb_state* mrb, mrb_value self)
{
  sf::TcpSocket* socket;
  sf::Packet* packet;
  mrb_get_args(mrb, "d", &packet, &mrb_sfml_packet_type);
  socket = mrb_sfml_tcp_socket_ptr(mrb, self);
  return mrb_fixnum_value(socket->send(*packet));
}

static mrb_value
tcp_socket_receive_packet(mrb_state* mrb, mrb_value self)
{
  sf::TcpSocket* socket;
  sf::Packet* packet;
  mrb_get_args(mrb, "d", &packet, &mrb_sfml_packet_type);
  socket = mrb_sfml_tcp_socket_ptr(mrb, self);
  return mrb_fixnum_value(socket->receive(*packet));
}

MRB_SFML_EXTERN void
mrb_sfml_tcp_socket_init_bind(mrb_state* mrb, struct RClass* mod)
{
  struct RClass* tcp_socket_class = mrb_define_class_under(mrb, mod, "TcpSocket", mrb_class_get_under(mrb, mod, "Socket"));
  MRB_SET_INSTANCE_TT(tcp_socket_class, MRB_TT_DATA);
  mrb_define_method(mrb, tcp_socket_class, "initialize",     tcp_socket_initialize,         MRB_ARGS_NONE());
  mrb_define_method(mrb, tcp_socket_class, "local_port",     tcp_socket_get_local_port,     MRB_ARGS_NONE());
  mrb_define_method(mrb, tcp_socket_class, "remote_address", tcp_socket_get_remote_address, MRB_ARGS_NONE());
  mrb_define_method(mrb, tcp_socket_class, "remote_port",    tcp_socket_get_remote_port,    MRB_ARGS_NONE());
  mrb_define_method(mrb, tcp_socket_class, "connect",        tcp_socket_connect,            MRB_ARGS_ARG(2,1));
  mrb_define_method(mrb, tcp_socket_class, "disconnect",     tcp_socket_disconnect,         MRB_ARGS_NONE());
  mrb_define_method(mrb, tcp_socket_class, "send_data",      tcp_socket_send_data,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, tcp_socket_class, "receive_data",   tcp_socket_receive_data,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, tcp_socket_class, "send_packet",    tcp_socket_send_packet,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, tcp_socket_class, "receive_packet", tcp_socket_receive_packet,     MRB_ARGS_REQ(1));
}
