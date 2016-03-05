/*
 * Copyright (c) 2016 Dato, Inc.
 *     All rights reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing,
 *  software distributed under the License is distributed on an "AS
 *  IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 *  express or implied.  See the License for the specific language
 *  governing permissions and limitations under the License.
 *
 * For more about this software visit:
 *
 *      https://dato.com
 *
 */

#include <cxxtest/TestSuite.h>
#include "../../oss_src/json/json.hpp"

using namespace graphlab;

class flexible_type_test : public CxxTest::TestSuite {
  public:
    void test_int_to_json() {
      TS_ASSERT_EQUALS(JSON::dumps(-2147483649), "-2147483649");
      TS_ASSERT_EQUALS(JSON::dumps(2147483648), "2147483648");
    }

    void test_float_to_json() {
      TS_ASSERT_EQUALS(JSON::dumps(std::numeric_limits<flex_float>::quiet_NaN()), "\"NaN\"");
      TS_ASSERT_EQUALS(JSON::dumps(-std::numeric_limits<flex_float>::infinity()), "\"-Infinity\"");
      TS_ASSERT_EQUALS(JSON::dumps(-1.1), "-1.1");
      TS_ASSERT_EQUALS(JSON::dumps(-1.0), "-1.0");
      TS_ASSERT_EQUALS(JSON::dumps(0.0), "0.0");
      TS_ASSERT_EQUALS(JSON::dumps(1.0), "1.0");
      TS_ASSERT_EQUALS(JSON::dumps(1.1), "1.1");
      TS_ASSERT_EQUALS(JSON::dumps(std::numeric_limits<flex_float>::infinity()), "\"Infinity\"");
    }

    void test_string_to_json() {
      TS_ASSERT_EQUALS(JSON::dumps("hello"), "\"hello\"");
      TS_ASSERT_EQUALS(JSON::dumps("a'b"), "\"a'b\"");
      TS_ASSERT_EQUALS(JSON::dumps("a\"b"), "\"a\\\"b\"");
      // TODO znation - test non-ascii, non-utf-8 charsets. test null byte inside string.
    }

    void test_vec_to_json() {
      TS_ASSERT_EQUALS(JSON::dumps(flex_vec()), "[]");
      TS_ASSERT_EQUALS(JSON::dumps(flex_vec({1.5})), "[1.5]");
      TS_ASSERT_EQUALS(JSON::dumps(flex_vec({2.1,2.5,3.1})), "[2.1,2.5,3.1]");
    }

    void test_list_to_json() {
      TS_ASSERT_EQUALS(JSON::dumps(flex_list()), "[]");
      TS_ASSERT_EQUALS(JSON::dumps(flex_list({1,2})), "[1,2]");
      TS_ASSERT_EQUALS(JSON::dumps(flex_list({"hello", 3, FLEX_UNDEFINED})), "[\"hello\",3,null]");
    }

    void test_dict_to_json() {
      TS_ASSERT_EQUALS(JSON::dumps(flex_dict()), "{}");
      TS_ASSERT_EQUALS(JSON::dumps(flex_dict({
        {"x", 1},
        {"y", 2}
      })), "{\"x\":1,\"y\":2}");
    }

    void test_date_time_to_json() {
      TS_ASSERT_EQUALS(JSON::dumps(flex_date_time()), "[0,null,0]");
      TS_ASSERT_EQUALS(JSON::dumps(flex_date_time(1,2,3)), "[1,2,3]");
    }

    void test_image_to_json() {
      char image_data[] = "abcd";
      flex_image image(image_data, 640, 480, 2, 4, 0, 1);
      // TODO znation test image
    }
};
