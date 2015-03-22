/**@file NanoUnit.h
*  @brief Mimimalistic (header only) Unit Test framework for C++11 and above.
*/

///Group test cases
#define NU_TEST_SUITE_BEGIN(testSuiteName) \
    class testSuiteName##_TestSuite protected TestSuiteBase

#define NU_TEST_SUITE_END

#define NU_TEST_CASE_BEGIN(testCaseName)

#define NU_TEST_CASE_END


#define NU_CHECK(condition)

#define NU_IS_EQUAL(expected)


namespace NanoUnit{

///Helper to create list static/global object instances
template<class T>
class InstanceListBase{
public:
    ///Setup unconnected instance
    InstanceListBase() : next(nullptr) {}

    ///Invoke callback for each known instance (in the order as they were added)
    template<class FcnToCallOnEachPtr>
    static void ForEachInstance(FcnToCallOnEachPtr fcn){
        for(InstanceListBase* ptr = head; ptr != nullptr; ptr = ptr->next){
            fcn((T*)ptr);
        }
    }

protected:
    ///Add this item to the end of the list (preserve order)
    void AppendThisToList(){
        *pointerToTailPtr = this; //this will be new end of list
        pointerToTailPtr = &this->next; //set up new tail to update next time
    }

private:
    ///All known instances list head
    /**use simple pointer chain to prevent problems with initialization order*/
    static InstanceListBase* head;
    ///Remember current tail position here
    static InstanceListBase* *pointerToTailPtr;

    ///Pointer to the next known instance
    InstanceListBase* next;

    //ban dynamic allocation
    void* operator new(size_t);          // standard new
    void* operator new(size_t, void*);   // placement new
    void* operator new[](size_t);        // array new
    void* operator new[](size_t, void*); // placement array new
};

template<class T>
InstanceListBase<T>* InstanceListBase<T>::head = nullptr;


///Base class to be executed
class TestSuite{
protected:
    ///Optional setup to be executed each time
    virtual void SetUp(){}
    ///Mandatory test to be runned
    virtual void Run() = 0;
    ///Optional teardown to be executed each time
    virtual void TearDown(){}

};

///Exception to be used to signal that test case failed
class TestCaseFailed{};

///Collect all items in the test suite
class Runner: private InstanceListBase<Runner>{
public:
    ///Execute all known Test Suites
    static void RunAll(){
        ForEachInstance([](Runner* ptr){
            //
        });
    }
public:
};

} //namespace NanoUnit
