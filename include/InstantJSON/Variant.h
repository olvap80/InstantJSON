/**\file InstantJSON/Variant.h
*  \brief
*/

#ifndef InstantJSON_Variant_HDR
#define InstantJSON_Variant_HDR

#include "Details/Container.h"

namespace InstantJSON{


class Variant{
public:
    ///Map to JSON types
    enum Type{
        TypeUndefined,
        TypeNull,
        TypeBoolean,
        TypeNumber,
        TypeString,
        TypeArray,
        TypeObject,

        TypeTotalCount
    };

    ///Map to JS like typed
    enum JSType{
        JSTypeUndefined,
        JSTypeBoolean,
        JSTypeNumber,
        JSTypeString,
        JSTypeObject,

        JSTypeTotalCount
    };

private:

};



} //namespace InstantJSON

#endif
