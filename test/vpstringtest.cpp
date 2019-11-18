#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <vapor/vpstring.hpp>


using namespace std;
using namespace vapor;

BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(vpstring_serialize)
{
    vparchive_t expect, result;
    vpstring vps;

    expect = "string;10;1234567890";
    vps = "1234567890";
    result = vps.serialize();
    BOOST_REQUIRE_EQUAL(expect, result);
}

BOOST_AUTO_TEST_CASE(vpstring_deserialize)
{
    vparchive_t a;
    vpstring expect, result;

    try {
        result.deserialize("void;10;1234567890");
        BOOST_FAIL("bad type shoud fail [" + result + "]");
    }
    catch (invalid_argument ex) {}

    //TODO add conversion fail tests (lexical tests)

    a = "string;10;1234567890";
    expect = "1234567890";
    result.deserialize(a.c_str());
    BOOST_REQUIRE_EQUAL(expect, result);

}

BOOST_AUTO_TEST_SUITE_END()
