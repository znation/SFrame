#include "../flexible_type/flexible_type.hpp"

// Wraps RapidJSON from https://github.com/miloyip/rapidjson
// and provides bidirectional serialization for flexible_type

namespace graphlab {
  namespace JSON {
    // flexible_type <-> JSON std::string or std::ostream&
    // mirrors Python JSON API of `json` module.
    std::string dumps(flexible_type input);
    void dump(flexible_type input, std::ostream& out);
  }
}
