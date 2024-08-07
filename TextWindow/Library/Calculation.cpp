#include "Calculation.h"

int EvoLib::Calculation::SineCurve(int currentFrame, int maxFrame, int maxValue, bool isAbs)
{
    // ABSを使用する場合、最大フレームを２倍する
    if (isAbs)
    {
        maxFrame *= 2;
    }

    // 現在のフレームを最大フレームで割る
    currentFrame %= maxFrame;

    // サイン値を求める
    int sinValue = static_cast<int>(sin(DX_PI_F * 2.0f / maxFrame * currentFrame) * maxValue);

    // ABSを使用する場合、絶対値を求める
    if (isAbs)
    {
        // 絶対値を求める
        sinValue = std::abs(sinValue);
    }

    // サイン値を返す
    return sinValue;
}

Vec2 EvoLib::Calculation::VibrationValue(int currentFrame, const int& maxFrame, const int& vibrationWidth)
{
    // 現在のフレームに最大フレームから現在のフレームを引いた値を代入する
    currentFrame = maxFrame - currentFrame;

    // 現在のフレームが０以下だった場合、0を代入
    if (currentFrame <= 0)
    {
        currentFrame = 0;
    }


    // x,yをマイナスするかしないか
    int x = GetRand(1);
    int y = GetRand(1);

    // パーセンテージを求める
    const float percentage = static_cast<float>(EvoLib::Convert::PercentageRate(static_cast<float>(maxFrame), static_cast<float>(currentFrame)));

    // 小数化
    const float decimal = percentage * 0.01f;

    // 振動幅(計算)
    int afterVibrationWidth = static_cast<int>(vibrationWidth * decimal);


    Vec2 vibrationPos = {};


    // ランダム値で座標を変換する
    vibrationPos.x = static_cast<float>(GetRand(afterVibrationWidth));
    vibrationPos.y = static_cast<float>(GetRand(afterVibrationWidth));


    // x or yが0の時、位置をマイナスする
    if (x == 0)vibrationPos.x *= -1;
    if (y == 0)vibrationPos.y *= -1;

    // 振動値を返す
    return vibrationPos;
}

int EvoLib::Calculation::SelectLoopNumber(const int& minNumber, const int& maxNumber, const int& currentNumber, bool isInverseLoop)
{
    // 現在の番号を代入
    int number = currentNumber;

    // 逆ループするかどうかで処理を変更する
    if (isInverseLoop)
    {
        // 現在の選択項目を一つ上にずらす(逆ループする)
        number = (currentNumber + (maxNumber - 1)) % maxNumber;
    }
    else
    {
        // 現在の選択項目を一つ下にずらす(ループする)
        number = (currentNumber + 1) % maxNumber;
    }

    // 求めた番号を返す
    return number;
}

std::vector<Vec2> EvoLib::Calculation::GraphicWidthCoordinate(const int& handle, const int& num, const float& graphScale, const Vec2& centerPos, const Vec2& distancePos, bool isSide)
{
    // 座標
    std::vector<Vec2> pos;

    // グラフィックの個数分、座標変数を増やす
    pos.resize(num);

    // 一時的なグラフィックのサイズ格納変数
    int sizeX = 0;
    int sizeY = 0;

    // グラフィックサイズを取得
    GetGraphSize(handle, &sizeX, &sizeY);

    // グラフィックのサイズ格納変数
    Vec2 size;

    // サイズを代入
    size.x = static_cast<float>(sizeX);
    size.y = static_cast<float>(sizeY);


    // 調整グラフィックサイズをかける
    size *= graphScale;
    size += distancePos;

    // 基準座標
    Vec2 basePos = {};

    // 偶数判定
    const bool isEvenNumber = (num % 2 == 0);

    // 偶数か奇数かでベース座標を変更する
    if (isEvenNumber)
    {
        basePos = centerPos;

        basePos -= (size * 0.5);
    }
    else
    {
        basePos = centerPos;
    }


    int n = num;

    if (isEvenNumber)
    {
        n--;
    }

    n /= 2;



    // 一時保存座標
    Vec2 savePos;

    // ナンバー変数
    int number = 0;

    // カウント変数
    int count = 0;

    for (int i = 0; i < num; i++)
    {
        // 一時保存座標にベース座標を代入
        savePos = basePos;

        // ナンバー変数初期化
        number = 0;

        // iが奇数が偶数かで代入する座標を変更する
        if (i % 2 == 0)
        {
            if (isSide)
            {
                savePos.x -= size.x * count;
            }
            else
            {
                savePos.y -= size.y * count;
            }

            number -= count;
        }
        else
        {
            if (isSide)
            {
                savePos.x += size.x * count;
            }
            else
            {
                savePos.y += size.y * count;
            }

            number += count;
        }

        // 座標代入
        pos[number + n] = savePos;

        if (i % 2 == 0)
        {
            count++;
        }
    }

    // 値を返す
    return pos;
}

