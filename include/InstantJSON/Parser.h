/**@file InstantJSON/Parser.h
*  @brief
*/

#ifndef InstantJSON_Parser_HDR
#define InstantJSON_Parser_HDR

#include <cstdlib>


namespace InstantJSON{


///Parse input data and call methods from HandlerMixin
/** HandlerMixin should provide following metods
    @code
        class Handler{
        public:
            ///construct handler instance
            Handler();
            ...
        protected:
            ///Handle error detected while parsing
            bool OnError(std::size_t line, std::size_t column, ErrorCode errorCode);
        private:
            ...
        );

    @endcode */
template<class HandlerMixin>
class Parser: public HandlerMixin{
public:
    ///Parse all data up to count bytes
    bool Parse(const char* data, std::size_t count);

    ///Parse all data from dataBegin to dataEnd
    template<class Itr>
    bool Parse(Itr dataBegin, Itr dataEnd);

    ///Parse data fragmet of count bytes
    bool OnFragment(const char* data, std::size_t count);

    ///Parse data fragmet from dataBegin to dataEnd
    template<class Itr>
    bool OnFragment(Itr dataBegin, Itr dataEnd);

    ///Sign that there are no more fragments
    bool OnFragmentsCompleted();

private:

};



//template<class HandlerMixin>


} //namespace InstantJSON

#endif
