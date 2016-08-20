#ifndef MRB_SFML_PACKET_H
#define MRB_SFML_PACKET_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Network/Packet.hpp>

extern "C" const struct mrb_data_type mrb_sfml_packet_type;
extern "C" mrb_value mrb_sfml_packet_value(mrb_state*, sf::Packet*);

static inline sf::Packet*
mrb_sfml_packet_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Packet*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_packet_type));
}

#endif
