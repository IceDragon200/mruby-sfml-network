#ifndef MRB_SFML_IP_ADDRESS_H
#define MRB_SFML_IP_ADDRESS_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Network/IpAddress.hpp>

extern "C" const struct mrb_data_type mrb_sfml_ip_address_type;
extern "C" mrb_value mrb_sfml_ip_address_value(mrb_state*, sf::IpAddress);
extern "C" sf::IpAddress mrb_sfml_mruby_to_ip_address(mrb_state* mrb, mrb_value self);

static inline sf::IpAddress*
mrb_sfml_ip_address_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::IpAddress*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_ip_address_type));
}

#endif
