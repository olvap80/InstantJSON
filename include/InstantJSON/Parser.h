/**\file InstantJSON/Parser.h
*  \brief
*/

#ifndef InstantJSON_Parser_HDR
#define InstantJSON_Parser_HDR

#include "Variant.h"
#include <cstdlib>


namespace InstantJSON{


template<class HandlerMixin>
class Parser: public HandlerMixin{
public:
    ///Parse data up to count bytes
    bool Parse(const char* data, std::size_t count);

    ///Parse data from dataBegin to dataEnd
    bool Parse(const char* dataBegin, const char* dataEnd);

private:

};



} //namespace InstantJSON

#endif
