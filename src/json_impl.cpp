#include <fstream>
#include "json_impl.h"

#define utf8_to_ansi(x) x

JsonImpl::JsonImpl()
    : m_reader()
    , m_root_value()
    , m_child_values()
{

}

JsonImpl::~JsonImpl()
{

}

bool JsonImpl::into_element(size_t element_index)
{
    Json::Value & json_parent = (m_child_values.empty() ? m_root_value : *m_child_values.back());
    if (!json_parent.isArray() || element_index >= json_parent.size())
    {
        return(false);
    }
    Json::Value & json_child = json_parent[static_cast<Json::Value::ArrayIndex>(element_index)];
    m_child_values.push_back(&json_child);
    return(true);
}

bool JsonImpl::into_element(const char * element_name)
{
    if (nullptr == element_name)
    {
        return(false);
    }
    Json::Value & json_parent = (m_child_values.empty() ? m_root_value : *m_child_values.back());
    if (!json_parent.isMember(element_name))
    {
        return(false);
    }
    Json::Value & json_child = json_parent[element_name];
    m_child_values.push_back(&json_child);
    return(true);
}

bool JsonImpl::outof_element()
{
    if (m_child_values.empty())
    {
        return(false);
    }
    m_child_values.pop_back();
    return(true);
}

Stupid::Base::json_value_t::v_t JsonImpl::get_type()
{
    const Json::Value & json_value = (m_child_values.empty() ? m_root_value : *m_child_values.back());
    if (json_value.isArray())
    {
        return(Stupid::Base::json_value_t::json_array);
    }
    else if (json_value.isObject())
    {
        return(Stupid::Base::json_value_t::json_object);
    }
    else
    {
        return(Stupid::Base::json_value_t::json_scalar);
    }
}

size_t JsonImpl::get_size()
{
    const Json::Value & json_value = (m_child_values.empty() ? m_root_value : *m_child_values.back());
    if (json_value.isArray())
    {
        return(json_value.size());
    }
    return(0);
}

bool JsonImpl::load(const char * file_name)
{
    if (nullptr == file_name)
    {
        return(false);
    }
    const std::string filename = utf8_to_ansi(file_name);
    std::ifstream ifs(filename.c_str(), std::ios::binary);
    if (!ifs.is_open())
    {
        return(false);
    }
    m_root_value.clear();
    m_child_values.clear();
    return(m_reader.parse(ifs, m_root_value, false));
}

bool JsonImpl::set_document(const char * document)
{
    if (nullptr == document)
    {
        return(false);
    }
    m_root_value.clear();
    m_child_values.clear();
    return(m_reader.parse(document, m_root_value, false));
}

bool JsonImpl::find_element(const char * element_name)
{
    if (nullptr == element_name)
    {
        return(false);
    }
    const Json::Value & json_value = (m_child_values.empty() ? m_root_value : *m_child_values.back());
    return(json_value.isMember(element_name));
}

bool JsonImpl::get_element(const char * element_name, std::string & element_value)
{
    if (nullptr == element_name)
    {
        return(false);
    }
    const Json::Value & json_parent = (m_child_values.empty() ? m_root_value : *m_child_values.back());
    if (!json_parent.isMember(element_name))
    {
        return(false);
    }
    const Json::Value & json_child = json_parent[element_name];
    if (!json_child.isConvertibleTo(Json::stringValue))
    {
        return(false);
    }
    element_value = json_child.asString();
    return(true);
}

bool JsonImpl::get_element(const char * element_name, char * element_value, size_t element_value_size)
{
    std::string str_element_value;
    if (!get_element(element_name, str_element_value))
    {
        return(false);
    }
    if (nullptr == element_value || str_element_value.size() >= element_value_size)
    {
        return(false);
    }
    strncpy(element_value, str_element_value.c_str(), element_value_size);
    return(true);
}

