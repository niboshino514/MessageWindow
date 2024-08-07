// コントローラー
#pragma once

// コントローラーからの入力状態を取得する
namespace Pad
{
	void update();					// パッドの入力状態取得
	bool isPress(int button);		// 押し下げ判定
	bool isTrigger(int button);		// トリガー判定
	bool isRelase(int button);		// 離した判定
}
