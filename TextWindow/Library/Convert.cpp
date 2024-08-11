#include "Convert.h"
#include "Sort.h"

VECTOR EvoLib::Convert::ConvertColorInto255(const VECTOR& color)
{
    // カラー変数
    VECTOR rgb_255 = {};

    // パーセンテージ変数
    float percentage = 0.0f;

    // 赤
    {
        percentage = static_cast<float>(PercentageRate(1.0f, color.x));

        rgb_255.x = static_cast<float>(ConvertValueToPercent(255, percentage));
    }
    // 緑
    {
        percentage = static_cast<float>(PercentageRate(1.0f, color.y));


        rgb_255.y = static_cast<float>(ConvertValueToPercent(255, percentage));
    }
    // 青
    {
        percentage = static_cast<float>(PercentageRate(1.0f, color.z));


        rgb_255.z = static_cast<float>(ConvertValueToPercent(255, percentage));
    }

    // カラー変数を返す
    return rgb_255;
}

int EvoLib::Convert::PercentageRate(const float& maxValue, const float& convertValue)
{
    // パーセントの小数値を求める
    const float decimal = convertValue / maxValue;

    // パーセントに変換
    const int percentage = static_cast<int>(decimal * 100);

    // パーセントを返す
    return percentage;
}

int EvoLib::Convert::ConvertValueToPercent(const int& maxValue, const float& percentage)
{
    // パーセンテージに対する値計算
    const int convertValue = static_cast<int>(maxValue * percentage * 0.01);

    // 変換値を返す
    return convertValue;
}

int EvoLib::Convert::ConvertFromPercentToValue(const int& maxValue, const float& percentage)
{
    // パーセントを小数に変換
    const float decimal = percentage * 0.01f;

    // 値を求める
    const int value = static_cast<int>(maxValue * decimal);

    // 値を返す
    return value;
}

float EvoLib::Convert::ConvertAngleToRadian(const float& angle)
{
    // 角度をラジアンに変換
    const float radian = angle * (DX_PI_F / 180.0f);

    // ラジアンを返す
    return radian;
}

float EvoLib::Convert::ConvertRadianToAngle(const float& radian)
{
    // ラジアンから角度に変換
    const float angle = radian * (180.0f / DX_PI_F);

    // 角度を返す
    return angle;
}

float EvoLib::Convert::ConvertDirectionToAngle(const Direction& direction)
{
    // 向き角度
    float directionAngle = 0.0f;

    // 向きによって代入する角度を変更する
    switch (direction)
    {
    case Direction::Top:

        directionAngle = TopAngle;
        break;
    case Direction::Bottom:

        directionAngle = BottomAngle;
        break;
    case Direction::Left:

        directionAngle = LeftAngle;
        break;
    case Direction::Right:

        directionAngle = RightAngle;
        break;
    default:
        break;
    }

    // 方向角度を返す
    return directionAngle;
}

Direction EvoLib::Convert::ConvertAngleToDirection(const float& angle, const float addSubValue)
{
    // 角度情報
    float directionAngle[5];

    directionAngle[0] = RightAngle;
    directionAngle[1] = BottomAngle;
    directionAngle[2] = LeftAngle;
    directionAngle[3] = TopAngle;
    directionAngle[4] = 360.0f;


    // 方向情報
    Direction direction;

    for (int i = 0; i < 5; i++)
    {
        if (EvoLib::Calculation::IsTargetRangeValue(angle, directionAngle[i], addSubValue))
        {
            switch (i)
            {
            case 0:
                direction = Direction::Right;
                break;
            case 1:
                direction = Direction::Bottom;
                break;
            case 2:
                direction = Direction::Left;
                break;
            case 3:
                direction = Direction::Top;
                break;
            case 4:
                direction = Direction::Right;
                break;
            default:
                break;
            }

            break;
        }
    }

    // 方向情報を返す
    return direction;
}

int EvoLib::Convert::ConvertFrameToSeconds(const int& frame, const int& fps)
{
    // 秒
    int second = 0;

    if (fps == 0)
    {
        second = frame / EvoLib::FPS::Fps;
    }
    else
    {
        second = frame / fps;
    }

    // 秒数を返す
    return second;
}

