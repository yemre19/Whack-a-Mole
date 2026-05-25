#include "ScoreManager.h"

ScoreManager::ScoreManager()
{
  skor=0;
  vurusSayisi=0;
}

void ScoreManager::puanEkle(int miktar)
{
  skor += miktar;
}

void ScoreManager::sifirla()
{
    skor = 0;
}

int ScoreManager::getSkor()
{
    return this->skor;
}