std::vector<Vec2> EvoLib::Calculation::SortCoordinateEqually(const int& num, const Vec2& centerPos, const Vec2& distancePos, bool isSide)
{
    // 座標
    std::vector<Vec2> pos;

    // 座標の要素を増やす
    pos.resize(num);

    // サイズ変数に幅とする座標を代入する
    const Vec2 size = distancePos;

    // 基準座標
    Vec2 basePos = {};

    // 偶数判定
    const bool isEvenNumber = (num % 2 == 0);

    // 偶数か奇数かでベース座標を変更する
    if (isEvenNumber)
    {
        basePos = centerPos;

        basePos -= (size * 0.5);
    }
    else
    {
        basePos = centerPos;
    }


    int n = num;

    if (isEvenNumber)
    {
        n--;
    }

    n /= 2;



    // 一時保存座標
    Vec2 savePos;

    // ナンバー変数
    int number = 0;
    // カウント変数
    int count = 0;

    for (int i = 0; i < num; i++)
    {
        // 一時保存座標にベース座標を代入
        savePos = basePos;

        // ナンバー変数初期化
        number = 0;

        // iが奇数か偶数かで一時保存座標の値を変更する
        if (i % 2 == 0)
        {
            if (isSide)
            {
                savePos.x -= size.x * count;
            }
            else
            {
                savePos.y -= size.y * count;
            }

            number -= count;
        }
        else
        {
            if (isSide)
            {
                savePos.x += size.x * count;
            }
            else
            {
                savePos.y += size.y * count;
            }

            number += count;
        }

        // 座標代入
        pos[number + n] = savePos;

        if (i % 2 == 0)
        {
            count++;
        }
    }

    // 値を返す
    return pos;
}

bool EvoLib::Calculation::IsTargetRangeValue(const float& currentValue, const float& targetValue, const float& addSubValue)
{
    // 値を補正
    if (currentValue <= (targetValue + addSubValue) &&
        currentValue >= (targetValue - addSubValue))
    {
        // true判定を返す
        return true;
    }

    // false判定を返す
    return false;
}

float EvoLib::Calculation::AngleLimitValueNotExceedToCalculate(const float& currentAngle, const float& addSubValue, EvoLib::Calculation::CalculationType calculation, bool isInteger, bool isAdjustment)
{
    // 現在の角度を代入
    float angle = currentAngle;

    // 調整値
    float adjustmentValue = 0.0f;

    // 加算の場合、360度を超えないようにする
    if (calculation == CalculationType::Addition)
    {
        // 角度に加減算値を加える
        angle += addSubValue;

        if (angle >= 360.0f)
        {
            // アングルを0度にする
            angle = 0.0f;

            // 調整値に現在のアングルから360.0f引いた数を求める
            adjustmentValue = angle - 360.0f;
        }
    }
    // 減算の場合、0度を下回らないようにする
    else
    {
        // 角度を加減算値分減らす
        angle -= addSubValue;

        if (angle <= 0.0f)
        {
            // 調整値に現在のアングルを代入する
            adjustmentValue = angle;

            // アングルを360度にする
            angle = 360.0f;
        }
    }

    // 調整値を使用する場合、調整値分加算を行う
    if (isAdjustment)
    {
        // アングルを調整値分、加算する
        angle += adjustmentValue;
    }

    // 整数値フラグがtrueならば整数値を返す
    if (isInteger)
    {
        // 整数値へ変換
        const int integerNum = static_cast<int>(angle);

        // 求めた角度を返す
        return static_cast<float>(integerNum);
    }


    // 求めた角度を返す
    return angle;
}

