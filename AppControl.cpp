//1.ソースコードの場合は必ずコンパイルが通り問題なく動作している状態でプッシュ→
//2.コミット字のコメントはどういう意図の変更を行ったかをコメントする
//3.定期的にプルを行う。
//4.コンフリクトを起こさないようにする。
#include "M5All-In-One-Gadget.h"
#include "AppControl.h"
#include <Arduino.h>
#include <M5Stack.h>
#include "MdLcd.h"

MdLcd mlcd;
MdWBGTMonitor mwbgt;
MdMusicPlayer mmplay;
MdMeasureDistance mmdist;
MdDateTime mdtime;


const char* g_str_orange[] = {
    COMMON_ORANGE0_IMG_PATH,
    COMMON_ORANGE1_IMG_PATH,
    COMMON_ORANGE2_IMG_PATH,
    COMMON_ORANGE3_IMG_PATH,
    COMMON_ORANGE4_IMG_PATH,
    COMMON_ORANGE5_IMG_PATH,
    COMMON_ORANGE6_IMG_PATH,
    COMMON_ORANGE7_IMG_PATH,
    COMMON_ORANGE8_IMG_PATH,
    COMMON_ORANGE9_IMG_PATH,
};

const char* g_str_blue[] = {
    COMMON_BLUE0_IMG_PATH,
    COMMON_BLUE1_IMG_PATH,
    COMMON_BLUE2_IMG_PATH,
    COMMON_BLUE3_IMG_PATH,
    COMMON_BLUE4_IMG_PATH,
    COMMON_BLUE5_IMG_PATH,
    COMMON_BLUE6_IMG_PATH,
    COMMON_BLUE7_IMG_PATH,
    COMMON_BLUE8_IMG_PATH,
    COMMON_BLUE9_IMG_PATH,
};

void AppControl::setBtnAFlg(bool flg)
{
    m_flag_btnA_is_pressed = flg;
}

void AppControl::setBtnBFlg(bool flg)
{
    m_flag_btnB_is_pressed = flg;
}

void AppControl::setBtnCFlg(bool flg)
{
    m_flag_btnC_is_pressed = flg;
}

void AppControl::setBtnAllFlgFalse()
{
    m_flag_btnA_is_pressed = false;
    m_flag_btnB_is_pressed = false;
    m_flag_btnC_is_pressed = false;
}

State AppControl::getState()
{
    return m_state;
}

void AppControl::setState(State state)
{
    m_state = state;
}

Action AppControl::getAction()
{
    return m_action;
}

void AppControl::setAction(Action action)
{
    m_action = action;
}

void AppControl::setStateMachine(State state, Action action)
{
    setState(state);
    setAction(action);
}

FocusState AppControl::getFocusState()
{
    return m_focus_state;
}

void AppControl::setFocusState(FocusState fs)
{
    m_focus_state = fs;
}

void AppControl::displayTitleInit()
{  
    mlcd.displayJpgImageCoordinate(TITLE_IMG_PATH,TITLE_X_CRD,TITLE_Y_CRD);
}

void AppControl::displayMenuInit()
{
    mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH,MENU_WBGT_X_CRD,MENU_WBGT_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH,MENU_MUSIC_X_CRD,MENU_MUSIC_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH,MENU_MEASURE_X_CRD,MENU_MEASURE_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH ,MENU_DATE_X_CRD,MENU_DATE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_UP_IMG_PATH ,COMMON_BUTTON_UP_X_CRD,COMMON_BUTTON_UP_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DECIDE_IMG_PATH ,COMMON_BUTTON_DECIDE_X_CRD,COMMON_BUTTON_DECIDE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DOWN_IMG_PATH ,COMMON_BUTTON_DOWN_X_CRD,COMMON_BUTTON_DOWN_Y_CRD);
 
}

void AppControl::focusChangeImg(FocusState current_state, FocusState next_state)
{
}

