'''
Copyright (C) 2016 Dato, Inc.
All rights reserved.

This software may be modified and distributed under the terms
of the BSD license. See the LICENSE file for details.
'''

import array
import datetime
import math
import pytz
import sframe
import unittest

class JSONTest(unittest.TestCase):
    def _run_test_case(self, value):
        # test that JSON serialization is invertible with respect to both
        # value and type.
        json = sframe.extensions.json.dumps(value)
        self.assertEquals(type(sframe.extensions.json.loads(json)), type(value))
        self.assertEquals(sframe.extensions.json.loads(json), value)

    def test_int(self):
        [self._run_test_case(value) for value in [
            0,
            1,
            -2147483650,
            -2147483649, # boundary of accurate representation in JS 64-bit float
            2147483648, # boundary of accurate representation in JS 64-bit float
            2147483649
        ]]

    def test_float(self):
        [self._run_test_case(value) for value in [
            -1.1,
            -1.0,
            0.0,
            1.0,
            1.1,
            float('-inf'),
            float('inf')
        ]]
        self.assertTrue(
            math.isnan(
                sframe.extensions.json.loads(
                    sframe.extensions.json.dumps(float('nan')))))

    def test_string_to_json(self):
        # TODO znation - test non-ascii, non-utf-8 charsets. test null byte inside string.
        [self._run_test_case(value) for value in [
            "hello",
            "a'b",
            "a\"b"
        ]]

    def test_vec_to_json(self):
        [self._run_test_case(value) for value in [
            array.array('d'),
            array.array('d', [1.5]),
            array.array('d', [2.1,2.5,3.1])
        ]]

    def test_list_to_json(self):
        [self._run_test_case(value) for value in [
            [],
            ["hello", "world"],
            ["hello", 3, None]
        ]]
        # TODO -- can't test just numbers, due to (Python <-> flexible_type)
        # not being reversible for lists of numbers.
        # if `list` of `int` goes into C++, the flexible_type representation
        # becomes flex_vec (vector<flex_float>). This is a lossy representation.
        # known issue, can't resolve here.

    def test_dict_to_json(self):
        [self._run_test_case(value) for value in [
            {},
            {
                "x": 1,
                "y": 2
            }
        ]]

    def test_date_time_to_json(self):
        d = datetime.datetime(year=2016, month=3, day=5)
        [self._run_test_case(value) for value in [
            d,
            pytz.utc.localize(d),
            pytz.timezone('US/Arizona').localize(d)
        ]]

    def test_image_to_json(self):
        # TODO znation test image
        pass
