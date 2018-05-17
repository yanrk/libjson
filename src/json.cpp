#include <cassert>

#include "json.h"
#include "json_impl.h"

namespace Stupid {
namespace Base {

Json::Json() : m_json_impl(new JsonImpl)
{
    assert(nullptr != m_json_impl);
}

Json::~Json()
{
    delete m_json_impl;
}

bool Json::into_element(size_t element_index)
{
    return(nullptr != m_json_impl && m_json_impl->into_element(element_index));
}

bool Json::into_element(const char * element_name)
{
    return(nullptr != m_json_impl && m_json_impl->into_element(element_name));
}

bool Json::outof_element()
{
    return(nullptr != m_json_impl && m_json_impl->outof_element());
}

json_value_t::v_t Json::get_type()
{
    return(nullptr != m_json_impl ? m_json_impl->get_type() : json_value_t::json_scalar);
}

size_t Json::get_size()
{
    return(nullptr != m_json_impl ? m_json_impl->get_size() : 0);
}

bool Json::load(const char * file_name)
{
    return(nullptr != m_json_impl && m_json_impl->load(file_name));
}

bool Json::set_document(const char * document)
{
    return(nullptr != m_json_impl && m_json_impl->set_document(document));
}

bool Json::find_element(const char * element_name)
{
    return(nullptr != m_json_impl && m_json_impl->find_element(element_name));
}

bool Json::get_element(const char * element_name, std::string & element_value)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value));
}

bool Json::get_element(const char * element_name, char * element_value, size_t element_value_size)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value, element_value_size));
}

bool Json::get_element(const char * element_name, std::list<std::string> & element_value_list)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value_list));
}

bool Json::save(const char * file_name, bool format)
{
    return(nullptr != m_json_impl && m_json_impl->save(file_name, format));
}

bool Json::get_document(std::string & document, bool format)
{
    return(nullptr != m_json_impl && m_json_impl->get_document(document, format));
}

bool Json::add_element(size_t element_index)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_index));
}

bool Json::add_element(const char * element_name)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name));
}

bool Json::add_element(const char * element_name, const char * element_value)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value));
}

bool Json::add_element(const char * element_name, const std::string & element_value)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value));
}

bool Json::add_element(const char * element_name, const std::list<std::string> & element_value_list)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value_list));
}

bool Json::set_element(const char * element_name, const char * element_value)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value));
}

bool Json::set_element(const char * element_name, const std::string & element_value)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value));
}

bool Json::set_element(const char * element_name, const std::list<std::string> & element_value_list)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value_list));
}

bool Json::remove_element(size_t element_index)
{
    return(nullptr != m_json_impl && m_json_impl->remove_element(element_index));
}

bool Json::remove_element(const char * element_name)
{
    return(nullptr != m_json_impl && m_json_impl->remove_element(element_name));
}

bool Json::get_element(const char * element_name, bool & element_value)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value));
}

bool Json::get_element(const char * element_name, int8_t & element_value)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value));
}

bool Json::get_element(const char * element_name, uint8_t & element_value)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value));
}

bool Json::get_element(const char * element_name, int16_t & element_value)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value));
}

bool Json::get_element(const char * element_name, uint16_t & element_value)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value));
}

bool Json::get_element(const char * element_name, int32_t & element_value)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value));
}

bool Json::get_element(const char * element_name, uint32_t & element_value)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value));
}

bool Json::get_element(const char * element_name, int64_t & element_value)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value));
}

bool Json::get_element(const char * element_name, uint64_t & element_value)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value));
}

bool Json::get_element(const char * element_name, float & element_value)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value));
}

bool Json::get_element(const char * element_name, double & element_value)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value));
}

bool Json::get_element(const char * element_name, std::list<bool> & element_value_list)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value_list));
}

bool Json::get_element(const char * element_name, std::list<int8_t> & element_value_list)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value_list));
}

bool Json::get_element(const char * element_name, std::list<uint8_t> & element_value_list)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value_list));
}

bool Json::get_element(const char * element_name, std::list<int16_t> & element_value_list)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value_list));
}

bool Json::get_element(const char * element_name, std::list<uint16_t> & element_value_list)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value_list));
}

bool Json::get_element(const char * element_name, std::list<int32_t> & element_value_list)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value_list));
}

bool Json::get_element(const char * element_name, std::list<uint32_t> & element_value_list)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value_list));
}