bool JsonImpl::get_element(const char * element_name, std::list<std::string> & element_value_list)
{
    if (nullptr == element_name)
    {
        return(false);
    }
    const Json::Value & json_parent = (m_child_values.empty() ? m_root_value : *m_child_values.back());
    if (!json_parent.isMember(element_name))
    {
        return(false);
    }
    const Json::Value & json_child = json_parent[element_name];
    if (!json_child.isArray())
    {
        return(false);
    }
    for (size_t index = 0; index < json_child.size(); ++index)
    {
        const Json::Value & json_grand_child = json_child[static_cast<Json::Value::ArrayIndex>(index)];
        if (!json_grand_child.isConvertibleTo(Json::stringValue))
        {
            return(false);
        }
        element_value_list.push_back(json_grand_child.asString());
    }
    return(true);
}

bool JsonImpl::save(const char * file_name, bool format)
{
    if (nullptr == file_name)
    {
        return(false);
    }
    Json::FastWriter fast_writer;
    Json::StyledWriter styled_writer;
    const std::string document(format ? styled_writer.write(m_root_value) : fast_writer.write(m_root_value));
    const std::string filename = utf8_to_ansi(file_name);
    std::ofstream ofs(filename.c_str(), std::ios::binary | std::ios::trunc);
    if (!ofs.is_open())
    {
        return(false);
    }
    ofs.write(document.c_str(), document.size());
    ofs.close();
    return(true);
}

bool JsonImpl::add_element(size_t element_index)
{
    Json::Value & json_parent = (m_child_values.empty() ? m_root_value : *m_child_values.back());
    if (!json_parent.isNull() && !json_parent.isArray())
    {
        return(false);
    }
    if (element_index > json_parent.size())
    {
        return(false);
    }
    Json::Value & json_child = json_parent[static_cast<Json::Value::ArrayIndex>(element_index)];
    return(true);
}

bool JsonImpl::add_element(const char * element_name)
{
    if (nullptr == element_name)
    {
        return(false);
    }
    Json::Value & json_parent = (m_child_values.empty() ? m_root_value : *m_child_values.back());
    Json::Value & json_child = json_parent[element_name];
    return(true);
}

bool JsonImpl::add_element(const char * element_name, const char * element_value)
{
    if (nullptr == element_name || nullptr == element_value)
    {
        return(false);
    }
    Json::Value & json_parent = (m_child_values.empty() ? m_root_value : *m_child_values.back());
    Json::Value & json_child = json_parent[element_name];
    json_child = element_value;
    return(true);
}

bool JsonImpl::add_element(const char * element_name, const std::string & element_value)
{
    return(add_element(element_name, element_value.c_str()));
}

bool JsonImpl::add_element(const char * element_name, const std::list<std::string> & element_value_list)
{
    if (nullptr == element_name)
    {
        return(false);
    }
    Json::Value & json_parent = (m_child_values.empty() ? m_root_value : *m_child_values.back());
    Json::Value & json_child = json_parent[element_name];
    for (std::list<std::string>::const_iterator iter = element_value_list.begin(); element_value_list.end() != iter; ++iter)
    {
        json_child.append(*iter);
    }
    return(true);
}

bool JsonImpl::set_element(const char * element_name, const char * element_value)
{
    if (nullptr == element_name || nullptr == element_value)
    {
        return(false);
    }
    Json::Value & json_parent = (m_child_values.empty() ? m_root_value : *m_child_values.back());
    Json::Value & json_child = json_parent[element_name];
    json_child = element_value;
    return(true);
}

bool JsonImpl::set_element(const char * element_name, const std::string & element_value)
{
    return(set_element(element_name, element_value.c_str()));
}

bool JsonImpl::set_element(const char * element_name, const std::list<std::string> & element_value_list)
{
    if (nullptr == element_name)
    {
        return(false);
    }
    Json::Value & json_parent = (m_child_values.empty() ? m_root_value : *m_child_values.back());
    Json::Value & json_child = json_parent[element_name];
    json_child.clear();
    for (std::list<std::string>::const_iterator iter = element_value_list.begin(); element_value_list.end() != iter; ++iter)
    {
        json_child.append(*iter);
    }
    return(true);
}

