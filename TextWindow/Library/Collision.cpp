#include "Collision.h"

bool EvoLib::Collision::SphereCollision(const Sphere& sphere1, const Sphere& sphere2)
{
    // 衝突したかどうか
    bool isCollision = false;


    // 球の衝突判定
    {
        const float dx = sphere1.pos.x - sphere2.pos.x;
        const float dy = sphere1.pos.y - sphere2.pos.y;
        const float dz = sphere1.pos.z - sphere2.pos.z;


        const float dr = (dx * dx) + (dy * dy) + (dz * dz);	// A²＝B²＋C²＋D²

        const float ar = sphere1.radius + sphere2.radius;		// 球の大きさ
        const float dl = ar * ar;

        if (dr <= dl)
        {
            // 衝突している
            isCollision = true;
        }
    }

    // 衝突判定を返す
    return isCollision;
}

bool EvoLib::Collision::IsAABBCollisionDetection(const Circle& circle, const Square& square)
{
	// 長さ
	float line = 0;

	// 上判定
	{
		if (circle.centerPos.x <= square.A.x)
		{
			line = std::powf(square.A.y - circle.centerPos.y, 2.0f)
				+ std::powf(square.A.x - circle.centerPos.x, 2.0f);
		}
		else if (square.B.x <= circle.centerPos.x)
		{
			line = std::powf(square.B.y - circle.centerPos.y, 2.0f)
				+ std::powf(square.B.x - circle.centerPos.x, 2.0f);
		}
		else
		{
			line = std::powf(square.A.y - circle.centerPos.y, 2.0f);
		}

		line = std::sqrtf(line);

		// 四角形の上に衝突
		if (circle.radius > line)
		{
			return true;
		}
	}

	// 下判定
	{
		if (circle.centerPos.x <= square.D.x)
		{
			line = std::powf(square.D.y - circle.centerPos.y, 2.0f)
				+ std::powf(square.D.x - circle.centerPos.x, 2.0f);
		}
		else if (square.C.x <= circle.centerPos.x)
		{
			line = std::powf(square.C.y - circle.centerPos.y, 2.0f)
				+ std::powf(square.C.x - circle.centerPos.x, 2.0f);
		}
		else
		{
			line = std::powf(square.D.y - circle.centerPos.y, 2.0f);
		}

		line = std::sqrtf(line);

		// 四角形の下に衝突
		if (circle.radius > line)
		{
			return true;
		}
	}

	// 右判定
	{
		if (circle.centerPos.y <= square.B.y)
		{
			line = std::powf(square.B.y - circle.centerPos.y, 2.0f)
				+ std::powf(square.B.x - circle.centerPos.x, 2.0f);
		}
		else if (square.C.y <= circle.centerPos.y)
		{
			line = std::powf(square.C.y - circle.centerPos.y, 2.0f)
				+ std::powf(square.C.x - circle.centerPos.x, 2.0f);
		}
		else
		{
			line = std::powf(square.C.x - circle.centerPos.x, 2.0f);
		}

		line = std::sqrtf(line);

		// 四角形の右に衝突
		if (circle.radius > line)
		{
			return true;
		}
	}

	// 左判定
	{
		if (circle.centerPos.y <= square.A.y)
		{
			line = std::powf(square.A.y - circle.centerPos.y, 2.0f)
				+ std::powf(square.A.x - circle.centerPos.x, 2.0f);
		}
		else if (square.D.y <= circle.centerPos.y)
		{
			line = std::powf(square.D.y - circle.centerPos.y, 2.0f)
				+ std::powf(square.D.x - circle.centerPos.x, 2.0f);
		}
		else
		{
			line = std::powf(square.D.x - circle.centerPos.x, 2.0f);
		}

		line = std::sqrtf(line);

		// 四角形の左に衝突
		if (circle.radius > line)
		{
			return true;
		}
	}

	// どこにも衝突していない
	return false;
}

bool EvoLib::Collision::IsCircleToCircle(const Circle& circle1, const Circle& circle2)
{
	// 衝突したかどうか
	bool isCollision = false;


	// 円の衝突判定
	{
		const float dx = circle1.centerPos.x - circle2.centerPos.x;
		const float dy = circle1.centerPos.y - circle2.centerPos.y;

		const float dr = (dx * dx) + (dy * dy);	// A²＝B²＋C²

		const float ar = circle1.radius + circle2.radius;		// 球の大きさ
		const float dl = ar * ar;

		if (dr <= dl)
		{
			// 衝突している
			isCollision = true;
		}
	}

	// 衝突判定を返す
	return isCollision;
}

