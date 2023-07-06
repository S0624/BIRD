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
    // windowモード設定
    ChangeWindowMode(Game::kWindowMode);

    // ウインドウ名設定
    SetMainWindowText("BIRD");

    // 画面サイズの設定
    SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
    SetWindowSizeChangeEnableFlag(true);//ウィンドウモードの拡大縮小（サイズ変更）
    SetAlwaysRunFlag(true);

    if (DxLib_Init() == -1)        // ＤＸライブラリ初期化処理
    {
        return -1;            // エラーが起きたら直ちに終了
    }

    SceneManager* pScene;
    pScene = new SceneManager;
    pScene->Init();

    // ダブルバッファモード
    SetDrawScreen(DX_SCREEN_BACK);

    while (ProcessMessage() == 0)
    {
        LONGLONG time = GetNowHiPerformanceCount();

        // 画面のクリア
        ClearDrawScreen();


        pScene->Update();
        pScene->Draw();
        // 裏画面を表画面を入れ替える
        ScreenFlip();

        // escキーを押したら終了する
        if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

        // fpsを60に固定
        while (GetNowHiPerformanceCount() - time < 16667)
        {

        }
    }
    pScene->End();
    delete(pScene);
    DxLib_End();                // ＤＸライブラリ使用の終了処理

    return 0;                // ソフトの終了
}