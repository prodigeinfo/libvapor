#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <vapor/vpunsignedbyte.hpp>


using namespace std;
using namespace vapor;

BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(vpunsignedbyte_serialize)
{
    vparchive_t expect, result;
    vpunsignedbyte vpb;

    expect = "unsignedByte;1;A";
    vpb = 'A';
    result = vpb.serialize();
    BOOST_REQUIRE_EQUAL(expect, result);
}

BOOST_AUTO_TEST_CASE(vpunsignedbyte_deserialize)
{
    unsigned char expect;
    vpunsignedbyte result;
    vparchive_t s;

    try {
        result.deserialize("void;1;A");
        BOOST_FAIL("bad type shoud fail [" + boost::lexical_cast<std::string>(result) + "]");
    }
    catch (invalid_argument ex) {}

    s = "unsignedByte;1;A";
    expect = 'A';
    result.deserialize(s.c_str());
    BOOST_REQUIRE_EQUAL(expect, result);
}

BOOST_AUTO_TEST_SUITE_END()
