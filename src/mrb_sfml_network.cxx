#include <mruby.h>
#include <mruby/class.h>
#include <SFML/Network.hpp>
#include "mrb/sfml/network.hxx"
#include "mrb/sfml/helpers.hxx"

MRB_SFML_EXTERN void mrb_sfml_ftp_init_bind(mrb_state* mrb, struct RClass* mod);
MRB_SFML_EXTERN void mrb_sfml_http_init_bind(mrb_state* mrb, struct RClass* mod);
MRB_SFML_EXTERN void mrb_sfml_ip_address_init_bind(mrb_state* mrb, struct RClass* mod);
MRB_SFML_EXTERN void mrb_sfml_packet_init_bind(mrb_state* mrb, struct RClass* mod);
MRB_SFML_EXTERN void mrb_sfml_socket_init_bind(mrb_state* mrb, struct RClass* mod);
MRB_SFML_EXTERN void mrb_sfml_socket_selector_init_bind(mrb_state* mrb, struct RClass* mod);
MRB_SFML_EXTERN void mrb_sfml_tcp_listener_init_bind(mrb_state* mrb, struct RClass* mod);
MRB_SFML_EXTERN void mrb_sfml_tcp_socket_init_bind(mrb_state* mrb, struct RClass* mod);
MRB_SFML_EXTERN void mrb_sfml_udp_socket_init_bind(mrb_state* mrb, struct RClass* mod);

MRB_SFML_EXTERN void
mrb_mruby_sfml_network_gem_init(mrb_state* mrb)
{
  struct RClass* sfml_module = mrb_define_module(mrb, "SFML");
  mrb_sfml_ftp_init_bind(mrb, sfml_module);
  mrb_sfml_http_init_bind(mrb, sfml_module);
  mrb_sfml_ip_address_init_bind(mrb, sfml_module);
  mrb_sfml_packet_init_bind(mrb, sfml_module);
  mrb_sfml_socket_init_bind(mrb, sfml_module);
  mrb_sfml_socket_selector_init_bind(mrb, sfml_module);
  mrb_sfml_tcp_listener_init_bind(mrb, sfml_module);
  mrb_sfml_tcp_socket_init_bind(mrb, sfml_module);
  mrb_sfml_udp_socket_init_bind(mrb, sfml_module);
}

MRB_SFML_EXTERN void
mrb_mruby_sfml_network_gem_final(mrb_state* mrb)
{

}
