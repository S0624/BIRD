#include "DxLib.h"
#include"Player.h"
#include"Camera.h"
#include"Map.h"
#include"BackGround.h"

#include "math.h"
#include "game.h"

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
    Player* pPlayer;
    pPlayer = new Player();
    Map* pMap;
    pMap = new Map();
    pMap->Load();
    BackGround* pBack;
    pBack = new BackGround();
    
    Camera* pCamera;
    pCamera = new Camera();

    // ダブルバッファモード
    SetDrawScreen(DX_SCREEN_BACK);

    while (ProcessMessage() == 0)
    {
        LONGLONG time = GetNowHiPerformanceCount();

        // 画面のクリア
        ClearDrawScreen();

        // デバッグ描画
#if _DEBUG
        //(仮決め)グリッドの表示
        VECTOR startY = VGet(0, 0.0f, -100.0f);		//線の始点
        VECTOR endY = VGet(0, 0.0f, 100.0f);		//線の終点
        DrawLine3D(startY, endY, 0x7fffd4);			//あお

        VECTOR startX = VGet(-100.0f, 0.0f, 0.0f);		//線の始点
        VECTOR endX = VGet(100.0f, 0.0f, -0.0f);			//線の終点
        DrawLine3D(startX, endX, 0xdc143c);			//あか
        float lineSize = 300.0f;
        // マップチップライン(課題当初のStageData1ColNum個(16)のマップチップをどう配置するか)
        // プレイヤーの地面をY=0としたいので、その周りを配置し、大体の基準でカメラを決める
        for (int i = 0; i < 16 + 2; i++)
        {
            // X軸とかぶるところはとりあえず描画しない
            if (i != 1)
            {
                float y = 10 * (i - 1); // 一個下のラインからチップが始まる
                DrawLine3D(VGet(-lineSize, y, 0), VGet(lineSize, y, 0), GetColor(255, 255, 0));
            }
        }
#endif // kWindowMode


        pPlayer->Update();
        pMap->Update();
        pBack->Update();
        pCamera->Update(*pPlayer);

        //pBack->Draw();
        pPlayer->Draw();
        pMap->Draw();

        // 裏画面を表画面を入れ替える
        ScreenFlip();

        // escキーを押したら終了する
        if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

        // fpsを60に固定
        while (GetNowHiPerformanceCount() - time < 16667)
        {

        }
    }

    DxLib_End();                // ＤＸライブラリ使用の終了処理

    return 0;                // ソフトの終了
}