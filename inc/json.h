#ifndef JSON_H
#define JSON_H


#include <cstdint>
#include <list>
#include <string>

#ifdef _MSC_VER
    #define STUPID_CDECL           __cdecl
    #define STUPID_STDCALL         __stdcall
    #ifdef EXPORT_STUPID_DLL
        #define STUPID_API         __declspec(dllexport)
    #else
        #ifdef USE_STUPID_DLL
            #define STUPID_API     __declspec(dllimport)
        #else
            #define STUPID_API
        #endif // USE_STUPID_DLL
    #endif // EXPORT_STUPID_DLL
#else
    #define STUPID_CDECL
    #define STUPID_STDCALL
    #define STUPID_API
#endif // _MSC_VER

class JsonImpl;

namespace Stupid {
namespace Base {

struct json_value_t
{
    enum v_t
    {
        json_scalar, 
        json_object, 
        json_array
    };
};

class STUPID_API Json
{
public:
    Json();
    ~Json();

private:
    Json(const Json & other);
    Json & operator = (const Json & other);

public:
    bool into_element(size_t element_index);
    bool into_element(const char * element_name);
    bool outof_element();

public:
    json_value_t::v_t get_type();
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
    bool get_document(std::string & document, bool format = true);
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

    bool add_element(const char * element_name, bool element_value, bool as_string = false);
    bool add_element(const char * element_name, int8_t element_value, bool as_string = false);
    bool add_element(const char * element_name, uint8_t element_value, bool as_string = false);
    bool add_element(const char * element_name, int16_t element_value, bool as_string = false);
    bool add_element(const char * element_name, uint16_t element_value, bool as_string = false);
    bool add_element(const char * element_name, int32_t element_value, bool as_string = false);
    bool add_element(const char * element_name, uint32_t element_value, bool as_string = false);
    bool add_element(const char * element_name, int64_t element_value, bool as_string = false);
    bool add_element(const char * element_name, uint64_t element_value, bool as_string = false);
    bool add_element(const char * element_name, float element_value, bool as_string = false);
    bool add_element(const char * element_name, double element_value, bool as_string = false);

    bool add_element(const char * element_name, const std::list<bool> & element_value_list, bool as_string = false);
    bool add_element(const char * element_name, const std::list<int8_t> & element_value_list, bool as_string = false);
    bool add_element(const char * element_name, const std::list<uint8_t> & element_value_list, bool as_string = false);
    bool add_element(const char * element_name, const std::list<int16_t> & element_value_list, bool as_string = false);
    bool add_element(const char * element_name, const std::list<uint16_t> & element_value_list, bool as_string = false);
    bool add_element(const char * element_name, const std::list<int32_t> & element_value_list, bool as_string = false);
    bool add_element(const char * element_name, const std::list<uint32_t> & element_value_list, bool as_string = false);
    bool add_element(const char * element_name, const std::list<int64_t> & element_value_list, bool as_string = false);
    bool add_element(const char * element_name, const std::list<uint64_t> & element_value_list, bool as_string = false);
    bool add_element(const char * element_name, const std::list<float> & element_value_list, bool as_string = false);
    bool add_element(const char * element_name, const std::list<double> & element_value_list, bool as_string = false);

    bool set_element(const char * element_name, bool element_value, bool as_string = false);
    bool set_element(const char * element_name, int8_t element_value, bool as_string = false);
    bool set_element(const char * element_name, uint8_t element_value, bool as_string = false);
    bool set_element(const char * element_name, int16_t element_value, bool as_string = false);
    bool set_element(const char * element_name, uint16_t element_value, bool as_string = false);
    bool set_element(const char * element_name, int32_t element_value, bool as_string = false);
    bool set_element(const char * element_name, uint32_t element_value, bool as_string = false);
    bool set_element(const char * element_name, int64_t element_value, bool as_string = false);
    bool set_element(const char * element_name, uint64_t element_value, bool as_string = false);
    bool set_element(const char * element_name, float element_value, bool as_string = false);
    bool set_element(const char * element_name, double element_value, bool as_string = false);

    bool set_element(const char * element_name, const std::list<bool> & element_value_list, bool as_string = false);
    bool set_element(const char * element_name, const std::list<int8_t> & element_value_list, bool as_string = false);
    bool set_element(const char * element_name, const std::list<uint8_t> & element_value_list, bool as_string = false);
    bool set_element(const char * element_name, const std::list<int16_t> & element_value_list, bool as_string = false);
    bool set_element(const char * element_name, const std::list<uint16_t> & element_value_list, bool as_string = false);
    bool set_element(const char * element_name, const std::list<int32_t> & element_value_list, bool as_string = false);
    bool set_element(const char * element_name, const std::list<uint32_t> & element_value_list, bool as_string = false);
    bool set_element(const char * element_name, const std::list<int64_t> & element_value_list, bool as_string = false);
    bool set_element(const char * element_name, const std::list<uint64_t> & element_value_list, bool as_string = false);
    bool set_element(const char * element_name, const std::list<float> & element_value_list, bool as_string = false);
    bool set_element(const char * element_name, const std::list<double> & element_value_list, bool as_string = false);

private:
    JsonImpl                      * m_json_impl;
};

}
}


#endif // JSON_H
