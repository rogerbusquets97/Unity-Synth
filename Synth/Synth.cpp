// Synth.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "olcNoiseMaker.h"
#include "Audio.h"

std::atomic<double> kAmplitude = 1.0;
std::atomic<double> kFrequency = 0.0;

Audio::sEnvelopeASDR Envelope;

#define MASTER_VOLUME 0.4

double MakeNoise(double dTime)
{
    double dOutput = Envelope.GetAmplitude(Audio::GetWaveSound(Audio::OscilatorType::Square, kFrequency, kAmplitude, dTime));

    return dOutput * MASTER_VOLUME;
}

int main()
{
    std::vector<std::wstring> devices = olcNoiseMaker<short>::Enumerate();

    for (auto d : devices)
    {
        std::wcout << "Found output device: " << d << endl;
    }

    olcNoiseMaker<short> sound(devices[0], 44100, 1U, 8U, 512U);
    sound.SetUserFunction(MakeNoise);
    
    double OctaveBaseFrequency = 110.0; // A2
    double d12thRootOf2 = pow(2.0, 1.0 / 12.0);

    int nCurrentKey = -1;
    bool bKeyPressed = false;

    while(true)
    {
        for (int k = 0; k < 16; k++)
        {
            if (GetAsyncKeyState((unsigned char)("ZSXCFVGBNJMK\xbcL\xbe\xbf"[k])) & 0x8000)
            {
                if (nCurrentKey != k)
                {
                    kFrequency = OctaveBaseFrequency * pow(d12thRootOf2, k);
                    Envelope.NoteOn(sound.GetTime());
                    nCurrentKey = k;
                }
                bKeyPressed = true;
            }
        }

        if (!bKeyPressed)
        {
            if (nCurrentKey != -1)
            {
                Envelope.NoteOff(sound.GetTime());
                nCurrentKey = -1;
            }
        }
    }

    return 0;
}
