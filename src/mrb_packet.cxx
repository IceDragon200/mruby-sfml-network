#include <mruby.h>
#include <mruby/array.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <SFML/Network/Packet.hpp>
#include "mrb/sfml/network/packet.hxx"
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/helpers.hxx"

static mrb_data_free_func packet_free = cxx_mrb_data_free<sf::Packet>;
extern "C" const struct mrb_data_type mrb_sfml_packet_type = { "sf::Packet", packet_free };

static mrb_value
packet_initialize(mrb_state* mrb, mrb_value self)
{
  sf::Packet* packet;
  cxx_mrb_data_free_value<sf::Packet*>(mrb, self);
  packet = new sf::Packet();
  mrb_data_init(self, packet, &mrb_sfml_packet_type);
  return self;
}

static mrb_value
packet_append_data(mrb_state* mrb, mrb_value self)
{
  sf::Packet* packet;
  char* bytes;
  mrb_int len;
  mrb_get_args(mrb, "s", &bytes, &len);
  packet = mrb_sfml_packet_ptr(mrb, self);
  packet->append(bytes, len);
  return self;
}

static mrb_value
packet_clear(mrb_state* mrb, mrb_value self)
{
  sf::Packet* packet;
  packet = mrb_sfml_packet_ptr(mrb, self);
  packet->clear();
  return self;
}

static mrb_value
packet_get_data_size(mrb_state* mrb, mrb_value self)
{
  sf::Packet* packet;
  packet = mrb_sfml_packet_ptr(mrb, self);
  return mrb_fixnum_value(packet->getDataSize());
}

static mrb_value
packet_end_of_packet(mrb_state* mrb, mrb_value self)
{
  sf::Packet* packet;
  packet = mrb_sfml_packet_ptr(mrb, self);
  return mrb_bool_value(packet->endOfPacket());
}

template <typename T>
static mrb_value
abstract_packet_read(mrb_state* mrb, mrb_value self)
{
  sf::Packet* packet;
  T value;
  mrb_value result;
  packet = mrb_sfml_packet_ptr(mrb, self);
  result = mrb_ary_new_capa(mrb, 2);
  if (*packet >> value) {
    mrb_ary_set(mrb, result, 0, mrb_bool_value(true));
    mrb_ary_set(mrb, result, 1, sfml_value_to_mrb<T>(mrb, value));
  } else {
    mrb_ary_set(mrb, result, 0, mrb_bool_value(false));
    mrb_ary_set(mrb, result, 1, mrb_nil_value());
  }
  return result;
}

static mrb_value
packet_write_bool(mrb_state* mrb, mrb_value self)
{
  mrb_bool value;
  bool output;
  sf::Packet* packet;
  mrb_get_args(mrb, "b", &value);
  packet = mrb_sfml_packet_ptr(mrb, self);
  output = static_cast<bool>(value);
  if (*packet << output) {
    return mrb_bool_value(true);
  }
  return mrb_bool_value(false);
}

template <typename T>
static mrb_value
abstract_packet_write_int(mrb_state* mrb, mrb_value self)
{
  sf::Packet* packet;
  mrb_int value;
  T output;
  mrb_get_args(mrb, "i", &value);
  packet = mrb_sfml_packet_ptr(mrb, self);
  output = static_cast<T>(value);
  if (*packet << output) {
    return mrb_bool_value(true);
  }
  return mrb_bool_value(false);
}

template <typename T>
static mrb_value
abstract_packet_write_float(mrb_state* mrb, mrb_value self)
{
  sf::Packet* packet;
  mrb_float value;
  T output;
  mrb_get_args(mrb, "f", &value);
  packet = mrb_sfml_packet_ptr(mrb, self);
  output = static_cast<T>(value);
  if (*packet << output) {
    return mrb_bool_value(true);
  }
  return mrb_bool_value(false);
}

static mrb_value
packet_write_string(mrb_state* mrb, mrb_value self)
{
  char* value;
  sf::Packet* packet;
  mrb_get_args(mrb, "z", &value);
  packet = mrb_sfml_packet_ptr(mrb, self);
  if (*packet << value) {
    return mrb_bool_value(true);
  }
  return mrb_bool_value(false);
}

extern "C" void
mrb_sfml_packet_init_bind(mrb_state* mrb, struct RClass* mod)
{
  struct RClass* packet_class = mrb_define_class_under(mrb, mod, "Packet", mrb->object_class);
  MRB_SET_INSTANCE_TT(packet_class, MRB_TT_DATA);
  mrb_define_method(mrb, packet_class, "initialize",      packet_initialize,                     MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "append_data",     packet_append_data,                    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, packet_class, "clear",           packet_clear,                          MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "data_size",       packet_get_data_size,                  MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "end_of_packet?",  packet_end_of_packet,                  MRB_ARGS_NONE());

  mrb_define_method(mrb, packet_class, "read_bool",       abstract_packet_read<bool>,            MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "read_int8",       abstract_packet_read<sf::Int8>,        MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "read_int16",      abstract_packet_read<sf::Int16>,       MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "read_int32",      abstract_packet_read<sf::Int32>,       MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "read_int64",      abstract_packet_read<sf::Int64>,       MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "read_uint8",      abstract_packet_read<sf::Uint8>,       MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "read_uint16",     abstract_packet_read<sf::Uint16>,      MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "read_uint32",     abstract_packet_read<sf::Uint32>,      MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "read_uint64",     abstract_packet_read<sf::Uint64>,      MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "read_float",      abstract_packet_read<float>,           MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "read_double",     abstract_packet_read<double>,          MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "read_cstring",    abstract_packet_read<char*>,           MRB_ARGS_NONE());

  mrb_define_method(mrb, packet_class, "write_bool",      packet_write_bool,                     MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "write_int8",      abstract_packet_write_int<sf::Int8>,   MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "write_int16",     abstract_packet_write_int<sf::Int16>,  MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "write_int32",     abstract_packet_write_int<sf::Int32>,  MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "write_int64",     abstract_packet_write_int<sf::Int64>,  MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "write_uint8",     abstract_packet_write_int<sf::Uint8>,  MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "write_uint16",    abstract_packet_write_int<sf::Uint16>, MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "write_uint32",    abstract_packet_write_int<sf::Uint32>, MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "write_uint64",    abstract_packet_write_int<sf::Uint64>, MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "write_float",     abstract_packet_write_float<float>,    MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "write_double",    abstract_packet_write_float<double>,   MRB_ARGS_NONE());
  mrb_define_method(mrb, packet_class, "write_cstring",   packet_write_string,                   MRB_ARGS_NONE());
}
