#ifndef JSON_IMPL_H
#define JSON_IMPL_H


#include <list>
#include <string>
#include "json/json.h"
#include "json.h"

#include <sstream>

template <typename T>
bool stupid_string_to_type(const std::string & str, T & val)
{
    std::istringstream iss(str);
    iss.setf(std::ios::boolalpha);
    iss >> val;
    return(!iss.fail());
}

template <typename T>
bool stupid_string_to_type(const std::string & str, T * val);

template <typename T>
bool stupid_type_to_string(T val, std::string & str)
{
    std::ostringstream oss;
    oss.setf(std::ios::fixed, std::ios::floatfield);
    oss.setf(std::ios::boolalpha);
    oss << val;
    str = oss.str();
    return(true);
}

template <typename T>
bool stupid_type_to_string(T * val, std::string & str);

template <typename T>
bool stupid_string_to_type(const std::list<std::string> & str_list, std::list<T> & val_list)
{
    bool ret = true;
    for (std::list<std::string>::const_iterator iter = str_list.begin(); str_list.end() != iter; ++iter)
    {
        T val;
        if (stupid_string_to_type(*iter, val))
        {
            val_list.push_back(val);
        }
        else
        {
            ret = false;
        }
    }
    return(ret);
}

template <typename T>
bool stupid_type_to_string(const std::list<T> & val_list, std::list<std::string> & str_list)
{
    bool ret = true;
    for (typename std::list<T>::const_iterator iter = val_list.begin(); val_list.end() != iter; ++iter)
    {
        std::string str;
        if (stupid_type_to_string(*iter, str))
        {
            str_list.push_back(str);
        }
        else
        {
            ret = false;
        }
    }
    return(ret);
}

class JsonImpl
{
public:
    JsonImpl();
    ~JsonImpl();

private:
    JsonImpl(const JsonImpl & other);
    JsonImpl & operator = (const JsonImpl & other);

public:
    bool into_element(size_t element_index);
    bool into_element(const char * element_name);
    bool outof_element();

public:
    Stupid::Base::json_value_t::v_t get_type();
    size_t get_size();

public: /* read */
    bool load(const char * file_name);
    bool set_document(const char * document);
    bool find_element(const char * element_name);
    bool get_element(const char * element_name, std::string & element_value);
    bool get_element(const char * element_name, char * element_value, size_t element_value_size);
    bool get_element(const char * element_name, std::list<std::string> & element_value_list);

public: /* write */
    bool save(const char * file_name, bool format = true);
    bool add_element(size_t element_index);
    bool add_element(const char * element_name);
    bool add_element(const char * element_name, const char * element_value);
    bool add_element(const char * element_name, const std::string & element_value);
    bool add_element(const char * element_name, const std::list<std::string> & element_value_list);
    bool set_element(const char * element_name, const char * element_value);
    bool set_element(const char * element_name, const std::string & element_value);
    bool set_element(const char * element_name, const std::list<std::string> & element_value_list);
    bool remove_element(size_t element_index);
    bool remove_element(const char * element_name);

public: /* overload */
    bool get_element(const char * element_name, bool & element_value);
    bool get_element(const char * element_name, int8_t & element_value);
    bool get_element(const char * element_name, uint8_t & element_value);
    bool get_element(const char * element_name, int16_t & element_value);
    bool get_element(const char * element_name, uint16_t & element_value);
    bool get_element(const char * element_name, int32_t & element_value);
    bool get_element(const char * element_name, uint32_t & element_value);
    bool get_element(const char * element_name, int64_t & element_value);
    bool get_element(const char * element_name, uint64_t & element_value);
    bool get_element(const char * element_name, float & element_value);
    bool get_element(const char * element_name, double & element_value);

    bool get_element(const char * element_name, std::list<bool> & element_value_list);
    bool get_element(const char * element_name, std::list<int8_t> & element_value_list);
    bool get_element(const char * element_name, std::list<uint8_t> & element_value_list);
    bool get_element(const char * element_name, std::list<int16_t> & element_value_list);
    bool get_element(const char * element_name, std::list<uint16_t> & element_value_list);
    bool get_element(const char * element_name, std::list<int32_t> & element_value_list);
    bool get_element(const char * element_name, std::list<uint32_t> & element_value_list);
    bool get_element(const char * element_name, std::list<int64_t> & element_value_list);
    bool get_element(const char * element_name, std::list<uint64_t> & element_value_list);
    bool get_element(const char * element_name, std::list<float> & element_value_list);
    bool get_element(const char * element_name, std::list<double> & element_value_list);

    bool add_element(const char * element_name, bool element_value, bool as_string);
    bool add_element(const char * element_name, int8_t element_value, bool as_string);
    bool add_element(const char * element_name, uint8_t element_value, bool as_string);
    bool add_element(const char * element_name, int16_t element_value, bool as_string);
    bool add_element(const char * element_name, uint16_t element_value, bool as_string);
    bool add_element(const char * element_name, int32_t element_value, bool as_string);
    bool add_element(const char * element_name, uint32_t element_value, bool as_string);
    bool add_element(const char * element_name, int64_t element_value, bool as_string);
    bool add_element(const char * element_name, uint64_t element_value, bool as_string);
    bool add_element(const char * element_name, float element_value, bool as_string);
    bool add_element(const char * element_name, double element_value, bool as_string);

