#include "DxLib.h"
#include"Player.h"
#include"Camera.h"

#include "math.h"
#include "game.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    // window���[�h�ݒ�
    ChangeWindowMode(Game::kWindowMode);

    // �E�C���h�E���ݒ�
    SetMainWindowText("BIRD");

    // ��ʃT�C�Y�̐ݒ�
    SetGraphMode(Game::kScreenWindth, Game::kScreenHeight, Game::kColorDepth);
    SetWindowSizeChangeEnableFlag(true);//�E�B���h�E���[�h�̊g��k���i�T�C�Y�ύX�j
    SetAlwaysRunFlag(true);

    if (DxLib_Init() == -1)        // �c�w���C�u��������������
    {
        return -1;            // �G���[���N�����璼���ɏI��
    }
    Player* pPlayer;
    pPlayer = new Player();  
    
    Camera* pCamera;
    pCamera = new Camera();

    // �_�u���o�b�t�@���[�h
    SetDrawScreen(DX_SCREEN_BACK);

    while (ProcessMessage() == 0)
    {
        LONGLONG time = GetNowHiPerformanceCount();

        // ��ʂ̃N���A
        ClearDrawScreen();

        // �f�o�b�O�`��
#if _DEBUG
        //(������)�O���b�h�̕\��
        VECTOR startY = VGet(0, 0.0f, -100.0f);		//���̎n�_
        VECTOR endY = VGet(0, 0.0f, 100.0f);		//���̏I�_
        DrawLine3D(startY, endY, 0x7fffd4);			//����

        VECTOR startX = VGet(-100.0f, 0.0f, 0.0f);		//���̎n�_
        VECTOR endX = VGet(100.0f, 0.0f, -0.0f);			//���̏I�_
        DrawLine3D(startX, endX, 0xdc143c);			//����
#endif // kWindowMode


        pPlayer->Update();
        pCamera->Update(*pPlayer);

        pPlayer->Draw();

        // ����ʂ�\��ʂ����ւ���
        ScreenFlip();

        // esc�L�[����������I������
        if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

        // fps��60�ɌŒ�
        while (GetNowHiPerformanceCount() - time < 16667)
        {

        }
    }

    DxLib_End();                // �c�w���C�u�����g�p�̏I������

    return 0;                // �\�t�g�̏I��
}