float EvoLib::Convert::ConvertFrameToSeconds_Revision(const int& frame, bool isInteger, int fps)
{
    // 秒
    float second = 0;

    // FPSを考慮して計算する
    if (fps == 0)
    {
        second = static_cast<float>(frame / EvoLib::FPS::Fps);
    }
    else
    {
        second = static_cast<float>(frame / fps);
    }

    // 整数値フラグがtrueの場合、整数値を返す
    if (isInteger)
    {
        // 整数値へ変換
        const int integerNum = static_cast<int> (second);

        return static_cast<float> (integerNum);
    }

    // 秒数を返す
    return second;
}

Sphere EvoLib::Convert::ConvertSphereInfo(const VECTOR& pos, const float& radius)
{
    // 球情報
    const Sphere sphere = { pos, radius };

    // 球情報を返す
    return sphere;
}

float EvoLib::Convert::ConvertingStringToFloat(const std::string& stringNum)
{
    // string型の数字をfloat型に変換する
    const float num = std::stof(stringNum);

    // 値を返す
    return num;
}

std::string EvoLib::Convert::ConvertingFloatToString(const float& num)
{
    // float型をstring型に変換
    const std::string stringNum = std::to_string(num);

    // 変換したstring型の数字を返す
    return stringNum;
}

int EvoLib::Convert::ConvertFrameCountToMillisecondUnit(const int& frame)
{
    // フレーム数から秒数を求める
    const float seconds = ConvertFrameToSeconds_Revision(frame);

    // 秒数からミリ秒単位を求める
    int millisecondUnit = static_cast<int>(seconds * 1000.0f);

    // ミリ秒単位を返す
    return millisecondUnit;
}

Cell EvoLib::Convert::PosToCell(const Vec2& pos, const float& cellSize)
{
    // 座標変数
    Cell cell = Cell();

    // セルを求める
    cell.x = static_cast<int>(pos.x / cellSize);
    cell.y = static_cast<int>(pos.y / cellSize);

    // セルを返す
    return cell;
}

Vec2 EvoLib::Convert::CellToPos(const Cell& cell, const float& cellSize)
{
    // 座標変数
    Vec2 pos = Vec2();

    // 座標を求める
    pos.x = (cell.x * cellSize) + (cellSize * 0.5f);
    pos.y = (cell.y * cellSize) + (cellSize * 0.5f);

    // 座標を返す
    return pos;
}

Line EvoLib::Convert::CalculateLine(const Vec2& pos1, const Vec2& pos2)
{
    // 直線変数
    Line line = Line();

    
    // 傾きを求める
    line.a = (pos2.y - pos1.y) / (pos2.x - pos1.x);
    // Y軸とこ交点を求める
    line.b = pos1.y - line.a * pos1.x;
    
  
    // 直線情報を返す
    return line;
}

Intersection EvoLib::Convert::CalculateIntersection(const Line& line1, const Line& line2)
{
    // 交差の構造体変数
    Intersection intersection = Intersection();


    // 傾きが同じ場合、交点は存在しない
    if (line1.a == line2.a)
    {
        return intersection;
    }

    // 交点が存在するので、フラグをtrueにする
    intersection.isFrag = true;

    // 交点のx座標を計算
    intersection.pos.x = (line2.b - line1.b) / (line1.a - line2.a);

    // 交点のy座標を計算
    intersection.pos.y = line1.a * intersection.pos.x + line1.b;


    // 交差情報を返す
    return intersection;
}

Vec2 EvoLib::Convert::QuadrangularCenter(const Square& square)
{
    // 直線を2点から計算
    const Line line1 = CalculateLine(square.A, square.C);
    const Line line2 = CalculateLine(square.B, square.D);

    // 2つの直線交点情報を取得
    const Intersection intersection = CalculateIntersection(line1, line2);

    // 中心点
    Vec2 centerPos = Vec2();

    // 直線が交差してなければ、ここで処理を終了する
    if (!intersection.isFrag)
    {
        return centerPos;
    }

    // 中心点を代入
    centerPos = intersection.pos;

    // 中心座標を返す
    return centerPos;
}

