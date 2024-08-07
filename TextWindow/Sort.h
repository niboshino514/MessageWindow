#pragma once
#include <vector>


struct Sort
{
public:

	/// <summary>
	/// <para>隣り合う2つの値の大小を比較し交換を行う</para>
	/// <para>要素数の少ない簡単なリストで用いることが望ましい</para>
	/// </summary>
	template <typename T>
	static void BubbleSort(T& data, const int dataSize)
	{
		//配列のサイズ - 1回操作
		for (int i = 0; i < dataSize - 1; i++)
		{
			//右からソート（左からやると変数が1つ増える）
			for (int j = dataSize - 1; i < j; j--)
			{
				//左の数値が大きい場合のみ入れ替える
				if (data[j - 1] < data[j]) continue;
				Swap(&data[j], &data[j - 1]);
			}
		}
	}

	/// <summary>
	/// <para>配列の最小値を探し先頭と交換を行う</para>
	/// <para>バブルソートより処理速度が速い</para>
	/// </summary>
	template <typename T>
	static void SelectionSort(T& data, const int dataSize)
	{
		//左から順にソート
		for (int i = 0; i < dataSize - 1; i++)
		{
			int min = i; //最小値,初期値は未定の部分の先頭

			//未定の部分の先頭から最後までを探索
			for (int j = i + 1; j < dataSize; j++)
			{
				//暫定の最小値より小さい数値があれば変更
				if (data[j] < data[min]) min = j;
			}
			//入れ替える（この時点で最小値の要素は判別済）
			Swap(&data[i], &data[min]);
		}
	}

	/// <summary>
	/// <para>人間が並び替えを行う時の考え方に近い</para>
	/// <para>ソート済みに近ければ処理速度は速く、逆順に並んでいると遅くなる</para>
	/// </summary>
	template <typename T>
	static void InsertionSort(T& data, const int dataSize)
	{
		//整列されていない部分の先頭を指す
		for (int i = 1; i < dataSize; i++)
		{
			// 交換要素のためのインデックス
			int j = i;

			// 整列済みの場合は処理しない
			while ((0 < j) && (data[j]) < data[j - 1])
			{
				// 整列されていない隣り合う要素を交換する
				Swap(&data[j - 1], &data[j]);

				// 隣り合う要素のインデックスを更新
				j--;
			}
		}
	}

	/// <summary>
	/// <para>全体を細かく分けて少しずつ並べ替えながら統合する</para>
	/// <para>挿入ソートより処理速度が早い</para>
	/// </summary>
	template <typename T>
	static void ShellSort(T& data, const int dataSize)
	{
		int powerNum = 0; //間隔用変数
		//適切な間隔の探索
		while ((Pow(3, powerNum) - 1) / 2 < dataSize)
		{
			powerNum++;
		}
		
		int interval = (Pow(3, powerNum) - 1) / 2; //間隔の初期値
		bool flag = false; //間隔1の時の判定用

		while (1 < interval || flag)
		{
			//間隔の変更
			if (1 < interval) interval = (interval - 1) / 3;
			//フラグの初期化
			flag = false;
			//間隔でグループ分け
			for (int i = 0; i < dataSize - interval; i++)
			{			
				//グループ毎に挿入ソートの実施
				int temp = data[i + interval];
			
				//比較(1回目)
				if(temp < data[i])
				{				
					int j = i; //要素番号のコピー
					//挿入場所の探索,挿入場所を空ける(挿入地点より右の整列要素を1つずつずらす)
					//継続条件,整列済要素に挿入する要素より値の大きい要素が存在
					while (j + interval > 0 && data[j] > temp)
					{
						data[j + interval] = data[j]; //要素を間隔分右にずらす
						j -= interval; //調べる要素を左にずらす
					}

					data[j + interval] = temp; //挿入
					flag = true;
				}
			}
		}
	}

	/// <summary>
	/// <para>基準値をもとにデータ群を2つに分け入れ替えを繰り返す</para>
	/// <para>処理速度が高速だが交換の際に同じ値の順番は保存されず安定ソートではない</para>
	/// </summary>
	template <typename T>
	static void QuickSort(T& data, const int dataSize)
	{
		const int sortTop = 0;
		const int sortLast = dataSize - 1;
		QuickSort(data, sortTop, sortLast);
	}

