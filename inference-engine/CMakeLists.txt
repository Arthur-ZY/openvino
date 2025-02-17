# Copyright (C) 2018-2021 Intel Corporation
# SPDX-License-Identifier: Apache-2.0
#

project(InferenceEngine)

add_subdirectory(thirdparty)
add_subdirectory(src)
add_subdirectory(ie_bridges/c)

if(ENABLE_PYTHON)
    add_subdirectory(ie_bridges/python)
endif()

add_subdirectory(samples)

# TODO: remove this
foreach(sample benchmark_app classification_sample_async hello_classification
                hello_nv12_input_classification hello_query_device hello_reshape_ssd
                ngraph_function_creation_sample object_detection_sample_ssd
                speech_sample style_transfer_sample)
    if(TARGET ${sample})
        install(TARGETS ${sample}
                RUNTIME DESTINATION tests COMPONENT tests EXCLUDE_FROM_ALL)
    endif()
endforeach()

if(TARGET format_reader)
    install(TARGETS format_reader
            RUNTIME DESTINATION ${IE_CPACK_RUNTIME_PATH} COMPONENT tests EXCLUDE_FROM_ALL
            LIBRARY DESTINATION ${IE_CPACK_LIBRARY_PATH} COMPONENT tests EXCLUDE_FROM_ALL)
endif()

openvino_developer_export_targets(COMPONENT openvino_common TARGETS format_reader ie_samples_utils)

if(ENABLE_TESTS)
    add_subdirectory(tests_deprecated)
    add_subdirectory(tests)
endif()

#
# Install
#

# install C++ samples

ie_cpack_add_component(cpp_samples DEPENDS cpp_samples_deps core)

if(UNIX)
    install(DIRECTORY samples/
            DESTINATION samples/cpp
            COMPONENT cpp_samples
            USE_SOURCE_PERMISSIONS
            PATTERN *.bat EXCLUDE
            PATTERN speech_libs_and_demos EXCLUDE
            PATTERN .clang-format EXCLUDE)
elseif(WIN32)
    install(DIRECTORY samples/
            DESTINATION samples/cpp
            COMPONENT cpp_samples
            USE_SOURCE_PERMISSIONS
            PATTERN *.sh EXCLUDE
            PATTERN speech_libs_and_demos EXCLUDE
            PATTERN .clang-format EXCLUDE)
endif()

