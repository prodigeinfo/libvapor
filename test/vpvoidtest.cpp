#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <vapor/vpvoid.hpp>


using namespace std;
using namespace vapor;

BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(vpvoid_serialize)
{
    vparchive_t expect, result;
    vpvoid vpnull1;

    expect = vpvoid::SERIALIZED;
    result = vpnull1.serialize();
    BOOST_REQUIRE_EQUAL(expect, result);
}

BOOST_AUTO_TEST_CASE(vpvoid_deserialize)
{
    vpvoid expect, result;
    vparchive_t a;

    try {
        result.deserialize("none;0;");
        BOOST_FAIL("bad type shoud fail: void");
    }
    catch (invalid_argument ex) {}

    result.deserialize(vpvoid::SERIALIZED);
    BOOST_REQUIRE_EQUAL(expect, result);
}

BOOST_AUTO_TEST_SUITE_END()