void AppControl::displayWBGTInit()
{   
    mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH,MENU_WBGT_X_CRD,MENU_WBGT_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH,MENU_MUSIC_X_CRD,MENU_MUSIC_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH,MENU_MEASURE_X_CRD,MENU_MEASURE_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH ,MENU_DATE_X_CRD,MENU_DATE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_UP_IMG_PATH ,COMMON_BUTTON_UP_X_CRD,COMMON_BUTTON_UP_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DECIDE_IMG_PATH ,COMMON_BUTTON_DECIDE_X_CRD,COMMON_BUTTON_DECIDE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DOWN_IMG_PATH ,COMMON_BUTTON_DOWN_X_CRD,COMMON_BUTTON_DOWN_Y_CRD);

}

void AppControl::displayTempHumiIndex()
{
}

void AppControl::displayMusicInit()
{
     mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH,MENU_WBGT_X_CRD,MENU_WBGT_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_FOCUS_IMG_PATH,MENU_MUSIC_X_CRD,MENU_MUSIC_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH,MENU_MEASURE_X_CRD,MENU_MEASURE_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH ,MENU_DATE_X_CRD,MENU_DATE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_UP_IMG_PATH ,COMMON_BUTTON_UP_X_CRD,COMMON_BUTTON_UP_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DECIDE_IMG_PATH ,COMMON_BUTTON_DECIDE_X_CRD,COMMON_BUTTON_DECIDE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DOWN_IMG_PATH ,COMMON_BUTTON_DOWN_X_CRD,COMMON_BUTTON_DOWN_Y_CRD);
}

void AppControl::displayMusicStop()
{
}

void AppControl::displayMusicTitle()
{
}

void AppControl::displayNextMusic()
{
}

void AppControl::displayMusicPlay()
{
}

void AppControl::displayMeasureInit()
{
}

void AppControl::displayMeasureDistance()
{
}

void AppControl::displayDateInit()
{
}

void AppControl::displayDateUpdate()
{
}

void AppControl::controlApplication()
{
    while (1) {//while(1)によりtrueになっているので無限ループになる

        switch (getState()) {
        case TITLE:
            switch (getAction()) {
            case ENTRY:
                /*
                ** まずはここにタイトル画面の表示処理を呼び出してみよう。
                ** タイトル画面表示の関数はdisplayTitleInit()である。
                ** この関数の中身はまだ何もないので、この関数にタイトル画面表示処理を書いてみよう。
                */ 
             displayTitleInit();//タイトル画面の呼び出し
             setStateMachine(TITLE,DO);
                break;


            case DO:
            if (m_flag_btnA_is_pressed || m_flag_btnB_is_pressed || m_flag_btnC_is_pressed) {
            mlcd.clearDisplay();	
            setStateMachine(MENU,ENTRY);
            }         
                break;

            case EXIT:
            setStateMachine(TITLE,ENTRY);
                break;

            default:
                break;
            }

            break;



        case MENU:

            switch (getAction()) {
            
            case ENTRY:
             displayMenuInit();//メニュー画面の呼び出し
             setStateMachine(MENU,DO);
                break;

            case DO:
              if(m_flag_btnC_is_pressed){
                displayWBGTInit();
                if(m_flag_btnC_is_pressed){
                    setStateMachine(MUSIC_STOP,ENTRY);
                }
             }
             else
             setStateMachine(MENU,ENTRY);

             
                break;

            case EXIT:

            default:
                break;
            }

            break;

        case WBGT:

            switch (getAction()) {
            case ENTRY:

                break;

            case DO:
                break;

            case EXIT:
                break;

            default:
                break;
            }

            break;

        case MUSIC_STOP:
            switch (getAction()) {
            case ENTRY:
            displayMusicInit();
                break;

            case DO:
                break;

            case EXIT:
                break;

            default:
                break;
            }

            break;

        case MUSIC_PLAY:

            switch (getAction()) {
            case ENTRY:
                break;

            case DO:
                break;

            case EXIT:
                break;

            default:
                break;
            }

            break;

        case MEASURE:

            switch (getAction()) {
            case ENTRY:
                break;

            case DO:
                break;

            case EXIT:
                break;

            default:
                break;
            }

            break;

        case DATE:

            switch (getAction()) {
            case ENTRY:
                break;

            case DO:
                break;

            case EXIT:
                break;

            default:
                break;
            }

        default:
            break;
        }
    }
}
