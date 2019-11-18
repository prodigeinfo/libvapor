#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <vapor/vpunsignedint.hpp>


using namespace std;
using namespace vapor;

BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(vpunsignedint_serialize)
{
    vparchive_t expect, result;
    vpunsignedint vpn;

    expect = "unsignedInt;10;1234567890";
    vpn = static_cast<vpunsignedint_t>(1234567890);
    result = vpn.serialize();
    BOOST_REQUIRE_EQUAL(expect, result);
}

BOOST_AUTO_TEST_CASE(vpunsignedint_deserialize)
{
    unsigned expect;
    vpunsignedint result;
    vparchive_t s;

    try {
        result.deserialize("void;10;1234567890");
        BOOST_FAIL("bad type shoud fail [" + boost::lexical_cast<std::string>(result) + "]");
    }
    catch (invalid_argument ex) {}

    s = "unsignedInt;10;1234567890";
    expect = static_cast<vpunsignedint_t>(1234567890);
    result.deserialize(s.c_str());
    BOOST_REQUIRE_EQUAL(expect, result);
}

BOOST_AUTO_TEST_SUITE_END()
