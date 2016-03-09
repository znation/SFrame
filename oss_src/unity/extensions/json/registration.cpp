#include "json.hpp"

#include <unity/lib/toolkit_function_macros.hpp>
#include <unity/lib/toolkit_class_macros.hpp>

#include <iostream>

using namespace graphlab;

BEGIN_FUNCTION_REGISTRATION;
REGISTER_NAMED_FUNCTION("json.dumps", JSON::dumps, "input");
REGISTER_NAMED_FUNCTION("json.loads", JSON::loads, "input");
END_FUNCTION_REGISTRATION;
