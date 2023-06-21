#include "MdMusicPlayer.h"
#include "AudioFileSourceID3.h"
#include "AudioFileSourceSD.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include <Arduino.h>
#include <M5Stack.h>

AudioGeneratorMP3* mp3;
AudioFileSourceSD* file;
AudioOutputI2S* out;
AudioFileSourceID3* id3;

File musicfolder;
File entry;

void MdMusicPlayer::init()
{
    SD.begin();
    musicfolder = SD.open("/music");
    if (!musicfolder) {
        // musicフォルダが無かった場合、開けなかった場合
        Serial.println("musicfolder open error");
    } else {
        entry = musicfolder.openNextFile();
        Serial.println("open ");
    }
}

char* MdMusicPlayer::getTitle()
{
    return (char*)entry.name();//entry.neme()をcharのポインタ型に変換して返す
}

void MdMusicPlayer::selectNextMusic()
{
    entry = musicfolder.openNextFile();
    if (!entry) {
        musicfolder.rewindDirectory();
        entry = musicfolder.openNextFile();
        Serial.println("return latestfile");
    }
}

void MdMusicPlayer::prepareMP3()
{
    file = new AudioFileSourceSD(entry.path());
    id3 = new AudioFileSourceID3(file);
    out = new AudioOutputI2S(0, 1); // Output to builtInDAC
    out->SetOutputModeMono(true);
    out->SetGain(0.045);
    mp3 = new AudioGeneratorMP3();
    mp3->begin(id3, out);
}

bool MdMusicPlayer::isRunningMP3()
{
    return mp3->isRunning();
}

bool MdMusicPlayer::playMP3()
{
    return mp3->loop();
}

void MdMusicPlayer::stopMP3()
{
    mp3->stop();
}
