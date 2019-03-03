#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <thread>
#include <vector>

#include <EulerAngles.h>

class EulerAnglesSimplifyTest : public ::testing::Test
{
protected:
    EulerAnglesSimplifyTest() {}
    virtual ~EulerAnglesSimplifyTest() {}
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

    static constexpr const double MaxDeg = 720.0;
    static constexpr const double MinDeg = -720.0;
    static constexpr const double StepDeg = 30.0;
    static constexpr const int Steps = (MaxDeg - MinDeg) / StepDeg;
    double Degs[Steps];
};

TEST_F(EulerAnglesSimplifyTest, RandomEulerAngles)
{
    for (int i = 0; i < 1000000; i++)
    {
        double x = Degs[rand() % Steps] * DegToRad;
        double y = Degs[rand() % Steps] * DegToRad;
        double z = Degs[rand() % Steps] * DegToRad;

        e1.Set(x, y, z);
        e2.Set(x, y, z);
        e2.Simplify();
        
        ASSERT_TRUE(e1.Equals(e2)) << e1 << ", " << e2;
    }
}
