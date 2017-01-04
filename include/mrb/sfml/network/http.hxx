#ifndef MRB_SFML_HTTP_H
#define MRB_SFML_HTTP_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Network/Http.hpp>
#include "mrb/sfml/helpers.hxx"

MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_http_type;
//MRB_SFML_EXTERN mrb_value mrb_sfml_http_value(mrb_state*, sf::Http*);

static inline sf::Http*
mrb_sfml_http_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Http*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_http_type));
}

#endif
