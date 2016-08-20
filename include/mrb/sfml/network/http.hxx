#ifndef MRB_SFML_HTTP_H
#define MRB_SFML_HTTP_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Network/Http.hpp>

extern "C" const struct mrb_data_type mrb_sfml_http_type;
//extern "C" mrb_value mrb_sfml_http_value(mrb_state*, sf::Http*);

static inline sf::Http*
mrb_sfml_http_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Http*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_http_type));
}

#endif
