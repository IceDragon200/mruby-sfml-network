#include <mruby.h>
#include <mruby/class.h>
#include <SFML/Network/UdpSocket.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/network/ip_address.hxx"
#include "mrb/sfml/network/packet.hxx"
#include "mrb/sfml/network/udp_socket.hxx"
#include "mrb/sfml/system/time.hxx"
#include "mrb/sfml/helpers.hxx"

static mrb_data_free_func udp_socket_free = cxx_mrb_data_free<sf::UdpSocket>;
MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_udp_socket_type = { "sf::UdpSocket", udp_socket_free };

static mrb_value
udp_socket_initialize(mrb_state* mrb, mrb_value self)
{
  cxx_mrb_data_free_value<sf::UdpSocket*>(mrb, self);
  sf::UdpSocket* socket = new sf::UdpSocket();
  mrb_data_init(self, socket, &mrb_sfml_udp_socket_type);
  return self;
}

static mrb_value
udp_socket_get_local_port(mrb_state* mrb, mrb_value self)
{
  sf::UdpSocket* socket = mrb_sfml_udp_socket_ptr(mrb, self);
  return mrb_fixnum_value((int)socket->getLocalPort());
}

static mrb_value
udp_socket_bind(mrb_state* mrb, mrb_value self)
{
  sf::UdpSocket* socket;
  mrb_int port;
  sf::IpAddress* address = &sf::IpAddress::Any;
  mrb_get_args(mrb, "i|d",
    &port,
    &address, &mrb_sfml_ip_address_type);
  socket = mrb_sfml_udp_socket_ptr(mrb, self);
  return mrb_fixnum_value(socket->bind(port, *address));
}

static mrb_value
udp_socket_unbind(mrb_state* mrb, mrb_value self)
{
  sf::UdpSocket* socket = mrb_sfml_udp_socket_ptr(mrb, self);
  socket->unbind();
  return self;
}

static mrb_value
udp_socket_send_data(mrb_state* mrb, mrb_value self)
{
  sf::UdpSocket* socket;
  sf::Socket::Status status;
  mrb_value result;
  char* bytes;
  mrb_int len;
  mrb_value remoteAddressObj;
  sf::IpAddress remoteAddress;
  mrb_int remotePort;
  mrb_get_args(mrb, "soi",
    &bytes, &len,
    &remoteAddressObj,
    &remotePort);
  socket = mrb_sfml_udp_socket_ptr(mrb, self);
  remoteAddress = mrb_sfml_mruby_to_ip_address(mrb, remoteAddressObj);
  status = socket->send(bytes, len * sizeof(char), remoteAddress, (unsigned short)remotePort);
  result = mrb_ary_new_capa(mrb, 2);
  mrb_ary_set(mrb, result, 0, mrb_fixnum_value(status));
  mrb_ary_set(mrb, result, 1, mrb_fixnum_value(len));
  return result;
}

static mrb_value
udp_socket_receive_data(mrb_state* mrb, mrb_value self)
{
  sf::UdpSocket* socket;
  mrb_value result;
  sf::Socket::Status status;
  std::size_t received = 0;
  char* bytes;
  mrb_int len;
  sf::IpAddress remoteAddress;
  unsigned short remotePort;
  mrb_get_args(mrb, "s", &bytes, &len);
  socket = mrb_sfml_udp_socket_ptr(mrb, self);
  status = socket->receive(bytes, len * sizeof(char), received, remoteAddress, remotePort);
  result = mrb_ary_new_capa(mrb, 4);
  mrb_ary_set(mrb, result, 0, mrb_fixnum_value(status));
  mrb_ary_set(mrb, result, 1, mrb_fixnum_value(received));
  mrb_ary_set(mrb, result, 2, mrb_sfml_ip_address_value(mrb, remoteAddress));
  mrb_ary_set(mrb, result, 3, mrb_fixnum_value(remotePort));
  return result;
}

static mrb_value
udp_socket_send_packet(mrb_state* mrb, mrb_value self)
{
  sf::UdpSocket* socket;
  sf::Socket::Status status;
  mrb_value result;
  sf::Packet* packet;
  mrb_value remoteAddressObj;
  sf::IpAddress remoteAddress;
  mrb_int remotePort;
  mrb_get_args(mrb, "doi",
    &packet, &mrb_sfml_packet_type,
    &remoteAddressObj,
    &remotePort);
  remoteAddress = mrb_sfml_mruby_to_ip_address(mrb, remoteAddressObj);
  socket = mrb_sfml_udp_socket_ptr(mrb, self);
  status = socket->send(*packet, remoteAddress, (unsigned short)remotePort);
  result = mrb_ary_new_capa(mrb, 2);
  return mrb_fixnum_value(status);
}

static mrb_value
udp_socket_receive_packet(mrb_state* mrb, mrb_value self)
{
  sf::UdpSocket* socket;
  mrb_value result;
  sf::Socket::Status status;
  sf::Packet* packet;
  sf::IpAddress remoteAddress;
  unsigned short remotePort;
  mrb_get_args(mrb, "d", &packet, &mrb_sfml_packet_type);
  socket = mrb_sfml_udp_socket_ptr(mrb, self);
  status = socket->receive(*packet, remoteAddress, remotePort);
  result = mrb_ary_new_capa(mrb, 3);
  mrb_ary_set(mrb, result, 0, mrb_fixnum_value(status));
  mrb_ary_set(mrb, result, 1, mrb_sfml_ip_address_value(mrb, remoteAddress));
  mrb_ary_set(mrb, result, 2, mrb_fixnum_value(remotePort));
  return result;
}

MRB_SFML_EXTERN void
mrb_sfml_udp_socket_init_bind(mrb_state* mrb, struct RClass* mod)
{
  struct RClass* udp_socket_class = mrb_define_class_under(mrb, mod, "UdpSocket", mrb_class_get_under(mrb, mod, "Socket"));
  MRB_SET_INSTANCE_TT(udp_socket_class, MRB_TT_DATA);
  mrb_define_method(mrb, udp_socket_class, "initialize",     udp_socket_initialize,       MRB_ARGS_NONE());
  mrb_define_method(mrb, udp_socket_class, "local_port",     udp_socket_get_local_port,   MRB_ARGS_NONE());
  mrb_define_method(mrb, udp_socket_class, "bind",           udp_socket_bind,             MRB_ARGS_ARG(1,1));
  mrb_define_method(mrb, udp_socket_class, "unbind",         udp_socket_unbind,           MRB_ARGS_NONE());
  mrb_define_method(mrb, udp_socket_class, "send_data",      udp_socket_send_data,        MRB_ARGS_REQ(3));
  mrb_define_method(mrb, udp_socket_class, "receive_data",   udp_socket_receive_data,     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, udp_socket_class, "send_packet",    udp_socket_send_packet,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, udp_socket_class, "receive_packet", udp_socket_receive_packet,   MRB_ARGS_REQ(1));
}