	/// <summary>
	/// <para>データをすべてばらして再度合わせる際に並び変える</para>
	/// <para>処理速度が高速だが元データの他に作業用のデータを使用する</para>
	/// </summary>
	template <typename T>
	static void MergeSort(T& data, const int dataSize)
	{
		const int sortTop = 0;
		const int sortLast = dataSize - 1;
		T tempData = data;
		MergeSort(data, tempData, sortTop, sortLast);
	}

	/// <summary>
	/// <para>ヒープ構造を利用しルートノードに最大値（最小値）が来るようにし値を順に取り出すことで並び変える</para>
	/// <para>処理速度が高速（クイックソートに劣る）だが交換の際に同じ値の順番は保存されず安定ソートではない</para>
	/// </summary>
	template <typename T>
	static void HeapSort(T& data, const int dataSize)
	{
		int index = 0;

		//ヒープ構築
		//二分木なので親ノードのインデックスは
		//(n - 1) / 2 となる
		for (index = (dataSize - 1) / 2; 0 <= index; index--)
		{
			HeapSort(data, index, dataSize - 1);
		}

		//ヒープソート実行
		//値を昇順に並べる。
		//
		//先頭要素(最大値)を配列の最後に移動させて
		//最後の要素を無視してヒープを構築すると
		//配列内で最も小さな値から順に並ぶ
		for (index = dataSize - 1; 0 < index; index--)
		{
			const int temp = data[0];
			data[0] = data[index];
			data[index] = temp;
			HeapSort(data, 0, index - 1);
		}
	}

	/// <summary>
	/// <para>データの最大値の値分のデータに値を入れていき並び変える</para>
	/// <para>今回の実装では整数のみしか並び変えられない</para>
	/// </summary>
	template <typename T>
	static void BucketSort(T& data, const int dataSize)
	{
		//入れ物の大きさをデータの値+1にする
		int bucketsSize = 0;
		for (int i = 0; i < dataSize; i++)
		{
			if (bucketsSize < data[i]) bucketsSize = data[i] + 1;
		}

		BucketSort(data, dataSize, bucketsSize);
	}

private:
	//データの入れ替えを行う
	template <typename T = int>
	static void Swap(T* leftData, T* rightData)
	{
		//一時格納
		const T temp = *leftData;

		//入れ替え
		*leftData = *rightData;
		*rightData = temp;
	}

	//累乗した値を返す
	template <typename T = int>
	[[nodiscard]] static const int Pow(T num, T power)
	{
		int powerNum = num;
		for (int i = 0; i < power; i++)
		{
			powerNum = powerNum * num;
		}
		return powerNum;
	}

	//中央値探索(クイックソート内部で利用)
	template <typename T = int>
	[[nodiscard]] static const int SearchMiddle(const T top, const T middle, const T last)
	{
		//先頭が中央値
		if ((top < middle && top > last) || (top < last && top > middle)) return top;
		//中央が中央値
		else if ((top < middle && middle < last) || (top > middle && middle > last)) return middle;
		//その他(後尾が中央値ではない場合も含む)
		else return last;
	}

	//クイックソート(クイックソート内部で利用)
	template <typename T1, typename T2 = int>
	static void QuickSort(T1& data, const T2 top, const T2 last)
	{
		T2 topIndex = top, lastIndex = last;

		const T2 middleIndex = topIndex + (lastIndex - topIndex) / 2;
		//3点の中央値を基準とする
		const T2 pivot = SearchMiddle(data[topIndex], data[middleIndex], data[lastIndex]);

		//ループ処理(1度のループで2分割する)
		while (true)
		{
			//基準より大きな値を先頭から探す
			while (data[topIndex] < pivot) topIndex++; //探索位置をずらす

			//基準より小さな値を最後から探す
			while (data[lastIndex] > pivot) lastIndex--; //探索位置をずらす

			//入れ替える必要がなくなればループを抜ける(iとjの位置関係が正順ならばループを抜ける)
			if (lastIndex - 1 < topIndex) break;

			//配列の入れ替えを行う
			Swap(&data[topIndex], &data[lastIndex]);

			//スワップを行なった場合範囲を一つずつ狭めて(スワップした場所を探索しないで)再探索
			topIndex++;
			lastIndex--;
		}

		//2分割した範囲をそれぞれで更に分割する(再帰的に繰り返す)
		if (top < topIndex - 1) RecurseQuick(data, top, topIndex - 1);
		if (lastIndex + 1 < last) RecurseQuick(data, lastIndex + 1, last);
	}

