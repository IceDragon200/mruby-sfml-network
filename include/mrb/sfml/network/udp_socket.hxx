#ifndef MRB_SFML_UDP_SOCKET_H
#define MRB_SFML_UDP_SOCKET_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Network/UdpSocket.hpp>
#include "mrb/sfml/helpers.hxx"

MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_udp_socket_type;
//MRB_SFML_EXTERN mrb_value mrb_sfml_udp_socket_value(mrb_state*, sf::UdpSocket*);

static inline sf::UdpSocket*
mrb_sfml_udp_socket_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::UdpSocket*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_udp_socket_type));
}

#endif
