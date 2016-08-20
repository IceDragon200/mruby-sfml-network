#ifndef MRB_SFML_SOCKET_SELECTOR_H
#define MRB_SFML_SOCKET_SELECTOR_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Network/SocketSelector.hpp>

extern "C" const struct mrb_data_type mrb_sfml_socket_selector_type;
//extern "C" mrb_value mrb_sfml_socket_selector_value(mrb_state*, sf::SocketSelector*);

static inline sf::SocketSelector*
mrb_sfml_socket_selector_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::SocketSelector*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_socket_selector_type));
}

#endif
