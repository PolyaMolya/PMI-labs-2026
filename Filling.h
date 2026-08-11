#pragma once
void Fill(struct Xn* r, float(*function)(float prev, float x, int n), float x);
void Errors(struct Xn* r, float(*etalon)(float x), float x);
void Sum(struct Xn* r);
