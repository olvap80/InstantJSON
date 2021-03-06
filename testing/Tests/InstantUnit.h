/** @file InstantUnit.h
    @brief Mimimalistic (header only) Unit Test framework for C++11 and above.

Simple usage sample:
@code

    IU_TEST("My test name"){
        //Optional setup statements
        ...
        //Checks and asserts (those like IU_CHECK, IU_IS_EQUAL, etc)
        ...
        //Optional teardown (cleanup)
        ...
        //Note: it is responsibility of the developer to ensure
        //      correct teardown in case of exception!
    }

@endcode

More complex sample (please notice how setup and teardown are located):
@code

    IU_TEST_SUITE("My Suite name"){ // ... __LINE__##_Run(NU::TestCaseRunner& NU_TestCaseRunner) {
        //optional setup code to be executed before every test case
        ... //declare variables, setup environment, etc

        IU_TEST_CASE("My TC 1"){ //NU_TestCaseRunner(__FILE__, __LINE__, "TC 1") ->* [&]() {
           ... //Checks and asserts (IU_CHECK, IU_IS_EQUAL, etc)
        };
        IU_TEST_CASE("My TC 2"){ //NU_TestCaseRunner(__FILE__, __LINE__, "TC 2") ->* [&]() {
           ... //Checks and asserts (IU_CHECK, IU_IS_EQUAL, etc)
        };
        ...//etc

        //optional teardown code to be executed after every test case
        ... //optionally cleanup the environment, if needed
        //Note: (teardown is automatically executed even in case of exception!)
    }

@endcode

Here test suite is not only a collection of test cases but also a way
to surround every test case in the collection with setup and teardown code.

Setup code from the test suite is executed before each test case like it is
pasted directly before the test case body. You can declare variables in setup
and they will be visible from test case body.

Teardown code from the test suite is executed after each test case like it is
pasted directly after the test case body. Teardown code is still automatically
executed even in case of exception in a test case body.
Every variable declared in Setup code is visible from Teardown code.

*/

#ifndef INSTANTUNIT_HDR_
#define INSTANTUNIT_HDR_

///Simple test
/** Place test code in braces after IU_TEST */
#define IU_TEST(testNameString)

///Group test cases together to support common setup/teardown
/**Place test setup, then test cases and then teardown in braces after IU_TEST.
   See example above on how to use this stuff.*/
#define IU_TEST_SUITE_BEGIN(testSuiteNameString) \
    class testSuiteName##_TestSuite protected TestSuiteBase

///Single test case item in test duite (share setup/teardown) with others
#define IU_TEST_CASE(testCaseNameString)



#define IU_CHECK(condition)

#define IU_IS_EQUAL(expectedValue, actualValue)


namespace InstantUnit{

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

} //namespace InstantUnit

#endif /*INSTANTUNIT_HDR_*/
