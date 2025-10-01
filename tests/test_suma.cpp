#include "suma.hpp"
#include <gtest/gtest.h>

TEST(suma_test, positivos) { EXPECT_EQ(suma(2, 3), 5); }

TEST(suma_test, negativos) { EXPECT_EQ(suma(-2, -3), -5); }
