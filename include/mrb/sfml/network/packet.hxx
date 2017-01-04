#ifndef MRB_SFML_PACKET_H
#define MRB_SFML_PACKET_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Network/Packet.hpp>
#include "mrb/sfml/helpers.hxx"

MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_packet_type;
//MRB_SFML_EXTERN mrb_value mrb_sfml_packet_value(mrb_state*, sf::Packet*);

static inline sf::Packet*
mrb_sfml_packet_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Packet*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_packet_type));
}

#endif
