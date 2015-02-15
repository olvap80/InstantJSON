/**\file InstantJSON/Details/Container.h
*  \brief
*/

#ifndef InstantJSON_Container_HDR
#define InstantJSON_Container_HDR

#include "../ConfigurationOptions.h"

#include <cstdlib>
#include <cstdint>

namespace InstantJSON{ namespace Details{


class Container{
private:
    friend class InstantJSON::Variant;

    ///Allocate minimum space
    std::uint8_t ReserveSpace[INSTANTJSON_VARIANT_CONTAINER_SIZE];

    std::uint8_t Type;

    struct{
        union{
            struct{
            } Int;

            struct{
            } UInt;

            struct{
            }

            struct{
            } Double;
        }
    } Number;

};

static_assert(sizeof);


}} //namespace InstantJSON::Details

#endif
