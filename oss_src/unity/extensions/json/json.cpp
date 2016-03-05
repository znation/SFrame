#include "json_flexible_type.hpp"

#include <unity/lib/toolkit_function_macros.hpp>
#include <unity/lib/toolkit_class_macros.hpp>

using namespace graphlab;

BEGIN_FUNCTION_REGISTRATION;
REGISTER_NAMED_FUNCTION("json.dumps", JSON::dumps, "input");
END_FUNCTION_REGISTRATION;
