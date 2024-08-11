#include "Load.h"



EvoLib::Load::DivGraphInfo EvoLib::Load::LoadDivGraph_EvoLib(const char* filePath, const int& div_x, const int& div_y)
{

    int wide = 0;       // グラフィックの横幅
    int height = 0;     // グラフィックの縦幅
    int graphic = -1;   // グラフィックの代入


    // プレイヤーのグラフィックサイズを取得
    {
        graphic = LoadGraph(filePath);
        GetGraphSize(graphic, &wide, &height);
    }


    // 分割数合計
    const int divNum = div_x * div_y;

    // グラフィック情報
    DivGraphInfo graphInfo;

    // スケールを代入
    graphInfo.scale.x = static_cast<float>(wide);
    graphInfo.scale.y = static_cast<float>(height);



    // 分割した画像をハンドルに入れる
    {
        // ハンドル
        int* handle = new int[divNum];

        // 分割した画像を入れる
        LoadDivGraph(filePath, divNum,
            div_x, div_y,
            wide / div_x, height / div_y, handle);

        for (int i = 0; i < divNum; i++)
        {
            // グラフィックを代入
            graphInfo.handle.push_back(handle[i]);
        }

        // メモリの開放
        delete[] handle;
    }

    return graphInfo;
}

std::vector<int> EvoLib::Load::LoadDivGraph_EvoLib_Revision(const char* filePath, const DivNum& div)
{
    // ファイルが存在しない場合、エラーメッセージを表示
    if(!EvoLib::File::IsFileExist(filePath))
    {
		// ファイルが存在しない場合、エラーメッセージを表示
		std::string errorMsg = "[" + static_cast<std::string>(filePath) + "]" +
			" のグラフィックファイルは存在しないようです。";

		// ファイル読込エラー処理
		EvoLib::Assert::ErrorMessageBox(errorMsg);
	}




    int wide = 0;       // グラフィックの横幅
    int height = 0;     // グラフィックの縦幅
    int graphic = -1;   // グラフィックの代入


    // プレイヤーのグラフィックサイズを取得
    {
        graphic = LoadGraph(filePath);
        GetGraphSize(graphic, &wide, &height);
    }


    // 分割数合計
    const int divNum = div.x * div.y;

    // 分割されたグラフィックハンドル
    std::vector<int> graphHandle;

    // 分割した画像をハンドルに入れる
    {
        // ハンドル
        int* handle = new int[divNum];

        // 分割した画像を入れる
        LoadDivGraph(filePath, divNum,
            div.x, div.y,
            wide / div.x, height / div.y, handle);

        for (int i = 0; i < divNum; i++)
        {
            // グラフィックを代入
            graphHandle.push_back(handle[i]);
        }


        





        // メモリの開放
        delete[] handle;
    }

    // グラフィック情報
    return graphHandle;
}

int EvoLib::Load::LoadFont(const char* filePath, const char* fontName, const int& fontSize)
{
    // 読み込むフォントファイルのパス
    LPCSTR font_path = filePath; 

    // エラーメッセージ
    std::string errorMsg = "";

 
    // ファイルが存在しない場合、エラーメッセージを表示
    if (!EvoLib::File::IsFileExist(filePath))
    {
        // エラーメッセージ
        errorMsg = "[" + static_cast<std::string>(filePath) + "]" +
			" は存在しないようです。";

        // ファイル読込エラー処理
        EvoLib::Assert::ErrorMessageBox(errorMsg);
    }


    // フォント読込
    if (AddFontResource(font_path) > 0) 
    {
        PostMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
    }
    else 
    {
        // エラーメッセージ
        errorMsg = "[" + static_cast<std::string>(filePath) + "]" +
            " にあるフォントの読み込みが失敗しました。";

        // フォント読込エラー処理
        EvoLib::Assert::ErrorMessageBox(errorMsg);
    }

    // フォントの保存
    const int fontData = CreateFontToHandle(fontName, fontSize, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, -1);

    // フォントデータが-1の場合、エラーメッセージを表示
    if (fontData == -1)
    {
        // エラーメッセージ
        errorMsg = "フォントを保存する際にエラーが発生しました。";

        // フォント読込エラー処理
        EvoLib::Assert::ErrorMessageBox(errorMsg);
    }

    // フォントデータを返す
    return fontData;
}


