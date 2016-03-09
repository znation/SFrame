#include <flexible_type/flexible_type.hpp>
#include <unity/lib/gl_sarray.hpp>

// Wraps RapidJSON from https://github.com/miloyip/rapidjson
// and provides bidirectional serialization for flexible_type

namespace graphlab {
  namespace JSON {
    // flexible_type <-> JSON std::string or std::ostream&
    // mirrors Python JSON API of `json` module.
    void dump(gl_sarray input, std::ostream& output);

    gl_sarray loads_sarray(gl_sarray input);
    gl_sarray load_sarray(std::istream& input);
  }
}
