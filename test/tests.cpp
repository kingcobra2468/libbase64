#define CATCH_CONFIG_MAIN
#include <base64/base64.hpp>
#include <catch.hpp>
#include <string>

TEST_CASE("Base64 string encode: 1", "[encode]")
{
    REQUIRE_THAT(base64::base64_encode("test"), Catch::Matchers::Equals("dGVzdA=="));
}

TEST_CASE("Base64 string encode: 2", "[encode]")
{
    REQUIRE_THAT(base64::base64_encode("This is a sentence. Special chars !@#$%^&*()"),
                 Catch::Matchers::Equals("VGhpcyBpcyBhIHNlbnRlbmNlLiBTcGVjaWFsIGNoYXJzICFAIyQlXiYqKCk="));
}

TEST_CASE("Base64 string decode: 1", "[decode]")
{
    REQUIRE_THAT(base64::base64_decode("VGhpcyBpcyBhIHNlbnRlbmNlLiBTcGVjaWFsIGNoYXJzICFAIyQlXiYqKCk="),
                 Catch::Matchers::Equals("This is a sentence. Special chars !@#$%^&*()"));
}

TEST_CASE("Base64 string decode: 2", "[decode]")
{
    REQUIRE_THAT(base64::base64_decode("dGVzdA=="),
                 Catch::Matchers::Equals("test"));
}