#include <flexible_type/flexible_type.hpp>

// Wraps RapidJSON from https://github.com/miloyip/rapidjson
// and provides bidirectional serialization for flexible_type

namespace graphlab {
  namespace JSON {
    // flexible_type <-> JSON std::string or std::ostream&
    // mirrors Python JSON API of `json` module.
    void dump(flexible_type input, std::ostream& output);

    flexible_type loads_flex_type(flex_string input);
    flexible_type load_flex_type(std::istream& input);
  }
}