bool JsonImpl::remove_element(size_t element_index)
{
    Json::Value & json_parent = (m_child_values.empty() ? m_root_value : *m_child_values.back());
    if (!json_parent.isArray() || element_index >= json_parent.size())
    {
        return(false);
    }
    Json::Value json_child;
    return(json_parent.removeIndex(static_cast<Json::Value::ArrayIndex>(element_index), &json_child));
}

bool JsonImpl::remove_element(const char * element_name)
{
    if (nullptr == element_name)
    {
        return(false);
    }
    Json::Value & json_parent = (m_child_values.empty() ? m_root_value : *m_child_values.back());
    if (!json_parent.isMember(element_name))
    {
        return(false);
    }
    Json::Value json_child;
    return(json_parent.removeMember(element_name, &json_child));
}

bool JsonImpl::get_element(const char * element_name, bool & element_value)
{
    return(do_get_element(element_name, element_value));
}

bool JsonImpl::get_element(const char * element_name, int8_t & element_value)
{
    return(do_get_element(element_name, element_value));
}

bool JsonImpl::get_element(const char * element_name, uint8_t & element_value)
{
    return(do_get_element(element_name, element_value));
}

bool JsonImpl::get_element(const char * element_name, int16_t & element_value)
{
    return(do_get_element(element_name, element_value));
}

bool JsonImpl::get_element(const char * element_name, uint16_t & element_value)
{
    return(do_get_element(element_name, element_value));
}

bool JsonImpl::get_element(const char * element_name, int32_t & element_value)
{
    return(do_get_element(element_name, element_value));
}

bool JsonImpl::get_element(const char * element_name, uint32_t & element_value)
{
    return(do_get_element(element_name, element_value));
}

bool JsonImpl::get_element(const char * element_name, int64_t & element_value)
{
    return(do_get_element(element_name, element_value));
}

bool JsonImpl::get_element(const char * element_name, uint64_t & element_value)
{
    return(do_get_element(element_name, element_value));
}

bool JsonImpl::get_element(const char * element_name, float & element_value)
{
    return(do_get_element(element_name, element_value));
}

bool JsonImpl::get_element(const char * element_name, double & element_value)
{
    return(do_get_element(element_name, element_value));
}

bool JsonImpl::get_element(const char * element_name, std::list<bool> & element_value_list)
{
    return(do_get_element(element_name, element_value_list));
}

bool JsonImpl::get_element(const char * element_name, std::list<int8_t> & element_value_list)
{
    return(do_get_element(element_name, element_value_list));
}

bool JsonImpl::get_element(const char * element_name, std::list<uint8_t> & element_value_list)
{
    return(do_get_element(element_name, element_value_list));
}

bool JsonImpl::get_element(const char * element_name, std::list<int16_t> & element_value_list)
{
    return(do_get_element(element_name, element_value_list));
}

bool JsonImpl::get_element(const char * element_name, std::list<uint16_t> & element_value_list)
{
    return(do_get_element(element_name, element_value_list));
}

bool JsonImpl::get_element(const char * element_name, std::list<int32_t> & element_value_list)
{
    return(do_get_element(element_name, element_value_list));
}

bool JsonImpl::get_element(const char * element_name, std::list<uint32_t> & element_value_list)
{
    return(do_get_element(element_name, element_value_list));
}

bool JsonImpl::get_element(const char * element_name, std::list<int64_t> & element_value_list)
{
    return(do_get_element(element_name, element_value_list));
}

bool JsonImpl::get_element(const char * element_name, std::list<uint64_t> & element_value_list)
{
    return(do_get_element(element_name, element_value_list));
}

bool JsonImpl::get_element(const char * element_name, std::list<float> & element_value_list)
{
    return(do_get_element(element_name, element_value_list));
}

