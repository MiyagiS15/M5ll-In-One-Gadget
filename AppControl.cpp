//1.ソースコードの場合は必ずコンパイルが通り問題なく動作している状態でプッシュ→
//2.コミット字のコメントはどういう意図の変更を行ったかをコメントする
//3.定期的にプルを行う。
//4.コンフリクトを起こさないようにする。
#include "M5All-In-One-Gadget.h"
#include "AppControl.h"
#include <Arduino.h>
#include <M5Stack.h>
#include "MdLcd.h"
#include "MdDateTime.h"
#include "DrTHSensor.h"
#include "DrUltraSonic.h"

//インスタンス化
MdLcd mlcd;
MdWBGTMonitor mwbgt;
MdMusicPlayer mmplay;
MdMeasureDistance mmdist;
MdDateTime mdtime;


//グローバル変数
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
    mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH,MENU_WBGT_X_CRD,MENU_WBGT_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH,MENU_MUSIC_X_CRD,MENU_MUSIC_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH,MENU_MEASURE_X_CRD,MENU_MEASURE_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH ,MENU_DATE_X_CRD,MENU_DATE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_UP_IMG_PATH ,COMMON_BUTTON_UP_X_CRD,COMMON_BUTTON_UP_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DECIDE_IMG_PATH ,COMMON_BUTTON_DECIDE_X_CRD,COMMON_BUTTON_DECIDE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DOWN_IMG_PATH ,COMMON_BUTTON_DOWN_X_CRD,COMMON_BUTTON_DOWN_Y_CRD);
 
}

void AppControl::focusChangeImg(FocusState current_state, FocusState next_state)
{
     mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH,MENU_WBGT_X_CRD,MENU_WBGT_Y_CRD);
     mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH,MENU_MUSIC_X_CRD,MENU_MUSIC_Y_CRD);	
     mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH,MENU_MEASURE_X_CRD,MENU_MEASURE_Y_CRD);	
     mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH,MENU_DATE_X_CRD,MENU_DATE_Y_CRD);	
   

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
    mlcd.displayJpgImageCoordinate(WBGT_SAFE_IMG_PATH,WBGT_SAFE_X_CRD,WBGT_SAFE_Y_CRD);
    mlcd.displayJpgImageCoordinate(WBGT_TEMPERATURE_IMG_PATH,WBGT_TEMPERATURE_X_CRD,WBGT_TEMPERATURE_Y_CRD);
    mlcd.displayJpgImageCoordinate(WBGT_HUMIDITY_IMG_PATH,WBGT_HUMIDITY_X_CRD,WBGT_HUMIDITY_Y_CRD);
    mlcd.displayJpgImageCoordinate(WBGT_DEGREE_IMG_PATH,WBGT_DEGREE_X_CRD,WBGT_DEGREE_Y_CRD);
    mlcd.displayJpgImageCoordinate(WBGT_PERCENT_IMG_PATH,WBGT_PERCENT_X_CRD,WBGT_PERCENT_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH,COMMON_BUTTON_X_CRD,COMMON_BUTTON_Y_CRD);
}

