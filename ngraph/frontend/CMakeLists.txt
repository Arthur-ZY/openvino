# Copyright (C) 2018-2021 Intel Corporation
# SPDX-License-Identifier: Apache-2.0
#

set(FRONTEND_INSTALL_INCLUDE "runtime/include/ngraph/frontend")

add_subdirectory(frontend_manager)

if (NGRAPH_ONNX_FRONTEND_ENABLE)
    add_subdirectory(onnx)
endif()

if (NGRAPH_PDPD_FRONTEND_ENABLE)
    add_subdirectory(paddlepaddle)
endif()

if (NGRAPH_IR_FRONTEND_ENABLE)
    add_subdirectory(ir)
endif()

if (NGRAPH_TF_FRONTEND_ENABLE)
    add_subdirectory(tensorflow)
endif()
