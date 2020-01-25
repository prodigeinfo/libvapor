#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <vapor/vpint.hpp>
#include <vapor/vpstring.hpp>
#include <vapor/vpvector.hpp>


using namespace std;
using namespace vapor;

BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(vpvector_element_gettype)
{
    string expect[2], result;
    vpvector vpv(2);
    vpint *vpn = new vpint;
    vpstring *vps = new vpstring;

    expect[0] = vpn->gettype();
    vpv.at(0) = vpn;

    expect[1] = vps->gettype();
    vpv.at(1) = vps;

    for (int i=0; i<vpv.size(); i++)
    {
        result = vpv.at(i)->gettype();
        BOOST_REQUIRE_EQUAL(expect[i], result);
    }
}

BOOST_AUTO_TEST_CASE(vpvector_serialize)
{
    vparchive_t expect, result;
    vpvector *vpv1 = new vpvector(2), vpv2(3);

    expect = "vector;44;int;1;2int;10;1234567890string;10;1234567890";
    vpv1->at(0) = new vpint(1234567890);
    vpv1->at(1) = new vpstring("1234567890");
    result = vpv1->serialize();
    BOOST_REQUIRE_EQUAL(expect, result);

    expect = "vector;98;int;1;3int;10;1234567890vector;44;int;1;2int;10;1234567890string;10;1234567890string;10;1234567890";
    vpv2[0] = new vpint(1234567890);
    vpv2[1] = vpv1;
    vpv2[2] = new vpstring("1234567890");
    result = vpv2.serialize();
    BOOST_REQUIRE_EQUAL(expect, result);

    expect = "vector;33;int;1;3;0;string;10;1234567890;0;";
    vpv2.clear();
    vpv2.resize(3);
    vpv2[1] = new vpstring("1234567890");
    result = vpv2.serialize();
    BOOST_REQUIRE_EQUAL(expect, result);
}

BOOST_AUTO_TEST_CASE(vpvector_deserialize)
{
    vpvector resultv1, *resultv2;
    int expectn, resultn;
    string expects, results;
    vptype *expectvpt, *resultvpt;

    expectn = 1234567890;
    expects = "1234567890";
    expectvpt = nullptr;

    resultv1.deserialize("vector;98;int;1;3int;10;1234567890vector;44;int;1;2int;10;1234567890string;10;1234567890string;10;1234567890");
    BOOST_REQUIRE_EQUAL(3, resultv1.size());
    resultn = vpint::read_int(resultv1[0]);
    BOOST_REQUIRE_EQUAL(expectn, resultn);
    resultv2 = reinterpret_cast<vpvector*>(resultv1[1]);;
    BOOST_REQUIRE_EQUAL(2, resultv2->size());
    resultn = vpint::read_int(resultv2->at(0));
    BOOST_REQUIRE_EQUAL(expectn, resultn);
    results = vpstring::get(resultv2->at(1));;
    BOOST_REQUIRE_EQUAL(expects, results);
    results = vpstring::get(resultv1[2]);;
    BOOST_REQUIRE_EQUAL(expects, results);

    resultv1.deserialize("vector;33;int;1;3;0;string;10;1234567890;0;");
    BOOST_REQUIRE_EQUAL(3, resultv1.size());
    resultvpt = resultv1[0];
    BOOST_REQUIRE_EQUAL(expectvpt, resultvpt);
    results = vpstring::get(resultv1[1]);;
    BOOST_REQUIRE_EQUAL(expects, results);
    resultvpt = resultv1[2];
    BOOST_REQUIRE_EQUAL(expectvpt, resultvpt);
}

BOOST_AUTO_TEST_SUITE_END()