void AppControl::displayTempHumiIndex()
{
    double temperature = 0;
    double humidity = 0;
    WbgtIndex index = SAFE;

    mwbgt.getWBGT(&temperature,&humidity,&index);//&変数でアドレスの取得、getWBGTに&temperature,&humidity,&indexのアドレスを引数として渡す。

    int calc_result = 0.68 * (temperature) + 0.12 * (humidity);

    if (calc_result <= 15) {//安全画像の出力
    mlcd.displayJpgImageCoordinate(WBGT_SAFE_IMG_PATH,WBGT_SAFE_X_CRD,WBGT_SAFE_Y_CRD);
    }
    else if (calc_result <= 24) {//注意画像の出力
    mlcd.displayJpgImageCoordinate(WBGT_ATTENTION_IMG_PATH,WBGT_ATTENTION_X_CRD,WBGT_ATTENTION_Y_CRD);
    }
    else if (calc_result <= 27) {//警戒画像の出力
    mlcd.displayJpgImageCoordinate(WBGT_ALERT_IMG_PATH,WBGT_ALERT_X_CRD,WBGT_ALERT_Y_CRD);
    }
    else if (calc_result <= 30) {//厳重警戒画像の出力
    mlcd.displayJpgImageCoordinate(WBGT_HIGH_ALERT_IMG_PATH,WBGT_HIGH_ALERT_X_CRD,WBGT_HIGH_ALERT_Y_CRD);
    }
    else{//危険画像の出力
    mlcd.displayJpgImageCoordinate(WBGT_DANGER_IMG_PATH,WBGT_DANGER_X_CRD,WBGT_DANGER_Y_CRD);
    }


Serial.println(temperature);//取得した温度を画面に表示
    int tempInt = (int)temperature;
    int t_digit1 = (tempInt / 10)%10;
    int t_digit2 = tempInt % 10;
    int t_decimal = (int)(temperature * 10) % 10;

    const char* t_imagePath1 = g_str_orange[t_digit1];
    const char* t_imagePath2 = g_str_orange[t_digit2];
    const char* t_imagePathDecimal = g_str_orange[t_decimal];

    mlcd.displayJpgImageCoordinate(t_imagePath1, WBGT_T2DIGIT_X_CRD, WBGT_T2DIGIT_Y_CRD);
    mlcd.displayJpgImageCoordinate(t_imagePath2,WBGT_T1DIGIT_X_CRD,WBGT_T1DIGIT_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_ORANGEDOT_IMG_PATH,WBGT_TDOT_X_CRD,WBGT_TDOT_Y_CRD);
    mlcd.displayJpgImageCoordinate(t_imagePathDecimal,WBGT_T1DECIMAL_X_CRD,WBGT_T1DECIMAL_Y_CRD);


    Serial.println(humidity);//取得した湿度を画面に表示
    int humiInt = (int)humidity;
    int h_digit1 = (humiInt / 10)%10;
    int h_digit2 = humiInt % 10;
    int h_decimal = (int)(humidity * 10) % 10;

    const char* h_imagePath1 = g_str_blue[h_digit1];
    const char* h_imagePath2 = g_str_blue[h_digit2];
    const char* h_imagePathDecimal = g_str_blue[h_decimal];

    mlcd.displayJpgImageCoordinate(h_imagePath1, WBGT_H2DIGIT_X_CRD, WBGT_H2DIGIT_Y_CRD);
    mlcd.displayJpgImageCoordinate(h_imagePath2,WBGT_H1DIGIT_X_CRD,WBGT_H1DIGIT_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH,WBGT_HDOT_X_CRD,WBGT_HDOT_Y_CRD);
    mlcd.displayJpgImageCoordinate(h_imagePathDecimal,WBGT_H1DECIMAL_X_CRD,WBGT_H1DECIMAL_Y_CRD);
}


void AppControl::displayMusicInit()
{
    mlcd.displayJpgImageCoordinate(MUSIC_NOWSTOPPING_IMG_PATH,MUSIC_NOWSTOPPING_X_CRD,MUSIC_NOWSTOPPING_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_NEXT_IMG_PATH,COMMON_BUTTON_NEXT_X_CRD,COMMON_BUTTON_NEXT_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_PLAY_IMG_PATH,COMMON_BUTTON_PLAY_X_CRD,COMMON_BUTTON_PLAY_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH,COMMON_BUTTON_X_CRD,COMMON_BUTTON_Y_CRD);
 }

void AppControl::displayMusicStop()
{
    mlcd.displayJpgImageCoordinate(MUSIC_NOWSTOPPING_IMG_PATH,MUSIC_NOWSTOPPING_X_CRD,MUSIC_NOWSTOPPING_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_NEXT_IMG_PATH,COMMON_BUTTON_NEXT_X_CRD,COMMON_BUTTON_NEXT_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_PLAY_IMG_PATH,COMMON_BUTTON_PLAY_X_CRD,COMMON_BUTTON_PLAY_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH,COMMON_BUTTON_X_CRD,COMMON_BUTTON_Y_CRD);

}

