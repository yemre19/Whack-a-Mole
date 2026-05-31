# Whack-a-Mole 

Bu proje, C++ ve SDL2 kütüphanesi kullanılarak geliştirilmiş, refleks geliştirmeye yönelik bir "Aim Trainer" oyunudur.

## Proje Hakkında
- **Geliştirici:** Yunus Emre Eren
- **Ders:** [Programlama-2]
- **Amaç:** Oyuncunun hedef takip etme ve tepki süresini optimize eden, düşük gecikmeli bir 2D oyun deneyimi sunmak.

## Kullanılan Teknolojiler
- C++ (OOP Prensipleri)
- SDL2 (Core, Image, TTF)
- VS Code & MSYS2

## Kurulum ve Çalıştırma
Projenin çalışması için gerekli tüm DLL dosyaları ve `assets` klasörü ana dizinde yer almaktadır.

1. Projeyi bilgisayarınıza indirin.
2. Ana dizindeki `oyun.exe` dosyasına çift tıklayarak oyunu başlatın.
3. Kendi geliştirme ortamınızda derlemek isterseniz, `Makefile` kullanarak `make` komutu ile derleme yapabilirsiniz.

## Kontroller
- **Menü Navigasyonu:** Fare ile etkileşim.
- **Oyun İçi:** Fare ile hedef vurma.
- **Geri Dönüş:** 'BACKSPACE' tuşu.
- **Çıkış:** 'ESC' tuşu.

## Özellikler
- Dinamik zorluk seviyeleri (Kolay, Orta, Zor, Çok Zor).
- 30 ve 60 saniyelik oyun modları.
- Anlık skor, seri (combo) ve isabet oranı takibi.
- Fütüristik neon görsel tema.