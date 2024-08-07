#include "Draw.h"

void EvoLib::Draw::DrawSimpleBackground(const int& graphHandle, const Vec2& screenSize, bool isFlipImage)
{
    // 各座標
    Vec2 pos_1;
    Vec2 pos_2;
    Vec2 pos_3;
    Vec2 pos_4;

    // 座標に値を代入
    pos_1 = Vec2(0, 0);
    pos_2 = Vec2(screenSize.x, 0);
    pos_3 = Vec2(pos_2.x, screenSize.y);
    pos_4 = Vec2(0, screenSize.y);

    // 反転する場合の処理
    if (isFlipImage)
    {
        pos_1.x = pos_2.x;
        pos_2.x = pos_1.x;
        pos_3.x = pos_4.x;
        pos_4.x = pos_3.x;
    }

    // 描画
    DrawModiGraphF(
        pos_1.x, pos_1.y,
        pos_2.x, pos_2.y,
        pos_3.x, pos_3.y,
        pos_4.x, pos_4.y,
        graphHandle, true);

    // 処理を終了する
    return;
}

float EvoLib::Draw::SimpleLoopBackground(const int& graphHandle, float currentMoveValue, float moveSpeed, const Vec2 screenSize, bool isSupportedImageInLoop, LoopDirection loopDirection)
{
    // 座標格納変数
    Vec2 pos;

    if (loopDirection == Draw::LoopDirection::Left ||
        loopDirection == Draw::LoopDirection::Up)
    {
        // 移動スピード分、移動量に減算する
        currentMoveValue -= moveSpeed;


        // 最小移動量
        float moveMinValue = 0.0f;

        if (loopDirection == Draw::LoopDirection::Left)
        {
            moveMinValue = -screenSize.x;
        }
        else
        {
            moveMinValue = -screenSize.y;
        }


        if (!isSupportedImageInLoop)
        {
            moveMinValue *= 2;
        }


        // 現在の移動量が最大移動量よりも小さかった場合、初期化を行う
        if (currentMoveValue <= moveMinValue)
        {
            currentMoveValue = 0.0f;
        }

    }
    else
    {
        // 移動スピード分、移動量に加算する
        currentMoveValue += moveSpeed;

        // 最大移動量
        float moveMaxValue = 0.0f;

        if (loopDirection == Draw::LoopDirection::Right)
        {
            moveMaxValue = screenSize.x;
        }
        else
        {
            moveMaxValue = screenSize.y;
        }

        if (!isSupportedImageInLoop)
        {
            moveMaxValue *= 2;
        }

        // 現在の移動量が最大移動量よりも小さかった場合、初期化を行う
        if (currentMoveValue >= moveMaxValue)
        {
            currentMoveValue = 0.0f;
        }
    }


    Vec2 pos_1;
    Vec2 pos_2;
    Vec2 pos_3;
    Vec2 pos_4;

    if (loopDirection == Draw::LoopDirection::Left ||
        loopDirection == Draw::LoopDirection::Right)
    {

        pos_1 = Vec2(currentMoveValue, 0);
        pos_2 = Vec2((screenSize.x + currentMoveValue), 0);
        pos_3 = Vec2(pos_2.x, screenSize.y);
        pos_4 = Vec2(currentMoveValue, screenSize.y);
    }
    else
    {
        pos_1 = Vec2(0, currentMoveValue);
        pos_2 = Vec2(screenSize.x, currentMoveValue);
        pos_3 = Vec2(screenSize.x, (screenSize.y + currentMoveValue));
        pos_4 = Vec2(0, pos_3.y);
    }


    DrawModiGraphF(pos_1.x, pos_1.y,
        pos_2.x, pos_2.y,
        pos_3.x, pos_3.y,
        pos_4.x, pos_4.y,
        graphHandle, true);

    switch (loopDirection)
    {
    case Draw::LoopDirection::Up:

        pos_1.y += screenSize.y;
        pos_2.y += screenSize.y;
        pos_3.y += screenSize.y;
        pos_4.y += screenSize.y;

        break;
    case Draw::LoopDirection::Down:

        pos_1.y -= screenSize.y;
        pos_2.y -= screenSize.y;
        pos_3.y -= screenSize.y;
        pos_4.y -= screenSize.y;

        break;
    case Draw::LoopDirection::Left:

        pos_1.x += screenSize.x;
        pos_2.x += screenSize.x;
        pos_3.x += screenSize.x;
        pos_4.x += screenSize.x;

        break;
    case Draw::LoopDirection::Right:

        pos_1.x -= screenSize.x;
        pos_2.x -= screenSize.x;
        pos_3.x -= screenSize.x;
        pos_4.x -= screenSize.x;

        break;
    default:
        break;
    }


    // 反転用の座標
    const Vec2 reversePos_1 = pos_1;
    const Vec2 reversePos_2 = pos_2;
    const Vec2 reversePos_3 = pos_3;
    const Vec2 reversePos_4 = pos_4;

    if (!isSupportedImageInLoop)
    {

        if (loopDirection == Draw::LoopDirection::Left ||
            loopDirection == Draw::LoopDirection::Right)
        {
            pos_1.x = reversePos_2.x;
            pos_2.x = reversePos_1.x;
            pos_3.x = reversePos_4.x;
            pos_4.x = reversePos_3.x;
        }
        else
        {
            pos_1.y = reversePos_4.y;
            pos_2.y = reversePos_3.y;
            pos_3.y = reversePos_2.y;
            pos_4.y = reversePos_1.y;
        }
    }

    DrawModiGraphF(pos_1.x, pos_1.y,
        pos_2.x, pos_2.y,
        pos_3.x, pos_3.y,
        pos_4.x, pos_4.y,
        graphHandle, true);


    if (!isSupportedImageInLoop)
    {

        switch (loopDirection)
        {
        case Draw::LoopDirection::Up:

            pos_1.y = (reversePos_1.y + screenSize.y);
            pos_2.y = (reversePos_2.y + screenSize.y);
            pos_3.y = (reversePos_3.y + screenSize.y);
            pos_4.y = (reversePos_4.y + screenSize.y);

            break;
        case Draw::LoopDirection::Down:

            pos_1.y = (reversePos_1.y - screenSize.y);
            pos_2.y = (reversePos_2.y - screenSize.y);
            pos_3.y = (reversePos_3.y - screenSize.y);
            pos_4.y = (reversePos_4.y - screenSize.y);

            break;
        case Draw::LoopDirection::Left:

            pos_1.x = (reversePos_1.x + screenSize.x);
            pos_2.x = (reversePos_2.x + screenSize.x);
            pos_3.x = (reversePos_3.x + screenSize.x);
            pos_4.x = (reversePos_4.x + screenSize.x);

            break;
        case Draw::LoopDirection::Right:

            pos_1.x = (reversePos_1.x - screenSize.x);
            pos_2.x = (reversePos_2.x - screenSize.x);
            pos_3.x = (reversePos_3.x - screenSize.x);
            pos_4.x = (reversePos_4.x - screenSize.x);

            break;
        default:
            break;
        }


        DrawModiGraphF(pos_1.x, pos_1.y,
            pos_2.x, pos_2.y,
            pos_3.x, pos_3.y,
            pos_4.x, pos_4.y,
            graphHandle, true);
    }

    // グラフィックの移動量を返す
    return currentMoveValue;
}

