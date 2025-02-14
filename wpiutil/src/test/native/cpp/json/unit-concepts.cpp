/*----------------------------------------------------------------------------*/
/* Modifications Copyright (c) FIRST 2017. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
/*
    __ _____ _____ _____
 __|  |   __|     |   | |  JSON for Modern C++ (test suite)
|  |  |__   |  |  | | | |  version 2.1.1
|_____|_____|_____|_|___|  https://github.com/nlohmann/json

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
Copyright (c) 2013-2017 Niels Lohmann <http://nlohmann.me>.

Permission is hereby  granted, free of charge, to any  person obtaining a copy
of this software and associated  documentation files (the "Software"), to deal
in the Software  without restriction, including without  limitation the rights
to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "unit-json.h"

#include <gtest/gtest.h>

using wpi::json;

TEST(JsonConceptsTest, ContainerRequirements)
{
    // X: container class: json
    // T: type of objects: json
    // a, b: values of type X: json

    // TABLE 96 - Container Requirements

    // X::value_type must return T
    EXPECT_TRUE((std::is_same<json::value_type, json>::value));

    // X::reference must return lvalue of T
    EXPECT_TRUE((std::is_same<json::reference, json&>::value));

    // X::const_reference must return const lvalue of T
    EXPECT_TRUE((std::is_same<json::const_reference, const json&>::value));

    // X::iterator must return iterator whose value_type is T
    EXPECT_TRUE((std::is_same<json::iterator::value_type, json>::value));
    // X::iterator must meet the forward iterator requirements
    EXPECT_TRUE((std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<json::iterator>::iterator_category>::value));
    // X::iterator must be convertible to X::const_iterator
    EXPECT_TRUE((std::is_convertible<json::iterator, json::const_iterator>::value));

    // X::const_iterator must return iterator whose value_type is T
    EXPECT_TRUE((std::is_same<json::const_iterator::value_type, json>::value));
    // X::const_iterator must meet the forward iterator requirements
    EXPECT_TRUE((std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<json::const_iterator>::iterator_category>::value));

    // X::difference_type must return a signed integer
    EXPECT_TRUE((std::is_signed<json::difference_type>::value));
    // X::difference_type must be identical to X::iterator::difference_type
    EXPECT_TRUE((std::is_same<json::difference_type, json::iterator::difference_type>::value));
    // X::difference_type must be identical to X::const_iterator::difference_type
    EXPECT_TRUE((std::is_same<json::difference_type, json::const_iterator::difference_type>::value));

    // X::size_type must return an unsigned integer
    EXPECT_TRUE((std::is_unsigned<json::size_type>::value));
    // X::size_type can represent any non-negative value of X::difference_type
    EXPECT_TRUE(static_cast<json::size_type>(std::numeric_limits<json::difference_type>::max()) <=
          std::numeric_limits<json::size_type>::max());

    // the expression "X u" has the post-condition "u.empty()"
    {
        json u;
        EXPECT_TRUE(u.empty());
    }

    // the expression "X()" has the post-condition "X().empty()"
    EXPECT_TRUE(json().empty());
}

TEST(JsonConceptsTest, DefaultConstructible)
{
    EXPECT_TRUE(std::is_nothrow_default_constructible<json>::value);
}

TEST(JsonConceptsTest, MoveConstructible)
{
    EXPECT_TRUE(std::is_nothrow_move_constructible<json>::value);
}

TEST(JsonConceptsTest, CopyConstructible)
{
    EXPECT_TRUE(std::is_copy_constructible<json>::value);
}

TEST(JsonConceptsTest, MoveAssignable)
{
    EXPECT_TRUE(std::is_nothrow_move_assignable<json>::value);
}

TEST(JsonConceptsTest, CopyAssignable)
{
    EXPECT_TRUE(std::is_copy_assignable<json>::value);
}

TEST(JsonConceptsTest, Destructible)
{
    EXPECT_TRUE(std::is_nothrow_destructible<json>::value);
}

TEST(JsonConceptsTest, StandardLayoutType)
{
    EXPECT_TRUE(std::is_standard_layout<json>::value);
}

TEST(JsonIteratorConceptsTest, CopyConstructible)
{
    EXPECT_TRUE(std::is_nothrow_copy_constructible<json::iterator>::value);
    EXPECT_TRUE(std::is_nothrow_copy_constructible<json::const_iterator>::value);
}

TEST(JsonIteratorConceptsTest, CopyAssignable)
{
    // STL iterators used by json::iterator don't pass this test in Debug mode
#if !defined(_MSC_VER) || (_ITERATOR_DEBUG_LEVEL == 0)
    EXPECT_TRUE(std::is_nothrow_copy_assignable<json::iterator>::value);
    EXPECT_TRUE(std::is_nothrow_copy_assignable<json::const_iterator>::value);
#endif
}

TEST(JsonIteratorConceptsTest, Destructible)
{
    EXPECT_TRUE(std::is_nothrow_destructible<json::iterator>::value);
    EXPECT_TRUE(std::is_nothrow_destructible<json::const_iterator>::value);
}

TEST(JsonIteratorConceptsTest, Swappable)
{
    json j {1, 2, 3};
    json::iterator it1 = j.begin();
    json::iterator it2 = j.end();
    std::swap(it1, it2);
    EXPECT_EQ(it1, j.end());
    EXPECT_EQ(it2, j.begin());
}

TEST(JsonIteratorConceptsTest, SwappableConst)
{
    json j {1, 2, 3};
    json::const_iterator it1 = j.cbegin();
    json::const_iterator it2 = j.cend();
    std::swap(it1, it2);
    EXPECT_EQ(it1, j.end());
    EXPECT_EQ(it2, j.begin());
}
