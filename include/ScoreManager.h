#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#pragma once

class ScoreManager
{
public:
    ScoreManager();
    void sifirla();
    int getSkor();
    void puanEkle(int miktar);

    

private:

int skor;
int vurusSayisi;


};

#endif