#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <thread>
#include <vector>

#include <EulerAngles.h>
#include <Quaternion.h>

// 這個測試將使用 EulerAngles 與 Quaternion 互相測試隨機案例
// 多執行幾次這個測試來判斷 EulerAngles 的篩選方式有無錯誤

class UniteTest : public ::testing::Test
{
protected:
    UniteTest() {}
    virtual ~UniteTest() {}
    virtual void SetUp() override
    {
        srand(time(NULL));
        for (int i = 0; i < Steps; i++)
        {
            Degs[i] = StepDeg * static_cast<double>(i) + MinDeg;
        }
    }
    virtual void TearDown() override
    {
    }

    // 產生隨機浮點數 [0.0,1.0]
    inline double randf()
    {
        return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    }

    // 四捨五入至小數點下第六位
    inline double round6(double v)
    {
        return round(v * 1000000) / 1000000;
    }

    // 產生隨機弧度 [-π, π]
    inline double randRad()
    {
        return M_PIx2 * randf() - M_PI;
    }

    EulerAngles e1;
    EulerAngles e2;
    Quaternion q1;
    Quaternion q2;

    static constexpr const double MaxDeg = 720.0;
    static constexpr const double MinDeg = -720.0;
    static constexpr const double StepDeg = 30.0;
    static constexpr const int Steps = (MaxDeg - MinDeg) / StepDeg;
    double Degs[Steps];
};

TEST_F(UniteTest, RandomEulerAngles)
{

    for (int i = 0; i < 1000000; i++)
    {
        double x1 = Degs[rand() % Steps] * DegToRad;
        double y1 = Degs[rand() % Steps] * DegToRad;
        double z1 = Degs[rand() % Steps] * DegToRad;
        double x2 = Degs[rand() % Steps] * DegToRad;
        double y2 = Degs[rand() % Steps] * DegToRad;
        double z2 = Degs[rand() % Steps] * DegToRad;

        e1.Set(x1, y1, z1);
        e2.Set(x2, y2, z2);

        q1.FromEuler(e1);
        q2.FromEuler(e2);

        double angle = round6(q1.Angle(q2));
        bool eq = e1.Equals(e2);

        if (angle == 0.0)
        {
            ASSERT_TRUE(eq) << e1 << ", " << e2;
        }
        else
        {
            ASSERT_FALSE(eq) << e1 << ", " << e2;
        }
    }
}
