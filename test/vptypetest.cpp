#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <vapor/vptype.hpp>
//#include <boost/date_time/posix_time/posix_time.hpp>


using namespace std;
using namespace vapor;

class vptypetest: public vptype
{
public:
    vptypetest() {}
    vptypetest(const string& v) : _v(v) {}

    vptypetest operator=(const vptypetest& t)
    {
        _v = t._v;
        return *this;
    }

    friend bool operator==(const vptypetest&, const vptypetest&);
    friend std::ostream& operator<< (std::ostream&, const vptypetest&);

    virtual vparchive_t serialize() const throw(std::runtime_error)
    {
        return std::string(TYPE) + VPARCHIVE_TOKEN_SEP + boost::lexical_cast<std::string>(_v.length()) + VPARCHIVE_TOKEN_SEP + _v.c_str();
    }

    virtual void deserialize(const char *s) throw(std::runtime_error, std::out_of_range, std::invalid_argument)
    {
        std::pair<std::string, std::string> rs = vptype::split(s);
        if (rs.first != TYPE) throw std::invalid_argument("bad format");
        _v = rs.second;
    }

    VPTYPE_CLASS_DECL(typetest, vptypetest)

protected:
    string _v;
};

inline bool operator==(const vptypetest& l, const vptypetest& r)
{
    return l._v == r._v;
}

inline std::ostream& operator<< (std::ostream& os, const vptypetest& x)
{
    return os << x._v;
}

VPTYPE_CLASS_DEF(vptypetest)

BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(vptype_newfrom)
{
    const char *s;
    vptypetest *expect;
    std::pair<vptype *, const char *> result;

    s = "typetest;0;";
    expect = new vptypetest("");
    result = vptype::newfrom(s);
    BOOST_REQUIRE_EQUAL(*expect, *static_cast<vptypetest *>(result.first));
    BOOST_REQUIRE_EQUAL(s+strlen(s), result.second);
    delete expect;
    delete result.first;

    s = "typetest;1;A";
    expect = new vptypetest("A");
    result = vptype::newfrom(s);
    BOOST_REQUIRE_EQUAL(*expect, *static_cast<vptypetest *>(result.first));
    BOOST_REQUIRE_EQUAL(s+strlen(s), result.second);
    delete expect;
    delete result.first;

    s = ";0;";
    expect = nullptr;
    result = vptype::newfrom(s);
    BOOST_REQUIRE_EQUAL(expect, static_cast<vptypetest *>(result.first));
    BOOST_REQUIRE_EQUAL(s+strlen(s), result.second);
}

BOOST_AUTO_TEST_CASE(vptype_deserialize)
{
    pair<string, string> expect, result;
    char buf[2*INT8_MAX];
    string sbuf;

    memset(buf, '\0', sizeof(buf));
    try {
        result = vptype::split(buf);
        BOOST_FAIL("bad type shoud fail [" + result.first + "," + result.second + "]");
    }
    catch (invalid_argument ex) {}

    sbuf = string("void") + VPARCHIVE_TOKEN_SEP;
    memcpy(buf, sbuf.c_str(), sbuf.length());
    try {
        result = vptype::split(buf);
        BOOST_FAIL("bad type shoud fail [" + result.first + "," + result.second + "]");
    }
    catch (invalid_argument ex) {}

    //TODO add empty types, size and content

    expect = std::make_pair("type", "1234567890");
    sbuf = string("type") + VPARCHIVE_TOKEN_SEP + "10" + VPARCHIVE_TOKEN_SEP + "1234567890x";
    result = vptype::split(sbuf.c_str());
    BOOST_REQUIRE_EQUAL(expect.first, result.first);
    BOOST_REQUIRE_EQUAL(expect.second, result.second);
}

BOOST_AUTO_TEST_SUITE_END()

    /*size_t sz = 300;
    sz *= 1024;
    sz *= 1024;
    cout << "sz=" << sz << " caracteres" << endl;
    size_t sz64 = sz/sizeof(uint64_t);
    char *c1 = new char[sz];
    uint64_t *p1 = (uint64_t *)c1;

    boost::posix_time::ptime time1, time2, time3, time4;
    time1 = boost::posix_time::microsec_clock::local_time();

    char *c2 = new char[sz];
    memcpy(c2, c1, sz);

    time2 = boost::posix_time::microsec_clock::local_time();

    string string1(c1, sz);

    time3 = boost::posix_time::microsec_clock::local_time();

    uint64_t *p2 = new uint64_t[sz64];
    for (size_t i=0; i<sz64; i++) {
        p2[i] = p1[i];
    }

    time4 = boost::posix_time::microsec_clock::local_time();

    boost::posix_time::time_duration dur;
    dur = time2 - time1;
    cout << "memcpy: " << dur.total_milliseconds() << "ms" << endl;
    dur = time3 - time2;
    cout << "string : " << dur.total_milliseconds() << "ms" << endl;
    dur = time4 - time3;
    cout << "int64_t: " << dur.total_milliseconds() << "ms" << endl;

    delete c1;
    delete c2;
    delete p2;*/
