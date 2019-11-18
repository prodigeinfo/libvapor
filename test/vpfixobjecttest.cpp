#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <vapor/vpfixobject.hpp>


using namespace std;
using namespace vapor;

VPFO_NAME_DEF(CF_NAME,    "name");
VPFO_NAME_DEF(CF_AGE,     "age");

static constexpr const vpfixobject::propdef_t CLIENT_FILE_PROPERTIES[] =
{
    { CF_NAME,   vpstring::TYPE  },
    { CF_AGE,    vpint::TYPE     },
};
#define CFP_SIZE VPFO_SIZEOF(CLIENT_FILE_PROPERTIES)

class clientfile : public vpfixobject {
public:
    clientfile() : vpfixobject(CLIENT_FILE_PROPERTIES, CFP_SIZE) {}

    virtual vparchive_t serialize() const throw(std::runtime_error)
    {
        std::string content = vpfixobject::serialize();
        return std::string(TYPE) + VPARCHIVE_TOKEN_SEP + boost::lexical_cast<std::string>(content.length()) + VPARCHIVE_TOKEN_SEP + content;
    }

    virtual void deserialize(const char *s) throw(std::runtime_error, std::out_of_range, std::invalid_argument)
    {
        std::pair<std::string, std::string> rs = vptype::split(s);
        if (rs.first != TYPE) throw std::invalid_argument("clientfile::deserialize: bad format: " + rs.first);
        vpfixobject::deserialize(rs.second.c_str());
    }

    VPTYPE_CLASS_DECL(clientfile, clientfile)
};
VPTYPE_CLASS_DEF(clientfile)

BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(vpfixobject_properties_restrictions)
{
    int expect, result;
    clientfile clientfile1;

    try
    {
        clientfile1.get("agex");
        BOOST_FAIL("unknown property should have failed: get agex");
    }
    catch (out_of_range ex) {}

    try
    {
        clientfile1.set("agex", new vpint);
        BOOST_FAIL("unknown property should have failed: set agex");
    }
    catch (out_of_range ex) {}

    try
    {
        clientfile1.set(CF_AGE, new vpstring);
        BOOST_FAIL("bad property type should have failed: age=>vpstring");
    }
    catch (invalid_argument ex) {}

    expect = 1234567890;
    clientfile1.set_int(CF_AGE, expect);
    result = clientfile1.read_int(CF_AGE);
    BOOST_REQUIRE_EQUAL(result, expect);
}


BOOST_AUTO_TEST_CASE(vpfixobject_serialize)
{
    vparchive_t expect, result;
    vpfixobject o = vpfixobject(CLIENT_FILE_PROPERTIES, CFP_SIZE);
    clientfile clientfile1;

    expect = "fixobject;86;object;76;properties;62;string;3;ageint;10;1234567890string;4;namestring;10;1234567890";
    o.set_int(CF_AGE, 1234567890);
    o.set_string(CF_NAME, "1234567890");
    result = o.serialize();
    BOOST_REQUIRE_EQUAL("fixobject;86;object;76;properties;62;string;3;ageint;10;1234567890string;4;namestring;10;1234567890", result);

    expect = "clientfile;82;fixobject;69;object;59;properties;45;string;3;ageint;10;1234567890string;4;name;0;";
    clientfile1.set_int(CF_AGE, 1234567890);
    result = clientfile1.serialize();
    BOOST_REQUIRE_EQUAL(expect, result);

    expect = "clientfile;99;fixobject;86;object;76;properties;62;string;3;ageint;10;1234567890string;4;namestring;10;1234567890";
    clientfile1.set_string(CF_NAME, "1234567890");
    result = clientfile1.serialize();
    BOOST_REQUIRE_EQUAL(expect, result);
}

BOOST_AUTO_TEST_CASE(vpfixobject_deserialize)
{
    vpfixobject o;
    clientfile clientfile1;
    int expectn, resultn;
    string expects, results;
    vptype *expectvpt, *resultvpt;

    expectn = 1234567890;
    expects = "1234567890";
    expectvpt = nullptr;

    o.deserialize("fixobject;86;object;76;properties;62;string;3;ageint;10;1234567890string;4;namestring;10;1234567890");
    resultn = o.read_int(CF_AGE);
    BOOST_REQUIRE_EQUAL(expectn, resultn);
    results = o.read_string(CF_NAME);
    BOOST_REQUIRE_EQUAL(expects, results);

    clientfile1.deserialize("clientfile;82;fixobject;69;object;59;properties;45;string;3;ageint;10;1234567890string;4;name;0;");
    resultn = clientfile1.read_int(CF_AGE);
    BOOST_REQUIRE_EQUAL(expectn, resultn);
    resultvpt = clientfile1.get(CF_NAME);
    BOOST_REQUIRE_EQUAL(expectvpt, resultvpt);

    clientfile1.deserialize("clientfile;99;fixobject;86;object;76;properties;62;string;3;ageint;10;1234567890string;4;namestring;10;1234567890");
    resultn = clientfile1.read_int(CF_AGE);
    BOOST_REQUIRE_EQUAL(expectn, resultn);
    results = clientfile1.read_string(CF_NAME);
    BOOST_REQUIRE_EQUAL(expects, results);
}

BOOST_AUTO_TEST_SUITE_END()
