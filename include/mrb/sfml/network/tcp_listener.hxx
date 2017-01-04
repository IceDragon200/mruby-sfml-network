#ifndef MRB_SFML_TCP_LISTENER_H
#define MRB_SFML_TCP_LISTENER_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Network/TcpListener.hpp>
#include "mrb/sfml/helpers.hxx"

MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_tcp_listener_type;
//MRB_SFML_EXTERN mrb_value mrb_sfml_tcp_listener_value(mrb_state*, sf::TcpListener*);

static inline sf::TcpListener*
mrb_sfml_tcp_listener_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::TcpListener*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_tcp_listener_type));
}

#endif