    bool add_element(const char * element_name, const std::list<bool> & element_value_list, bool as_string);
    bool add_element(const char * element_name, const std::list<int8_t> & element_value_list, bool as_string);
    bool add_element(const char * element_name, const std::list<uint8_t> & element_value_list, bool as_string);
    bool add_element(const char * element_name, const std::list<int16_t> & element_value_list, bool as_string);
    bool add_element(const char * element_name, const std::list<uint16_t> & element_value_list, bool as_string);
    bool add_element(const char * element_name, const std::list<int32_t> & element_value_list, bool as_string);
    bool add_element(const char * element_name, const std::list<uint32_t> & element_value_list, bool as_string);
    bool add_element(const char * element_name, const std::list<int64_t> & element_value_list, bool as_string);
    bool add_element(const char * element_name, const std::list<uint64_t> & element_value_list, bool as_string);
    bool add_element(const char * element_name, const std::list<float> & element_value_list, bool as_string);
    bool add_element(const char * element_name, const std::list<double> & element_value_list, bool as_string);

    bool set_element(const char * element_name, bool element_value, bool as_string);
    bool set_element(const char * element_name, int8_t element_value, bool as_string);
    bool set_element(const char * element_name, uint8_t element_value, bool as_string);
    bool set_element(const char * element_name, int16_t element_value, bool as_string);
    bool set_element(const char * element_name, uint16_t element_value, bool as_string);
    bool set_element(const char * element_name, int32_t element_value, bool as_string);
    bool set_element(const char * element_name, uint32_t element_value, bool as_string);
    bool set_element(const char * element_name, int64_t element_value, bool as_string);
    bool set_element(const char * element_name, uint64_t element_value, bool as_string);
    bool set_element(const char * element_name, float element_value, bool as_string);
    bool set_element(const char * element_name, double element_value, bool as_string);

    bool set_element(const char * element_name, const std::list<bool> & element_value_list, bool as_string);
    bool set_element(const char * element_name, const std::list<int8_t> & element_value_list, bool as_string);
    bool set_element(const char * element_name, const std::list<uint8_t> & element_value_list, bool as_string);
    bool set_element(const char * element_name, const std::list<int16_t> & element_value_list, bool as_string);
    bool set_element(const char * element_name, const std::list<uint16_t> & element_value_list, bool as_string);
    bool set_element(const char * element_name, const std::list<int32_t> & element_value_list, bool as_string);
    bool set_element(const char * element_name, const std::list<uint32_t> & element_value_list, bool as_string);
    bool set_element(const char * element_name, const std::list<int64_t> & element_value_list, bool as_string);
    bool set_element(const char * element_name, const std::list<uint64_t> & element_value_list, bool as_string);
    bool set_element(const char * element_name, const std::list<float> & element_value_list, bool as_string);
    bool set_element(const char * element_name, const std::list<double> & element_value_list, bool as_string);

private: /* template */
    template <typename T> bool do_get_element(const char * element_name, T & element_value);
    template <typename T> bool do_get_element(const char * element_name, std::list<T> & element_value_list);
    template <typename T> bool do_add_element(const char * element_name, T element_value);
    template <typename T> bool do_add_element(const char * element_name, const std::list<T> & element_value_list);
    template <typename T> bool do_set_element(const char * element_name, T element_value);
    template <typename T> bool do_set_element(const char * element_name, const std::list<T> & element_value_list);

private:
    Json::Reader                    m_reader;
    Json::Value                     m_root_value;
    std::list<Json::Value *>        m_child_values;
};

template <typename T>
bool JsonImpl::do_get_element(const char * element_name, T & element_value)
{
    std::string str_element_value;
    return(get_element(element_name, str_element_value) && stupid_string_to_type(str_element_value, element_value));
}

template <typename T>
bool JsonImpl::do_get_element(const char * element_name, std::list<T> & element_value_list)
{
    std::list<std::string> str_element_value_list;
    return(get_element(element_name, str_element_value_list) && stupid_string_to_type(str_element_value_list, element_value_list));
}

template <typename T>
bool JsonImpl::do_add_element(const char * element_name, T element_value)
{
    if (nullptr == element_name)
    {
        return(false);
    }
    Json::Value & json_parent = (m_child_values.empty() ? m_root_value : *m_child_values.back());
    Json::Value & json_child = json_parent[element_name];
    json_child = element_value;
    return(true);
}

template <typename T>
bool JsonImpl::do_add_element(const char * element_name, const std::list<T> & element_value_list)
{
    if (nullptr == element_name)
    {
        return(false);
    }
    Json::Value & json_parent = (m_child_values.empty() ? m_root_value : *m_child_values.back());
    Json::Value & json_child = json_parent[element_name];
    for (typename std::list<T>::const_iterator iter = element_value_list.begin(); element_value_list.end() != iter; ++iter)
    {
        json_child.append(*iter);
    }
    return(true);
}

template <typename T>
bool JsonImpl::do_set_element(const char * element_name, T element_value)
{
    if (nullptr == element_name)
    {
        return(false);
    }
    Json::Value & json_parent = (m_child_values.empty() ? m_root_value : *m_child_values.back());
    Json::Value & json_child = json_parent[element_name];
    json_child = element_value;
    return(true);
}

template <typename T>
bool JsonImpl::do_set_element(const char * element_name, const std::list<T> & element_value_list)
{
    if (nullptr == element_name)
    {
        return(false);
    }
    Json::Value & json_parent = (m_child_values.empty() ? m_root_value : *m_child_values.back());
    Json::Value & json_child = json_parent[element_name];
    json_child.clear();
    for (typename std::list<T>::const_iterator iter = element_value_list.begin(); element_value_list.end() != iter; ++iter)
    {
        json_child.append(*iter);
    }
    return(true);
}


#endif // JSON_IMPL_H
