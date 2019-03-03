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

# 歐拉角化簡

在完成特殊角度組合篩選之後，可以再依照這個篩選條件設計一個化簡歐拉角的固定模式，同樣以順序 XYZ 的歐拉角為例，可以歸納出這樣的化簡方式：

1. 將 Y 轉換為在範圍 (-π, π] 內的同界角
2. 若 Y 是 π/2 則 X = X + Z, Z = 0, 並將 X 轉換為在範圍 (-π, π] 內的同界角，得化簡的歐拉角。
3. 若 Y 是 -π/2 則 X = X - Z, Z = 0, 並將 X 轉換為在範圍 (-π, π] 內的同界角，得化簡的歐拉角。
4. 若 |Y| > π/2 則 Y = π - Y, X = X + π, Z = Z - π, 並將 X, Y, Z 轉換為在範圍 (-π, π] 內的同界角，得化簡的歐拉角。
5. 若沒有條件符合，將 X, Z 轉換為在範圍 (-π, π] 內的同界角，得化簡的歐拉角。