float EvoLib::Calculation::ThreeSquareTheorem(const Vec2& poa1, const Vec2& pos2)
{
    // 一辺の長さ
    float length = 0.0f;

    // 2乗された、一辺の長さを求める
    length = std::powf(poa1.x - pos2.x, 2.0f)
        + std::powf(poa1.y - pos2.y, 2.0f);

    // 平方根を計算
    length = std::sqrtf(length);

    // 一辺の長さを返す
    return length;
}

int EvoLib::Calculation::InearInterpolationCount(const Vec2& pos, const Vec2& vec, const Vec2& size)
{
    // 移動量が0ならば、ここで処理を終了する
    if (vec.x == 0.0f &&
        vec.y == 0.0f)
    {
        return 0;
    }

    // 最小サイズを調べる
    float minSize = size.x;

    if (minSize > size.x)
    {
        minSize = size.y;
    }

    // 最大の移動量を求める
    float maxVec = std::abs(vec.x);

    if (maxVec < std::abs(vec.y))
    {
        maxVec = std::abs(vec.y);
    }


    const int iinearInterpolationCount =
        static_cast<int>(maxVec / minSize);

    return iinearInterpolationCount;
}

std::vector<Vec2> EvoLib::Calculation::InearInterpolationPos(const Vec2& pos, const Vec2& vec, const int& inearInterpolationCount)
{
    // 線形補間座標
    std::vector<Vec2>inearInterpolationPos;

    // 加算座標計算
    Vec2 addVec = Vec2();
    addVec.x = (vec.x / inearInterpolationCount);
    addVec.y = (vec.y / inearInterpolationCount);


    // 線形補間座標を計算
    for (int i = 1; i < inearInterpolationCount + 1; i++)
    {
        inearInterpolationPos.push_back(pos + (addVec * static_cast<float>(i)));
    }

    // 線形補間座標を返す
    return inearInterpolationPos;
}

