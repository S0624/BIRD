#include "Common.h"
#include"Object/Player.h"
#include"Camera/Camera.h"
#include"Stage/Map.h"
#include"Object/BackGround.h"
#include"Scene/SceneManager.h"

#include "math.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    // シーンマネージャーの宣言
    SceneManager* pSceneManager;
    pSceneManager = new SceneManager;
    pSceneManager->Init();

    while (ProcessMessage() == 0)
    {
        LONGLONG time = GetNowHiPerformanceCount();

        // 画面のクリア
        ClearDrawScreen();

        // 更新処理
        pSceneManager->Update();
        // 描画処理
        pSceneManager->Draw();

        // 裏画面を表画面を入れ替える
        ScreenFlip();

        // escキーを押したら終了する
        if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

        // fpsを60に固定
        while (GetNowHiPerformanceCount() - time < 16667)
        {

        }
    }
    // エンド処理
    pSceneManager->End();
    // デリート
    delete(pSceneManager);
    DxLib_End();                // ＤＸライブラリ使用の終了処理

    return 0;                // ソフトの終了
}