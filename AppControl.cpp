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
    switch(current_state){
    case MENU_WBGT:
     mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH,MENU_WBGT_FOCUS_X_CRD,MENU_WBGT_FOCUS_Y_CRD);
  
    break;
    case MENU_MUSIC:
     mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH,MENU_MUSIC_FOCUS_X_CRD,MENU_MUSIC_FOCUS_Y_CRD);	
    break;
    case MENU_MEASURE:
     mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH,MENU_MEASURE_FOCUS_X_CRD,MENU_MEASURE_FOCUS_Y_CRD);	
    break;
    case MENU_DATE:
     mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH,MENU_DATE_FOCUS_X_CRD,MENU_DATE_FOCUS_Y_CRD);	
    break;
    }

    switch(next_state){
    case MENU_WBGT:
     mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH,MENU_WBGT_FOCUS_X_CRD,MENU_WBGT_FOCUS_Y_CRD);
    break;
    case MENU_MUSIC:
     mlcd.displayJpgImageCoordinate(MENU_MUSIC_FOCUS_IMG_PATH,MENU_MUSIC_FOCUS_X_CRD,MENU_MUSIC_FOCUS_Y_CRD);	
    break;
    case MENU_MEASURE:
     mlcd.displayJpgImageCoordinate(MENU_MEASURE_FOCUS_IMG_PATH,MENU_MEASURE_FOCUS_X_CRD,MENU_MEASURE_FOCUS_Y_CRD);	
    break;
    case MENU_DATE:
     mlcd.displayJpgImageCoordinate(MENU_DATE_FOCUS_IMG_PATH,MENU_DATE_FOCUS_X_CRD,MENU_DATE_FOCUS_Y_CRD);	
    break;
    }
 
}

void AppControl::displayWBGTInit()
{   
    

}

void AppControl::displayTempHumiIndex()
{
}

void AppControl::displayMusicInit()
{
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

    mmplay.init();
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
                //if(setBtnAllFlgFalse(true))
                 if (m_flag_btnA_is_pressed || m_flag_btnB_is_pressed || m_flag_btnC_is_pressed) { //ボタンを押した際にMENU画面に移行
                    mlcd.fillBackgroundWhite();	
                    setStateMachine(MENU,ENTRY);
                }
            break;


            case DO:
                setStateMachine(TITLE,EXIT);
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
               mlcd.fillBackgroundWhite();	
               displayMenuInit();//メニュー画面の呼び出し
                setStateMachine(MENU,DO);
            break;



            case DO:
   switch(getFocusState()){


                  case MENU_WBGT:
                      
                       Serial.println("1");
                       setFocusState(MENU_WBGT);
                         if(m_flag_btnC_is_pressed==true){
                       setBtnAllFlgFalse();//ボタンがおされていない状態にする：全部false
                      Serial.println("a");
                         
                           displayMenuInit();
                             getFocusState();
                      setFocusState(MENU_WBGT);//現在のフォーカス状態の設定
                     
                      focusChangeImg(MENU_WBGT,MENU_MUSIC);
                      }
                      else if(m_flag_btnA_is_pressed==true){
                        setBtnAllFlgFalse();
                       Serial.println("A");
                           displayMenuInit();
                       setFocusState(MENU_WBGT);
                        displayMenuInit();
                      focusChangeImg(MENU_WBGT, MENU_DATE);
                      }
                      else  
                       setFocusState(MENU_WBGT);
  Serial.println("@");
                      focusChangeImg(MENU_WBGT, MENU_MUSIC);
                    break;

                    case MENU_MUSIC:
                       Serial.println("2");

                       if(m_flag_btnC_is_pressed==true){
                      setBtnAllFlgFalse();//ボタンがおされていない状態にする：全部false
                      Serial.println("b");
                           displayMenuInit();	
                      setFocusState(MENU_MEASURE);//現在のフォーカス状態の設定
                       getFocusState();
                      focusChangeImg(MENU_MUSIC,MENU_MEASURE);
                      }


                      else if(m_flag_btnA_is_pressed==true){
                        setBtnAllFlgFalse();
                        Serial.println("B");
                           displayMenuInit();
                        setFocusState(MENU_MUSIC);
                      focusChangeImg(MENU_MUSIC, MENU_WBGT);
                    }



                    else
                      setFocusState(MENU_WBGT);
                    focusChangeImg(MENU_MUSIC,MENU_MUSIC);

                    break;





                    case MENU_MEASURE:
                 
                       Serial.println("3");
                         if(m_flag_btnC_is_pressed==true){
                       setBtnAllFlgFalse();//ボタンがおされていない状態にする：全部false
                      Serial.println("c");  
                           displayMenuInit();	
                      setFocusState(MENU_DATE);//現在のフォーカス状態の設定
                      focusChangeImg(MENU_MEASURE,MENU_DATE);
                      }

                      else if(m_flag_btnA_is_pressed==true){
                        setBtnAllFlgFalse();
                        Serial.println("C");
                           displayMenuInit();
                        setFocusState(MENU_MUSIC);
                      focusChangeImg(MENU_MEASURE, MENU_MUSIC);
                    }
                      else
                       setFocusState(MENU_MEASURE);
                      focusChangeImg(MENU_MEASURE, MENU_MEASURE);
                    break;


                  case MENU_DATE:{}
                      displayDateInit();
                       Serial.println("4");
                     if(m_flag_btnC_is_pressed==true){
                       setBtnAllFlgFalse();//ボタンがおされていない状態にする：全部false
                      Serial.println("d");
                           displayMenuInit();	
                      setFocusState(MENU_WBGT);//現在のフォーカス状態の設定
                      focusChangeImg(MENU_DATE,MENU_WBGT);
                      }

                      else if(m_flag_btnA_is_pressed==true){
                        setBtnAllFlgFalse();
                        Serial.println("D");
                           displayMenuInit();
                        setFocusState(MENU_MEASURE);
                      focusChangeImg(MENU_DATE, MENU_MEASURE);
                    }
                      else
                       setFocusState(MENU_DATE);
                      focusChangeImg(MENU_DATE, MENU_DATE);
                    break;

                  default:
                  break;
                }    
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