Rect EvoLib::Calculation::CalculateRectangleMovementRange(const Rect& rect, const Cell& maxCell, const float& cellSize, const std::vector<std::vector<int>>& cellData, const std::vector<int> groundCellNumber)
{
    // 結果の矩形
    Rect result = Rect();

	// マップ全体を移動可能な状態で初期化
	result.top = 0.0f;
	result.bottom = (maxCell.y * cellSize) - (rect.bottom - rect.top) / 2.0f;
	result.left = 0.0f;
	result.right = (maxCell.x * cellSize) - (rect.right - rect.left) / 2.0f;


	// 判定対象の位置をマップチップのインデックスに変更
	const int indexMinX = static_cast<int>(rect.left / cellSize);
	const int indexMaxX = static_cast<int>((rect.right - 1) / cellSize);
	const int indexMinY = static_cast<int>(rect.top / cellSize);
	const int indexMaxY = static_cast<int>((rect.bottom - 1) / cellSize);

	// 上方向チェック
	for (int y = indexMinY; y >= 0; y--)
	{
		for (int x = indexMinX; x <= indexMaxX; x++)
		{
			if (!IsCellRange(Cell(x, y), Cell(maxCell.x, maxCell.x), Cell(0, 0)))
			{
				return Rect();
			}

            if (cellData[x][y] == 0)
            {
				continue;
			}

            bool isContinue = true;

            // 地面セル番号がある場合、そのセル番号は無視する
            for (auto& unused : groundCellNumber)
            {
				if (cellData[x][y] == unused)
				{
                    isContinue = false;
				}
            }

            if (isContinue)
            {
                continue;
            }



			// 一番最初に見つかったぶつかるマップチップの一番下Y座標を取る
			float temp = static_cast<float>(y * cellSize + cellSize);
			if (temp > result.top)
			{
				result.top = temp;
			}
		}
	}
	// 下方向チェック
	for (int y = indexMaxY; y < maxCell.y; y++)
	{
		for (int x = indexMinX; x <= indexMaxX; x++)
		{
			if (!IsCellRange(Cell(x, y), Cell(maxCell.x, maxCell.x), Cell(0, 0)))
			{
				return Rect();
			}

            if (cellData[x][y] == 0)
            {
                continue;
            }

            bool isContinue = true;

            // 地面セル番号がある場合、そのセル番号は無視する
            for (auto& unused : groundCellNumber)
            {
                if (cellData[x][y] == unused)
                {
                    isContinue = false;
                }
            }

            if (isContinue)
            {
                continue;
            }


			// 一番最初に見つかったぶつかるマップチップの一番上Y座標を取る
			float temp = static_cast<float>(y * cellSize);
			if (temp < result.bottom)
			{
				result.bottom = temp;
			}
		}
	}
	// 左方向
	for (int x = indexMinX; x >= 0; x--)
	{
		for (int y = indexMinY; y <= indexMaxY; y++)
		{
			if (!IsCellRange(Cell(x, y), maxCell, Cell(0, 0)))
			{
				return Rect();
			}

            if (cellData[x][y] == 0)
            {
                continue;
            }

            bool isContinue = true;

            // 地面セル番号がある場合、そのセル番号は無視する
            for (auto& unused : groundCellNumber)
            {
                if (cellData[x][y] == unused)
                {
                    isContinue = false;
                }
            }

            if (isContinue)
            {
                continue;
            }


			// 一番最初に見つかったぶつかるマップチップの一番右X座標を取る
			float temp = static_cast<float>(x * cellSize + cellSize);
			if (temp > result.left)
			{
				result.left = temp;
			}
		}
	}
	// 右方向
	for (int x = indexMaxX; x < maxCell.x; x++)
	{
		for (int y = indexMinY; y <= indexMaxY; y++)
		{
			if (!IsCellRange(Cell(x, y), maxCell, Cell(0, 0)))
			{
				return Rect();
			}


            if (cellData[x][y] == 0)
            {
                continue;
            }

            bool isContinue = true;

            // 地面セル番号がある場合、そのセル番号は無視する
            for (auto& unused : groundCellNumber)
            {
                if (cellData[x][y] == unused)
                {
                    isContinue = false;
                }
            }

            if (isContinue)
            {
                continue;
            }


			// 一番最初に見つかったぶつかるマップチップの一番左X座標を取る
			float temp = static_cast<float>(x * cellSize);
			if (temp < result.right)
			{
				result.right = temp;
			}
		}
	}

	return result;
}

bool EvoLib::Calculation::IsCellRange(const Cell& cell, const Cell& maxCell, const Cell& minCell)
{
    // セルが最大セルを超えているかどうかを確認する
    if (cell.x >= maxCell.x ||
        cell.y >= maxCell.y)
    {
        // 超えていたらfalseを返す
        return false;
    }

    // セルが最小セルを下回っているかどうかを確認する
    if (cell.x < minCell.x ||
        cell.y < minCell.y)
    {
        // 下回っていたらfalseを返す
        return false;
    }

    // trueを返す
    return true;
}

Vec2 EvoLib::Calculation::TargetMoveValue(const Vec2& pos, const Vec2& targetPos, const float& moveSpeed)
{

    // ターゲットの座標から自身の座標を引いた値を求める
    Vec2 vel = targetPos - pos;

    // 求めた距離をノマライズすることにより距離の長さを１とみる
    vel.normalize();

    // ノーマライズされた距離に移動速度をかける
    vel *= moveSpeed;

    // 移動量を返す
    return vel;
}
