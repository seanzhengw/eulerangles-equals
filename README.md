# 等效歐拉角判斷

等效歐拉角有兩種判斷方式

1. 依照旋轉順序，直接篩選特殊角度組合
2. 使用四元數計算兩個歐拉角之間的旋轉角度

這裡歐拉角的順序為 XYZ

方法 1 寫在類別 [EulerAngles](include/EulerAngles.h) 中的成員函式

    bool EulerAngles::Equals(const EulerAngles &e2)

測試方式在 [test/euler/test.cpp](test/euler/test.cpp)

方法 2 則是在類別 [Quaternion](include/Quaternion.h) 中的成員函式

    // 從歐拉角轉為四元數
    void Quaternion::FromEuler(const EulerAngles &e)
    // 兩個四元數夾角
    double Quaternion::Angle(const Quaternion &q)

測試方式在 [test/quat/quat](test/quat/test.cpp)

另外為了避免方法 1 有篩選漏洞，另外寫了隨機歐拉角搭配四元數檢查是否相等的測試 [test/unite/test.cpp](test/unite/test.cpp)

## 建置

使用 CMake

    mkdir build && cd mkdir build
    cmake ..
    make
    make test
