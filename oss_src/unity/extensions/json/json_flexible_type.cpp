#include "json_flexible_type.hpp"

#include <rapidjson/writer.h>
#include <rapidjson/ostreamwrapper.h>

#include <stdexcept>

using namespace graphlab;

// TODO znation -- use JSON schema as described in http://rapidjson.org/md_doc_schema.html

typedef rapidjson::Writer<rapidjson::OStreamWrapper> json_writer;
void _dump(flexible_type input, json_writer& output); // defined below

flex_string JSON::dumps(flexible_type input) {
  std::stringstream output;
  JSON::dump(input, output);
  return output.str();
}

void _dump_int(flex_int input, json_writer& output) {
  // we can write integers of any size -- they turn into 64-bit float in JS,
  // but the serialization format doesn't specify a max int value.
  // see http://stackoverflow.com/questions/13502398/json-integers-limit-on-size
  output.Int64(input);
}

void _dump_float(flex_float input, json_writer& output) {
  // Float values (like 0.0 or -234.56) are allowed in JSON,
  // but not inf, -inf, or nan. Have to adjust for those.
  if (std::isnan(input)) {
    output.String("NaN");
  } else if (std::isinf(input)) {
    if (input > 0) {
      output.String("Infinity");
    } else {
      output.String("-Infinity");
    }
  } else {
    // finite float value, can output as is.
    output.Double(input);
  }
}

void _dump_string(flex_string input, json_writer& output) {
  output.String(input.c_str());
}

template<typename T>
static void _dump(std::vector<T> input, json_writer& output) {
  output.StartArray();
  for (const T& element : input) {
    _dump(element, output);
  }
  output.EndArray();
}

void _dump_vector(flex_vec input, json_writer& output) {
  _dump<flex_float>(input, output);
}

void _dump_list(flex_list input, json_writer& output) {
  _dump<flexible_type>(input, output);
}

void _dump_dict(flex_dict input, json_writer& output) {
  output.StartObject();
  for (const auto& kv : input) {
    const flex_string& key = kv.first;
    const flexible_type& value = kv.second;
    output.Key(key.c_str());
    _dump(value, output);
  }
  output.EndObject();
}

void _dump_date_time(flex_date_time input, json_writer& output) {
  int32_t time_zone_offset = input.time_zone_offset();
  _dump<flexible_type>(std::vector<flexible_type>({
    input.posix_timestamp(),
    time_zone_offset == 64 ? FLEX_UNDEFINED : flexible_type(flex_int(time_zone_offset)),
    input.microsecond()
  }), output);
}

void _dump_image(flex_image input, json_writer& output) {
  // TODO znation: write this function
}

void _dump(flexible_type input, json_writer& output) {
  switch (input.get_type()) {
    case flex_type_enum::INTEGER:
      _dump_int(input.get<flex_int>(), output);
      break;
    case flex_type_enum::FLOAT:
      _dump_float(input.get<flex_float>(), output);
      break;
    case flex_type_enum::STRING:
      _dump_string(input.get<flex_string>(), output);
      break;
    case flex_type_enum::VECTOR:
      _dump_vector(input.get<flex_vec>(), output);
      break;
    case flex_type_enum::LIST:
      _dump_list(input.get<flex_list>(), output);
      break;
    case flex_type_enum::DICT:
      _dump_dict(input.get<flex_dict>(), output);
      break;
    case flex_type_enum::DATETIME:
      _dump_date_time(input.get<flex_date_time>(), output);
      break;
    case flex_type_enum::IMAGE:
      _dump_image(input.get<flex_image>(), output);
      break;
    case flex_type_enum::UNDEFINED:
      output.Null();
      break;
  }
}

void JSON::dump(flexible_type input, std::ostream& output) {
  rapidjson::OStreamWrapper wrapper(output);
  json_writer writer(wrapper);
  _dump(input, writer);
}
