#include "json.hpp"
#include "json_flexible_type.hpp"
#include "json_sarray.hpp"

using namespace graphlab;

flex_string JSON::dumps(variant_type input) {
  std::stringstream output;
  JSON::dump(input, output);
  return output.str();
}

void JSON::dump(variant_type input, std::ostream& output) {
  rapidjson::OStreamWrapper wrapper(output);
  JSON::writer writer(wrapper);
  JSON::dump(input, writer);
}

class dump_visitor : public boost::static_visitor<void> {
  private:
    JSON::writer& m_output;

  public:
    dump_visitor(output) : m_output(output) {}

    void operator()(const flexible_type& value) {
      JSON::dump(boost::get<flexible_type>(input), m_output);
    }
    void operator()(const std::shared_ptr<unity_sgraph_base>& value) {
      throw "not implemented";
    }
    void operator()(const dataframe_t& value) {
      throw "not implemented";
    }
    void operator()(const std::shared_ptr<model_base>& value) {
      throw "not implemented";
    }
    void operator()(const std::shared_ptr<unity_sframe_base>& value) {
      throw "not implemented";
    }
    void operator()(const std::shared_ptr<unity_sarray_base>& value) {
      throw "not implemented";
    }
    void operator()(const std::map<std::string, boot::recursive_variant_>& value) {
      throw "not implemented";
    }
    void operator()(const std::vector<boot::recursive_variant_>& value) {
      throw "not implemented";
    }
    void operator()(const std::vector<boot::recursive_variant_>& value) {
      throw "not implemented";
    }
}

void JSON::dump(variant_type input, JSON::writer& output) {
  boost::apply_visitor(dump_visitor(output), input);
  /*
  switch (input.which()) {
    case 0:
      JSON::dump(boost::get<flexible_type>(input), output);
      return;
    case 5:
      JSON::dump(boost::get<gl_sarray>(input), output);
      return;
    default:
      throw "Unexpected type of input to JSON::dump(s). Expected either an SFrame, SArray, or flexible_type (one of: Python int, float, str, list, dict, array.array, datetime.datetime, or Image).";
  }
  */
}

variant_type JSON::loads(flex_string input) {
  return JSON::loads_flex_type(input);
}

variant_type JSON::load(std::istream& input) {
  return JSON::load_flex_type(input);
}
