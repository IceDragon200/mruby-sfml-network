#ifndef MRB_SFML_TCP_LISTENER_H
#define MRB_SFML_TCP_LISTENER_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Network/TcpListener.hpp>

extern "C" const struct mrb_data_type mrb_sfml_tcp_listener_type;
//extern "C" mrb_value mrb_sfml_tcp_listener_value(mrb_state*, sf::TcpListener*);

static inline sf::TcpListener*
mrb_sfml_tcp_listener_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::TcpListener*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_tcp_listener_type));
}

#endif
