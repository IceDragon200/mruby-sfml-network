#ifndef MRB_SFML_TCP_SOCKET_H
#define MRB_SFML_TCP_SOCKET_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Network/TcpSocket.hpp>

extern "C" const struct mrb_data_type mrb_sfml_tcp_socket_type;
//extern "C" mrb_value mrb_sfml_tcp_socket_value(mrb_state*, sf::TcpSocket*);

static inline sf::TcpSocket*
mrb_sfml_tcp_socket_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::TcpSocket*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_tcp_socket_type));
}

#endif
