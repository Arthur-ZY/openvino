// Copyright (C) 2018-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "openvino/core/attribute_visitor.hpp"
#include "openvino/core/function.hpp"
#include "openvino/core/node.hpp"
#include "openvino/op/util/variable.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace util
{
    class DictAttributeDeserializer : public ov::AttributeVisitor
    {
    public:
        DictAttributeDeserializer(
            const py::dict& attributes,
            std::unordered_map<std::string, std::shared_ptr<ov::op::util::Variable>>& variables);

        void on_adapter(const std::string& name, ov::ValueAccessor<void>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<bool>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::string>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<int8_t>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<int16_t>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<int32_t>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<int64_t>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<uint8_t>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<uint16_t>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<uint32_t>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<uint64_t>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<float>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<double>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<std::string>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<int8_t>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<int16_t>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<int32_t>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<int64_t>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<uint8_t>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<uint16_t>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<uint32_t>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<uint64_t>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<float>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<double>>& adapter) override;

        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::shared_ptr<ov::Function>>& adapter) override;

    protected:
        const py::dict& m_attributes;
        std::unordered_map<std::string, std::shared_ptr<ov::op::util::Variable>>& m_variables;
    };

    class DictAttributeSerializer : public ov::AttributeVisitor
    {
    public:
        explicit DictAttributeSerializer(const std::shared_ptr<ov::Node>& node);

        void on_adapter(const std::string& name, ov::ValueAccessor<void>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<bool>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::string>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<int8_t>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<int16_t>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<int32_t>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<int64_t>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<uint8_t>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<uint16_t>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<uint32_t>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<uint64_t>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<float>& adapter) override;
        void on_adapter(const std::string& name, ov::ValueAccessor<double>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<std::string>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<int8_t>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<int16_t>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<int32_t>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<int64_t>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<uint8_t>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<uint16_t>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<uint32_t>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<uint64_t>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<float>>& adapter) override;
        void on_adapter(const std::string& name,
                        ov::ValueAccessor<std::vector<double>>& adapter) override;

        template <typename T>
        T get_attribute(const std::string& name)
        {
            NGRAPH_CHECK(m_attributes.contains(name),
                         "Couldn't find attribute \"",
                         name,
                         "\" in serialized node attribute dictionary.");
            return m_attributes[name.c_str()].cast<T>();
        }

        py::dict get_attributes() const { return m_attributes; }

    protected:
        py::dict m_attributes;
    };
} // namespace util