	//再帰するための呼び出し
	template <typename T1, typename T2 = int>
	static void RecurseQuick(T1& data, const T2 top, const T2 last)
	{
		QuickSort(data, top, last);
	}

	//マージソート
	template <typename T>
	static void MergeSort(T& data, T& tempData, const int start, const int end)
	{
		if (end <= start) return;

		//startとendの中間地点を分割点とする
		const int middle = (start + end) / 2;
		//前半部分を再帰的に整列
		MergeSort(data, tempData, start, middle);
		//後半部分を再帰的に整列
		MergeSort(data, tempData, middle + 1, end);
		//作業用のデータ
		int left = 0, right = 0, index = 0;
		//仮想領域のデータをマージしながらコピーする
		for (left = start; left <= middle; left++)
		{
			tempData[index] = data[left];
			index++;
		}
		for (right = end; middle + 1 <= right; right--)
		{
			tempData[index] = data[right];
			index++;
		}
		//末端からデータを取得して、マージしていく
		left = 0;
		right = end - start;
		for (index = start; index <= end; index++)
		{
			if (tempData[left] <= tempData[right])
			{
				data[index] = tempData[left];
				left++;
			}
			else
			{
				data[index] = tempData[right];
				right--;
			}
		}
	}

	//ヒープソート
	template <typename T>
	void HeapSort(T& data, const int root, const int bottom)
	{
		// 子ノードのインデックス
		int child = (2 * root) + 1;

		// 親ノードの値を保持しておく
		const int temp = data[root];

		while (child <= bottom)
		{
			//二分木のふたつの子ノードから値が大きいほうの子ノードを選択する
			if (child < bottom && data[child] < data[child + 1]) child = child + 1;

			//親ノードの値が子ノードの値以下の場合入れ替える
			if (data[child] < temp) break;

			data[(child - 1) / 2] = data[child];
			//子ノードのインデックスを進める
			child = (2 * child) + 1;
		}
		// 親ノードとなる要素に値を入れる
		data[(child - 1) / 2] = temp;
	}

	//再帰するための呼び出し
	template <typename T>
	void RecurseHeap(T& data, const int root, const int bottom)
	{
		//子ノードのインデックス
		//配列の先頭要素のインデックスが 0 なので
		//子ノードは 2n + 1 と 2n + 2 で計算する
		int left = (root * 2) + 1;
		int right = (root * 2) + 2;

		//最大値を持つ要素のインデックス
		int maxChild = 0;

		if (left <= bottom && data[root] < data[left]) maxChild = left;
		else maxChild = root;

		if (right <= bottom && data[maxChild] < data[right]) maxChild = right;

		if (maxChild != root)
		{
			const int temp = data[root];
			data[root] = data[maxChild];
			data[maxChild] = temp;
			//配列の先頭要素には最大値を持つ要素のインデックスを指定する
			RecurseHeap(data, maxChild, bottom);
		}
	}

	//バケットソート
	template <typename T>
	static void BucketSort(T& data, const int dataSize, int bucketsSize)
	{
		T buckets(bucketsSize);
		for (int i = 0; i < bucketsSize; i++)
		{
			buckets[i] = 0;
		}

		//元のデータをバケットに入れる
		for (int i = 0; i < dataSize; i++)
		{
			buckets[data[i]] = data[i];
		}
		//配列のインデックス
		int index = 0;
		//バケットから元の配列に戻す
		for (int i = 0; i < bucketsSize; i++)
		{
			if (0 < buckets[i]) data[index++] = buckets[i];
		}
	}
};