bool JsonImpl::get_element(const char * element_name, std::list<double> & element_value_list)
{
    return(do_get_element(element_name, element_value_list));
}

bool JsonImpl::add_element(const char * element_name, bool element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && add_element(element_name, str_element_value));
    }
    else
    {
        return(do_add_element(element_name, element_value));
    }
}

bool JsonImpl::add_element(const char * element_name, int8_t element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && add_element(element_name, str_element_value));
    }
    else
    {
        return(do_add_element(element_name, element_value));
    }
}

bool JsonImpl::add_element(const char * element_name, uint8_t element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && add_element(element_name, str_element_value));
    }
    else
    {
        return(do_add_element(element_name, element_value));
    }
}

bool JsonImpl::add_element(const char * element_name, int16_t element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && add_element(element_name, str_element_value));
    }
    else
    {
        return(do_add_element(element_name, element_value));
    }
}

bool JsonImpl::add_element(const char * element_name, uint16_t element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && add_element(element_name, str_element_value));
    }
    else
    {
        return(do_add_element(element_name, element_value));
    }
}

bool JsonImpl::add_element(const char * element_name, int32_t element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && add_element(element_name, str_element_value));
    }
    else
    {
        return(do_add_element(element_name, element_value));
    }
}

bool JsonImpl::add_element(const char * element_name, uint32_t element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && add_element(element_name, str_element_value));
    }
    else
    {
        return(do_add_element(element_name, element_value));
    }
}

bool JsonImpl::add_element(const char * element_name, int64_t element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && add_element(element_name, str_element_value));
    }
    else
    {
        return(do_add_element(element_name, element_value));
    }
}

bool JsonImpl::add_element(const char * element_name, uint64_t element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && add_element(element_name, str_element_value));
    }
    else
    {
        return(do_add_element(element_name, element_value));
    }
}

bool JsonImpl::add_element(const char * element_name, float element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && add_element(element_name, str_element_value));
    }
    else
    {
        return(do_add_element(element_name, element_value));
    }
}

bool JsonImpl::add_element(const char * element_name, double element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && add_element(element_name, str_element_value));
    }
    else
    {
        return(do_add_element(element_name, element_value));
    }
}

bool JsonImpl::add_element(const char * element_name, const std::list<bool> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && add_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_add_element(element_name, element_value_list));
    }
}

bool JsonImpl::add_element(const char * element_name, const std::list<int8_t> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && add_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_add_element(element_name, element_value_list));
    }
}

bool JsonImpl::add_element(const char * element_name, const std::list<uint8_t> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && add_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_add_element(element_name, element_value_list));
    }
}

bool JsonImpl::add_element(const char * element_name, const std::list<int16_t> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && add_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_add_element(element_name, element_value_list));
    }
}

bool JsonImpl::add_element(const char * element_name, const std::list<uint16_t> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && add_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_add_element(element_name, element_value_list));
    }
}

bool JsonImpl::add_element(const char * element_name, const std::list<int32_t> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && add_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_add_element(element_name, element_value_list));
    }
}

bool JsonImpl::add_element(const char * element_name, const std::list<uint32_t> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && add_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_add_element(element_name, element_value_list));
    }
}

bool JsonImpl::add_element(const char * element_name, const std::list<int64_t> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && add_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_add_element(element_name, element_value_list));
    }
}

bool JsonImpl::add_element(const char * element_name, const std::list<uint64_t> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && add_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_add_element(element_name, element_value_list));
    }
}

bool JsonImpl::add_element(const char * element_name, const std::list<float> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && add_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_add_element(element_name, element_value_list));
    }
}

bool JsonImpl::add_element(const char * element_name, const std::list<double> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && add_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_add_element(element_name, element_value_list));
    }
}

bool JsonImpl::set_element(const char * element_name, bool element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && set_element(element_name, str_element_value));
    }
    else
    {
        return(do_set_element(element_name, element_value));
    }
}