bool EvoLib::Collision::IsTriangleToSquare(const Triangle& triangle, const Square& square)
{

	// 三角形情報
	std::vector<Line> triangleLine;
	{
		triangleLine.resize(3);

		triangleLine[0].start = triangle.pos_1;
		triangleLine[0].end = triangle.pos_2;

		triangleLine[1].start = triangle.pos_2;
		triangleLine[1].end = triangle.pos_3;

		triangleLine[2].start = triangle.pos_3;
		triangleLine[2].end = triangle.pos_1;
	}

	// 四角形情報
	std::vector<Line> squareLine;
	{
		squareLine.resize(4);

		squareLine[0].start = square.A;
		squareLine[0].end = square.B;

		squareLine[1].start = square.B;
		squareLine[1].end = square.C;

		squareLine[2].start = square.C;
		squareLine[2].end = square.D;

		squareLine[3].start = square.D;
		squareLine[3].end = square.A;
	}


	// 四角形と三角形の当たり判定を行う
	for (int i = 0; i < static_cast<int>(squareLine.size()); i++)
	{
		for (int j = 0; j < static_cast<int>(triangleLine.size()); j++)
		{
			// 四角形と三角形のライン同士の当たり判定を行う
			if (IsLineToLine(squareLine[i], triangleLine[j]))
			{
				return true;
			}
		}
	}




	std::vector<Vec2> squareStart;
	{
		squareStart.resize(4);

		squareStart[0] = square.A;
		squareStart[1] = square.B;
		squareStart[2] = square.C;
		squareStart[3] = square.D;
	}

	std::vector<Vec2> triangleStart;
	{
		triangleStart.resize(3);

		triangleStart[0] = triangle.pos_1;
		triangleStart[1] = triangle.pos_2;
		triangleStart[2] = triangle.pos_3;
	}



	// 三角形の頂点が四角形の内部にあるかの判定
	for (const auto& vertex : triangleStart)
	{
		if (PointInPolygon(vertex, squareStart))
		{
			return true;
		}
	}


	// 四角形の頂点が三角形の内部にあるかの判定
	for (const auto& vertex : squareStart)
	{
		if (PointInPolygon(vertex, triangleStart))
		{
			return true;
		}
	}

	return false;
}

bool EvoLib::Collision::IsSquareToSquare(const Square& square1, const Square& square2)
{
	// 四角形情報1
	std::vector<Line> squareLine1;
	{
		squareLine1.resize(4);

		squareLine1[0].start = square1.A;
		squareLine1[0].end = square1.B;

		squareLine1[1].start = square1.B;
		squareLine1[1].end = square1.C;

		squareLine1[2].start = square1.C;
		squareLine1[2].end = square1.D;

		squareLine1[3].start = square1.D;
		squareLine1[3].end = square1.A;
	}

	// 四角形情報2
	std::vector<Line> squareLine2;
	{
		squareLine2.resize(4);

		squareLine2[0].start = square2.A;
		squareLine2[0].end = square2.B;

		squareLine2[1].start = square2.B;
		squareLine2[1].end = square2.C;

		squareLine2[2].start = square2.C;
		squareLine2[2].end = square2.D;

		squareLine2[3].start = square2.D;
		squareLine2[3].end = square2.A;
	}


	// 四角形同士の当たり判定を行う
	for (int i = 0; i < static_cast<int>(squareLine1.size()); i++)
	{
		for (int j = 0; j < static_cast<int>(squareLine2.size()); j++)
		{
			// 四角形と四角形のライン同士の当たり判定を行う
			if (IsLineToLine(squareLine1[i], squareLine2[j]))
			{
				return true;
			}
		}
	}

	std::vector<Vec2> squareStaet1;
	{
		squareStaet1.resize(4);

		squareStaet1[0] = square1.A;
		squareStaet1[1] = square1.B;
		squareStaet1[2] = square1.C;
		squareStaet1[3] = square1.D;
	}

	std::vector<Vec2> squareStaet2;
	{
		squareStaet2.resize(4);

		squareStaet2[0] = square2.A;
		squareStaet2[1] = square2.B;
		squareStaet2[2] = square2.C;
		squareStaet2[3] = square2.D;
	}


	for (const auto& vertex : squareStaet1)
	{
		if (PointInPolygon(vertex, squareStaet2))
		{
			return true;
		}
	}

	for (const auto& vertex : squareStaet2)
	{
		if (PointInPolygon(vertex, squareStaet1))
		{
			return true;
		}
	}

	return false;
}

bool EvoLib::Collision::IsLineToLine(const Line& line1, const Line& line2)
{
	float s1_x = line1.end.x - line1.start.x, s1_y = line1.end.y - line1.start.y;
	float s2_x = line2.end.x - line2.start.x, s2_y = line2.end.y - line2.start.y;

	float s, t;

	s = (-s1_y * (line1.start.x - line2.start.x) + s1_x * (line1.start.y - line2.start.y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = (s2_x * (line1.start.y - line2.start.y) - s2_y * (line1.start.x - line2.start.x)) / (-s2_x * s1_y + s1_x * s2_y);

	return s >= 0 && s <= 1 && t >= 0 && t <= 1;
}

bool EvoLib::Collision::PointInPolygon(const Vec2& point, const std::vector<Vec2>& polygon)
{
	bool inside = false;

	const int numVertices = static_cast<int>(polygon.size());

	for (int i = 0, j = numVertices - 1; i < numVertices; j = i++) {
		// ポリゴンの辺を定義する2点
		const Vec2& vertex1 = polygon[i];
		const Vec2& vertex2 = polygon[j];

		// 点の水平線がこの辺と交差するかどうかをチェック
		bool intersect = ((vertex1.y > point.y) != (vertex2.y > point.y)) &&
			(point.x < (vertex2.x - vertex1.x) * (point.y - vertex1.y) / (vertex2.y - vertex1.y) + vertex1.x);

		if (intersect) {
			inside = !inside;
		}
	}
	return inside;
}
