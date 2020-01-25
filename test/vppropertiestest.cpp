#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <vapor/vpint.hpp>
#include <vapor/vpstring.hpp>
#include <vapor/vpproperties.hpp>


using namespace std;
using namespace vapor;

BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(vpproperties_serialize)
{
    vparchive_t expect, result;
    vpproperties vpprop;

    expect = "properties;62;string;3;ageint;10;1234567890string;4;namestring;10;1234567890";
    vpprop["age"] = new vpint(1234567890);
    vpprop["name"] = new vpstring("1234567890");
    result = vpprop.serialize();
    BOOST_REQUIRE_EQUAL(expect, result);

    vpprop.clear();
    expect = "properties;13;string;1;x;0;";
    vpprop["x"] = nullptr;
    result = vpprop.serialize();
    BOOST_REQUIRE_EQUAL(expect, result);
}

BOOST_AUTO_TEST_CASE(vpproperties_deserialize)
{
    const char *s;
    vpproperties result;
    int expectn, resultn;
    string expects, results;
    vptype *expectvpt, *resultvpt;


    try {
        result.deserialize("void;62;string;3;ageint;10;1234567890string;4;namestring;10;1234567890");
        BOOST_FAIL("bad type shoud fail: void");
    }
    catch (invalid_argument ex) {}

    s = "properties;62;string;3;ageint;10;1234567890string;4;namestring;10;1234567890";
    result.deserialize(s);
    expectn = 1234567890;
    resultn = vpint::read(result.at("age"));
    BOOST_REQUIRE_EQUAL(expectn, resultn);
    expects = "1234567890";
    results = vpstring::get(result.at("name"));
    BOOST_REQUIRE_EQUAL(expects, results);

    s = "properties;13;string;1;x;0;";
    expectvpt = nullptr;
    result.deserialize(s);
    resultvpt = result.at("x");
    BOOST_REQUIRE_EQUAL(expectvpt, resultvpt);
}

BOOST_AUTO_TEST_SUITE_END()