bool JsonImpl::set_element(const char * element_name, int8_t element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && set_element(element_name, str_element_value));
    }
    else
    {
        return(do_set_element(element_name, element_value));
    }
}

bool JsonImpl::set_element(const char * element_name, uint8_t element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && set_element(element_name, str_element_value));
    }
    else
    {
        return(do_set_element(element_name, element_value));
    }
}

bool JsonImpl::set_element(const char * element_name, int16_t element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && set_element(element_name, str_element_value));
    }
    else
    {
        return(do_set_element(element_name, element_value));
    }
}

bool JsonImpl::set_element(const char * element_name, uint16_t element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && set_element(element_name, str_element_value));
    }
    else
    {
        return(do_set_element(element_name, element_value));
    }
}

bool JsonImpl::set_element(const char * element_name, int32_t element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && set_element(element_name, str_element_value));
    }
    else
    {
        return(do_set_element(element_name, element_value));
    }
}

bool JsonImpl::set_element(const char * element_name, uint32_t element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && set_element(element_name, str_element_value));
    }
    else
    {
        return(do_set_element(element_name, element_value));
    }
}

bool JsonImpl::set_element(const char * element_name, int64_t element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && set_element(element_name, str_element_value));
    }
    else
    {
        return(do_set_element(element_name, element_value));
    }
}

bool JsonImpl::set_element(const char * element_name, uint64_t element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && set_element(element_name, str_element_value));
    }
    else
    {
        return(do_set_element(element_name, element_value));
    }
}

bool JsonImpl::set_element(const char * element_name, float element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && set_element(element_name, str_element_value));
    }
    else
    {
        return(do_set_element(element_name, element_value));
    }
}

bool JsonImpl::set_element(const char * element_name, double element_value, bool as_string)
{
    if (as_string)
    {
        std::string str_element_value;
        return(stupid_type_to_string(element_value, str_element_value) && set_element(element_name, str_element_value));
    }
    else
    {
        return(do_set_element(element_name, element_value));
    }
}

bool JsonImpl::set_element(const char * element_name, const std::list<bool> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && set_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_set_element(element_name, element_value_list));
    }
}

bool JsonImpl::set_element(const char * element_name, const std::list<int8_t> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && set_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_set_element(element_name, element_value_list));
    }
}

bool JsonImpl::set_element(const char * element_name, const std::list<uint8_t> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && set_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_set_element(element_name, element_value_list));
    }
}

bool JsonImpl::set_element(const char * element_name, const std::list<int16_t> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && set_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_set_element(element_name, element_value_list));
    }
}

bool JsonImpl::set_element(const char * element_name, const std::list<uint16_t> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && set_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_set_element(element_name, element_value_list));
    }
}

bool JsonImpl::set_element(const char * element_name, const std::list<int32_t> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && set_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_set_element(element_name, element_value_list));
    }
}

bool JsonImpl::set_element(const char * element_name, const std::list<uint32_t> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && set_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_set_element(element_name, element_value_list));
    }
}

bool JsonImpl::set_element(const char * element_name, const std::list<int64_t> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && set_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_set_element(element_name, element_value_list));
    }
}

bool JsonImpl::set_element(const char * element_name, const std::list<uint64_t> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && set_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_set_element(element_name, element_value_list));
    }
}

bool JsonImpl::set_element(const char * element_name, const std::list<float> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && set_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_set_element(element_name, element_value_list));
    }
}

bool JsonImpl::set_element(const char * element_name, const std::list<double> & element_value_list, bool as_string)
{
    if (as_string)
    {
        std::list<std::string> str_element_value_list;
        return(stupid_type_to_string(element_value_list, str_element_value_list) && set_element(element_name, str_element_value_list));
    }
    else
    {
        return(do_set_element(element_name, element_value_list));
    }
}
