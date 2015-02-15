/**\file InstantJSON/Details/Container.h
*  \brief
*/

#ifndef InstantJSON_Container_HDR
#define InstantJSON_Container_HDR

#include "../ConfigurationOptions.h"

#include <cstdlib>
#include <cstdint>

namespace InstantJSON{ namespace Details{


struct LongString{
    ///Number of bytes in string tail
    std::size_t ByteCount;

    ///Bytes pointer
    std::uint8_t* Utf8Ptr;
};


union Container{
    ///Types for items inside container
    enum ItemType{
        ItemTypeInt,
        ItemTypeUInt,
        ItemTypeDouble,
        ItemTypeShortString,
        ItemTypeLongString,
        ItemTypeTotalItems
    };

    ///Allocate minimum space
    std::uint8_t ReserveSpace[INSTANTJSON_VARIANT_CONTAINER_SIZE];

    ///Type of item encapsulated in the container
    std::uint8_t Type;

    //numeric types
    struct{
        ///Type of item encapsulated in the container (force alignment)
        /** One of  */
        std::uint8_t NumberType;

        //Items
        union{
            std::int_least32_t Int;

            std::uint_least32_t UInt;

            double Double;
        };
    } Number;

    struct{
        ///Type of string item encapsulated in the container (force alignment)
        /** Set to for ShortString*/
        std::uint8_t Type;

        ///Bytes
        std::uint8_t Utf8[INSTANTJSON_VARIANT_CONTAINER_SIZE-1];
    } ShortString;

    struct{
        ///Type of string item encapsulated in the container (force alignment)
        /** Set to for ShortString*/
        std::uint8_t Type;

        LongString* Data;
    } LongString;
};

static_assert(sizeof(Container) == INSTANTJSON_VARIANT_CONTAINER_SIZE, "Container does not fit into INSTANTJSON_VARIANT_CONTAINER_SIZE");


}} //namespace InstantJSON::Details

#endif