void AppControl::displayMusicTitle()
{
   
   char* title = mmplay.getTitle();
   Serial.println(title);
   mlcd.displayText(title,10,120);			

}

void AppControl::displayNextMusic()
{
    
    mmplay.selectNextMusic();
    char* title = mmplay.getTitle();
    Serial.println(title);
    mlcd.displayText(title,10,120);
}

void AppControl::displayMusicPlay()
{
    mlcd.displayJpgImageCoordinate(MUSIC_NOWPLAYING_IMG_PATH,MUSIC_NOWSTOPPING_X_CRD,MUSIC_NOWSTOPPING_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_STOP_IMG_PATH,COMMON_BUTTON_STOP_X_CRD,COMMON_BUTTON_STOP_Y_CRD);       
}

void AppControl::displayMeasureInit()
{   
   mlcd.clearDisplay();
    mlcd.fillBackgroundWhite();
    mlcd.displayJpgImageCoordinate(MEASURE_NOTICE_IMG_PATH, MEASURE_NOTICE_X_CRD, MEASURE_NOTICE_Y_CRD);
    mlcd.displayJpgImageCoordinate(MEASURE_CM_IMG_PATH, MEASURE_CM_X_CRD, MEASURE_CM_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, MEASURE_BACK_X_CRD, MEASURE_BACK_Y_CRD);
    displayMeasureDistance();
}

void AppControl::displayMeasureDistance()
{
   double dist = mmdist.getDistance();
    Serial.println(dist);
    if (dist >= 400 || dist < 0) {
        return;
    }

    int digit3 = (int)dist / 100;
    int digit2 = ((int)dist / 10) % 10;
    int digit1 = (int)dist % 10;
    int decimal = (int)(dist * 10) % 10;

    if (digit3 == 0) {
        mlcd.displayJpgImageCoordinate(COMMON_BLUEFILLWHITE_IMG_PATH, MEASURE_DIGIT3_X_CRD, MEASURE_DIGIT3_Y_CRD);
    } else {
        mlcd.displayJpgImageCoordinate(g_str_blue[digit3], MEASURE_DIGIT3_X_CRD, MEASURE_DIGIT3_Y_CRD);
    }

    if (digit2 == 0 && dist < 10) {
        mlcd.displayJpgImageCoordinate(COMMON_BLUEFILLWHITE_IMG_PATH, MEASURE_DIGIT2_X_CRD, MEASURE_DIGIT2_Y_CRD);
    } else {
        mlcd.displayJpgImageCoordinate(g_str_blue[digit2], MEASURE_DIGIT2_X_CRD, MEASURE_DIGIT2_Y_CRD);
    }

    mlcd.displayJpgImageCoordinate(g_str_blue[digit1], MEASURE_DIGIT1_X_CRD, MEASURE_DIGIT1_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH, MEASURE_DOT_X_CRD, MEASURE_DOT_Y_CRD);
    mlcd.displayJpgImageCoordinate(g_str_blue[decimal], MEASURE_DECIMAL_X_CRD, MEASURE_DECIMAL_Y_CRD);
    
}

void AppControl::displayDateInit()
{
    mlcd.clearDisplay();
    mlcd.fillBackgroundWhite();

    mlcd.displayJpgImageCoordinate(DATE_NOTICE_IMG_PATH, DATE_NOTICE_X_CRD, DATE_NOTICE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, DATE_BACK_X_CRD, DATE_BACK_Y_CRD);

    displayDateUpdate();
   
}