void EvoLib::Draw::DrawGprah3D_EvoLib(const int& graphHandle, const float& graphScale, const VECTOR& angle, const VECTOR& pos, Color color)
{
    // 立体表示
    VERTEX3D vertex[6];

    // ２ポリゴン分の頂点の座標と法線以外のデータをセット
    {
        vertex[0].dif = GetColorU8(0, 0, 0, 255);
        vertex[0].spc = GetColorU8(0, 0, 0, 0);
        vertex[0].u = 0.0f;
        vertex[0].v = 0.0f;
        vertex[0].su = 0.0f;
        vertex[0].sv = 0.0f;

        vertex[1].dif = GetColorU8(0, 0, 0, 255);
        vertex[1].spc = GetColorU8(0, 0, 0, 0);
        vertex[1].u = 1.0f;
        vertex[1].v = 0.0f;
        vertex[1].su = 0.0f;
        vertex[1].sv = 0.0f;

        vertex[2].dif = GetColorU8(0, 0, 0, 255);
        vertex[2].spc = GetColorU8(0, 0, 0, 0);
        vertex[2].u = 0.0f;
        vertex[2].v = 1.0f;
        vertex[2].su = 0.0f;
        vertex[2].sv = 0.0f;

        vertex[3].dif = GetColorU8(0, 0, 0, 255);
        vertex[3].spc = GetColorU8(0, 0, 0, 0);
        vertex[3].u = 1.0f;
        vertex[3].v = 1.0f;
        vertex[3].su = 0.0f;
        vertex[3].sv = 0.0f;

        vertex[4] = vertex[2];
        vertex[5] = vertex[1];
    }

    // 座標、角度をセット
    {
        MATRIX TransformMatrix;

        // ラジアン
        VECTOR radian;

        // 角度をラジアンに変換
        radian.x = EvoLib::Convert::ConvertAngleToRadian(angle.x);
        radian.y = EvoLib::Convert::ConvertAngleToRadian(angle.y);
        radian.z = EvoLib::Convert::ConvertAngleToRadian(angle.z);

        // 回転( x, y, z軸回転の順 )＋座標移動行列の作成
        TransformMatrix = MGetRotX(radian.x);
        TransformMatrix = MMult(TransformMatrix, MGetRotY(radian.y));
        TransformMatrix = MMult(TransformMatrix, MGetRotZ(radian.z));
        TransformMatrix = MMult(TransformMatrix, MGetTranslate(VGet(0.0f, 0.0f, 0.0f)));

        // 行列を使ってワールド座標を算出
        vertex[0].pos = VTransform(VGet(pos.x + -graphScale, pos.y + graphScale, pos.z), TransformMatrix);
        vertex[1].pos = VTransform(VGet(pos.x + graphScale, pos.y + graphScale, pos.z), TransformMatrix);
        vertex[2].pos = VTransform(VGet(pos.x + -graphScale, pos.y + -graphScale, pos.z), TransformMatrix);
        vertex[3].pos = VTransform(VGet(pos.x + graphScale, pos.y + -graphScale, pos.z), TransformMatrix);

        vertex[4].pos = vertex[2].pos;
        vertex[5].pos = vertex[1].pos;

        // 行列を使って法線を算出
        vertex[0].norm = VTransformSR(VGet(0.0f, 0.0f, -1.0f), TransformMatrix);
        vertex[1].norm = vertex[0].norm;
        vertex[2].norm = vertex[0].norm;
        vertex[3].norm = vertex[0].norm;
        vertex[4].norm = vertex[0].norm;
        vertex[5].norm = vertex[0].norm;
    }



    MATERIALPARAM Material;

    // 色
    {
        Material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
        Material.Specular = GetColorF(1.0f, 1.0f, 1.0f, 0.0f);
        Material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
        Material.Emissive = GetColorF(color.r, color.g, color.b, 0.0f);
        Material.Power = 20.0f;


        SetMaterialParam(Material);
    }


    // 2Dポリゴンの描画
    DrawPolygon3D(vertex, 2, graphHandle, true);


    // 初期マテリアル
    MATERIALPARAM initMaterial = {};


    // ここでマテリアルのパラメータを元に戻す
    SetMaterialParam(initMaterial);
}

