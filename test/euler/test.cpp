#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <thread>
#include <vector>

#include <EulerAngles.h>

class EulerAnglesFilterTest : public ::testing::Test
{
protected:
    EulerAnglesFilterTest() {}
    virtual ~EulerAnglesFilterTest() {}
    virtual void SetUp() override
    {
        srand(time(NULL));
    }
    virtual void TearDown() override
    {
    }

    // 產生隨機浮點數 [0.0,1.0]
    inline double randf()
    {
        return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    }

    // 產生隨機弧度 [-π, π]
    inline double randRad()
    {
        return M_PIx2 * randf() - M_PI;
    }

    EulerAngles e1;
    EulerAngles e2;
};

// 在任意一個值上增減 2π 並不會改變旋轉狀態
// (x1, y1, z1) -> (x1 + 2nπ, y1 + 2mπ, z1 + 2oπ), n,m,o 皆為整數
TEST_F(EulerAnglesFilterTest, PlusNPi)
{
    for (int i = 0; i < 1000; i++)
    {
        double x1 = randRad();
        double y1 = randRad();
        double z1 = randRad();
        double x2 = x1 + M_PIx2 * (rand() % 100);
        double y2 = y1 + M_PIx2 * (rand() % 100);
        double z2 = z1 + M_PIx2 * (rand() % 100);

        e1.Set(x1, y1, z1);
        e2.Set(x2, y2, z2);

        ASSERT_TRUE(e1.Equals(e2)) << e1 << ", " << e2;
    }
}

// 當 Y 為 π/2 (90度) 時， X 與 Z 會造成同樣方向的旋轉
// (x1, π/2, z1) -> (x1 - n, π/2, z1 + n), n 為實數
TEST_F(EulerAnglesFilterTest, WhileYisHalfPi)
{
    for (int i = 0; i < 1000; i++)
    {
        double x1 = randRad();
        double y1 = M_PI_2;
        double z1 = randRad();
        double n = randRad();
        double x2 = x1 - n;
        double y2 = M_PI_2;
        double z2 = z1 + n;

        e1.Set(x1, y1, z1);
        e2.Set(x2, y2, z2);

        ASSERT_TRUE(e1.Equals(e2)) << e1 << ", " << e2;
    }
}

// 當 Y 為 -π/2 (-90度) 時， X 與 Z 會造成同反方向的旋轉
// (x1, -π/2, z1) -> (x1 - n, -π/2, z1 - n), n 為實數
TEST_F(EulerAnglesFilterTest, WhileYisNegHalfPi)
{
    for (int i = 0; i < 1000; i++)
    {
        double x1 = randRad();
        double y1 = -M_PI_2;
        double z1 = randRad();
        double n = randRad();
        double x2 = x1 - n;
        double y2 = -M_PI_2;
        double z2 = z1 - n;

        e1.Set(x1, y1, z1);
        e2.Set(x2, y2, z2);

        ASSERT_TRUE(e1.Equals(e2)) << e1 << ", " << e2;
    }
}

// 當 Y2 = π - Y1, X2 = X1 + π, Z2 = Z1 - π 時代表相同的歐拉角
// (x1, y1, z1) -> (x1 + 180, -y1 + 180, z1 - 180)
TEST_F(EulerAnglesFilterTest, SpecialPiOperate)
{
    for (int i = 0; i < 1000; i++)
    {
        double x1 = randRad();
        double y1 = randRad();
        double z1 = randRad();
        double n = randRad();
        double x2 = x1 + M_PI;
        double y2 = M_PI - y1;
        double z2 = z1 - M_PI;

        e1.Set(x1, y1, z1);
        e2.Set(x2, y2, z2);

        ASSERT_TRUE(e1.Equals(e2)) << e1 << ", " << e2;
    }
}
