/**\file InstantJSON/Details/Container.h
*  \brief
*/

#ifndef InstantJSON_Container_HDR
#define InstantJSON_Container_HDR

#include "../ConfigurationOptions.h"

#include <cstdlib>
#include <cstdint>

namespace InstantJSON{ namespace Details{

union Container{
    typedef std::uint8_t Byte;
    ///Type to physically hold integers
    typedef std::int_least32_t Int;
    ///Type to physically hold unsigned integers
    typedef std::uint_least32_t UInt;
    ///Type to physically hold double precision float
    typedef double Double;

    ///Natural machine word
    typedef unsigned Word;

    enum{
        ///Number of words
        WordCount = (INSTANTJSON_VARIANT_CONTAINER_MINIMUM_SIZE + sizeof(Word)-1)/ sizeof(Word),
        ByteCount = sizeof(Word) * WordCount
    };

    ///Allocate minimum space in bytes (union with all types)
    Byte SpaceAsBytes[ByteCount];

    ///Allocate minimum space in Words (union with all types)
    Word SpaceAsWords[WordCount];

    ///Types for items inside container (internal represetation)
    enum ItemType{
        ItemTypeUndefined,

        ItemTypeNull,

        ItemTypeBooleanTrue,
        ItemTypeBooleanFalse,

        ItemTypeInt,
        ItemTypeUInt,
        ItemTypeDouble,

        ItemTypeShortString,
        ItemTypeLongString,

        ItemTypeArray,
        ItamTypeObject,

        ItemTypeTotalCount
    };

    ///Type of item encapsulated in the container
    Byte Type;

    ///Hold boolean values

    ///Hold numeric types
    struct{
        ///Type of item encapsulated in the container (force alignment)
        /** One of ItemTypeInt, ItemTypeUInt, ItemTypeDouble*/
        Byte NumberType;

        //Items
        union{
            Int IntValue;

            UInt UIntValue;

            Double DoubleValue;
        };
    } Number;


    ///Hold short string that fits into container size
    struct{
        ///Type of string item encapsulated in the container (force alignment)
        /** Set to for ShortString*/
        Byte Type;

        ///Bytes of the string in place
        Byte Utf8[ByteCount-1];
    } ShortString;

    ///Use this struct to contain long strings
    struct LongStringData{
        LongStringData() : refCount(0) {}
        ///Number of references to this object
        int refCount;

        ///Number of bytes in string tail
        std::size_t ByteCount;

        ///Bytes pointer
        Byte* Utf8Ptr;
    };

    ///Hold long string that does not fits into container size
    struct{
        ///Type of string item encapsulated in the container (force alignment)
        /** Set to for ShortString*/
        std::uint8_t Type;

        LongStringData* Data;
    } LongString;
};

static_assert(sizeof(Container) <= INSTANTJSON_VARIANT_CONTAINER_MINIMUM_SIZE, "Container does not fit into INSTANTJSON_VARIANT_CONTAINER_MINIMUM_SIZE");
static_assert(sizeof(Container) == Container::ByteCount, "Container size is calculated wrong");
static_assert(sizeof(Container::SpaceAsBytes) == sizeof(Container::SpaceAsWords), "Container representations do not fit");


}} //namespace InstantJSON::Details

#endif
