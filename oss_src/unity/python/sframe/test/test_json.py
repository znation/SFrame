'''
Copyright (C) 2016 Dato, Inc.
All rights reserved.

This software may be modified and distributed under the terms
of the BSD license. See the LICENSE file for details.
'''

import array
import datetime
import pytz
import sframe
import unittest

dumps = sframe.extensions.json.dumps

class JSONTest(unittest.TestCase):
    def test_int(self):
      self.assertEquals(dumps(-2147483649), "-2147483649")
      self.assertEquals(dumps(2147483648), "2147483648")

    def test_float(self):
      self.assertEquals(dumps(float('nan')), "\"NaN\"");
      self.assertEquals(dumps(float('-inf')), "\"-Infinity\"");
      self.assertEquals(dumps(-1.1), "-1.1");
      self.assertEquals(dumps(-1.0), "-1.0");
      self.assertEquals(dumps(0.0), "0.0");
      self.assertEquals(dumps(1.0), "1.0");
      self.assertEquals(dumps(1.1), "1.1");
      self.assertEquals(dumps(float('inf')), "\"Infinity\"");

    def test_string_to_json(self):
      self.assertEquals(dumps("hello"), "\"hello\"");
      self.assertEquals(dumps("a'b"), "\"a'b\"");
      self.assertEquals(dumps("a\"b"), "\"a\\\"b\"");
      # TODO znation - test non-ascii, non-utf-8 charsets. test null byte inside string.

    def test_vec_to_json(self):
      self.assertEquals(dumps(array.array('d')), "[]");
      self.assertEquals(dumps(array.array('d', [1.5])), "[1.5]");
      self.assertEquals(dumps(array.array('d', [2.1,2.5,3.1])), "[2.1,2.5,3.1]");

    def test_list_to_json(self):
      self.assertEquals(dumps([]), "[]");
      self.assertEquals(dumps([1,2]), "[1.0,2.0]"); # TODO should these stay int?
      self.assertEquals(dumps(["hello", 3, None]), "[\"hello\",3,null]");

    def test_dict_to_json(self):
      self.assertEquals(dumps({}), "{}");
      self.assertEquals(dumps({
        "x": 1,
        "y": 2
      }), "{\"y\":2,\"x\":1}");

    def test_date_time_to_json(self):
      d = datetime.datetime(year=2016, month=3, day=5)
      self.assertEquals(dumps(d), "[1457136000,null,0]");
      d2 = pytz.utc.localize(d)
      self.assertEquals(dumps(d2), "[1457136000,0,0]");
      d3 = pytz.timezone('US/Arizona').localize(d)
      self.assertEquals(dumps(d3), "[1457161200,-28,0]");

    def test_image_to_json(self):
      # TODO znation test image
      pass
