#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <vapor/vpshort.hpp>


using namespace std;
using namespace vapor;

BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(vpshort_serialize)
{
    vparchive_t expect, result;
    vpshort vpn;

    expect = "short;5;12345";
    vpn = 12345;
    result = vpn.serialize();
    BOOST_REQUIRE_EQUAL(expect, result);
}

BOOST_AUTO_TEST_CASE(vpshort_deserialize)
{
    short expect;
    vpshort result;
    vparchive_t s;

    try {
        result.deserialize("void;5;12345");
        BOOST_FAIL("bad type shoud fail [" + boost::lexical_cast<std::string>(result) + "]");
    }
    catch (invalid_argument ex) {}

    s = "short;5;12345";
    expect = 12345;
    result.deserialize(s.c_str());
    BOOST_REQUIRE_EQUAL(expect, result);
}

BOOST_AUTO_TEST_SUITE_END()