bool Json::get_element(const char * element_name, std::list<int64_t> & element_value_list)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value_list));
}

bool Json::get_element(const char * element_name, std::list<uint64_t> & element_value_list)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value_list));
}

bool Json::get_element(const char * element_name, std::list<float> & element_value_list)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value_list));
}

bool Json::get_element(const char * element_name, std::list<double> & element_value_list)
{
    return(nullptr != m_json_impl && m_json_impl->get_element(element_name, element_value_list));
}

bool Json::add_element(const char * element_name, bool element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value, as_string));
}

bool Json::add_element(const char * element_name, int8_t element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value, as_string));
}

bool Json::add_element(const char * element_name, uint8_t element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value, as_string));
}

bool Json::add_element(const char * element_name, int16_t element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value, as_string));
}

bool Json::add_element(const char * element_name, uint16_t element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value, as_string));
}

bool Json::add_element(const char * element_name, int32_t element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value, as_string));
}

bool Json::add_element(const char * element_name, uint32_t element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value, as_string));
}

bool Json::add_element(const char * element_name, int64_t element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value, as_string));
}

bool Json::add_element(const char * element_name, uint64_t element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value, as_string));
}

bool Json::add_element(const char * element_name, float element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value, as_string));
}

bool Json::add_element(const char * element_name, double element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value, as_string));
}

bool Json::add_element(const char * element_name, const std::list<bool> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value_list, as_string));
}

bool Json::add_element(const char * element_name, const std::list<int8_t> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value_list, as_string));
}

bool Json::add_element(const char * element_name, const std::list<uint8_t> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value_list, as_string));
}

bool Json::add_element(const char * element_name, const std::list<int16_t> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value_list, as_string));
}

bool Json::add_element(const char * element_name, const std::list<uint16_t> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value_list, as_string));
}

bool Json::add_element(const char * element_name, const std::list<int32_t> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value_list, as_string));
}

bool Json::add_element(const char * element_name, const std::list<uint32_t> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value_list, as_string));
}

bool Json::add_element(const char * element_name, const std::list<int64_t> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value_list, as_string));
}

bool Json::add_element(const char * element_name, const std::list<uint64_t> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value_list, as_string));
}

bool Json::add_element(const char * element_name, const std::list<float> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value_list, as_string));
}

bool Json::add_element(const char * element_name, const std::list<double> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->add_element(element_name, element_value_list, as_string));
}

bool Json::set_element(const char * element_name, bool element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value, as_string));
}

bool Json::set_element(const char * element_name, int8_t element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value, as_string));
}

bool Json::set_element(const char * element_name, uint8_t element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value, as_string));
}

bool Json::set_element(const char * element_name, int16_t element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value, as_string));
}

bool Json::set_element(const char * element_name, uint16_t element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value, as_string));
}

bool Json::set_element(const char * element_name, int32_t element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value, as_string));
}

bool Json::set_element(const char * element_name, uint32_t element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value, as_string));
}

bool Json::set_element(const char * element_name, int64_t element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value, as_string));
}

bool Json::set_element(const char * element_name, uint64_t element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value, as_string));
}

bool Json::set_element(const char * element_name, float element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value, as_string));
}

bool Json::set_element(const char * element_name, double element_value, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value, as_string));
}

bool Json::set_element(const char * element_name, const std::list<bool> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value_list, as_string));
}

bool Json::set_element(const char * element_name, const std::list<int8_t> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value_list, as_string));
}

bool Json::set_element(const char * element_name, const std::list<uint8_t> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value_list, as_string));
}

bool Json::set_element(const char * element_name, const std::list<int16_t> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value_list, as_string));
}

bool Json::set_element(const char * element_name, const std::list<uint16_t> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value_list, as_string));
}

bool Json::set_element(const char * element_name, const std::list<int32_t> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value_list, as_string));
}

bool Json::set_element(const char * element_name, const std::list<uint32_t> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value_list, as_string));
}

bool Json::set_element(const char * element_name, const std::list<int64_t> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value_list, as_string));
}

bool Json::set_element(const char * element_name, const std::list<uint64_t> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value_list, as_string));
}

bool Json::set_element(const char * element_name, const std::list<float> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value_list, as_string));
}

bool Json::set_element(const char * element_name, const std::list<double> & element_value_list, bool as_string)
{
    return(nullptr != m_json_impl && m_json_impl->set_element(element_name, element_value_list, as_string));
}

}
}