Circle EvoLib::Convert::SquareToCircle(const Square& square)
{
    // 直線を2点から計算
    const Line line1 = EvoLib::Convert::CalculateLine(square.A, square.C);
    const Line line2 = EvoLib::Convert::CalculateLine(square.B, square.D);

    // 2つの直線交点情報を取得
    const Intersection intersection = CalculateIntersection(line1, line2);

    // 円情報
    Circle circle;

    // 直線が交差してなければ、ここで処理を終了する
    if (!intersection.isFrag)
    {
        return circle;
    }

    // 距離
    std::vector<float>range;

    // 値を代入
    range.push_back(EvoLib::Calculation::ThreeSquareTheorem(square.A, intersection.pos));
    range.push_back(EvoLib::Calculation::ThreeSquareTheorem(square.B, intersection.pos));
    range.push_back(EvoLib::Calculation::ThreeSquareTheorem(square.C, intersection.pos));
    range.push_back(EvoLib::Calculation::ThreeSquareTheorem(square.D, intersection.pos));

    // 数値が小さい順になるよう、ソートを行う
    Sort::SelectionSort(range, static_cast<int>(range.size()));



    // 円の中心点を代入
    circle.centerPos = intersection.pos;
    // 半径を代入
    circle.radius = range.back();

    // 円情報を返す
    return circle;
}

Square EvoLib::Convert::RectToSquare(const Rect& rect)
{
    // 四角形情報
    Square square = Square();

    // 四角形情報を計算
    {
        square.A = Vec2(rect.left, rect.top);
        square.B = Vec2(rect.right, rect.top);
        square.C = Vec2(rect.right, rect.bottom);
        square.D = Vec2(rect.left, rect.bottom);
    }

    // 四角形情報を返す
    return square;
}

Rect EvoLib::Convert::PosToRect(const Vec2& pos, const Vec2& size)
{
    // 矩形変数
    Rect rect = Rect();

    // 矩形情報を計算
    rect.top = pos.y - (size.y * 0.5f);
    rect.bottom = pos.y + (size.y * 0.5f);
    rect.left = pos.x - (size.x * 0.5f);
    rect.right = pos.x + (size.x * 0.5f);

    // 計算した矩形を返す
    return rect;
}

bool EvoLib::Convert::ConvertStringToBool(const std::string& str)
{
    bool isFlag = false;

    if (str == "FALSE" ||
        str == "false")
    {
        isFlag = false;
    }
    else if (
        str == "TRUE" ||
        str == "true")
    {
        isFlag = true;
    }
    else
    {

        EvoLib::Assert::ErrorMessageBox("ConvertStringToBoolで変換する際、スペルミスがあったようです。");
    }

    return isFlag;
}

std::string EvoLib::Convert::WStringToString(const std::wstring& wstr)
{
    // wstring → SJIS
    int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, wstr.c_str()
        , -1, (char*)NULL, 0, NULL, NULL);

    // バッファの取得
    CHAR* cpMultiByte = new CHAR[iBufferSize];

    // wstring → SJIS
    WideCharToMultiByte(CP_OEMCP, 0, wstr.c_str(), -1, cpMultiByte
        , iBufferSize, NULL, NULL);

    // stringの生成
    std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);

    // バッファの破棄
    delete[] cpMultiByte;

    // 変換結果を返す
    return(oRet);
}

std::wstring EvoLib::Convert::StringToWString(const std::string& str)
{
    // string → wstring
    int iBufferSize = MultiByteToWideChar(CP_OEMCP, 0, str.c_str(), -1, nullptr, 0);

    // バッファの取得
    WCHAR* wpWideChar = new WCHAR[iBufferSize];

    // string → wstring
    MultiByteToWideChar(CP_OEMCP, 0, str.c_str(), -1, wpWideChar, iBufferSize);

    // wstringの生成
    std::wstring oRet(wpWideChar, wpWideChar + iBufferSize - 1);

    // バッファの破棄
    delete[] wpWideChar;

    // 変換結果を返す
    return oRet;
}

