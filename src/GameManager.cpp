#include "GameManager.h"
#include <iostream>
#include <string>

GameManager::GameManager()
{
    mevcutDurum = OyunDurumu::ANA_MENU;
    secilenSure=30;
    secilenHiz=5;
    secilenSpawnSuresi=2000;
    aktifPortal=0;
}

void GameManager::setDurum(OyunDurumu yeniDurum)
{
    mevcutDurum=yeniDurum;
}

OyunDurumu GameManager::getDurum()
{
    return this->mevcutDurum;
}

