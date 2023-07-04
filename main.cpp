#include "Common.h"
#include"Object/Player.h"
#include"Camera/Camera.h"
#include"Stage/Map.h"
#include"Object/BackGround.h"
#include"Scene/SceneManager.h"

#include "math.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    // window���[�h�ݒ�
    ChangeWindowMode(Game::kWindowMode);

    // �E�C���h�E���ݒ�
    SetMainWindowText("BIRD");

    // ��ʃT�C�Y�̐ݒ�
    SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
    SetWindowSizeChangeEnableFlag(true);//�E�B���h�E���[�h�̊g��k���i�T�C�Y�ύX�j
    SetAlwaysRunFlag(true);

    if (DxLib_Init() == -1)        // �c�w���C�u��������������
    {
        return -1;            // �G���[���N�����璼���ɏI��
    }

    SceneManager* pScene;
    pScene = new SceneManager;
    pScene->Init();

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
        float lineSize = 300.0f;
        // �}�b�v�`�b�v���C��(�ۑ蓖����StageData1ColNum��(16)�̃}�b�v�`�b�v���ǂ��z�u���邩)
        // �v���C���[�̒n�ʂ�Y=0�Ƃ������̂ŁA���̎����z�u���A��̂̊�ŃJ���������߂�
        for (int i = 0; i < 16 + 2; i++)
        {
            // X���Ƃ��Ԃ�Ƃ���͂Ƃ肠�����`�悵�Ȃ�
            if (i != 1)
            {
                float y = 10 * (i - 1); // ����̃��C������`�b�v���n�܂�
                DrawLine3D(VGet(-lineSize, y, 0), VGet(lineSize, y, 0), GetColor(255, 255, 0));
            }
        }
#endif // kWindowMode

        pScene->Update();
        pScene->Draw();
        // ����ʂ�\��ʂ����ւ���
        ScreenFlip();

        // esc�L�[����������I������
        if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

        // fps��60�ɌŒ�
        while (GetNowHiPerformanceCount() - time < 16667)
        {

        }
    }
    pScene->End();
    delete(pScene);
    DxLib_End();                // �c�w���C�u�����g�p�̏I������

    return 0;                // �\�t�g�̏I��
}