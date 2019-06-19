//
// Created by frenchcommando on 6/7/2019.
//

#include <gtest/gtest.h>
#include <string>
#include <exchange.h>


TEST(book_check, test_book){
    std::string s = "09:30:00 1 b 100 l 9.99\n"
                    "09:31:00 2 b 1000 l 9.95\n"
                    "09:32:00 3 s 100 l 10.01\n"
                    "09:33:00 4 s 1000 l 10.05\n"
                    "09:41:00 5 b 200 m 10.02";
    auto b = Book::build_from_string(s);
    auto bb = b.view_order();
    EXPECT_EQ(s, bb);
}

TEST(book_check, test_book_execs){
    std::string s = "09:30:00 1 b 100 l 9.99\n"
                    "09:31:00 2 b 1000 l 9.95\n"
                    "09:32:00 3 s 100 l 10.01\n"
                    "09:33:00 4 s 1000 l 10.05\n"
                    "09:41:06 5 b 200 m 10.02";
    std::string ss = "09:41:00 5 3 10.01 100\n"
                     "09:41:00 5 4 10.05 100";
    const auto b = Book::build_from_string(s);
    auto bb = b.view_execs();
    EXPECT_EQ(ss, bb);
}
