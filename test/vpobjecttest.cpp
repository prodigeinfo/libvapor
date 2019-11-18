#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <vapor/vpfixobject.hpp>


using namespace std;
using namespace vapor;

BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(vpobject_properties_get_set)
{
    int expectn, resultn;
    string expects, results;
    vpobject o;

    try
    {
        o.get("test");
        BOOST_FAIL("unknown property should have failed: get \"test\"");
    }
    catch (out_of_range ex) {}

    // test basic types
    expectn = 1234567890;
    o.set_int("test2", expectn);
    resultn = o.read_int("test2");
    BOOST_REQUIRE_EQUAL(expectn, resultn);

    // test basic types
    expects = "1234567890";
    o.set_string("test2", expects);
    results = o.read_string("test2");
    BOOST_REQUIRE_EQUAL(expects, results);
}


BOOST_AUTO_TEST_CASE(vpobject_serialize)
{
    vparchive_t result;
    vpobject o;

    o.set_int("test1", 1234567890);
    o.set_string("test2", "1234567890");
    result = o.serialize();
    BOOST_REQUIRE_EQUAL("object;79;properties;65;string;5;test1int;10;1234567890string;5;test2string;10;1234567890", result);
}

BOOST_AUTO_TEST_CASE(vpobject_deserialize)
{
    vpobject o;
    int resultn;
    string results;

    o.deserialize("object;79;properties;65;string;5;test1int;10;1234567890string;5;test2string;10;1234567890");
    resultn = o.read_int("test1");
    BOOST_REQUIRE_EQUAL(resultn, 1234567890);
    results = o.read_string("test2");
    BOOST_REQUIRE_EQUAL(results, "1234567890");
}

BOOST_AUTO_TEST_SUITE_END()