void AppControl::displayDateUpdate()
{   
  mlcd.displayDateText(mdtime.readDate(), DATE_YYYYMMDD_X_CRD, DATE_YYYYMMDD_Y_CRD);
    mlcd.displayDateText(mdtime.readTime(), DATE_HHmmSS_X_CRD, DATE_HHmmSS_Y_CRD);
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
            break;


        case DO:
            setStateMachine(TITLE,EXIT);
            break;

        case EXIT:
            setStateMachine(TITLE,ENTRY);
            if (m_flag_btnA_is_pressed || m_flag_btnB_is_pressed || m_flag_btnC_is_pressed) { //ボタンを押した際にMENU画面に移行
            mlcd.fillBackgroundWhite();	
            setStateMachine(MENU,ENTRY);
            setBtnAllFlgFalse();//これがないとボタンが押しっぱなしの状態
            }
            break;

            default:
            break;
            }

            break;



//ここからMENUの始まり
        case MENU:
        switch (getAction()) {
            
            case ENTRY:
            mlcd.fillBackgroundWhite();	
            displayMenuInit();//メニュー画面の呼び出し
            setStateMachine(MENU,DO);
            break;

//DO
            case DO:
            if(m_flag_btnC_is_pressed){
            setBtnAllFlgFalse();
           
                    
        switch(getFocusState()){       //初期状態ではFocusState m_focus_state = MENU_WBGT;の中身が入ってくる。
                     
            case MENU_WBGT:  
            focusChangeImg( MENU_WBGT,MENU_MUSIC);
            setFocusState(MENU_MUSIC);  
            break; 
                  

            case MENU_MUSIC:                 
            focusChangeImg(MENU_MUSIC,MENU_MEASURE);
            setFocusState(MENU_MEASURE); 
            break;
                    
            case MENU_MEASURE: 
            focusChangeImg(MENU_MEASURE,MENU_DATE);
            setFocusState(MENU_DATE);       
            break;
                     
            case MENU_DATE:  
            focusChangeImg(MENU_DATE,MENU_WBGT);
            setFocusState(MENU_WBGT);       
            break;               
            }         
        }  



     if(m_flag_btnA_is_pressed){
             setBtnAllFlgFalse();
           
                    
        switch(getFocusState()){       //   FocusState m_focus_state = MENU_WBGT;の中身が入ってくる。
                     
            case MENU_WBGT: 
            focusChangeImg( MENU_WBGT,MENU_DATE);
            setFocusState(MENU_DATE);  
            break; 
                  

            case MENU_DATE:                 
            focusChangeImg(MENU_DATE,MENU_MEASURE);
            setFocusState(MENU_MEASURE); 
            break;
                    
            case MENU_MEASURE: 
            focusChangeImg( MENU_MEASURE,MENU_MUSIC);
            setFocusState(MENU_MUSIC);       
            break;
                     
            case MENU_MUSIC:     
            focusChangeImg(MENU_MUSIC,MENU_WBGT);
            setFocusState(MENU_WBGT);       
            break;               
            }         
        }  

            if(m_flag_btnB_is_pressed==true){ 
            setStateMachine(MENU,EXIT);      
            } 

   
            break;
//ここまでがMENUのDOの中身



    case EXIT:
     if(m_flag_btnB_is_pressed){
             setBtnAllFlgFalse();
           
                    
     switch(getFocusState()){       //   FocusState m_focus_state = MENU_WBGT;の中身が入ってくる。
                     
            case MENU_WBGT: 
            setStateMachine(WBGT,ENTRY);    
            break; 
                  
            case MENU_MUSIC:                 
            setStateMachine(MUSIC_STOP,ENTRY);    
            break;
                    
            case MENU_MEASURE: 
            setStateMachine(MEASURE,ENTRY);       
            break;
                     
            case MENU_DATE:     
            setStateMachine(DATE,ENTRY);       
            break;               
            }         
            }  

            break;
            
            }
            break;
//case MENUの処理の終わり





