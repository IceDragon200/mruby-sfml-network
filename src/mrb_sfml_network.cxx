#include <mruby.h>
#include <mruby/class.h>
#include <SFML/Network.hpp>

static struct RClass *sfml_module;

extern "C" void
mrb_mruby_sfml_network_gem_init(mrb_state *mrb)
{
  sfml_module = mrb_define_module(mrb, "SFML");
}

extern "C" void
mrb_mruby_sfml_network_gem_final(mrb_state *mrb)
{

}
