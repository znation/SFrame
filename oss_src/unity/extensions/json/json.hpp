#include <unity/lib/variant.hpp>

#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>

// Wraps RapidJSON from https://github.com/miloyip/rapidjson
// and provides bidirectional serialization for flexible_type

namespace graphlab {
  namespace JSON {
    typedef rapidjson::Writer<rapidjson::OStreamWrapper> writer;

    // flexible_type <-> JSON std::string or std::ostream&
    // mirrors Python JSON API of `json` module.
    flex_string dumps(variant_type input);
    void dump(variant_type input, std::ostream& output);
    void dump(variant_type input, writer& output);

    variant_type loads(flex_string input);
    variant_type load(std::istream& input);
  }
}
