#ifndef MRB_SFML_FTP_H
#define MRB_SFML_FTP_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/Network/Ftp.hpp>
#include "mrb/sfml/helpers.hxx"

MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_ftp_type;
//MRB_SFML_EXTERN mrb_value mrb_sfml_ftp_value(mrb_state*, sf::Ftp*);

static inline sf::Ftp*
mrb_sfml_ftp_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Ftp*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_ftp_type));
}

#endif
