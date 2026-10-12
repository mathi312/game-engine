#pragma once
#include <cmath>
#include <iostream>
inline int g_failures = 0;
#define CHECK(cond) do { if (!(cond)) { std::cout << "FAIL " << __FILE__ << ':' << __LINE__ << "  " << #cond << std::endl; ++g_failures; } } while (0)
#define CHECK_NEAR(a, b) CHECK(std::fabs((a) - (b)) < 1e-4)
#define TEST_MAIN_END() do { if (g_failures == 0) std::cout << "ALL PASSED" << std::endl; return g_failures ? 1 : 0; } while (0)
