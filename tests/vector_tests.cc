#include <gtest/gtest.h>
#include <vector/vector.h>

using namespace std;

TEST(VectorTest, Test1) {
    int list1[]{ 1, 0 };
    auto v1 = Vector(list1, 2);
    EXPECT_EQ(v1[0], 1);
    EXPECT_EQ(v1[1], 0);
}

TEST(VectorTest, Test2) {
    float list1[]{ 1.31f, 0.1213f };
    auto v1 = Vector(list1, 2);
    EXPECT_EQ(v1[0], 1.31f);
    EXPECT_EQ(v1[1] , 0.1213f);
}

TEST(VectorTest, Test3) {
    double list1[]{ 1.22321, 0.214241 };
    auto v1 = Vector(list1, 2);
    EXPECT_EQ(v1[0], 1.22321);
    EXPECT_EQ(v1[1], 0.214241);
}

TEST(VectorTest, Test4) {
    complex<float> list1[]{ complex(3.0f, 1.0f), complex(4.0f, 5.0f) };
    auto v1 = Vector(list1, 2);
    EXPECT_EQ(v1[0], complex(3.0f, 1.0f));
    EXPECT_EQ(v1[1], complex(4.0f, 5.0f));
}

TEST(VectorTest, Test5) {
    complex<double> list1[]{ complex(3.123123, 1.123231), complex(4.123123, 5.32423) };
    auto v1 = Vector(list1, 2);
    EXPECT_EQ(v1[0], complex(3.123123, 1.123231));
    EXPECT_EQ(v1[1], complex(4.123123, 5.32423));
}

TEST(VectorTest, Test6) {
    int list1[]{ 1, 0 };
    auto v1 = Vector(list1, 2);
    EXPECT_EQ(v1.get_size(), 2);
}

TEST(VectorTest, Test7) {
    int list1[]{ 1, 0 };
    auto v1 = Vector(list1, 2);
    auto v2 = Vector(v1);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 0);
}

TEST(VectorTest, Test8) {
    int list1[]{ 1, 0 };
    EXPECT_ANY_THROW(auto v1 = Vector(list1, -1));
}

TEST(VectorTest, Test9) {
    int list1[]{ 3, 4 };
    auto v1 = Vector(list1, 2);
    EXPECT_EQ(v1.abs(), 5);
}

TEST(VectorTest, Test10) {
    float list1[]{ 3.0f, 4.0f };
    auto v1 = Vector(list1, 2);
    EXPECT_EQ(float(v1.abs()), 5.0);
}

//TEST(VectorTest, Test11) {
//    complex<float> list1[]{ complex(3.0f, 1.0f), complex(4.0f, 5.0f) };
//    auto v1 = Vector(list1, 2);
//    EXPECT_EQ(float(v1.abs()), complex(7.0f, 19.0f));
//}

TEST(VectorTest, Test12) {
    float list1[]{ 4.0f, 4.0f };
    float list2[]{ 7.0f, 3.0f };
    auto v1 = Vector(list1, 2);
    auto v2 = Vector(list2, 2);
    v1 += v2;
    EXPECT_EQ(v1[0], 11.0);
    EXPECT_EQ(v1[1], 7.0);
}

TEST(VectorTest, Test13) {
    float list1[]{ 4.0f, 4.0f };
    float list2[]{ 7.0f, 3.0f };
    auto v1 = Vector(list1, 2);
    auto v2 = Vector(list2, 2);
    v1 -= v2;
    EXPECT_EQ(v1[0], -3.0);
    EXPECT_EQ(v1[1], 1.0);
}

TEST(VectorTest, Test14) {
    float list1[]{ 4.0f, 4.0f };
    float list2[]{ 7.0f, 3.0f };
    auto v1 = Vector(list1, 2);
    auto v2 = Vector(list2, 2);
    auto v3 = v1 + v2;
    EXPECT_EQ(v3[0], 11.0);
    EXPECT_EQ(v3[1], 7.0);
}

TEST(VectorTest, Test15) {
    float list1[]{ 4.0f, 4.0f };
    float list2[]{ 7.0f, 3.0f };
    auto v1 = Vector(list1, 2);
    auto v2 = Vector(list2, 2);
    auto v3 = v1 - v2;
    EXPECT_EQ(v3[0], -3.0);
    EXPECT_EQ(v3[1], 1.0);
}

TEST(VectorTest, Test16) {
    float list1[]{ 4.0f, 3.0f };
    auto v1 = Vector(list1, 2);
    v1 *= 3;
    EXPECT_EQ(v1[0], 12.0);
    EXPECT_EQ(v1[1], 9.0);
}

TEST(VectorTest, Test17) {
    float list1[]{ 4.0f, 3.0f };
    auto v1 = Vector(list1, 2);
    v1 /= 3;
    EXPECT_EQ(v1[0], float(4)/3);
    EXPECT_EQ(v1[1], 1.0);
}

TEST(VectorTest, Test18) {
    float list1[]{ 2.0f, 4.0f };
    auto v1 = Vector(list1, 2);
    auto v2 = v1 * 5;
    EXPECT_EQ(v2[0], 10.0);
    EXPECT_EQ(v2[1], 20.0);
}

TEST(VectorTest, Test19) {
    float list1[]{ 2.0f, 4.0f };
    auto v1 = Vector(list1, 2);
    auto v2 = v1 / 5;
    EXPECT_EQ(v2[0], 0.4f);
    EXPECT_EQ(v2[1], 0.8f);
}

TEST(VectorTest, Test20) {
    float list1[]{ 2.0f, 4.0f };
    auto v1 = Vector(list1, 2);
    auto v2 = 5.0f * v1;
    EXPECT_EQ(v2[0], 10.0);
    EXPECT_EQ(v2[1], 20.0);
}

TEST(VectorTest, Test21) {
    float list1[]{ 4.0f, 4.0f };
    float list2[]{ 7.0f, 3.0f };
    auto v1 = Vector(list1, 2);
    auto v2 = Vector(list2, 2);
    EXPECT_EQ(v1 == v2, false);
}

TEST(VectorTest, Test22) {
    float list1[]{ 4.0f, 3.0f };
    float list2[]{ 4.0f, 3.0f };
    auto v1 = Vector(list1, 2);
    auto v2 = Vector(list2, 2);
    EXPECT_EQ(v1 == v2, true);
}

TEST(VectorTest, Test23) {
    float list1[]{ 1.0f, 3.0f };
    float list2[]{ 3.0f, 2.0f };
    auto v1 = Vector(list1, 2);
    auto v2 = Vector(list2, 2);
    auto v3 = v1 * v2;
    EXPECT_EQ(v3, 9.0f);
}

TEST(VectorTest, Test24) {
    float list1[]{ 4.0f, 4.0f };
    auto v1 = Vector(list1, 2);
    cout <<"Operator <<" << endl << v1 << endl;
}

TEST(VectorTest, Test25) {
    float list1[]{ 2.0f, 0.0f };
    float list2[]{ 0.0f, 2.0f };
    auto v1 = Vector(list1, 2);
    auto v2 = Vector(list2, 2);
    auto v3 = bis(v1, v2);
    EXPECT_EQ(v3[0], 1.0f);
    EXPECT_EQ(v3[1], 1.0f);
}

TEST(VectorTest, Test26) {
    float list1[]{ 5.0f, 2.0f };
    float list2[]{ 1.0f, 4.0f };
    auto v1 = Vector(list1, 2);
    auto v2 = Vector(list2, 2);
    auto v3 = bis(v1, v2);
    EXPECT_EQ(v3[0], 2.73453);
    EXPECT_EQ(v3[1], 3.13273);
}

