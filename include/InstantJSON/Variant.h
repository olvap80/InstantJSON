/**@file InstantJSON/Variant.h
*  @brief
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
        TypeError,
        TypeNull,
        TypeBoolean,
        TypeInteger,
        TypeReal,
        TypeString,
        TypeArray,
        TypeObject,

        TypeTotalCount
    };

    ///Map to JS like types
    enum JSType{
        JSTypeUndefined,
        JSTypeError,
        JSTypeBoolean,
        JSTypeNumber,
        JSTypeString,
        JSTypeObject,

        JSTypeTotalCount
    };

    template<class T>
    T As() const;

    template<class T>
    bool To(T& outResult);

private:
    Details::Container container;
};



} //namespace InstantJSON

#endif
