# Cyber-Whack-a-Mole

Bu proje, C++ ve SDL2 kütüphanesi kullanılarak geliştirilmiş, refleks geliştirmeye yönelik bir nişan alma oyunudur.

## Proje Hakkında
- **Geliştirici:** Yunus Emre Eren - 240229020
- **Kurum:** Kocaeli Üniversitesi - Yazılım Mühendisliği Bölümü
- **Ders:** Programlama-2
- **Amaç:** Oyuncunun hedef takip etme ve tepki süresini optimize eden, nesne yönelimli programlama (OOP) prensipleriyle inşa edilmiş 2D bir oyun deneyimi sunmak.

## Kullanılan Teknolojiler
- C++
- SDL2 (Core, Image, TTF)
- VS Code & MSYS2 (MinGW ucrt64)

## Kurulum ve Doğrudan Çalıştırma (Önerilen)
Oyunun çalışması için gerekli tüm motor kütüphaneleri (DLL dosyaları) ve grafik kaynakları (`assets` klasörü) ana dizinde hazır bulunmaktadır. Başka bir bilgisayarda çalıştırmak için:

1. Proje klasörünü (.zip dosyasından) bilgisayarınıza çıkartın.
2. Ana dizindeki **`oyun.exe`** dosyasına çift tıklayarak oyunu hiçbir kurulum yapmadan anında başlatabilirsiniz.

## Kaynak Koddan Derleme (Eğitmenler / Geliştiriciler İçin)
Proje kodlarını kendi sisteminizde sıfırdan derleyip test etmek isterseniz:

1. Sisteminizde `g++` derleyicisinin ve **SDL2 geliştirme kütüphanelerinin** (SDL2, SDL2_image, SDL2_ttf) eksiksiz kurulu olması gerekmektedir.
2. Proje dizininde (Makefile'ın bulunduğu konumda) terminal açıp yalnızca `make` komutunu çalıştırmanız yeterlidir.
> *Not: Derleme sırasında kütüphane veya derleyici bulunamadı hatası alırsanız, lütfen derleyicinizin (bin klasörünün) Windows PATH ortam değişkenlerine eklendiğinden emin olun.*

## Kontroller
- **Menü Navigasyonu:** Fare ile etkileşim (Üzerine gelme ve Tıklama)
- **Oyun İçi:** Fare (Sol Tık) ile hedefleri vurma
- **Ana Menüye Dönüş:** `BACKSPACE` tuşu
- **Oyundan Çıkış:** `ESC` tuşu

## Temel Özellikler
- **Donanımsal İmleç (Hardware Cursor):** Yazılımsal render gecikmesini (input lag) sıfıra indiren işletim sistemi düzeyinde nişangah entegrasyonu.
- **Dinamik Zorluk Seviyeleri:** Kolay, Orta, Zor ve Çok Zor hedefler.
- **Süreli Modlar:** 30 ve 60 saniyelik zaman kısıtlamalı refleks antrenmanları.
- **Gelişmiş İstatistik Takibi:** Anlık skor, art arda vurma (combo) sayacı ve isabet oranı (accuracy) hesaplaması.
- **Görsel Tasarım:** Uzay temalı siberpunk neon estetik ve uzamsal derinlik algısı (2.5D illüzyonu).