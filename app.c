#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OGRENCI 10

typedef struct {
    char isim[30];
    float vize;
    float final;
    float ortalama;
    char harf[3];
} Ogrenci;

int main(void) {
    const int screenWidth = 900;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "GelismiS Ogrenci Yönetim Paneli");
    SetTargetFPS(60);

    Ogrenci ogrenciler[MAX_OGRENCI];
    int ogrenciSayisi = 0;

    // Girdi Kutusu Değişkenleri
    char isimBuf[30] = "\0";
    char vizeBuf[10] = "\0";
    char finalBuf[10] = "\0";
    
    int aktifKutu = 0; // 1: Isim, 2: Vize, 3: Final

    Rectangle isimKutusu = { 50, 100, 180, 35 };
    Rectangle vizeKutusu = { 250, 100, 100, 35 };
    Rectangle finalKutusu = { 370, 100, 100, 35 };
    Rectangle ekleButon = { 490, 100, 120, 35 };

    while (!WindowShouldClose()) {
        // --- GİRDİ KONTROLLERİ ---
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointRec(mousePos, isimKutusu)) aktifKutu = 1;
            else if (CheckCollisionPointRec(mousePos, vizeKutusu)) aktifKutu = 2;
            else if (CheckCollisionPointRec(mousePos, finalKutusu)) aktifKutu = 3;
            else if (CheckCollisionPointRec(mousePos, ekleButon)) {
                // Öğrenci Ekleme Mantığı
                if (strlen(isimBuf) > 0 && ogrenciSayisi < MAX_OGRENCI) {
                    strcpy(ogrenciler[ogrenciSayisi].isim, isimBuf);
                    ogrenciler[ogrenciSayisi].vize = atof(vizeBuf);
                    ogrenciler[ogrenciSayisi].final = atof(finalBuf);
                    
                    float ort = (ogrenciler[ogrenciSayisi].vize * 0.4f) + (ogrenciler[ogrenciSayisi].final * 0.6f);
                    ogrenciler[ogrenciSayisi].ortalama = ort;

                    if (ort >= 90) strcpy(ogrenciler[ogrenciSayisi].harf, "AA");
                    else if (ort >= 80) strcpy(ogrenciler[ogrenciSayisi].harf, "BA");
                    else if (ort >= 70) strcpy(ogrenciler[ogrenciSayisi].harf, "BB");
                    else if (ort >= 60) strcpy(ogrenciler[ogrenciSayisi].harf, "CB");
                    else if (ort >= 50) strcpy(ogrenciler[ogrenciSayisi].harf, "CC");
                    else strcpy(ogrenciler[ogrenciSayisi].harf, "FF");

                    ogrenciSayisi++;
                    
                    // Kutuları Temizle
                    isimBuf[0] = '\0';
                    vizeBuf[0] = '\0';
                    finalBuf[0] = '\0';
                    aktifKutu = 0;
                }
            } else {
                aktifKutu = 0;
            }
        }

        // Klavyeden Yazı Alma
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125)) {
                if (aktifKutu == 1 && strlen(isimBuf) < 25) {
                    int len = strlen(isimBuf);
                    isimBuf[len] = (char)key;
                    isimBuf[len + 1] = '\0';
                } else if (aktifKutu == 2 && strlen(vizeBuf) < 5) {
                    int len = strlen(vizeBuf);
                    vizeBuf[len] = (char)key;
                    vizeBuf[len + 1] = '\0';
                } else if (aktifKutu == 3 && strlen(finalBuf) < 5) {
                    int len = strlen(finalBuf);
                    finalBuf[len] = (char)key;
                    finalBuf[len + 1] = '\0';
                }
            }
            key = GetCharPressed();
        }

        // Backspace (Silme) Kontrolü
        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (aktifKutu == 1 && strlen(isimBuf) > 0) isimBuf[strlen(isimBuf) - 1] = '\0';
            if (aktifKutu == 2 && strlen(vizeBuf) > 0) vizeBuf[strlen(vizeBuf) - 1] = '\0';
            if (aktifKutu == 3 && strlen(finalBuf) > 0) finalBuf[strlen(finalBuf) - 1] = '\0';
        }

        // --- ÇİZİM AŞAMASI ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Panel Başlığı
        DrawRectangle(0, 0, screenWidth, 60, DARKBLUE);
        DrawText("OGRENCI NOT YONETIM PANELI", 50, 18, 22, WHITE);

        // Form Alanı Etiketleri
        DrawText("Ogrenci Adi", 50, 78, 14, DARKGRAY);
        DrawText("Vize (%40)", 250, 78, 14, DARKGRAY);
        DrawText("Final (%60)", 370, 78, 14, DARKGRAY);

        // Girdi Kutularını Çizme
        DrawRectangleRec(isimKutusu, LIGHTGRAY);
        DrawRectangleLinesEx(isimKutusu, 2, (aktifKutu == 1) ? BLUE : GRAY);
        DrawText(isimBuf, isimKutusu.x + 8, isimKutusu.y + 8, 18, BLACK);

        DrawRectangleRec(vizeKutusu, LIGHTGRAY);
        DrawRectangleLinesEx(vizeKutusu, 2, (aktifKutu == 2) ? BLUE : GRAY);
        DrawText(vizeBuf, vizeKutusu.x + 8, vizeKutusu.y + 8, 18, BLACK);

        DrawRectangleRec(finalKutusu, LIGHTGRAY);
        DrawRectangleLinesEx(finalKutusu, 2, (aktifKutu == 3) ? BLUE : GRAY);
        DrawText(finalBuf, finalKutusu.x + 8, finalKutusu.y + 8, 18, BLACK);

        // Ekle Butonu
        DrawRectangleRec(ekleButon, DARKGREEN);
        DrawText("KAYDET", ekleButon.x + 25, ekleButon.y + 8, 16, WHITE);

        // Tablo Başlığı
        DrawRectangle(50, 160, 800, 30, SKYBLUE);
        DrawText("ISIM", 60, 167, 16, BLACK);
        DrawText("VIZE", 260, 167, 16, BLACK);
        DrawText("FINAL", 380, 167, 16, BLACK);
        DrawText("ORTALAMA", 500, 167, 16, BLACK);
        DrawText("HARF NOTU", 660, 167, 16, BLACK);

        // Liste Verileri
        int startY = 200;
        for (int i = 0; i < ogrenciSayisi; i++) {
            Color harfRengi = (ogrenciler[i].ortalama >= 50) ? DARKGREEN : RED;

            DrawText(ogrenciler[i].isim, 60, startY, 16, DARKGRAY);
            DrawText(TextFormat("%.1f", ogrenciler[i].vize), 260, startY, 16, DARKGRAY);
            DrawText(TextFormat("%.1f", ogrenciler[i].final), 380, startY, 16, DARKGRAY);
            DrawText(TextFormat("%.2f", ogrenciler[i].ortalama), 500, startY, 16, DARKGRAY);
            DrawText(ogrenciler[i].harf, 660, startY, 16, harfRengi);

            DrawLine(50, startY + 25, 850, startY + 25, LIGHTGRAY);
            startY += 35;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}