//熱中症処理の始まり
    case WBGT:

        switch (getAction()) {
            case ENTRY:
            mlcd.fillBackgroundWhite();
            displayWBGTInit();
            setStateMachine(WBGT,DO); 
            break;

            case DO:
            displayTempHumiIndex();
            setStateMachine(WBGT,EXIT);
            break;

            case EXIT:
            setStateMachine(WBGT,DO);
            if(m_flag_btnB_is_pressed){
            setStateMachine(MENU,ENTRY); 
            setBtnAllFlgFalse();
            }  
            break;
            
            default:
            break;
            }
            break;
//熱中症処理の終わり







//音楽停止画面の始まり
    case MUSIC_STOP:
        switch (getAction()) {
            case ENTRY:
            setBtnAllFlgFalse();
            mlcd.fillBackgroundWhite();	//画面白にリセット  
            displayMusicInit();//初期画面の呼び出し
            mmplay.init();//音楽プレーヤーの初期化
            setStateMachine(MUSIC_STOP,DO); 
            break;

            case DO:	
            displayMusicTitle();
            setStateMachine(MUSIC_STOP,EXIT);
            break;

            case EXIT:
            if(m_flag_btnB_is_pressed){
            setBtnAllFlgFalse();
            setStateMachine(MENU,ENTRY); 
            }

            else if(m_flag_btnA_is_pressed){
            setBtnAllFlgFalse();
            mlcd.fillBackgroundWhite();	
            setStateMachine(MUSIC_PLAY,ENTRY); 
            }  

            if(m_flag_btnC_is_pressed){
            setBtnAllFlgFalse();
            displayNextMusic();
             mlcd.fillBackgroundWhite();
            displayMusicInit();//初期画面の呼び出し
            setStateMachine(MUSIC_STOP,DO); 
            }
            break;
            default:
            break;
            }
            break;
//音楽停止画面の終わり



//音楽再生画面の始まり
        case MUSIC_PLAY:

            switch (getAction()) {
            case ENTRY:
            setBtnAllFlgFalse();
            displayMusicPlay();
            mmplay.prepareMP3();
            setStateMachine(MUSIC_PLAY,DO); 
             //setStateMachine(MUSIC_PLAY,ENTRY);
            break;

            case DO:
            mmplay.playMP3();
            setStateMachine(MUSIC_PLAY,DO);
            if(m_flag_btnA_is_pressed){
            setBtnAllFlgFalse();
            mmplay.stopMP3();
            setStateMachine(MUSIC_PLAY,EXIT); 
            } 
            break;

            case EXIT:
            setBtnAllFlgFalse();
            setStateMachine(MUSIC_STOP,ENTRY); 
            break;

            default:
            break;
            }

            break;
//音楽再生画面の終わり




//距離測定の始まり
          case MEASURE:

            switch (getAction()) {
            case ENTRY:
                displayMeasureInit();
                setStateMachine(MEASURE, DO);
                break;

            case DO:
                delay(250);
                displayMeasureDistance();
                if (m_flag_btnB_is_pressed) {
                    setStateMachine(MEASURE, EXIT);
                }
                break;

            case EXIT:
                setStateMachine(MENU, ENTRY);
                setBtnAllFlgFalse();
                break;

            default:
                break;
            }

            break;
//距離測定の終わり



//時刻表示処理始まり
    case DATE:
         switch (getAction()) {
            case ENTRY:
                displayDateInit();
                setStateMachine(DATE, DO);
                break;

            case DO:
                displayDateUpdate();
                delay(100);
                if (m_flag_btnB_is_pressed) {
                    setStateMachine(DATE, EXIT);
                }
                break;

            case EXIT:
                setStateMachine(MENU, ENTRY);
                setBtnAllFlgFalse();
                break;

            default:
                break;
            }

            break;
//時刻表示終わり
    

    case HIGHLOW:
    switch (getAction()) {
          
          case ENTRY:
          break;

          case DO:
          break;

          case EXIT:
          break;
          
          }
            break;


        }
       
    }

}