void EvoLib::Draw::DrawCube3D_EvoLib(const VECTOR& centerPos, const VECTOR& oneSideLength, int alphaValue, int lineThickness, Color color)
{

    // アルファブレンドをかける
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaValue);

    // 半分の一辺の値
    VECTOR halfOneSideLength = VScale(oneSideLength, 0.5f);


    VECTOR start = centerPos;
    VECTOR end = centerPos;

    for (int i = 0; i < lineThickness; i++)
    {

        float shiftValue = i * 0.05f;

        {
            start = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));
            end = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));


            start.x -= halfOneSideLength.x;
            start.y += halfOneSideLength.y;
            start.z -= halfOneSideLength.z;

            end.x += halfOneSideLength.x;
            end.y += halfOneSideLength.y;
            end.z -= halfOneSideLength.z;

            DrawLine3D(start, end, GetColor(0, 0, 0));
        }

        {
            start = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));
            end = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));


            start.x -= halfOneSideLength.x;
            start.y -= halfOneSideLength.y;
            start.z -= halfOneSideLength.z;

            end.x += halfOneSideLength.x;
            end.y -= halfOneSideLength.y;
            end.z -= halfOneSideLength.z;


            DrawLine3D(start, end, GetColor(0, 0, 0));
        }

        {
            start = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));
            end = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));


            start.x -= halfOneSideLength.x;
            start.y -= halfOneSideLength.y;
            start.z += halfOneSideLength.z;

            end.x += halfOneSideLength.x;
            end.y -= halfOneSideLength.y;
            end.z += halfOneSideLength.z;


            DrawLine3D(start, end, GetColor(0, 0, 0));
        }

        {
            start = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));
            end = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));


            start.x -= halfOneSideLength.x;
            start.y += halfOneSideLength.y;
            start.z += halfOneSideLength.z;

            end.x += halfOneSideLength.x;
            end.y += halfOneSideLength.y;
            end.z += halfOneSideLength.z;


            DrawLine3D(start, end, GetColor(0, 0, 0));
        }

        {
            start = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));
            end = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));


            start.x += halfOneSideLength.x;
            start.y += halfOneSideLength.y;
            start.z -= halfOneSideLength.z;

            end.x += halfOneSideLength.x;
            end.y += halfOneSideLength.y;
            end.z += halfOneSideLength.z;


            DrawLine3D(start, end, GetColor(0, 0, 0));
        }

        {
            start = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));
            end = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));


            start.x += halfOneSideLength.x;
            start.y -= halfOneSideLength.y;
            start.z -= halfOneSideLength.z;

            end.x += halfOneSideLength.x;
            end.y -= halfOneSideLength.y;
            end.z += halfOneSideLength.z;


            DrawLine3D(start, end, GetColor(0, 0, 0));
        }

        {
            start = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));
            end = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));


            start.x -= halfOneSideLength.x;
            start.y -= halfOneSideLength.y;
            start.z -= halfOneSideLength.z;

            end.x -= halfOneSideLength.x;
            end.y -= halfOneSideLength.y;
            end.z += halfOneSideLength.z;


            DrawLine3D(start, end, GetColor(0, 0, 0));
        }

        {
            start = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));
            end = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));


            start.x -= halfOneSideLength.x;
            start.y += halfOneSideLength.y;
            start.z -= halfOneSideLength.z;

            end.x -= halfOneSideLength.x;
            end.y += halfOneSideLength.y;
            end.z += halfOneSideLength.z;


            DrawLine3D(start, end, GetColor(0, 0, 0));
        }

        {
            start = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));
            end = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));


            start.x += halfOneSideLength.x;
            start.y += halfOneSideLength.y;
            start.z -= halfOneSideLength.z;

            end.x += halfOneSideLength.x;
            end.y -= halfOneSideLength.y;
            end.z -= halfOneSideLength.z;


            DrawLine3D(start, end, GetColor(0, 0, 0));
        }

        {
            start = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));
            end = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));


            start.x += halfOneSideLength.x;
            start.y += halfOneSideLength.y;
            start.z += halfOneSideLength.z;

            end.x += halfOneSideLength.x;
            end.y -= halfOneSideLength.y;
            end.z += halfOneSideLength.z;


            DrawLine3D(start, end, GetColor(0, 0, 0));
        }

        {
            start = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));
            end = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));


            start.x -= halfOneSideLength.x;
            start.y += halfOneSideLength.y;
            start.z += halfOneSideLength.z;

            end.x -= halfOneSideLength.x;
            end.y -= halfOneSideLength.y;
            end.z += halfOneSideLength.z;


            DrawLine3D(start, end, GetColor(0, 0, 0));
        }


        {
            start = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));
            end = VAdd(centerPos, VGet(shiftValue, shiftValue, shiftValue));


            start.x -= halfOneSideLength.x;
            start.y += halfOneSideLength.y;
            start.z -= halfOneSideLength.z;

            end.x -= halfOneSideLength.x;
            end.y -= halfOneSideLength.y;
            end.z -= halfOneSideLength.z;


            DrawLine3D(start, end, GetColor(0, 0, 0));
        }
    }

    // 通常描画に戻す
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
