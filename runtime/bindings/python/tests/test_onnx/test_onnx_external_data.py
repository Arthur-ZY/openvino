# Copyright (C) 2018-2021 Intel Corporation
# SPDX-License-Identifier: Apache-2.0

import os

import numpy as np
from openvino import Core

from tests.runtime import get_runtime


def test_import_onnx_with_external_data():
    model_path = os.path.join(os.path.dirname(__file__), "models/external_data.onnx")
    ie = Core()
    network = ie.read_network(model=model_path)

    ng_function = network.get_function()

    dtype = np.float32
    value_a = np.array([1.0, 3.0, 5.0], dtype=dtype)
    value_b = np.array([3.0, 5.0, 1.0], dtype=dtype)
    # third input [5.0, 1.0, 3.0] read from external file

    runtime = get_runtime()
    computation = runtime.computation(ng_function)
    result = computation(value_a, value_b)
    assert np.allclose(result, np.array([3.0, 3.0, 3.0], dtype=dtype))
